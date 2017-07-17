//================================================================================
//
// (c) Copyright China Digital Video (Beijing) Limited, 2017. All rights reserved.
//
// This code and information is provided "as is" without warranty of any kind,
// either expressed or implied, including but not limited to the implied
// warranties of merchantability and/or fitness for a particular purpose.
//
//--------------------------------------------------------------------------------
//   Birth Date:    Feb 17. 2017
//   Author:        NewAuto video team
//================================================================================
#pragma once

#import "NvsFx.h"
#import <CoreGraphics/CGGeometry.h>

/*!
    \brief 时间线动画贴纸，带有动画效果的贴纸
   
    时间线动画贴纸是视频编辑时使用的一种美化特效，叠加在视频上会产生一些特殊效果。编辑视频时，可通过时间线(Time Line)来添加和移除动画贴纸。如果添加的贴纸位置不合理，还可进行调整移动。
 */
@interface NvsTimelineAnimatedSticker : NvsFx

@property (readonly) int64_t inPoint; //!< \if ENGLISH \else 动画贴纸在时间线上显示的入点 \endif
@property (readonly) int64_t outPoint; //!< \if ENGLISH \else 动画贴纸在时间线上显示的出点 \endif

/*!
     \brief 改变动画贴纸在时间线上显示的入点
     \param newInPoint 动画贴纸在时间线上的新的入点
     \return 返回动画贴纸在时间线上的显示的入点值
     \warning 此接口会引发流媒体引擎状态跳转到引擎停止状态，具体情况请参见[引擎变化专题] (\ref EngineChange.md)。
     \sa changeOutPoint:
     \sa movePosition:
 */
- (int64_t)changeInPoint:(int64_t)newInPoint;

/*!
     \brief 改变动画贴纸在时间线上显示的出点
     \param newOutPoint 动画贴纸在时间线上的新的出点
     \return 返回动画贴纸在时间线上的显示的出点值
     \warning 此接口会引发流媒体引擎状态跳转到引擎停止状态，具体情况请参见[引擎变化专题] (\ref EngineChange.md)。
     \sa changeInPoint:
     \sa movePosition:
 */
- (int64_t)changeOutPoint:(int64_t)newOutPoint;

/*!
     \brief 改变动画贴纸在时间线上的显示位置(入点和出点同时偏移offset值)
     \param offset 入点和出点改变的偏移值
     \warning 此接口会引发流媒体引擎状态跳转到引擎停止状态，具体情况请参见[引擎变化专题] (\ref EngineChange.md)。
     \sa changeInPoint:
     \sa changeOutPoint:
 */
- (void)movePosition:(int64_t)offset;

/*!
     \brief 设置缩放
     \param scale 缩放值
     \sa getScale
 */
- (void)setScale:(float)scale;

/*!
     \brief 获取缩放值
     \return 返回获取的缩放值
     \sa setScale:
 */
- (float)getScale;

/*!
     \brief 设置水平翻转
     \param flip 是否水平翻转。true表示水平翻转，false则不翻转
     \sa getHorizontalFlip
 */
- (void)setHorizontalFlip:(bool)flip;

/*!
     \brief 获取水平翻转状态
     \return 返回BOOL值，表示水平翻转状态。YES表示已翻转，NO则未翻转
     \sa setHorizontalFlip:
 */
- (BOOL)getHorizontalFlip;

/*!
     \brief 设置竖直翻转
     \param flip 是否竖直翻转。true表示竖直翻转，false则不翻转
     \sa getVerticalFlip
 */
- (void)setVerticalFlip:(bool)flip;

/*!
     \brief 获取竖直翻转状态
     \return 返回BOOL值，表示竖直翻转状态。YES表示已翻转，NO则未翻转
     \sa setVerticalFlip:
 */
- (BOOL)getVerticalFlip;

/*!
     \brief 设置旋转角度
     \param angle 旋转角度值
     \sa getRotationZ
 */
- (void)setRotationZ:(float)angle;

/*!
     \brief 获取旋转角度值
     \return 返回获取的旋转角度值
     \sa setRotationZ:
 */
- (float)getRotationZ;

/*!
     \brief 设置平移
     \param translation 平移位置
     \sa getTransltion
 */
- (void)setTranslation:(CGPoint)translation;

/*!
     \brief 获取平移位置
     \return 返回CGPoint对象，表示获取的平移位置
     \sa setTranslation:
 */
- (CGPoint)getTransltion;

/*!
     \brief 获取原始矩形框
     \return 返回NvsRect对象，表示获取的原始矩形框
 */
- (NvsRect)getOriginalBoundingRect;

@end

