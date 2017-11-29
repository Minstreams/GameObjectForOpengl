#pragma once
//物理引擎
class Physics
{
private:
	//刚体表
	std::vector<RigidBody*> rigidBodyList;
	//碰撞箱表
	std::vector<SphereCollider*> sphereColliderList;
public:
	//添加刚体
	void AddRigidBody(RigidBody *pointer);
	//添加碰撞箱
	void AddSphereCollider(SphereCollider *pointer);

	//Contract方法用于进行碰撞，并根据结果复写rigidBody的速度
	void Contract();
private:
	void Contract(RigidBody* rigidBody, SphereCollider *solidCollider);
	void Contract(RigidBody* lhs, RigidBody* rhs);
};

