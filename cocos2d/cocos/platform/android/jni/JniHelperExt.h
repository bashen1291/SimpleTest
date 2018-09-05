/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
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
#ifndef __ANDROID_JNI_HELPER_EXT_H__
#define __ANDROID_JNI_HELPER_EXT_H__

#include <jni.h>
#include <string>
#include "platform/CCPlatformMacros.h"

template <class T>
class SafeRef {
    
public:
    
    //Construct using a C pointer
    SafeRef(T* ptr = nullptr)
    : p(ptr)
    {
       
    }
    
    //Copy constructor
    SafeRef(const SafeRef &ptr);
    // : p(ptr.p)
    // {
    // }
    
    //Move constructor
    SafeRef(SafeRef &&ptr)
    : p(ptr.p)
    {
        ptr.p = nullptr;
    }
    
    ~SafeRef()
    {
        if(p != nullptr && !_notDeleteRef) {cocos2d::JniHelper::getEnv()->DeleteLocalRef(p);}
    }
    
    //Assign a pointer
    SafeRef &operator=(T* ptr)
    {
        if(p != nullptr) {cocos2d::JniHelper::getEnv()->DeleteLocalRef(p);}
        p = ptr;
        return (*this);
    }
    
    //Assign another CCSafeObject
    SafeRef &operator=(const SafeRef &ptr);
    // {
    //     return (*this) = ptr.p;
    // }
    
    T* getObject() const {
        return p;
    }
    
    void setObject(T* p) {
        (*this) = p;
    }
    
    bool isNULL() {
        return p == nullptr;
    }
    
    T* operator->() const {return p;}        //x->member
    T &operator*() const {return *p;}        //*x, (*x).member
    operator T*() const {return p;}        //T* y = x;
    operator bool() const {return p != nullptr;}    //if(x) {/*x is not NULL*/}
     operator int*() const { return nullptr; }
    // CAUTION :
    // USE OPERATOR == TO COMPARE TWO CCSafeObject IS UNDEFINED !!!
    
    T *p;    //Actual pointer
    bool _notDeleteRef{false};
};

typedef struct JniMethodInfoExt_ : cocos2d::JniMethodInfo
{

    ~JniMethodInfoExt_() {
        if( classID != NULL ) {
            if(env)env->DeleteLocalRef(classID);
        }
    }
} sJniMethodInfo;

typedef SafeRef<_jstring> sjstring;
typedef SafeRef<_jclass> sjclass;
typedef SafeRef<_jobject> sjobject;
typedef SafeRef<_jarray> sjarray;
typedef SafeRef<_jobjectArray> sjobjectArray;
typedef SafeRef<_jbooleanArray> sjbooleanArray;
typedef SafeRef<_jbyteArray> sjbyteArray;
typedef SafeRef<_jcharArray> sjcharArray;
typedef SafeRef<_jshortArray> sjshortArray;
typedef SafeRef<_jintArray> sjintArray;
typedef SafeRef<_jlongArray> sjlongArray;
typedef SafeRef<_jfloatArray> sjfloatArray;
typedef SafeRef<_jdoubleArray> sjdoubleArray;
typedef SafeRef<_jthrowable> sjthrowable;

#endif // __ANDROID_JNI_HELPER_EXT_H__
