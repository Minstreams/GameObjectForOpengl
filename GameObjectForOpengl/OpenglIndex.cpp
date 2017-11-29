#include <time.h>
#include "OpenglIndex.h"

GameObject* currentGameObjectPointer = NULL;

Scene mainScene;
double deltaTime;//To实现
int lastTime;

void Initial() {
	//glutGameModeString("1920x1080");
	//设置全屏模式时使用的分辨率
	/*
	格式如下:
	“WxH:Bpp@Rr”
	W - 屏幕宽度的像素
	H - 屏幕高度的像素
	Bpp - 每个像素的比特数
	Rr - 垂直刷新的速率, 单位是赫兹(hz)

	在进行下一步之前, 注意这些设置只是请求到硬件.如果指定的模式是不可用, 设置会被忽略.
	例如:
	"800x600:32@100" - 屏幕大小800x600; 32位真色彩; 100赫兹 垂直刷新
	"640x480:16@75" - 屏幕大小640x480; 16位真色彩; 75赫兹

	下面这字符串模板用来设置需要的全屏设置是允许的:
	“WxH”
	“WxH : Bpp”
	“WxH@Rr”
	“@Rr”
	“:Bpp”
	“Bpp : @Rr”*/
	SetGameMode(true);
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

	glEnable(GL_DEPTH_TEST);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	//glEnable(GL_CULL_FACE);
	//glEnable(GL_FOG);	// 启用深度测试
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
	deltaTime = 1000.0f / 60;
	lastTime = clock();
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

	int time = clock();
	int delta = time - lastTime;
	deltaTime = delta / 1000.0;
	lastTime = time;

	Input::Update();

	mainScene.Update();
	mainScene.FixedUpdate();
	mainScene.Render();
	glutSwapBuffers();
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