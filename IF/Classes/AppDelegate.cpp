//
//  IFAppDelegate.cpp
//  IF
//
//  Created by 吴 凌江 on 13-8-28.
//  Copyright __MyCompanyName__ 2013年. All rights reserved.
//

#include "AppDelegate.h"
#include "SimpleAudioEngine.h"

#include "TestScene.h"
#include <curl/curl.h>

extern void printDebugKeyValue(const char* key, const char* value);
extern void startHttpServer();
//#include "HelpshiftCocos2dx.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "android/jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"
#elif(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//#include "CrashReport.h"
#endif

extern pthread_t MAIN_THREAD_ID;
extern void getRandomUUID(std::string& uuid);
extern bool g_isUseCwrzImage;
extern bool g_enable_record_client_pic;
bool g_isApplicationExit = false;
void atexitfun() {
    g_isApplicationExit = true;
}
extern bool g_localZip;

USING_NS_CC;
using namespace CocosDenshion;

extern void printDebugKeyInfo( const char* key, bool value);

bool _main_thread_init = false;
decltype(std::this_thread::get_id()) _main_thread_id;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
    SimpleAudioEngine::end();
}

static float systemBN = -1.0f;

void AppDelegate::initGLContextAttrs()
{
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};
    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching()
{
    CCLOG("applicationDidFinishLaunching start");
    atexit(atexitfun);
    _main_thread_id = std::this_thread::get_id();
    _main_thread_init = true;
    
    MAIN_THREAD_ID = pthread_self();

    printDebugKeyInfo("AppLaunching", true);

    
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    CrashReport::setAppChannel("ios_channel");
//    CrashReport::setAppVersion(GlobalData::shared()->version.c_str());
//    CrashReport::initCrashReport("833dcd3d1a", false);
#endif
    

    // initialize director
    Director* pDirector = Director::getInstance();
//    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());//400ms
    auto glview = pDirector->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("Last WarZ");
    }

    pDirector->setOpenGLView(glview);
    // set PVR enable
    CCTexture2D::PVRImagesHavePremultipliedAlpha(true);
    // set resolution size (width free adjust , width fixed 768)
    Director::getInstance()->getOpenGLView()->setDesignResolutionSize(640, 852, kResolutionFixedWidth);

#if COCOS2D_DEBUG > 0
    // 打开这个测多分辨率
    //    radio=1.78; // iphone5
    //    radio=1.67; // WVGA
    //    radio=1.33; // Ipad
    //    radio=1.5; //Iphone4/4s
    CCSize winSize = pDirector->getWinSize();
    CCSize screenSize = glview->getFrameSize();
    float radio = winSize.width/winSize.height;
    float scale = 852/screenSize.width;
    CCLOG("screen width: %d, height: %d \n resolution width: %d, height: %d \n radio:%.2f, scale:%.2f",
          (int)screenSize.width,(int)screenSize.height,
          (int)winSize.width,(int)winSize.height,
          radio,scale);

    // turn on display FPS
    bool _bDisplayFlag = CCUserDefault::getInstance()->getBoolForKey("displayStats",true);
    pDirector->setDisplayStats(!_bDisplayFlag);

    
#endif

/* Native API */
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//    CrashController::initContext();
//#endif

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 40);

    //资源更新,下载武器图标，所以需要首先读取缓存

    // run
    pDirector->runWithScene(TestScene::create());
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    if (GlobalData::shared()->screenBrightness > 0) {
//        cocos2d::extension::CCDevice::setBrightness(systemBN);
//    }
#endif

    CCLOG("applicationDidEnterBackground start");
    printDebugKeyInfo("AppInWork", false);

    
    cocos2d::CCDirector::sharedDirector()->pause();
    CCDirector::sharedDirector()->stopAnimation();
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->pauseAllEffects();

}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    if (GlobalData::shared()->screenBrightness > 0) {
//        cocos2d::extension::CCDevice::setBrightness(GlobalData::shared()->screenBrightness / 100.0f);
//    }
#endif
    

    
    CCLOG("EnterForeground start");
    printDebugKeyInfo("AppInWork", true);

    cocos2d::CCDirector::sharedDirector()->resume();
    CCDirector::sharedDirector()->startAnimation();
    SimpleAudioEngine::sharedEngine()->resumeAllEffects();

//    });

}

void AppDelegate::applicationDidBecomeActive()
{
    CCLOG("applicationDidBecomeActive start");
    CCLOG("applicationDidBecomeActive end");
}
