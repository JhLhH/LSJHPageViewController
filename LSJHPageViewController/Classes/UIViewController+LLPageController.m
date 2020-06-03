//
//  UIViewController+LLPageController.m
//  FMDB
//
//  Created by 李俊恒 on 2018/11/14.
//

#import "UIViewController+LLPageController.h"
#import "LLPageController.h"

@implementation UIViewController (LLPageController)
- (LLPageController *)ll_PageController
{
    UIViewController * parentViewController = self.parentViewController;
    while (parentViewController) {
        if ([parentViewController isKindOfClass:[LLPageController class]]) {
            return (LLPageController *)parentViewController;
        }
        parentViewController = parentViewController.parentViewController;
    }
    return nil;
}
@end
