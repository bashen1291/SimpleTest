//
//  IFAppController.h
//  IF
//
//  Created by 吴 凌江 on 13-8-28.
//  Copyright __MyCompanyName__ 2013年. All rights reserved.
//

#import "RootViewController.h"
#import "string"
#include "cocos2d.h"
#include "cocos-ext.h"

//#import "PreviewViewController.h"

//#include "../Classes/Ext/3dtouch/OCCppHelper.h"

extern std::string g_theBranchLinkData;
static RootViewController* theRootViewController = nil;

@implementation RootViewController

@synthesize completionDelegate;

+(RootViewController*)shared {
    return theRootViewController;
}

+ (void)afterGetBranchData:(NSDictionary *)data {
    //  {"+is_first_session":0,"+clicked_branch_link":0}
    if(data == nil || [data count] == 2) {
        return;
    }
    g_theBranchLinkData.clear();
    NSMutableString* strJson = [[NSMutableString alloc] init];
    [strJson appendString:@"{"];
    NSArray* keyList = [data allKeys];
    for(int i = [keyList count]; i > 0; i--) {
        id key = [keyList objectAtIndex:(i - 1)];
        id value = [data objectForKey: key];
        NSLog (@"Key: %@ for value: %@", key, value);
        if ( [value isKindOfClass:[NSNumber class]] ) {
            if(i > 1) {
                [strJson appendFormat:@"\"%@\":%d,", key, [value integerValue]];
            } else {
                [strJson appendFormat:@"\"%@\":%d", key, [value integerValue]];
            }
        } else {
            if(i > 1) {
                [strJson appendFormat:@"\"%@\":\"%@\",", key, value];
            } else {
                [strJson appendFormat:@"\"%@\":\"%@\"", key, value];
            }
        }
    }
    [strJson appendString:@"}"];

}

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    if ((self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil])) {
        // Custom initialization
        theRootViewController = self;
    }
    return self;
}

- (void)configureControlWithData:(NSDictionary *)data {
    [RootViewController afterGetBranchData:data];
}

// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    [[Branch getInstance] registerDeepLinkController:self forKey:@"ljlastwars"];
}

-(void)register3DTouch{
    if ([[[UIDevice currentDevice] systemVersion] floatValue] >= 9.0)
    {

    }
}

- (nullable UIViewController *)previewingContext:(id <UIViewControllerPreviewing>)previewingContext viewControllerForLocation:(CGPoint)point
{

    
//    if (GlobalData::shared()->peekPageType == peekType_playerInfo)
//    {
//        GlobalData::shared()->peekPageType = peekType_peek;
//        
//        previewingContext.sourceRect = CGRectMake(0, 0, previewingContext.sourceView.frame.size.width, previewingContext.sourceView.frame.size.height);
//        
//        UIViewController *childVC = [[PreviewViewController alloc] init] ;
//        childVC.preferredContentSize = CGSizeMake(0.0f,450.f);
//        childVC.view.backgroundColor = [UIColor orangeColor];
//        
//        OCCppHelper::share()->notificationIOSUpdatePlayerInfo();
//        
//        return childVC;
//    }
    
    
    
    return nil;
}


- (void)previewingContext:(id <UIViewControllerPreviewing>)previewingContext commitViewController:(UIViewController *)viewControllerToCommit
{
    
    //    [self presentViewController:viewControllerToCommit animated:YES completion:nil];
    
    [self showViewController:viewControllerToCommit sender:self];
}

// Override to allow orientations other than the default portrait orientation.
// This method is deprecated on ios6
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    return UIInterfaceOrientationIsLandscape( interfaceOrientation );
}

// For ios6, use supportedInterfaceOrientations & shouldAutorotate instead
- (NSUInteger) supportedInterfaceOrientations{
#ifdef __IPHONE_6_0
    return UIInterfaceOrientationMaskPortrait;
#endif
}

- (BOOL) shouldAutorotate {
    return YES;
}

//fix not hide status on ios7
- (BOOL)prefersStatusBarHidden
{
    return YES;
}

- (void)didReceiveMemoryWarning {
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}

- (void)viewDidUnload {
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
    [self.completionDelegate deepLinkingControllerCompleted];
}

//- (void)viewWillAppear:(BOOL)animated
//{
//    [self.view layoutIfNeeded];
//    if(IS_IPHONEX())
//        [self.view setFrame:kTopScreenFrame];
//    [super viewWillAppear:animated];
//}
//
//- (void)viewDidAppear:(BOOL)animated
//{
//    if(IS_IPHONEX())
//        [self.view setFrame:kTopScreenFrame];
//    [super viewDidAppear:animated];
//}

- (void)viewWillDisappear:(BOOL)animated
{

    [super viewWillDisappear:animated];
}

//add by liudi for iphoneX fix
- (void)viewWillLayoutSubviews
{
    //reset key window color and size of cegl

    [super viewWillLayoutSubviews];
}

@end
