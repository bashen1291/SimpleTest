//
//  CommonInclude.h
//  IF
//
//  Created by 吴 凌江 on 13-8-28.
//
//

#ifndef IF_CommonInclude_h
#define IF_CommonInclude_h

#include "cocos2d.h"
#include "cocos-ext.h"
#include "DebugLog.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

#define __for_filter__ \
{string name = __FILE__;\
cocos2d::log("%s::%s,line:%d",\
name.substr(name.find_last_of("/") + 1).c_str(), __FUNCTION__, __LINE__);\
}\

#endif
