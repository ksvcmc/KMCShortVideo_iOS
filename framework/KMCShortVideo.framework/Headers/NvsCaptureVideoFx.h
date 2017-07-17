//================================================================================
//
// (c) Copyright China Digital Video (Beijing) Limited, 2017. All rights reserved.
//
// This code and information is provided "as is" without warranty of any kind,
// either expressed or implied, including but not limited to the implied
// warranties of merchantability and/or fitness for a particular purpose.
//
//--------------------------------------------------------------------------------
//   Birth Date:    Jan 18. 2017
//   Author:        NewAuto video team
//================================================================================

#pragma once

#import "NvsFx.h"

/*!
 *  \brief 采集视频特效

 *  采集视频特效是一种应用在视频采集时的特效。获取流媒体上下文(Streaming Context)实例后，可按内建方式，包裹方式，美颜方式来添加或移除多个采集视频特效。
 * 
 */
@interface NvsCaptureVideoFx : NvsFx

@property (readonly) unsigned int index;   //!< \if ENGLISH brief member variable description \else 视频特效索引 \endif

@end
