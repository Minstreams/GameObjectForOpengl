#pragma once
class CarController : public MonoBehaviour {
private:
	RigidBody *rid = NULL;
	const double maxSpeed;
	const double maxSpeedSqr;
	double speed;
	Quaternion forwardRot;
	Transform* model;
public:
	CarController(double maxSpeed, Transform *model) :maxSpeed(maxSpeed), maxSpeedSqr(maxSpeed*maxSpeed), model(model) {}
	void Awake() override {
		if (gameObject->rigidBody == NULL) {
			ShowWarnMessage("There is no rigidBody!!\n没有刚体组件！！", "来自FPSRigidBodyMover组件");
			gameObject->DestroyComponent(this);
		}
		else {
			rid = gameObject->rigidBody;
		}
		speed = 0;
		forwardRot = Quaternion::identity;
	}
	void Update() override {
		double h = (Input::GetKey('d') ? 1 : 0) + (Input::GetKey('a') ? -1 : 0);
		double v = (Input::GetKey('w') ? 1 : 0) + (Input::GetKey('s') ? -1 : 0);

		if (Input::GetKeyDown(KeyCode::Esc)) {
			SetGameMode(false);
			exit(0);
		}
		if (Input::GetKeyDown('f')) {
			Input::SetFPSmode(!Input::FPSmode);
		}

		Vector3 right = mainScene.camera.transform.rotation * Vector3::right;
		Vector3 forward = Vector3::Cross(Vector3::up, right);
		Vector3 vec = right.normalized() * h + forward.normalized() * v;

		rid->SetVelocity(model->forward() * vec.magnitude() * maxSpeed);

		speed = rid->velocity.sqrMagnitude();

		if (vec.sqrMagnitude() > 0.1)
			forwardRot = Quaternion::LookAtRotation(vec, Vector3::up);

		double t = sqrt(speed) / maxSpeed;
		model->SetRotation(Quaternion::Slerp(
			model->rotation,
			forwardRot,
			0.02 * min(t, 0.6)
		));
	}

};