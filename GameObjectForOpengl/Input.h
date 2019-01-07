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
	static bool GetKey(unsigned char key);
	static bool GetKeyDown(unsigned char key);
	static bool GetKeyUp(unsigned char key);
	static bool GetMouseButton(unsigned char mouseIndex);
	static bool GetMouseButtonDown(unsigned char mouseIndex);
	static bool GetMouseButtonUp(unsigned char mouseIndex);
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
//键值
class KeyCode {
public:
	//normal <128
	static const unsigned char Space = (unsigned char)32;
	static const unsigned char Esc = (unsigned char)27;

	//special >=128
	static const unsigned char Up = (unsigned char)128;
	static const unsigned char Down = (unsigned char)129;
	static const unsigned char Left = (unsigned char)130;
	static const unsigned char Right = (unsigned char)132;
	static const unsigned char LeftShift = (unsigned char)133;
	static const unsigned char RightShift = (unsigned char)134;
	static const unsigned char LeftCtrl = (unsigned char)135;
	static const unsigned char RightCtrl = (unsigned char)136;
	static const unsigned char LeftAlt = (unsigned char)137;
	static const unsigned char RightAlt = (unsigned char)138;
	static const unsigned char Mouse0 = (unsigned char)139;	//左键
	static const unsigned char Mouse1 = (unsigned char)140;	//右键
	static const unsigned char Mouse2 = (unsigned char)141;	//中键
};