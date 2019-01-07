#pragma once
#include<vector>
//物理引擎
class Physics
{
private:
	//地面参数
	//地面高度
	double floorHeight;
	//地面弹性
	double floorBoundness;

	//刚体表
	std::vector<RigidBody*> rigidBodyList;
	//碰撞箱表
	std::vector<SphereCollider*> sphereColliderList;
public:
	Physics();
	Physics(double height, double boundness);

	//设置地面参数
	void SetFloorParameters(double height, double boundness);
	//添加刚体
	void AddRigidBody(RigidBody *pointer);
	//添加碰撞箱
	void AddSphereCollider(SphereCollider *pointer);

	//Contract方法用于进行碰撞，并根据结果复写rigidBody的速度
	void Contract();
private:
	void Contract(RigidBody* rigidBody);
	void Contract(RigidBody* rigidBody, SphereCollider *solidCollider);
	void Contract(RigidBody* lhs, RigidBody* rhs);
};

