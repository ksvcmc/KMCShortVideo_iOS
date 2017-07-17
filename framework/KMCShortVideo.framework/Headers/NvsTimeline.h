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

#import "NvsCommonDef.h"
#import "NvsObject.h"
#import "NvsLiveWindow.h"


@class NvsVideoTrack;
@class NvsAudioTrack;
@class NvsTimelineCaption;
@class NvsTimelineAnimatedSticker;

/*!
     \brief 时间线，编辑场景的时间轴实体
 
     时间线由轨道组成，可视作一系列音视频轨道的集合。在时间线上可添加或者移除多条视频轨道和音轨轨道，多条轨道之间是相互叠加合成的关系。
     当编辑视频时，根据需要还会添加上时间线字幕，主题以及相应的动画贴纸，以制作出美观的视频。

     注：时间线上时间单位都为微秒。
 */
@interface NvsTimeline : NvsObject

@property (readonly) NvsVideoResolution videoRes;  //!< \if ENGLISH \else 视频解析度(图像宽高及横纵比) \endif

@property (readonly) NvsAudioResolution audioRes;  //!< \if ENGLISH \else 音频解析度(采样率、采样格式及通道数) \endif

@property (readonly) NvsRational videoFps;  //!< \if ENGLISH \else 视频帧率 \endif

@property (readonly) int64_t duration;   //!< \if ENGLISH \else 时间线的时长 \endif

/*!
    \brief 追加视频轨道
    \return 返回追加的视频轨道对象
    \warning 此接口会引发流媒体引擎状态跳转到引擎停止状态，具体情况请参见[引擎变化专题] (\ref EngineChange.md)。
    \sa removeVideoTrack:
    \sa videoTrackCount
    \sa getVideoTrackByIndex:
 */
- (NvsVideoTrack *)appendVideoTrack;

/*!
    \brief 追加音频轨道
    \return 返回追加的音频轨道对象
    \warning 此接口会引发流媒体引擎状态跳转到引擎停止状态，具体情况请参见[引擎变化专题] (\ref EngineChange.md)。
    \sa removeAudioTrack:
    \sa audioTrackCount
    \sa getAudioTrackByIndex:
 */
- (NvsAudioTrack *)appendAudioTrack;

/*!
	\brief 移除视频轨道
	\param trackIndex 视频轨道索引
    \return  判断是否移除成功。返回YES移除成功，NO则失败
    \warning 此接口会引发流媒体引擎状态跳转到引擎停止状态，具体情况请参见[引擎变化专题] (\ref EngineChange.md)。
    \sa appendVideoTrack
    \sa videoTrackCount
    \sa getVideoTrackByIndex:
 */
- (BOOL)removeVideoTrack:(unsigned int)trackIndex;

/*!
	\brief 移除音频轨道
	\param trackIndex 音频轨道索引
    \return 判断是否移除成功,YES表示移除成功,NO表示失败。
    \warning 此接口会引发流媒体引擎状态跳转到引擎停止状态，具体情况请参见[引擎变化专题] (\ref EngineChange.md)。
    \sa appendAudioTrack
    \sa audioTrackCount
    \sa getAudioTrackByIndex:
 */
- (BOOL)removeAudioTrack:(unsigned int)trackIndex;

/*!
	\brief 获取视频轨道数量
	\return 返回视频轨道的数量
    \sa appendVideoTrack
    \sa removeVideoTrack:
 */
- (unsigned int)videoTrackCount;

/*!
	\brief 获取音频轨道数量
	\return 返回音频轨道的数量
    \sa appendAudioTrack
    \sa removeAudioTrack:
 */
- (unsigned int)audioTrackCount;

/*!
	\brief 通过索引获取视频轨道
	\param trackIndex 视频轨道索引
    \return 返回获取的视频轨道对象
    \sa appendVideoTrack
    \sa videoTrackCount
    \sa removeVideoTrack:
 */
- (NvsVideoTrack *)getVideoTrackByIndex:(unsigned int)trackIndex;

/*!
	\brief 通过索引获取音频轨道
	\param trackIndex 音频轨道索引
    \return 返回获取的音频轨道对象
    \sa appendAudioTrack
    \sa audioTrackCount
    \sa removeAudioTrack:
 */
- (NvsAudioTrack *)getAudioTrackByIndex:(unsigned int)trackIndex;

/*!
    \brief 获取时间线上的第一个字幕
    \return 返回获取的时间线字幕对象
    \sa getLastCaption
    \sa addCaption:inPoint:duration:captionStylePackageId:
 */
- (NvsTimelineCaption *)getFirstCaption;

/*!
    \brief 获取时间线上的最后一个字幕
    \return 返回获取的时间线字幕对象
    \sa getFirstCaption
    \sa addCaption:inPoint:duration:captionStylePackageId:
 */
- (NvsTimelineCaption *)getLastCaption;

/*!
    \brief 获取时间线上的当前字幕的前一个字幕
	\param caption 时间线上当前字幕对象
    \return 返回获取的时间线字幕对象
    \sa getNextCaption:
 */
- (NvsTimelineCaption *)getPrevCaption:(NvsTimelineCaption *)caption;

/*!
    \brief 获取时间线上的当前字幕的后一个字幕
    \param caption 时间线上当前字幕对象
    \return 返回获取的时间线字幕对象
    \sa getPrevCaption:
 */
- (NvsTimelineCaption *)getNextCaption:(NvsTimelineCaption *)caption;

/*!
	\brief 根据时间线上的位置获得字幕
	\param timelinePos 时间线上的位置(微秒)
	\return 返回保存当前位置字幕的数组对象
    \sa addCaption:inPoint:duration:captionStylePackageId:
 */
- (NSArray *)getCaptionsByTimelinePosition:(int64_t)timelinePos;

/*!
	\brief 在时间线上添加字幕
	\param captionText 添加的字幕
	\param inPoint 字幕在时间线上的起点
	\param duration 字幕显示时长(微秒)
	\param captionStylePackageId 字幕样式包Id
	\return 返回时间线字幕对象
    \warning 此接口会引发流媒体引擎状态跳转到引擎停止状态，具体情况请参见[引擎变化专题] (\ref EngineChange.md)。
    \sa removeCaption:
 */
- (NvsTimelineCaption *)addCaption:(NSString *)captionText inPoint:(int64_t)inPoint duration:(int64_t)duration captionStylePackageId:(NSString *)captionStylePackageId;

/*!
	\brief 移除时间上的字幕
	\param caption 要移除的时间线字幕对象
    \return 返回下一个时间线字幕对象
    \warning 此接口会引发流媒体引擎状态跳转到引擎停止状态，具体情况请参见[引擎变化专题] (\ref EngineChange.md)。
    \sa addCaption:inPoint:duration:captionStylePackageId:
 */
- (NvsTimelineCaption *)removeCaption:(NvsTimelineCaption *)caption;

/*!
	\brief 获取时间线上第一个动画贴纸
	\return 返回获取的时间线动画贴纸对象
    \sa getLastAnimatedSticker
    \sa addAnimatedSticker:duration:animatedStickerPackageId:
 */
- (NvsTimelineAnimatedSticker *)getFirstAnimatedSticker;

/*!
	\brief 获取时间线上最后一个动画贴纸
	\return 返回获取的时间线动画贴纸对象
    \sa getFirstAnimatedSticker
 */
- (NvsTimelineAnimatedSticker *)getLastAnimatedSticker;

/*!
	\brief 获取时间线当前动画贴纸的前一个动画贴纸
	\param animatedSticker 时间线动画贴纸对象
	\return 返回获取的时间线动画贴纸对象
    \sa getNextAnimatedSticker:
 */
- (NvsTimelineAnimatedSticker *)getPrevAnimatedSticker:(NvsTimelineAnimatedSticker *)animatedSticker;

/*!
	\brief 获取时间线当前动画贴纸的后一个动画贴纸
	\param animatedSticker 时间线动画贴纸对象
	\return 返回获取的时间线动画贴纸对象
    \sa getPrevAnimatedSticker:
 */
- (NvsTimelineAnimatedSticker *)getNextAnimatedSticker:(NvsTimelineAnimatedSticker *)animatedSticker;

/*!
	\brief 根据时间线上的位置获得动画贴纸
	\param timelinePos 时间线上的位置(微秒)
	\return 返回保存当前位置动画贴纸对象的数组对象
    \sa addAnimatedSticker:duration:animatedStickerPackageId:
 */
- (NSArray *)getAnimatedStickersByTimelinePosition:(int64_t)timelinePos;

/*!
	\brief 在时间线上添加动画贴纸
    \param inPoint 动画贴纸在时间线上的入点
	\param duration 动画贴纸的显示时长(微秒)
	\param animatedStickerPackageId 动画贴纸包Id
	\return 返回时间线动画贴纸对象
    \warning 此接口会引发流媒体引擎状态跳转到引擎停止状态，具体情况请参见[引擎变化专题] (\ref EngineChange.md)。
    \sa removeAnimatedSticker:
 */
- (NvsTimelineAnimatedSticker *)addAnimatedSticker:(int64_t)inPoint duration:(int64_t)duration animatedStickerPackageId:(NSString *)animatedStickerPackageId;

/*!
	\brief 移除时间上的动画贴纸
	\param animatedSticker 要移除的动画贴纸对象
    \return 返回下一个时间线动画贴纸对象
    \warning 此接口会引发流媒体引擎状态跳转到引擎停止状态，具体情况请参见[引擎变化专题] (\ref EngineChange.md)。
    \sa addAnimatedSticker:duration:animatedStickerPackageId:
 */
- (NvsTimelineAnimatedSticker *)removeAnimatedSticker:(NvsTimelineAnimatedSticker *)animatedSticker;

/*!
    \brief 获得当前主题的id
	\return 当前主题id，若无主题返回nil
    \sa applyTheme:
    \sa removeCurrentTheme
 */
- (NSString *)getCurrentThemeId;

/*!
	\brief 对当前时间线应用主题(主题是相对于整个时间线而言)

    对于主题，可能包含有片头或片尾，或片头片尾都有，也有可能都没有。应用含有片头或片尾的主题时，片头和片尾都被视作一个clip，从而导致clip数量的增加。使用此接口时请注意判断片段的数量。
	\param themeId 主题包裹的id
    \return 判断是否应用主题成功。返回YES则主题运用成功，NO则运用失败。
    \warning 此接口会引发流媒体引擎状态跳转到引擎停止状态，具体情况请参见[引擎变化专题] (\ref EngineChange.md)。
    \sa getCurrentThemeId
    \sa removeCurrentTheme
 */
- (BOOL)applyTheme:(NSString *)themeId;

/*!
    \brief 移除当前主题
    \warning 此接口会引发流媒体引擎状态跳转到引擎停止状态，具体情况请参见[引擎变化专题] (\ref EngineChange.md)。
    \sa applyTheme:
    \sa getCurrentThemeId
 */
- (void)removeCurrentTheme;

/*!
    \brief 设置主题片头字幕文本
    \param text 字幕文本
    \sa setThemeTrailerCaptionText:
    \sa applyTheme:
 */
- (void)setThemeTitleCaptionText:(NSString *)text;

/*!
    \brief 设置主题片尾字幕文本
    \param text 字幕文本
    \sa setThemeTitleCaptionText:
    \sa applyTheme:
 */
- (void)setThemeTrailerCaptionText:(NSString *)text;

/*!
	\brief 设置主题音乐音量
	\param leftVolumeGain 左声道
	\param rightVolumeGain 右声道
    \sa getThemeMusicVolumeGain:rightVolumeGain:
 */
- (void)setThemeMusicVolumeGain:(float)leftVolumeGain rightVolumeGain:(float)rightVolumeGain;

/*!
	\brief 获取主题音乐音量
    \param leftVolumeGain 返回值，返回左声道值
    \param rightVolumeGain 返回值，返回右声道值
    \sa setThemeMusicVolumeGain:rightVolumeGain:
 */
- (void)getThemeMusicVolumeGain:(float *)leftVolumeGain rightVolumeGain:(float *)rightVolumeGain;


@end

