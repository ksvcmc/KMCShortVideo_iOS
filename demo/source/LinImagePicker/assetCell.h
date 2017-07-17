//
//  QBAssetCell.h
//  QBImagePicker
//
//  Created by Katsuma Tanaka on 2015/04/03.
//  Copyright (c) 2015 Katsuma Tanaka. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "videoIndicatorView.h"

@interface assetCell : UICollectionViewCell

//图像层
@property (strong, nonatomic) UIImageView *imageView;
//视频标示
@property (strong, nonatomic) videoIndicatorView *videoIndicatorView;
//遮盖层
@property (strong, nonatomic) UIView *overlayView;
//数字
@property (strong, nonatomic) UILabel* clickNumLabel;
//存储的asset
@property (strong, nonatomic) PHAsset* asset;

@end
