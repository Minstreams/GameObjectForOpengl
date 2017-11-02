#pragma once
class MouseRotater : public MonoBehavour {
private:
	float Xsensitivity = 1;
	float Ysensitivity = 1;
	bool hideMouseOnPlay;

	void Update() override
	{
		float x = Input::GetMouseX();
		float y = Input::GetMouseY();
		transform->Rotate(-y * Ysensitivity, 0, 0);
		transform->Rotate(0, -x * Xsensitivity, 0);
	}

	void Start() override
	{
		//Cursor.visible = !hideMouseOnPlay;
	}
public:
	MouseRotater(float xSens, float ySens) :Xsensitivity(xSens), Ysensitivity(ySens) {

	}
};