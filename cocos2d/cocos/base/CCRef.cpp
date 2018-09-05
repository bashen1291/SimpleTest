/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2014 Chukong Technologies

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

#include "base/CCRef.h"
#include "base/CCAutoreleasePool.h"
#include "base/ccMacros.h"
#include "base/CCScriptSupport.h"
#include "base/CCDirector.h"
#if CC_REF_LEAK_DETECTION
#include <algorithm>    // std::find
#endif

extern pthread_t BACK_PROCESS_THREAD_ID;
extern bool g_isApplicationExit;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

//#define CC_ENABLE_BACKTRACE
#ifdef CC_ENABLE_BACKTRACE

#include <iostream>
#include <iomanip>
#include <unwind.h>
#include <dlfcn.h>
#include <stdio.h>

namespace test_debug{
    
    struct BacktraceState
    {
        void** current;
        void** end;
    };
    
    static _Unwind_Reason_Code unwindCallback(struct _Unwind_Context* context, void* arg)
    {
        BacktraceState* state = static_cast<BacktraceState*>(arg);
        uintptr_t pc = _Unwind_GetIP(context);
        if (pc) {
            if (state->current == state->end) {
                return _URC_END_OF_STACK;
            } else {
                *state->current++ = reinterpret_cast<void*>(pc);
            }
        }
        return _URC_NO_REASON;
    }
    
}

size_t captureBacktrace(void** buffer, size_t max)
{
    test_debug::BacktraceState state = {buffer, buffer + max};
    _Unwind_Backtrace(test_debug::unwindCallback, &state);
    
    return state.current - buffer;
}

void dumpBacktrace(void** buffer, size_t count)
{
    std::string filecontent;
    for (size_t idx = 0; idx < count; ++idx) {
        const void* addr = buffer[idx];
        const char* symbol = "";
        
        Dl_info info;
        if (dladdr(addr, &info) && info.dli_sname) {
            symbol = info.dli_sname;
        }
        
        char buff[200] = {0};
        snprintf(buff, sizeof(buff), "backtrace #%zu 0x%llu %s", idx, (uint64_t)addr, symbol);
        
        filecontent += buff;
        filecontent += "\n";
        cocos2d::log("%s",buff);
    }
    filecontent += "=============================\n";
    FILE* file = fopen("/sdcard/backtrace.log","a+");
    
    if (file != NULL)
    {
        fputs(filecontent.c_str(), file);
        fflush(file);
        fclose(file);
    }
    
}

#endif
#endif

extern bool g_performanceCrashSwitch;
//extern void printBackTraceTolog(const char* debugData);
//extern void printRefDebugInfo(cocos2d::Ref* object);
//extern void addBackTraceInfo(cocos2d::Ref* object);

extern bool _main_thread_init;
extern decltype(std::this_thread::get_id()) _main_thread_id;

NS_CC_BEGIN

#if CC_REF_LEAK_DETECTION
static void trackRef(Ref* ref);
static void untrackRef(Ref* ref);
#endif
bool Ref::ms_bEnableAutoRelease = true;

void Ref::enableAutorelease(bool bIsEnable)
{
    ms_bEnableAutoRelease = bIsEnable;
}

Ref::Ref()
:_isInAutoPool(false)
,_isObjPaused(false),_isObjAnimation(false)
,_DebugAllRefCountBackTrace(false)// when the Ref is created, the reference count of it is 1
{
#if CC_ENABLE_SCRIPT_BINDING
    static unsigned int uObjectCount = 0;
    _luaID = 0;
    _ID = ++uObjectCount;
    _scriptObject = nullptr;
#endif
    
#if CC_REF_LEAK_DETECTION
    trackRef(this);
#endif
    
// added by Tao Cheng
#ifdef CC_SHOW_STATISTICS_OBJECT_COUNTS
    increaseInstanceCount(true);
#endif // #ifdef CC_SHOW_STATISTICS_OBJECT_COUNTS

    _lifeFg = std::make_shared<bool>(true);
    
    if (BACK_PROCESS_THREAD_ID == pthread_self()) {
        _isObjPaused = true;
        Director::getInstance()->addPausedList(this);
    }

}

Ref::Ref(const Ref &rRef):_isInAutoPool(false),_DebugAllRefCountBackTrace(false)
{
    _luaID = 0;
    debugNodeType = rRef.debugNodeType;
    _isObjAnimation = rRef._isObjAnimation;
    _DebugAllRefCountBackTrace = rRef._DebugAllRefCountBackTrace;
// added by Tao Cheng
#ifdef CC_SHOW_STATISTICS_OBJECT_COUNTS
    increaseInstanceCount(true);
#endif // #ifdef CC_SHOW_STATISTICS_OBJECT_COUNTS
    
    _lifeFg = std::make_shared<bool>(true);
    
    if (BACK_PROCESS_THREAD_ID == pthread_self()) {
        _isObjPaused = true;
        Director::getInstance()->addPausedList(this);
    }
}

Ref& Ref::operator= (const Ref &rRef)
{
    debugNodeType = rRef.debugNodeType;
    return *this;
}

Ref::~Ref()
{
#if CC_ENABLE_SCRIPT_BINDING
    // if the object is referenced by Lua engine, remove it
    if (_luaID)
    {
        ScriptEngineManager::getInstance()->getScriptEngine()->removeScriptObjectByObject(this);
    }
    else
    {
        // we use lua engine so we don't need these source!!! guok
//        ScriptEngineProtocol* pEngine = ScriptEngineManager::getInstance()->getScriptEngine();
//        if (pEngine != nullptr && pEngine->getScriptType() == kScriptTypeJavascript)
//        {
//            pEngine->removeScriptObjectByObject(this);
//        }
    }
#endif


#if CC_REF_LEAK_DETECTION
    if (_referenceCount != 0)
        untrackRef(this);
#endif
    
    if (_referenceCount > 1) {
//        printRefDebugInfo(this);
    }

// added by Tao Cheng
#ifdef CC_SHOW_STATISTICS_OBJECT_COUNTS
    increaseInstanceCount(false);
#endif // #ifdef CC_SHOW_STATISTICS_OBJECT_COUNTS
    
    if (_isObjPaused) {
        Director::getInstance()->removePausedList(this);
    }
}

void Ref::retain()
{
    CCASSERT(_referenceCount > 0, "reference count should be greater than 0");
    if(_referenceCount <= 0){
        return;
    }
//    ++_referenceCount;
    std::atomic_fetch_add_explicit(&_referenceCount, 1u, std::memory_order_relaxed);
    
    if (debugNodeType.length() == 0) {
        debugNodeType = typeid(*this).name();
    }
    if (_DebugAllRefCountBackTrace) {
//        addBackTraceInfo(this);
    }
    
}

void Ref::release()
{
    if (g_isApplicationExit) {
        return;
    }
    
    if (_DebugAllRefCountBackTrace) {
//        addBackTraceInfo(this);
    }
    
    CCASSERT(_referenceCount > 0, "reference count should be greater than 0");
    if(_referenceCount <= 0){
//        printRefDebugInfo(this);
        return;
    }
//    --_referenceCount;
    bool destory = std::atomic_fetch_sub_explicit(&_referenceCount, 1u, std::memory_order_release) == 1;
    if( destory ) {
        std::atomic_thread_fence(std::memory_order_acquire);
    }
    
    if(!_isInAutoPool) {
        if (destory) {
            delete this;
        }
        return;
    }
    
    auto poolManager = PoolManager::getInstance();
    if (poolManager->getCurrentPool() && poolManager->getCurrentPool()->isClearing()) {
        _isInAutoPool = false;
    }

    if (destory)
    {
#if CC_REF_LEAK_DETECTION
        untrackRef(this);
#endif
        if (_isInAutoPool && poolManager->getCurrentPool() && !poolManager->getCurrentPool()->isClearing())
        {
//#ifdef CC_ENABLE_BACKTRACE
//            const size_t max = 30;
//            void* buffer[max];
//            dumpBacktrace( buffer, captureBacktrace(buffer, max));
//#endif
//

            std::string str = "Ref::release (should not be release) " + this->debugNodeType;
//            printBackTraceTolog(str.c_str());
        }
        
        delete this;
    }
}

Ref* Ref::autorelease()
{
    // zym 2015.12.15 如果游戏退出时就不让进入了
    if(ms_bEnableAutoRelease == false)
        return this;
    
//    static std::once_flag thread_id_flag;
//    static decltype(std::this_thread::get_id()) thread_id;
//    
//    std::call_once(thread_id_flag, [&]()
//                   {
//                       thread_id = std::this_thread::get_id();
//                   });
//
//    CCASSERT(!_main_thread_init || (_main_thread_init && std::this_thread::get_id() == _main_thread_id),"DO NOT CALL autorelease AT SUB THREAD!!");
    

    
    PoolManager::getInstance()->getCurrentPool()->addObject(this);
    _isInAutoPool = true;
    return this;
}

unsigned int Ref::getReferenceCount() const
{
    return _referenceCount;
}

bool Ref::isObjPaused() {
    return _isObjPaused;
}

bool Ref::isObjAnimation() {
    return _isObjAnimation;
}

void Ref::setObjPaused(bool isPaused) {
    _isObjPaused = isPaused;
}

void Ref::setObjAnimation(bool isAnimation) {
    _isObjAnimation = isAnimation;
}

#if CC_REF_LEAK_DETECTION

static std::list<Ref*> __refAllocationList;

void Ref::printLeaks()
{
    // Dump Ref object memory leaks
    if (__refAllocationList.empty())
    {
        log("[memory] All Ref objects successfully cleaned up (no leaks detected).\n");
    }
    else
    {
        log("[memory] WARNING: %d Ref objects still active in memory.\n", (int)__refAllocationList.size());

        for (const auto& ref : __refAllocationList)
        {
            CC_ASSERT(ref);
            const char* type = typeid(*ref).name();
            log("[memory] LEAK: Ref object '%s' still active with reference count %d.\n", (type ? type : ""), ref->getReferenceCount());
        }
    }
}

static void trackRef(Ref* ref)
{
    CCASSERT(ref, "Invalid parameter, ref should not be null!");

    // Create memory allocation record.
    __refAllocationList.push_back(ref);
}

static void untrackRef(Ref* ref)
{
    auto iter = std::find(__refAllocationList.begin(), __refAllocationList.end(), ref);
    if (iter == __refAllocationList.end())
    {
        log("[memory] CORRUPTION: Attempting to free (%s) with invalid ref tracking record.\n", typeid(*ref).name());
        return;
    }

    __refAllocationList.erase(iter);
}

#endif // #if CC_REF_LEAK_DETECTION

// get how many Ref objects is running, added by Tao Cheng
#ifdef CC_SHOW_STATISTICS_OBJECT_COUNTS
std::atomic_ulong Ref::instanceCount(0);
//std::recursive_mutex Ref::instanceCountMutex;

unsigned long Ref::getInstanceCount()
{
    return instanceCount;
}

void Ref::increaseInstanceCount(bool increased)
{
    if(increased)
    {
        ++instanceCount;
    }
    else
    {
        --instanceCount;
    }
}

#endif //#ifdef CC_SHOW_STATISTICS_OBJECT_COUNTS

NS_CC_END
