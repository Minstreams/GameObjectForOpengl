#pragma once
///<summary>
///刚体，必须加在关联的碰撞箱前面
///</summary>
class RigidBody :public MonoBehavour {
public:
	Vector3 velocity = Vector3::zero;
	//数组的大小，在类初始化时就应该赋好值
	int colliderNum = 0;
	//可以考虑在awake的时候初始化,在Start赋值
	SphereCollider** colliders = NULL;
	//重量
	double Mass;
private:
	//用于引导添加
	int startAddColliderPointer = 0;
	//加速度大小
	double g;
public:

	void StartAddCollider(SphereCollider *pointer);
	///<summary>
	///预计用于用加速度模拟设置速度
	///</summary>
	void SetVelocity(const Vector3& v);

	///<summary>
	///刚体，必须加在关联的碰撞箱前面
	///</summary>
	RigidBody(double g = 10.0, double mass = 1);
	~RigidBody();
	void Init() override;
	void Awake() override;
	void Update() override;
	void FixedUpdate() override;
};