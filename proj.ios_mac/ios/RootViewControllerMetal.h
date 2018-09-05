//
//  IFAppController.h
//  IF
//
//  Created by 吴 凌江 on 13-8-28.
//  Copyright __MyCompanyName__ 2013年. All rights reserved.
//
#ifdef METAL_ENABLE
#import <UIKit/UIKit.h>
#import <Branch/Branch.h>
#import <Metal/Metal.h>
#import <MetalKit/MetalKit.h>

@interface RootViewControllerMetal : UIViewController <BranchDeepLinkingController, MTKViewDelegate>

+ (void)afterGetBranchData:(NSDictionary *)data;
+(RootViewControllerMetal*)shared;

-(void)setMetalView:(MTKView*)metalView
             glView:(UIView*)glView;

@end
#endif