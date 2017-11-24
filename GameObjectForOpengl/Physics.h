#pragma once
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
	void AwakeInit();
	void StartInit();
	~Physics();
	void AwakeAddSolidCollider(SphereCollider *pointer);
	void AwakeAddRigidBody(RigidBody *pointer);

	//Contract方法用于进行碰撞，并根据结果复写rigidBody的速度
	void Contract();
private:
	void Contract(RigidBody* rigidBody, SphereCollider *solidCollider);
	void Contract(RigidBody* lhs, RigidBody* rhs);
};

