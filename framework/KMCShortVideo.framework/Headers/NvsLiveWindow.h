//================================================================================
//
// (c) Copyright China Digital Video (Beijing) Limited, 2016. All rights reserved.
//
// This code and information is provided "as is" without warranty of any kind,
// either expressed or implied, including but not limited to the implied
// warranties of merchantability and/or fitness for a particular purpose.
//
//--------------------------------------------------------------------------------
//   Birth Date:    Dec 27. 2016
//   Author:        NewAuto video team
//================================================================================
#pragma once

#import <GLKit/GLKit.h>


/*!
 *  \brief Live Window 填充模式
 */
typedef enum {
    /*!
        \brief 图像按比例均匀填充，必要时进行裁剪(默认模式)

        ![] (PreserveAspectCrop.png)
    */
    NvsLiveWindowFillModePreserveAspectCrop = 0,
    /*!
        \brief 图像均匀地缩放来适合窗口，没有裁剪

        ![] (PreserveAspectFit.png)
    */
    NvsLiveWindowFillModePreserveAspectFit,
    /*!
        \brief 图像被缩放来适合窗口

        ![] (Stretch.png)
    */
    NvsLiveWindowFillModeStretch
} NvsLiveWindowFillMode;

/*!
 *  \brief 实时拍摄预览窗口
 * 
 *  在拍摄视频时，将实时预览窗口与采集预览连接，对拍摄场景进行实时预览。完成拍摄后，将实时预览窗口与创建的时间线
(Time Line)连接，对已完成拍摄的视频根据需要进行编辑，然后生成视频输出.mov格式的文件。
 */
@interface NvsLiveWindow : GLKView

@property (nonatomic, assign) NvsLiveWindowFillMode fillMode;  //!< \if ENGLISH \else LiveWindow的填充模式 \endif

- (instancetype)init;
- (instancetype)initWithFrame:(CGRect)frame;
- (instancetype)initWithCoder:(NSCoder *)aDecoder;
- (instancetype)initWithFrame:(CGRect)frame context:(EAGLContext *)context;

/*!
    \brief 时间线坐标转换成视图坐标
    \param ptCanonical 时间线坐标点
    \return 返回转换后的视图坐标点CGPoint对象
    \sa mapViewToCanonical:
*/
- (CGPoint)mapCanonicalToView:(CGPoint)ptCanonical;
/*!
    \brief 视图坐标转换成时间线坐标
    \param ptView 视图坐标点
    \return 返回转换后的时间线坐标点CGPoint对象
    \sa mapCanonicalToView:
*/
- (CGPoint)mapViewToCanonical:(CGPoint)ptView;
/*!
    \brief 归一化坐标转换成视图坐标
    \param ptNormalized 归一化坐标点
    \return 返回转换后的视图坐标点CGPoint对象
    \sa mapViewToNormalized:
*/
- (CGPoint)mapNormalizedToView:(CGPoint)ptNormalized;
/*!
    \brief 视图坐标转换成归一化坐标
    \param ptView 视图坐标点
    \return 返回转换后的归一化坐标点CGPoint对象
    \sa mapNormalizedToView:
*/
- (CGPoint)mapViewToNormalized:(CGPoint)ptView;

/*!
    \brief 清除LiveWindow的视频帧
*/
- (void)clearVideoFrame;

@end

