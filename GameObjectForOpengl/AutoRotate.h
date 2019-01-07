#pragma once
class AutoRotate : public MonoBehaviour {
public:
	AutoRotate(Vector3 rot) {
		rotation = rot;
	}
	void Update() override {
		transform->Rotate(Quaternion::Slerp(Quaternion::identity, Quaternion::Euler(rotation), deltaTime));
	}

private:
	Vector3 rotation;
};