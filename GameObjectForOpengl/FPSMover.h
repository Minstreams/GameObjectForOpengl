#pragma once
class FPSMover : public MonoBehavour {
public:
	FPSMover() {
	}
	void Start() override{
		Input::SetFPSmode(true);
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