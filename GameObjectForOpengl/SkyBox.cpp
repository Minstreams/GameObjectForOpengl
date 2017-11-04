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

#include "OpenglIndex.h"


CSkyBox::CSkyBox() :length(700.0f), width(700.0f), height(700.0f), yRot(0.01f)
{

}

CSkyBox::~CSkyBox()
{
	/** 删除纹理对象及其占用的内存 */
	for (int i = 0;i< 6; i++)
	{
		m_texture[i].FreeImage();
		glDeleteTextures(1, &m_texture[i].ID);
	}

}


/** 天空盒初始化 */
bool CSkyBox::init()
{
	char filename[128];                                         /**< 用来保存文件名 */
	char *bmpName[] = { "back","front","up","left","right","down" };
	for (int i = 0; i< 6; i++)
	{
		sprintf_s(filename, "data/Sky Box Bmp/%s", bmpName[i]);
		strcat_s(filename, ".bmp");
		m_texture[i].loadTexture(filename);
	}
	return true;

}


void CSkyBox::render()
{
	/** 获得场景中光照状态 */
	GLboolean lp;
	glGetBooleanv(GL_LIGHTING, &lp);


	glDisable(GL_LIGHTING);            /**< 关闭光照 */
	glEnable(GL_TEXTURE_2D);

	/** 开始绘制 */
	glPushMatrix();

	/** 绘制背面 */
	glBindTexture(GL_TEXTURE_2D, m_texture[0].ID);
	glBegin(GL_QUADS);

	/** 指定纹理坐标和顶点坐标 */
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-width, -height, -length + 1);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-width, height, -length + 1);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(width, height, -length + 1);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(width, -height, -length + 1);
	glEnd();


	/** 绘制前面 */
	glBindTexture(GL_TEXTURE_2D, m_texture[1].ID);
	glBegin(GL_QUADS);

	/** 指定纹理坐标和顶点坐标 */
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-width, -height, length - 1);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-width, height, length - 1);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(width, height, length - 1);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(width, -height, length - 1);

	glEnd();



	/** 绘制顶面 */
	glBindTexture(GL_TEXTURE_2D, m_texture[2].ID);
	glBegin(GL_QUADS);

	/** 指定纹理坐标和顶点坐标 */
	glTexCoord2f(0.0f, 0.0f); glVertex3f(width, height - 1, -length);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(width, height - 1, length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-width, height - 1, length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-width, height - 1, -length);

	glEnd();


	/** 绘制左面 */
	glBindTexture(GL_TEXTURE_2D, m_texture[3].ID);
	glBegin(GL_QUADS);

	/** 指定纹理坐标和顶点坐标 */
	glTexCoord2f(1.0f, 1.0f);  glVertex3f(-width + 1, height, -length);
	glTexCoord2f(0.0f, 1.0f);  glVertex3f(-width + 1, height, length);
	glTexCoord2f(0.0f, 0.0f);  glVertex3f(-width + 1, -height, length);
	glTexCoord2f(1.0f, 0.0f);  glVertex3f(-width + 1, -height, -length);

	glEnd();

	/** 绘制右面 */
	glBindTexture(GL_TEXTURE_2D, m_texture[4].ID);
	glBegin(GL_QUADS);

	/** 指定纹理坐标和顶点坐标 */
	glTexCoord2f(0.0f, 0.0f); glVertex3f(width - 1, -height, -length);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(width - 1, -height, length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(width - 1, height, length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(width - 1, height, -length);
	glEnd();

	/** 绘制底面 */
	glBindTexture(GL_TEXTURE_2D, m_texture[5].ID);
	glBegin(GL_QUADS);

	/** 指定纹理坐标和顶点坐标 */
	glTexCoord2f(0.0f, 1.0f); glVertex3f(width, -height + 1, -length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-width, -height + 1, -length);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-width, -height + 1, length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(width, -height + 1, length);

	glEnd();


	glPopMatrix();                 /** 绘制结束 */

	if (lp)                         /** 恢复光照状态 */
		glEnable(GL_LIGHTING);

	glDisable(GL_TEXTURE_2D);
}
