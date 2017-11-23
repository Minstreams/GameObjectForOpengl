#pragma once
class RigidBody :MonoBehavour {
public:
	Vector3 velocity;
	//数组的大小，在类初始化时就应该赋好值
	int colliderNum = 0;
	//可以考虑在awake的时候初始化,在Start赋值
	SphereCollider** colliders = NULL;
private:
	//用于引导添加
	int startAddColliderPointer = 0;
public:

	void StartAddCollider(SphereCollider *pointer) {
		colliders[startAddColliderPointer] = pointer;
		startAddColliderPointer++;
	}

	RigidBody() {
		mainScene.physicEngine.rigidBodyNum++;
	}
	~RigidBody() {
		if (colliders != NULL) {
			delete colliders;
		}
	}
	void Init() override {
		gameObject->rigidBody = this;
	}

	void Awake() override {
		mainScene.physicEngine.AwakeAddRigidBody(this);
	}
};