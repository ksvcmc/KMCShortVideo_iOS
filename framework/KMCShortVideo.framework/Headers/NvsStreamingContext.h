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

#import <Foundation/Foundation.h>
#import "NvsTimeline.h"
#import "NvsAssetPackageManager.h"
#import "NvsAVFileInfo.h"
#import "NvsVideoFrameRetriever.h"

/*!
 *  \brief
 *  生成视频文件的分辨率高度级别(创建时间线(createTimeline)时指定视频的宽高和横纵比，根据输出的视频分辨率高度算出生成视频文件的宽度)
 */
typedef enum {
    NvsCompileVideoResolutionGrade360 = 0, //!< \if ENGLISH \else 输出高度360像素 \endif
    NvsCompileVideoResolutionGrade480,     //!< \if ENGLISH \else 输出高度480像素 \endif
    NvsCompileVideoResolutionGrade720,     //!< \if ENGLISH \else 输出高度720像素 \endif
    NvsCompileVideoResolutionGrade1080     //!< \if ENGLISH \else 输出高度1080像素 \endif
} NvsCompileVideoResolutionGrade;

/*!
 *  \brief 生成视频文件的码率级别
 */
typedef enum {
    NvsCompileBitrateGradeLow = 0,          //!< \if ENGLISH \else 低码率 \endif
    NvsCompileBitrateGradeMedium,           //!< \if ENGLISH \else 中等码率 \endif
    NvsCompileBitrateGradeHigh              //!< \if ENGLISH \else 高码率 \endif
} NvsCompileVideoBitrateGrade;

/*!
 *  \brief 视频预览模式
 */
typedef enum {
    NvsVideoPreviewSizeModeFullSize = 0,     //!< \if ENGLISH \else 全屏预览 \endif
    NvsVideoPreviewSizeModeLiveWindowSize    //!< \if ENGLISH \else liveWindow预览 \endif
} NvsVideoPreviewSizeMode;

/*!
 *  \brief 视频采集分辨率级别
 */
typedef enum {
    NvsVideoCaptureResolutionGradeLow = 0,   //!< \if ENGLISH \else 低分辨率 \endif
    NvsVideoCaptureResolutionGradeMedium,    //!< \if ENGLISH \else 中等分辨率 \endif
    NvsVideoCaptureResolutionGradeHigh       //!< \if ENGLISH \else 高分辨率 \endif
} NvsVideoCaptureResolutionGrade;

/*!
 *  \brief 流媒体引擎状态
 */
typedef enum {
    NvsStreamingEngineState_Stopped = 0,      //!< \if ENGLISH \else 引擎停止 \endif
    NvsStreamingEngineState_CapturePreview,   //!< \if ENGLISH \else 采集预览 \endif
    NvsStreamingEngineState_CaptureRecording, //!< \if ENGLISH \else 采集录制 \endif
    NvsStreamingEngineState_Playback,         //!< \if ENGLISH \else 播放 \endif
    NvsStreamingEngineState_Seeking,          //!< \if ENGLISH \else 定位 \endif
    NvsStreamingEngineState_Compile           //!< \if ENGLISH \else 生成 \endif
} NvsStreamingEngineState;

/*!
 *  \brief 采集标志
 */
typedef enum
{
    NvsStreamingEngineSeekFlag_GrabCapturedVideoFrame = 1,      //!< \if ENGLISH \else 获取采集视频的帧内容（打开这个标志会降低性能，只有在必要的时候开启这个标志） \endif
} NvsStreamingEngineCaptureFlag;

/*!
 *  \brief 引擎定位标识
 */
typedef enum {
    NvsStreamingEngineSeekFlag_ShowCaptionPoster = 2,          //!< \if ENGLISH \else 整体展示字幕效果 \endif
    NvsStreamingEngineSeekFlag_ShowAnimatedStickerPoster = 4,  //!< \if ENGLISH \else 整体展示动画贴纸效果 \endif
} NvsStreamingEngineSeekFlag;


@class NvsCaptureDeviceCapability;
@class NvsCaptureVideoFx;
@class NvsFxDescription;
@class NvsCaptureDeviceCapability;
@class NvsCaptureVideoFx;
@class NvsFxDescription;

@protocol NvsStreamingContextDelegate <NSObject>
@optional

/*!
 *  \brief 采集设备准备完成
 *  \param captureDeviceIndex 设备索引
 */
- (void)didCaptureDeviceCapsReady:(unsigned int)captureDeviceIndex;

/*!
 *  \brief 采集设备预览解析度准备完成
 *  \param captureDeviceIndex 设备索引
 */
- (void)didCaptureDevicePreviewResolutionReady:(unsigned int)captureDeviceIndex;

/*!
 *  \brief 采集设备预览开始
 *  \param captureDeviceIndex 设备索引
 */
- (void)didCaptureDevicePreviewStarted:(unsigned int)captureDeviceIndex;

/*!
 *  \brief 采集设备错误
 *  \param captureDeviceIndex 设备索引 
 *  \param errorCode 错误码
 */
- (void)didCaptureDeviceError:(unsigned int)captureDeviceIndex errorCode:(int32_t)errorCode;

/*!
 *  \brief 采集设备停止
 *  \param captureDeviceIndex 设备索引
 */
- (void)didCaptureDeviceStopped:(unsigned int)captureDeviceIndex;

/*!
 *  \brief 采集设备自动对焦完成
 *  \param captureDeviceIndex 设备索引
 *  \param succeeded 对焦是否完成
 */
- (void)didCaptureDeviceAutoFocusComplete:(unsigned int)captureDeviceIndex succeeded:(BOOL)succeeded;

/*!
 *  \brief 采集录制完成
 *  \param captureDeviceIndex 设备索引
 *  \sa didCaptureRecordingError:
 */
- (void)didCaptureRecordingFinished:(unsigned int)captureDeviceIndex;

/*!
 *  \brief 采集录制失败
 *  \param captureDeviceIndex 设备索引
 */
- (void)didCaptureRecordingError:(unsigned int)captureDeviceIndex;

/*!
 *  \brief 播放预先加载完成
 *  \param timeline 时间线
 */
- (void)didPlaybackPreloadingCompletion:(NvsTimeline *)timeline;

/*!
 *  \brief 播放停止
 *  \param timeline 时间线
 */
- (void)didPlaybackStopped:(NvsTimeline *)timeline;

/*!
 *  \brief 播放到结尾
 *  \param timeline 时间线
 */
- (void)didPlaybackEOF:(NvsTimeline *)timeline;

/*!
 *  \brief 生成视频文件进度
 *  \param timeline 时间线
 *  \param progress 进度值
 */
- (void)didCompileProgress:(NvsTimeline *)timeline progress:(int)progress;

/*!
 *  \brief 生成视频文件完成
 *  \param timeline 时间线
 *  \sa didCompileFailed:
 */
- (void)didCompileFinished:(NvsTimeline *)timeline;

/*!
 *  \brief 生成视频文件失败
 *  \param timeline 时间线
 */
- (void)didCompileFailed:(NvsTimeline *)timeline;

/*!
 *  \brief 引擎状态改变
 *  \param state 引擎状态
 */
- (void)didStreamingEngineStateChanged:(NvsStreamingEngineState)state;

/*!
 *  \brief 第一视频帧呈现
 *  \param timeline 时间线
 */
- (void)didFirstVideoFramePresented:(NvsTimeline *)timeline;

/*!
 *  \brief 时间线越界（注：非必要情况请勿使用此回调接口）
 *  \param timeline 时间线
 *  \since 1.2.0
 */

- (void)didTimestampOutOfRange:(NvsTimeline *)timeline;

@end

/*!
 *  \brief 流媒体上下文
 * 
 *  流媒体上下文类可视作整个SDK框架的入口。开发过程中，NvsStreamingContext类提供了静态sharedInstance()接口创建流上下文的唯一实例。
 *  通过这个实例对象，我们可以开启采集设备录制视频，添加采集视频特效，设置拍摄时的各项参数，包括自动聚焦，自动曝光调节，开关换补光灯等。
 *  同时，还能够创建时间线，并将时间线与实时预览窗口(Live Window)连接起来，实时预览播放已经拍摄完成的视频。整个视频制作完成后，要销毁流媒体上下文的对象实例。
 *
 *  注意: 视频录制和视频生成时只支持输出.mov格式的文件
 */
@interface NvsStreamingContext : NSObject

@property (nonatomic, retain) id<NvsStreamingContextDelegate> delegate;
@property (readonly) NvsAssetPackageManager *assetPackageManager;

/*!
 *  \brief 验证SDK授权文件
 *  \param sdkLicenseFilePath SDK授权文件路径
 *  \return 返回BOOL值。YES表示授权验证成功，NO则验证失败。若验证失败，则后续的视频预览和生成视频会出现水印。
 */
+ (BOOL)verifySdkLicenseFile:(NSString *)sdkLicenseFilePath;

/*!
 *  \brief 获取流媒体上下文的唯一实例
 *  \return 返回流媒体上下文的对象实例
 *  \sa destroyInstance
 */
+ (NvsStreamingContext *)sharedInstance;

/*!
 *  \brief 销毁流媒体上下文实例。注意: 销毁之后无法再次创建及获取
 *  \sa sharedInstance
 */
+ (void)destroyInstance;

/*!
 *  \brief 获取文件的音视频信息
 *  \param avFilePath 文件路径
 *  \return 返回音视频文件信息的对象
 */
- (NvsAVFileInfo *)getAVFileInfo:(NSString *)avFilePath;

/*!
 *  \brief 设置默认主题logo图片路径
 *  \param logoImageFilePath logo图片文件路径
 *  \return 返回BOOL值。YES 设置成功；NO 设置失败
 *  \sa getDefaultThemeEndingLogoImageFilePath
 */
- (BOOL)setDefaultThemeEndingLogoImageFilePath:(NSString *)logoImageFilePath;

/*!
 *  \brief 获取默认主题logo图片路径
 *  \return 返回表示图片路径的字符串
 *  \sa setDefaultThemeEndingLogoImageFilePath:
 */
- (NSString *)getDefaultThemeEndingLogoImageFilePath;


/*!
 *  \brief 创建时间线
 *  \param videoEditRes 视频编辑解析度(指定视频宽高及横纵比)。对于视频编辑解析度，在传入对应参数值时，目前要求传入的图像宽度值是4的倍数，高度值是2的倍数，并且视频编辑解析度里的imageWidth * imageHeight不能高于1920 * 1080像素。
 *  \param videoFps 视频帧率
 *  \param audioEditRes 音频编辑解析度(指定采样率、采样格式及声道数)。对于音频编辑解析度，传入的采样率值支持两种：44100与48000。
 *  \return 返回创建的时间线对象
 *  \sa removeTimeline:
 */
- (NvsTimeline *)createTimeline:(NvsVideoResolution *)videoEditRes videoFps:(NvsRational *)videoFps audioEditRes:(NvsAudioResolution *)audioEditRes;

/*!
 *  \brief 移除时间线
 *  \param timeline 要移除的时间线
 *  \return 返回BOOL值。YES 移除成功；NO 移除失败
 *  \warning 此接口会引发流媒体引擎状态跳转到引擎停止状态，具体情况请参见[引擎变化专题] (\ref EngineChange.md)。
 *  \sa createTimeline:videoFps:audioEditRes:
 */
- (BOOL)removeTimeline:(NvsTimeline *)timeline;


/*!
 *  \brief 获取引擎状态
 *  \return 返回引擎状态
 */
- (NvsStreamingEngineState)getStreamingEngineState;

/*!
 *  \brief 取得时间线当前时间位置，单位为微秒
 *  \param timeline 时间线
 *  \return 返回时间线的当前位置值
 */
- (int64_t)getTimelineCurrentPosition:(NvsTimeline *)timeline;

/*!
 *  \brief 时间线生成视频文件
 *  \param timeline 时间线
 *  \param startTime 开始时间。startTime取值范围在[0,timeline.duration - 1],传入其他值无效。
 *  \param endTime 结束时间。endTime取值范围在(startTime,timeline.duration],同样传入其他值无效。
 *  \param outputFilePath 生成视频输出的文件路径。注意: 目前只支持输出.mov格式的文件
 *  \param videoResolutionGrade 生成视频输出的分辨率级别
 *  \param videoBitrateGrade 生成视频输出的码率
 *  \param flags 生成视频输出的特殊标志(暂时只设为0)
 *  \return 返回BOOL值。注意：时间线生成视频文件是异步操作。返回值为YES则启动时间线生成文件成功，NO则时间线生成文件启动失败。
 *  \warning 此接口会引发流媒体引擎状态跳转到引擎停止状态，具体情况请参见[引擎变化专题] (\ref EngineChange.md)。
 *  \sa seekTimeline:timestamp:videoSizeMode:flags:
 *  \sa playbackTimeline:startTime:endTime:videoSizeMode:preload:flags:
 */
- (BOOL)compileTimeline:(NvsTimeline *)timeline startTime:(int64_t)startTime endTime:(int64_t)endTime outputFilePath:(NSString *)outputFilePath videoResolutionGrade:(NvsCompileVideoResolutionGrade)videoResolutionGrade videoBitrateGrade:(NvsCompileVideoBitrateGrade)videoBitrateGrade flags:(int)flags;

/*!
 *  \brief 连接时间线和实时预览窗口
 *  \param timeline 时间线
 *  \param liveWindow 实时预览窗口
 *  \return 返回BOOL值。返回YES则连接成功，NO则连接失败。
 */
- (BOOL)connectTimeline:(NvsTimeline *)timeline withLiveWindow:(NvsLiveWindow *)liveWindow;

/*!
 *  \brief 定位某一时间戳的图像
 *  \param timeline 时间线
 *  \param timestamp 时间戳(单位是微秒)。timestamp取值范围在[0,timeline.duration - 1]。传入其他值无效，seekTimeline会返回No,导致无法开启定位。
 *  \param videoSizeMode 图像预览模式
 *  \param flags 引擎定位的特殊标志。请参见 [NvsStreamingEngineSeekFlag] (@ref NvsStreamingEngineSeekFlag)
 *  \return 返回BOOL值。注意：定位某时间戳图像是异步操作。返回值为YES则成功开启定位，NO则无法开启定位。
 *  \warning 此接口会引发流媒体引擎状态跳转到引擎停止状态，具体情况请参见[引擎变化专题] (\ref EngineChange.md)。
 *  \sa compileTimeline:startTime:endTime:outputFilePath:videoResolutionGrade:videoBitrateGrade:flags:
 *  \sa playbackTimeline:startTime:endTime:proxyScale:preload:flags:
 *  \sa seekTimeline:timestamp:proxyScale:flags:
 */
- (BOOL)seekTimeline:(NvsTimeline *)timeline timestamp:(int64_t)timestamp videoSizeMode:(NvsVideoPreviewSizeMode)videoSizeMode flags:(int)flags;

/*!
 *  \brief 定位某一时间戳的图像
 *  \param timeline 时间线
 *  \param timestamp 时间戳(单位是微秒)。timestamp取值范围在[0,timeline.duration - 1]。传入其他值无效，seekTimeline会返回No,导致无法开启定位。
 *  \param proxyScale 代理缩放比例
 *  \param flags 引擎定位的特殊标志。请参见 [NvsStreamingEngineSeekFlag] (@ref NvsStreamingEngineSeekFlag)
 *  \return 返回BOOL值。注意：定位某时间戳图像是异步操作。返回值为YES则成功开启定位，NO则无法开启定位。
 *  \warning 此接口会引发流媒体引擎状态跳转到引擎停止状态，具体情况请参见[引擎变化专题] (\ref EngineChange.md)。
 *  \sa seekTimeline:timestamp:videoSizeMode:flags:
 *  \sa playbackTimeline:startTime:endTime:videoSizeMode:preload:flags:
 *  \sa compileTimeline:startTime:endTime:outputFilePath:videoResolutionGrade:videoBitrateGrade:flags:
 */
- (BOOL)seekTimeline:(NvsTimeline *)timeline timestamp:(int64_t)timestamp proxyScale:(const NvsRational *)proxyScale flags:(int)flags;

/*!
 *  \brief 获取时间线某一时间戳的图像。详细情况参见[视频帧图像提取专题] (@ref videoFrameRetriever.md)
 *  \param timeline 欲获取图像的时间线对象
 *  \param timestamp 欲获取图像的时间戳(单位是微秒)。timestamp取值范围在[0,timeline.duration - 1]。传入其他值无效，grabImageFromTimeline会返回nil。
 *  \param proxyScale 代理缩放比例，填写nil表示使用默认比例1:1
 *  \return 返回该时间戳图像的UIImage对象，如果获取图像失败返回nil
 *  \since 1.1.2
 */
- (UIImage *)grabImageFromTimeline:(NvsTimeline *)timeline
                         timestamp:(int64_t)timestamp
                        proxyScale:(const NvsRational *)proxyScale;

/*!
 *  \brief 播放时间线
 *  \param timeline 时间线
 *  \param startTime 开始时间(单位是微秒)。startTime取值范围在[0,timeline.duration - 1]。传入其他值无效，playbackTimeline会返回No导致无法开启播放。
 *  \param endTime 结束时间(单位是微秒)。如果endTime值传入是负值，则默认播放到视频末尾。
 *  \param videoSizeMode 图像预览模式
 *  \param preload 是否预先加载
 *  \param flags 预览的特殊标志(暂时只设为0)
 *  \return 返回BOOL值。注意：播放时间线是异步操作。返回YES则可以开启播放时间线，NO则无法开启播放。
 *  \warning 此接口会引发流媒体引擎状态跳转到引擎停止状态，具体情况请参见[引擎变化专题] (\ref EngineChange.md)。
 *  \sa playbackTimeline:startTime:endTime:proxyScale:preload:flags:
 *  \sa compileTimeline:startTime:endTime:outputFilePath:videoResolutionGrade:videoBitrateGrade:flags:
 *  \sa seekTimeline:timestamp:videoSizeMode:flags:
 */
- (BOOL)playbackTimeline:(NvsTimeline *)timeline startTime:(int64_t)startTime endTime:(int64_t)endTime videoSizeMode:(NvsVideoPreviewSizeMode)videoSizeMode preload:(BOOL)preload flags:(int)flags;

/*!
 *  \brief 预览播放时间线
 *  \param timeline 时间线
 *  \param startTime 开始时间(单位是微秒)。startTime取值范围在[0,timeline.duration - 1]。传入其他值无效，playbackTimeline会返回No导致无法开启播放。
 *  \param endTime 结束时间(单位是微秒)。如果endTime值传入是负值，则默认播放到视频末尾。
 *  \param proxyScale 代理缩放比例
 *  \param preload 是否预先加载
 *  \param flags 预览的特殊标志(暂时只设为0)
 *  \return 返回BOOL值。注意：播放时间线是异步操作。返回YES则可以开启播放时间线，NO则无法开启播放。
 *  \warning 此接口会引发流媒体引擎状态跳转到引擎停止状态，具体情况请参见[引擎变化专题] (\ref EngineChange.md)。
 *  \sa playbackTimeline:startTime:endTime:videoSizeMode:preload:flags:
 *  \sa seekTimeline:timestamp:proxyScale:flags:
 *  \sa compileTimeline:startTime:endTime:outputFilePath:videoResolutionGrade:videoBitrateGrade:flags:
 */
- (BOOL)playbackTimeline:(NvsTimeline *)timeline startTime:(int64_t)startTime endTime:(int64_t)endTime proxyScale:(const NvsRational *)proxyScale preload:(BOOL)preload flags:(int)flags;

/*!
 *  \brief 停止引擎
 */
- (void)stop;

/*!
 *  \brief 清除缓存资源
 *  \param asynchronous 是否异步
 */
- (void)clearCachedResources:(BOOL)asynchronous;

/*!
 *  \brief 采集设备的数量
 *  \return 返回采集设备数
 */
- (unsigned int)captureDeviceCount;

/*!
 *  \brief 是否为后置采集设备
 *  \param catpureDeviceIndex 采集设备索引
 *  \return 返回BOOL值。返回YES则是后置采集设备，NO则不是。
 */
- (BOOL)isCaptureDeviceBackFacing:(unsigned int)catpureDeviceIndex;

/*!
 *  \brief 获取采集设备的能力描述对象
 *  \param catpureDeviceIndex 采集设备索引
 *  \return 返回采集设备能力描述对象
 */
- (NvsCaptureDeviceCapability *)getCaptureDeviceCapability:(unsigned int)catpureDeviceIndex;

/*!
 *  \brief 连接采集预览和实时预览窗口
 *  \param liveWindow 实时预览窗口
 *  \return 返回BOOL值。返回YES则连接成功，NO则连接失败。
 *  \sa connectTimeline:withLiveWindow:
 */
- (BOOL)connectCapturePreviewWithLiveWindow:(NvsLiveWindow *)liveWindow;

/*!
 *  \brief 启动采集设备预览
 *  \param captureDeviceIndex 采集设备索引
 *  \param videoResGrade 视频采集分辨率级别
 *  \param flags 标志字段，如无特殊需求请填写0。请参见 [NvsStreamingEngineCaptureFlag] (@ref NvsStreamingEngineCaptureFlag)
 *  \param aspectRatio 预览视频横纵比，传入nil则由系统采集设备来决定横纵比
 *  \return 返回BOOL值。返回YES则启动预览成功，NO则启动预览失败。
 */
- (BOOL)startCapturePreview:(unsigned int)captureDeviceIndex
              videoResGrade:(NvsVideoCaptureResolutionGrade)videoResGrade
                      flags:(int)flags
                aspectRatio:(const NvsRational *)aspectRatio;

/*!
 *  \brief 为直播启动采集设备预览
 *  \param captureDeviceIndex 采集设备索引
 *  \param videoResGrade 视频采集分辨率级别
 *  \param flags 标志字段，如无特殊需求请填写0。请参见 [NvsStreamingEngineCaptureFlag] (@ref NvsStreamingEngineCaptureFlag)
 *  \param aspectRatio 预览视频横纵比，传入nil则由系统采集设备来决定横纵比
 *  \param liveStreamingEndPoint 直播推流的目的地址(rtmp://xxx)
 *  \return 返回BOOL值。返回YES则启动预览成功，NO则启动预览失败。
 *  \since 1.1.0
 */
- (BOOL)startCapturePreviewForLiveStreaming:(unsigned int)captureDeviceIndex
                              videoResGrade:(NvsVideoCaptureResolutionGrade)videoResGrade
                                      flags:(int)flags
                                aspectRatio:(const NvsRational *)aspectRatio
                      liveStreamingEndPoint:(NSString *)liveStreamingEndPoint;

/*!
 *  \brief 对采集设备的视频帧内容进行采样
 *  \param sampleRect 采样的矩形区域，坐标为实时预览窗口的自身坐标系
 *  \return 返回值为采样的颜色值，该颜色值是采样的矩形区域内所有像素颜色的平均值
 *  \since 1.2.0
 */
- (NvsColor)sampleColorFromCapturedVideoFrame:(CGRect)sampleRect;

/*!
 *  \brief 启动自动聚焦
 *  \param focusPointOfInterest 自动聚焦的目标点，坐标为实时预览窗口的自身坐标系
 *  \sa cancelAutoFocus
 */
- (void)startAutoFocus:(CGPoint)focusPointOfInterest;

/*!
 *  \brief 取消正在进行中的自动聚焦
 *  \sa startAutoFocus:
 */
- (void)cancelAutoFocus;

/*!
 *  \brief 启动自动曝光调节
 *  \param pointOfInterest 曝光调节点
 */
- (void)startAutoExposure:(CGPoint)pointOfInterest;

/*!
 *  \brief 设置缩放因子
 *  \param zoomFactor 缩放比例
 *  \sa getZoomFactor
 */
- (void)setZoomFactor:(float)zoomFactor;

/*!
 *  \brief 获取缩放因子
 *  \return 返回缩放因子值
 *  \sa setZoomFactor:
 */
- (float)getZoomFactor;

/*!
 *  \brief 开/关换补光灯
 *  \param on 设置灯光开或关
 *  \sa isFlashOn
 */
- (void)toggleFlash:(BOOL)on;

/*!
 *  \brief 开/关换补光灯状态
 *  \return 返回BOOL值。返回YES则换补光灯是打开状态，NO则是关闭状态。
 *  \sa toggleFlash:
 */
- (BOOL)isFlashOn;

/*!
 *  \brief 设置曝光补偿
 *  \param exposureBias 曝光补偿值
 *  \sa getExposureBias
 */
- (void)setExposureBias:(float)exposureBias;

/*!
 *  \brief 获取曝光补偿
 *  \return 返回曝光补偿值
 *  \sa setExposureBias:
 */
- (float)getExposureBias;

/*!
 *  \brief 给采集追加一个内建视频特效
 *  \param videoFxName 视频特效名。获取视频特效名称，请参见[getAllBuiltinCaptureVideoFxNames()] (@ref getAllBuiltinCaptureVideoFxNames)或[内建特效名称列表] (\ref FxNameList.md)。
 *  \return 返回追加的内建视频特效对象
 *  \sa insertBuiltinCaptureVideoFx:withInsertPosition:
 */
- (NvsCaptureVideoFx *)appendBuiltinCaptureVideoFx:(NSString *)videoFxName;

/*!
 *  \brief 给采集插入一个内建视频特效
 *  \param videoFxName 视频特效名。获取视频特效名称，请参见[getAllBuiltinCaptureVideoFxNames()] (@ref getAllBuiltinCaptureVideoFxNames)或[内建特效名称列表] (\ref FxNameList.md)。
 *  \param insertPosition 插入位置
 *  \return 返回插入的内建视频特效对象
 *  \sa appendBuiltinCaptureVideoFx:
 */
- (NvsCaptureVideoFx *)insertBuiltinCaptureVideoFx:(NSString *)videoFxName withInsertPosition:(unsigned int)insertPosition;

/*!
 *  \brief 给采集追加一个包裹视频特效
 *  \param videoFxPackageId 视频特效包裹ID
 *  \return 返回追加的包裹视频特效对象
 *  \sa insertPackagedCaptureVideoFx:withInsertPosition:
 */
- (NvsCaptureVideoFx *)appendPackagedCaptureVideoFx:(NSString *)videoFxPackageId;

/*!
 *  \brief 给采集插入一个包裹视频特效
 *  \param videoFxPackageId 视频特效包裹ID
 *  \param insertPosition 插入位置
 *  \return 返回插入的包裹视频特效对象
 *  \sa appendPackagedCaptureVideoFx:
 */
- (NvsCaptureVideoFx *)insertPackagedCaptureVideoFx:(NSString *)videoFxPackageId withInsertPosition:(unsigned int)insertPosition;

/*!
 *  \brief 给采集追加一个美颜视频特效
 *  \return 返回追加的美颜视频特效对象
 *  \sa insertBeautyCaptureVideoFx:
 */
- (NvsCaptureVideoFx *)appendBeautyCaptureVideoFx;

/*!
 *  \brief 给采集插入一个美颜视频特效
 *  \param insertPosition 插入位置
 *  \return 返回插入的美颜视频特效对象
 *  \sa appendBeautyCaptureVideoFx:
 */
- (NvsCaptureVideoFx *)insertBeautyCaptureVideoFx:(unsigned int)insertPosition;

/*!
 *  \brief 对采集的视频移除特定索引值的采集视频特效
 *  \param captureVideoFxIndex 视频特效索引
 *  \return 返回BOOL值。返回YES则移除成功，NO则失败
 *  \sa appendBuiltinCaptureVideoFx:
 *  \sa appendPackagedCaptureVideoFx:
 *  \sa appendBeautyCaptureVideoFx
 */
- (BOOL)removeCaptureVideoFx:(unsigned int)captureVideoFxIndex;

/*!
 *  \brief 移除所有采集视频特效
 *  \sa removeCaptureVideoFx:
 *  \sa getCaptureVideoFxCount
 */
- (void)removeAllCaptureVideoFx;

/*!
 *  \brief 获得采集视频特效的数量
 *  \return 返回视频特效数量
 */
- (unsigned int)getCaptureVideoFxCount;

/*!
 *  \brief 获得采集视频特效的对象
 *  \param captureVideoFxIndex 视频特效索引
 *  \return 返回视频特效对象
 *  \sa removeCaptureVideoFx:
 */
- (NvsCaptureVideoFx *)getCaptureVideoFxByIndex:(unsigned int)captureVideoFxIndex;

/*!
 *  \brief 对采集设备应用拍摄场景资源包
 *  \param captureSceneId 拍摄场景资源包的ID
 *  \return 返回BOOL值。值为YES则应用成功，NO则失败。
 *  \since 1.2.0
 *  \sa getCurrentCaptureSceneId
 *  \sa removeCurrentCaptureScene
 */
- (BOOL)applyCaptureScene:(NSString *)captureSceneId;

/*!
 *  \brief 取得当前拍摄场景资源包的ID
 *  \return 当前拍摄场景资源包的ID字符串，返回nil表示当前没有拍摄场景资源包
 *  \since 1.2.0
 *  \sa applyCaptureScene:
 *  \sa removeCurrentCaptureScene
 */
- (NSString *)getCurrentCaptureSceneId;

/*!
 *  \brief 移除当前拍摄场景
 *  \since 1.2.0
 *  \sa applyCaptureScene:
 *  \sa getCurrentCaptureSceneId
 */
- (void)removeCurrentCaptureScene;

/*!
 *  \brief 启动录制采集设备信号
 *  \param outputFilePath 录制文件的路径。注意: 目前只支持输出.mov格式的文件
 *  \return 返回BOOL值。返回YES则启动录制成功，NO则启动失败。
 *  \sa stopRecording
 */
- (BOOL)startRecording:(NSString *)outputFilePath;

/*!
 *  \brief 启动采集设备的录制，录制的内容包含所有的特效处理效果。注意：如果特效处理过于复杂
 *         可能会导致录制的视频丢帧，所以使用这个方法一定要慎重，要确保特效的处理对于当前
 *         手机是完全可以实时处理的。
 *  \param outputFilePath 录制文件的路径
 *  \return 返回BOOL值。返回YES则启动录制成功，NO则启动失败。
 *  \sa stopRecording
 */
- (BOOL)startRecordingWithFx:(NSString *)outputFilePath;

/*!
 *  \brief 结束录制采集设备信号
 *  \sa startRecording:
 */
- (void)stopRecording;

/*!
 *  \brief 获取全部内嵌视频特效名称
 *  \return 返回包含所有内嵌的视频特效名称的数组对象
 *  \sa getAllBuiltinAudioFxNames
 */
- (NSArray *)getAllBuiltinVideoFxNames;

/*!
 *  \brief 获取全部内嵌音频特效名称
 *  \return 返回包含所有内嵌的音频特效名称的数组对象
 *  \sa getAllBuiltinVideoFxNames
 */
- (NSArray *)getAllBuiltinAudioFxNames;

/*!
 *  \brief 获取全部内嵌视频转场名称
 *  \return 返回包含所有内嵌的视频转场名称的数组对象
    \sa getAllBuiltinCaptureVideoFxNames
    \sa getBeautyVideoFxName
    \sa getDefaultVideoTransitionName
 */
- (NSArray *)getAllBuiltinVideoTransitionNames;

/*!
 *  \brief 获取全部内嵌采集视频特效名称
 *  \return 返回包含所有内嵌的采集视频特效名称的数组对象
 *  \sa getBeautyVideoFxName
 *  \sa getAllBuiltinVideoFxNames
 */
- (NSArray *)getAllBuiltinCaptureVideoFxNames;

/*!
 *  \brief 获得美颜的视频特效名称
 *  \return 返回包含所有美颜视频特效名称的数组对象
    \sa getAllBuiltinVideoFxNames
    \sa getAllBuiltinCaptureVideoFxNames
 */
- (NSString *)getBeautyVideoFxName;

/*!
 *  \brief 获得默认视频转场名称
 *  \return 返回表示默认转场名称的字符串
 *  \sa getAllBuiltinVideoTransitionNames
 */
- (NSString *)getDefaultVideoTransitionName;

/*!
 *  \brief 获取视频特效描述
 *  \param fxName 视频特效名称
 *  \return 返回视频特效描述的对象
 *  \sa getAudioFxDescription:
 */
- (NvsFxDescription *)getVideoFxDescription:(NSString *)fxName;

/*!
 *  \brief 获取音频特效描述
 *  \param fxName 音频特效名称
 *  \return 返回音频特效描述的对象
 *  \sa getVideoFxDescription:
 */
- (NvsFxDescription *)getAudioFxDescription:(NSString *)fxName;

/*!
 *  \brief 创建视频帧提取对象
 *  \param videoFilePath 原始视频文件路径
 *  \return 返回NvsVideoFrameRetriever对象，表示视频帧提取对象
 *  \since 1.2.0
 */
- (NvsVideoFrameRetriever *)createVideoFrameRetriever:(NSString *)videoFilePath;

@end

/*!
 *  \brief 采集设备能力描述
 *
 *  定义采集设备的相关属性，包含自动聚焦，自动曝光，缩放等
 */
@interface NvsCaptureDeviceCapability : NSObject

@property (readonly) BOOL supportAutoFocus;      //!< \if ENGLISH \else 是否支持自动聚焦 \endif
@property (readonly) BOOL supportAutoExposure;   //!< \if ENGLISH \else 是否支持自动曝光 \endif
@property (readonly) BOOL supportZoom;           //!< \if ENGLISH \else 是否支持缩放 \endif
@property (readonly) float maxZoomFactor;        //!< \if ENGLISH \else 最大缩放比例 \endif
@property (readonly) BOOL supportFlash;          //!< \if ENGLISH \else 是否支持换补灯光 \endif
@property (readonly) BOOL supportExposureBias;   //!< \if ENGLISH \else 是否支持曝光补偿 \endif
@property (readonly) float minExposureBias;      //!< \if ENGLISH \else 最小曝光补偿系数 \endif
@property (readonly) float maxExposureBias;      //!< \if ENGLISH \else 最大曝光补偿系数 \endif

@end

