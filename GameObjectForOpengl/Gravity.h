#pragma once
class Gravity : public MonoBehavour {
public:
	double gravity;
	RigidBody *rid = NULL;
	Gravity(double gravity) :gravity(gravity) {}
	void Awake() override {
		if (gameObject->rigidBody == NULL) {
			ShowWarnMessage("There is no rigidBody!!\n没有刚体组件！！", "来自Gravity组件");
			gameObject->DestroyComponent(this);
		}
		else {
			rid = gameObject->rigidBody;
		}
	}
	void FixedUpdate() override {
		rid->velocity.y -= gravity * deltaTime;
	}
};