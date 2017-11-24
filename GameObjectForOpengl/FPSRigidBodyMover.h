#pragma once
class FPSRigidBodyMover : public MonoBehavour {
private:
	RigidBody *rid = NULL;
	double speed;
public:
	FPSRigidBodyMover(double speed) :speed(speed)
	{

	}
	void Awake() override {
		if (gameObject->rigidBody == NULL) {
			printf_s("There is no rigidBody!!\n");
			gameObject->DestroyComponent(this);
		}
		else {
			rid = gameObject->rigidBody;
		}
	}
	void Update() override {
		double h = Input::GetAxisHorizontal();
		double v = Input::GetAxisVertical();
		Vector3 vec(h, 0, -v);
		if (Input::GetKey(KeyCode::Space)) {
			vec += Vector3::up;
		}
		if (Input::GetKey(KeyCode::LeftCtrl)) {
			vec -= Vector3::up;
		}
		if (Input::GetKeyDown(KeyCode::Esc)) {
			SetGameMode(false);
			exit(0);
		}
		if (Input::GetKeyDown('f')) {
			Input::SetFPSmode(!Input::FPSmode);
		}
		rid->SetVelocity(
			transform->GetWorldMatrix() ^ (vec*speed)
		);
	}

};