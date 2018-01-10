#pragma once
class mover : public MonoBehavour {
public:
	void Update() override {
		if (Input::GetKey('J')) {
			transform->Translate(Vector3::back);
		}

	}

};