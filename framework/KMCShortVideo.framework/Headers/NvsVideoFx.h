//================================================================================
//
// (c) Copyright China Digital Video (Beijing) Limited, 2016. All rights reserved.
//
// This code and information is provided "as is" without warranty of any kind,
// either expressed or implied, including but not limited to the implied
// warranties of merchantability and/or fitness for a particular purpose.
//
//--------------------------------------------------------------------------------
//   Birth Date:    Dec 29. 2016
//   Author:        NewAuto video team
//================================================================================
#pragma once

#import "NvsFx.h"

@class NvsFxDescription;

/*!
    \brief 视频特效

    视频特效是显示在视频片段上的特效，能够改变视频图像整体或者局部的颜色、亮度、透明度等，使视频显示出特殊的效果。在视频片段(Video Clip)上，可以添加、移除、获取多个视频特效。
 */
@interface NvsVideoFx : NvsFx

@property (readonly) unsigned int index;  //!< \if ENGLISH \else 视频特效索引 \endif

@property (readonly) NvsFxDescription *description; //!< \if ENGLISH \else 视频特效描述 \endif

@end
