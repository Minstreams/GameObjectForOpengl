#pragma once

class CamVelocityRecorder : public MonoBehavour {
private:
	Vector3 lastPos;
public:
	static Vector3 currentVelocity;
	void Start() override {
		lastPos = transform->GetPosition();
	}
	void Update() override {
		Vector3 currentPos = transform->GetPosition();
		currentVelocity = (currentPos - lastPos) / deltaTime;
		lastPos = currentPos;
	}

};

Vector3 CamVelocityRecorder::currentVelocity = Vector3::zero;