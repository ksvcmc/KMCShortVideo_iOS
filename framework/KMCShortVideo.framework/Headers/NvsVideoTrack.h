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

/*! \file NvsVideoTrack.h 
*/
#pragma once

#import "NvsTrack.h"

@class NvsVideoClip;
@class NvsVideoTransition;

/*!
    \brief 视频轨道，视频片段的集合

    视频轨道是容纳视频片段的实体，可以添加、插入、删移多个视频片段。视频轨道随着片段的增加不断延展，而片段与片段之间可进行视频转场设置。
    视频轨道添加的视频片段源可以是视频或图片。如果片段源选择的是图片，则图片分辨率不能高于1920 * 1080，否则在Live Window 上渲染不出来。

    注：视频片段的索引都是从0开始。
 */
@interface NvsVideoTrack : NvsTrack

/*!
    \brief 在视频轨道尾部追加片段
    \param filePath 片段路径。对于片段路径方式，请参见[addClip()] (@ref addClip:inPoint:)的参数filePath。
    \return 返回追加的视频片段对象

    示例如下:

    ![] (@ref TrackClip.PNG)
    上图中视频轨道上有三个片段C1、C2、C3, 如果在视频轨道尾部追加一个新的片段C4,实现代码：

            NvsVideoTrack *videoTrack;//videoTrack这里省略创建
            [videoTrack appendClip:filepath];//filepath为C4片段的视频文件路径

    追加后的结果:
    ![] (@ref TrackAppendClip.PNG)
    \warning 此接口会引发流媒体引擎状态跳转到引擎停止状态，具体情况请参见[引擎变化专题] (\ref EngineChange.md)。 
    \sa insertClip:clipIndex:
    \sa getClipWithIndex:
    \sa appendClip:trimIn:trimOut:
 */
- (NvsVideoClip *)appendClip:(NSString *)filePath;

/*!
    \brief 在轨道尾部追加指定长度的片段
    \param filePath 片段路径。对于片段路径方式，请参见[addClip()] (@ref addClip:inPoint:)的参数filePath。
    \param trimIn 片段裁剪入点。
    \param trimOut 片段裁剪出点
    \return 返回追加的视频片段对象

    对于片段裁剪入点与出点的理解，具体请参见[裁剪入点与出点(trimIn and trimOut)] (\ref TrimInOut.md)专题。
    \warning 此接口会引发流媒体引擎状态跳转到引擎停止状态，具体情况请参见[引擎变化专题] (\ref EngineChange.md)。
    \sa appendClip:
    \sa insertClip:clipIndex:
    \sa getClipWithIndex: 
 */
- (NvsVideoClip *)appendClip:(NSString *)filePath trimIn:(int64_t)trimIn trimOut:(int64_t)trimOut;

/*!
     \brief 在视频轨道上指定片段索引处插入片段
     \param filePath 片段路径。对于片段路径方式，请参见[addClip()] (@ref addClip:inPoint:)的参数filePath。
     \param clipIndex 插入后片段索引
     \return 返回插入的视频片段对象

     调用insertClip()执行的是前插入即在clipIndex所表示的片段之前进行插入。示例如下:

     ![] (@ref TrackClip.PNG)
     上图中轨道上有三个视频片段C1、C2、C3，待插入的片段记为C4。如果在C1之前插入,则clipIndex值为0,其它以此类推。相应代码实现如下：

            NvsVideoTrack *videoTrack; //videoTrack这里省略创建
            [videoTrack insertClip:filepath clipIndex:0];//filepath为片段C4的路径,clipIndex取值为[0,clipCount-1]

     插入后结果:
     ![] (@ref TrackInsertClip.PNG)
     \warning 此接口会引发流媒体引擎状态跳转到引擎停止状态，具体情况请参见[引擎变化专题] (\ref EngineChange.md)。
     \sa appendClip:
     \sa getClipWithIndex:
     \sa insertClip:trimIn:trimOut:clipIndex:
 */
- (NvsVideoClip *)insertClip:(NSString *)filePath clipIndex:(unsigned int)clipIndex;

/*!
	 \brief 在轨道上指定片段索引处插入指定长度的片段
     \param filePath 片段路径。对于片段路径方式，请参见[addClip()] (@ref addClip:inPoint:)的参数filePath。
     \param trimIn 片段裁剪入点
     \param trimOut 片段裁剪出点
	 \param clipIndex 插入片段索引
     \return 返回插入的视频片段对象

     示例如下:

     ![] (@ref beforeInsertClip.PNG)
     上图中轨道上有三个视频片段C1、C2、C3，以及待插入的片段C4。C4片段上箭头所指处即为片段裁剪的的入点和出点，裁剪后将对应片段插入到轨道上。注意：裁剪入点和出点值必须在此片段的时长范围里，且裁剪入点值必须小于裁剪出点值。实现代码如下：

            NvsVideoTrack *videoTrack; //videoTrack这里省略创建
            [videoTrack insertClip:filepath trimIn:trimIn trimOut:trimOut clipIndex:0];//filepath为片段C4的路径,trimIn和trimOut为上图C4片段上箭头所指位置处的值，clipIndex取值为[0,clipCount-1]

     插入后结果:
     ![] (@ref TrackInsertClip.PNG)
     \warning 此接口会引发流媒体引擎状态跳转到引擎停止状态，具体情况请参见[引擎变化专题] (\ref EngineChange.md)。
     \sa appendClip:trimIn:trimOut:
     \sa insertClip:clipIndex:
     \sa getClipWithIndex:
 */
- (NvsVideoClip *)insertClip:(NSString *)filePath trimIn:(int64_t)trimIn trimOut:(int64_t)trimOut clipIndex:(unsigned int)clipIndex;

/*!
     \brief 添加片段
     \param filePath 片段路径

     IOS中，对于导入的音视频片段的路径，有四种方式：

     a. 通过ALAssetsLibrary实例导入，片段路径格式如下："assets-library://asset/asset.mov?id=E0723C86-AA47-409C-B4E2-526D7C2AA9B5&ext=mov"；

     b. 通过IPod Library库的MPMediaQuery实例导入，片段路径格式如下："ipod-library://item/item.mp3?id=1217463725835578132"；

     c. 通过沙河路径路径导入，片段路径格式如下："/var/mobile/Containers/Data/Documents/tmp/video20170406101714.mp4"；

     d. IOS 8.0版以后，Photos框架替代ALAssetsLibrary库，通过PHAsset实例导入，片段路径如下："file:///var/mobile/Media/DCIM/100APPLE/IMG_0646.MP4"。
     \param inPoint 片段在时间线上的入点
     \return 返回添加的视频片段对象

     对于片段在时间线上的入点与出点的理解，具体请参见[裁剪入点与出点(trimIn and trimOut)] (\ref TrimInOut.md)专题。
     \warning 此接口会引发流媒体引擎状态跳转到引擎停止状态，具体情况请参见[引擎变化专题] (\ref EngineChange.md)。
     \sa appendClip:
     \sa insertClip:clipIndex:
     \sa addClip:inPoint:trimIn:trimOut:
 */
- (NvsVideoClip *)addClip:(NSString *)filePath inPoint:(int64_t)inPoint;

/*!
     \brief 添加指定长度的片段
     \param filePath 片段路径。对于片段路径方式，请参见[addClip()] (@ref addClip:inPoint:)的参数filePath。
     \param inPoint 片段在时间线上的入点
     \param trimIn 片段裁剪入点
     \param trimOut 片段裁剪出点
     \return 返回添加的视频片段对象

     使用addClip()添加片段时，待添加的片段会在时间线上指定的入点分割当前片段，再从当前指定的入点起，在轨道上按待添加片段的长度删除对应长度的位置里面所包含的片段，然后添加需要添加的片段。如果在对应位置上有空隙，则直接覆盖。

     示例如下:

     ![] (@ref beforeAddClip.PNG)
     如上图，轨道上有三个视频片段C1、C2、C3，以及待添加的片段C4。C4片段上箭头所指处即为片段裁剪的的入点和出点，轨道上箭头所指即为片段在时间线上的入点，裁剪后将对应片段添加到轨道上。代码实现如下：

            NvsVideoTrack *videoTrack; //videoTrack这里省略创建
            [videoTrack addClip:filepath inPoint:inPoint trimIn:trimIn trimOut:trimOut];//filepath为片段C4的路径,inPoint为图中轨道上箭头所指位置的值，trimIn和trimOut为上图C4片段上箭头所指位置处的值

     添加后结果如下：

     ![] (@ref afterAddClip.PNG)
     \warning 此接口会引发流媒体引擎状态跳转到引擎停止状态，具体情况请参见[引擎变化专题] (\ref EngineChange.md)。
     \sa appendClip:trimIn:trimOut:
     \sa insertClip:trimIn:trimOut:clipIndex:
     \sa addClip:inPoint:
 */
- (NvsVideoClip *)addClip:(NSString *)filePath inPoint:(int64_t)inPoint trimIn:(int64_t)trimIn trimOut:(int64_t)trimOut;

/*!
     \brief 通过索引获取片段对象
     \param clipIndex 片段索引。片段索引取值范围:clipIndex的取值范围为[0,clipCount-1]
     \return 返回获取的视频片段对象
     \sa getClipWithTimelinePosition:
     \sa appendClip:
     \sa insertClip:clipIndex:
 */
- (NvsVideoClip *)getClipWithIndex:(unsigned int)clipIndex;

/*!
     \brief 通过时间获取片段对象
     \param timelinePos 时间线上的位置(微秒)
     \return 返回获取的视频片段对象
     \sa getClipWithIndex:
 */
- (NvsVideoClip *)getClipWithTimelinePosition:(int64_t)timelinePos;

/*!
	 \brief  设置内嵌式转场
     \param  srcClipIndex 源片段索引
     \param  transitionName 转场名称。获取视频转场名称，请参见[getAllBuiltinVideoTransitionNames()] (@ref NvsStreamingContext::getAllBuiltinVideoTransitionNames)或[内建特效名称列表] (\ref FxNameList.md)。
     注意：转场名称若设为空字符串，则删除原有转场
     \return 返回设置的视频转场对象。若transitionName设为空字符串(即删除原有转场),返回nil

     示例:

     ![] (@ref Clip.PNG)

     设置视频转场的作用是为了片段与片段间的平缓过渡，避免视频预览时出现跳跃。视频转场必须设置在相互连接的片段间，而在有空隙的片段之间，则不能设置视频转场。
     如上图中轨道上有四个视频片段C1、C、C3、C4,在C1和C2之间可以设置一个内嵌式转场，而C3和C4则不能设置视频转场。实现代码：

           NvsVideoTrack *videoTrack; //videoTrack这里省略创建
           [videoTrack setBuiltinTransition:0 withName:transitionName]; //srcClipIndex取值范围为(1,clipCount-1),transitionName为要设置的转场的名称

     设置转场后:
     ![] (@ref TrackTransition.PNG)
     \warning 此接口会引发流媒体引擎状态跳转到引擎停止状态，具体情况请参见[引擎变化专题] (\ref EngineChange.md)。
     \sa setPackagedTransition:withPackageId:
 */
- (NvsVideoTransition *)setBuiltinTransition:(unsigned int)srcClipIndex withName:(NSString *)transitionName;

/*!
     \brief 设置包裹转场
     \param srcClipIndex 片段索引
     \param packageId 转场资源包ID。若packageId为空，则删除该视频片段处的转场；若packageId设为"theme",则该视频片段处的转场设为当前主题的转场。注意：若无主题，则删除该视频片段处的转场。
     \return 返回设置的视频转场对象
     \warning 此接口会引发流媒体引擎状态跳转到引擎停止状态，具体情况请参见[引擎变化专题] (\ref EngineChange.md)。
     \sa setBuiltinTransition:withName:
 */
- (NvsVideoTransition *)setPackagedTransition:(unsigned int)srcClipIndex withPackageId:(NSString *)packageId;

/*!
     \brief 通过源片段索引获取转场对象
	 \param srcClipIndex 源片段索引
     \return 返回获取的视频转场对象
     \sa setBuiltinTransition:withName:
 */
- (NvsVideoTransition *)getTransitionWithSourceClipIndex:(unsigned int)srcClipIndex;

@end
