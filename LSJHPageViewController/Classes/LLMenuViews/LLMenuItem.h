//
//  LLMenuItem.h
//  Masonry
//
//  Created by 李俊恒 on 2018/11/10.
//

#import <UIKit/UIKit.h>
@class LLMenuItem;
typedef NS_ENUM(NSUInteger, LLMenuItemState) {
    LLMenuItemStateSelected,
    LLMenuItemStateNormal,
};
NS_ASSUME_NONNULL_BEGIN
@protocol LLMenuItemDelegate <NSObject>

@optional

/**
 点击Item

 @param menuItem 返回当前被点击的menuItem;
 */
- (void)ll_didPressedMenuItem:(LLMenuItem *)menuItem;

@end

@interface LLMenuItem : UILabel
@property (nonatomic, assign) CGFloat rate;          // 设置rate,并且h刷新标题状态（0~1）
@property (nonatomic, assign) CGFloat normalSize;    // Normal状态的字体大小，默认大小为15
@property (nonatomic, assign) CGFloat selectedSize;  // Selected状态的字体大小，默认大小为18
@property (nonatomic, strong) UIColor * normalColor; // Normal状态的字体颜色，默认为黑色 (可动画)
@property (nonatomic, strong)
UIColor * selectedColor;                           // Selected状态的字体颜色，默认为红色 (可动画)
@property (nonatomic, assign) CGFloat speedFactor; // 进度条的速度因数，默认 15,越小越快 必须大于0
@property (nonatomic, weak, nullable) id<LLMenuItemDelegate> delegate;
@property (nonatomic, assign, readonly) BOOL selected;

/**
 当前的item是否需要选中,以及显示动画效果

 @param selected 是否被选中
 @param animation 是否有动画效果
 */
- (void)ll_setSelected:(BOOL)selected withAnimation:(BOOL)animation;
@end

NS_ASSUME_NONNULL_END
