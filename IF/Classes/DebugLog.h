//
//  DebugLog.h
//  WarZ
//  using NSLOG instead of NSLog in Debug Model
//  Created by xuzhuang on 16/4/2.
//
//

#ifndef DebugLog_h
#define DebugLog_h

#if DEBUG || COCOS2D_DEBUG > 0
#define NSLOG(format, ...) NSLog(format, ## __VA_ARGS__)
#else
#define NSLOG(format, ...)
#endif
#endif /* DebugLog_h */
