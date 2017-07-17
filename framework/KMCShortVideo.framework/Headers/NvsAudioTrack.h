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

#import "NvsTrack.h"

@class NvsAudioClip;
@class NvsAudioTransition;

/*!
 *  \brief 音频轨道，音频片段的集合
 *
 *  音频轨道是容纳音频片段的实体。每条音频轨道可以添加或者移除多个音频片段。一个音频片段播放到另一个音频片段时，需要进行音频转场设置，以便过渡衔接。
 * 
 *  注：对于音频轨道的一系列接口及所其属参数含义,请参照视频轨道[NvsVideoTrack] (@ref NvsVideoTrack)的对应接口来对照理解。
 */
@interface NvsAudioTrack : NvsTrack

/*!
 *  \brief 在轨道尾部追加片段
 *  \param filePath 片段路径。对于片段路径方式，请参见[addClip()] (@ref addClip:inPoint:)的参数filePath。
 *  \return 返回追加的音频片段对象
 *  \warning 此接口会引发流媒体引擎状态跳转到引擎停止状态，具体情况请参见[引擎变化专题] (\ref EngineChange.md)。
 *  \sa appendClip:trimIn:trimOut:
 *  \sa getClipWithIndex:
 *  \sa insertClip:clipIndex:
 */
- (NvsAudioClip *)appendClip:(NSString *)filePath;

/*!
 *  \brief 在轨道尾部追加片段
 *  \param filePath 片段路径。对于片段路径方式，请参见[addClip()] (@ref addClip:inPoint:)的参数filePath。
 *  \param trimIn 片段裁剪入点
 *  \param trimOut 片段裁剪出点
 *  \return 返回追加的音频片段对象
 *  \warning 此接口会引发流媒体引擎状态跳转到引擎停止状态，具体情况请参见[引擎变化专题] (\ref EngineChange.md)。
 *  \sa appendClip:
 *  \sa insertClip:trimIn:trimOut:clipIndex:
 *  \sa getClipWithIndex:
 */
- (NvsAudioClip *)appendClip:(NSString *)filePath trimIn:(int64_t)trimIn trimOut:(int64_t)trimOut;

/*!
 *  \brief 在轨道上指定片段索引处插入片段
 *  \param filePath 片段路径。对于片段路径方式，请参见[addClip()] (@ref addClip:inPoint:)的参数filePath。
 *  \param clipIndex 插入片段索引
 *  \return 返回插入的音频片段对象
 *  \warning 此接口会引发流媒体引擎状态跳转到引擎停止状态，具体情况请参见[引擎变化专题] (\ref EngineChange.md)。
 *  \sa appendClip:
 *  \sa getClipWithIndex:
 *  \sa insertClip:trimIn:trimOut:clipIndex:
 */
- (NvsAudioClip *)insertClip:(NSString *)filePath clipIndex:(unsigned int)clipIndex;

/*!
 *  \brief 在轨道上指定片段索引处插入片段
 *  \param filePath 片段路径。对于片段路径方式，请参见[addClip()] (@ref addClip:inPoint:)的参数filePath。
 *  \param trimIn 片段裁剪入点
 *  \param trimOut 片段裁剪出点
 *  \param clipIndex 插入片段索引
 *  \return 返回插入的音频片段对象
 *  \warning 此接口会引发流媒体引擎状态跳转到引擎停止状态，具体情况请参见[引擎变化专题] (\ref EngineChange.md)。
 *  \sa appendClip:trimIn:trimOut:
 *  \sa getClipWithIndex:
 *  \sa insertClip:clipIndex:
 */
- (NvsAudioClip *)insertClip:(NSString *)filePath trimIn:(int64_t)trimIn trimOut:(int64_t)trimOut clipIndex:(unsigned int)clipIndex;

/*!
     \brief 添加片段
     \param filePath 片段路径

     IOS中，对于导入的音视频片段的路径，有四种方式：

     a. 通过ALAssetsLibrary实例导入，片段路径格式如下："assets-library://asset/asset.mov?id=E0723C86-AA47-409C-B4E2-526D7C2AA9B5&ext=mov"；

     b. 通过IPod Library库的MPMediaQuery实例导入，片段路径格式如下："ipod-library://item/item.mp3?id=1217463725835578132"；

     c. 通过沙河路径路径导入，片段路径格式如下："/var/mobile/Containers/Data/Documents/tmp/video20170406101714.mp4"；

     d. IOS 8.0版以后，Photos框架替代ALAssetsLibrary库，通过PHAsset实例导入，片段路径如下："file:///var/mobile/Media/DCIM/100APPLE/IMG_0646.MP4"。
     \param inPoint 片段在时间线上的入点
     \return 返回添加的音频片段对象
     \warning 此接口会引发流媒体引擎状态跳转到引擎停止状态，具体情况请参见[引擎变化专题] (\ref EngineChange.md)。
     \sa appendClip:
     \sa insertClip:clipIndex:
     \sa addClip:inPoint:trimIn:trimOut:
 */
- (NvsAudioClip *)addClip:(NSString *)filePath inPoint:(int64_t)inPoint;

/*!
     \brief 添加指定长度的片段
     \param filePath 片段路径。对于片段路径方式，请参见[addClip()] (@ref addClip:inPoint:)的参数filePath。
     \param inPoint 片段在时间线上的入点
     \param trimIn 片段裁剪入点
     \param trimOut 片段裁剪出点
     \return 返回添加的音频片段对象
     \warning 此接口会引发流媒体引擎状态跳转到引擎停止状态，具体情况请参见[引擎变化专题] (\ref EngineChange.md)。
     \sa appendClip:trimIn:trimOut:
     \sa insertClip:trimIn:trimOut:clipIndex:
     \sa addClip:inPoint:
 */
- (NvsAudioClip *)addClip:(NSString *)filePath inPoint:(int64_t)inPoint trimIn:(int64_t)trimIn trimOut:(int64_t)trimOut;

/*!
 *  \brief 通过索引获取片段
 *  \param clipIndex 片段索引
 *  \return 返回获取的音频片段对象
 *  \sa getClipWithTimelinePosition:
 *  \sa appendClip:
 *  \sa insertClip:clipIndex:
 */
- (NvsAudioClip *)getClipWithIndex:(unsigned int)clipIndex;

/*!
     \brief 通过时间获取片段对象
     \param timelinePos 时间线上的位置(微秒)
     \return 返回获取的音频片段对象
     \sa getClipWithIndex:
 */
- (NvsAudioClip *)getClipWithTimelinePosition:(int64_t)timelinePos;

/*!
 *  \brief 设置内嵌式转场
 *  \param srcClipIndex 转场的源片段索引
 *  \param transitionName 音频转场名称。注意：如果设为空字符串，则删除原有转场
 *  \return 返回音频转场对象
 *  \warning 此接口会引发流媒体引擎状态跳转到引擎停止状态，具体情况请参见[引擎变化专题] (\ref EngineChange.md)。
 *  \sa getTransitionWithSourceClipIndex:
 */
- (NvsAudioTransition *)setBuiltinTransition:(unsigned int)srcClipIndex withName:(NSString *)transitionName;

/*!
 *  \brief 通过源片段索引获取转场
 *  \param srcClipIndex 源片段索引
 *  \return 返回获取的音频转场对象
 *  \sa setBuiltinTransition:withName:
 */
- (NvsAudioTransition *)getTransitionWithSourceClipIndex:(unsigned int)srcClipIndex;

@end
