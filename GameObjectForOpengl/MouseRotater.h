#pragma once
//鼠标移动控制旋转
class MouseRotater : public MonoBehavour {
private:
	float Xsensitivity = 1;
	float Ysensitivity = 1;
	bool hideMouseOnPlay;

	void Update() override
	{
		int x = Input::GetMouseX();
		int y = Input::GetMouseY();
		transform->Rotate(Quaternion::EulerY(-x * Xsensitivity), World);
		transform->Rotate(Quaternion::EulerX(-y * Ysensitivity), Self);
	}

	void Start() override
	{
		//Cursor.visible = !hideMouseOnPlay;
	}
public:
	MouseRotater(float xSens, float ySens) :Xsensitivity(xSens), Ysensitivity(ySens) {

	}
};