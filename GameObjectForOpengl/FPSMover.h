#pragma once
class FPSMover : public MonoBehavour {
public:
	FPSMover() {
	}
	void Start() override {
		Input::SetFPSmode(true);
	}
	void Update() override {
		double h = Input::GetAxisHorizontal();
		double v = Input::GetAxisVertical();
		transform->Translate(transform->forward() * v + transform->right() * h);
		if (Input::GetKey(KeyCode::Space)) {
			transform->Translate(transform->up());
		}
		if (Input::GetKey(KeyCode::LeftCtrl)) {
			transform->Translate(-transform->up());
		}
		if (Input::GetKeyDown(KeyCode::Esc)) {
			SetGameMode(false);
			exit(0);
		}
		if (Input::GetKeyDown('f')) {
			Input::SetFPSmode(!Input::FPSmode);
		}
	}

};