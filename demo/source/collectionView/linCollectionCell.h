//
//  NemoFilterCell.h
//  Nemo
//
//  Created by ksyun on 17/4/20.
//  Copyright © 2017年 com.ksyun. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <KMCShortVideo/KMCMaterial.h>

@interface linCollectionCell : UICollectionViewCell

@property(nonatomic,strong)KMCMaterial * material;

//开始下载动画
-(void)startDownload;
//下载中动画
-(void)downloading:(float)process;
//完成后动画
-(void)finishDownload;
//下载失败后动画
-(void)downloadFail;
//选中后的遮罩
@property (nonatomic, strong) UIView * selectedMaskView;

@end
