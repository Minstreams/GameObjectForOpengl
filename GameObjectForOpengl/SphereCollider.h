#pragma once
//球形碰撞箱
class SphereCollider : public MonoBehavour {
public:
	const Vector3 offset;
	double radius;
	Vector3 position;	//世界坐标
	SphereCollider(double r) :offset(Vector3::zero), radius(r) {

	}
	SphereCollider(double r, const Vector3& offset) :offset(offset), radius(r) {

	}
	//获取碰撞中心世界坐标
	Vector3 GetPosition() {
		if (transform->worldNeedFlush) {
			position = transform->GetWorldMatrix()*offset;
		}
		return position;
	}
private:
	void Awake() override {
		position = transform->GetWorldMatrix()*offset;
	}
};