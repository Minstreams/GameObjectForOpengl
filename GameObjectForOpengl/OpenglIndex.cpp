#include <time.h>
#include "OpenglIndex.h"

Scene mainScene;
double deltaTime;//To实现
int lastTime;

void Initial()
{
	deltaTime = 1000.0f / 60;
	lastTime = GetTickCount();

	glEnable(GL_DEPTH_TEST | GL_FOG);	// 启用深度测试
	glFrontFace(GL_CCW);		// 指定逆时针绕法表示多边形正面
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);	//背景

	//其他设置
	//glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_SMOOTH);
	//glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	
	if (!mainScene.skyBox.init())
	{
		MessageBox(NULL, "初始化天空失败!", "错误", MB_OK);
		exit(0);
	}
	SetScene();
	SetLight();

	mainScene.Start();
}
void ChangeSize(int w, int h)
{
	if (h == 0)	h = 1;

	// 设置视区尺寸
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// 设置修剪空间
	GLfloat fAspect;
	fAspect = (float)w / (float)h;
	gluPerspective(45.0, fAspect, 1.0, 1500.0);

	/*
	GLfloat nRange = 100.0f;
	if (w <= h)
	glOrtho(-nRange, nRange, nRange*h / w, -nRange*h / w, -nRange*2.0f + 300, nRange*2.0f + 300);
	else
	glOrtho(-nRange*w / h, nRange*w / h, nRange, -nRange, -nRange*2.0f + 300, nRange*2.0f + 300);
	*/
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	

	//清空鼠标显示计数器
	ShowCursor(false);
}

void RenderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	 //重置模型视图矩阵
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	int time = GetTickCount();
	int delta = time - lastTime;
	deltaTime = delta / 1000.0;
	lastTime = time;


	mainScene.Update();
	mainScene.Render();
	glutSwapBuffers();
}

void TimerFunc(int value)
{
	glutPostRedisplay();
	glutTimerFunc(1000 / 60, TimerFunc, 1);
}
