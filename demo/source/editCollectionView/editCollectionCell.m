//
//  NemoFilterCell.m
//  Nemo
//
//  Created by ksyun on 17/4/20.
//  Copyright © 2017年 com.ksyun. All rights reserved.
//

#import "editCollectionCell.h"

@interface editCollectionCell(){
}
@property (nonatomic, strong) UIButton * closeBtn;
@property (nonatomic, strong) UIButton * editBtn;
@property (nonatomic, strong) UIImageView * imageView;
@property (nonatomic, strong) PHCachingImageManager *imageManager;

@end

@implementation editCollectionCell

- (id)initWithFrame:(CGRect)frame
{
    if (self = [super initWithFrame:frame]) {
        [self setupUI];
    }
    return self;
}

- (void)setupUI{
    //缩略图
    self.imageView = [[UIImageView alloc] init];
    self.imageView.contentMode =  UIViewContentModeCenter;
    self.imageView.clipsToBounds = YES;
    //关闭按钮
    self.closeBtn = [[UIButton alloc]init];
    [self.closeBtn setImage:[UIImage imageNamed:@"close"] forState:UIControlStateNormal];
    [self.closeBtn addTarget:self action:@selector(close:) forControlEvents:(UIControlEventTouchUpInside)];
    //编辑按钮
    self.editBtn = [[UIButton alloc] init];

    
    [self.contentView addSubview:self.imageView];
    [self.contentView addSubview:self.closeBtn];
    [self.imageView addSubview:self.editBtn];

    
    [self.imageView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.equalTo(self.contentView).offset(15);
        make.bottom.leading.equalTo(self.contentView);
        make.trailing.equalTo(self.contentView).offset(-15);
    }];
    
    [self.closeBtn mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.equalTo(self.contentView);
        make.trailing.equalTo(self.contentView);
        make.height.mas_equalTo(30);
        make.width.mas_equalTo(30);
    }];
    
    [self.editBtn mas_makeConstraints:^(MASConstraintMaker *make) {
        make.centerX.equalTo(self.imageView);
        make.centerY.equalTo(self.imageView);
        make.height.mas_equalTo(43);
        make.width.mas_equalTo(43);
    }];
}

-(void)setAsset:(PHAsset *)asset{
    //获取缩略图
    CGSize itemSize =  CGSizeMake(217, 122);
    CGSize targetSize = CGSizeMake(itemSize.width *[[UIScreen mainScreen] scale], itemSize.height*[[UIScreen mainScreen] scale]);
    [self.imageManager requestImageForAsset:asset
                                 targetSize:targetSize
                                contentMode:PHImageContentModeAspectFit
                                    options:nil
                              resultHandler:^(UIImage *result, NSDictionary *info) {
                                      self.imageView.image = result;
                                  }];
    //根据视频，图片信息设置按钮图样
    if(asset.mediaType == PHAssetMediaTypeImage){
        [self.editBtn setImage:[UIImage imageNamed:@"ImageEdit"] forState:UIControlStateNormal];
    }else if(asset.mediaType == PHAssetMediaTypeVideo){
        [self.editBtn setImage:[UIImage imageNamed:@"videoEdit"] forState:UIControlStateNormal];
    }

}

#pragma mark - 懒加载
- (PHCachingImageManager *)imageManager
{
    if (_imageManager == nil) {
        _imageManager = [PHCachingImageManager new];
    }
    
    return _imageManager;
}

#pragma mark - action
- (void)close:(UIButton *)btn{
    if(self.delegate)
        [self.delegate deleteCell:self];
}
@end
