#pragma once
class mover : public MonoBehaviour {
public:
	void Update() override {
		if (Input::GetKey('J')) {
			transform->Translate(Vector3::back);
		}

	}

};