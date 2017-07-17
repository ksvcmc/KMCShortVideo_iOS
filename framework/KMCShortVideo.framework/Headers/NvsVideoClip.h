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
/*! \file NvsVideoClip.h
 */
#pragma once

#import "NvsCommonDef.h"
#import "NvsClip.h"

typedef enum NvsVideoClipType {
    NvsVideoClipType_AV = 0,   /*!< 音视频(0) */
    NvsVideoClipType_Image,    /*!< 图片*/
} NvsVideoClipType;  /*!< 片段类型 */

/*!
 *  \brief 图片片段运作模式
 *  \since 1.1.0
 */
typedef enum {
    NvsStreamingEngineImageClipMotionMode_LetterBoxZoomIn = 0, //!< \if ENGLISH \else 放大 \endif
    NvsStreamingEngineImageClipMotionMode_LetterBoxZoomOut,    //!< \if ENGLISH \else 缩小 \endif
    NvsStreamingEngineImageClipMotionMode_ROI                  //!< \if ENGLISH \else 图片片段ROI(Region Of Interesting) \endif
} NvsStreamingEngineImageClipMotionMode;

@class NvsVideoFx;

/*!
    \brief 视频片段，对视频文件的描述

    视频片段源可以是视频或者图片。每个视频片段可以修改其裁剪入点、裁剪出点以及播放速度，也可以设置摇摄和扫描。编辑视频时，可以按特效类型的不同（内建特效，包裹式特效，美颜特效）添加或者插入多个视频特效。
 */
@interface NvsVideoClip : NvsClip


@property (readonly) NvsVideoClipType videoType;  //!< \if ENGLISH \else 视频片段类型(音视频、图片)\endif


@property (readonly) NvsRoleInTheme roleInTheme;  //!< \if ENGLISH \else 视频片段在主题中角色(通用、片头、片尾)\endif


@property (nonatomic, assign) NvsStreamingEngineImageClipMotionMode imageMotionMode; //!< \if ENGLISH \else 图片片段运作模式 \since 1.1.0 \endif

@property (nonatomic, assign) BOOL imageMotionAnimationEnabled;  //!< \if ENGLISH \else 是否支持图片动画 \since 1.1.0 \endif

@property (readonly) NvsRect startROI; //!< \if ENGLISH \else 图片片段起始ROI \since 1.1.0 \endif

@property (readonly) NvsRect endROI;   //!< \if ENGLISH \else 图片片段终止ROI \since 1.1.0 \endif

/*!
    \brief 设置摇摄和扫描

    摇摄和扫描功能是用来适配图像在显示窗口上的位置与大小的。具体请参见[摇摄与扫描(Pan and Scan)] (\ref Pan_Scan.md)专题。
    \param pan 摇摄
    \param scan 扫描
    \sa getPan:andScan:
 */
- (void)setPan:(float)pan andScan:(float)scan;

/*!
    \brief 获取摇摄和扫描
    \param pan 返回值，获取摇摄值
    \param scan 返回值，获取扫描值
    \sa setPan:andScan:
 */
- (void)getPan:(float *)pan andScan:(float *)scan;

/*!
    \brief 设置图片片段动态移动ROI

    具体情况请参见[图片片段ROI专题] (\ref ImageROI.md)
    \param startROI 图片片段起始ROI
    \param endROI 图片片段终止ROI
    \since 1.1.0
    \sa setPan:andScan:
 */
- (void)setImageMotionROI:(NvsRect *)startROI endROI:(NvsRect *)endROI;

/*!
    \brief 在片段末尾追加内嵌式特效
    \param fxName 特效名称。获取视频特效名称，请参见[getAllBuiltinVideoFxNames()] (@ref NvsStreamingContext::getAllBuiltinVideoFxNames)或[内建特效名称列表] (\ref FxNameList.md)
    \return 返回追加的视频特效对象
    \warning 此接口会引发流媒体引擎状态跳转到引擎停止状态，具体情况请参见[引擎变化专题] (\ref EngineChange.md)。
    \sa insertBuiltinFx:fxIndex:
    \sa appendBeautyFx
    \sa appendPackagedFx:
 */
- (NvsVideoFx *)appendBuiltinFx:(NSString *)fxName;

/*!
    \brief 在片段上指定特效索引处插入内嵌式特效
    \param fxName 特效名称。获取视频特效名称，请参见[getAllBuiltinVideoFxNames()] (@ref NvsStreamingContext::getAllBuiltinVideoFxNames)或[内建特效名称列表] (\ref FxNameList.md)
    \param fxIndex 插入特效索引
    \return 返回插入的视频特效对象
    \warning 此接口会引发流媒体引擎状态跳转到引擎停止状态，具体情况请参见[引擎变化专题] (\ref EngineChange.md)。
    \sa appendBuiltinFx:
    \sa insertPackagedFx:fxIndex:
    \sa insertBeautyFx:
 */
- (NvsVideoFx *)insertBuiltinFx:(NSString *)fxName fxIndex:(unsigned int)fxIndex;

/*!
    \brief 在片段末尾追加资源包特效
    \param fxPackageId 特效资源包ID
    \return 返回追加的视频特效对象
    \warning 此接口会引发流媒体引擎状态跳转到引擎停止状态，具体情况请参见[引擎变化专题] (\ref EngineChange.md)。
    \sa appendBeautyFx
    \sa appendBuiltinFx:
    \sa insertPackagedFx:fxIndex:
 */
- (NvsVideoFx *)appendPackagedFx:(NSString *)fxPackageId;

/*!
    \brief 在片段上指定特效索引处插入包裹特效
    \param fxPackageId 包裹特效Id
    \param fxIndex 插入特效索引
    \return 返回插入的视频特效对象
    \warning 此接口会引发流媒体引擎状态跳转到引擎停止状态，具体情况请参见[引擎变化专题] (\ref EngineChange.md)。
    \sa insertBeautyFx:
    \sa appendPackagedFx:
    \sa insertBuiltinFx:fxIndex:
 */
- (NvsVideoFx *)insertPackagedFx:(NSString *)fxPackageId fxIndex:(unsigned int)fxIndex;

/*!
    \brief 在片段末尾追加美颜特效
    \return 返回追加的视频特效对象
    \warning 此接口会引发流媒体引擎状态跳转到引擎停止状态，具体情况请参见[引擎变化专题] (\ref EngineChange.md)。
    \sa insertBeautyFx:
    \sa appendPackagedFx:
    \sa appendBuiltinFx:
 */
- (NvsVideoFx *)appendBeautyFx;

/*!
    \brief 在片段上指定特效索引处插入美颜特效
    \param fxIndex 插入特效索引
    \return 返回插入的视频特效对象
    \warning 此接口会引发流媒体引擎状态跳转到引擎停止状态，具体情况请参见[引擎变化专题] (\ref EngineChange.md)。
    \sa appendBeautyFx
    \sa insertPackagedFx:fxIndex:
    \sa insertBuiltinFx:fxIndex:
 */
- (NvsVideoFx *)insertBeautyFx:(unsigned int)fxIndex;

/*!
    \brief 移除特效
    \param fxIndex 特效索引
    \return 判断是否移除成功。返回true则移除成功，false则失败。
    \warning 此接口会引发流媒体引擎状态跳转到引擎停止状态，具体情况请参见[引擎变化专题] (\ref EngineChange.md)。
    \sa removeAllFx
 */
- (BOOL)removeFx:(unsigned int)fxIndex;

/*!
    \brief 移除所有特效
    \return 判断是否移除成功。返回true则移除成功，false则失败。
    \warning 此接口会引发流媒体引擎状态跳转到引擎停止状态，具体情况请参见[引擎变化专题] (\ref EngineChange.md)。
    \sa removeFx:
 */
- (BOOL)removeAllFx;

/*!
    \brief 通过索引获取特效
    \param fxIndex 特效索引
    \return 返回获取的视频特效对象
 */
- (NvsVideoFx *)getFxWithIndex:(unsigned int)fxIndex;

@end
