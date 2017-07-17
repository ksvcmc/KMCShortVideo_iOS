//
//  QBAssetCell.m
//  QBImagePicker
//
//  Created by Katsuma Tanaka on 2015/04/03.
//  Copyright (c) 2015 Katsuma Tanaka. All rights reserved.
//

#import "assetCell.h"

@interface assetCell ()

@end

@implementation assetCell


- (id)initWithFrame:(CGRect)frame
{
    if (self = [super initWithFrame:frame]) {
        //设置imageView
        [self setupUI];
        self.contentView.backgroundColor = [UIColor blackColor];

    }
    return self;
}

-(void)setupUI{
    self.imageView = [[UIImageView alloc] init];
    self.imageView.contentMode = UIViewContentModeScaleAspectFill;
    self.imageView.clipsToBounds = YES;
    self.videoIndicatorView = [[videoIndicatorView alloc] init];
    self.overlayView = [[UIView alloc] init];
    self.overlayView.hidden = YES;
    self.overlayView.backgroundColor = [UIColor colorWithHexString:@"#9012ef"];
    self.overlayView.alpha = 0.4f;
    
    self.clickNumLabel = [[UILabel alloc] init];
    self.clickNumLabel.font = [UIFont systemFontOfSize:48];
    self.clickNumLabel.textColor = [UIColor colorWithHexString:@"#ffffff"];
    self.clickNumLabel.textAlignment = NSTextAlignmentCenter;
    
    [self.contentView addSubview:self.imageView];
    [self.contentView addSubview:self.videoIndicatorView];
    [self.contentView addSubview:self.overlayView];
    [self.contentView addSubview:self.clickNumLabel];

    
    [self.imageView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.bottom.leading.trailing.equalTo(self.contentView);
    }];
    
    [self.videoIndicatorView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.bottom.leading.trailing.equalTo(self.contentView);
        make.height.mas_equalTo(30);
    }];
    
    [self.overlayView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.bottom.leading.trailing.equalTo(self.contentView);
    }];
    
    [self.clickNumLabel mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.bottom.leading.trailing.equalTo(self.contentView);
    }];
}

- (void)setSelected:(BOOL)selected
{
    [super setSelected:selected];
    
    // Show/hide overlay view
    self.overlayView.hidden = !selected;
}

@end
