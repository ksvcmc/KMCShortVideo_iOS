//================================================================================
//
// (c) Copyright China Digital Video (Beijing) Limited, 2017. All rights reserved.
//
// This code and information is provided "as is" without warranty of any kind,
// either expressed or implied, including but not limited to the implied
// warranties of merchantability and/or fitness for a particular purpose.
//
//--------------------------------------------------------------------------------
//   Birth Date:    Jan 3. 2017
//   Author:        NewAuto video team
//================================================================================

#pragma once

#import "NvsCommonDef.h"
#import <Foundation/NSObject.h>

/*!
 *  \brief 音视频文件信息
 * 
 *  显示音视频文件的信息，包括音视频文件的时长，数据速率，像素横纵比，音视频流数目等。
 * 
 *  音视频文件信息
 */
@interface NvsAVFileInfo : NSObject

@property (readonly) NvsAVFileType avFileType;       //!< \if ENGLISH brief member variable description \else 文件类型 \endif
@property (readonly) int64_t duration;               //!< \if ENGLISH brief member variable description \else 时长(单位微秒) \endif
@property (readonly) uint64_t dataRate;              //!< \if ENGLISH brief member variable description \else 数据速率\endif
@property (readonly) unsigned int videoStreamCount;  //!< \if ENGLISH brief member variable description \else 视频流数目 \endif
@property (readonly) unsigned int audioStreamCount;  //!< \if ENGLISH brief member variable description \else 音频流数目 \endif

/*!
 *  \brief 通过视频流索引获取视频流时长
 *  \param videoStreamIndex 视频流索引
 *  \return 返回当前视频流的时长
 *  \sa getAudioStreamDuration:
 */
- (int64_t)getVideoStreamDuration:(unsigned int)videoStreamIndex;

/*!
 *  \brief 通过视频流索引获取视频流尺寸
 *  \param videoStreamIndex 视频流索引
 *  \return 返回值为NvsSize对象，表示视频流的尺寸(宽度与高度)
 */
- (NvsSize)getVideoStreamDimension:(unsigned int)videoStreamIndex;

/*!
 *  \brief 通过视频流索引获取视频流像素横纵比
 *  \param videoStreamIndex 视频流索引
 *  \return 返回NvsRational对象，表示当前视频流的像素横纵比
 *  \sa getVideoStreamFrameRate:
 */
- (NvsRational)getVideoStreamPixelAspectRatio:(unsigned int)videoStreamIndex;

/*!
 *  \brief 通过视频流索引获取视频流帧速率
 *  \param videoStreamIndex 视频流索引
 *  \return 返回NvsRational对象，表示当前视频流的帧速率
 *  \sa getVideoStreamPixelAspectRatio:
 */
- (NvsRational)getVideoStreamFrameRate:(unsigned int)videoStreamIndex;

/*!
 *  \brief 通过视频流索引获取视频流旋转角度类型
 *  \param videoStreamIndex 视频流索引
 *  \return 返回NvsVideoRotation对象，表示当前视频流的旋转角度类型
 */
- (NvsVideoRotation)getVideoStreamRotation:(unsigned int)videoStreamIndex;

/*!
 *  \brief 通过音频流索引获取音频流时长
 *  \param audioStreamIndex 音频流索引
 *  \return 返回当前音频流的时长
 *  \sa getVideoStreamDuration:
 */
- (int64_t)getAudioStreamDuration:(unsigned int)audioStreamIndex;

/*!
 *  \brief 通过音频流索引获取音频流的采样率
 *  \param audioStreamIndex 音频流索引
 *  \return 返回当前音频流的采样率
 */
- (unsigned int)getAudioStreamSampleRate:(unsigned int)audioStreamIndex;

/*!
 *  \brief 通过音频流索引获取音频流的声道数
 *  \param audioStreamIndex 音频流索引
 *  \return 返回当前音频流的声道数
 */
- (unsigned int)getAudioStreamChannelCount:(unsigned int)audioStreamIndex;

@end

