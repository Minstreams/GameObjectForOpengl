#include"OpenglPrefab.h"

bool Input::FPSmode = false;
void Input::SetFPSmode(bool b) {
	Input::FPSmode = b;
	//进入FPS模式
	ShowCursor(!b);
	if (b) {
		Input::SetLastMousePos(centerX, centerY);
		POINT p;
		GetCursorPos(&p);
		mouseXCenterworld = p.x + centerX - mouseXPos;
		mouseYCenterworld = p.y + centerY - mouseYPos;
		mouseXPos = centerX;
		mouseYPos = centerY;
	}
}

unsigned char Input::keyChar = 0;
int Input::mouseXPos = 0;
int Input::mouseYPos = 0;
int Input::mouseXCenterworld = 0;
int Input::mouseYCenterworld = 0;
int Input::centerX = 640;
int Input::centerY = 360;
int Input::lastMouseX = centerX;
int Input::lastMouseY = centerY;
bool Input::isMouseDown = false;
bool Input::GetKey(unsigned char key) {
	return key == keyChar;
}
bool Input::GetKeyDown(unsigned char key) {
	return false;
}
bool Input::GetKeyUp(unsigned char key) {
	return false;
}
int Input::GetMouseX() {
	int out = mouseXPos - lastMouseX;
	if (FPSmode) {
		if (out <= 1 && out >= -1)out = 0;
		SetCursorPos(mouseXCenterworld, mouseYCenterworld);
	}
	else {
		lastMouseX = mouseXPos;
	}
	return out;
}
int Input::GetMouseY() {
	int out = mouseYPos - lastMouseY;
	if (FPSmode) {
		if (out <= 1 && out >= -1)out = 0;
	}
	else {
		lastMouseY = mouseYPos;
	}
	return out;
}
void Input::SetLastMousePos(int x, int y) {
	lastMouseX = x;
	lastMouseY = y;
}
void Input::Init() {
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutMotionFunc(MouseMove);
	glutPassiveMotionFunc(MouseMove);
}
//键盘响应回调函数
void Keyboard(unsigned char key, int x, int y)
{
	Input::keyChar = key;
	/*•返回键盘上被按下键的ASCII码和鼠标位置*/
}
//鼠标回调函数
void Mouse(int button, int state, int x, int y) {
	if (state == GLUT_DOWN) {
		Input::isMouseDown = true;
		Input::SetFPSmode(!Input::FPSmode);
	}
	if (state == GLUT_UP) {
		Input::isMouseDown = false;
	}
	//if (state == GLUT_UP)Input::isMouseDown = false;
	/*其中button的值可能是GLUT_LEFT_BUTTON,GLUT_MIDDLE_BUTTON,GLUT_RIGHT_BUTTON表示哪个按钮导致了事件发生
	state表示相应按钮的状态：GL_UP, GL_DOWN
	x, y表示在窗口中的位置*/
}
//鼠标移动回调函数
void MouseMove(int x, int y) {
	Input::mouseXPos = x;
	Input::mouseYPos = y;
	printf("%d,%d\n", x, y);
	//不明，也许是鼠标位置吧
}