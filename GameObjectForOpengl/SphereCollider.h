#pragma once
//球形碰撞箱
class SphereCollider : public MonoBehavour {
public:
	const Vector3 offset;
	double radius;
	Vector3 position;	//世界坐标
	SphereCollider(double r);
	SphereCollider(double r, const Vector3& offset);
	//获取碰撞中心世界坐标
	Vector3 GetPosition();
private:
	void Awake() override;
	void Start() override;
};