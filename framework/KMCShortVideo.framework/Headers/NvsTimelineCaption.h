//================================================================================
//
// (c) Copyright China Digital Video (Beijing) Limited, 2017. All rights reserved.
//
// This code and information is provided "as is" without warranty of any kind,
// either expressed or implied, including but not limited to the implied
// warranties of merchantability and/or fitness for a particular purpose.
//
//--------------------------------------------------------------------------------
//   Birth Date:    Feb 16. 2017
//   Author:        NewAuto video team
//================================================================================
#pragma once

#import "NvsFx.h"
#import <CoreGraphics/CGGeometry.h>

/*!
    \brief 时间线字幕

    时间线字幕是视频上叠加的自定义文字。编辑视频时，可以添加和移除时间线字幕，并对字幕位置进行调整处理。添加完字幕，还可以进行样式设置，包括字体大小，颜色，阴影，描边等。
 */
@interface NvsTimelineCaption : NvsFx

@property (readonly) int64_t inPoint;    //!< \if ENGLISH \else 字幕在时间线上显示的入点 \endif
@property (readonly) int64_t outPoint;   //!< \if ENGLISH \else 字幕在时间线显示上的出点 \endif
@property (readonly) NvsRoleInTheme roleInTheme; //!< \if ENGLISH \else 字幕在主题中的角色(通用、片头、片尾) \endif
@property (readonly) NvsCategory category;//!< \if ENGLISH \else 片段类型 \endif
@property (readonly) NSString* captionStylePackageId;//!< \if ENGLISH \else 字幕样式包裹ID \endif

/*!
     \brief 改变字幕在时间线上显示的入点
     \param newInPoint 字幕在时间线上的新的入点
     \return 返回字幕在时间线上的显示的入点值
     \warning 此接口会引发流媒体引擎状态跳转到引擎停止状态，具体情况请参见[引擎变化专题] (\ref EngineChange.md)。
     \sa changeOutPoint:
     \sa movePosition:
 */
- (int64_t)changeInPoint:(int64_t)newInPoint;

/*!
     \brief 改变字幕在时间线上显示的出点
     \param newOutPoint 字幕在时间线上的新的出点
     \return 返回字幕在时间线上显示的出点值
     \warning 此接口会引发流媒体引擎状态跳转到引擎停止状态，具体情况请参见[引擎变化专题] (\ref EngineChange.md)。
     \sa changeInPoint:
     \sa movePosition:
 */
- (int64_t)changeOutPoint:(int64_t)newOutPoint;

/*!
     \brief 改变字幕在时间线上的显示位置(入点和出点同时偏移offset值)
     \param offset 入点和出点改变的偏移值
     \warning 此接口会引发流媒体引擎状态跳转到引擎停止状态，具体情况请参见[引擎变化专题] (\ref EngineChange.md)。
     \sa changeInPoint:
     \sa changeOutPoint:
 */
- (void)movePosition:(int64_t)offset;

/*!
     \brief 运用字幕样式
     \param captionStylePackageId 字幕样式资源包ID
     \return 返回bool值。true表示成功运用字幕样式，false则运用失败
     \warning 此接口会引发流媒体引擎状态跳转到引擎停止状态，具体情况请参见[引擎变化专题] (\ref EngineChange.md)。
 */
-(bool) applyCaptionStyle:(NSString*) captionStylePackageId;

/*!
     \brief 设置字幕文本
     \param text 字幕文本
     \sa getText
 */
- (void)setText:(NSString *)text;

/*!
     \brief 获取字幕文本
     \return 返回获取的字幕文本
     \sa setText:
 */
- (NSString *)getText;

/*!
     \brief 设置字幕字体加粗
     \param bold 表示字幕字体是否加粗。YES表示加粗，NO则不加粗
     \sa getBold
 */
- (void)setBold:(BOOL)bold;

/*!
     \brief 获取字幕字体加粗状态
     \return 返回字幕字体加粗状态。YES表示字体已加粗，NO则字体未加粗
     \sa setBold:
 */
- (BOOL)getBold;

/*!
     \brief 设置字幕字体斜体
     \param italic 是否设为斜体。YES表示设置字幕字体为斜体，NO则不设为斜体
     \sa getItalic
 */
- (void)setItalic:(BOOL)italic;

/*!
     \brief 获取字幕斜体状态
     \return 返回BOOL值，YES表示是斜体字体，NO则不是斜体
     \sa setItalic:
 */
- (BOOL)getItalic;

/*!
     \brief 设置字幕文本颜色
     \param textColor 字幕文本颜色值
     \sa getTextColor
 */
- (void)setTextColor:(const NvsColor *)textColor;

/*!
     \brief 获取字幕字体的当前颜色值
     \return 返回NvsColor对象，表示获得的颜色值
     \sa setTextColor:
 */
- (NvsColor)getTextColor;

/*!
     \brief 设置字幕描边
     \param drawOutline 是否对字幕描边。YES表示对字幕进行描边，NO则不描边
     \sa getDrawOutline
 */
- (void)setDrawOutline:(BOOL)drawOutline;

/*!
     \brief 获取字幕描边状态
     \return 返回BOOL值，YES表示已描边，NO则未描边
     \sa setDrawOutline:
 */
- (BOOL)getDrawOutline;

/*!
     \brief 设置字幕描边的颜色
     \param outlineColor 字幕描边颜色值
     \sa getOutlineColor
 */
- (void)setOutlineColor:(const NvsColor *)outlineColor;

/*!
     \brief 获取当前字幕描边的颜色值
     \return 返回NvsColor对象，表示获得的字幕描边的颜色
     \sa setOutlineColor:
 */
- (NvsColor)getOutlineColor;

/*!
     \brief 设置字幕描边的宽度
     \param outlineWidth 字幕描边的宽度
     \sa getOutlineWidth
 */
- (void)setOutlineWidth:(float)outlineWidth;

/*!
     \brief 获取当前字幕描边的宽度
     \return 返回获得的字幕描边的宽度值
     \sa setOutlineWidth:
 */
- (float)getOutlineWidth;

/*!
     \brief 设置字幕阴影
     \param drawShadow 是否设置字幕阴影。YES表示设置字幕阴影，NO则不设置
     \sa getDrawShadow
 */
- (void)setDrawShadow:(BOOL)drawShadow;

/*!
     \brief 获取当前字幕阴影状态
     \return 返回BOOL值，YES表示有字幕阴影，NO则没有字幕阴影
     \sa setDrawShadow:
 */
- (BOOL)getDrawShadow;

/*!
     \brief 设置字幕阴影的颜色
     \param shadowColor 字幕阴影颜色值
     \sa getShadowColor
 */
- (void)setShadowColor:(const NvsColor *)shadowColor;

/*!
     \brief 获取当前字幕阴影的颜色
     \return 返回NvsColor对象，表示获得的字幕阴影颜色值
     \sa setShadowColor:
 */
- (NvsColor)getShadowColor;

/*!
     \brief 设置字幕阴影的偏移量
     \param shadowOffset 字幕阴影的偏移量
     \sa getShadowOffset
 */
- (void)setShadowOffset:(CGPoint)shadowOffset;

/*!
     \brief 获取当前字幕阴影的偏移量
     \return 返回CGPoint对象，表示获得的字幕阴影偏移量
     \sa setShadowOffset:
 */
- (CGPoint)getShadowOffset;

/*!
     \brief 设置字幕字体大小
     \param fontSize 字幕字体大小值
     \sa getFontSize
 */
- (void)setFontSize:(float)fontSize;

/*!
     \brief 获取当前字幕的字体大小
     \return 返回获得的字幕字体大小值
     \sa setFontSize:
 */
- (float)getFontSize;

/*!
     \brief 设置字幕字体
     \param filePath 字幕字体文件路径，若设为空字符串，则设为默认字体
     \since 1.3.0
     \sa getFontFilePath
 */
- (void)setFontWithFilePath:(NSString *)filePath;

/*!
     \brief 获取字幕字体的文件路径
     \return 返回字幕字体的文件路径
     \since 1.3.0
     \sa setFontWithFilePath:
 */
- (NSString *)getFontFilePath;

/*!
     \brief 字幕平移
     \param translation 字幕平移的x,y值
     \sa getCaptionTranslation
 */
- (void)setCaptionTranslation:(CGPoint)translation;

/*!
     \brief 获取字幕的平移量
     \return 返回CGPoint对象，表示获得的字幕平移量
     \sa setCaptionTranslation:
 */
- (CGPoint)getCaptionTranslation;

/*!
     \brief 获取字幕文本矩形框
     \return 返回NvsRect对象，表示获得的字幕文本矩形框
 */
- (NvsRect)getTextBoundingRect;

@end

