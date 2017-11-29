#pragma once
//球形碰撞箱
class SphereCollider : public MonoBehavour {
public:
	const Vector3 offset;
	double radius;
	Vector3 position;	//世界坐标
	double boundness;	//弹性系数
	SphereCollider(double r);
	SphereCollider(double r, const Vector3& offset);
	SphereCollider(double r, const Vector3& offset, double boundness);
	//获取碰撞中心世界坐标
	Vector3 GetPosition();
	Vector3 GetNextPosition();
private:
	void Awake() override;
};