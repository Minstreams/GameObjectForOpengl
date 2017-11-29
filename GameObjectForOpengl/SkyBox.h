//========================================================
/**
*  @file      SkyBox.h
*
*  项目描述： OPENGL赛车游戏
*  文件描述:  天空盒类
*  适用平台： Windows
*
*  作者：     405
*  电子邮件:  459762891@qq.com
*  创建日期： 2016-6-14
*  修改日期： 2016-6-14
*
*/
//========================================================
#pragma once
/** 天空盒类 */
class CSkyBox
{
public:
	/** 构造函数 */
	CSkyBox();
	~CSkyBox();

	/** 初始化 */
	bool init();

	/** 渲染 */
	void render();

private:

	GLint  m_texture[6];   /**< 天空盒纹理   */
	float       length;         /**< 长度 */
	float       width;          /**< 宽度 */
	float       height;         /**< 高度 */
	float       yRot;           /**< 绕Y轴旋转 */

};