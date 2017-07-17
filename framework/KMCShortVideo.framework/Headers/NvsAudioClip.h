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

#import "NvsClip.h"

@class NvsAudioFx;

/*!
 *  \brief 音频片段，对音频文件的描述
 *   
 *  音频片段既可以修改其裁剪入点和出点，播放速度等，还可以添加、插入、移除以及获取多个音频特效(Audio Fx)。
 */
@interface NvsAudioClip: NvsClip

/*!
 *  \brief 在片段尾部追加特效
 *  \param fxName 特效名称。获取特效名称，请参照[getAllBuiltinAudioFxNames()](@ref NvsStreamingContext::getAllBuiltinAudioFxNames)或[内建特效名称列表] (\ref FxNameList.md)
 *  \return 返回追加的音频特效对象
 *  \warning 此接口会引发流媒体引擎状态跳转到引擎停止状态，具体情况请参见[引擎变化专题] (\ref EngineChange.md)。
 *  \sa insertFx:fxIndex:
 *  \sa removeFx:
 *  \sa getFxWithIndex:
 */
- (NvsAudioFx *)appendFx:(NSString *)fxName;

/*!
 *  \brief 在片段上指定特效索引处插入特效
 *  \param fxName 特效名称。获取特效名称，请参照[getAllBuiltinAudioFxNames()](@ref NvsStreamingContext::getAllBuiltinAudioFxNames)或[内建特效名称列表] (\ref FxNameList.md)
 *  \param fxIndex 插入特效索引
 *  \return 返回插入的音频特效对象
 *  \warning 此接口会引发流媒体引擎状态跳转到引擎停止状态，具体情况请参见[引擎变化专题] (\ref EngineChange.md)。
 *  \sa appendFx:
 *  \sa removeFx:
 *  \sa getFxWithIndex:
 */
- (NvsAudioFx *)insertFx:(NSString *)fxName fxIndex:(unsigned int)fxIndex;

/*!
 *  \brief 移除指定索引的特效
 *  \param fxIndex 特效索引
 *  \return 返回BOOL值。值为YES则移除成功，NO则移除失败。
 *  \warning 此接口会引发流媒体引擎状态跳转到引擎停止状态，具体情况请参见[引擎变化专题] (\ref EngineChange.md)。
 *  \sa appendFx:
 *  \sa insertFx:fxIndex:
 *  \sa getFxWithIndex:
 */
- (BOOL)removeFx:(unsigned int)fxIndex;

/*!
 *  \brief 通过索引获取特效
 *  \param fxIndex 特效索引
 *  \return 返回获取的音频特效对象
 *  \sa appendFx:
 *  \sa insertFx:fxIndex:
 *  \sa removeFx:
 */
- (NvsAudioFx *)getFxWithIndex:(unsigned int)fxIndex;

@end
