/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
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

#include "renderer/CCTextureCache.h"

#include <errno.h>
#include <stack>
#include <cctype>
#include <list>

#include "renderer/CCTexture2D.h"
#include "base/ccMacros.h"
#include "base/CCDirector.h"
#include "base/CCScheduler.h"
#include "platform/CCFileUtils.h"
#include "base/ccUtils.h"

#include "deprecated/CCString.h"
#include "base/CCNinePatchImageParser.h"


#ifdef EMSCRIPTEN
#include <emscripten/emscripten.h>
#include "platform/emscripten/CCTextureCacheEmscripten.h"
#endif // EMSCRIPTEN

#include "base/CCGlobalLock.h"
#include <unordered_set>
#include <sys/stat.h>
using namespace std;

std::unordered_set<std::string> g_loading_cache_textures;
bool g_isUseCwrzImage = false;
extern pthread_t MAIN_THREAD_ID;

NS_CC_BEGIN

#define SAFE_FUN_LOCK GlobalLock::AutoLock autolock_tmp_by_type(GlobalLock::Class_Mutex::Class_TextureCache)
// implementation TextureCache



static bool gEnableTextureCacheAsyncSwitch = true;
static bool gEnableTextureCacheImageCacheSwitch = true;



TextureCache * TextureCache::getInstance()
{
    return Director::getInstance()->getTextureCache();
}

TextureCache::TextureCache()
: _loadingThread(nullptr)
, _needQuit(false)
, _asyncRefCount(0)
, _asyncRefCount4Wait(0)
, bDefaultTexture(true)
, _enableSyncAddImageSync(false)
{
}

TextureCache::~TextureCache()
{
    CCLOGINFO("deallocing TextureCache: %p", this);

    for( auto it=_textures.begin(); it!=_textures.end(); ++it)
        (it->second)->release();

    CC_SAFE_DELETE(_loadingThread);
}

// Added by ChenFei 2014-12-16 V3.2 support
__Dictionary* TextureCache::snapshotTextures()
{
    __Dictionary* pRet = new __Dictionary();
    for( auto it=_textures.begin(); it!=_textures.end(); ++it)
    {
        pRet->setObject(it->second, it->first);
    }
    pRet->autorelease();
    return pRet;
}

void TextureCache::destroyInstance()
{
}

TextureCache * TextureCache::sharedTextureCache() 
{
    return Director::getInstance()->getTextureCache();
}

void TextureCache::purgeSharedTextureCache() 
{ 
}

std::string TextureCache::getDescription() const
{
    return StringUtils::format("<TextureCache | Number of textures = %d>", static_cast<int>(_textures.size()));
}

//void TextureCache::addImageAsync(Texture2D* holder, const std::string &path, const std::function<void(Texture2D*)>& callback) {
//    Texture2D *texture = nullptr;
//    
//    std::string fullpath = FileUtils::getInstance()->fullPathForFilename(path);
//    
//    auto it = _textures.find(fullpath);
//    if( it != _textures.end() )
//        texture = it->second;
//    
//    if (texture != nullptr)
//    {
//        holder->setContent(texture);
//        if (callback) callback(holder);
//        return;
//    }
//
//}

struct TextureCache::AsyncStruct
{
public:
    AsyncStruct(const std::string& fn, const std::string& cfn, const std::function<void(Texture2D*)>& f) : filename(fn), callback(f), cachefilename(cfn), pixelFormat(Texture2D::getDefaultAlphaPixelFormat()), loadSuccess(false) {}
    
    std::string filename;
    std::function<void(Texture2D*)> callback;
    Image image;
    Texture2D::PixelFormat pixelFormat;
    bool loadSuccess;
    std::string cachefilename;
    bool notaddCache{false};
    Texture2D* srcTex{nullptr};
};

void TextureCache::waitAddImageAsync( const std::function<void()>& callback ) {
//    if (_asyncStructQueue == nullptr)
//    {
//        if( callback ) {
//            callback();
//        }
//    }
//    else {
//        _asyncMutex.lock();
//        bool isEmpty = _imageInfoQueue->empty();
//        bool isEmpty1 = _asyncStructQueue->empty();
//        _asyncMutex.unlock();
//
//        if( isEmpty && isEmpty1 ) {
//            if( callback ) {
//                callback();
//            }
//        }
////        Director::getInstance()->getScheduler()->unschedule("TextureCache::waitAddImageAsync", this);
//
//        
//        if (0 == _asyncRefCount4Wait)
//        {
//            Director::getInstance()->getScheduler()->schedule([this,callback](float dt){
//                _asyncMutex.lock();
//                bool isEmpty = _imageInfoQueue->empty();
//                bool isEmpty1 = _asyncStructQueue->empty();
//                _asyncMutex.unlock();
//                if( isEmpty && isEmpty1 && callback ) {
//                    --_asyncRefCount4Wait;
//                    callback();
//                }
//                
//                if (0 == _asyncRefCount4Wait)
//                {
//                    Director::getInstance()->getScheduler()->unschedule("TextureCache::waitAddImageAsync", this);
//                }
//
//            }, this, 0, false,"TextureCache::waitAddImageAsync");
//        }
//        
//        ++_asyncRefCount4Wait;
//    
//
//    }
    
}

void TextureCache::addImageAsync(const std::string &path, const std::function<void(Texture2D*)>& callback,
                                 Texture2D* srcTex, bool bNotAddCache)
{
    SAFE_FUN_LOCK;
    Texture2D *texture = nullptr;

    std::string fullpath = FileUtils::getInstance()->fullPathForFilename(path);

    auto it = _textures.find(fullpath);
    if( it != _textures.end() )
        texture = it->second;

    if (texture != nullptr && texture->getName() != 0)
    {
        if (callback) callback(texture);
        return;
    }

    // check if file exists
    if ( fullpath.empty() || ! FileUtils::getInstance()->isFileExist( fullpath ) ) {
        if (callback) callback(nullptr);
        return;
    }

    // lazy init
    if (_loadingThread == nullptr)
    {             
        // create a new thread to load images
        _loadingThread = new std::thread(&TextureCache::loadImage, this);

        _needQuit = false;
    }

    if (0 == _asyncRefCount)
    {
        Director::getInstance()->getScheduler()->schedule(CC_SCHEDULE_SELECTOR(TextureCache::addImageAsyncCallBack), this, 0, false);
    }

    ++_asyncRefCount;

    string cachefilename;
    if ( gEnableTextureCacheImageCacheSwitch && _enableImageCache) {
        size_t hashval = std::hash<std::string>()(fullpath);
        char tempStrVal[128] = {0};
        snprintf(tempStrVal, 128, "%lu_", hashval);
        std::string base_filename = fullpath.substr(fullpath.find_last_of("/\\") + 1);
        cachefilename = FileUtils::getInstance()->getWritablePath() + "cacheTex/tex_" + tempStrVal + base_filename;
        
    }
    // generate async struct
    AsyncStruct *data = new (std::nothrow) AsyncStruct(fullpath, cachefilename, callback);
    data->srcTex = srcTex;
    data->notaddCache = bNotAddCache;
    
    // add async struct into queue
    _asyncStructQueue.push_back(data);
    _requestMutex.lock();
    _requestQueue.push_back(data);
    _requestMutex.unlock();

    _sleepCondition.notify_one();
}

void TextureCache::unbindImageAsync(const std::string& filename)
{
    SAFE_FUN_LOCK;
    if (_asyncStructQueue.empty())
    {
        return;
    }
    std::string fullpath = FileUtils::getInstance()->fullPathForFilename(filename);
    for (auto& asyncStruct : _asyncStructQueue)
    {
        if (asyncStruct->filename == fullpath)
        {
            asyncStruct->callback = nullptr;
        }
    }
}

void TextureCache::unbindAllImageAsync()
{
    SAFE_FUN_LOCK;
    if (_asyncStructQueue.empty())
    {
        return;
        
    }
    for (auto& asyncStruct : _asyncStructQueue)
    {
        asyncStruct->callback = nullptr;
    }
}

void TextureCache::loadImage()
{
    AsyncStruct *asyncStruct = nullptr;
    std::mutex signalMutex;
    std::unique_lock<std::mutex> signal(signalMutex);
    
    while (!_needQuit)
    {
        // pop an AsyncStruct from request queue
        _requestMutex.lock();
        if (_requestQueue.empty())
        {
            asyncStruct = nullptr;
        }
        else
        {
            asyncStruct = _requestQueue.front();
            _requestQueue.pop_front();
        }
        _requestMutex.unlock();
        
        if (nullptr == asyncStruct) {
            _sleepCondition.wait(signal);
            continue;
        }
        
        if( !asyncStruct->cachefilename.empty() ) {
            
            asyncStruct->image.setCachePath(asyncStruct->cachefilename);
            asyncStruct->image.setEnableCache(true);
        }
        
        // load image
        asyncStruct->loadSuccess = asyncStruct->image.initWithImageFileThreadSafe(asyncStruct->filename);
        
//        // ETC1 ALPHA supports.
//        if (asyncStruct->loadSuccess && asyncStruct->image.getFileType() == Image::Format::ETC && !s_etc1AlphaFileSuffix.empty())
//        { // check whether alpha texture exists & load it
//            auto alphaFile = asyncStruct->filename + s_etc1AlphaFileSuffix;
//            if (FileUtils::getInstance()->isFileExist(alphaFile))
//                asyncStruct->imageAlpha.initWithImageFileThreadSafe(alphaFile);
//        }
        // push the asyncStruct to response queue
        _responseMutex.lock();
        _responseQueue.push_back(asyncStruct);
        _responseMutex.unlock();
    }
}

void TextureCache::addImageAsyncCallBack(float dt)
{
    Texture2D *texture = nullptr;
    AsyncStruct *asyncStruct = nullptr;
    while (true)
    {
        // pop an AsyncStruct from response queue
        _responseMutex.lock();
        if (_responseQueue.empty())
        {
            asyncStruct = nullptr;
        }
        else
        {
            asyncStruct = _responseQueue.front();
            _responseQueue.pop_front();
            
            // the asyncStruct's sequence order in _asyncStructQueue must equal to the order in _responseQueue
            CC_ASSERT(asyncStruct == _asyncStructQueue.front());
            _asyncStructQueue.pop_front();
        }
        _responseMutex.unlock();
        
        if (nullptr == asyncStruct) {
            break;
        }
        
        // check the image has been convert to texture or not
        auto it = _textures.find(asyncStruct->filename);
        if (it != _textures.end() && asyncStruct->srcTex == nullptr)
        {
            texture = it->second;
        }
        else
        {
            // convert image to texture
            if (asyncStruct->loadSuccess)
            {
                Image* image = &(asyncStruct->image);
                // generate texture in render thread
                if( asyncStruct->srcTex ) {
                    texture = asyncStruct->srcTex;
                }
                else
                {
                    // generate texture in render thread
                    texture = new (std::nothrow) Texture2D();
                }

                
                texture->initWithImage(image, asyncStruct->pixelFormat);
                //parse 9-patch info
                this->parseNinePatchImage(image, texture, asyncStruct->filename);
                
                if( asyncStruct->srcTex && texture->_texParams.wrapS != 0 ) {
                    texture->setTexParameters(texture->_texParams);
                }
                
#if CC_ENABLE_CACHE_TEXTURE_DATA
                // cache the texture file name
                VolatileTextureMgr::addImageTexture(texture, asyncStruct->filename);
#endif
                if(asyncStruct->notaddCache) {
                    
                }
                else {
                    // cache the texture. retain it, since it is added in the map
                    _textures.emplace(asyncStruct->filename, texture);
                    texture->retain();
                    
                    texture->autorelease();
                }


            }
            else {
                texture = nullptr;
                CCLOG("cocos2d: failed to call TextureCache::addImageAsync(%s)", asyncStruct->filename.c_str());
            }
        }
        
        // call callback function
        if (asyncStruct->callback)
        {
            (asyncStruct->callback)(texture);
        }
        
        // release the asyncStruct
        delete asyncStruct;
        --_asyncRefCount;
    }
    
    if (0 == _asyncRefCount)
    {
        Director::getInstance()->getScheduler()->unschedule(CC_SCHEDULE_SELECTOR(TextureCache::addImageAsyncCallBack), this);
    }
    
    
//    // the image is generated in loading thread
//    std::deque<ImageInfo*> *imagesQueue = _imageInfoQueue;
//
//    _asyncMutex.lock();
//    if (imagesQueue->empty())
//    {
//        _asyncMutex.unlock();
//    }
//    else
//    {
//        ImageInfo *imageInfo = imagesQueue->front();
//        imagesQueue->pop_front();
//        _asyncMutex.unlock();
//
//        AsyncStruct *asyncStruct = imageInfo->asyncStruct;
//        Image *image = imageInfo->image;
//
//        const std::string& filename = asyncStruct->filename;
//
//        Texture2D *texture = nullptr;
//        if (image)
//        {
//            if( asyncStruct->srcTex ) {
//                texture = asyncStruct->srcTex;
//            }
//            else
//            {
//                // generate texture in render thread
//                texture = new (std::nothrow) Texture2D();
//            }
//
//            
//            
//
//            texture->initWithImage(image);
//            //parse 9-patch info
//            this->parseNinePatchImage(image, texture, filename);
//#if CC_ENABLE_CACHE_TEXTURE_DATA
//            // cache the texture file name
//            VolatileTextureMgr::addImageTexture(texture, filename);
//#endif
//            if( asyncStruct->notaddCache) {
//                
//            }
//            else {
//                // cache the texture. retain it, since it is added in the map
//                _textures.insert( std::make_pair(filename, texture) );
//                texture->retain();
//                
//                texture->autorelease();
//            }
//
//        }
//        else
//        {
//            auto it = _textures.find(asyncStruct->filename);
//            if(it != _textures.end())
//                texture = it->second;
//        }
//        
//        if (asyncStruct->callback)
//        {
//            asyncStruct->callback(texture);
//        }
//        
//        if(image)
//        {
//            image->release();
//        }       
//        delete asyncStruct;
//        delete imageInfo;
//
//        --_asyncRefCount;
//        if (0 == _asyncRefCount)
//        {
//            Director::getInstance()->getScheduler()->unschedule(CC_SCHEDULE_SELECTOR(TextureCache::addImageAsyncCallBack), this);
//        }
//    }
}


#define CC_2x2_WHITE_IMAGE_KEY_DEFAULT  "cc_2x2_white_image_default"
static unsigned char cc_2x2_white_image_default[] = {
    // RGBA8888
    0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF
};


Texture2D* TextureCache::getFirstImage()
{
    SAFE_FUN_LOCK;
    
    if( !bDefaultTexture )
    {
        return NULL;
    }
    auto texture = CCTextureCache::sharedTextureCache()->textureForKey(CC_2x2_WHITE_IMAGE_KEY_DEFAULT);
    // If texture wasn't in cache, create it from RAW data.
    if (nullptr == texture)
    {
        Image* image = new Image();
        bool isOK = image->initWithRawData(cc_2x2_white_image_default, sizeof(cc_2x2_white_image_default), 2, 2, 8);
        texture = Director::getInstance()->getTextureCache()->addImage(image, CC_2x2_WHITE_IMAGE_KEY_DEFAULT);
        texture->retain();
        CC_SAFE_RELEASE(image);
    }
    
    if( texture ) {
        return  texture;
    }
    
    auto itor =  _textures.begin();
    if( itor != _textures.end() )
    {
        CCLOG("zym use uncrashed image:%s", itor->first.c_str() );
        return itor->second;
    }
    CCLOG("zym use uncrashed image: null"  );
    return NULL;
    
}

void TextureCache::EnableTextureCacheOptimize(bool val) {
    gEnableTextureCacheAsyncSwitch = val;
    gEnableTextureCacheImageCacheSwitch = val;
}

Texture2D * TextureCache::addImage(const std::string &filepath, const cocos2d::Size &texSize, bool isUseDefault) {
//    bool writelog = false;
//    if( filepath.find("Imperial_33") != string::npos) {
//        writelog = true;
//    }
//    if( writelog ) {
//        cocos2d::log("addImageGK 0 %d %d", _enableSyncAddImageSync, (MAIN_THREAD_ID != pthread_self()));
//    }
    if ( !gEnableTextureCacheAsyncSwitch || _enableSyncAddImageSync || MAIN_THREAD_ID != pthread_self()) {
//        if( writelog ) {
//            cocos2d::log("addImageGK 1 %s", filepath.c_str());
//        }
        return addImage( filepath ) ;
    }
//    if( writelog ) {
//        cocos2d::log("addImageGK 2 s%s", filepath.c_str());
//    }
    SAFE_FUN_LOCK;
    Texture2D * texture = nullptr;
    std::string fullpath = FileUtils::getInstance()->fullPathForFilename(filepath);
    if (fullpath.size() == 0)
    {
        // CCASSERT( nullptr, "zymerror TextureCache::addImage ");
        if( isUseDefault ) {
            return getFirstImage();
        }
        else {
            return NULL;
        }
    }
    // Added by ChenFei 2014-12-26 V3.2 support
    if (!FileUtils::getInstance()->isFileExist(fullpath)
        && string::npos != fullpath.find(".png"))
    {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        fullpath.replace(fullpath.length() -3, 3, "pkm");
#else
        fullpath.replace(fullpath.length() - 3, 7, "pvr.ccz");
#endif
    }
    
    if(g_isUseCwrzImage) {
        std::string filepathnew = fullpath + ".wrz";
        struct stat buffer;
        bool isExist = (stat(filepathnew.c_str(), &buffer) == 0);
        if( isExist ) {
            fullpath = filepathnew;
        }
    }
    auto it = _textures.find(fullpath);
    if( it != _textures.end() )
        texture = it->second;
    
    if( !texture) {
        texture = new Texture2D();
        texture->_hasPremultipliedAlpha = true;
        texture->_isEmptyTex =true;
        texture->setContentSizeInPixel(texSize);
        _textures.insert( std::make_pair(fullpath, texture) );
        
        if( filepath.find("_alpha_") != string::npos ) {
            texture->_hasPremultipliedAlpha = false;
            texture->_hasAlphaChannel = true;
        }
        
        texture->retain();
        
        {
//            auto texturebg = Director::getInstance()->getTextureCache()->getTextureForKey("cc_async_add_background_image");
//            if( !texturebg ) {
//                unsigned char cc_2x2_white_image[] = {
//                    // RGBA8888
//                    0x00, 0x00, 0x00, 0x80,
//                    0x00, 0x00, 0x00, 0x80,
//                    0x00, 0x00, 0x00, 0x80,
//                    0x00, 0x00, 0x00, 0x80
//                };
//                
//                
//                Image* image = new (std::nothrow) Image();
//                bool isOK = image->initWithRawData(cc_2x2_white_image, sizeof(cc_2x2_white_image), 2, 2, 8);
//                CC_UNUSED_PARAM(isOK);
//                CCASSERT(isOK, "The 2x2 empty texture was created unsuccessfully.");
//                
//                texturebg = Director::getInstance()->getTextureCache()->addImage(image, "cc_async_add_background_image");
//                texturebg->setTexParameters({GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT});
//                CC_SAFE_RELEASE(image);
//            }
//
//            
//            texture->m_realContentTex = texturebg;
//            CC_SAFE_RETAIN(texture->m_realContentTex);
        }
        
        addImageAsync(fullpath, [this,texture,fullpath](Texture2D* texRes) {
//            texture->m_realContentTex = texRes;
//            texRes->retain();
//            _textures.erase(fullpath);
//            int i = 0;
//            i++;
            texture->release();
        },texture,true);
    }
    return texture;
}

Texture2D * TextureCache::addImage(const std::string &path, bool isUseDefault)
{
    SAFE_FUN_LOCK;
    Texture2D * texture = nullptr;
    Image* image = nullptr;
    // Split up directory and filename
    // MUTEX:
    // Needed since addImageAsync calls this method from a different thread

    std::string fullpath = FileUtils::getInstance()->fullPathForFilename(path);
    if (fullpath.size() == 0)
    {
        if(isUseDefault) {
            // CCASSERT( nullptr, "zymerror TextureCache::addImage ");
            return getFirstImage();
        }
        else {
            return NULL;
        }
    }
    // Added by ChenFei 2014-12-26 V3.2 support
    if (!FileUtils::getInstance()->isFileExist(fullpath)
        && string::npos != fullpath.find(".png"))
    {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        fullpath.replace(fullpath.length() -3, 3, "pkm");
#else
        fullpath.replace(fullpath.length() - 3, 7, "pvr.ccz");
#endif
    }
    
    if(g_isUseCwrzImage) {
        std::string filepathnew = fullpath + ".wrz";
        struct stat buffer;
        bool isExist = (stat(filepathnew.c_str(), &buffer) == 0);
        if( isExist ) {
            fullpath = filepathnew;
        }
    }
     
    auto it = _textures.find(fullpath);
    if( it != _textures.end() )
        texture = it->second;

    if (! texture)
    {
        // all images are handled by UIImage except PVR extension that is handled by our own handler
        do 
        {
            image = new (std::nothrow) Image();
            CC_BREAK_IF(nullptr == image);

            string cachefilename;
            if ( gEnableTextureCacheImageCacheSwitch && _enableImageCache) {
                size_t hashval = std::hash<std::string>()(fullpath);
                char tempStrVal[128] = {0};
                snprintf(tempStrVal, 128, "%lu_", hashval);
                std::string base_filename = fullpath.substr(fullpath.find_last_of("/\\") + 1);
                cachefilename = FileUtils::getInstance()->getWritablePath() + "cacheTex/tex_" + tempStrVal + base_filename;
                
            }
            
            if(image) {
                image->setCachePath(cachefilename);
                image->setEnableCache(true);
            }

            bool bRet = image->initWithImageFile(fullpath);
            CC_BREAK_IF(!bRet);

            texture = new (std::nothrow) Texture2D();


            if( texture && texture->initWithImage(image,fullpath))
            {
#if CC_ENABLE_CACHE_TEXTURE_DATA
                // cache the texture file name
                VolatileTextureMgr::addImageTexture(texture, fullpath);
#endif
                // texture already retained, no need to re-retain it
                _textures.insert( std::make_pair(fullpath, texture) );

                //parse 9-patch info
                this->parseNinePatchImage(image, texture, path);

            }
            else
            {

                CCLOG("cocos2d: Couldn't create texture for file:%s in TextureCache", path.c_str());
                CC_SAFE_RELEASE(image);
                 CCASSERT( nullptr, "zymerror TextureCache::addImage ");
                //暂时不删texture,以防崩溃，就让它先泄露吧
                return getFirstImage();
            }
        } while (0);
    }

    CC_SAFE_RELEASE(image);

    if( texture == nullptr )
    {
        CCASSERT( nullptr, "zymerror TextureCache::addImage ");
        return getFirstImage();
    }
    
    
    return texture;
}

void TextureCache::parseNinePatchImage(cocos2d::Image *image, cocos2d::Texture2D *texture,const std::string& path)
{
    if(NinePatchImageParser::isNinePatchImage(path))
    {
        Rect frameRect = Rect(0,0,image->getWidth(), image->getHeight());
        NinePatchImageParser parser(image, frameRect, false);
        texture->addSpriteFrameCapInset(nullptr, parser.parseCapInset());
    }

}

Texture2D* TextureCache::addImage(Image *image, const std::string &key)
{
    SAFE_FUN_LOCK;
    
    CCASSERT(image != nullptr, "TextureCache: image MUST not be nil");

    Texture2D * texture = nullptr;

    do
    {
        auto it = _textures.find(key);
        if( it != _textures.end() ) {
            texture = it->second;
            break;
        }

        // prevents overloading the autorelease pool
        texture = new (std::nothrow) Texture2D();
        texture->initWithImage(image);

        if(texture)
        {
            _textures.insert( std::make_pair(key, texture) );
            texture->retain();

            texture->autorelease();
        }
        else
        {
            CCLOG("cocos2d: Couldn't add UIImage in TextureCache");
        }

    } while (0);
    
#if CC_ENABLE_CACHE_TEXTURE_DATA
    VolatileTextureMgr::addImage(texture, image);
#endif
    
    return texture;
}

bool TextureCache::reloadTexture(const std::string& fileName)
{
    SAFE_FUN_LOCK;
    Texture2D * texture = nullptr;
    Image * image = nullptr;

    std::string fullpath = FileUtils::getInstance()->fullPathForFilename(fileName);
    if (fullpath.size() == 0)
    {
        return false;
    }

    auto it = _textures.find(fullpath);
    if (it != _textures.end()) {
        texture = it->second;
    }

    bool ret = false;
    if (! texture) {
        texture = this->addImage(fullpath);
        ret = (texture != nullptr);
    }
    else
    {
        do {
            image = new (std::nothrow) Image();
            CC_BREAK_IF(nullptr == image);

            bool bRet = image->initWithImageFile(fullpath);
            CC_BREAK_IF(!bRet);
            
            ret = texture->initWithImage(image,fullpath);
        } while (0);
    }
    
    CC_SAFE_RELEASE(image);

    return ret;
}

// TextureCache - Remove

void TextureCache::removeAllTextures()
{
    SAFE_FUN_LOCK;
    for( auto it=_textures.begin(); it!=_textures.end(); ++it ) {
        (it->second)->release();
    }
    _textures.clear();
}

void TextureCache::removeUnusedTextures()
{
    SAFE_FUN_LOCK;
    for( auto it=_textures.cbegin(); it!=_textures.cend(); /* nothing */) {
        Texture2D *tex = it->second;
        if( tex->getReferenceCount() == 1 ) {
//            CCLOG("cocos2d: TextureCache: removing unused texture: %s", it->first.c_str());
            
            if( g_loading_cache_textures.size() > 0 && g_loading_cache_textures.find(it->first) != g_loading_cache_textures.end()) {
                ++it;
                continue;
            }
            
            tex->release();
            _textures.erase(it++);
        } else {
//            CCLOG("cocos2d: TextureCache: texture: %s, ref count : %d", it->first.c_str(),tex->getReferenceCount());
            ++it;
        }

    }
}

void TextureCache::removeTexture(Texture2D* texture)
{
    SAFE_FUN_LOCK;
    if( ! texture )
    {
        return;
    }

    for( auto it=_textures.cbegin(); it!=_textures.cend(); /* nothing */ ) {
        if( it->second == texture ) {
            texture->release();
            _textures.erase(it++);
            break;
        } else
            ++it;
    }
}

void TextureCache::removeTextureForKey(const std::string &textureKeyName)
{
    std::string key = textureKeyName;
    auto it = _textures.find(key);

    if( it == _textures.end() ) {
        key = FileUtils::getInstance()->fullPathForFilename(textureKeyName);
        it = _textures.find(key);
    }

    if( it != _textures.end() ) {
        (it->second)->release();
        _textures.erase(it);
    }
}

Texture2D* TextureCache::getTextureForKey(const std::string &textureKeyName) const
{
    SAFE_FUN_LOCK;
    std::string key = textureKeyName;
    auto it = _textures.find(key);

    if( it == _textures.end() ) {
        key = FileUtils::getInstance()->fullPathForFilename(textureKeyName);
        it = _textures.find(key);
    }

    if( it != _textures.end() )
        return it->second;
    return nullptr;
}

// Added by ChenFei 2014-12-15 V3.2 support
void TextureCache::dumpCachedTextureInfo()
{
    SAFE_FUN_LOCK;
    unsigned int count = 0;
    unsigned int totalBytes = 0;
    
    for( auto it=_textures.begin(); it!=_textures.end(); ++it )
    {
        Texture2D* tex = (Texture2D*)it->second;
        unsigned int bpp = tex->bitsPerPixelForFormat();
        // Each texture takes up width * height * bytesPerPixel bytes.
        unsigned int bytes = tex->getPixelsWide() * tex->getPixelsHigh() * bpp / 8;
        totalBytes += bytes;
        count++;
        CCLOG("cocos2d: \"%s\" rc=%lu id=%lu %lu x %lu @ %ld bpp => %lu KB",
              it->first.c_str(),
              (long)tex->getReferenceCount(),
              (long)tex->getName(),
              (long)tex->getPixelsWide(),
              (long)tex->getPixelsHigh(),
              (long)bpp,
              (long)bytes / 1024);
    }
    
    CCLOG("cocos2d: CCTextureCache dumpDebugInfo: %ld textures, for %lu KB (%.2f MB)", (long)count, (long)totalBytes / 1024, totalBytes / (1024.0f*1024.0f));
}
void TextureCache::reloadAllTextures()
{
//will do nothing
// #if CC_ENABLE_CACHE_TEXTURE_DATA
//     VolatileTextureMgr::reloadAllTextures();
// #endif
}

const std::string TextureCache::getTextureFilePath( cocos2d::Texture2D *texture )const
{
    SAFE_FUN_LOCK;
    for(auto& item : _textures)
    {
        if(item.second == texture)
        {
            return item.first;
            break;
        }
    }
    return "";
}

void TextureCache::waitForQuit()
{
    // notify sub thread to quick
    _needQuit = true;
    _sleepCondition.notify_one();
    if (_loadingThread) _loadingThread->join();
}

std::string TextureCache::getCachedTextureInfo() const
{
    SAFE_FUN_LOCK;
    std::string buffer;
    char buftmp[4096];

    unsigned int count = 0;
    unsigned int totalBytes = 0;

    for( auto it = _textures.begin(); it != _textures.end(); ++it ) {

        memset(buftmp,0,sizeof(buftmp));


        Texture2D* tex = it->second;
        unsigned int bpp = tex->getBitsPerPixelForFormat();
        // Each texture takes up width * height * bytesPerPixel bytes.
        auto bytes = tex->getPixelsWide() * tex->getPixelsHigh() * bpp / 8;
        totalBytes += bytes;
        count++;
        snprintf(buftmp,sizeof(buftmp)-1,"\"%s\" rc=%lu id=%lu %lu x %lu @ %ld bpp => %lu KB\n",
               it->first.c_str(),
               (long)tex->getReferenceCount(),
               (long)tex->getName(),
               (long)tex->getPixelsWide(),
               (long)tex->getPixelsHigh(),
               (long)bpp,
               (long)bytes / 1024);
        
        buffer += buftmp;
    }

    snprintf(buftmp, sizeof(buftmp)-1, "TextureCache dumpDebugInfo: %ld textures, for %lu KB (%.2f MB)\n", (long)count, (long)totalBytes / 1024, totalBytes / (1024.0f*1024.0f));
    buffer += buftmp;

    return buffer;
}

#if CC_ENABLE_CACHE_TEXTURE_DATA

#define SAFE_FUN_LOCK_VOM GlobalLock::AutoLock autolock_tmp_by_type(GlobalLock::Class_Mutex::Class_VolatileMgr)

std::list<VolatileTexture*> VolatileTextureMgr::_textures;
bool VolatileTextureMgr::_isReloading = false;

VolatileTexture::VolatileTexture(Texture2D *t)
: _texture(t)
, _cashedImageType(kInvalid)
, _textureData(nullptr)
, _pixelFormat(Texture2D::PixelFormat::RGBA8888)
, _fileName("")
, _text("")
, _uiImage(nullptr)
, _hasMipmaps(false)
{
    _texParams.minFilter = GL_LINEAR;
    _texParams.magFilter = GL_LINEAR;
    _texParams.wrapS = GL_CLAMP_TO_EDGE;
    _texParams.wrapT = GL_CLAMP_TO_EDGE;
}

VolatileTexture::~VolatileTexture()
{
    CC_SAFE_RELEASE(_uiImage);
}

void VolatileTextureMgr::addImageTexture(Texture2D *tt, const std::string& imageFileName)
{
    SAFE_FUN_LOCK_VOM;
    if (_isReloading)
    {
        return;
    }

    VolatileTexture *vt = findVolotileTexture(tt);

    vt->_cashedImageType = VolatileTexture::kImageFile;
    vt->_fileName = imageFileName;
    vt->_pixelFormat = tt->getPixelFormat();
}

void VolatileTextureMgr::addImage(Texture2D *tt, Image *image)
{
    SAFE_FUN_LOCK_VOM;
    VolatileTexture *vt = findVolotileTexture(tt);
    image->retain();
    vt->_uiImage = image;
    vt->_cashedImageType = VolatileTexture::kImage;
}

void VolatileTextureMgr::reloadTexture(Texture2D *tt) {

    SAFE_FUN_LOCK_VOM;
    VolatileTexture *vt = 0;
    auto i = _textures.begin();
    while (i != _textures.end())
    {
        VolatileTexture *v = *i++;
        if (v->_texture == tt)
        {
            vt = v;
            break;
        }
    }
    if (!vt) {
        return;
    }
    switch (vt->_cashedImageType)
    {
        case VolatileTexture::kImageFile:
        {
            Image* image = new (std::nothrow) Image();
            
            // Data data = FileUtils::getInstance()->getDataFromFile(vt->_fileName);
            CCLOG("reload texture path kImageFile: %p",vt->_fileName.c_str());
            // if (image && image->initWithImageData(data.getBytes(), data.getSize()))
            if (image && image->initWithImageFile(vt->_fileName))
            {
                Texture2D::PixelFormat oldPixelFormat = Texture2D::getDefaultAlphaPixelFormat();
                Texture2D::setDefaultAlphaPixelFormat(vt->_pixelFormat);
                vt->_texture->initWithImage(image,vt->_fileName);
                Texture2D::setDefaultAlphaPixelFormat(oldPixelFormat);
            }
            
            CC_SAFE_RELEASE(image);
        }
            break;
        case VolatileTexture::kImageData:
        {
            vt->_texture->initWithData(vt->_textureData,
                                       vt->_dataLen,
                                       vt->_pixelFormat,
                                       vt->_textureSize.width,
                                       vt->_textureSize.height,
                                       vt->_textureSize);
        }
            break;
        case VolatileTexture::kString:
        {
            vt->_texture->initWithString(vt->_text.c_str(), vt->_fontDefinition);
        }
            break;
        case VolatileTexture::kImage:
        {
            CCLOG("reload texture path image: %p",vt->_uiImage);
            vt->_texture->initWithImage(vt->_uiImage);
        }
            break;
        default:
            break;
    }
    if (vt->_hasMipmaps) {
        vt->_texture->generateMipmap();
    }
    vt->_texture->setTexParameters(vt->_texParams);
}

VolatileTexture* VolatileTextureMgr::findVolotileTexture(Texture2D *tt)
{
    SAFE_FUN_LOCK_VOM;
    VolatileTexture *vt = 0;
    auto i = _textures.begin();
    while (i != _textures.end())
    {
        VolatileTexture *v = *i++;
        if (v->_texture == tt)
        {
            vt = v;
            break;
        }
    }
    
    if (! vt)
    {
        vt = new (std::nothrow) VolatileTexture(tt);
        _textures.push_back(vt);
    }
    
    return vt;
}

void VolatileTextureMgr::addDataTexture(Texture2D *tt, void* data, int dataLen, Texture2D::PixelFormat pixelFormat, const Size& contentSize)
{
    SAFE_FUN_LOCK_VOM;
    if (_isReloading)
    {
        return;
    }

    VolatileTexture *vt = findVolotileTexture(tt);

    vt->_cashedImageType = VolatileTexture::kImageData;
    vt->_textureData = data;
    vt->_dataLen = dataLen;
    vt->_pixelFormat = pixelFormat;
    vt->_textureSize = contentSize;
}

void VolatileTextureMgr::addStringTexture(Texture2D *tt, const char* text, const FontDefinition& fontDefinition)
{
    SAFE_FUN_LOCK_VOM;
    if (_isReloading)
    {
        return;
    }

    VolatileTexture *vt = findVolotileTexture(tt);

    vt->_cashedImageType = VolatileTexture::kString;
    vt->_text     = text;
    vt->_fontDefinition = fontDefinition;
}

void VolatileTextureMgr::setHasMipmaps(Texture2D *t, bool hasMipmaps)
{
    SAFE_FUN_LOCK_VOM;
    VolatileTexture *vt = findVolotileTexture(t);
    vt->_hasMipmaps = hasMipmaps;
}

void VolatileTextureMgr::setTexParameters(Texture2D *t, const Texture2D::TexParams &texParams)
{
    SAFE_FUN_LOCK_VOM;
    VolatileTexture *vt = findVolotileTexture(t);

    if (texParams.minFilter != GL_NONE)
        vt->_texParams.minFilter = texParams.minFilter;
    if (texParams.magFilter != GL_NONE)
        vt->_texParams.magFilter = texParams.magFilter;
    if (texParams.wrapS != GL_NONE)
        vt->_texParams.wrapS = texParams.wrapS;
    if (texParams.wrapT != GL_NONE)
        vt->_texParams.wrapT = texParams.wrapT;
}

void VolatileTextureMgr::removeTexture(Texture2D *t) 
{
    SAFE_FUN_LOCK_VOM;
    auto i = _textures.begin();
    while (i != _textures.end())
    {
        VolatileTexture *vt = *i++;
        if (vt->_texture == t) 
        {
            _textures.remove(vt);
            delete vt;
            break;
        }
    }
}

void VolatileTextureMgr::reloadAllTextures()
{
    SAFE_FUN_LOCK_VOM;
    _isReloading = true;

    // we need to release all of the glTextures to avoid collisions of texture id's when reloading the textures onto the GPU
    for(auto iter = _textures.begin(); iter != _textures.end(); ++iter)
    {
	    (*iter)->_texture->releaseGLTexture();
    }

    CCLOG("reload all texture");
    auto iter = _textures.begin();

    while (iter != _textures.end())
    {
        VolatileTexture *vt = *iter++;
        CCLOG("reload texture path: %s",vt->_fileName.c_str());
        switch (vt->_cashedImageType)
        {
        case VolatileTexture::kImageFile:
            {
                Image* image = new (std::nothrow) Image();
                
               // Data data = FileUtils::getInstance()->getDataFromFile(vt->_fileName);
                CCLOG("reload texture path kImageFile: %p",vt->_fileName.c_str());
               // if (image && image->initWithImageData(data.getBytes(), data.getSize()))
                if (image && image->initWithImageFile(vt->_fileName))
                {
                    Texture2D::PixelFormat oldPixelFormat = Texture2D::getDefaultAlphaPixelFormat();
                    Texture2D::setDefaultAlphaPixelFormat(vt->_pixelFormat);
                    vt->_texture->initWithImage(image,vt->_fileName);
                    Texture2D::setDefaultAlphaPixelFormat(oldPixelFormat);
                }
                
                CC_SAFE_RELEASE(image);
            }
            break;
        case VolatileTexture::kImageData:
            {
                vt->_texture->initWithData(vt->_textureData,
                                           vt->_dataLen,
                                          vt->_pixelFormat, 
                                          vt->_textureSize.width, 
                                          vt->_textureSize.height, 
                                          vt->_textureSize);
            }
            break;
        case VolatileTexture::kString:
            {
                vt->_texture->initWithString(vt->_text.c_str(), vt->_fontDefinition);
            }
            break;
        case VolatileTexture::kImage:
            {
                CCLOG("reload texture path image: %p",vt->_uiImage);
                vt->_texture->initWithImage(vt->_uiImage);
            }
            break;
        default:
            break;
        }
        if (vt->_hasMipmaps) {
            vt->_texture->generateMipmap();
        }
        vt->_texture->setTexParameters(vt->_texParams);
    }

    _isReloading = false;
}

#endif // CC_ENABLE_CACHE_TEXTURE_DATA

NS_CC_END

