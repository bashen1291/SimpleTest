//
//  IFAppController.h
//  IF
//
//  Created by 吴 凌江 on 13-8-28.
//  Copyright __MyCompanyName__ 2013年. All rights reserved.
//

#import "AppsFlyerTracker.h"
#import "WeiboSDK.h"
#ifdef METAL_ENABLE
@class RootViewControllerMetal;
#else
@class RootViewController;
#endif

@interface AppController : NSObject <UIAccelerometerDelegate, UIAlertViewDelegate, UITextFieldDelegate,UIApplicationDelegate,AppsFlyerTrackerDelegate,WeiboSDKDelegate> {
    UIWindow *window;
#ifdef METAL_ENABLE
    RootViewControllerMetal *viewController;
#else
    RootViewController *viewController;
#endif
}

@property (nonatomic, retain) UIWindow *window;

#ifdef METAL_ENABLE
@property (nonatomic, retain) RootViewControllerMetal *viewController;
#else
@property (nonatomic, retain) RootViewController *viewController;
#endif

@end

