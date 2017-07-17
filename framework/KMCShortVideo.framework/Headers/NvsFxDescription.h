//================================================================================
//
// (c) Copyright China Digital Video (Beijing) Limited, 2016. All rights reserved.
//
// This code and information is provided "as is" without warranty of any kind,
// either expressed or implied, including but not limited to the implied
// warranties of merchantability and/or fitness for a particular purpose.
//
//--------------------------------------------------------------------------------
//   Birth Date:    Jan 22. 2017
//   Author:        NewAuto video team
//================================================================================

#pragma once

#import <Foundation/Foundation.h>

/*! \anchor PARAM_TYPE */
/*! @name 特效参数类型 */
//!@{
#define NVS_PARAM_TYPE_INT              @"INT"     
#define NVS_PARAM_TYPE_FLOAT            @"FLOAT"
#define NVS_PARAM_TYPE_BOOL             @"BOOL"
#define NVS_PARAM_TYPE_MENU             @"MENU"
#define NVS_PARAM_TYPE_STRING           @"STRING"
#define NVS_PARAM_TYPE_COLOR            @"COLOR"
#define NVS_PARAM_TYPE_POSITION2D       @"POSITION2D"
#define NVS_PARAM_TYPE_POSITION3D       @"POSITION3D"

//!@}


#define NVS_PARAM_NAME                  @"paramName"  //!< \if ENGLISH \else 特效参数名称 \endif

/*!
 *	\brief 特效参数类型  请参见[PARAM_TYPE] (@ref PARAM_TYPE)
 */
#define NVS_PARAM_TYPE                  @"paramType"

/*! @name 特效参数整数类型的默认值和取值范围 */
//!@{
#define NVS_PARAM_INT_DEF_VAL           @"intDefVal"
#define NVS_PARAM_INT_MIN_VAL           @"intMinVal"
#define NVS_PARAM_INT_MAX_VAL           @"intMaxVal"

//!@}

/*! @name 特效参数浮点数类型的默认值和取值范围 */
//!@{
#define NVS_PARAM_FLOAT_DEF_VAL         @"floatDefVal"
#define NVS_PARAM_FLOAT_MIN_VAL         @"floatMinVal"
#define NVS_PARAM_FLOAT_MAX_VAL         @"floatMaxVal"

//!@}

/*! @name 特效参数布尔值类型的默认值 */
#define NVS_PARAM_BOOL_DEF_VAL          @"boolDefVal"

/*! @name 特效参数颜色值类型的默认值 */
//!@{
#define NVS_PARAM_COLOR_DEF_R           @"colorDefR"
#define NVS_PARAM_COLOR_DEF_G           @"colorDefG"
#define NVS_PARAM_COLOR_DEF_B           @"colorDefB"
#define NVS_PARAM_COLOR_DEF_A           @"colorDefA"

//!@}

/*! @name 特效参数二维坐标的默认值 */
//!@{
#define NVS_PARAM_POSITION2D_DEF_X      @"position2DDefX"
#define NVS_PARAM_POSITION2D_DEF_Y      @"position2DDefY"

//!@}

/*! @name 特效参数三维坐标的默认值 */
//!@{
#define NVS_PARAM_POSITION3D_DEF_X      @"position3DDefX"
#define NVS_PARAM_POSITION3D_DEF_Y      @"position3DDefY"
#define NVS_PARAM_POSITION3D_DEF_Z      @"position3DDefZ"

//!@}
/*! @name 特效字符串参数类型 */
/*! 相关特效字符串参数类型 请参见[NvsFxStringParamType] (@ref NvsFxStringParamType) */
#define NVS_PARAM_STRING_TYPE           @"stringType"
/*! @name 特效字符串参数默认值 */
#define NVS_PARAM_STRING_DEF            @"stringDef"

/*! @name 特效菜单参数默认值 */
#define NVS_PARAM_MENU_DEF_VAL          @"menuDefVal"

/*! @name 特效菜单参数数组 */
#define NVS_PARAM_MENU_ARRAY            @"menuArray"

/*!
 *  \brief 特效字符串参数类型
 */
typedef enum
{
    NvsFxStringParamType_Invalid = -1,     //!< \if ENGLISH \else 无效 \endif
    NvsFxStringParamType_SingleLine = 0,   //!< \if ENGLISH \else 单行 \endif
    NvsFxStringParamType_MultiLine,        //!< \if ENGLISH \else 多行 \endif
    NvsFxStringParamType_FilePath,         //!< \if ENGLISH \else 文件路径 \endif
    NvsFxStringParamType_DirectoryPath,    //!< \if ENGLISH \else 目录路径 \endif
    NvsFxStringParamType_Label             //!< \if ENGLISH \else 标签 \endif
} NvsFxStringParamType;

/*!
    \brief 特效参数描述

    在视频拍摄和编辑时会设置各种不同参数类型的特效，特效参数描述就是专门用来获取各种特效参数值的，以便查看和了解。
*/
@interface NvsFxDescription : NSObject

@property (readonly) NSString *name;    //!< \if ENGLISH \else 特效名称 \endif

/*!
    \brief 获取所有特效参数信息
    \retval (NSArray *) 返回包含所有特效参数列表的数组对象

	详细描述：返回类型(NSArray *) {(NSDictionary *), ...}
	
	NSDictionary*内部结构:

		{
        NVS_PARAM_NAME:               (NSString *)
        NVS_PARAM_TYPE:               (NSString *)
        NVS_PARAM_INT_DEF_VAL:        (NSNumber)
        NVS_PARAM_INT_MIN_VAL:        (NSNumber)
        NVS_PARAM_INT_MAX_VAL:        (NSNumber)
        NVS_PARAM_FLOAT_DEF_VAL:      (NSNumber)
        NVS_PARAM_INT_MIN_VAL:        (NSNumber)
        NVS_PARAM_INT_MAX_VAL:        (NSNumber)
        NVS_PARAM_BOOL_DEF_VAL:       (NSNumber)
        NVS_PARAM_COLOR_DEF_R:        (NSNumber)
        NVS_PARAM_COLOR_DEF_G:        (NSNumber)
        NVS_PARAM_COLOR_DEF_B:        (NSNumber)
        NVS_PARAM_COLOR_DEF_A:        (NSNumber)
        NVS_PARAM_POSITION2D_DEF_X:   (NSNumber)
        NVS_PARAM_POSITION2D_DEF_Y:   (NSNumber)
        NVS_PARAM_POSITION3D_DEF_X:   (NSNumber)
        NVS_PARAM_POSITION3D_DEF_Y:   (NSNumber)
        NVS_PARAM_POSITION3D_DEF_Z:   (NSNumber)
        NVS_PARAM_STRING_TYPE:        (NSNumber)
        NVS_PARAM_STRING_DEF:         (NSString *)
        NVS_PARAM_MENU_DEF_VAL:       (NSString *)
        NVS_PARAM_MENU_ARRAY:         (NSArray *) {(NSString *), ...}
		}
*/
- (NSArray *)getAllParamsInfo;

@end
