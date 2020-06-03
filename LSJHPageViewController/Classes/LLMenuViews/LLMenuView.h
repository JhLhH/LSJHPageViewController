//
//  LLMenuView.h
//  FMDB
//
//  Created by 李俊恒 on 2018/11/14.
//

#import "LLMenuItem.h"
#import "LLPageProgressView.h"
#import <UIKit/UIKit.h>

#define LLUNDEFINED_VALUE -1

@class LLMenuView;
// 标题栏的样式
typedef NS_ENUM(NSUInteger, LLMenuViewStyle) {
    LLMenuViewStyleDefault,     // 默认
    LLMenuViewStyleLine,        // 带下划线（若要选中字体大小不变，设置选中合肥选中大小一样即可）
    LLMenuViewStyleTriangle,    // 三角形(progressHeight 为三角形的高，progressWidths为底边长)
    LLMenuViewStyleFlood,       // 涌入效果（填充）
    LLMenuViewStyleFloodHollow, // 涌入效果（空心的）
    LLMenuViewStyleSegmented,   // 涌入带边框的，类似网易新闻选项卡
};

/**
 关于布局格式的样式
 */
typedef NS_ENUM(NSUInteger, LLMenuViewLayoutMode) {
    LLMenuViewLayoutModeScatter, // 默认的布局模式，item会均匀的分布在屏幕上，成分散状
    LLMenuViewLayoutModeLeft,    // Item紧靠屏幕左侧
    LLMenuViewLayoutModeRight,   // Item紧靠屏幕右侧
    LLMenuViewLayoutModeCenter,  // Item紧挨且居中分布
};
NS_ASSUME_NONNULL_BEGIN

@protocol LLMenuViewDelegate <NSObject>

@optional

/**
 选中某个Item

 @param menu 选中的menuView
 @param index 被选中的Index
 @return YES/NO
 */
- (BOOL)ll_menuView:(LLMenuView *)menu shouldSelectedIndex:(NSInteger)index;

/**
 被选中的index

 @param menu menuView
 @param index 被选中的index
 @param currentIndex 当前的index
 */
- (void)ll_menuView:(LLMenuView *)menu
    didSelectedIndex:(NSInteger)index
        currentINdex:(NSInteger)currentIndex;

/**
 设置menuView宽度

 @param menu menuView
 @param index 选中的index
 @return 返回视图宽度
 */
- (CGFloat)ll_menuView:(LLMenuView *)menu widthForItemAtIndex:(NSInteger)index;

/**
 返回间隔距离

 @param menu menuView
 @param index index
 @return margin
 */
- (CGFloat)ll_menuView:(LLMenuView *)menu itemMarginAtIndex:(NSInteger)index;

/**
 标题的文字title

 @param menu menuView
 @param state 选中未选中
 @param index index
 @return 字体大小
 */
- (CGFloat)ll_menuView:(LLMenuView *)menu
      titleSizeForState:(LLMenuItemState)state
                atIndex:(NSInteger)index;

/**
 返回颜色

 @param menu menuView
 @param state 选中未选中
 @param index index
 @return 返回颜色
 */
- (UIColor *)ll_menuView:(LLMenuView *)menu
       titleColorForState:(LLMenuItemState)state
                  atIndex:(NSInteger)index;

/**
 获取当前的index下的item

 @param menu menuView
 @param menItem item
 @param index index
 */
- (void)ll_menuView:(LLMenuView *)menu
  didLayoutItemFrame:(LLMenuItem *)menItem
             atIndex:(NSInteger)index;
@end

@protocol LLMenuViewDataSource <NSObject>

@required

/**
 获取标题数量

 @param menu menuView
 @return 返回一个数值来确定标题个数
 */
- (NSInteger)ll_numberOfTitlesInMenuView:(LLMenuView *)menu;

/**
 每一个item的标题文字

 @param menu menuView
 @param index index
 @return 返回文字
 */
- (NSString *)ll_menuView:(LLMenuView *)menu titleAtIndex:(NSInteger)index;
@optional
/**
 *  角标 (例如消息提醒的小红点) 的数据源方法，在 WMPageController 中实现这个方法来为 menuView
 提供一个 badgeView
 需要在返回的时候同时设置角标的 frame 属性，该 frame 为相对于 menuItem 的位置
 *
 *  @param index 角标的序号
 *
 *  @return 返回一个设置好 frame 的角标视图
 */
- (UIView *)ll_menuView:(LLMenuView *)menu badgeViewAtIndex:(NSInteger)index;

/**
 用于定制LLMenuItem,可以传出initialMenuItem
 进行修改定制，也可以返回自己创建的子类，需要注意的士m，此时的item的frame是不确定的，所以请不要根据此时的frame做计算。如果需要根据frame修改，请使用代理

 @param meun 当前的menuView，frame不确定哦
 @param initialMenuItem 初始化完成的menuItem
 @param index item所属的位置
 */
- (LLMenuItem *)ll_menuView:(LLMenuView *)meun
              initialMenuItem:(LLMenuItem *)initialMenuItem
                      atIndex:(NSInteger)index;
@end

@interface LLMenuView : UIView <LLMenuItemDelegate>
@property (nonatomic, strong) NSArray * progressWidths;
@property (nonatomic, weak) LLPageProgressView * progressView;
@property (nonatomic, assign) CGFloat progressHeight;
@property (nonatomic, assign) LLMenuViewStyle style;
@property (nonatomic, assign) LLMenuViewLayoutMode layoutMode;
@property (nonatomic, assign) CGFloat contentMargin;
@property (nonatomic, strong) UIColor * lineColor;
@property (nonatomic, assign) CGFloat progressViewBottomSpace;

@property (nonatomic, weak) id<LLMenuViewDelegate> delegate;
@property (nonatomic, weak) id<LLMenuViewDataSource> dataSource;

@property (nonatomic, weak) UIView * leftView;
@property (nonatomic, weak) UIView * rightView;
@property (nonatomic, copy) NSString * fontName;
@property (nonatomic, weak) UIScrollView * scrollView;

/**
 进度条的速度因数，默认为15，越小越快，大于0
 */
@property (nonatomic, assign) CGFloat speedFactor;
@property (nonatomic, assign) CGFloat progressViewCornerRadius;
@property (nonatomic, assign) BOOL progressViewIsNaughty;
@property (nonatomic, assign) BOOL showOnNavigationBar;

- (void)ll_slidMenuAtProgress:(CGFloat)progress;
- (void)ll_selectItemAtIndex:(NSInteger)index;
- (void)ll_resetFrames;
- (void)ll_reload;
- (void)ll_updateTitle:(NSString *)title atIndex:(NSInteger)index anWidth:(BOOL)update;
- (void)ll_updateAttributeTitle:(NSAttributedString *)title
                         atIndex:(NSInteger)index
                        andWidth:(BOOL)update;
- (LLMenuItem *)ll_itemAtIndex:(NSInteger)index;

/**
 立即刷新menuView的contentOffset，使得title居中
 */
- (void)ll_refreshContentOffset;
- (void)ll_deselectedItemsIfNeeded;

/**
 更新交角标视图，如果要移除，在ll_menuView:bageViewAtIndex:中返回nil即可

 @param index index
 */
- (void)ll_updateBadgeViewAtIndex:(NSInteger)index;
@end

NS_ASSUME_NONNULL_END
