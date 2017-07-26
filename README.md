# -KMCShortVideoDemo_IOS
美摄短视频IOS
## 项目背景
金山魔方是一个多媒体能力提供平台，通过统一接入API、统一鉴权、统一计费等多种手段，降低客户接入多媒体处理能力的代价，提供多媒体能力供应商的效率

## 安装
KMCShortVideo.framework 直接集成

## SDK包总体介绍
+ KMCMaterial 素材类(主题、音乐、滤镜)
+ KMCShortVideo为短视频编辑类


## SDK使用指南
#### 1. KMCShortVideo
+ **鉴权**
  本sdk包采用鉴权加密方式，需要通过商务渠道拿到授权的token信息，方可以使用，具体请咨询商务。
鉴权函数如下，其中auth为ak信息，date为过期时间。
```objectivec
(void)authorizeWithTokeID:(NSString *)tokeID
                onSuccess:(void (^)(void))completeSuccess
                onFailure:(void (^)(AuthorizeError iErrorCode))completeFailure;
```

+ **初始化**
```objectivec
(BOOL)configWithWindow:(NvsLiveWindow *)window
         videoResolution:(NvsVideoResolution*)videoResolution
                videoFps:(NvsRational *)videoFps
         audioResolution:(NvsAudioResolution*)audioResolution;
```
+ **插入短视频片段**
```objectivec
/**
 @discuss 从相册添加短视频
 @param asset 单个相册资源
 @param index 插入位置
 */
- (BOOL)insertVideoClip:(PHAsset *)asset
                atIndex:(int)index;
```
+ **移除短视频片段**
```objectivec 
/**
 @discuss 从相册删除短视频
 @param index 插入位置
 */
- (BOOL)removeVideoClip:(int)index;
```
+ **定位短视频**
```objectivec 
/**
 @discuss 短视频Seek
 @param time seek的时间点
 */
-(BOOL)seek:(float)time;
```
+ **播放短视频**
```objectivec 
/**
 @discuss 短视频播放
 @param startTime 开始播放的时间点
 @param endTime 结束播放的时间点
 */
-(BOOL)playFrom:(float)startTime
             To:(float)endTime;
```
+ **停止短视频播放**
```objectivec 
/**
 @discuss 停止短视频播放
 */
-(void)stopPlay;
```
+ **更换主题**
```objectivec 
/**
 @discuss 设置主题封面文字
 */
-(void)setThemeTitleCaptionText:(NSString *)text;
```
+ **获取素材**
```objectivec 
/**
 @discuss 获取 Material 索引列表
 @param type 素材列表类型
 @param completeSuccess 获取素材列表成功
 @param completeFailure 获取素材列表失败 , iErrorCode 错误码 , strMessage 错误描述 .
 */
- (void)fetchThemeMaterialsWithType:(ResourceType)type
                          OnSuccess:(void (^)(NSArray *))completeSuccess
                          onFailure:(void (^)(int iErrorCode , NSString *strMessage))completeFailure;
```
+ **下载素材**
```objectivec 
- (void)downloadMeterial:(KMCMaterial *) meterial
               onSuccess:(void (^)(void))completeSuccess
               onFailure:(void (^)(int iErrorCode , NSString *strMessage))completeFailure
              onProgress:(void (^)(float fProgress , int64_t iSize))processingCallBack;
```
+ **应用素材**
```objectivec 
/**
 @discuss 应用素材，请确保该素材已经下载完成
 @param material 素材索引
 */
-(BOOL)applyMaterial:(KMCMaterial *)material;
```
+ **关闭素材**
```objectivec 
/**
 @discuss 关闭素材，请确保该素材已经下载完成
 */
-(void)removeMaterial:(KMCMaterial *) meterial;
```
+ **生成文件**
```objectivec 
- (BOOL)compileFile:(NSString *)outputFilePath
    resolutionGrade:(KMCCompileVideoResolutionGrade)resolution
       bitrateGrade:(KMCCompileVideoBitrateGrade)bitrate;
```








## 接入流程
![金山魔方接入流程](https://raw.githubusercontent.com/wiki/ksvcmc/KMCSTFilter_Android/all.jpg "金山魔方接入流程")
## 接入步骤  
1.登录[金山云控制台]( https://console.ksyun.com)，选择视频服务-金山魔方
![步骤1](https://raw.githubusercontent.com/wiki/ksvcmc/KMCSTFilter_Android/step1.png "接入步骤1")

2.在金山魔方控制台中挑选所需服务。
![步骤2](https://raw.githubusercontent.com/wiki/ksvcmc/KMCSTFilter_Android/step2.png "接入步骤2")

3.点击申请试用，填写申请资料。
![步骤3](https://raw.githubusercontent.com/wiki/ksvcmc/KMCSTFilter_Android/step3.png "接入步骤3")

![步骤4](https://raw.githubusercontent.com/wiki/ksvcmc/KMCSTFilter_Android/step4.png "接入步骤4")

4.待申请审核通过后，金山云注册时的邮箱会收到邮件及试用token。
![步骤5](https://raw.githubusercontent.com/wiki/ksvcmc/KMCSTFilter_Android/step5.png "接入步骤5")

5.下载安卓/iOS版本的SDK集成进项目。
![步骤6](https://raw.githubusercontent.com/wiki/ksvcmc/KMCSTFilter_Android/step6.png "接入步骤6")

6.参照文档和DEMO填写TOKEN，就可以Run通项目了。
7.试用中或试用结束后，有意愿购买该服务可以与我们的商务人员联系购买。
（商务Email:KSC-VBU-KMC@kingsoft.com）
## 反馈与建议  
主页：[金山魔方](https://docs.ksyun.com/read/latest/142/_book/index.html)  
邮箱：ksc-vbu-kmc-dev@kingsoft.com  
QQ讨论群：574179720 [视频云技术交流群]

