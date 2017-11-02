//========================================================
/**
*  @file  CBMPLoader.h
*
*  项目描述： OPENGL赛车游戏
*  文件描述:  位图载入类
*  适用平台： Windows
*
*  作者：     405
*  电子邮件:  459762891@qq.com
*  创建日期： 2016-6-14
*  修改日期： 2016-6-14
*
*/
//========================================================
#ifndef __CBMPLOADER_H__
#define __CBMPLOADER_H__

#define BITMAP_ID 0x4D42	/**< 位图文件的标志 */

/** 位图载入类 */
class CBMPLoader
{
public:
	CBMPLoader();
	~CBMPLoader();
	bool LoadBitmap(const char *file, bool flag);
	bool LoadBitmap(const char *filename); /**< 装载一个bmp文件 */
	void FreeImage();                /**< 释放图像数据 */
	bool loadTexture(char* path, int wrap_s = GL_REPEAT, int wrap_T = GL_REPEAT);//一键装载纹理

	unsigned int ID;                 /**< 生成纹理的ID号 */
	int imageWidth;                  /**< 图像宽度 */
	int imageHeight;                 /**< 图像高度 */
	unsigned char *image;            /**< 指向图像数据的指针 */
};

#endif //__CBMPLOADER_H__

