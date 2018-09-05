/****************************************************************************
 Copyright (c) 2012      cocos2d-x.org
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

#include "CCDictionary.h"
#include "deprecated/CCString.h"
#include "CCInteger.h"
#include "platform/CCFileUtils.h"
#include "deprecated/CCString.h"
#include "CCBool.h"
#include "CCInteger.h"
#include "CCFloat.h"
#include "CCDouble.h"
#include "CCArray.h"

NS_CC_BEGIN

__Dictionary* __Dictionary::create()
{
    __Dictionary* ret = new __Dictionary();
    if (ret && ret->init() )
    {
        ret->autorelease();
    }
    return ret;
}
__Dictionary* __Dictionary::create_NO_AL()
{
    __Dictionary* ret = new __Dictionary();
    if (ret && ret->init() )
    {
        
    }
    return ret;
}

__Dictionary* __Dictionary::createWithDictionary(__Dictionary* srcDict)
{
    return srcDict->clone();
}

static __Array* visitArray(const ValueVector& array);

static __Dictionary* visitDict(const ValueMap& dict)
{
    __Dictionary* ret = new __Dictionary();
    ret->init();
    
    for (auto iter = dict.begin(); iter != dict.end(); ++iter)
    {
        if (iter->second.getType() == Value::Type::MAP)
        {
            const ValueMap& subDict = iter->second.asValueMap();
            auto sub = visitDict(subDict);
            ret->setObject(sub, iter->first);
            sub->release();
        }
        else if (iter->second.getType() == Value::Type::VECTOR)
        {
            const ValueVector& arr = iter->second.asValueVector();
            auto sub = visitArray(arr);
            ret->setObject(sub, iter->first);
            sub->release();
        }
        else
        {
            auto str = new __String(iter->second.asString());
            ret->setObject(str, iter->first);
            str->release();
        }
    }
    return ret;
}

static __Array* visitArray(const ValueVector& array)
{
    __Array* ret = __Array::createOL();//new __Array();
   // ret->init();

    for(const auto &value : array) {
        if (value.getType() == Value::Type::MAP)
        {
            const ValueMap& subDict = value.asValueMap();
            auto sub = visitDict(subDict);
            ret->addObject(sub);
            sub->release();
        }
        else if (value.getType() == Value::Type::VECTOR)
        {
            const ValueVector& arr = value.asValueVector();
            auto sub = visitArray(arr);
            ret->addObject(sub);
            sub->release();
        }
        else
        {
            auto str = new __String(value.asString());
            ret->addObject(str);
            str->release();
        }
    }
    
    return ret;
}

__Dictionary* __Dictionary::createWithContentsOfFileThreadSafe(const char *pFileName)
{
    return visitDict(FileUtils::getInstance()->getValueMapFromFile(pFileName));
}

void __Dictionary::acceptVisitor(DataVisitor &visitor)
{
    return visitor.visit(this);
}

__Dictionary* __Dictionary::createWithContentsOfFile(const char *pFileName)
{
    auto ret = createWithContentsOfFileThreadSafe(pFileName);
    if (ret != nullptr)
    {
        ret->autorelease();
    }
    return ret;
}

static ValueMap ccdictionary_to_valuemap(__Dictionary* dict);

static ValueVector ccarray_to_valuevector(__Array* arr)
{
    ValueVector ret;
    
    Ref* obj;
    CCARRAY_FOREACH(arr, obj)
    {
        Value arrElement;

        __String* strVal = nullptr;
        __Dictionary* dictVal = nullptr;
        __Array* arrVal = nullptr;
        __Double* doubleVal = nullptr;
        __Bool* boolVal = nullptr;
        __Float* floatVal = nullptr;
        __Integer* intVal = nullptr;
        
        if ((strVal = dynamic_cast<__String *>(obj))) {
            arrElement = Value(strVal->getCString());
        } else if ((dictVal = dynamic_cast<__Dictionary*>(obj))) {
            arrElement = ccdictionary_to_valuemap(dictVal);
        } else if ((arrVal = dynamic_cast<__Array*>(obj))) {
            arrElement = ccarray_to_valuevector(arrVal);
        } else if ((doubleVal = dynamic_cast<__Double*>(obj))) {
            arrElement = Value(doubleVal->getValue());
        } else if ((floatVal = dynamic_cast<__Float*>(obj))) {
            arrElement = Value(floatVal->getValue());
        } else if ((intVal = dynamic_cast<__Integer*>(obj))) {
            arrElement = Value(intVal->getValue());
        }  else if ((boolVal = dynamic_cast<__Bool*>(obj))) {
            arrElement = boolVal->getValue() ? Value(true) : Value(false);
        } else {
            CCASSERT(false, "the type isn't suppored.");
        }

        ret.push_back(arrElement);
    }
    return ret;
}

static ValueMap ccdictionary_to_valuemap(__Dictionary* dict)
{
    ValueMap ret;
    DictElement* pElement = nullptr;
    CCDICT_FOREACH(dict, pElement)
    {
        Ref* obj = pElement->getObject();
        
        __String* strVal = nullptr;
        __Dictionary* dictVal = nullptr;
        __Array* arrVal = nullptr;
        __Double* doubleVal = nullptr;
        __Bool* boolVal = nullptr;
        __Float* floatVal = nullptr;
        __Integer* intVal = nullptr;
        
        Value dictElement;
        
        if ((strVal = dynamic_cast<__String *>(obj))) {
            dictElement = Value(strVal->getCString());
        } else if ((dictVal = dynamic_cast<__Dictionary*>(obj))) {
            dictElement = ccdictionary_to_valuemap(dictVal);
        } else if ((arrVal = dynamic_cast<__Array*>(obj))) {
            dictElement = ccarray_to_valuevector(arrVal);
        } else if ((doubleVal = dynamic_cast<__Double*>(obj))) {
            dictElement = Value(doubleVal->getValue());
        } else if ((floatVal = dynamic_cast<__Float*>(obj))) {
            dictElement = Value(floatVal->getValue());
        } else if ((intVal = dynamic_cast<__Integer*>(obj))) {
            dictElement = Value(intVal->getValue());
        } else if ((boolVal = dynamic_cast<__Bool*>(obj))) {
            dictElement = boolVal->getValue() ? Value(true) : Value(false);
        } else {
            CCASSERT(false, "the type isn't suppored.");
        }

        const char* key = pElement->getStrKey();
        if (key && strlen(key) > 0)
        {
            ret[key] = dictElement;
        }
    }
    return ret;
}


bool __Dictionary::writeToFile(const char *fullPath)
{
    ValueMap dict = ccdictionary_to_valuemap(this);
    return FileUtils::getInstance()->writeToFile(dict, fullPath);
}

__Dictionary* __Dictionary::clone() const
{
    __Dictionary* newDict = __Dictionary::create();
    
    newDict->_dictType = _dictType;
    
    for(auto &item : elements)
    {
        item.second->retain();
        newDict->elements.emplace(item);
    }
    
    return newDict;
}

NS_CC_END
