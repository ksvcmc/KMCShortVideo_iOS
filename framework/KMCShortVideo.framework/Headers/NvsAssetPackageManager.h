//================================================================================
//
// (c) Copyright China Digital Video (Beijing) Limited, 2017. All rights reserved.
//
// This code and information is provided "as is" without warranty of any kind,
// either expressed or implied, including but not limited to the implied
// warranties of merchantability and/or fitness for a particular purpose.
//
//--------------------------------------------------------------------------------
//   Birth Date:    Jan 23. 2017
//   Author:        NewAuto video team
//================================================================================
#pragma once

#import <Foundation/Foundation.h>

/*!
 *  \brief 资源包类型
 */
typedef enum
{
    NvsAssetPackageType_VideoFx = 0,         //!< \if ENGLISH \else 视频特效 \endif
    NvsAssetPackageType_VideoTransition,     //!< \if ENGLISH \else 视频转场 \endif
    NvsAssetPackageType_CaptionStyle,        //!< \if ENGLISH \else 字幕样式 \endif
    NvsAssetPackageType_AnimatedSticker,     //!< \if ENGLISH \else 动画贴纸 \endif
    NvsAssetPackageType_Theme,               //!< \if ENGLISH \else 主题 \endif
    NvsAssetPackageType_CaptureScene         //!< \if ENGLISH \else 拍摄场景 \endif
} NvsAssetPackageType;

/*!
 *  \brief 资源包状态
 */
typedef enum
{
    NvsAssetPackageStatus_NotInstalled = 0,  //!< \if ENGLISH brief enum description \else 未安装 \endif
    NvsAssetPackageStatus_Installing,        //!< \if ENGLISH brief enum description \else 正在安装 \endif
    NvsAssetPackageStatus_Ready,             //!< \if ENGLISH brief enum description \else 准备 \endif
    NvsAssetPackageStatus_Upgrading          //!< \if ENGLISH brief enum description \else 正在升级 \endif
} NvsAssetPackageStatus;

/*!
 *  \brief 资源包管理器错误类别，NvsAssetPackageManagerError值为NvsAssetPackageManagerError_NoError表示安装成功，其他则安装失败
 */
typedef enum
{
    NvsAssetPackageManagerError_NoError = 0,          //!< \if ENGLISH brief enum description \else 安装成功 \endif
    NvsAssetPackageManagerError_Name,                 //!< \if ENGLISH brief enum description \else 名称错误 \endif
    NvsAssetPackageManagerError_AlreadyInstalled,     //!< \if ENGLISH brief enum description \else 已经安装 \endif
    NvsAssetPackageManagerError_WorkingInProgress,    //!< \if ENGLISH brief enum description \else 安装或升级正在进行中 \endif
    NvsAssetPackageManagerError_NotInstalled,         //!< \if ENGLISH brief enum description \else 尚未安装 \endif
    NvsAssetPackageManagerError_ImproperStatus,       //!< \if ENGLISH brief enum description \else 不正确状态 \endif
    NvsAssetPackageManagerError_Decompression,        //!< \if ENGLISH brief enum description \else 解压错误 \endif
    NvsAssetPackageManagerError_InvalidPackage,       //!< \if ENGLISH brief enum description \else 无效包 \endif
    NvsAssetPackageManagerError_AssetType,            //!< \if ENGLISH brief enum description \else 资源类型错误 \endif
    NvsAssetPackageManagerError_Permission,           //!< \if ENGLISH brief enum description \else 许可错误 \endif
    NvsAssetPackageManagerError_MetaContent,          //!< \if ENGLISH brief enum description \else 元内容错误 \endif
    NvsAssetPackageManagerError_SdkVersion,           //!< \if ENGLISH brief enum description \else Sdk版本错误 \endif
    NvsAssetPackageManagerError_UpgradeVersion,       //!< \if ENGLISH brief enum description \else 升级版本错误 \endif
    NvsAssetPackageManagerError_IO,                   //!< \if ENGLISH brief enum description \else 输入输出错误 \endif
    NvsAssetPackageManagerError_Resource              //!< \if ENGLISH brief enum description \else 资源错误 \endif
} NvsAssetPackageManagerError;


@protocol NvsAssetPackageManagerDelegate <NSObject>
@optional

/*!
 *  \brief 通知资源包的安装过程结束 
 *  \param assetPackageId 安装资源包ID
 *  \param assetPackageFilePath 安装资源包的文件路径
 *  \param assetPackageType 安装资源包的类型
 *  \param error 返回值，返回安装过程的错误值。值为NvsAssetPackageManagerError_NoError表示安装成功，否则表示安装失败
 *  \sa didFinishAssetPackageUpgrading:filePath:type:error:
 */
- (void)didFinishAssetPackageInstallation:(NSString *)assetPackageId filePath:(NSString *)assetPackageFilePath type:(NvsAssetPackageType)assetPackageType error:(NvsAssetPackageManagerError)error;

/*!
 *  \brief 通知资源包的升级过程结束
 *  \param assetPackageId 升级资源包ID
 *  \param assetPackageFilePath 升级资源包的文件路径
 *  \param assetPackageType 升级资源包的类型
 *  \param error 返回值，返回升级过程的错误值。值为NvsAssetPackageManagerError_NoError表示安装成功，否则表示安装失败
 *  \sa didFinishAssetPackageInstallation:filePath:type:error:
 */
- (void)didFinishAssetPackageUpgrading:(NSString *)assetPackageId filePath:(NSString *)assetPackageFilePath type:(NvsAssetPackageType)assetPackageType error:(NvsAssetPackageManagerError)error;

@end

/*!
 *  \brief 资源包管理器，管理视频场景中的资源包

 *   在SDK开发过中，资源包管理器统一对需要的各种特技资源包包括字幕，主题，动画贴纸等进行相应的安装，升级，卸载等操作。在安装，升级，卸载时，出现差错都会有相应的错误提示类型，以便快速定位和解决错误。
 */
@interface NvsAssetPackageManager : NSObject

@property (nonatomic, retain) id<NvsAssetPackageManagerDelegate> delegate;

/*!
 *  \brief 从资源包的文件路径获得资源包ID
 *  \param assetPackageFilePath 资源包的文件路径
 *  \return 返回表示资源包ID的字符串
 */
- (NSString *)getAssetPackageIdFromAssetPackageFilePath:(NSString *)assetPackageFilePath;

/*!
 *  \brief 安装资源包
 *  \param assetPackageFilePath 待安装资源包的文件路径
 *  \param licenseFilePath 待安装资源包的授权文件路径
 *  \param type 待安装资源包的类型
 *  \param synchronous 是否同步安装。值为YES则安装过程会阻塞当前线程直到安装成功或者失败，NO则安装过程的结果通过delegate异步通知（但也在当前线程通知）。
 *  \param assetPackageId 返回值，返回该资源包ID。
 *  \return 返回一种资源包的错误类型。NvsAssetPackageManagerError_NoError: 表示安装成功（只有同步安装才可能返回这个)，任何其它返回值都表示安装错误。
 *  \sa upgradeAssetPackage:license:type:sync:assetPackageId:
 *  \sa uninstallAssetPackage:type:
 */
// 安装asset package
// @assetPackageFilePath: 待安装asset package的文件路径
// @licenseFilePath: 待安装asset package的授权文件
// @type: 待安装asset package的类型
// @synchronous: 是否同步安装
//               YES: 安装过程会阻塞当前线程直到安装成功或者失败
//               NO: 安装过程的结果通过delegate异步通知（但也在当前线程通知）
// @assetPackageId: 返回该asset package的标识符
//
// 返回值为一个错误号
// NvsAssetPackageManagerError_NoError: 表示安装成功（只有同步安装才可能返回这个值）
// NvsAssetPackageManagerError_AlreadyInstalled: 表示当前asset package已经安装
// NvsAssetPackageManagerError_WorkingInProgress: 表示安装正在进行中（只有异步安装才可能返回这个值）
// 任何其它返回值都表示安装错误
//
- (NvsAssetPackageManagerError)installAssetPackage:(NSString *)assetPackageFilePath license:(NSString *)licenseFilePath type:(NvsAssetPackageType)type sync:(BOOL)synchronous assetPackageId:(NSMutableString *)assetPackageId;

/*!
 *  \brief 升级资源包
 *  \param assetPackageFilePath 待升级资源包的文件路径
 *  \param licenseFilePath 待升级资源包的授权文件路径
 *  \param type 待升级资源包的类型
 *  \param synchronous 是否同步升级。值为YES则升级过程会阻塞当前线程直到升级成功或者失败，NO则升级过程的结果通过delegate异步通知（但也在当前线程通知）。
 *  \param assetPackageId 返回值，返回该资源包ID
 *  \return 返回一种资源包的错误类型。值为NvsAssetPackageManagerError_NoError表示升级成功（只有同步升级才可能返回这个)，任何其它返回值都表示升级错误
 *  \sa installAssetPackage:license:type:sync:assetPackageId:
 *  \sa uninstallAssetPackage:type:
 */
// 升级asset package
// @assetPackageFilePath: 待升级asset package的文件路径
// @licenseFilePath: 待升级asset package的授权文件
// @type: 待升级asset package的类型
// @synchronous: 是否同步升级
//               YES: 升级过程会阻塞当前线程直到升级成功或者失败
//               NO: 升级过程的结果通过delegate异步通知（但也在当前线程通知）
// @assetPackageId: 返回该asset package的标识符
//
// 返回值为一个错误号
// NvsAssetPackageManagerError_NoError: 表示升级成功（只有同步升级才可能返回这个值）
// NvsAssetPackageManagerError_NotInstalled: 表示当前asset package尚未安装
// NvsAssetPackageManagerError_WorkingInProgress: 表示升级正在进行中（只有异步升级才可能返回这个值）
// 任何其它返回值都表示升级错误
//
- (NvsAssetPackageManagerError)upgradeAssetPackage:(NSString *)assetPackageFilePath license:(NSString *)licenseFilePath type:(NvsAssetPackageType)type sync:(BOOL)synchronous assetPackageId:(NSMutableString *)assetPackageId;

/*!
 *  \brief 卸载资源包
 *  \param assetPackageId 待卸载资源包ID
 *  \param type 待卸载资源包的类型
 *  \return 返回表示资源包的一个错误类型。返回NvsAssetPackageManagerError_NoError表示卸载成功，其它则卸载失败
 *  \sa installAssetPackage:license:type:sync:assetPackageId:
 *  \sa upgradeAssetPackage:license:type:sync:assetPackageId:
 */
- (NvsAssetPackageManagerError)uninstallAssetPackage:(NSString *)assetPackageId type:(NvsAssetPackageType)type;

/*!
 *  \brief 获取资源包的当前状态
 *  \param assetPackageId 待查询状态资源包ID
 *  \param type 待查询状态资源包的类型
 *  \return 返回资源包的当前状态值 
 */
- (NvsAssetPackageStatus)getAssetPackageStatus:(NSString *)assetPackageId type:(NvsAssetPackageType)type;

/*!
 *  \brief 获取已安装资源包的版本号
 *  \param assetPackageId 待查询状态资源包ID
 *  \param type 待查询状态资源包的类型
 *  \return 返回资源包的版本号。如果该资源包未安装，则返回1。
 */
- (int)getAssetPackageVersion:(NSString *)assetPackageId type:(NvsAssetPackageType)type;

/*!
 *  \brief 获取某个类型的资源包列表
 *  \param type 资源包类型
 *  \return 返回NSArray数组对象，表示某个类型下资源包的的列表。列表里每个NSString元素都是一个资源包ID。
 */
// 获取某个类型的asset package的列表
// @type: asset package的类型
// 返回值为一个NSString类型的NSArray，每一个NSString都是一个资源包的标识符
- (NSArray *)getAssetPackageListOfType:(NvsAssetPackageType)type;

@end

