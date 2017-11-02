#pragma once
class AutoRotate : public MonoBehavour {
public:
	AutoRotate(Vector3* rot) {
		rotation = rot;
	}
	void Update() override {
		transform->Rotate(rotation*deltaTime/1000.0f);
	}

private:
	Vector3 rotation;
};