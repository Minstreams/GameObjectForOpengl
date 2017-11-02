//========================================================
/**
*  @file      SkyBox.cpp
*
*  ��Ŀ������ OPENGL������Ϸ
*  �ļ�����:  ��պ���
*  ����ƽ̨�� Windows
*
*  ���ߣ�     405
*  �����ʼ�:  459762891@qq.com
*  �������ڣ� 2016-6-14
*  �޸����ڣ� 2016-6-14
*
*/
//========================================================

#include "OpenglPrefab.h"


CSkyBox::CSkyBox() :length(700.0f), width(700.0f), height(700.0f), yRot(0.01f)
{
	for (int i = 0;i < 6; i++)
		m_texture[i].ID = i;
}

CSkyBox::~CSkyBox()
{
	/** ɾ������������ռ�õ��ڴ� */
	for (int i = 0;i< 6; i++)
	{
		m_texture[i].FreeImage();
		glDeleteTextures(1, &m_texture[i].ID);
	}

}


/** ��պг�ʼ�� */
bool CSkyBox::init()
{
	char filename[128];                                         /**< ���������ļ��� */
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
	/** ��ó����й���״̬ */
	GLboolean lp;
	glGetBooleanv(GL_LIGHTING, &lp);


	glDisable(GL_LIGHTING);            /**< �رչ��� */
	glEnable(GL_TEXTURE_2D);

	/** ��ʼ���� */
	glPushMatrix();

	/** ���Ʊ��� */
	glBindTexture(GL_TEXTURE_2D, m_texture[0].ID);
	glBegin(GL_QUADS);

	/** ָ����������Ͷ������� */
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-width, -height, -length + 1);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-width, height, -length + 1);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(width, height, -length + 1);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(width, -height, -length + 1);
	glEnd();


	/** ����ǰ�� */
	glBindTexture(GL_TEXTURE_2D, m_texture[1].ID);
	glBegin(GL_QUADS);

	/** ָ����������Ͷ������� */
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-width, -height, length - 1);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-width, height, length - 1);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(width, height, length - 1);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(width, -height, length - 1);

	glEnd();



	/** ���ƶ��� */
	glBindTexture(GL_TEXTURE_2D, m_texture[2].ID);
	glBegin(GL_QUADS);

	/** ָ����������Ͷ������� */
	glTexCoord2f(0.0f, 0.0f); glVertex3f(width, height - 1, -length);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(width, height - 1, length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-width, height - 1, length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-width, height - 1, -length);

	glEnd();


	/** �������� */
	glBindTexture(GL_TEXTURE_2D, m_texture[3].ID);
	glBegin(GL_QUADS);

	/** ָ����������Ͷ������� */
	glTexCoord2f(1.0f, 1.0f);  glVertex3f(-width + 1, height, -length);
	glTexCoord2f(0.0f, 1.0f);  glVertex3f(-width + 1, height, length);
	glTexCoord2f(0.0f, 0.0f);  glVertex3f(-width + 1, -height, length);
	glTexCoord2f(1.0f, 0.0f);  glVertex3f(-width + 1, -height, -length);

	glEnd();

	/** �������� */
	glBindTexture(GL_TEXTURE_2D, m_texture[4].ID);
	glBegin(GL_QUADS);

	/** ָ����������Ͷ������� */
	glTexCoord2f(0.0f, 0.0f); glVertex3f(width - 1, -height, -length);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(width - 1, -height, length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(width - 1, height, length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(width - 1, height, -length);
	glEnd();

	/** ���Ƶ��� */
	glBindTexture(GL_TEXTURE_2D, m_texture[5].ID);
	glBegin(GL_QUADS);

	/** ָ����������Ͷ������� */
	glTexCoord2f(0.0f, 1.0f); glVertex3f(width, -height + 1, -length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-width, -height + 1, -length);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-width, -height + 1, length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(width, -height + 1, length);

	glEnd();


	glPopMatrix();                 /** ���ƽ��� */

	if (lp)                         /** �ָ�����״̬ */
		glEnable(GL_LIGHTING);

	glDisable(GL_TEXTURE_2D);
}