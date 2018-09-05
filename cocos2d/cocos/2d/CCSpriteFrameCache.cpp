/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2009      Jason Booth
Copyright (c) 2009      Robert J Payne
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#include "2d/CCSpriteFrameCache.h"

#include <vector>


#include "2d/CCSprite.h"
#include "platform/CCFileUtils.h"
#include "base/CCNS.h"
#include "base/ccMacros.h"
#include "base/CCDirector.h"
#include "renderer/CCTexture2D.h"
#include "renderer/CCTextureCache.h"
#include "base/CCNinePatchImageParser.h"

#include "deprecated/CCString.h"
#include "base/ZipUtils.h"
#include "base/CCGlobalLock.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#endif
using namespace std;


static int myStrToInt(const char *str, unsigned int& pos) {
    int x = 0;
    bool neg = false;
    const char* p = str;
    while (true) {
        if( *p == 0 || *p == '-' || (*p >= '0' && *p <= '9'))
        {
            break;
        }
        ++p;
    }
    
    if (*p == '-') {
        neg = true;
        ++p;
    }
    while (*p >= '0' && *p <= '9') {
        x = (x*10) + (*p - '0');
        ++p;
    }
    if (neg) {
        x = -x;
    }
    pos = p - str;
    return x;
}
//extern void addSpriteframeToFirebaseDatabase(const std::string& filename);
bool unCompress(const char * pOutFileName,std::string &writePath);

void splitString(const std::string& strSrc, const std::string& strFind, std::vector<std::string>& arSplit)
{
    string tmpStr(strSrc.data(),strSrc.length());
    
    if(tmpStr.length() > strFind.length())
    {
        while (!tmpStr.empty() && tmpStr.find(strFind.c_str()) == 0) {
            tmpStr = tmpStr.substr(strFind.length(), tmpStr.length()-strFind.length());
        }
        while (!tmpStr.empty() && tmpStr.rfind(strFind.c_str()) == (tmpStr.length()-strFind.length())) {
            tmpStr = tmpStr.substr(0, tmpStr.length()-strFind.length());
        }
    }
    
    char* src = const_cast<char*>(tmpStr.c_str());
    while (src != nullptr && !tmpStr.empty()) {
        arSplit.push_back(std::string(strtok_r(src, strFind.c_str(), &src)));
    }
}



NS_CC_BEGIN

static SpriteFrameCache *_sharedSpriteFrameCache = nullptr;

#define SAFE_FUN_LOCK GlobalLock::AutoLock autolock_tmp_by_type(GlobalLock::Class_Mutex::Class_SpriteFrameCache)

//extern bool g_enable_add_image_async_switch;
static bool gEnableSpriteFrameCache = true;

struct SpriteFrameInner {
//    Vec2 _offset;
//    Size _originalSize;
    Rect _rectInPixels;
    bool   _rotated;
//    Rect _rect;
    Vec2 _offsetInPixels;
    Size _originalSizeInPixels;
    std::string name;
};

void getSpriteFrameMyInner( CCSpriteFrame* in, SpriteFrameInner& out, std::string name ) {
//    out._offset = in->getOffset();
//    out._originalSize = in->getOriginalSize();
    out._rectInPixels = in->getRectInPixels();
    out._rotated = in->isRotated();
//    out._rect = in->getRect();
    out._offsetInPixels = in->getOffsetInPixels();
    out._originalSizeInPixels = in->getOriginalSizeInPixels();
    out.name = name;
}

CCSpriteFrame* createSpriteFrameFromMyInner( const SpriteFrameInner& in, Texture2D* texture ) {
    auto ret = SpriteFrame::createWithTexture(texture,
                                            in._rectInPixels,
                                            in._rotated,
                                            in._offsetInPixels,
                                            in._originalSizeInPixels);
    ret->setTextureFileName(in.name);
    return ret;
}



static std::unordered_multimap<std::string,SpriteFrameInner> g_spriteframeFastCache;
struct TexureInfoStruct {
    Size size;
    string filename;
    bool isGood{false};
    bool isScale{false};
    float scaleRate{1.0f};
};
static std::unordered_map<std::string, TexureInfoStruct> g_spriteframeTextureSizeCache;

SpriteFrameCache* SpriteFrameCache::getInstance()
{
    SAFE_FUN_LOCK;
    if (! _sharedSpriteFrameCache)
    {
        _sharedSpriteFrameCache = new (std::nothrow) SpriteFrameCache();
        _sharedSpriteFrameCache->init();
    }

    return _sharedSpriteFrameCache;
}

void SpriteFrameCache::destroyInstance()
{
    SAFE_FUN_LOCK;
    CC_SAFE_RELEASE_NULL(_sharedSpriteFrameCache);
}

bool SpriteFrameCache::init()
{
    SAFE_FUN_LOCK;
    _spriteFrames.reserve(20);
    _spriteFramesAliases.reserve(20);
    _loadedFileNames = new std::set<std::string>();
    return true;
}

SpriteFrameCache::~SpriteFrameCache()
{
    CC_SAFE_DELETE(_loadedFileNames);
}

bool SpriteFrameCache::addSpriteFramesWithDictionaryNOTexture(ValueMap& dictionary, const std::string& textureName,const std::string& frameName)
{
    SAFE_FUN_LOCK;
    bool bRet = false;
    if( dictionary["frames"].getType() != Value::Type::MAP )
        return false;
    
    ValueMap& framesDict = dictionary["frames"].asValueMap();
    
    
    int format = 0;
    
    // get the format
    if (dictionary.find("metadata") != dictionary.end())
    {
        ValueMap& metadataDict = dictionary["metadata"].asValueMap();
        format = metadataDict["format"].asInt();
    }
    
    // check the format
    CCASSERT(format >=0 && format <= 3, "format is not supported for SpriteFrameCache addSpriteFramesWithDictionary:textureFilename:");
    
    auto textureFileName = textureName;
    
    Image* image = nullptr;
    
    for (auto iter = framesDict.begin(); iter != framesDict.end(); ++iter)
    {
        ValueMap& frameDict = iter->second.asValueMap();
        std::string spriteFrameName = iter->first;

        if(format == 0)
        {
            float x = frameDict["x"].asFloat();
            float y = frameDict["y"].asFloat();
            float w = frameDict["width"].asFloat();
            float h = frameDict["height"].asFloat();
            float ox = frameDict["offsetX"].asFloat();
            float oy = frameDict["offsetY"].asFloat();
            int ow = frameDict["originalWidth"].asInt();
            int oh = frameDict["originalHeight"].asInt();
            // check ow/oh
            if(!ow || !oh)
            {
                CCLOGWARN("cocos2d: WARNING: originalWidth/Height not found on the SpriteFrame. AnchorPoint won't work as expected. Regenrate the .plist");
            }
            // abs ow/oh
            ow = abs(ow);
            oh = abs(oh);
        }
        else if(format == 1 || format == 2)
        {
            Rect frame = RectFromString(frameDict["frame"].asString());
            bool rotated = false;
            
            // rotation
            if (format == 2)
            {
                rotated = frameDict["rotated"].asBool();
            }
            
            Vec2 offset = PointFromString(frameDict["offset"].asString());
            Size sourceSize = SizeFromString(frameDict["sourceSize"].asString());
            
            if (frameName == spriteFrameName)
            {
                image = new (std::nothrow) Image();
                
                std::string _pngpath = FileUtils::getInstance()->getWritablePath();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
                CC_BREAK_IF(!image->initWithETCDataBySoftUncompressed(textureName, frame,rotated));
                _pngpath = _pngpath + "imageCaches/";
#else
                 CC_BREAK_IF(!image->initWithPVRv2Data(textureName, frame,rotated));
                _pngpath = _pngpath.substr(0,_pngpath.length()-10) + "Library/Caches/imageCaches/";
#endif
                if(!FileUtils::getInstance()->createDirectory(_pngpath.c_str()))
                {
                    bRet = false;
                    break;
                }
                
                _pngpath = _pngpath+frameName;
                
                if (FileUtils::getInstance()->isFileExist(_pngpath))
                {
                    std::remove(_pngpath.c_str());
                }
                CCLOG("_pngpath=%s", _pngpath.c_str());
                image->saveToFile(_pngpath, false);
                
                bRet = true;
            }
        }
        else if (format == 3)
        {
            // get values
            Size spriteSize = SizeFromString(frameDict["spriteSize"].asString());
            Vec2 spriteOffset = PointFromString(frameDict["spriteOffset"].asString());
            Size spriteSourceSize = SizeFromString(frameDict["spriteSourceSize"].asString());
            Rect textureRect = RectFromString(frameDict["textureRect"].asString());
            bool textureRotated = frameDict["textureRotated"].asBool();
            
            // get aliases
            ValueVector& aliases = frameDict["aliases"].asValueVector();
            
            for(const auto &value : aliases) {
                std::string oneAlias = value.asString();
                if (_spriteFramesAliases.find(oneAlias) != _spriteFramesAliases.end())
                {
                    CCLOGWARN("cocos2d: WARNING: an alias with name %s already exists", oneAlias.c_str());
                }
                
                _spriteFramesAliases[oneAlias] = Value(spriteFrameName);
            }
            
            if (frameName == spriteFrameName)
            {
                image = new (std::nothrow) Image();

                std::string _pngpath = FileUtils::getInstance()->getWritablePath();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
               CC_BREAK_IF(!image->initWithETCDataBySoftUncompressed(textureName, textureRect,textureRotated));
                _pngpath = _pngpath + "imageCaches/";
#else
               CC_BREAK_IF(!image->initWithPVRv2Data(textureName, textureRect,textureRotated));
                _pngpath = _pngpath.substr(0,_pngpath.length()-10) + "Library/Caches/imageCaches/";
#endif
                
                if(!FileUtils::getInstance()->createDirectory(_pngpath.c_str()))
                {
                    bRet = false;
                    break;
                }
                
                _pngpath = _pngpath+frameName;
                if (FileUtils::getInstance()->isFileExist(_pngpath))
                {
                    std::remove(_pngpath.c_str());
                }
                CCLOG("_pngpath=%s", _pngpath.c_str());
                image->saveToFile(_pngpath, false);
                
                bRet = true;
            }
            

        }
        
    }
    
     CC_SAFE_DELETE(image);
    
    return bRet;
}
/*
 * 针对重复名称图片资源，
 * 1. 重复资源在debug的时候提醒给开发人员
 * 2. 重复名称不加入移除队列
*/

#define FRAME_NAME_FIX (1)




bool SpriteFrameCache::addSpriteFramesWithDictionary(ValueMap& dictionary, Texture2D* texture, const std::string& plistName)
{
    SAFE_FUN_LOCK;
    /*
    Supported Zwoptex Formats:

    ZWTCoordinatesFormatOptionXMLLegacy = 0, // Flash Version
    ZWTCoordinatesFormatOptionXML1_0 = 1, // Desktop Version 0.0 - 0.4b
    ZWTCoordinatesFormatOptionXML1_1 = 2, // Desktop Version 1.0.0 - 1.0.1
    ZWTCoordinatesFormatOptionXML1_2 = 3, // Desktop Version 1.0.2+
    */

    if( dictionary["frames"].getType() != Value::Type::MAP )
        return false;
    
    ValueMap& framesDict = dictionary["frames"].asValueMap();
    
 
    int format = 0;

    // get the format
    if (dictionary.find("metadata") != dictionary.end())
    {
        ValueMap& metadataDict = dictionary["metadata"].asValueMap();
        format = metadataDict["format"].asInt();
    }

    // check the format
    CCASSERT(format >=0 && format <= 3, "format is not supported for SpriteFrameCache addSpriteFramesWithDictionary:textureFilename:");

    auto textureFileName = Director::getInstance()->getTextureCache()->getTextureFilePath(texture);
    bool isGood = true;
    Image* image = nullptr;
    NinePatchImageParser parser;
    for (auto iter = framesDict.begin(); iter != framesDict.end(); ++iter)
    {
        ValueMap& frameDict = iter->second.asValueMap();
        std::string spriteFrameName = iter->first;
        SpriteFrame* spriteFrame = _spriteFrames.at(spriteFrameName);
        if (spriteFrame)
        {
            if(FRAME_NAME_FIX && plistName != "")
            {
               _sameNameFrames[plistName][spriteFrameName] = 1;
            }

            isGood = false;
            continue;
        }
        
        if(format == 0) 
        {
            float x = frameDict["x"].asFloat();
            float y = frameDict["y"].asFloat();
            float w = frameDict["width"].asFloat();
            float h = frameDict["height"].asFloat();
            float ox = frameDict["offsetX"].asFloat();
            float oy = frameDict["offsetY"].asFloat();
            int ow = frameDict["originalWidth"].asInt();
            int oh = frameDict["originalHeight"].asInt();
            // check ow/oh
            if(!ow || !oh)
            {
                CCLOGWARN("cocos2d: WARNING: originalWidth/Height not found on the SpriteFrame. AnchorPoint won't work as expected. Regenrate the .plist");
            }
            // abs ow/oh
            ow = abs(ow);
            oh = abs(oh);
            // create frame
            spriteFrame = SpriteFrame::createWithTexture(texture,
                                                         Rect(x, y, w, h),
                                                         false,
                                                         Vec2(ox, oy),
                                                         Size((float)ow, (float)oh)
                                                         );
        } 
        else if(format == 1 || format == 2) 
        {
            Rect frame = RectFromString(frameDict["frame"].asString());
            bool rotated = false;

            // rotation
            if (format == 2)
            {
                rotated = frameDict["rotated"].asBool();
            }

            Vec2 offset = PointFromString(frameDict["offset"].asString());
            Size sourceSize = SizeFromString(frameDict["sourceSize"].asString());

            // create frame
            spriteFrame = SpriteFrame::createWithTexture(texture,
                                                         frame,
                                                         rotated,
                                                         offset,
                                                         sourceSize
                                                         );
        } 
        else if (format == 3)
        {
            // get values
            Size spriteSize = SizeFromString(frameDict["spriteSize"].asString());
            Vec2 spriteOffset = PointFromString(frameDict["spriteOffset"].asString());
            Size spriteSourceSize = SizeFromString(frameDict["spriteSourceSize"].asString());
            Rect textureRect = RectFromString(frameDict["textureRect"].asString());
            bool textureRotated = frameDict["textureRotated"].asBool();

            // get aliases
            ValueVector& aliases = frameDict["aliases"].asValueVector();

            for(const auto &value : aliases) {
                std::string oneAlias = value.asString();
                if (_spriteFramesAliases.find(oneAlias) != _spriteFramesAliases.end())
                {
                    CCLOGWARN("cocos2d: WARNING: an alias with name %s already exists", oneAlias.c_str());
                }

                _spriteFramesAliases[oneAlias] = Value(spriteFrameName);
            }

            // create frame
            spriteFrame = SpriteFrame::createWithTexture(texture,
                                                         Rect(textureRect.origin.x, textureRect.origin.y, spriteSize.width, spriteSize.height),
                                                         textureRotated,
                                                         spriteOffset,
                                                         spriteSourceSize);
        }

        bool flag = NinePatchImageParser::isNinePatchImage(spriteFrameName);
        if(flag)
        {
            if (image == nullptr) {
                image = new Image();
                image->initWithImageFile(textureFileName);
            }
            parser.setSpriteFrameInfo(image, spriteFrame->getRectInPixels(), spriteFrame->isRotated());
            texture->addSpriteFrameCapInset(spriteFrame, parser.parseCapInset());
        }
        // add sprite frame
        _spriteFrames.insert(spriteFrameName, spriteFrame);
        spriteFrame->setTextureFileName(spriteFrameName);
    }
    CC_SAFE_DELETE(image);
    dictionary["isGood"] = Value(isGood);
    if(!isGood)
    {
        CCLOG("ERROR SAME NAME %s",plistName.c_str());
    }
    return true;
}

void SpriteFrameCache::addSpriteFramesWithFile(const std::string& plist, Texture2D *texture)
{
    SAFE_FUN_LOCK;
    
    if (_loadedFileNames->find(plist) != _loadedFileNames->end())
    {
        return; // We already added it10
    }
    if(gEnableSpriteFrameCache)
    {
        auto&& plist_file_name = plist;
        if(!plist_file_name.empty()) {
            
            if( g_spriteframeFastCache.find(plist_file_name) != g_spriteframeFastCache.end() ) {
                auto range = g_spriteframeFastCache.equal_range(plist_file_name);
                for_each (
                          range.first,
                          range.second,
                          [this,texture](std::unordered_multimap<std::string,SpriteFrameInner>::value_type& x)
                          {
                              //                                std::cout << " " << x.second;
                              auto ret = createSpriteFrameFromMyInner(x.second, texture);
                              _spriteFrames.insert(x.second.name, ret);
                          }
                          );
                 _loadedFileNames->insert(plist);
                return;
            }
        }
    }
#if (COCOS2D_DEBUG == 0) && (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    getPlistFilePath(plist);
#endif
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(plist);
    ValueMap dict = FileUtils::getInstance()->getValueMapFromFile(fullPath);

    addSpriteFramesWithDictionary(dict, texture, plist);
    _loadedFileNames->insert(plist);
}

void SpriteFrameCache::addSpriteFramesWithFileContent(const std::string& plist_content, Texture2D *texture)
{
    SAFE_FUN_LOCK;
    ValueMap dict = FileUtils::getInstance()->getValueMapFromData(plist_content.c_str(), static_cast<int>(plist_content.size()));
    addSpriteFramesWithDictionary(dict, texture, "");
}

void SpriteFrameCache::addSpriteFramesWithFile(const std::string& plist, const std::string& textureFileName)
{
    SAFE_FUN_LOCK;
    
    CCASSERT(textureFileName.size()>0, "texture name should not be null");
    
    Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(textureFileName,false);

    if (texture)
    {
        addSpriteFramesWithFile(plist, texture);
    }
    else
    {
        CCLOG("cocos2d: SpriteFrameCache: couldn't load texture file. File not found %s", textureFileName.c_str());
    }
    
}

void SpriteFrameCache::addSpriteFramesWithFile(const std::string& plist)
{
    SAFE_FUN_LOCK;
    
    CCASSERT(plist.size()>0, "plist filename should not be nullptr");
    
#if (COCOS2D_DEBUG == 0) && (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    getPlistFilePath(plist);
#endif
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(plist);
    if (fullPath.size() == 0)
    {
        // return if plist file doesn't exist
        CCLOG("cocos2d: SpriteFrameCache: can not find %s", plist.c_str());
        return;
    }

    if (_loadedFileNames->find(plist) != _loadedFileNames->end())
    {
        return;
    }
    if(gEnableSpriteFrameCache)
    {
        auto&& plist_file_name = plist;
        if(!plist_file_name.empty()) {
            
            if( g_spriteframeFastCache.find(plist_file_name) != g_spriteframeFastCache.end() ) {
//                string texturePath = plist_file_name;
                
//                texturePath.replace(texturePath.length() - 5, 5, "pvr.ccz");
//                Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(texturePath);
                
                auto&& textureinfo = g_spriteframeTextureSizeCache[plist];
                Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(textureinfo.filename
                                ,textureinfo.size,false);
                if( textureinfo.isScale ) {
                    if( texture ) {
                        texture->_scaleRate = textureinfo.scaleRate;
                    }
                }
                auto range = g_spriteframeFastCache.equal_range(plist_file_name);
                for_each (
                          range.first,
                          range.second,
                          [this,texture](std::unordered_multimap<std::string,SpriteFrameInner>::value_type& x)
                          {
                              //                                std::cout << " " << x.second;
                              auto ret = createSpriteFrameFromMyInner(x.second, texture);
                              _spriteFrames.insert(x.second.name, ret);
                          }
                          );
                _loadedFileNames->insert(plist);
                return;
            }
        }
    }
    
    string texturePath("");

    {
        
        
        
        
        ValueMap dict = FileUtils::getInstance()->getValueMapFromFile(fullPath);

        
        string texturePath("");
        Size textureSize;
        float scaleRate = 1.0f;
        if (dict.find("metadata") != dict.end())
        {
            ValueMap& metadataDict = dict["metadata"].asValueMap();
            // try to read  texture file name from meta data
            texturePath = metadataDict["textureFileName"].asString();
            
            string strSize = metadataDict["size"].asString();
            int w{0},h{0};
//            sscanf(strSize.c_str(), "{%d,%d}", &w, &h);
            unsigned int pos = 0;
            w = myStrToInt(strSize.c_str(),pos);
            h = myStrToInt(&(strSize.c_str()[pos]), pos);
            textureSize = Size(w,h);
            float tmpsr = metadataDict["scale"].asFloat();
            if( tmpsr != 0.0f ) {
                scaleRate = tmpsr;
            }
        }

        if (!texturePath.empty())
        {
            // build texture path relative to plist file
            texturePath = FileUtils::getInstance()->fullPathFromRelativeFile(texturePath.c_str(), plist);
        }
        else
        {
            // build texture path by replacing file extension
            texturePath = plist;

            // remove .xxx
            size_t startPos = texturePath.find_last_of("."); 
            texturePath = texturePath.erase(startPos);

            // append .png
            texturePath = texturePath.append(".png");

            CCLOG("cocos2d: SpriteFrameCache: Trying to use file %s as texture", texturePath.c_str());
        }
        bool isGood = false;

        
        Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(texturePath.c_str()
            ,textureSize,false);
        if (texture)
        {
            texture->_scaleRate = scaleRate;
            addSpriteFramesWithDictionary(dict, texture, plist);
            _loadedFileNames->insert(plist);
            Value resGood = dict["isGood"];
            if(!resGood.isNull()) {
                isGood = resGood.asBool();
            }
        }
        else
        {
            CCLOG("cocos2d: SpriteFrameCache: Couldn't load texture");
        }
        TexureInfoStruct tis;
        tis.size = textureSize;
        tis.filename = texturePath;
        tis.isGood = isGood;
        tis.scaleRate = scaleRate;
        tis.isScale = scaleRate != 1.0f ? true:false;
        g_spriteframeTextureSizeCache[plist] = tis;
    }
}

bool SpriteFrameCache::addSpriteFramesWithFileNoTexture(const std::string& plist, const std::string& framename)
{
    SAFE_FUN_LOCK;
    
    CCASSERT(plist.size()>0, "plist filename should not be nullptr");
    
#if (COCOS2D_DEBUG == 0) && (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    getPlistFilePath(plist);
#endif
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(plist);
    if (fullPath.size() == 0)
    {
        // return if plist file doesn't exist
        CCLOG("cocos2d: SpriteFrameCache: can not find %s", plist.c_str());
        return false;
    }
    
//    if (_loadedFileNames->find(plist) != _loadedFileNames->end())
//    {
//        return;
//    }
    bool bRet = false;
    string texturePath("");

    {
        
        ValueMap dict = FileUtils::getInstance()->getValueMapFromFile(fullPath);
        
        
        string texturePath("");
        float scaleRate = 1.0f;
        if (dict.find("metadata") != dict.end())
        {
            ValueMap& metadataDict = dict["metadata"].asValueMap();
            // try to read  texture file name from meta data
            texturePath = metadataDict["textureFileName"].asString();
            float tmpsr = metadataDict["scale"].asFloat();
            if ( tmpsr != 0.0f ) {
                scaleRate = tmpsr;
            }
        }
        
        if (!texturePath.empty())
        {
            // build texture path relative to plist file
            texturePath = FileUtils::getInstance()->fullPathFromRelativeFile(texturePath.c_str(), plist);
        }
        else
        {
            // build texture path by replacing file extension
            texturePath = plist;
            
            // remove .xxx
            size_t startPos = texturePath.find_last_of(".");
            texturePath = texturePath.erase(startPos);
            
            // append .png
            texturePath = texturePath.append(".png");
            
            CCLOG("cocos2d: SpriteFrameCache: Trying to use file %s as texture", texturePath.c_str());
        }
//        TextureCache::sharedTextureCache()->EnableDefaultTexture(false);
//        Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(texturePath.c_str());
//        TextureCache::sharedTextureCache()->EnableDefaultTexture(true);
//        if (texture)
//        {
            bRet = addSpriteFramesWithDictionaryNOTexture(dict, texturePath, framename);
//            _loadedFileNames->insert(plist);
//        }
//        else
//        {
//            CCLOG("cocos2d: SpriteFrameCache: Couldn't load texture");
//        }
    }
    
    return bRet;
}

bool SpriteFrameCache::getSpriteFramesWithFile(const std::string& plist, ValueMap& dict, std::string& textPath, unsigned char*& CCZbuffer, int& CCZsize)
{
    SAFE_FUN_LOCK;
    
    CCASSERT(plist.size()>0, "plist filename should not be nullptr");
    
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(plist);
    if (fullPath.size() == 0)
    {
        // return if plist file doesn't exist
        CCLOG("cocos2d: SpriteFrameCache: can not find %s", plist.c_str());
        return false;
    }
    
    CCZbuffer = NULL;
    CCZsize = 0;
    
    // 没有较好的同步方案，暂时屏蔽。在加入的时候会判断
//    if (_loadedFileNames->find(plist) != _loadedFileNames->end())
//    {
//        return;
//    }
    string texturePath("");

    {
        
        /*ValueMap*/ dict = FileUtils::getInstance()->getValueMapFromFile(fullPath);
        
        
        string texturePath("");
        
        if (dict.find("metadata") != dict.end())
        {
            ValueMap& metadataDict = dict["metadata"].asValueMap();
            // try to read  texture file name from meta data
            texturePath = metadataDict["textureFileName"].asString();
        }
        
        if (!texturePath.empty())
        {
            // build texture path relative to plist file
            texturePath = FileUtils::getInstance()->fullPathFromRelativeFile(texturePath.c_str(), plist);
        }
        else
        {
            // build texture path by replacing file extension
            texturePath = plist;
            
            // remove .xxx
            size_t startPos = texturePath.find_last_of(".");
            texturePath = texturePath.erase(startPos);
            
            // append .png
            texturePath = texturePath.append(".png");
            
            CCLOG("cocos2d: SpriteFrameCache: Trying to use file %s as texture", texturePath.c_str());
        }
        
        textPath = texturePath;
    }

    return true;
}

bool SpriteFrameCache::isSpriteFramesWithFileLoaded(const std::string& plist) const
{
    SAFE_FUN_LOCK;
    bool result = false;

    if (_loadedFileNames->find(plist) != _loadedFileNames->end())
    {
        result = true;
    }

    return result;
}

void SpriteFrameCache::addSpriteFrame(SpriteFrame* frame, const std::string& frameName)
{
    SAFE_FUN_LOCK;
    _spriteFrames.insert(frameName, frame);
    frame->setTextureFileName(frameName);
}

void SpriteFrameCache::removeSpriteFrames()
{
    SAFE_FUN_LOCK;
    _spriteFrames.clear();
    _spriteFramesAliases.clear();
    _loadedFileNames->clear();
}

void SpriteFrameCache::dumpSpriteFrames() {
    SAFE_FUN_LOCK;
    cocos2d::log("begin dumpSpriteFrames");
    
    
    for (auto iter = _spriteFrames.begin(); iter != _spriteFrames.end(); ++iter)
    {
        SpriteFrame* spriteFrame = iter->second;

        cocos2d::log("key: %s texture: %s", iter->first.c_str(), spriteFrame->getTexture()->getFileName().c_str());
        
    }
    
    cocos2d::log("end dumpSpriteFrames");
}

void SpriteFrameCache::removeUnusedSpriteFrames()
{
    SAFE_FUN_LOCK;
    bool removed = false;
    std::vector<std::string> toRemoveFrames;
    
    for (auto iter = _spriteFrames.begin(); iter != _spriteFrames.end(); ++iter)
    {
        SpriteFrame* spriteFrame = iter->second;
        if( spriteFrame->getReferenceCount() == 1 )
        {
            toRemoveFrames.push_back(iter->first);
            spriteFrame->getTexture()->removeSpriteFrameCapInset(spriteFrame);
            CCLOG("cocos2d: SpriteFrameCache: removing unused frame: %s", iter->first.c_str());
            removed = true;
        }
    }

    _spriteFrames.erase(toRemoveFrames);

    // FIXME:. Since we don't know the .plist file that originated the frame, we must remove all .plist from the cache
    if( removed )
    {
        _loadedFileNames->clear();
    }
}


void SpriteFrameCache::removeSpriteFrameByName(const std::string& name)
{
    SAFE_FUN_LOCK;
    // explicit nil handling
    if( !(name.size()>0) )
        return;

    // Is this an alias ?
    std::string key = _spriteFramesAliases[name].asString();

    if (!key.empty())
    {
        _spriteFrames.erase(key);
        _spriteFramesAliases.erase(key);
    }
    else
    {
        _spriteFrames.erase(name);
    }

    // FIXME:. Since we don't know the .plist file that originated the frame, we must remove all .plist from the cache
    _loadedFileNames->clear();
}


void SpriteFrameCache::forceReloadSpriteFrameWithFile(const std::string& plist)
{
    //clear cache
    if(gEnableSpriteFrameCache)
    {
        auto pos = g_spriteframeFastCache.find(plist);
        if(pos != g_spriteframeFastCache.end()) {
            g_spriteframeFastCache.erase(plist);
            g_spriteframeTextureSizeCache.erase(plist);
        }
    }


    // remove it from the cache
    set<string>::iterator ret = _loadedFileNames->find(plist);
    if (ret != _loadedFileNames->end())
    {
        //file already loaded
        _loadedFileNames->erase(ret);
        std::string fullPath = FileUtils::getInstance()->fullPathForFilename(plist);
        ValueMap dict = FileUtils::getInstance()->getValueMapFromFile(fullPath);
        if (dict.empty())
        {
            CCLOG("cocos2d:SpriteFrameCache:removeSpriteFramesFromFile: create dict by %s fail.",plist.c_str());
            return;
        }
        removeSpriteFramesFromDictionary(dict, plist);
        CCTextureCache::sharedTextureCache()->removeUnusedTextures();
        addSpriteFramesWithFile(plist);

    }
}

void SpriteFrameCache::removeSpriteFramesFromFile(const std::string& plist)
{
    SAFE_FUN_LOCK;
    if(gEnableSpriteFrameCache)
    {
        auto pos = g_spriteframeFastCache.find(plist);
        if(pos != g_spriteframeFastCache.end()) {
            
            auto range = g_spriteframeFastCache.equal_range(plist);
            for_each (
                      range.first,
                      range.second,
                      [this](std::unordered_multimap<std::string, SpriteFrameInner>::value_type& x)
                        {
                            _spriteFrames.erase(x.second.name);
                        }
                      );
            // remove it from the cache
            set<string>::iterator ret = _loadedFileNames->find(plist);
            if (ret != _loadedFileNames->end())
            {
                _loadedFileNames->erase(ret);
            }
            return;
        }
    }
    
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(plist);
    ValueMap dict = FileUtils::getInstance()->getValueMapFromFile(fullPath);
    if (dict.empty())
    {
        CCLOG("cocos2d:SpriteFrameCache:removeSpriteFramesFromFile: create dict by %s fail.",plist.c_str());
        return;
    }
    // get the removed the one to the cache
    

    if(gEnableSpriteFrameCache)
    {
        bool isGood = false;
        auto tsc = g_spriteframeTextureSizeCache.find(plist);
        if (tsc != g_spriteframeTextureSizeCache.end()) {
            isGood = tsc->second.isGood;
        }

        if(isGood ) {
            auto&& dictionary = dict;
            if( dictionary["frames"].getType() != Value::Type::MAP )
                return;
            
            ValueMap framesDict = dictionary["frames"].asValueMap();
            std::vector<std::string> keysToRemove;
            
            for (auto iter = framesDict.cbegin(); iter != framesDict.cend(); ++iter)
            {
                if (_spriteFrames.at(iter->first))
                {
                    keysToRemove.push_back(iter->first);
                    
                    SpriteFrameInner sfi;
                    getSpriteFrameMyInner(_spriteFrames.at(iter->first), sfi, iter->first);
                    std::pair<std::string,SpriteFrameInner> mypair(plist,sfi);
                    g_spriteframeFastCache.insert(mypair);
                }
            }
            
            _spriteFrames.erase(keysToRemove);
        }
        else {
            removeSpriteFramesFromDictionary(dict, plist);
        }

        
    }
    else
    {
        removeSpriteFramesFromDictionary(dict, plist);
    }
    // remove it from the cache
    set<string>::iterator ret = _loadedFileNames->find(plist);
    if (ret != _loadedFileNames->end())
    {
        _loadedFileNames->erase(ret);
    }
}

void SpriteFrameCache::removeSpriteFramesFromFileContent(const std::string& plist_content)
{
    SAFE_FUN_LOCK;
    ValueMap dict = FileUtils::getInstance()->getValueMapFromData(plist_content.data(), static_cast<int>(plist_content.size()));
    if (dict.empty())
    {
        CCLOG("cocos2d:SpriteFrameCache:removeSpriteFramesFromFileContent: create dict by fail.");
        return;
    }
    removeSpriteFramesFromDictionary(dict, "");
}

void SpriteFrameCache::removeSpriteFramesFromDictionary(ValueMap& dictionary, const std::string& plistName)
{
    if( dictionary["frames"].getType() != Value::Type::MAP )
        return;
    
    ValueMap framesDict = dictionary["frames"].asValueMap();
    std::vector<std::string> keysToRemove;
    bool checkFile = false;
    if(FRAME_NAME_FIX && plistName != "" && _sameNameFrames.find(plistName)!= _sameNameFrames.end())
    {
       checkFile = true;
    }
    for (auto iter = framesDict.cbegin(); iter != framesDict.cend(); ++iter)
    {
        if (_spriteFrames.at(iter->first))
        {
            if(!checkFile || _sameNameFrames[plistName].find(iter->first) == _sameNameFrames[plistName].end())
                keysToRemove.push_back(iter->first);
        }
    }

    _spriteFrames.erase(keysToRemove);
    _sameNameFrames.erase(plistName);
}

void SpriteFrameCache::removeSpriteFramesFromTexture(Texture2D* texture)
{
    SAFE_FUN_LOCK;
    std::vector<std::string> keysToRemove;

    for (auto iter = _spriteFrames.cbegin(); iter != _spriteFrames.cend(); ++iter)
    {
        std::string key = iter->first;
        SpriteFrame* frame = _spriteFrames.at(key);
        if (frame && (frame->getTexture() == texture))
        {
            keysToRemove.push_back(key);
        }
    }

    _spriteFrames.erase(keysToRemove);
}

SpriteFrame* SpriteFrameCache::getSpriteFrameByName(const std::string& name)
{
    SAFE_FUN_LOCK;
    SpriteFrame* frame = _spriteFrames.at(name);
    if (!frame)
    {
        // try alias dictionary
        std::string key = _spriteFramesAliases[name].asString();
        if (!key.empty())
        {
            frame = _spriteFrames.at(key);
            if (!frame)
            {
                CCLOG("cocos2d: SpriteFrameCache: Frame '%s' not found", name.c_str());
            }
        }
    }
    return frame;
}

bool SpriteFrameCache::addSpriteFramesWithDataNoTexture(const unsigned char* buffer, ssize_t len,const std::string& textureName,const std::string& frameName)
{
    SAFE_FUN_LOCK;
    
    bool bRet = false;
    ssize_t __size = len;
    
    uint8_t len1 = buffer[4];
    
    char tmp[512];
    memset(tmp, 0, sizeof(tmp));
    
    size_t index = 5 + len1;
    
    while (index < __size)
    {
        len1 = buffer[index];
        ++index;
        memset(tmp, 0, sizeof(tmp));
        memcpy(tmp, buffer+index, len1);
        std::string spriteFrameName = string(tmp);
        index += len1;
        Rect frame;
        uint16_t num;
        num = *(uint16_t*)(buffer+index);
        num = CC_SWAP_INT16_LITTLE_TO_HOST(num);
        frame.origin.x = num;
        index += 2;
        num = *(uint16_t*)(buffer+index);
        
        num = CC_SWAP_INT16_LITTLE_TO_HOST(num);
        frame.origin.y = num;
        index += 2;
        num = *(uint16_t*)(buffer+index);
        num = CC_SWAP_INT16_LITTLE_TO_HOST(num);
        frame.size.width = num;
        index += 2;
        num = *(uint16_t*)(buffer+index);
        num = CC_SWAP_INT16_LITTLE_TO_HOST(num);
        frame.size.height = num;
        
        index += 2;
        Point offset;
        int16_t num2;
        num2 = *(int16_t*)(buffer + index);
        num2 = CC_SWAP_INT16_LITTLE_TO_HOST(num2);
        offset.x = num2;
        index += 2;
        num2 = *(int16_t*)(buffer + index);
        num2 = CC_SWAP_INT16_LITTLE_TO_HOST(num2);
        offset.y = num2;
        index += 2;
        
        bool rotated = buffer[index];
        index += 1;
        Size sourceSize;
        num = *(uint16_t*)(buffer+index);
        num = CC_SWAP_INT16_LITTLE_TO_HOST(num);
        sourceSize.width = num;
        index += 2;
        num = *(uint16_t*)(buffer+index);
        num = CC_SWAP_INT16_LITTLE_TO_HOST(num);
        sourceSize.height = num;
        index += 2;
        
        
        if (spriteFrameName == frameName)
        {
            Image* image = new (std::nothrow) Image();
            
            std::string _pngpath = FileUtils::getInstance()->getWritablePath();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
            CC_BREAK_IF(!image->initWithETCDataBySoftUncompressed(textureName, frame,rotated));
            _pngpath = _pngpath + "imageCaches/";
#else
            CC_BREAK_IF(!image->initWithPVRv2Data(textureName, frame,rotated));
            _pngpath = _pngpath.substr(0,_pngpath.length()-10) + "Library/Caches/imageCaches/";
#endif
            
            if(!FileUtils::getInstance()->createDirectory(_pngpath.c_str()))
            {
                bRet = false;
                break;
            }
            
            _pngpath = _pngpath+frameName;
            if (FileUtils::getInstance()->isFileExist(_pngpath))
            {
                std::remove(_pngpath.c_str());
            }
            CCLOG("_pngpath=%s", _pngpath.c_str());
            image->saveToFile(_pngpath, false);
            
            CC_SAFE_DELETE(image);
            
            bRet = true;
            break;
        }
    }
    
    return bRet;
}

//add by elex
void SpriteFrameCache::addSpriteFramesWithData(const unsigned char* buffer, ssize_t len, Texture2D *pobTexture)
{
    SAFE_FUN_LOCK;
    
    ssize_t __size = len;
    
    uint8_t len1 = buffer[4];
    
    char tmp[512];
    memset(tmp, 0, sizeof(tmp));
    
    size_t index = 5 + len1;
    
    while (index < __size)
    {
        len1 = buffer[index];
        ++index;
        memset(tmp, 0, sizeof(tmp));
        memcpy(tmp, buffer+index, len1);
        std::string spriteFrameName = string(tmp);
        index += len1;
        Rect frame;
        uint16_t num;
        num = *(uint16_t*)(buffer+index);
        num = CC_SWAP_INT16_LITTLE_TO_HOST(num);
        frame.origin.x = num;
        index += 2;
        num = *(uint16_t*)(buffer+index);
        
        num = CC_SWAP_INT16_LITTLE_TO_HOST(num);
        frame.origin.y = num;
        index += 2;
        num = *(uint16_t*)(buffer+index);
        num = CC_SWAP_INT16_LITTLE_TO_HOST(num);
        frame.size.width = num;
        index += 2;
        num = *(uint16_t*)(buffer+index);
        num = CC_SWAP_INT16_LITTLE_TO_HOST(num);
        frame.size.height = num;
        
        index += 2;
        Point offset;
        int16_t num2;
        num2 = *(int16_t*)(buffer + index);
        num2 = CC_SWAP_INT16_LITTLE_TO_HOST(num2);
        offset.x = num2;
        index += 2;
        num2 = *(int16_t*)(buffer + index);
        num2 = CC_SWAP_INT16_LITTLE_TO_HOST(num2);
        offset.y = num2;
        index += 2;
        
        bool rotated = buffer[index];
        index += 1;
        Size sourceSize;
        num = *(uint16_t*)(buffer+index);
        num = CC_SWAP_INT16_LITTLE_TO_HOST(num);
        sourceSize.width = num;
        index += 2;
        num = *(uint16_t*)(buffer+index);
        num = CC_SWAP_INT16_LITTLE_TO_HOST(num);
        sourceSize.height = num;
        index += 2;
        
        // create frame
        SpriteFrame* spriteFrame = (SpriteFrame*)_spriteFrames.at(spriteFrameName);
        if (spriteFrame)
        {
            continue;
        }
        
        spriteFrame = new SpriteFrame();
        spriteFrame->initWithTexture(pobTexture,
                                     frame,
                                     rotated,
                                     offset,
                                     sourceSize
                                     );
        // add sprite frame
        _spriteFrames.insert(spriteFrameName, spriteFrame);
        spriteFrame->setTextureFileName(spriteFrameName);
        spriteFrame->release();
        CCLOG("%s=referenceCount=%d",spriteFrameName.c_str(), pobTexture->getReferenceCount());
    }
}
void SpriteFrameCache::addSpriteFramesName(const char *pszPlist)
{
    SAFE_FUN_LOCK;
    if (_loadedFileNames->find(pszPlist) == _loadedFileNames->end())
    {
        _loadedFileNames->insert(pszPlist);
    }
}

void SpriteFrameCache::enableSpriteFrameOptimize(bool val) {
    gEnableSpriteFrameCache = val;
}

#if (COCOS2D_DEBUG == 0) && (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
std::string  SpriteFrameCache::getPlistFilePath(const std::string& plist)
{
    SAFE_FUN_LOCK;
    std::string plistPath = plist;
    std::string plistNoSuffix = plist;
    plistNoSuffix =plistNoSuffix.substr(0,plistNoSuffix.find_last_of("."));
    std::string zipName = plistNoSuffix+".plistf";
    if(FileUtils::sharedFileUtils()->isFileExist(zipName)) {
        plistPath =plistPath.substr(0,plistPath.find_last_of("/"));
        string dir = "";
        if(plistPath.size()>0){
            dir = plistPath + "/";
        }
        std::string fileName = "LResource/" + dir;
        unCompress(zipName.c_str(),fileName);
    }
    return plist;
}
#endif

NS_CC_END
