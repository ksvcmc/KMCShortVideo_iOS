//
//  NemoFilterCell.m
//  Nemo
//
//  Created by ksyun on 17/4/20.
//  Copyright © 2017年 com.ksyun. All rights reserved.
//

#import "buttonCollectionCell.h"
#import "linImagePickerViewController.h"

@interface buttonCollectionCell(){
}

@end

@implementation buttonCollectionCell

- (id)initWithFrame:(CGRect)frame
{
    if (self = [super initWithFrame:frame]) {
        [self setupUI];
    }
    return self;
}

- (void)setupUI{
    
    self.addButton = [[UIButton alloc] init];
    [self.addButton setImage:[UIImage imageNamed:@"addvideo"] forState:UIControlStateNormal];
    self.addButton.contentHorizontalAlignment = UIControlContentHorizontalAlignmentLeft;
    [self.contentView addSubview:self.addButton];
    [self.addButton addTarget:self action:@selector(addAsset:) forControlEvents:(UIControlEventTouchUpInside)];

    [self.addButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.leading.trailing.bottom.equalTo(self.contentView);
    }];
}

- (void)addAsset:(UIButton *)btn{
    if(self.delegate){
        [self.delegate addAssetClicked:self];
    }
}


@end
