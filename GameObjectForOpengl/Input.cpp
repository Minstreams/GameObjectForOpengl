#include"OpenglIndex.h"

#define SIMPLE_KEY_NUM 256

bool Input::FPSmode = false;
void Input::SetFPSmode(bool b) {
	Input::FPSmode = b;
	//进入FPS模式
	SetCursorVisible(!b);
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

bool* Input::keyHold = new bool[SIMPLE_KEY_NUM];
bool* Input::keyDown = new bool[SIMPLE_KEY_NUM];
bool* Input::keyUp = new bool[SIMPLE_KEY_NUM];
int Input::mouseXPos = 0;
int Input::mouseYPos = 0;
int Input::mouseXCenterworld = 0;
int Input::mouseYCenterworld = 0;
int Input::centerX = 960;
int Input::centerY = 540;
int Input::lastMouseX = centerX;
int Input::lastMouseY = centerY;
bool Input::isMouseDown = false;
bool Input::GetKey(unsigned char key) {
	return keyHold[key];
}
bool Input::GetKeyDown(unsigned char key) {
	if (keyDown[key]) {
		keyDown[key] = false;
		return true;
	}
	return false;
}
bool Input::GetKeyUp(unsigned char key) {
	if (keyUp[key]) {
		keyUp[key] = false;
		return true;
	}
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
	glutKeyboardFunc(KeyboardDown);
	glutKeyboardUpFunc(KeyboardUp);
	glutSpecialFunc(SpecialKeyboardDown);
	glutSpecialUpFunc(SpecialKeyboardUp);
	glutMouseFunc(Mouse);
	glutMotionFunc(MouseMove);
	glutPassiveMotionFunc(MouseMove);

	POINT p;
	GetCursorPos(&p);
	mouseXPos = p.x;
	mouseYPos = p.y;
	for (int i = 0;i < SIMPLE_KEY_NUM;i++) {
		keyHold[i] = false;
		keyDown[i] = false;
		keyUp[i] = false;
	}
}
void Input::Update() {

}
void SetDown(unsigned char key) {
	if (!Input::keyHold[key]) {
		Input::keyDown[key] = true;
		Input::keyUp[key] = false;
	}
	Input::keyHold[key] = true;
}
void SetUp(unsigned char key) {
	Input::keyHold[key] = false;
	Input::keyDown[key] = false;
	Input::keyUp[key] = true;
}
//键盘按下响应回调函数
void KeyboardDown(unsigned char key, int x, int y)
{
	printf_s("\n%d \tpressed", key);
	SetDown(key);
	//对于小写字母
	if (97 <= key&&key <= 122) {
		SetDown(key - 32);
	}
	//对于大写字母
	if (65 <= key&&key <= 90) {
		SetDown(key + 32);
	}
	/*•返回键盘上被按下键的ASCII码和鼠标位置*/
}
//键盘释放响应回调函数
void KeyboardUp(unsigned char key, int x, int y)
{
	SetUp(key);
	//对于小写字母
	if (97 <= key&&key <= 122) {
		SetUp(key - 32);
	}
	//对于大写字母
	if (65 <= key&&key <= 90) {
		SetUp(key + 32);
	}
	/*•返回键盘上被按下键的ASCII码和鼠标位置*/
}
void SpecialKeyboardDown(int key, int x, int y) {
	printf_s("\n%d \tSpcPressed", key);
	int keyCode = 0;
	switch (key) {
	case GLUT_KEY_UP:
		keyCode = KeyCode::Up;
		break;
	case GLUT_KEY_DOWN:
		keyCode = KeyCode::Down;
		break;
	case GLUT_KEY_LEFT:
		keyCode = KeyCode::Left;
		break;
	case GLUT_KEY_RIGHT:
		keyCode = KeyCode::Right;
		break;
	case 112:
		keyCode = KeyCode::LeftShift;
		break;
	case 113:
		keyCode = KeyCode::RightShift;
		break;
	case 114:
		keyCode = KeyCode::LeftCtrl;
		break;
	case 115:
		keyCode = KeyCode::RightCtrl;
		break;
	case 116:
		keyCode = KeyCode::LeftAlt;
		break;
	case 117:
		keyCode = KeyCode::RightAlt;
		break;
	}
	SetDown(keyCode);
}
void SpecialKeyboardUp(int key, int x, int y) {
	int keyCode = 0;
	switch (key) {
	case GLUT_KEY_UP:
		keyCode = KeyCode::Up;
		break;
	case GLUT_KEY_DOWN:
		keyCode = KeyCode::Down;
		break;
	case GLUT_KEY_LEFT:
		keyCode = KeyCode::Left;
		break;
	case GLUT_KEY_RIGHT:
		keyCode = KeyCode::Right;
		break;
	case 112:
		keyCode = KeyCode::LeftShift;
		break;
	case 113:
		keyCode = KeyCode::RightShift;
		break;
	case 114:
		keyCode = KeyCode::LeftCtrl;
		break;
	case 115:
		keyCode = KeyCode::RightCtrl;
		break;
	case 116:
		keyCode = KeyCode::LeftAlt;
		break;
	case 117:
		keyCode = KeyCode::RightAlt;
		break;
	}
	SetUp(keyCode);
}
//鼠标回调函数
void Mouse(int button, int state, int x, int y) {
	if (state == GLUT_DOWN) {
		Input::isMouseDown = true;
		//Input::SetFPSmode(!Input::FPSmode);
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
	//不明，也许是鼠标位置吧
}