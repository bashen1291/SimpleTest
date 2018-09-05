//
//  DebugHelper.cpp
//  WarZ
//
//  Created by kakalong on 16/3/3.
//
//

#include "DebugHelper.hpp"

#include "cocos2d.h"



#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>
#include "tinyftp.h"

bool g_enable_global_log = false;
bool g_enable_remote_log = false;
extern void startHttpServer();
extern void startFTPServer();
void* operator new(std::size_t sz) {
    void* ptr = std::malloc(sz);
    std::memset(ptr, 0, sz);
    return ptr;
}

void* operator new[](std::size_t sz) {
    void* ptr = std::malloc(sz);
    std::memset(ptr, 0, sz);
    return ptr;
}

void operator delete(void* ptr) noexcept
{
    std::free(ptr);
}

void operator delete[](void* ptr) noexcept
{
    std::free(ptr);
}


void CrashlyticsLog(const char* content) {
    CrashController::setLog(content);
}
void CrashlyticsLogException(const char* content) {
    CrashController::exception(content);
}
void printDebugKeyValue(const char* key, const char* val) {
    CrashController::setKeyValue(key, val);
}

void startDebugPopupWindow();

std::string GetUTCTimeString(void)
{
    time_t rawtime;
    struct tm * ptm;
    
    time ( &rawtime );
    
    ptm = gmtime ( &rawtime );
    
    printf ("UTC : %2d:%02d\n", (ptm->tm_hour)%24, ptm->tm_min);
    char data[100] = {0};
    strftime (data, 100, "%c", ptm );
    return std::string(data);
}

static std::list<std::string> popupBaseViewList;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
extern void postFLOGString(const char* buf);
extern bool isPostFLOGString();
#endif

void _flog(const char *format, va_list args);

static bool _flog_flag = false;
static string _flog_val_str;
bool IsFLOG() {
    return _flog_flag;
}

static bool _IsLoadingInf_flag = false;
bool IsLoadingInf() {
    return _IsLoadingInf_flag;
}
void setLoadingInf(bool val) {
    _IsLoadingInf_flag = val;
}

bool IsFLOGStr(const string& str) {
    if( _flog_flag && _flog_val_str.find(str) != string::npos && str != "") {
        return true;
    }
    return false;
}

static void remove_dir(const char *path)
{
    struct dirent *entry = NULL;
    DIR *dir = NULL;
    dir = opendir(path);
    if( !dir ) {
        return;
    }
    while(entry = readdir(dir))
    {
        DIR *sub_dir = NULL;
        FILE *file = NULL;
        char abs_path[1024] = {0};
        if(*(entry->d_name) != '.')
        {
            sprintf(abs_path, "%s/%s", path, entry->d_name);
            if(sub_dir = opendir(abs_path))
            {
                closedir(sub_dir);
                remove_dir(abs_path);
            }
            else
            {
                if(file = fopen(abs_path, "r"))
                {
                    fclose(file);
                    remove(abs_path);
                }
            }
        }
    }
    closedir(dir);
    //    remove(path);
}

void setFLOG(bool val, const std::string& flogParameters) {
    _flog_flag = val;
    string filepath;
    string path;

        
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    path = cocos2d::extension::CCDevice::getExternalFilesDir() + "/";
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    path = FileUtils::getInstance()->getWritablePath();
#endif
        
    filepath = path+"fconf.txt";
    if( _flog_flag) {
        FILE *fp;
        fp = fopen(filepath.c_str(), "w+");
        bool ret = false;

        do {
            if(!fp){
                break;
            }
            string content = string("flog=20170621") + ";" + flogParameters;
            size_t wlen = fprintf(fp,"%s",content.c_str());

            if( wlen <= 0){
                break;
            }
            ret = true;
        }while (0);
        if(fp)fclose(fp);
    }
    else {
        remove(filepath.c_str());
        string log_dir = path+"log";
        remove_dir(log_dir.c_str());
    }
    
}
void CheckFLOG() {
    string filepath;
    if( 1 ) {
        
        string path;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        string documents = cocos2d::extension::CCDevice::getExternalFilesDir();
        string documents_internal = FileUtils::getInstance()->getWritablePath();
        mkdir(documents.c_str(), S_IRWXU | S_IRWXG | S_IRWXO);
        mkdir(documents_internal.c_str(), S_IRWXU | S_IRWXG | S_IRWXO);
        path = documents + "/fconf.txt";
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        string documents = FileUtils::getInstance()->getWritablePath();
        mkdir(documents.c_str(), S_IRWXU | S_IRWXG | S_IRWXO);
        path = documents + "fconf.txt";
#endif
        filepath = path;
    }
    
    FILE *fp;
    fp = fopen(filepath.c_str(), "rt");
    bool ret = false;
    
    do {
        if(!fp){
            break;
        }
        char data[100] = {0};
        
        size_t wlen = fread(data, 1, 100, fp);
        _flog_val_str = data;
        if( wlen <= 0){
            break;
        }
        ret = true;
    }while (0);
    if(fp)fclose(fp);
    
    if( _flog_val_str.find("flog=20170621") != string::npos  ) {
        _flog_flag = true;
    }
}

std::string getFLOGPath() {
    string filepath;
    if( filepath == "") {
        string path;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        path = cocos2d::extension::CCDevice::getExternalFilesDir() + "/log";
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        path = FileUtils::getInstance()->getWritablePath() + "log";
#endif
        mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IRWXO);
        
        filepath = path;
    }
    
    time_t tt = time(NULL);
    tm* t= localtime(&tt);
    
    char filename[256] = {0};
    snprintf(filename, 256, "%d_%02d_%02d.log",t->tm_year + 1900, t->tm_mon + 1, t->tm_mday);
    string logfilepath;
    logfilepath.append(filepath).append("/flog_").append(filename);
    return logfilepath;
}
static string loadinglog;
void prepareLoadingInfo(const char * format, ...) {
    va_list args;
    va_start(args, format);
    {
        static const int MAX_LOG_LENGTH = 16*1024;
        char buf[MAX_LOG_LENGTH*10];
        
        vsnprintf(buf, MAX_LOG_LENGTH*10-3, format, args);
        
        time_t tt = time(NULL);
        tm* t= localtime(&tt);
        
        snprintf(buf, MAX_LOG_LENGTH,
                 "%d-%02d-%02d %02d:%02d:%02d %s",
                 t->tm_year + 1900,
                 t->tm_mon + 1,
                 t->tm_mday,
                 t->tm_hour,
                 t->tm_min,
                 t->tm_sec,
                 buf);
        loadinglog.append(buf);

    }
    va_end(args);
}
void clearLoadingInfo() {
    string del;
    std::swap(del, loadinglog);
    loadinglog.clear();
}

void prepareLoadingInfo(std::string& result) {
    result.swap(loadinglog);
}

void FLOG(const char * format, ...)
{
    if(!_flog_flag) return;
    va_list args;
    va_start(args, format);
    _flog(format, args);
    va_end(args);
}

void _flog(const char *format, va_list args)
{
    static const int MAX_LOG_LENGTH = 16*1024;
    char buf[MAX_LOG_LENGTH*10];
    time_t tt = time(NULL);
    tm* t= localtime(&tt);
    vsnprintf(buf, MAX_LOG_LENGTH*10-3, format, args);
    
    CCLOG(buf);
    
    strcat(buf, "\n");

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if( isPostFLOGString() ) {
        char buf1[100] = {0};
        snprintf(buf1, 100, "%02d:%02d:%02d %s",
                 t->tm_hour,
                 t->tm_min,
                 t->tm_sec,
                 buf);
        postFLOGString(buf1);
    }

#endif
    static string filepath;
    if( filepath == "") {
        string path;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        path = cocos2d::extension::CCDevice::getExternalFilesDir() + "/log";
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        path = FileUtils::getInstance()->getWritablePath() + "log";
#endif
        mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IRWXO);
        
        filepath = path;
    }



    char filename[256] = {0};
    snprintf(filename, 256, "%d_%02d_%02d.log",t->tm_year + 1900, t->tm_mon + 1, t->tm_mday);
    string logfilepath;
    logfilepath.append(filepath).append("/flog_").append(filename);
    
    FILE *fp;
    fp = fopen(logfilepath.c_str(), "at+");
    bool ret = false;
    do {
        if(!fp){
            break;
        }
        size_t wlen = fprintf(fp,
                              "%d-%02d-%02d %02d:%02d:%02d %s",
                              t->tm_year + 1900,
                              t->tm_mon + 1,
                              t->tm_mday,
                              t->tm_hour,
                              t->tm_min,
                              t->tm_sec,
                              buf);
        if( wlen <= 0){
            break;
        }
        ret = true;
    }while (0);
    if(fp)fclose(fp);
}
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#ifdef __cplusplus
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
extern "C" {
#endif

    JNIEXPORT jboolean JNICALL  Java_com_elex_chatservice_util_LogUtil_nativeIsFLOG()
    {
        if( IsFLOG() ) {
            return JNI_TRUE;
        }
        return JNI_FALSE;
    }
    
    JNIEXPORT jboolean JNICALL  Java_com_elex_chatservice_util_LogUtil_nativeIsDEBUG()
    {
#if COCOS2D_DEBUG > 0         
        return JNI_TRUE;
#else        
        return JNI_FALSE;
#endif
    }

    JNIEXPORT void JNICALL  Java_com_elex_chatservice_util_LogUtil_nativeFLOG(JNIEnv* env, jobject thiz, jstring text)
    {
        string ret=cocos2d::JniHelper::jstring2string(text);
        FLOG(ret.c_str());
    }
    
#ifdef __cplusplus
}
#endif

#endif
void printDebugBaseViewKeyInfo(const char* baseViewType, bool value) {
    std::string strValue= baseViewType + GetUTCTimeString() + (value?" open" : " close");
    printDebugKeyValue("PopupBaseView", strValue.c_str());
    
    if (value) {
        popupBaseViewList.push_back(baseViewType);
    } else {
        auto iter = std::find(popupBaseViewList.begin(), popupBaseViewList.end(), baseViewType);
        if (iter != popupBaseViewList.end()) {
            popupBaseViewList.erase(iter);
        }
    }
    
    if ( popupBaseViewList.size() > 0 ) {
        std::string buffer;
        size_t index = 0;
        for (auto iter = popupBaseViewList.rbegin(); iter != popupBaseViewList.rend(); ++iter) {
            buffer += *iter + " ";
            index++;
            if (index > 10) {
                break;
            }
        }
        printDebugKeyValue("PopupStackInfo", buffer.c_str());
    }
}

void printDebugKeyInfo(const char* sceneInfo, bool value) {
    std::string strValue= GetUTCTimeString();
    char temp[100] = {0};
    if (value) {
        sprintf(temp, "%s_open",sceneInfo);
    }
    else {
        sprintf(temp, "%s_close",sceneInfo);
    }
    printDebugKeyValue(temp, strValue.c_str());
}

////#define ENABLE_DEBUGHELPER
//#ifndef ENABLE_DEBUGHELPER
//
//void printBackTraceTolog( const char* data ) {
////    CCASSERT(0, "printBackTraceTolog");
//}
//void addBackTraceInfo( cocos2d::Ref* object ) {
////    if (object) {
////        int max = 16;
////        void* buffer[max];
////        object->nameDebugInfo1.assign(buffer, buffer + max);
////    }
//}
//void printRefDebugInfo( cocos2d::Ref* object ) {
////    CCASSERT(0, "printRefDebugInfo");
//}
//
//#else

bool DebugHelper_Disalbe_addBackTraceFlag = false;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include <jni.h>
#include "platform/android/jni/JniHelper.h"

#include <iomanip>
#include <unwind.h>
#include <dlfcn.h>


namespace debug_helper{
/*
http://stackoverflow.com/questions/8115192/android-ndk-getting-the-backtrace
*/
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
    debug_helper::BacktraceState state = {buffer, buffer + max};
    _Unwind_Backtrace(debug_helper::unwindCallback, &state);
    
    return state.current - buffer;
}

void dumpBacktrace(void** buffer, size_t count)
{
    for (size_t idx = 0; idx < count; ++idx) {
        const void* addr = buffer[idx];
        const char* symbol = "";
        
        Dl_info info;
        void* codeAddr = NULL;
        char* moduleName = NULL;
        if (dladdr(addr, &info) && info.dli_sname) {
            symbol = info.dli_sname;
            moduleName = (char* )info.dli_fname;
            codeAddr =  (void*) ((char*)info.dli_saddr  - (char*)info.dli_fbase );
        }
        
        char buff[500] = {0};
        snprintf(buff, sizeof(buff), "backtrace #%zu 0x%llx  Pos 0x%llx %s", idx, (uint64_t)addr, (uint64_t)codeAddr, symbol);
        CrashlyticsLog(buff);
        CCLOG("%s",buff);
    }
}

void printBackTraceTolog(const char* data)
{
    if (!CrashController::getFabricFlag()) {
        return;
    }
    
    CrashlyticsLog(data);
    
    if (!DebugHelper_Disalbe_addBackTraceFlag) {
        const size_t max = 30;
        void* buffer[max];
        dumpBacktrace( buffer, captureBacktrace(buffer, max));
    }
    
    CrashlyticsLogException((data?data:""));
}

void ForcePrintBackTraceTolog(const char* data)
{
    CrashlyticsLog(data);
    
    if (!DebugHelper_Disalbe_addBackTraceFlag) {
        const size_t max = 30;
        void* buffer[max];
        dumpBacktrace( buffer, captureBacktrace(buffer, max));
    }
    
    CrashlyticsLogException((data?data:""));
}

void addBackTraceInfo(cocos2d::Ref* object)
{
    if (DebugHelper_Disalbe_addBackTraceFlag) {
        return;
    }

    if (!CrashController::getFabricFlag()) {
        return;
    }
    
    if( object != NULL ) {
        const size_t max = 10;
        void* buffer[max] = {0};
        debug_helper::BacktraceState state = {buffer, buffer + max};
        _Unwind_Backtrace(debug_helper::unwindCallback, &state);
        int count = state.current - buffer;
//        object->nameDebugInfo1.assign(buffer, buffer + max);
        object->nameDebugInfo1.insert(object->nameDebugInfo1.end(), buffer, buffer + max);
    }
}

void printRefDebugInfo(cocos2d::Ref* object)
{
    if (!CrashController::getFabricFlag()) {
        return;
    }
    
    if (object != NULL ) {
        void** buffer = (void**)object->nameDebugInfo1.data();
        size_t count = object->nameDebugInfo1.size();
        
        for (size_t idx = 0; idx < count; ++idx) {
            const void* addr = buffer[idx];
            const char* symbol = "";
            
            Dl_info info;
            void* codeAddr = NULL;
            char* moduleName = NULL;
            if (dladdr(addr, &info) && info.dli_sname) {
                symbol = info.dli_sname;
                moduleName = (char* )info.dli_fname;
                codeAddr =  (void*) ((char*)info.dli_saddr  - (char*)info.dli_fbase );
            }
            
            char buff[500] = {0};
            snprintf(buff, sizeof(buff), "backtrace #%zu 0x%llx  Pos 0x%llx %s", idx, (uint64_t)addr, (uint64_t)codeAddr, symbol);
            CrashlyticsLog(buff);
            CCLOG("%s",buff);
        }
        
        if ( count > 0 ) {
            char buff[500] = {0};
            snprintf(buff, sizeof(buff), "object type: %s", object->debugNodeType.c_str());
            CrashlyticsLog(buff);
            CCLOG("%s",buff);
            
            CrashlyticsLogException(object->debugNodeType.c_str());
        }
    }
}

#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include <libkern/OSAtomic.h>
#include <execinfo.h>
#include <cxxabi.h>

void printBackTraceTolog( const char* data ) {
    
    if (!CrashController::getFabricFlag()) {
        return;
    }
    
    CrashlyticsLog(data);
    
    struct User_Data {
        void* callstack[128];
        int frames;
        char** strs;
    };
    User_Data* userData = new User_Data();
    userData->strs = NULL;
    userData->frames = backtrace(userData->callstack, 128);
    userData->strs = backtrace_symbols(userData->callstack, userData->frames);
    for ( int i = 0; i < userData->frames; i++ ) {
        char buff[500] = {0};
        snprintf(buff, sizeof(buff), "frames %s", userData->strs[i]);
        CrashlyticsLog(buff);
        CCLOG(buff);
    }
    if( userData->strs) {
        free(userData->strs);
    }
    delete userData;
    
    assert(0);
    
    CrashlyticsLogException(data);
}

void addBackTraceInfo( cocos2d::Ref* object ) {
    
    if (!CrashController::getFabricFlag()) {
        return;
    }
    
    if( object != NULL ) {
        const size_t max = 10;
        void* buffer[max] = {0};
        backtrace(buffer, max);
//        object->nameDebugInfo1.assign(buffer, buffer + max);
        object->nameDebugInfo1.insert(object->nameDebugInfo1.end(), buffer, buffer + max);
    }
}
void printRefDebugInfo( cocos2d::Ref* object ) {
    
    if (!CrashController::getFabricFlag()) {
        return;
    }
    
    if (object != nullptr && object->nameDebugInfo1.size() > 0) {
        char buff[500] = {0};
        snprintf(buff, sizeof(buff), "types: %s", object->debugNodeType.c_str());
        CrashlyticsLog(buff);
        CCLOG(buff);
        char** strs = backtrace_symbols(object->nameDebugInfo1.data(), object->nameDebugInfo1.size());
        for ( int i = 0; i < object->nameDebugInfo1.size(); i++ ) {
            char buff2[500] = {0};
            snprintf(buff2, sizeof(buff2), "frames %s", strs[i]);
            CrashlyticsLog(buff2);
            CCLOG(buff2);
        }
        if( strs) {
            free(strs);
        }
        
        assert(0);
        
        CrashlyticsLogException(object->debugNodeType.c_str());
    }
}

void ForcePrintBackTraceTolog(const char* data)
{
    CrashlyticsLog(data);
    
    struct User_Data {
        void* callstack[128];
        int frames;
        char** strs;
    };
    User_Data* userData = new User_Data();
    userData->strs = NULL;
    userData->frames = backtrace(userData->callstack, 128);
    userData->strs = backtrace_symbols(userData->callstack, userData->frames);
    for ( int i = 0; i < userData->frames; i++ ) {
        char buff[500] = {0};
        snprintf(buff, sizeof(buff), "frames %s", userData->strs[i]);
        CrashlyticsLog(buff);
        CCLOG(buff);
    }
    if( userData->strs) {
        free(userData->strs);
    }
    delete userData;
    
    assert(0);
    
    CrashlyticsLogException(data);
}

chash_map<std::string, chash_set<std::intptr_t> *> ObjectsTracer::_traceInfo;
chash_map<std::string, unsigned int> ObjectsTracer::_traceInfoSimple;
ObjectsTracer::CallstackEntry ObjectsTracer::_callstackEntry;
char * ObjectsTracer::_parsedSymbolBuff(nullptr);
bool ObjectsTracer::isTracing(false);
unsigned int ObjectsTracer::_tracingType(0);

void ot_onObjectCreate(void *obj) { ObjectsTracer::onObjectCreate(obj); }
void ot_onObjectDestroy(void *obj) { ObjectsTracer::onObjectDestroy(obj); }
bool ot_isTracing() { return ObjectsTracer::inTracing(); }
void ot_start(unsigned int type = 0) { ObjectsTracer::start(type); }
void ot_stop() { ObjectsTracer::stop(); }
std::string ot_getCurrentCallStackString() { return ObjectsTracer::getCurrentCallStackString(); }

void ObjectsTracer::onObjectCreate(void *obj)
{
    if(!isTracing) { return; }
    if(obj == nullptr) { return; }
    
#ifndef _IF_debug_helper_object_tracing_stack_depth
#define _IF_debug_helper_object_tracing_stack_depth 40
#endif
//    if(ObjectsTracer::_tracingType == 0) // normal
//    {
        // read calling-stack info
        std::string entryString = ObjectsTracer::getCurrentCallStackString(3);
        
        // save object address
        chash_map<std::string, chash_set<std::intptr_t> *>::iterator it = ObjectsTracer::_traceInfo.find(entryString);
        chash_set<std::intptr_t> * set = nullptr;
        if(it == ObjectsTracer::_traceInfo.end())
        {
            set = new chash_set<std::intptr_t>();
            ObjectsTracer::_traceInfo[entryString] = set;
        }
        else
        {
            set = it->second;
        }
        set->insert(std::intptr_t(obj));
//    }
//    else if(ObjectsTracer::_tracingType == 1) // simple
//    {
//        std::string typeString = typeid(*obj).name();
//        if(typeString.empty()) { typeString = "(type_not_found)"; }
//        chash_map<std::string, unsigned int>::iterator it = ObjectsTracer::_traceInfoSimple.find(typeString);
//        if(it == ObjectsTracer::_traceInfoSimple.end())
//        {
//            ObjectsTracer::_traceInfoSimple[typeString] = 1;
//        }
//        else
//        {
//            ++it->second;
//        }
//    }
}

void ObjectsTracer::onObjectDestroy(void *obj)
{
    if (!isTracing) { return; }
    
    // find call-stack entry with address and remove entry
    chash_map<std::string, chash_set<std::intptr_t> *>::iterator it = ObjectsTracer::_traceInfo.begin();
    for(; it != ObjectsTracer::_traceInfo.end(); ++ it)
    {
        chash_set<std::intptr_t>* set = it->second;
        chash_set<std::intptr_t>::iterator entry = set->find(std::intptr_t(obj));
        if(entry != set->end())
        {
            set->erase(entry);
        }
    }
}

void ObjectsTracer::start(unsigned int type/* = 0*/)
{
    ObjectsTracer::_tracingType = type;
    ObjectsTracer::isTracing = true;
}
void ObjectsTracer::stop(bool report/* = true*/)
{
    ObjectsTracer::isTracing = false;
    if(report)
    {
        ObjectsTracer::printTracingReport();
    }
    ObjectsTracer::clean();
}

void ObjectsTracer::printTracingReport()
{
    // if all objects are destroyed,
    if(ObjectsTracer::_traceInfo.empty())
    {
        // print OK
        CCLOG("----------- all objects released in the session ---------------");
    }
    
    int objectCount = 0;
//    if(ObjectsTracer::_tracingType == 0)
//    {
        chash_map<std::string, chash_set<std::intptr_t> *>::iterator it = ObjectsTracer::_traceInfo.begin();
        for(; it != ObjectsTracer::_traceInfo.end(); ++ it)
        {
            chash_set<std::intptr_t>* set = it->second;
            if (!set || set->empty()) { continue; }
            
            if(objectCount == 0)
            {
                CCLOG("-----------object(s) not released in the session (below) ---------------");
            }
            
            // print callstack and set count
            CCLOG("%d object(s) created at:\n", set->size());
            CCLOG(it->first.c_str());
            
            objectCount += set->size();
        }
//    }
//    else if(ObjectsTracer::_tracingType == 1)
//    {
//        chash_map<std::string, unsigned int>::iterator it = ObjectsTracer::_traceInfoSimple.begin();
//        for(; it != ObjectsTracer::_traceInfoSimple.end(); ++it)
//        {
//            if(objectCount == 0)
//            {
//                CCLOG("-----------object(s) not released in the session (below) ---------------");
//            }
//            
//            // print callstack and set count
//            CCLOG("%d %s object(s) \n", it->second, it->first.c_str());
//            
//            objectCount += it->second;
//        }
//    }

    if(objectCount == 0)
    {
        // print OK
        CCLOG("-----------all objects released in the session---------------");
    }
    else
    {
        CCLOG("-----------%d object(s) not released in the session (above) ---------------", objectCount);
    }
}

void ObjectsTracer::clean()
{
    if(ObjectsTracer::_traceInfo.empty())
    {
        return;
    }
    
    chash_map<std::string, chash_set<std::intptr_t> *>::iterator it = ObjectsTracer::_traceInfo.begin();
    for(; it != ObjectsTracer::_traceInfo.end(); ++ it)
    {
        chash_set<std::intptr_t>* set = it->second;
        if (set)
        {
            delete set;
        }
    }
    ObjectsTracer::_traceInfo.clear();
}

std::string objectsTracer_getCallStack(int ignoreStacks = 0)
{
    return ObjectsTracer::getCurrentCallStackString(ignoreStacks);
}

std::string ObjectsTracer::getCurrentCallStackString(int ignoreStacks)
{
    void * callStackData[_IF_debug_helper_object_tracing_stack_depth] = {0};
    int count = backtrace(callStackData, _IF_debug_helper_object_tracing_stack_depth);
    char ** symbols =backtrace_symbols(callStackData, count);
    std::string callstackString;
    for ( int i = 0; i < count; i++ ) {
        if(i < ignoreStacks) { continue; }
        callstackString += ObjectsTracer::_tracingType == 0 ? ObjectsTracer::parseSymbol(symbols[i]) : symbols[i];
        
        callstackString += "\n";
        if(ObjectsTracer::_tracingType == 1 && count == 25) { break; }
    }
    
    if(symbols) { free(symbols); }
    
    return callstackString;
}

std::string ObjectsTracer::parseSymbol(char * symbol)
{
    ObjectsTracer::parseSymbol(symbol, &ObjectsTracer::_callstackEntry);
    std::string str = ObjectsTracer::composeCallstackString();
    
    return str;
}

#define objects_tracer_symbol_column_no_length 4
#define objects_tracer_symbol_column_offset_length 8
#define objects_tracer_symbol_column_module_length 14
#define objects_tracer_symbol_column_address_length 24
#define objects_tracer_symbol_column_function_length 200

void ObjectsTracer::parseSymbol(char * symbol, ObjectsTracer::CallstackEntry * entry)
{
    assert(entry != nullptr);
    
    // initialize entry object
    if(entry->no == nullptr)
    {
        entry->no = new char[objects_tracer_symbol_column_no_length + 1];
        entry->module = new char[objects_tracer_symbol_column_module_length + 1];
        entry->address = new char[objects_tracer_symbol_column_address_length + 1];
        entry->offset = new char[objects_tracer_symbol_column_offset_length + 1];
        entry->function = new char[objects_tracer_symbol_column_function_length + 1];
    }
    
    entry->no[objects_tracer_symbol_column_no_length] = 0;
    entry->module[objects_tracer_symbol_column_module_length] = 0;
    entry->address[objects_tracer_symbol_column_address_length] = 0;
    entry->offset[objects_tracer_symbol_column_offset_length] = 0;
    
    memset(entry->no, ' ', objects_tracer_symbol_column_no_length);
    memset(entry->module, ' ', objects_tracer_symbol_column_module_length);
    memset(entry->address, ' ', objects_tracer_symbol_column_address_length);
    memset(entry->offset, ' ', objects_tracer_symbol_column_offset_length);
    memset(entry->function, 0, objects_tracer_symbol_column_function_length);
    
    if(symbol == nullptr) { return; }
    unsigned int length = strlen(symbol);
    
    bool in_spaces = false;
    bool in_bracket = false;
    size_t item_start = 0;
    size_t item_end = 0;
    unsigned int column_index = 0;
    //const char * symbol_buff = symbol.c_str();
    
    for(unsigned int i = 0; i < length; ++i)
    {
        bool item_closed = false;
        
        char c = symbol[i];
        if(i == 0) {
            in_spaces = c == ' ';
            continue;
        }
        
        if(in_bracket)
        {
            if(c == ']')
            {
                in_bracket = false;
            }
        }
        else
        {
            if(in_spaces)
            {
                if(c != ' ')
                {
                    in_spaces = false;
                    item_start = i;
                }
            }
            else
            {
                if(c == ' ')
                {
                    in_spaces = true;
                    item_closed = true;
                    item_end = i - 1;
                }
            }
            
            if(c == '[')
            {
                in_bracket = true;
            }
        }
        
        // last column
        if(i == length - 1 && c != ' ')
        {
            item_closed = true;
            item_end = i;
        }
        
        int status;
        char * buff = nullptr;
        if(item_closed)
        {
            switch (column_index) {
                case 0:
                    // stack index
                    memcpy(entry->no, symbol + item_start, MIN(item_end - item_start + 1, objects_tracer_symbol_column_no_length));
                    break;
                case 1:
                    // module
                    memcpy(entry->module, symbol + item_start, MIN(item_end - item_start + 1, objects_tracer_symbol_column_module_length));
                    break;
                case 2:
                    // address
                    memcpy(entry->address, symbol + item_start, MIN(item_end - item_start + 1, objects_tracer_symbol_column_address_length));
                    break;
                case 3:
                    // function
                    memcpy(entry->function, symbol + item_start, MIN(item_end - item_start + 1, objects_tracer_symbol_column_function_length));
                    buff = abi::__cxa_demangle(entry->function, 0, 0, &status);
                    if(buff != nullptr)
                    {
                        strncpy(entry->function, buff, MIN(strlen(buff), objects_tracer_symbol_column_function_length)) ;
                        free(buff);
                    }
                    break;
                    //case 4: // +
                case 5:
                    // offset
                    memcpy(entry->offset, symbol + item_start, MIN(item_end - item_start + 1, objects_tracer_symbol_column_offset_length));
                    break;
                default:
                    break;
            }
            ++column_index;
        }
    }
    
    if(column_index != 6)
    {
        CCLOG("ot>>>>>>>> abnormal symbol string: %s", symbol);
    }
}
std::string ObjectsTracer::composeCallstackString()
{
    if(ObjectsTracer::_parsedSymbolBuff == nullptr)
    {
        ObjectsTracer::_parsedSymbolBuff = new char[500];
    }
    snprintf(ObjectsTracer::_parsedSymbolBuff, 500, " %s %s   %s  +  %s",
             ObjectsTracer::_callstackEntry.no,
             ObjectsTracer::_callstackEntry.module,
             ObjectsTracer::_callstackEntry.function,
             ObjectsTracer::_callstackEntry.offset);
    
    return ObjectsTracer::_parsedSymbolBuff;
}

#endif



void startDebugPopupWindow() {
    
}


#include "mongoose.h"
static void ev_mqtt_handler(struct mg_connection *nc, int ev, void *p);
class RemoteLog {
public:
    static list<string> logs;
    static std::mutex mu;
    static struct mg_connection *nc;
    static struct mg_mgr mgr;
    static bool hasSendSuccess;
    static bool hasSubSuccess;
    static bool hasConnect;
    static bool hasError;
    static condition_variable m_sleepCondition;
    static condition_variable m_hasCreateServer;
    static void OutputLog(const char* val) {
        mu.lock();
        logs.push_back(val);
        mu.unlock();
        m_sleepCondition.notify_all();
    }
    
    static void sendLogs() {
        for(;;) {
            mu.lock();
            int size = logs.size();
            string onelog;
            if( size > 0 ) {
                onelog = logs.front();
                logs.pop_front();
            }
            mu.unlock();
            
            if( onelog.size() == 0 ) {
                break;
            }
            if( hasError ) {
                break;
            }
            static int i = 0;
            hasSendSuccess = false;
            mg_mqtt_publish(nc, "/logs", i++, MG_MQTT_QOS(0), onelog.c_str(),
                            onelog.size());
            mg_mgr_poll(&mgr, 10);
            if( size == 0 ) {
                break;
            }
        }
    }
    
    static void startSendingService() {
        
        auto startProcess = []{
            std::mutex signalMutexForConnect;
            std::unique_lock<std::mutex> signal_eventForConnect(signalMutexForConnect);
            m_hasCreateServer.wait(signal_eventForConnect);
            mg_mgr_init(&mgr, NULL);
            nc = mg_connect(&mgr, "127.0.0.1:2883", ev_mqtt_handler);
            if ( nc == NULL) {
                fprintf(stderr, "mg_connect(%s) failed\n", "127.0.0.1");
                return;
            }
            for (;;) {
                if( hasConnect ) {
                    break;
                }
                if( hasError ) {
                    break;
                }
                mg_mgr_poll(&mgr, 10);
            }
            if( hasError ) {
                return;
            }
            struct mg_mqtt_topic_expression s_topic_expr = {NULL, 0};
            s_topic_expr.topic = "/logs";
            mg_mqtt_subscribe(nc, &s_topic_expr, 1, 42);
            for (;;) {
                if( hasSubSuccess ) {
                    break;
                }
                if( hasError ) {
                    break;
                }
                mg_mgr_poll(&mgr, 10);
            }
            if( hasError ) {
                return;
            }
            std::mutex signalMutex;
            std::unique_lock<std::mutex> signal_event(signalMutex);
            for(;;) {
                if( hasError ) {
                    break;
                }
                sendLogs();
                m_sleepCondition.wait(signal_event);
            }
            if( hasError ) {
                return;
            }
            
        };
        
        auto t = std::thread(startProcess);
        t.detach();
        
    }
    
    static void ev_mqtt_boker_handler(struct mg_connection *c, int ev, void *ev_data) {
//        if (ev != MG_EV_POLL) printf("USER HANDLER GOT EVENT %d\n", ev);
        /* Do your custom event processing here */
        mg_mqtt_broker(c, ev, ev_data);
    }
    
    static void startBokerService() {
        
        auto startProcess = []{

            struct mg_mgr mgr_ser;
            struct mg_connection *c;
            struct mg_mqtt_broker brk;
            
            mg_mgr_init(&mgr_ser, NULL);
            
            if ((c = mg_bind(&mgr_ser, "0.0.0.0:2883", ev_mqtt_boker_handler)) == NULL) {
                fprintf(stderr, "mg_bind(%s) failed\n", "0.0.0.0:2883");
                hasError = true;
                m_hasCreateServer.notify_all();
                return;
            }
            mg_mqtt_broker_init(&brk, NULL);
            c->priv_2 = &brk;
            mg_set_protocol_mqtt(c);

            m_hasCreateServer.notify_all();
            for (;;) {
                mg_mgr_poll(&mgr_ser, 1000);
            }
        };
        auto t = std::thread(startProcess);
        t.detach();
    }
    
};

list<string> RemoteLog::logs;
std::mutex RemoteLog::mu;
struct mg_connection *RemoteLog::nc = nullptr;
struct mg_mgr RemoteLog::mgr;
bool RemoteLog::hasSendSuccess = false;
bool RemoteLog::hasSubSuccess = false;
bool RemoteLog::hasConnect = false;
bool RemoteLog::hasError = false;
condition_variable RemoteLog::m_sleepCondition;
condition_variable RemoteLog::m_hasCreateServer;

static void ev_mqtt_handler(struct mg_connection *nc, int ev, void *p) {
    struct mg_mqtt_message *msg = (struct mg_mqtt_message *) p;
    (void) nc;
    
//    if (ev != MG_EV_POLL) printf("USER HANDLER GOT EVENT %d\n", ev);
    
    switch (ev) {
        case MG_EV_CONNECT: {
            struct mg_send_mqtt_handshake_opts opts;
            memset(&opts, 0, sizeof(opts));
            opts.user_name = "";
            opts.password = "";
            
            mg_set_protocol_mqtt(nc);
            mg_send_mqtt_handshake_opt(nc, "dummy", opts);
            
            break;
        }
        case MG_EV_MQTT_CONNACK:
            if (msg->connack_ret_code != MG_EV_MQTT_CONNACK_ACCEPTED) {
//                printf("Got mqtt connection error: %d\n", msg->connack_ret_code);
            }
            //            s_topic_expr.topic = s_topic;
            //            printf("Subscribing to '%s'\n", s_topic);
            //            mg_mqtt_subscribe(nc, &s_topic_expr, 1, 42);
            RemoteLog::hasConnect = true;
            break;
        
        case MG_EV_MQTT_PUBACK:
            //            printf("Message publishing acknowledged (msg_id: %d)\n", msg->message_id);
            RemoteLog::hasSendSuccess = true;
            break;
        case MG_EV_MQTT_SUBACK:
//            printf("Subscription acknowledged, forwarding to '/test'\n");
            RemoteLog::hasSubSuccess = true;
            break;
        case MG_EV_MQTT_PUBLISH: {
            RemoteLog::hasSendSuccess = true;
            break;
        }
        case MG_EV_CLOSE:
            printf("Connection closed\n");
    }
}

void outputRemoateLog(const char* val) {
    if(g_enable_remote_log && !RemoteLog::hasError) {
        RemoteLog::OutputLog(val);
    }
}

void startRemoteLogService() {
    g_enable_remote_log = CCUserDefault::getInstance()->getBoolForKey("IsRemoteLogService", false);
    g_enable_global_log = g_enable_remote_log;
    if( g_enable_remote_log ) {
        //顺序很重要，先启动客户端，再启动服务端
        RemoteLog::startSendingService();
        RemoteLog::startBokerService();
    }
    
    bool isStartHttp = CCUserDefault::getInstance()->getBoolForKey("IsHttpStarting", false);
    if( isStartHttp ) {
        startHttpServer();
    }
    
    bool isStartFTP = CCUserDefault::getInstance()->getBoolForKey("IsFTPService", false);
    if( isStartFTP ) {
        startFTPServer();
    }
}

//#include "cocos2d.h"
extern void getIPAddress(string& ips, const char* port);
void enableNetService( bool val, const char* content, const char* port ) {
    auto layerColor =  LayerColor::create(Color4B(255,255,255,255), 400, 600);
    layerColor->ignoreAnchorPointForPosition(false);
    layerColor->setAnchorPoint({0.5f,0.5f});
    auto size = CCDirector::sharedDirector()->getWinSize();
    layerColor->setPosition(size.width/2, size.height/2);
    auto textContent = Label::create();
    textContent->setAnchorPoint({0.0f,1.0f});
    string ips;
    getIPAddress(ips,port);
    if( val ) {
        ips.append("\nOpen ").append(content);
    }
    else {
        ips.append("\nClose ").append(content);
    }
    ips.append("\nPlease Restart!!!");
    textContent->setString(ips.c_str());
    textContent->setFontSize(30);
    textContent->setPosition(10,600 - 10);
    textContent->setTextColor(Color4B(0,0,0,255));
    layerColor->addChild(textContent);
    
    auto displayLayer = SceneController::getInstance()->getCurrentLayerByLevel(LEVEL_AUTO_TIP);
    displayLayer->addChild(layerColor);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    auto spClose = CCLoadSprite::createSprite("panel_close_btn.png");
    spClose->setPosition({400 - 50,  50});
    layerColor->addChild(spClose);
    listener->onTouchBegan = [layerColor,spClose](Touch *touch, Event *unused_event) {
        if( isTouchInside(spClose, touch) && layerColor->isVisible() ) {
            return true;
        }
        return false;
    };
    listener->onTouchMoved = [](Touch *touch, Event *unused_event) {
        return;
    };
    listener->onTouchEnded = [layerColor](Touch *touch, Event *unused_event) {
        layerColor->removeFromParent();
        return;
    };;
    listener->onTouchCancelled = CC_CALLBACK_2(Layer::onTouchCancelled, layerColor);
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, layerColor);
}
static bool isFTPHasStarting = false;
void startFTPServer() {
    
    auto startProcess = []{
        isFTPHasStarting = true;
        string s = CCFileUtils::getInstance()->getWritablePath();
        struct cmd_opts *copts= (struct cmd_opts *)malloc(sizeof(struct cmd_opts));
        copts->daemonize    = false;
        copts->listen_any   = true;
        copts->port         = 2100;
        copts->userid       = 0;
        copts->chrootdir    = (char*)s.c_str();
        copts->max_conn     = 5;
        copts->listen_addr  = NULL;
        create_socket(copts);
        free(copts);
        isFTPHasStarting = false;
    };
    if( !isFTPHasStarting ) {
        auto t = std::thread(startProcess);
        t.detach();
    }

}


