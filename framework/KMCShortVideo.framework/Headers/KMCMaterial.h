//
//  KMCMaterial.h
//  KMCShortVideo
//
//  Created by ksyun on 2017/6/16.
//  Copyright © 2017年 ksyun. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface KMCMaterial : NSObject
/**
 *  MaterialID
 */
@property (nonatomic , copy) NSString *strID;
/**
 *  缩略图地址
 */
@property (nonatomic , copy) NSString *strThumbnailURL;
/**
 *  缩略图名称
 */
@property (nonatomic , copy) NSString *strThumbnailName;
/**
 *  素材地址
 */
@property (nonatomic , copy) NSString *strMaterialURL;
/**
 *  素材名称
 */
@property (nonatomic , copy) NSString *strName;
/**
 *  授权文件地址
 */
@property (nonatomic , copy) NSString * licenseURL;
/**
 *  素材类别
 */
@property (nonatomic , copy) NSString *strType;

@end
