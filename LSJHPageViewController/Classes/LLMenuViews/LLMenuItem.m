//
//  LLMenuItem.m
//  Masonry
//
//  Created by 李俊恒 on 2018/11/10.
//

#import "LLMenuItem.h"

@implementation LLMenuItem {
    CGFloat _selectedRed, _selectedGreen, _selectedBlue, _selectedAlpha;
    CGFloat _normalRed, _normalGreen, _normalBlue, _normalAlpha;
    int _sign;
    CGFloat _gap;
    CGFloat _step;
    __weak CADisplayLink * _link;
}
#pragma mark ======= Public Methods
- (instancetype)initWithFrame:(CGRect)frame
{
    if (self = [super initWithFrame:frame]) {
        self.normalColor   = [UIColor blackColor];
        self.selectedColor = [UIColor blackColor];
        self.normalSize    = 15;
        self.selectedSize  = 18;
        self.numberOfLines = 0;
        [self setupGestureRecognizer];
    }
    return self;
}
#pragma mark----------- setter getter
- (CGFloat)speedFactor
{
    if (_speedFactor <= 0) {
        _speedFactor = 15.0;
    }
    return _speedFactor;
}
- (void)setSelectedColor:(UIColor *)selectedColor
{
    _selectedColor = selectedColor;
    [selectedColor getRed:&_selectedRed
                    green:&_selectedGreen
                     blue:&_selectedBlue
                    alpha:&_selectedAlpha];
}

- (void)setNormalColor:(UIColor *)normalColor
{
    _normalColor = normalColor;
    [normalColor getRed:&_normalRed green:&_normalGreen blue:&_normalBlue alpha:&_normalAlpha];
}
// 设置rate,并刷新标题状态
- (void)setRate:(CGFloat)rate
{
    if (rate < 0.0 || rate > 1.0) {
        return;
    }
    _rate             = rate;
    CGFloat r         = _normalRed + (_selectedRed - _normalRed) * rate;
    CGFloat g         = _normalGreen + (_selectedGreen - _normalGreen) * rate;
    CGFloat b         = _normalBlue + (_selectedBlue - _normalBlue) * rate;
    CGFloat a         = _normalAlpha + (_selectedAlpha - _normalAlpha) * rate;
    self.textColor    = [UIColor colorWithRed:r green:g blue:b alpha:a];
    CGFloat minScale  = self.normalSize / self.selectedSize;
    CGFloat trueScale = minScale + (1 - minScale) * rate;
    self.transform    = CGAffineTransformMakeScale(trueScale, trueScale);
}
// 添加点击手势
- (void)setupGestureRecognizer
{
    UITapGestureRecognizer * tap =
    [[UITapGestureRecognizer alloc] initWithTarget:self
                                            action:@selector(touchUpInside:)];
    [self addGestureRecognizer:tap];
}

- (void)ll_setSelected:(BOOL)selected withAnimation:(BOOL)animation
{
    _selected = selected;
    if (!animation) {
        self.rate = selected ? 1.0 : 0.0;
        return;
    }
    _sign = (selected == YES) ? 1 : -1;                                // 记录左右滑动的标志
    _gap  = (selected == YES) ? (1.0 - self.rate) : (self.rate - 0.0); // 记录距离
    _step = _gap / self.speedFactor;
    if (_link) {
        [_link invalidate];
    }
    CADisplayLink * link =
    [CADisplayLink displayLinkWithTarget:self
                                selector:@selector(rateChange)];
    [link addToRunLoop:[NSRunLoop mainRunLoop] forMode:NSRunLoopCommonModes];
    _link = link;
}
- (void)rateChange
{
    if (_gap > 0.000001) {
        _gap -= _step;
        if (_gap < 0.0) {
            self.rate = (int)(self.rate + _sign * _step + 0.5);
            return;
        }
        self.rate += _sign * _step;
    } else {
        self.rate = (int)(self.rate + 0.5);
        [_link invalidate];
        _link = nil;
    }
}
#pragma mark ======= Event
- (void)touchUpInside:(id)sender
{
    if ([self.delegate respondsToSelector:@selector(ll_didPressedMenuItem:)]) {
        [self.delegate ll_didPressedMenuItem:self];
    }
}
@end
