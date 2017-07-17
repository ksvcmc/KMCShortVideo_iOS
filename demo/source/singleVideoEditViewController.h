//
//  singleVideoEditViewController.h
//  KMCShortVideoDemo
//
//  Created by ksyun on 2017/7/1.
//  Copyright © 2017年 ksyun. All rights reserved.
//

#import <UIKit/UIKit.h>

typedef struct {
    CGFloat startTime;
    CGFloat endTime;
    int     speed;
    CGFloat bright;
    CGFloat Saturation;
    CGFloat Contrast;
    CGFloat rotate;
    CGFloat scale;
}config;

@protocol singleVideoEditViewControllerDelegate <NSObject>

- (void)doneWithClipIndex:(int)index
                   Config:(config)config;

@end

@interface singleVideoEditViewController : UIViewController

//视频列表
@property(strong,nonatomic) NSArray * assets;
//视频位置
@property(nonatomic,assign) int assetIndex;

@property(nonatomic,weak) id<singleVideoEditViewControllerDelegate> delegate;


@end
