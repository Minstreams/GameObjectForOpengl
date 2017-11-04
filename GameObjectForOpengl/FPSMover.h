#pragma once
class FPSMover : public MonoBehavour {
public:
	FPSMover() {
	}
	void Update() override {
		if (Input::GetKey('w')) {
			transform->Translate(transform->forward());
		}
		if (Input::GetKey('s')) {
			transform->Translate(-transform->forward());
		}
		if (Input::GetKey('a')) {
			transform->Translate(-transform->right());
		}		
		if (Input::GetKey('d')) {
			transform->Translate(transform->right());
		}
	}

};