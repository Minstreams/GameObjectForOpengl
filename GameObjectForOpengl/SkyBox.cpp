//========================================================
/**
*  @file      SkyBox.cpp
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

#include "OpenglHeader.h"
#include "ModelIndex.h"
#include "SkyBox.h"


CSkyBox::CSkyBox() :length(1400.0f), width(1400.0f), height(1400.0f), yRot(0.01f)
{

}

CSkyBox::~CSkyBox()
{
	/** 删除纹理对象及其占用的内存 */

}


/** 天空盒初始化 */
bool CSkyBox::init()
{
	char filename[128];                                         /**< 用来保存文件名 */
	char *bmpName[] = { "back","front","up","left","right","down" };
	for (int i = 0; i < 6; i++)
	{
		sprintf_s(filename, "data/Sky Box Bmp/%s", bmpName[i]);
		strcat_s(filename, ".bmp");
		m_texture[i] = TextureHelper::load2DTexture(filename);
		if (m_texture[i] == 0)
			return false;
	}
	return true;

}


void CSkyBox::render()
{
	/** 获得场景中光照状态 */
	GLboolean lp;
	glGetBooleanv(GL_LIGHTING, &lp);

	if (lp)  /**< 关闭光照 */
		glDisable(GL_LIGHTING);

	glColor3f(1, 1, 1);

	glActiveTexture(GL_TEXTURE0);

	/** 开始绘制 */
	glPushMatrix();

	/** 绘制背面 */
	TextureHelper::use2DTexture(m_texture[0]);
	glBegin(GL_QUADS);

	/** 指定纹理坐标和顶点坐标 */
	glTexCoord2f(1.0f, 0.0f); glVertex3f(width, height, -length + 1);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-width, height, -length + 1);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-width, -height, -length + 1);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(width, -height, -length + 1);
	glEnd();



	/** 绘制前面 */
	TextureHelper::use2DTexture(m_texture[1]);
	glBegin(GL_QUADS);

	/** 指定纹理坐标和顶点坐标 */
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-width, -height, length - 1);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-width, height, length - 1);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(width, height, length - 1);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(width, -height, length - 1);

	glEnd();



	/** 绘制顶面 */
	TextureHelper::use2DTexture(m_texture[2]);
	glBegin(GL_QUADS);

	/** 指定纹理坐标和顶点坐标 */
	glTexCoord2f(0.0f, 1.0f); glVertex3f(width, height - 1, -length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(width, height - 1, length);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-width, height - 1, length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-width, height - 1, -length);

	glEnd();


	/** 绘制左面 */
	TextureHelper::use2DTexture(m_texture[3]);
	glBegin(GL_QUADS);

	/** 指定纹理坐标和顶点坐标 */
	glTexCoord2f(1.0f, 0.0f);  glVertex3f(-width + 1, height, -length);
	glTexCoord2f(0.0f, 0.0f);  glVertex3f(-width + 1, height, length);
	glTexCoord2f(0.0f, 1.0f);  glVertex3f(-width + 1, -height, length);
	glTexCoord2f(1.0f, 1.0f);  glVertex3f(-width + 1, -height, -length);

	glEnd();

	/** 绘制右面 */
	TextureHelper::use2DTexture(m_texture[4]);
	glBegin(GL_QUADS);

	/** 指定纹理坐标和顶点坐标 */
	glTexCoord2f(0.0f, 1.0f); glVertex3f(width - 1, -height, -length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(width - 1, -height, length);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(width - 1, height, length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(width - 1, height, -length);
	glEnd();

	/** 绘制底面 */
	TextureHelper::use2DTexture(m_texture[5]);
	glBegin(GL_QUADS);

	/** 指定纹理坐标和顶点坐标 */
	glTexCoord2f(0.0f, 0.0f); glVertex3f(width, -height + 1, -length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-width, -height + 1, -length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-width, -height + 1, length);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(width, -height + 1, length);

	glEnd();


	glPopMatrix();                 /** 绘制结束 */

	if (lp)                         /** 恢复光照状态 */
		glEnable(GL_LIGHTING);
}
