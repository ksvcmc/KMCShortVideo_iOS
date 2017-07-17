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
 *  \brief 音频特效
 *  
 *  音频特效是叠加显示在音频片段上的特效，可以改变音频片段的声调和速率。获取音频片段(Audio Clip)对象实例后，根据需要来添加或者移除多个音频特效。
 * 
 */
@interface NvsAudioFx : NvsFx

@property (readonly) unsigned int index;              //!< \if ENGLISH brief member variable description \else 音频特效索引 \endif

@property (readonly) NvsFxDescription *description;   //!< \if ENGLISH brief member variable description \else 音频特效描述 \endif

@end
