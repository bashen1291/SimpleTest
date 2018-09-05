/****************************************************************************
Copyright (c) 2012      cocos2d-x.org
 opyright (c) 2013-2015 Chukong Technologies Inc.

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

#ifndef __CCDICTIONARY_H__
#define __CCDICTIONARY_H__
/// @cond DO_NOT_SHOW

#include <functional>
#include "base/chash_map.h"
#include "base/CCRef.h"
#include "CCArray.h"
#include "deprecated/CCString.h"
#include "CCInteger.h"
#include "CCArray.h"

extern void printBackTraceTolog(const char* data);

NS_CC_BEGIN


class __Dictionary;

/**
 * calc hash when construct
 * use DictKey("str", DictKeyRefTag()) construct to ref outside string , keep the "str" alive !
 * DO NOT compare integer and string
 */

struct DictKeyRefTag{};
struct DictKey
{
    enum
    {
        type_error = 0,
        type_integer = 1,
        type_string = 2,
        type_ref = 3,
        buffer_size = 32,
    };
    struct
    {
        uint32_t _type : 2;
        uint32_t _length : 30;
    };
    union
    {
        char _buffer[buffer_size];
        char *_string;
        char const *_string_const;
        intptr_t _integer;
    };
    
    DictKey() : _type(type_error), _length(0)
    {
    }
    DictKey(DictKey const &other) : _type(other._type), _length(other._length)
    {
        if(_type == type_string && _length >= buffer_size)
        {
            _string = new char[_length + 1];
            std::memcpy(_string, other._string, _length + 1);
        }
        else
        {
            std::memcpy(_buffer, other._buffer, _length + 1);
        }
    }
    DictKey(DictKey &&other) : _type(other._type), _length(other._length)
    {
        if(_type == type_string && _length >= buffer_size)
        {
            _string = other._string;
        }
        else
        {
            std::memcpy(_buffer, other._buffer, _length + 1);
        }
        other._type = type_error;
        other._length = 0;
    }
    DictKey(intptr_t value) : _type(type_integer), _length(sizeof(intptr_t)), _integer(value)
    {
    }
    DictKey(char const *value) : _type(type_string), _length(uint32_t(std::strlen(value)))
    {
        if(_length >= buffer_size)
        {
            _string = new char[_length + 1];
            std::memcpy(_string, value, _length + 1);
        }
        else
        {
            std::memcpy(_buffer, value, _length + 1);
        }
    }
    DictKey(char const *value, size_t len) : _type(type_string), _length(uint32_t(len))
    {
        if(_length >= buffer_size)
        {
            _string = new char[_length + 1];
            std::memcpy(_string, value, _length + 1);
        }
        else
        {
            std::memcpy(_buffer, value, _length + 1);
        }
    }
    DictKey(char const *ptr, DictKeyRefTag) : _type(type_ref), _length(uint32_t(std::strlen(ptr))), _string_const(ptr)
    {
    }
    DictKey(char const *ptr, size_t len, DictKeyRefTag) : _type(type_ref), _length(uint32_t(len)), _string_const(ptr)
    {
    }
    ~DictKey()
    {
        if(_type == type_string && _length >= buffer_size)
        {
            delete[] _string;
        }
    }
    DictKey &operator = (DictKey const &other)
    {
        this->~DictKey();
        ::new(this) DictKey(other);
        return *this;
    }
    DictKey &operator = (DictKey &&other)
    {
        this->~DictKey();
        ::new(this) DictKey(std::move(other));
        return *this;
    }
    
    template<class T, size_t N> struct make_hash
    {
        static uint64_t invoke(uint8_t const *data, uint64_t length)
        {
            const uint64_t offset_basis = 14695981039346656037ULL;
            const uint64_t prime = 1099511628211ULL;
            
            uint64_t val = offset_basis;
            for(size_t next = 0; next < length; ++next)
            {
                val ^= (size_t)data[next];
                val *= prime;
            }
            return val;
        }
    };
    template<class Unused> struct make_hash<Unused, 32>
    {
        static uint32_t invoke(uint8_t const *data, uint32_t length)
        {
            const uint32_t offset_basis = 2166136261U;
            const uint32_t prime = 16777619U;
            
            uint32_t val = offset_basis;
            for(size_t next = 0; next < length; ++next)
            {
                val ^= (size_t)data[next];
                val *= prime;
            }
            return val;
        }
    };
    
    struct hasher
    {
        size_t operator()(DictKey const &key) const
        {
            return make_hash<void, sizeof(size_t)>::invoke(reinterpret_cast<uint8_t const *>(key.data()), key._length);
        }
    };
    
    bool is_string() const
    {
        return _type == type_string || _type == type_ref;
    }
    char const *string() const
    {
        return _length >= buffer_size ? _string : _buffer;
    }
    bool is_integer() const
    {
        return _type == type_integer;
    }
    intptr_t integer() const
    {
        return _integer;
    }
    void const *data() const
    {
        switch(_type)
        {
            case type_ref:
                return _string;
            case type_string:
                return _length >= buffer_size ? _string : _buffer;
            default:
                return _buffer;
        }
    }
    bool operator < (DictKey const &other) const
    {
        if(_length != other._length)
        {
            return _length < other._length;
        }
        else
        {
            return std::memcmp(data(), other.data(), _length) < 0;
        }
    }
    bool operator == (DictKey const &other) const
    {
        if(_length != other._length)
        {
            return false;
        }
        else
        {
            return std::memcmp(data(), other.data(), _length) == 0;
        }
    }
};
using DictionaryImpl = chash_map<DictKey, Ref *, DictKey::hasher>;


/**
 *  Dictionary is a class like NSDictionary in Obj-C .
 *
 *  @note Only the pointer of Object or its subclass can be inserted to Dictionary.
 *  @code
 *  // Create a dictionary, return an autorelease object.
 *  Dictionary* pDict = Dictionary::create();
 *
 *  // Insert objects to dictionary
 *  String* pValue1 = String::create("100");
 *  String* pValue2 = String::create("120");
 *  Integer* pValue3 = Integer::create(200);
 *  pDict->setObject(pValue1, "key1");
 *  pDict->setObject(pValue2, "key2");
 *  pDict->setObject(pValue3, "key3");
 *
 *  // Get the object for key
 *  String* pStr1 = static_cast<String*>(pDict->objectForKey("key1"));
 *  log("{ key1: %s }", pStr1->getCString());
 *  Integer* pInteger = static_cast<Integer*>(pDict->objectForKey("key3"));
 *  log("{ key3: %d }", pInteger->getValue());
 *  @endcode
 *
 */

class CC_DLL DictElement
{
public:
    char const *getStrKey() const
    {
        CCASSERT(ptr->first.is_string(), "Should not call this function for integer dictionary");
        return ptr->first.string();
    }

    intptr_t getIntKey() const
    {
        CCASSERT(ptr->first.is_integer(), "Should not call this function for string dictionary");
        return ptr->first.integer();
    }
    
    Ref* getObject() const
    {
        return ptr->second;
    }

    DictionaryImpl::const_iterator where;
    DictionaryImpl::value_type const *ptr;
};

/** The macro for traversing dictionary
 *  
 *  @note It's faster than getting all keys and traversing keys to get objects by objectForKey.
 *        It's also safe to remove elements while traversing.
 */
template<class T> struct CCDICT_FOREACH_HELPER
{
    T t;
    operator bool() const
    {
        return true;
    }
};
#define CCDICT_FOREACH(__dict__, __el__) \
    if (__dict__) \
    if(cocos2d::CCDICT_FOREACH_HELPER<cocos2d::DictElement> it##__dict__##__el__ = {(__dict__)->elements.cbegin(), nullptr})\
    for((__el__) = &it##__dict__##__el__.t; it##__dict__##__el__.t.where != (__dict__)->elements.cend(); ++it##__dict__##__el__.t.where) \
    if((it##__dict__##__el__.t.ptr = &*it##__dict__##__el__.t.where), true)


class CC_DLL __Dictionary : public Ref, public Clonable
{
public:
    /**
     * The constructor of Dictionary.
     * @js NA
     * @lua NA
     */
    __Dictionary() : _dictType(kDictUnknown)
    {
    }
    
    /**
     * The destructor of Dictionary
     * @js NA
     * @lua NA
     */
    ~__Dictionary()
    {
        removeAllObjects();
    }
    
    /** Initializes the dictionary. It returns true if the initializations was successful. 
     * @js NA
     * @lua NA
     */
    bool init()
    {
        return true;
    }

    /**
     *  Get the count of elements in Dictionary.
     *
     *  @return  The count of elements.
     * @js NA
     */
    unsigned int count()
    {
        return (unsigned int)elements.size();
    }

    /**
     *  Return all keys of elements.
     *
     *  @return  The array contains all keys of elements. It's an autorelease object yet.
     * @js NA
     */
    __Array* allKeys()
    {
        if (elements.empty())
        {
            return nullptr;
        }
        __Array* array = __Array::createWithCapacity(elements.size());
        
        if (_dictType == kDictStr)
        {
            for(auto const &item : elements)
            {
                __String* pOneKey = new __String(item.first.string());
                array->addObject(pOneKey);
                CC_SAFE_RELEASE(pOneKey);
            }
        }
        else if (_dictType == kDictInt)
        {
            for(auto const &item : elements)
            {
                __Integer* pOneKey = new __Integer((int)item.first.integer());
                array->addObject(pOneKey);
                CC_SAFE_RELEASE(pOneKey);
            }
        }
        return array;
    }

    /** 
     *  Get all keys according to the specified object.
     *  @warning  We use '==' to compare two objects
     *  @return   The array contains all keys for the specified object. It's an autorelease object yet.
     * @js NA
     */
    __Array* allKeysForObject(Ref* object)
    {
        if (elements.empty())
        {
            return nullptr;
        }
        __Array* array = __Array::createWithCapacity(elements.size());
        
        if (_dictType == kDictStr)
        {
            for(auto const &item : elements)
            {
                if(item.second == object)
                {
                    __String* pOneKey = new __String(item.first.string());
                    array->addObject(pOneKey);
                    CC_SAFE_RELEASE(pOneKey);
                }
            }
        }
        else if (_dictType == kDictInt)
        {
            for(auto const &item : elements)
            {
                if(item.second == object)
                {
                    __Integer* pOneKey = new __Integer((int)item.first.integer());
                    array->addObject(pOneKey);
                    CC_SAFE_RELEASE(pOneKey);
                }
            }
        }
        return array;
    }

    /**
     *  Get the object according to the specified string key.
     *
     *  @note The dictionary needs to use string as key. If integer is passed, an assert will appear.
     *  @param key  The string key for searching.
     *  @return The object matches the key. You need to force convert it to the type you know.
     *  @code
     *     // Assume that the elements are String* pointers. Convert it by following code.
     *     String* pStr = static_cast<String*>(pDict->objectForKey("key1"));
     *     // Do something about pStr.
     *     // If you don't know the object type, properly you need to use dynamic_cast<SomeType*> to check it.
     *     String* pStr2 = dynamic_cast<String*>(pDict->objectForKey("key1"));
     *     if (pStr2 != NULL) {
     *          // Do something about pStr2
     *     }
     *  @endcode
     *  @see objectForKey(intptr_t)
     * @js NA
     */
    Ref* objectForKey(std::string const &key)
    {
        if( NULL == this ) {
            std::string* debugInfo = new std::string();
            (*debugInfo) += std::string("NullCall:[") + __FUNCTION__ + "(std::string const)] key: " + key;
            printBackTraceTolog(debugInfo->c_str());
            delete debugInfo;
        }
        
        if (_dictType == kDictUnknown)
        {
            return nullptr;
        }
        CCASSERT(_dictType == kDictStr, "this dictionary does not use string as key.");
        
        auto find = elements.find(DictKey(key.data(), key.length(), DictKeyRefTag()));
        if(find == elements.end())
        {
            return nullptr;
        }
        return find->second;
    }
    Ref* objectForKey(char const *key)
    {
        if( NULL == this ) {
            std::string* debugInfo = new std::string();
            (*debugInfo) += std::string("NullCall:[") + __FUNCTION__ + "(char const)] key: " + (key?key:"");
            printBackTraceTolog(debugInfo->c_str());
            delete debugInfo;
        }
        
        if (_dictType == kDictUnknown)
        {
            return nullptr;
        }
        CCASSERT(_dictType == kDictStr, "this dictionary does not use string as key.");
        
        auto find = elements.find(DictKey(key, DictKeyRefTag()));
        if(find == elements.end())
        {
            return nullptr;
        }
        return find->second;
    }
    
    /**
     *  Get the object according to the specified integer key.
     *
     *  @note The dictionary needs to use integer as key. If string is passed, an assert will appear.
     *  @param key  The integer key for searching.
     *  @return The object matches the key.
     *  @see objectForKey(const std::string&)
     * @js NA
     */
    Ref* objectForKey(intptr_t key)
    {
        if( NULL == this ) {
            std::string* debugInfo = new std::string();
            char tempBuffer[32] = {0};
            snprintf(tempBuffer, 32, "%zd", key);
            (*debugInfo) += std::string("NullCall:[") + __FUNCTION__ + "(intptr_t)] key: " + tempBuffer;
            printBackTraceTolog(debugInfo->c_str());
            delete debugInfo;
        }
        
        if (_dictType == kDictUnknown)
        {
            return nullptr;
        }
        CCASSERT(_dictType == kDictInt, "this dictionary does not use integer as key.");
        auto find = elements.find(DictKey(key));
        if(find == elements.end())
        {
            return nullptr;
        }
        return find->second;
    }
    
    /** Get the value according to the specified string key.
     *
     *  @note Be careful to use this function since it assumes the objects in the dictionary are __String pointer.
     *  @param key  The string key for searching
     *  @return An instance of String.
     *          It will return an empty string if the objects aren't __String pointer or the key wasn't found.
     *  @see valueForKey(intptr_t)
     *  @js NA
     */
    const __String* valueForKey(std::string const &key)
    {
        if( NULL == this ) {
            std::string* debugInfo = new std::string();
            (*debugInfo) += std::string("NullCall:[") + __FUNCTION__ + "(std::string const &)] key: " + key;
            printBackTraceTolog(debugInfo->c_str());
            delete debugInfo;
        }

        __String* pStr = dynamic_cast<__String*>(objectForKey(key));
        if (pStr == nullptr)
        {
            return &(__String::EmptySTR);
        }
        return pStr;
    }
    const __String* valueForKey(char const *key)
    {
        if( NULL == this ) {
            std::string* debugInfo = new std::string();
            (*debugInfo) += std::string("NullCall:[") + __FUNCTION__ + "(char const)] key: " + (key?key:"");
            printBackTraceTolog(debugInfo->c_str());
            delete debugInfo;
        }
        __String* pStr = dynamic_cast<__String*>(objectForKey(key));
        if (pStr == nullptr)
        {
            return &(__String::EmptySTR);
        }
        return pStr;
    }
    
    /** Get the value according to the specified integer key.
     *
     *  @note Be careful to use this function since it assumes the objects in the dictionary are __String pointer.
     *  @param key  The string key for searching.
     *  @return An instance of String.
     *          It will return an empty string if the objects aren't __String pointer or the key wasn't found.
     *  @see valueForKey(intptr_t)
     *  @js NA
     */
    const __String* valueForKey(intptr_t key)
    {
        __String* pStr = dynamic_cast<__String*>(objectForKey(key));
        if (pStr == nullptr)
        {
            return &(__String::EmptySTR);
        }
        return pStr;
    }

    /** Insert an object to dictionary, and match it with the specified string key.
     *
     *  @note Whe the first time this method is invoked, the key type will be set to string.
     *        After that you can't setObject with an integer key.
     *        If the dictionary contains the key you passed, the object matching the key will be released and removed from dictionary.
     *        Then the new object will be inserted after that.
     *
     *  @param pObject  The Object to be inserted.
     *  @param key      The string key for searching.
     *  @see setObject(Ref*, intptr_t)
     * @js NA
     */
    void setObject(Ref* pObject, std::string const &key)
    {
        setObject(pObject, key.c_str());
    }
    void setObject(Ref* pObject, char const *key)
    {
        CCASSERT(key != nullptr && key[0] != 0 && pObject != nullptr, "Invalid Argument!");
        if (_dictType == kDictUnknown)
        {
            _dictType = kDictStr;
        }
        CCASSERT(_dictType == kDictStr, "this dictionary doesn't use string as key.");
        
        auto result = elements.emplace(key, pObject);
        pObject->retain();
        if(!result.second)
        {
            result.first->second->release();
            result.first->second = pObject;
        }
    }
    
    /** Insert an object to dictionary, and match it with the specified string key.
     *
     *  @note Then the first time this method is invoked, the key type will be set to string.
     *        After that you can't setObject with an integer key.
     *        If the dictionary contains the key you passed, the object matching the key will be released and removed from dictionary.
     *        Then the new object will be inserted after that.
     *  @param pObject  The Object to be inserted.
     *  @param key      The string key for searching.
     *  @see setObject(Ref*, const std::string&)
     *  @js NA
     */
    void setObject(Ref* pObject, intptr_t key)
    {
        CCASSERT(pObject != nullptr, "Invalid Argument!");
        if (_dictType == kDictUnknown)
        {
            _dictType = kDictInt;
        }
        CCASSERT(_dictType == kDictInt, "this dictionary doesn't use integer as key.");
        
        auto result = elements.emplace(key, pObject);
        pObject->retain();
        if(!result.second)
        {
            result.first->second->release();
            result.first->second = pObject;
        }
        
    }

    /** 
     *  Remove an object by the specified string key.
     *
     *  @param key  The string key for searching.
     *  @see removeObjectForKey(intptr_t), removeObjectsForKeys(__Array*),
     *       removeObjectForElememt(DictElement*), removeAllObjects().
     *  @js NA
     */
    void removeObjectForKey(const std::string& key)
    {
        if (_dictType == kDictUnknown)
        {
            return;
        }
        CCASSERT(_dictType == kDictStr, "this dictionary doesn't use string as its key");
        CCASSERT(key.length() > 0, "Invalid Argument!");
        
        auto find = elements.find(DictKey(key.c_str(), DictKeyRefTag()));
        if(find != elements.end())
        {
            find->second->release();
            elements.erase(find);
        }
    }
    
    /**
     *  Remove an object by the specified integer key.
     *
     *  @param key  The integer key for searching.
     *  @see removeObjectForKey(const std::string&), removeObjectsForKeys(__Array*),
     *       removeObjectForElememt(DictElement*), removeAllObjects().
     *  @js NA
     */
    void removeObjectForKey(intptr_t key)
    {
        if (_dictType == kDictUnknown)
        {
            return;
        }
        CCASSERT(_dictType == kDictInt, "this dictionary doesn't use integer as its key");
        
        auto find = elements.find(DictKey(key));
        if(find != elements.end())
        {
            find->second->release();
            elements.erase(find);
        }
    }
    
    /**
     *  Remove objects by an array of keys.
     *
     *  @param pKeyArray  The array contains keys to be removed.
     *  @see removeObjectForKey(const std::string&), removeObjectForKey(intptr_t),
     *       removeObjectForElememt(DictElement*), removeAllObjects().
     *  @js NA
     */
    void removeObjectsForKeys(__Array* pKey__Array)
    {
        Ref* pObj = nullptr;
        CCARRAY_FOREACH(pKey__Array, pObj)
        {
            __String* pStr = static_cast<__String*>(pObj);
            removeObjectForKey(pStr->getCString());
        }
    }
    
    /**
     *  Remove all objects in the dictionary.
     *
     *  @see removeObjectForKey(const std::string&), removeObjectForKey(intptr_t),
     *       removeObjectsForKeys(__Array*), removeObjectForElememt(DictElement*).
     * @js NA
     */
    void removeAllObjects()
    {
        for(auto &item : elements)
        {
            item.second->release();
        }
        elements.clear();
    }
    
    /**
     *  Return a random object in the dictionary.
     *
     *  @return The random object. 
     *  @see objectForKey(intptr_t), objectForKey(const std::string&)
     *  @js NA
     *  @lua NA
     */
    Ref* randomObject()
    {
        return std::next(elements.begin(), std::rand() % elements.size())->second;
    }
    
    /**
     *  Create a dictionary.
     *  @return A dictionary which is an autorelease object.
     *  @see createWithDictionary(Dictionary*), createWithContentsOfFile(const char*), createWithContentsOfFileThreadSafe(const char*).
     *  @js NA
     */
    static __Dictionary* create();
    
    /*字典创建不用autorelease */
    static  __Dictionary* create_NO_AL();
    /**
     *  Create a dictionary with an existing dictionary.
     *
     *  @param srcDict The exist dictionary.
     *  @return A dictionary which is an autorelease object.
     *  @see create(), createWithContentsOfFile(const char*), createWithContentsOfFileThreadSafe(const char*).
     *  @js NA
     */
    static __Dictionary* createWithDictionary(__Dictionary* srcDict);
    
    /**
     *  Create a dictionary with a plist file.
     *  @param  pFileName  The name of the plist file.
     *  @return A dictionary which is an autorelease object.
     *  @see create(), createWithDictionary(Dictionary*), createWithContentsOfFileThreadSafe(const char*).
     *  @js NA
     */
    static __Dictionary* createWithContentsOfFile(const char *pFileName);
    
    /**
     *  Write a dictionary to a plist file.
     *  @param fullPath The full path of the plist file. You can get writeable path by getWritablePath()
     *  @return true if successed, false if failed
     *  @js NA
     *  @lua NA
     */
    bool writeToFile(const char *fullPath);
     
    /**
     *  Create a dictionary with a plist file.
     *  
     *  @note the return object isn't an autorelease object.
     *        This can make sure not using autorelease pool in a new thread.
     *        Therefore, you need to manage the lifecycle of the return object.
     *        It means that when you don't need it, CC_SAFE_RELEASE needs to be invoked.
     *
     *  @param  pFileName  The name of the plist file.
     *  @return A dictionary which isn't an autorelease object.
     *  @js NA
     *  @lua NA
     */
    static __Dictionary* createWithContentsOfFileThreadSafe(const char *pFileName);

    /* override functions 
     *  @js NA
     *  @lua NA
     */
    virtual void acceptVisitor(DataVisitor &visitor);
    /**
     *  @js NA
     *  @lua NA
     */
    virtual __Dictionary* clone() const;
    
    
public:
    /**
     *  All the elements in dictionary.
     * 
     *  @note For internal usage, we need to declare this member variable as public since it's used in UT_HASH.
     */
    DictionaryImpl elements;
private:
    
    /** The support type of dictionary, it's confirmed when setObject is invoked. */
    enum DictType
    {
        kDictUnknown = 0,
        kDictStr,
        kDictInt
    };
    
    /** 
     *  The type of dictionary, it's assigned to kDictUnknown by default.
     */
    DictType _dictType;
};


namespace CCDictionaryLoaderDetail
{
    template<class T> struct get
    {
        static T invoke(__String *str)
        {
            static_assert(std::is_same<T, void>::value, "error type");
        }
    };
    template<> struct get<bool>
    {
        static bool invoke(__String *str)
        {
            return str->boolValue();
        }
    };
    template<> struct get<int>
    {
        static int invoke(__String *str)
        {
            return str->intValue();
        }
    };
    template<> struct get<unsigned int>
    {
        static unsigned int invoke(__String *str)
        {
            return str->uintValue();
        }
    };
    template<> struct get<long>
    {
        static long invoke(__String *str)
        {
            return str->longValue();
        }
    };
    template<> struct get<unsigned long>
    {
        static unsigned long invoke(__String *str)
        {
            return str->longValue();
        }
    };
    template<> struct get<float>
    {
        static float invoke(__String *str)
        {
            return str->floatValue();
        }
    };
    template<> struct get<double>
    {
        static double invoke(__String *str)
        {
            return str->doubleValue();
        }
    };
    template<> struct get<std::string>
    {
        static std::string invoke(__String *str)
        {
            return str->getCString();
        }
    };
}

class CCDictionaryLoader
{
public:
    CCDictionaryLoader() : _d(nullptr)
    {
    }
    CCDictionaryLoader(__Dictionary *dict) : _d(dict)
    {
    }
    
    operator bool() const
    {
        return _d != nullptr;
    }
    bool operator !() const
    {
        return _d == nullptr;
    }
    __Dictionary *operator->() const
    {
        return _d;
    }
    operator __Dictionary *() const
    {
        return _d;
    }
    class GetResult
    {
    public:
        GetResult(__String *str) : _s(str)
        {
        }
        GetResult() : _s(nullptr)
        {
        }
        
        operator bool() const
        {
            return _s != nullptr;
        }
        bool operator !() const
        {
            return _s == nullptr;
        }
        
        template<class T> T get()
        {
            if(_s != nullptr)
            {
                return CCDictionaryLoaderDetail::get<T>::invoke(_s);
            }
            else
            {
                return T();
            }
        }
        
    private:
        __String *_s;
    };
    
public:
    template<class T, class D> typename std::enable_if<std::is_convertible<D, T>::value, CCDictionaryLoader &>::type load(T &assign, char const *key, D &&default_value)
    {
        
        if(_d == nullptr)
        {
            assign = std::forward<D>(default_value);
            return *this;
        }
        auto find = _d->elements.find(DictKey(key, DictKeyRefTag()));
        __String *value = nullptr;
        if(find != _d->elements.end() && (value = dynamic_cast<__String *>(find->second)) != nullptr)
        {
            assign = CCDictionaryLoaderDetail::get<T>::invoke(value);
        }
        else
        {
            assign = std::forward<D>(default_value);
        }
        return *this;
    }
    template<class T, class D, class F> typename std::enable_if<std::is_convertible<D, T>::value && std::is_convertible<F, std::function<T(T)>>::value, CCDictionaryLoader &>::type load(T &assign, char const *key, D &&default_value, F &&value_change)
    {
        if(_d == nullptr)
        {
            assign = std::forward<D>(default_value);
            return *this;
        }
        auto find = _d->elements.find(DictKey(key, DictKeyRefTag()));
        __String *value = nullptr;
        if(find != _d->elements.end() && (value = dynamic_cast<__String *>(find->second)) != nullptr)
        {
            assign = value_change(CCDictionaryLoaderDetail::get<T>::invoke(value));
        }
        else
        {
            assign = std::forward<D>(default_value);
        }
        return *this;
    }
    template<class T> CCDictionaryLoader &load(T &assign, char const *key)
    {
        if(_d == nullptr)
        {
            return *this;
        }
        auto find = _d->elements.find(DictKey(key, DictKeyRefTag()));
        __String *value = nullptr;
        if(find != _d->elements.end() && (value = dynamic_cast<__String *>(find->second)) != nullptr)
        {
            assign = CCDictionaryLoaderDetail::get<T>::invoke(value);
        }
        return *this;
    }
    template<class T, class F> typename std::enable_if<std::is_convertible<F, std::function<T(T)>>::value, CCDictionaryLoader &>::type load(T &assign, char const *key, F &&value_change)
    {
        if(_d == nullptr)
        {
            return *this;
        }
        auto find = _d->elements.find(DictKey(key, DictKeyRefTag()));
        __String *value = nullptr;
        if(find != _d->elements.end() && (value = dynamic_cast<__String *>(find->second)) != nullptr)
        {
            assign = value_change(CCDictionaryLoaderDetail::get<T>::invoke(value));
        }
        return *this;
    }
    template<class T, class D = T> T get(char const *key, D &&default_value = T())
    {
        if(_d == nullptr)
        {
            return std::forward<D>(default_value);
        }
        auto find = _d->elements.find(DictKey(key, DictKeyRefTag()));
        __String *value = nullptr;
        if(find != _d->elements.end() && (value = dynamic_cast<__String *>(find->second)) != nullptr)
        {
            return CCDictionaryLoaderDetail::get<T>::invoke(value);
        }
        else
        {
            return std::forward<D>(default_value);
        }
    }
    GetResult get(char const *key)
    {
        if(_d == nullptr)
        {
            return GetResult();
        }
        auto find = _d->elements.find(DictKey(key, DictKeyRefTag()));
        __String *value = nullptr;
        if(find != _d->elements.end() && (value = dynamic_cast<__String *>(find->second)) != nullptr)
        {
            return GetResult(value);
        }
        else
        {
            return GetResult();
        }
    }
    __Dictionary *get_dict(char const *key)
    {
        if(_d == nullptr)
        {
            return nullptr;
        }
        auto find = _d->elements.find(DictKey(key, DictKeyRefTag()));
        __Dictionary *value = nullptr;
        if(find != _d->elements.end() && (value = dynamic_cast<__Dictionary *>(find->second)) != nullptr)
        {
            return value;
        }
        else
        {
            return nullptr;
        }
    }
    CCDictionaryLoader get_loader(char const *key)
    {
        return CCDictionaryLoader(get_dict(key));
    }
    
private:
    __Dictionary *_d;
};

// end of data_structure group
/// @}

NS_CC_END

/// @endcond
#endif /* __CCDICTIONARY_H__ */
