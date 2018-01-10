#pragma once

class Input {
public:
	static bool FPSmode;
	static void SetFPSmode(bool b);
	static bool* keyHold;
	static bool* keyUp;
	static bool* keyDown;
	static int mouseXPos;//当前鼠标x坐标
	static int mouseYPos;//当前鼠标y坐标
	static int centerX;
	static int centerY;
	static bool isMouseDown;
	static bool GetKey(unsigned char key);
	static bool GetKeyDown(unsigned char key);
	static bool GetKeyUp(unsigned char key);
	static int GetMouseX();//鼠标移动变量
	static int GetMouseY();//鼠标移动变量
	static double GetAxisHorizontal();
	static double GetAxisVertical();
	static void SetLastMousePos(int x, int y);
	static void Init();
	static void Update();//每一帧被调用
	static int mouseXCenterworld;//当前中心相对屏幕坐标
	static int mouseYCenterworld;//当前中心相对屏幕坐标
private:
	static int lastMouseX;
	static int lastMouseY;
	static double hAxis;//水平Axis
	static double vAxis;//垂直Axis
	static const double axisAcceleratingRate;//Axis加速度
};
void KeyboardDown(unsigned char key, int x, int y);
void KeyboardUp(unsigned char key, int x, int y);
void SpecialKeyboardDown(int key, int x, int y);
void SpecialKeyboardUp(int key, int x, int y);
void Mouse(int button, int state, int x, int y);
void MouseMove(int x, int y);
//键值
class KeyCode {
public:
	//normal <128
	static const char Space = (char)32;
	static const char Esc = (char)27;

	//special >=128
	static const char Up = (char)128;
	static const char Down = (char)129;
	static const char Left = (char)130;
	static const char Right = (char)132;
	static const char LeftShift = (char)133;
	static const char RightShift = (char)134;
	static const char LeftCtrl = (char)135;
	static const char RightCtrl = (char)136;
	static const char LeftAlt = (char)137;
	static const char RightAlt = (char)138;
};