//
//  KMCShortVideo.h
//  KMCShortVideo
//
//  Created by ksyun on 2017/6/14.
//  Copyright © 2017年 ksyun. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "NvsLiveWindow.h"
#import "NvsStreamingContext.h"
#import "KMCMaterial.h"
#import <AVFoundation/AVFoundation.h>
#import <Photos/Photos.h>

typedef enum : NSUInteger {
    /**
     错误参数
     */
    AUTH_ERROR_WRONG_PARAMETER = 1001,
    /**
     token不匹配
     */
    AUTH_ERROR_TOKEN_NOT_MATCHED = 1002,
    /**
     token无效
     */
    AUTH_ERROR_TOKEN_NOT_VALID = 1003,
    /**
     未知错误
     */
    AUTH_ERROR_KMCS_ERROR_UNKONWN = 1004,
    /**
     第三方鉴权错误
     */
    AUTHORIZE_ERROR_FACTORY_ERROR = 1005,
    /**
     内部服务器错误
     */
    AUTHORIZE_SERVER_ERROR = 1006,
    /**
     token过期
     */
    AUTHORIZE_TOKEN_EXPIRE = 1007,
    /**
     服务器异常
     */
    AUTHORIZE_SERVICE_EXCEPTION = 1008
} AuthorizeError;

typedef NS_ENUM(NSInteger, ResourceType) {
    Type_Theme,
    Type_Music,
    Type_Filter
};

typedef enum {
    KMCCompileVideoResolutionGrade360 = 0, //!< \if ENGLISH \else 输出高度360像素 \endif
    KMCCompileVideoResolutionGrade480,     //!< \if ENGLISH \else 输出高度480像素 \endif
    KMCCompileVideoResolutionGrade720,     //!< \if ENGLISH \else 输出高度720像素 \endif
    KMCCompileVideoResolutionGrade1080     //!< \if ENGLISH \else 输出高度1080像素 \endif
} KMCCompileVideoResolutionGrade;

/*!
 *  \brief 生成视频文件的码率级别
 */
typedef enum {
    KMCCompileBitrateGradeLow = 0,          //!< \if ENGLISH \else 低码率 \endif
    KMCCompileBitrateGradeMedium,           //!< \if ENGLISH \else 中等码率 \endif
    KMCCompileBitrateGradeHigh              //!< \if ENGLISH \else 高码率 \endif
} KMCCompileVideoBitrateGrade;

@protocol KMCShortVideoDelegate <NSObject>

- (void)didPlaybackEOF;

/*!
 *  \brief 生成视频文件进度
 *  \param progress 进度值
 */
- (void)didCompileProgress:(int)progress;

/*!
 *  \brief 生成视频文件完成
 */
- (void)didCompileFinished:(NSString *)outputFilePath;

/*!
 *  \brief 生成视频文件失败
 */
- (void)didCompileFailed;

@end

@interface KMCShortVideo: NSObject

/**
 @discuss 申请得到的tokeID
 @param completeSuccess 完成回调
 @param completeFailure 失败回调
 */
+ (void)authorizeWithTokeID:(NSString *)tokeID
                 onSuccess:(void (^)(void))completeSuccess
                 onFailure:(void (^)(AuthorizeError iErrorCode))completeFailure;


- (BOOL)configWithWindow:(NvsLiveWindow *)window
         videoResolution:(NvsVideoResolution*)videoResolution
                videoFps:(NvsRational *)videoFps
         audioResolution:(NvsAudioResolution*)audioResolution;

@property(nonatomic,weak) id<KMCShortVideoDelegate> delegate;

-(void)remove;
#pragma mark - 短视频操作
/**
 @discuss 从相册添加短视频
 @param asset 单个相册资源
 @param index 插入位置
 */
- (BOOL)insertVideoClip:(PHAsset *)asset
                atIndex:(int)index;
/**
 @discuss 从相册删除短视频
 @param index 插入位置
 */
- (BOOL)removeVideoClip:(int)index;

/**
 @discuss 短视频Seek
 @param time seek的时间点
 */
-(BOOL)seek:(float)time;
/**
 @discuss 短视频播放
 @param startTime 开始播放的时间点
 @param endTime 结束播放的时间点
 */
-(BOOL)playFrom:(float)startTime
             To:(float)endTime;
/**
 @discuss 停止短视频播放
 */
-(void)stopPlay;

#pragma mark - 主题
/**
 @discuss 设置主题封面文字
 */
-(void)setThemeTitleCaptionText:(NSString *)text;
#pragma mark - 素材操作
/**
 @discuss 获取 Material 索引列表
 @param type 素材列表类型
 @param completeSuccess 获取素材列表成功
 @param completeFailure 获取素材列表失败 , iErrorCode 错误码 , strMessage 错误描述 .
 */
- (void)fetchThemeMaterialsWithType:(ResourceType)type
                          OnSuccess:(void (^)(NSArray *))completeSuccess
                          onFailure:(void (^)(int iErrorCode , NSString *strMessage))completeFailure;

/**
 @discuss 下载素材
 */
- (void)downloadMeterial:(KMCMaterial *) meterial
               onSuccess:(void (^)(void))completeSuccess
               onFailure:(void (^)(int iErrorCode , NSString *strMessage))completeFailure
              onProgress:(void (^)(float fProgress , int64_t iSize))processingCallBack;
/**
 @discuss 应用素材，请确保该素材已经下载完成
 @param material 素材索引
 */
-(BOOL)applyMaterial:(KMCMaterial *)material;
/**
 @discuss 关闭素材，请确保该素材已经下载完成
 */
-(void)removeMaterial:(KMCMaterial *) meterial;

#pragma mark - 短视频信息
/**
 @discuss 短视频时长,单位微妙
 */
@property (assign,nonatomic) int64_t duration;
/**
 @discuss 短视频当前播放位置,单位微妙
 */
@property (assign,nonatomic) int64_t curPosition;
/**
 @discuss 短视频当前状态
 */
@property (assign,nonatomic) NvsStreamingEngineState state;

#pragma mark - 单个视频操作
/**
 @discuss 裁剪trimin
 @param index 当前视频的索引值
 
 */
- (void)changeClip:(int)index
       TrimInPoint:(CGFloat)point;
/**
 @discuss 裁剪trimOut
 @param index 当前视频的索引值
 
 */
- (void)changeClip:(int)index
      TrimOutPoint:(CGFloat)point;
/**
 @discuss 获得视频速度
 @param index 当前视频的索引值
 */
- (double)getSpeed:(int)index;
/**
 @discuss 改变视频速度
 @param index 当前视频的索引值
 */
- (void)changeClip:(int)index
             Speed:(double)newSpeed;
/**
 @discuss 获取亮度信息
 @param index 当前视频的索引值
 */
- (float)getBright:(int)index;
/**
 @discuss 设置亮度信息
 @param index 当前视频的索引值
 */
- (void)changeClip:(int)index
            bright:(float)bright;
/**
 @discuss 获取对比度信息
 @param index 当前视频的索引值
 */
- (float)getContrast:(int)index;
/**
 @discuss 设置对比度信息
 @param index 当前视频的索引值
 */
- (void)changeClip:(int)index
          contrast:(float)contrast;
/**
 @discuss 获取饱和度信息
 @param index 当前视频的索引值
 */
- (float)getSaturation:(int)index;
/**
 @discuss 设置饱和度信息
 @param index 当前视频的索引值
 */
- (void)changeClip:(int)index
        saturation:(float)saturation;
/**
 @discuss 获取旋转信息
 @param index 当前视频的索引值
 */
- (float)getRotate:(int)index;
/**
 @discuss 设置旋转信息
 @param index 当前视频的索引值
 */
- (void)changeClip:(int)index
            rotate:(float)rotate;

/**
 @discuss 获取x轴缩放信息
 @param index 当前视频的索引值
 */
- (float)getXScale:(int)index;
/**
 @discuss 设置x轴缩放信息
 @param index 当前视频的索引值
 */
- (void)changeClip:(int)index
            xScale:(float)xScale;
/**
 @discuss 获取Y轴缩放信息
 @param index 当前视频的索引值
 */
- (float)getYScale:(int)index;
/**
 @discuss 设置Y轴缩放信息
 @param index 当前视频的索引值
 */
- (void)changeClip:(int)index
            yScale:(float)yScale;
#pragma mark - 生成
- (BOOL)compileFile:(NSString *)outputFilePath
    resolutionGrade:(KMCCompileVideoResolutionGrade)resolution
       bitrateGrade:(KMCCompileVideoBitrateGrade)bitrate;

@end

