////
//  IFAppController.mm
//  IF
//
//  Created by 吴 凌江 on 13-8-28.
//  Copyright __MyCompanyName__ 2013年. All rights reserved.
//
#import <UIKit/UIKit.h>
#import "AppController.h"
#import "cocos2d.h"
#import "CCEAGLView-ios.h"
#import "AppDelegate.h"
#ifdef METAL_ENABLE
    #import "RootViewControllerMetal.h"
#else
    #import "RootViewController.h"
#endif
#import <FBSDKCoreKit/FBSDKCoreKit.h>
#import <FBSDKLoginKit/FBSDKLoginKit.h>
//#import <NanigansSDK/NanigansSDK.h>
#import <Branch/Branch.h>
#import <Fabric/Fabric.h>
#import <Crashlytics/Crashlytics.h>

//#import "AppLibHelper.h"
#include "CCGlobalLock.h"
#include "DebugLog.h"
// -- FCM -- below
//#import <Parse/Parse.h>
#import "Firebase.h"
// -- FCM -- above

//用来防止icloud同步资源
#include "sys/xattr.h"


#import <TencentOpenAPI/TencentOAuth.h>
#import "WeiboSDK.h"

#include "TrackingIO.h"
@implementation AppController

@synthesize window;
@synthesize viewController;

#pragma mark -
#pragma mark Application lifecycle

dispatch_queue_t BackRenderLoopQueue = nil;
EAGLContext* backgroundContext = nil;

// cocos2d application instance
static AppDelegate* s_sharedApplication = new AppDelegate();
static BOOL s_isEnterFLOGMode = NO;
static BOOL s_showFLOGInScreen = NO;
extern bool g_reSendHeartBreak;
extern pthread_t MAIN_THREAD_ID;

- (void)registerElvaCloseNotifications
{
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(elvaCloseNotifications:)
                                                 name:@"elva_notify_warz"
                                               object:nil];
}

- (void)unregisterElvaCloseNotifications {
    [[NSNotificationCenter defaultCenter] removeObserver:self
                                                    name:@"elva_notify_warz"
                                                  object:nil];
}

- (void)elvaCloseNotifications:(NSNotification *)notice
{
//    NSLOG(@"elva close!");
//    self.viewController.view.backgroundColor = [UIColor blackColor];
}

// -- FCM -- below
- (void)connectToFCM
{
    [[FIRMessaging messaging] connectWithCompletion:^(NSError * _Nullable error) {
        if (error != nil) {
            NSLOG(@"Unable to connect to FCM. %@. Code 2001 means already connected.", error);
        } else {
            NSLOG(@"Connected to FCM.");
        }
    }];
}
- (void)onFCMTokenRefresh {
    // Get the default token if the earlier default token was nil. If the we already
    // had a default token most likely this will be nil too. But that is OK we just
    // wait for another notification of this type.
//    NSString *token = [[FIRInstanceID instanceID] token];
//    // custom stuff as before.
//    [self connectToFCM];
//    if (token) {
//        NSLOG(@"parse token is %s",[token UTF8String]);
////        cocos2d::CCUserDefault::sharedUserDefault()->setStringForKey("ftoken", [token UTF8String]);
//        PushUtil::getInstance()->onRegisterdAccount("fcm",[token UTF8String],"");
//    }
//    else{
//        NSLOG(@"TOKEN IS NIL");
//    }

}
// -- FCM -- above
//static Reachability *s_reachability = nil;
- (void)setUpRechability
{

//    [[Reachability reachabilityForInternetConnection] startNotifier];
//    if( s_reachability == nil) {
//        s_reachability = [Reachability reachabilityForInternetConnection];
//        [s_reachability retain];
//    }
//    [s_reachability startNotifier];
}

- (void)handleNetworkChange:(NSNotification *)notice
{
//    Reachability* reachablility = [Reachability reachabilityForInternetConnection];
//    NetworkStatus remoteHostStatus = [reachablility currentReachabilityStatus];
//
//    if (remoteHostStatus == ReachableViaWiFi || remoteHostStatus == ReachableViaWWAN) {
//        CCSafeNotificationCenter::sharedNotificationCenter()->postNotification("NetworkAvailable");
//        g_reSendHeartBreak = true;
//    }
//    [reachablility release];
}

/**
 *  下面方法为防止icloud同步资源
 */
-(void)addNotBackUpiCloud{
    
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_LOW,0), ^{
    
        NSArray *docPaths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask,YES);

        NSArray *libPaths = NSSearchPathForDirectoriesInDomains(NSLibraryDirectory, NSUserDomainMask, YES);

        NSString *docPath = [docPaths objectAtIndex:0];

        NSString *libPath = [libPaths objectAtIndex:0];


        [self fileList:docPath];

        [self fileList:libPath];
    
    });
}

- (void)fileList:(NSString*)directory{
    
    
    NSError *error = nil;
    
    NSFileManager * fileManager = [NSFileManager defaultManager];
    
    NSArray *fileList = [fileManager contentsOfDirectoryAtPath:directory error:&error];
    
    for (NSString* each in fileList) {
        
        NSMutableString* path = [[[NSMutableString alloc]initWithString:directory] autorelease];
        
        [path appendFormat:@"/%@",each];
        
        
        NSURL *filePath = [NSURL fileURLWithPath:path];
        
        [self addSkipBackupAttributeToItemAtURL:filePath];
        
        [self fileList:path];
        
        
    }
    
}

//设置禁止云同步

-(BOOL)addSkipBackupAttributeToItemAtURL:(NSURL *)URL{
    
    
    double version = [[UIDevice currentDevice].systemVersion doubleValue];//判定系统版本。
    
    
    
    if(version >=5.1f){
        
        
        NSError *error = nil;
        
        BOOL success = [URL setResourceValue: [NSNumber numberWithBool: YES]
                        
                                      forKey: NSURLIsExcludedFromBackupKey error: &error];
        
        if(!success){
            
            NSLOG(@"Error excluding %@ from backup %@", [URL lastPathComponent], error);
            
        }
        
        
        return success;
        
        
    }
    
    const char* filePath = [[URL path] fileSystemRepresentation];
    
    
    const char* attrName = "com.apple.MobileBackup";
    
    u_int8_t attrValue = 1;
    
    
    int result = setxattr(filePath, attrName, &attrValue, sizeof(attrValue), 0, 0);
    
    return result == 0;
    
    
}



- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    GBLK_GLOBAL_LOCK_UNIQUE;
    // set Reachability observer
    signal(SIGPIPE, SIG_IGN);
    [self setUpRechability];
    
    [self registerElvaCloseNotifications];
    
    if (launchOptions[UIApplicationLaunchOptionsURLKey] == nil) {
        [FBSDKAppLinkUtility fetchDeferredAppLink:^(NSURL *url, NSError *error) {
            if (error) {
                NSLOG(@"Received error while fetching deferred app link %@", error);
            }
            if (url) {
                NSLOG(@" deferred app link %@", url);
                [[UIApplication sharedApplication] openURL:url];
            }
        }];
    }


    MAIN_THREAD_ID = pthread_self();
    
    [Fabric with:@[[Crashlytics class]]];
    
//    [WeiboSDK enableDebugMode:YES];
//    [WeiboSDK registerApp:@"1076104563"];
    
    //初始化iphoneX开关
    

    id handler = ^(CFRunLoopObserverRef observer, CFRunLoopActivity activity) {
        static int lockCount = 0;
        switch (activity) {
            case kCFRunLoopEntry:
                // About to enter the processing loop. Happens
                // once per `CFRunLoopRun` or `CFRunLoopRunInMode` call
//                NSLOG(@"kCFRunLoopEntry");
                lockCount++;
                cocos2d::GlobalLock::lockMainThread();
                
                break;
//            case kCFRunLoopBeforeTimers:
//                NSLOG(@"kCFRunLoopBeforeTimers");
//                break;
//            case kCFRunLoopBeforeSources:
//                // Happens before timers or sources are about to be handled
//                NSLOG(@"kCFRunLoopBeforeSources");
//                break;
            case kCFRunLoopBeforeWaiting:
                lockCount--;
                if( lockCount < 0) {
                    lockCount = 0;
                    return;
                }
                cocos2d::GlobalLock::unlockMainThread();
                // All timers and sources are handled and loop is about to go
                // to sleep. This is most likely what you are looking for :)
//                NSLOG(@"kCFRunLoopBeforeWaiting count %d", ++i);
                break;
            case kCFRunLoopAfterWaiting:
                lockCount++;
                cocos2d::GlobalLock::lockMainThread();
                // About to process a timer or source
//                NSLOG(@"kCFRunLoopAfterWaiting count %d", --i);
                break;
            case kCFRunLoopExit:
                // The `CFRunLoopRun` or `CFRunLoopRunInMode` call is about to
                // return
                lockCount--;
                if( lockCount < 0) {
                    lockCount = 0;
                    return;
                }
                cocos2d::GlobalLock::unlockMainThread();
                break;
        }
    };
    
    CFRunLoopObserverRef obs = CFRunLoopObserverCreateWithHandler(kCFAllocatorDefault, kCFRunLoopAllActivities, true, 0 /* order */, handler);
    CFRunLoopAddObserver([NSRunLoop mainRunLoop].getCFRunLoop, obs, kCFRunLoopCommonModes);
    CFRelease(obs);
    // Override point for customization after application launch.

//    cocos2d::Application *app = cocos2d::Application::getInstance();
//    app->initGLContextAttrs();
//    cocos2d::GLViewImpl::convertAttrs();
    
    // Add the view controller's view to the window and display.
    window = [[UIWindow alloc] initWithFrame: [[UIScreen mainScreen] bounds]];
    
    auto viewFrameSize = [[UIScreen mainScreen] bounds];

    
    //anning begin
    

    
    
    //pixelFormat: (NSString*)cocos2d::GLViewImpl::_pixelFormat
    //depthFormat: cocos2d::GLViewImpl::_depthFormat
    
    //pixelFormat: kEAGLColorFormatRGBA8
    //depthFormat: GL_DEPTH_COMPONENT16
    CCEAGLView *__glView = [CCEAGLView viewWithFrame: viewFrameSize
                                     pixelFormat: kEAGLColorFormatRGBA8
                                     depthFormat: GL_DEPTH_COMPONENT16
                              preserveBackbuffer: NO
                                      sharegroup: nil
                                   multiSampling: NO
                                 numberOfSamples:0 ];
    
    [__glView setMultipleTouchEnabled: YES];
    __glView.opaque = NO;
    __glView.backgroundColor = [UIColor blackColor];
    float systemVersion = [[UIDevice currentDevice].systemVersion floatValue];
#ifdef METAL_ENABLE
    // Use RootViewController manage EAGLView
    viewController = [[RootViewControllerMetal alloc] initWithNibName:nil bundle:nil];
    viewController.wantsFullScreenLayout = YES;
    if(systemVersion < 9.0) {
        viewController.view = __glView;
    } else {
        UIView* theMainView = [[UIView alloc] initWithFrame:[window bounds]];

        CGRect frameRect;
        frameRect.origin.x = 0;
        frameRect.origin.y = 0;
        frameRect.size.width = 320;
        frameRect.size.height = 480;
        MTKView* __metalView = [[MTKView alloc] initWithFrame:frameRect
                                                        device:nil];

        [theMainView addSubview:__metalView];
        [theMainView addSubview:__glView];

        viewController.view = theMainView;

        [viewController setMetalView:__metalView
                              glView:__glView];
    }
#else
    // Use RootViewController manage EAGLView
    viewController = [[RootViewController alloc] initWithNibName:nil bundle:nil];
    viewController.wantsFullScreenLayout = YES;
    viewController.view = __glView;
#endif
    // Set RootViewController to window
    if (systemVersion < 6.0) {
        // warning: addSubView doesn't work on iOS6
        [window addSubview: viewController.view];
    } else {
        // use this method on ios6
        [window setRootViewController:viewController];
    }
    

    
    [window makeKeyAndVisible];
    

    
        [[UIApplication sharedApplication] setStatusBarHidden: YES];
    
//    [[SKPaymentQueue defaultQueue] addTransactionObserver:[ShopIAPHelper sharedHelper]];
    
    [viewController register3DTouch];
    
    //[Fabric with:@[CrashlyticsKit]];
    // Override point for customization after application launch.
    Branch *branch = [Branch getInstance];
    [branch initSessionWithLaunchOptions:launchOptions
                            isReferrable:YES
              andRegisterDeepLinkHandler:^(NSDictionary *params, NSError *error) {
                  // route the user based on what's in params
                  if (!error) {
                      NSLOG(@"finished init with params = %@", [params description]);
#ifdef METAL_ENABLE
                      [RootViewControllerMetal afterGetBranchData:params];
#else
                      [RootViewController afterGetBranchData:params];
#endif
                  } else {
                      NSLOG(@"failed init: %@", error);
                  }
              }];

//    [Parse setApplicationId:@"Ldq0MwmxgHRg0mZYrcHsPBXUu1mj4O399HS0jXzr"
//                  clientKey:@"uXHQxnjNDimLohO5czyq34zj2bKZxBg4TE9o7jp2"];
    

//    
//    [Helpshift installForApiKey:@"724912cc76e6e0e0b3426d0f83a88832"
//                     domainName:@"lcyd.helpshift.com"
//                          appID:@"lcyd_platform_20150630021209965-edefcf5f44a595e"];

//    AppLibHelper::initLibs();
        // -- FCM -- below
        //registerUILocalNotification();

        // Add observer to listen for the token refresh notification.
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(onFCMTokenRefresh) name:kFIRInstanceIDTokenRefreshNotification object:nil];
        // -- FCM -- above

    cocos2d::GLViewImpl *glview = cocos2d::GLViewImpl::createWithEAGLView(__glView);
    cocos2d::Director::getInstance()->setOpenGLView(glview);

    if (BackRenderLoopQueue == nil) {
        BackRenderLoopQueue = dispatch_queue_create("BackRenderLoopQueue", DISPATCH_QUEUE_SERIAL);
        dispatch_set_target_queue(BackRenderLoopQueue, dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_HIGH, 0));
    }

    cocos2d::CCApplication::sharedApplication()->run();
    
    //注册消息推送
//#if __IPHONE_OS_VERSION_MAX_ALLOWED <= __IPHONE_7_1
//    [[UIApplication sharedApplication] registerForRemoteNotificationTypes: (UIRemoteNotificationTypeBadge | UIRemoteNotificationTypeSound | UIRemoteNotificationTypeAlert)];
//#elif __IPHONE_OS_VERSION_MAX_ALLOWED >= __IPHONE_8_0
//    if ([application respondsToSelector:@selector(registerUserNotificationSettings:)]) {
//        UIUserNotificationSettings* notificationSettings = [UIUserNotificationSettings settingsForTypes:UIUserNotificationTypeAlert | UIUserNotificationTypeBadge | UIUserNotificationTypeSound categories:nil];
//        [[UIApplication sharedApplication] registerUserNotificationSettings:notificationSettings];
//        [[UIApplication sharedApplication] registerForRemoteNotifications];
//    } else {
//        [[UIApplication sharedApplication] registerForRemoteNotificationTypes: (UIRemoteNotificationTypeBadge | UIRemoteNotificationTypeSound | UIRemoteNotificationTypeAlert)];
//    }
//#else
//    [[UIApplication sharedApplication] registerForRemoteNotificationTypes: (UIRemoteNotificationTypeBadge | UIRemoteNotificationTypeSound | UIRemoteNotificationTypeAlert)];
//#endif

    
    [FBSDKProfile enableUpdatesOnAccessTokenChange:YES];
    
    //防止icloud同步
    [self addNotBackUpiCloud];
    
#if __IPHONE_OS_VERSION_MAX_ALLOWED >= __IPHONE_9_0
    [[FBSDKApplicationDelegate sharedInstance] application:application didFinishLaunchingWithOptions:launchOptions];
    return true;
#else
    return [[FBSDKApplicationDelegate sharedInstance] application:application didFinishLaunchingWithOptions:launchOptions];
#endif
    
}

bool isPostFLOGString() {
    return s_showFLOGInScreen == YES ? true:false;
}

void postFLOGString( const char* buf ) {
    if(s_showFLOGInScreen) {
        NSDictionary *userInfo = [NSDictionary dictionaryWithObject:[NSString stringWithUTF8String:buf] forKey:@"content"];
        [[NSNotificationCenter defaultCenter] postNotificationName:
         @"FLOG_UPDATE" object:nil userInfo:userInfo];
    }
}

- (void)applicationWillResignActive:(UIApplication *)application {
    if(s_isEnterFLOGMode)return;
    /*
     Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
     Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
     */
//    cocos2d::CCDirector::sharedDirector()->pause();
//    CSApplicationActiveStatusMonitor_Util::cs_App_WillResignActive();
    cocos2d::CCApplication::sharedApplication()->applicationDidEnterBackground();
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
    if(s_isEnterFLOGMode)return;
    /*
     Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
     */
//    cocos2d::CCDirector::sharedDirector()->resume();
    cocos2d::CCApplication::sharedApplication()->applicationWillEnterForeground();

//TODO:: 
//    cocos2d::Application::getInstance()->applicationDidBecomeActive();
    // 进入游戏，右上角计数清0
    [[UIApplication sharedApplication] setApplicationIconBadgeNumber:0];
//    [FBSDKAppEvents activateApp];
//    AppLibHelper::activateAppsflyer();

    // -- FCM-- below
    [self connectToFCM];
    // -- FCM-- above
}

- (void)applicationDidEnterBackground:(UIApplication *)application {
    if(s_isEnterFLOGMode)return;
    /*
     Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
     If your application supports background execution, called instead of applicationWillTerminate: when the user quits.
     */
//    cocos2d::CCApplication::sharedApplication()->applicationDidEnterBackground();
    //原生发送进入后台的通知
//    CSApplicationActiveStatusMonitor_Util::cs_App_DidEnterBackground();
    [[FIRMessaging messaging] disconnect];
}

- (void)applicationWillEnterForeground:(UIApplication *)application {
    if(s_isEnterFLOGMode)return;
    GBLK_GLOBAL_LOCK_UNIQUE;
    /*
     Called as part of  transition from the background to the inactive state: here you can undo many of the changes made on entering the background.
     */
//    [NANTracking trackAppLaunch:nil];
//    cocos2d::CCApplication::sharedApplication()->applicationWillEnterForeground();
    
//    CSApplicationActiveStatusMonitor_Util:: cs_App_WillEnterForeground();
}

- (void)applicationWillTerminate:(UIApplication *)application {
    /*
     Called when the application is about to terminate.
     See also applicationDidEnterBackground:.
     */
}
//fusheng edit
//腾讯互联SDK接入
- (BOOL)application:(UIApplication *)application handleOpenURL:(NSURL *)url
{
    /*
     给自己的App注册一个URL Scheme非常简单，就是在info.plist文件里定义两个键值就OK。
     添加一个叫URL types的键值。
     给其下的Item 1添加一个URL identifier，格式为Reverse Domain Name：com.mycompany.myapp。
     再加一个URL Scheme，然后给它定义一个值，任意字符串。比如：myapp。
     定义结束，就可以使用下面的模式来发送一个URL：

     myapp://
     myapp://some/path/here
     myapp://?foo=1&amp;bar=2
     myapp://some/path/here?foo=1&amp;bar=2

     然后，你的App的 handleOpenURL 会收到一个消息。我们可以把传过来的URL保存在本地。
     */
    if (!url)
    {
        return NO;
    }
    NSString *theURLString = [url absoluteString];
    [[NSUserDefaults standardUserDefaults] setObject:theURLString forKey:@"openurl"];
    [[NSUserDefaults standardUserDefaults] synchronize];
    
    [TencentOAuth HandleOpenURL:url];
    [WeiboSDK handleOpenURL:url delegate:self ];
    return YES;
}

//- (BOOL)application:(UIApplication *)app
//            openURL:(NSURL *)url
//            options:(NSDictionary<NSString *, id> *)options {
//    return [self application:app openURL:url sourceApplication:nil annotation:@{}];
//}

//fusheng end

//- (void)application:(UIApplication *)application didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken {
//    // Store the deviceToken in the current installation and save it to Parse.
//    PFInstallation *currentInstallation = [PFInstallation currentInstallation];
//    [currentInstallation setDeviceTokenFromData:deviceToken];
//    [currentInstallation saveInBackground];
//}
//
//- (void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo {
//    [PFPush handlePush:userInfo];
//}

//获取DeviceToken成功
- (void)application:(UIApplication *)application
        didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken {
    GBLK_GLOBAL_LOCK_UNIQUE;
    NSString *token = [NSString
            stringWithFormat:@"%@", deviceToken];
    token = [token stringByReplacingOccurrencesOfString:@"<" withString:@""];
    token = [token stringByReplacingOccurrencesOfString:@">" withString:@""];
    token = [token stringByReplacingOccurrencesOfString:@" " withString:@""];
    NSLOG(@"deviceToken is:%@", token);

    NSString *fcmtoken = [[FIRInstanceID instanceID] token];
//    GlobalData::shared()->parseRegisterId = std::string([token UTF8String]) + "|apns";
//    if (![token isEqualToString:@""])
//        cocos2d::extension::CCDevice::pushStatus = 1;
//    PushUtil::getInstance()->onRegisterdParseAccount([token UTF8String], "apns");
//    [[AppsFlyerTracker sharedTracker] registerUninstall:deviceToken];

}

//注册消息推送失败
- (void)application:(UIApplication *)application
didFailToRegisterForRemoteNotificationsWithError:(NSError *)error
{
    NSLOG(@"Register Remote Notifications error:{%@}",[error localizedDescription]);
}

//处理收到的消息推送
- (void)application:(UIApplication *)application
didReceiveRemoteNotification:(NSDictionary *)userInfo
{
    GBLK_GLOBAL_LOCK_UNIQUE;
    NSLOG(@"Receive remote notification : %@",userInfo);
    // 收到来自服务器的推送时，图标右上角显示计数为1
    //    int count = CCUserDefault::sharedUserDefault()->getIntegerForKey("badge_number");
    //    CCUserDefault::sharedUserDefault()->setIntegerForKey("badge_number", count + 1);
    [UIApplication sharedApplication].applicationIconBadgeNumber = 1;

//    if (application.applicationState == UIApplicationStateInactive) {
//        [PFAnalytics trackAppOpenedWithRemoteNotificationPayload:userInfo];
//    }
    
    // -- FCM -- below
    // Let FCM know about the message for analytics etc.
    [[FIRMessaging messaging] appDidReceiveMessage:userInfo];
    // handle your message.
    
    // Print message ID.
    NSLOG(@"Firebase message ID: %@", userInfo[@"gcm.message_id"]);
    
    // Pring full message.
    NSLOG(@"%@", userInfo);
    
    // need to call this when setting FirebaseAppDelegateProxyEnabled:NO in GoogleService-Info.plist
//    [[FIRMessaging messaging] appDidReceiveMessage:userInfo];
    // -- FCM -- above
    
    //本地推送记录
//    NSMutableDictionary *newPushInfo = [NSMutableDictionary dictionaryWithDictionary:userInfo];
//    if (application.applicationState == UIApplicationStateInactive || application.applicationState == UIApplicationStateBackground) {
//        if([userInfo objectForKey:@"aps"] && [[userInfo objectForKey:@"aps"] objectForKey:@"alert"]){
//            std::string push_type = "0";
//            NSDictionary *tempAlert = [[userInfo objectForKey:@"aps"] objectForKey:@"alert"];
//            std::string push_msg = [[tempAlert objectForKey:@"body"] UTF8String];
//            if([userInfo objectForKey:@"cok_push_type"]){
//                push_type = [[userInfo objectForKey:@"cok_push_type"] UTF8String];
//            }
//            std::string recordPush = cocos2d::extension::CCDevice::recordPush(push_msg,push_type);
//            NSString *nsRecordPush = [NSString stringWithUTF8String : recordPush.c_str()];
//            [newPushInfo setValue:nsRecordPush forKey:@"cok_push_click"];
//            //sendDataToXingcloud
//            string gameUID = CCCommonUtils::getStringWithEncBySharedUser(GAME_UID);
//            CCCommonUtils::recordPushNotify(push_type,"inner_open",gameUID,"");
//
//            if([userInfo objectForKey:@"goto_type"]){
//                std::string goto_type = [[userInfo objectForKey:@"goto_type"] UTF8String];
//                cocos2d::extension::CCDevice::setGotoType(goto_type);
//            }
//        }
////        [PFPush handlePush:newPushInfo];
//    }
//    if ([[userInfo objectForKey:@"origin"] isEqualToString:@"helpshift"]) {
//        [[Helpshift sharedInstance] handleRemoteNotification:userInfo withController:self.viewController];
//    }
}

- (NSString *)valueForKey:(NSString *)key
           fromQueryItems:(NSArray *)queryItems
{
    NSPredicate *predicate = [NSPredicate predicateWithFormat:@"name=%@", key];
    NSURLQueryItem *queryItem = [[queryItems
                                  filteredArrayUsingPredicate:predicate]
                                 firstObject];
    return queryItem.value;
}

- (void)doDeeplinkParse:(NSURL*)url {
    NSString *version = [UIDevice currentDevice].systemVersion;
    NSString *title = nil;
    NSString *promoteCode = nil;
    NSString *im30_campion = nil;
    if (version.doubleValue >= 8.0) { // iOS系统版本 >= 8.0
        NSURLComponents *urlComponents = [NSURLComponents componentsWithURL:url resolvingAgainstBaseURL:NO];
        NSArray *queryItems = urlComponents.queryItems;
        title = [self valueForKey:@"utm_campaign" fromQueryItems:queryItems];
        promoteCode = [self valueForKey:@"pro_code" fromQueryItems:queryItems];
        im30_campion = [self valueForKey:@"im30_camp" fromQueryItems:queryItems];
    } else{ //iOS系统版本 < 8.0
        NSString *query = [url query];
        NSArray *components = [query componentsSeparatedByString:@"&"];
        NSMutableDictionary *parameters = [[NSMutableDictionary alloc] init];
        if ([parameters count] > 0) {
            for (NSString *component in components) {
                NSArray *subcomponents = [component componentsSeparatedByString:@"="];
                [parameters setObject:[[subcomponents objectAtIndex:1] stringByReplacingPercentEscapesUsingEncoding:NSUTF8StringEncoding]
                               forKey:[[subcomponents objectAtIndex:0] stringByReplacingPercentEscapesUsingEncoding:NSUTF8StringEncoding]];
            }
        }

        title = [parameters objectForKey:@"utm_campaign"];
        promoteCode = [parameters objectForKey:@"pro_code"];
        im30_campion = [parameters objectForKey:@"im30_camp"];
    }


        //    NSString *value = [self valueForKey:@"utm_campaign" fromQueryItems:queryItems];

//
//    if (value == nil) {
//        value = @"";
//    }

    
    
}

//腾讯互联SDK接入
- (BOOL)application:(UIApplication *)application
            openURL:(NSURL *)url
//            options:(NSDictionary<NSString *,id> *)options
  sourceApplication:(NSString *)sourceApplication
         annotation:(id)annotation
{
    GBLK_GLOBAL_LOCK_UNIQUE;
    if (url == nil) {
        NSLOG(@"appLink url= nil ");
        return YES;
    }
    
    NSString *temp = [url absoluteString];
    NSLOG(@"appLink url=%@",temp);

//    [TrackingIO RYApplication:application openURL:url options:options];

    // google deep link start
    FIRDynamicLink *dynamicLink =
    [[FIRDynamicLinks dynamicLinks] dynamicLinkFromCustomSchemeURL:url];
    
    if(dynamicLink && [dynamicLink url] == nil)
    {
        NSLOG(@"Firebase Deeplink error");
        return YES;
    }
    
    
    if (dynamicLink) {
        NSURL* dlink = [dynamicLink url];
        NSString *dstring = [dlink absoluteString];
        NSLOG(@"deeplink url=%@",dstring);
        [self doDeeplinkParse:dlink];

        return YES;
    }
    // google deep link end
    //fb的deeplink
    if (![[Branch getInstance] handleDeepLink:url]) {
        // do other deep link routing for the Facebook SDK, Pinterest SDK, etc
        temp = [temp stringByReplacingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
        std::string tempLink = [temp cStringUsingEncoding:NSUTF8StringEncoding];
        [self doDeeplinkParse:url];
//        cocos2d::CCUserDefault::sharedUserDefault()->setStringForKey("iso_fbAPPLink", tempLink);
        // [NANTracking trackAppLaunch:url];
        [TencentOAuth HandleOpenURL:url];
        [WeiboSDK handleOpenURL:url delegate:self];
        return  [[FBSDKApplicationDelegate sharedInstance] application:application
                                                               openURL:url
                                                     sourceApplication:sourceApplication
                                                            annotation:annotation];
    }
    
    return YES;
}
- (BOOL)application:(UIApplication *)application
continueUserActivity:(NSUserActivity *)userActivity
 restorationHandler:(void (^)(NSArray *))restorationHandler {
        //如果有安装程序就会走这里
    BOOL handled = [[FIRDynamicLinks dynamicLinks]
                    handleUniversalLink:userActivity.webpageURL
                    completion:^(FIRDynamicLink * _Nullable dynamicLink,
                                 NSError * _Nullable error) {
                        if (dynamicLink) {
                            [self doDeeplinkParse:[dynamicLink url]];
                        }
                        
                    }];

    return handled;
}
//    // Reports app open from deeplink for iOS 10
//- (BOOL)application:(UIApplication *)application openURL:(NSURL *)url
//            options:(NSDictionary *) options
//{
//
//    [[AppsFlyerTracker sharedTracker] handleOpenUrl:url options:options];
//    return YES;
//}

- (void)didReceiveWeiboResponse:(WBBaseResponse *)response
{
    if ([response isKindOfClass:WBSendMessageToWeiboResponse.class])
    {
        //分享成功
        //todo
    }
    else if ([response isKindOfClass:WBAuthorizeResponse.class])
    {
        //登陆授权成功
        NSString * userID = [(WBAuthorizeResponse *)response userID];
        NSString * wbtoken = [(WBAuthorizeResponse *)response accessToken];



    }
    else if ([response isKindOfClass:WBPaymentResponse.class])
    {

    }
    else if([response isKindOfClass:WBSDKAppRecommendResponse.class])
    {

    }else if([response isKindOfClass:WBShareMessageToContactResponse.class])
    {

    }
}


- (NSDictionary *)parametersWithSeparator:(NSString *)separator delimiter:(NSString *)delimiter url:(NSString *)str{
    NSArray *parameterPairs =[str componentsSeparatedByString:delimiter];
    NSMutableDictionary *parameters = [NSMutableDictionary dictionaryWithCapacity:[parameterPairs count]];
    for (NSString *currentPair in parameterPairs) {
        NSRange range = [currentPair rangeOfString:separator];
        if(range.location == NSNotFound)
            continue;
        NSString *key = [currentPair substringToIndex:range.location];
        NSString *value =[currentPair substringFromIndex:range.location + 1];
        [parameters setObject:value forKey:key];
    }
    return parameters;
}

#if __IPHONE_OS_VERSION_MAX_ALLOWED >= __IPHONE_9_0
- (void)application:(UIApplication *)application performActionForShortcutItem:(UIApplicationShortcutItem *)shortcutItem completionHandler:(void (^)(BOOL))completionHandler{

    GBLK_GLOBAL_LOCK_UNIQUE;
    
    NSLOG(@"===%@",shortcutItem.type);
    

    
    completionHandler(true);
}
#endif

#pragma mark -
#pragma mark Memory management

- (void)applicationDidReceiveMemoryWarning:(UIApplication *)application {
    /*
     Free up as much memory as possible by purging cached data objects that can be recreated (or reloaded from disk) later.
     */
//    cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
//    cocos2d::CCDirector::sharedDirector()->purgeCachedData();
}


- (void)dealloc {
    [self unregisterElvaCloseNotifications];
    [super dealloc];
}

- (void)onConversionDataReceived:(NSDictionary*) installData {

}

- (void)onConversionDataRequestFailure:(NSError *) error {
    NSLOG(@"%@",error);
}

- (void)application:(UIApplication *)application didRegisterUserNotificationSettings:(UIUserNotificationSettings *)notificationSettings
{
}


@end

