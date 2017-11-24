#pragma once
class FPSMover : public MonoBehavour {
public:
	void Start() override {
//		Input::SetFPSmode(true);
	}
	void Update() override {
		double h = Input::GetAxisHorizontal();
		double v = Input::GetAxisVertical();
		transform->Translate(Vector3::forward * v + Vector3::right * h);
		if (Input::GetKey(KeyCode::Space)) {
			transform->Translate(Vector3::up);
		}
		if (Input::GetKey(KeyCode::LeftCtrl)) {
			transform->Translate(-Vector3::up);
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