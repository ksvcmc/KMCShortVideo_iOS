//
//  singleVideoEditViewController.h
//  KMCShortVideoDemo
//
//  Created by ksyun on 2017/7/1.
//  Copyright © 2017年 ksyun. All rights reserved.
//

#import <UIKit/UIKit.h>

typedef struct {
    CGFloat duration;
    CGFloat bright;
    CGFloat Saturation;
    CGFloat Contrast;
    CGFloat rotate;
}imageConfig;

@protocol singleImageEditViewControllerDelegate <NSObject>

- (void)doneWithImageClipIndex:(int)index
                        Config:(imageConfig)config;

@end

@interface singleImageEditViewController : UIViewController

//图片
@property(strong,nonatomic) NSArray * assets;
//图片位置
@property(nonatomic,assign) int assetIndex;

@property(nonatomic,weak) id<singleImageEditViewControllerDelegate> delegate;


@end
