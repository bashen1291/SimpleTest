//
//  DebugHelper.hpp
//  WarZ
//
//  Created by kakalong on 16/3/3.
//
//

#ifndef DebugHelper_hpp
#define DebugHelper_hpp

#include <stdio.h>
#include <string>
//void printBackTraceTolog(const char* debugData = nullptr);
bool IsLoadingInf();
void setLoadingInf(bool val);
void prepareLoadingInfo(const char * format, ...);
void clearLoadingInfo();
void getPrepareLoadingInfo(std::string& result);
bool IsFLOG();
void setFLOG(bool val, const std::string& flogParameters);
void CheckFLOG();
void FLOG(const char * format, ...);
bool IsFLOGStr(const std::string& str);
std::string getFLOGPath();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "base/chash_map.h"
#include "base/chash_set.h"

class ObjectsTracer{
public:
    typedef struct CallstackEntry
    {
        char * no;
        char * module;
        char * address;
        char * function;
        char * offset;
        
        CallstackEntry() :
        no(nullptr),
        module(nullptr),
        address(nullptr),
        function(nullptr),
        offset(nullptr) {}
        
        ~CallstackEntry()
        {
            if(no) { delete no; }
            if(module) { delete module; }
            if(address) { delete address; }
            if(function) { delete function; }
            if(offset) { delete offset; }
        }
    }CallstackEntry;
    
    // 0-normal 1-simple
    static void start(unsigned int type = 0);
    static void stop(bool report = true);
    static void onObjectCreate(void * obj);
    static void onObjectDestroy(void * obj);
    static bool inTracing() { return ObjectsTracer::isTracing; }
    static std::string getCurrentCallStackString(int ignoreStacks = 0);
    static void parseSymbol(char * symbol, CallstackEntry * entry);
    
private:
    static bool isTracing;
    static void printTracingReport();
    static void clean();
    static std::string parseSymbol(char * symbol);
    static std::string composeCallstackString();
    
    static chash_map<std::string, chash_set<std::intptr_t> *> _traceInfo;
    static chash_map<std::string, unsigned int> _traceInfoSimple;
    static CallstackEntry _callstackEntry;
    static char * _parsedSymbolBuff;
    static unsigned int _tracingType;
};
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_IOS

#endif /* DebugHelper_hpp */
