//
//  IFAppController.h
//  IF
//
//  Created by 吴 凌江 on 13-8-28.
//  Copyright __MyCompanyName__ 2013年. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Branch/Branch.h>

@interface RootViewController : UIViewController <BranchDeepLinkingController,UIViewControllerPreviewingDelegate> {

}

+ (void)afterGetBranchData:(NSDictionary *)data;
+(RootViewController*)shared;
-(void)register3DTouch;

@end
