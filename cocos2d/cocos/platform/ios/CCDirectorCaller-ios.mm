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

#include "platform/CCPlatformConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS

#import "CCDirectorCaller-ios.h"

#import <Foundation/Foundation.h>
#import <OpenGLES/EAGL.h>

#import "base/CCDirector.h"
#import "CCEAGLView-ios.h"
#include "base/CCGlobalLock.h"

static id s_sharedDirectorCaller;

@interface NSObject(CADisplayLink)
+(id) displayLinkWithTarget: (id)arg1 selector:(SEL)arg2;
-(void) addToRunLoop: (id)arg1 forMode: (id)arg2;
-(void) setFrameInterval: (NSInteger)interval;
-(void) invalidate;
@end

@implementation CCDirectorCaller

@synthesize interval;

extern dispatch_queue_t BackRenderLoopQueue;
extern EAGLContext* backgroundContext;
extern pthread_t MAIN_THREAD_ID;
bool isStopBackRender = false;


static void animationloop() {
//    if( isStopBackRender ) {
//        return;
//    }
    cocos2d::Director* director = cocos2d::Director::getInstance();
    [EAGLContext setCurrentContext:backgroundContext];
    [(CCEAGLView*)director->getOpenGLView()->getEAGLView() prepareBufferForMultiThread];
    director->mainLoop();
    
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, 16 * NSEC_PER_MSEC), BackRenderLoopQueue, (BackRenderLoopQueue, ^{ animationloop(); }));
}

+(id) sharedDirectorCaller
{
    if (s_sharedDirectorCaller == nil)
    {
        s_sharedDirectorCaller = [CCDirectorCaller new];
    }
    
    return s_sharedDirectorCaller;
}

+(void) destroy
{
    [s_sharedDirectorCaller stopMainLoop];
    [s_sharedDirectorCaller release];
    s_sharedDirectorCaller = nil;
}

-(void) alloc
{
        interval = 1;
}

-(void) dealloc
{
    [displayLink release];
    [super dealloc];
}

-(void) startMainLoop
{
        // Director::setAnimationInterval() is called, we should invalidate it first
    [self stopMainLoop];
    
    displayLink = [NSClassFromString(@"CADisplayLink") displayLinkWithTarget:self selector:@selector(doCaller:)];
    [displayLink setFrameInterval: self.interval];
    [displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
}

-(void) stopMainLoop
{
    [displayLink invalidate];
    displayLink = nil;
}

-(void) runInBackThread:(const std::function<void ()>)func
{
    dispatch_async(BackRenderLoopQueue, ^{
        if (func) {
//            cocos2d::GlobalLock::lockMainThread();
            
//            cocos2d::Director* director = cocos2d::Director::getInstance();
//            [EAGLContext setCurrentContext:backgroundContext];
//            [(CCEAGLView*)director->getOpenGLView()->getEAGLView() prepareBufferForMultiThread];
            func();
            
//            cocos2d::GlobalLock::unlockMainThread();
        }
    });
}

-(void) runInMainThread:(const std::function<void ()>)func
{
    dispatch_async(dispatch_get_main_queue(), ^{
        if (func) {
            //            cocos2d::Director* director = cocos2d::Director::getInstance();
            //            [EAGLContext setCurrentContext:backgroundContext];
            //            [(CCEAGLView*)director->getOpenGLView()->getEAGLView() prepareBufferForMultiThread];
            func();
        }
    });
}

-(void) setAnimationInterval:(double)intervalNew
{
    // Director::setAnimationInterval() is called, we should invalidate it first
    [self stopMainLoop];
        
    self.interval = 60.0 * intervalNew;
        
    displayLink = [NSClassFromString(@"CADisplayLink") displayLinkWithTarget:self selector:@selector(doCaller:)];
    [displayLink setFrameInterval: self.interval];
    [displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
}
                      
-(void) doCaller: (id) sender
{
    cocos2d::Director* director = cocos2d::Director::getInstance();
    [EAGLContext setCurrentContext: [(CCEAGLView*)director->getOpenGLView()->getEAGLView() context]];
    director->mainLoop();
}

@end

#endif // CC_TARGET_PLATFORM == CC_PLATFORM_IOS

