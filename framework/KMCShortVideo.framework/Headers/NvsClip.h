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

#import "NvsObject.h"

/*!
 *  \brief 片段类型,有视频和音频两种类型
 */
typedef enum NvsClipType {
    NvsClipType_Video = 0,     //!< \if ENGLISH brief element description \else 视频片段 \endif
    NvsClipType_Audio,         //!< \if ENGLISH brief element description \else 音频片段 \endif
} NvsClipType;

/*!
 *  \brief 片段，音视频文件的具体描述
 *   
 *  片段是容纳音视频内容的实体，是对视频、音频文件的描述，分为音频片段(Audio Clip)和视频片段(Video Clip)。它定义了不同类型片段所拥有的共同属性和行为，
 *  即派生的音频片段和和视频片段可根据需要修改各自的裁剪出入点，左右声道，播放速度等。在SDK框架中，在轨道(Track)上可添加相应的音频片段和视频片段。
 * 
 */
@interface NvsClip : NvsObject

@property (readonly) int64_t trimIn;             //!< \if ENGLISH \else 片段裁剪入点。注意：所有关于片段及时间线的时间单位均为微秒 \endif

@property (readonly) int64_t trimOut;            //!< \if ENGLISH \else 片段裁剪出点 \endif

@property (readonly) int64_t inPoint;            //!< \if ENGLISH \else 片段在时间线上的入点 \endif

@property (readonly) int64_t outPoint;           //!< \if ENGLISH \else 片段在时间线上的出点 \endif

@property (readonly) NvsClipType type;           //!< \if ENGLISH \else 片段类型（视频、音频） \endif

@property (readonly) unsigned int index;         //!< \if ENGLISH \else 片段在轨道上的索引 \endif

@property (readonly) NSString *filePath;         //!< \if ENGLISH \else 片段文件路径 \endif

@property (readonly) unsigned int fxCount;       //!< \if ENGLISH \else 片段上的特效数量 \endif

/*!
 *  \brief 修改片段裁剪入点
 *  \param newTrimInPoint 新裁剪入点
 *  \param affectSibling 是否影响同轨道上其他片段(YES/NO)
 *  \return 返回实际可到达的裁剪入点。注意：实际可达到的裁剪入点范围在[0,trimOut - 1]
 *  \warning 此接口会引发流媒体引擎状态跳转到引擎停止状态，具体情况请参见[引擎变化专题] (\ref EngineChange.md)。
 *  \sa changeTrimOutPoint:affectSibling:
 */
- (int64_t)changeTrimInPoint:(int64_t)newTrimInPoint affectSibling:(BOOL)affectSibling;

/*!
 *  \brief 修改片段裁剪出点
 *  \param newTrimOutPoint 新裁剪出点
 *  \param affectSibling 是否影响同轨道上其他片段(YES/NO)
 *  \return 返回实际可到达的裁剪出点。注意：实际可达到的裁剪出点范围在[trimIn + 1,clipDuration],clipDuration为片段时长。
 *  \warning 此接口会引发流媒体引擎状态跳转到引擎停止状态，具体情况请参见[引擎变化专题] (\ref EngineChange.md)。
 *  \sa changeTrimInPoint:affectSibling:
 */
- (int64_t)changeTrimOutPoint:(int64_t)newTrimOutPoint affectSibling:(BOOL)affectSibling;

/*!
 *  \brief 获取片段的播放速度。
 *
 *  默认值为1，表示按正常速度播放;小于1的值表示慢放;大于1的值表示快放
 *  \return 返回当前片段的播放速度
 *  \sa changeSpeed:
 */
- (double)getSpeed;

/*!
 *  \brief 改变片段的播放速度
 *  \param newSpeed 新的播放速度
 *  \warning 此接口会引发流媒体引擎状态跳转到引擎停止状态，具体情况请参见[引擎变化专题] (\ref EngineChange.md)。
 *  \sa getSpeed
 */
- (void)changeSpeed:(double)newSpeed;

/*!
 *  \brief 设置声道（左声道和右声道）
 *  \param leftVolumeGain 要设置的左声道值
 *  \param rightVolumeGain 要设置的右声道值
 *  \sa getVolumeGain:rightVolumeGain:
 */
- (void)setVolumeGain:(float)leftVolumeGain rightVolumeGain:(float)rightVolumeGain;

/*!
 *  \brief 获取置声道值（左声道和右声道）
 *  \param leftVolumeGain 返回要获取的左声道值
 *  \param rightVolumeGain 返回要获取的右声道值
 *  \sa setVolumeGain:rightVolumeGain:
 */
- (void)getVolumeGain:(float *)leftVolumeGain rightVolumeGain:(float *)rightVolumeGain;

@end

