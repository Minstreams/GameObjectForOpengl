#pragma once

class Input {
public:
	static bool FPSmode;
	static void SetFPSmode(bool b);
	static unsigned char keyChar;
	static int mouseXPos;//当前鼠标x坐标
	static int mouseYPos;//当前鼠标y坐标
	static int mouseXCenterworld;//当前中心相对屏幕坐标
	static int mouseYCenterworld;//当前中心相对屏幕坐标
	static int centerX;
	static int centerY;
	static bool isMouseDown;
	static bool GetKey(unsigned char key);
	static bool GetKeyDown(unsigned char key);
	static bool GetKeyUp(unsigned char key);
	static int GetMouseX();
	static int GetMouseY();
	static void SetLastMousePos(int x, int y);
	static void Init();
private:
	static int lastMouseX;
	static int lastMouseY;
};
void Keyboard(unsigned char key, int x, int y);
void Mouse(int button, int state, int x, int y);
void MouseMove(int x, int y);