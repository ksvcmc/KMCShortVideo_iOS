//
//  QBVideoIndicatorView.m
//  QBImagePicker
//
//  Created by Katsuma Tanaka on 2015/04/04.
//  Copyright (c) 2015 Katsuma Tanaka. All rights reserved.
//

#import "videoIndicatorView.h"

@implementation videoIndicatorView

- (instancetype)init
{
    self = [super init];
    
    //[self addGradientLayer];
    
    [self setupUI];
    
    return self;
}

-(void)setupUI{
    self.videoIcon = [[videoIconView alloc] init];
    self.timeLabel = [[UILabel alloc] init];
    self.timeLabel.textColor = [UIColor colorWithHexString:@"#ffffff"];
    self.timeLabel.font = [UIFont systemFontOfSize:12.0f];
    [self addSubview:self.timeLabel];
    [self addSubview:self.videoIcon];

    
    [self.videoIcon mas_makeConstraints:^(MASConstraintMaker *make) {
        make.trailing.equalTo(self.timeLabel.mas_leading).offset(-5);
        make.centerY.equalTo(self.timeLabel.mas_centerY);
        make.width.mas_equalTo(14);
        make.height.mas_equalTo(8);
    }];
    
    [self.timeLabel mas_makeConstraints:^(MASConstraintMaker *make) {
        make.trailing.equalTo(self).offset(-10);
        make.bottom.equalTo(self).offset(-10);
    }];

}

- (void)addGradientLayer
{
    CAGradientLayer *gradientLayer = [CAGradientLayer layer];
    gradientLayer.frame = self.bounds;
    gradientLayer.colors = @[
                             (__bridge id)[[UIColor clearColor] CGColor],
                             (__bridge id)[[UIColor blackColor] CGColor]
                             ];
    
    [self.layer insertSublayer:gradientLayer atIndex:0];
}

@end
