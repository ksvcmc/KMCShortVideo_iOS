//================================================================================
//
// (c) Copyright China Digital Video (Beijing) Limited, 2017. All rights reserved.
//
// This code and information is provided "as is" without warranty of any kind,
// either expressed or implied, including but not limited to the implied
// warranties of merchantability and/or fitness for a particular purpose.
//
//--------------------------------------------------------------------------------
//   Birth Date:    Feb 22. 2017
//   Author:        NewAuto video team
//================================================================================
#pragma once

#import <UIKit/UIView.h>

/*!
    \brief 缩略图序列

    缩略图序列，即视频按照某种程度缩放，来静态缩略显示的序列。视频编辑时，通过预览定位视频序列，可以设置序列的开始时间，时长，缩略图横纵比等。同时，依照缩略图在对应时段位置精确添加字幕和裁剪视频。
 */
@interface NvsThumbnailSequenceView : UIView

@property (nonatomic, retain) NSString *mediaFilePath; //!< \if ENGLISH \else 媒体文件路径 \endif
@property (nonatomic, assign) int64_t startTime;       //!< \if ENGLISH \else 序列开始时间 \endif
@property (nonatomic, assign) int64_t duration;        //!< \if ENGLISH \else 序列时长 \endif
@property (nonatomic, assign) float thumbnailAspectRatio; //!< \if ENGLISH \else 缩略图横纵比 \endif
@property (nonatomic, assign) BOOL stillImageHint;     //!< \if ENGLISH \else 是否是静态图片 \endif

- (instancetype)init;
- (instancetype)initWithFrame:(CGRect)frame;
- (instancetype)initWithCoder:(NSCoder *)aDecoder;

@end

