#include <time.h>
#include "OpenglIndex.h"

GameObject* currentGameObjectPointer = NULL;

Scene mainScene;
double deltaTime;//To实现
int lastTime;

void Initial() {
	BasicInitial();
	SceneInitial();
}
/*全屏与窗口模式共用的初始化方法
*/
void BasicInitial() {
	// 初始化GLEW 获取OpenGL函数
	glewExperimental = GL_TRUE; // 让glew获取所有拓展函数
	GLenum status = glewInit();
	if (status != GLEW_OK)
	{
		std::cout << "Error::GLEW glew version:" << glewGetString(GLEW_VERSION)
			<< " error string:" << glewGetErrorString(status) << std::endl;
		//glfwTerminate();
		std::system("pause");
		//return -1;
	}


	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);
	Input::Init();
	glutTimerFunc(100, TimerFunc, 1);

	glEnable(GL_DEPTH_TEST);// 启用深度测试
	glEnable(GL_CULL_FACE);
	//glEnable(GL_FOG);	
	//glFrontFace(GL_CCW);		// 指定逆时针绕法表示多边形正面
	//glShadeModel(GL_SMOOTH);
	if (!mainScene.skyBox.init())
	{
		MessageBox(NULL, "初始化天空失败!", "错误", MB_OK);
		exit(0);
	}
	SetLight();
}
void SceneInitial() {
	glClearColor(0.2f, 1.0f, 0.1f, 1.0f);	//背景
	lastTime = -1;
	//其他设置
	//glDepthFunc(GL_LEQUAL);
	//glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	currentGameObjectPointer = &mainScene.camera;

	SetScene();

	mainScene.Awake();
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
}

void RenderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//重置模型视图矩阵
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	mainScene.Render();
	glutSwapBuffers();


	if (lastTime < 0) {
		lastTime = clock();
	}
	int time = clock();
	int delta = time - lastTime;
	deltaTime = delta / 1000.0;
	lastTime = time;

	Input::Update();

	mainScene.Update();
	mainScene.FixedUpdate();
}

void TimerFunc(int value)
{
	glutPostRedisplay();
	glutTimerFunc(1000 / 60, TimerFunc, 1);
}

void SetCursorVisible(bool visible) {
	while (visible != (ShowCursor(visible) >= 0));
}

void SetGameMode(bool b) {
	if (b) {
		if (glutGameModeGet(GLUT_GAME_MODE_POSSIBLE)) {
			glutEnterGameMode();
			//禁用DPI缩放
			SetProcessDPIAware();
		}
		else {
			ShowWarnMessage("无法进入全屏模式！");
		}
	}
	else {
		glutLeaveGameMode();
	}
}

void ShowWarnMessage(const char* message, const char* title) {
	MessageBox(NULL, message, title, MB_ICONEXCLAMATION);
}