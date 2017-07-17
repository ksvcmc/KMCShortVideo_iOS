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
 *  \brief 音频转场,音频片段间切换的特效
 *  
 *  一般通过音频轨道(Audio Track)来设置和获取音频转场。目前默认音频转场是淡入淡出转场(fade)。
 * 
 */
@interface NvsAudioTransition : NvsFx

@property (readonly) NvsFxDescription *description;  //!< \if ENGLISH \else 音频转场特效描述 \endif

@end
