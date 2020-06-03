//
//  UIViewController+LLPageController.h
//  FMDB
//
//  Created by 李俊恒 on 2018/11/14.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN
@class LLPageController;

@interface UIViewController (LLPageController)

/**
 获取控制器所在的LLPageController
 */
@property (nonatomic, nullable, strong, readonly) LLPageController * ll_PageController;
@end

NS_ASSUME_NONNULL_END
