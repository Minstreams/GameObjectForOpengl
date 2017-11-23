#pragma once
//
class Physics
{
public:
	//数组的大小，在类初始化时就应该赋好值
	int solidColliderNum = 0;
	int rigidBodyNum = 0;
private:
	//可以考虑在awake的时候初始化并赋值
	SphereCollider** solidColliders = NULL;
	RigidBody** rigidBodys = NULL;

	//用于引导添加
	int awakeSolidColliderNumPointer = 0;
	int awakeRigidBodyNumPointer = 0;
public:
	void AwakeInit() {
		if (solidColliderNum != 0) {
			solidColliders = new SphereCollider*[solidColliderNum];
		}
		if (rigidBodyNum != 0) {
			rigidBodys = new RigidBody*[rigidBodyNum];
		}
	}
	void StartInit() {
		for (int i = 0;i < rigidBodyNum;i++) {
			if (rigidBodys[i]->colliderNum != 0) {
				rigidBodys[i]->colliders = new SphereCollider*[rigidBodys[i]->colliderNum];
			}
		}
	}
	~Physics() {
		if (solidColliders != NULL) {
			delete solidColliders;
		}
		if (rigidBodys != NULL) {
			delete rigidBodys;
		}
	}
	void AwakeAddSolidCollider(SphereCollider *pointer) {
		solidColliders[awakeSolidColliderNumPointer] = pointer;
		awakeSolidColliderNumPointer++;
	}
	void AwakeAddRigidBody(RigidBody *pointer) {
		rigidBodys[awakeRigidBodyNumPointer] = pointer;
		awakeRigidBodyNumPointer++;
	}

	//Contract方法用于进行碰撞，并根据结果复写rigidBody的速度
	void Contract() {
		//对每一个rigidBody
		for (int r = 0; r < rigidBodyNum;r++) {
			//与静态碰撞箱检测
			for (int i = 0;i < solidColliderNum;i++) {
				Contract(rigidBodys[r], solidColliders[i]);
			}
			//与其他rigidBody检测
			for (int i = r + 1;i < rigidBodyNum;i++) {
				Contract(rigidBodys[r], rigidBodys[i]);
			}
		}
	}
private:
	void Contract(RigidBody* rigidBody, SphereCollider *solidCollider) {

	}
	void Contract(RigidBody* lhs, RigidBody* rhs) {

	}
};

