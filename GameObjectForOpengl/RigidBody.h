#pragma once
/*刚体，必须加在关联的碰撞箱前面*/
class RigidBody :public MonoBehavour {
public:
	Vector3 velocity = Vector3::zero;

	//碰撞箱表
	std::vector<SphereCollider*> sphereColliderList;
	//重量
	double Mass;
private:
	//加速度大小
	double g;
public:

	//添加碰撞箱
	void AddSphereCollider(SphereCollider *pointer);
	//预计用于用加速度模拟设置速度
	void SetVelocity(const Vector3& v);

	//刚体，必须加在关联的碰撞箱前面
	RigidBody(double g = 10.0, double mass = 1);
	void Init() override;
	void Update() override;
	void FixedUpdate() override;
};