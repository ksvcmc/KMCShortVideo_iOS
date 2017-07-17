//
//  assetViewController.h
//  KMCShortVideoDemo
//
//  Created by ksyun on 2017/6/22.
//  Copyright © 2017年 ksyun. All rights reserved.
//

#import "ViewController.h"
#import "assetCell.h"

@protocol assetViewControllerDelegate <NSObject>

- (void)itemSelected:(assetCell *)cell;

- (void)itemDeSelected:(assetCell *)cell;

@end

@interface assetViewController : UIViewController

@property (nonatomic, strong) PHFetchResult * _Nullable fetchResult;

@property(nonatomic,weak) id<assetViewControllerDelegate> delegate;
@end
