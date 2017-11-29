#include"UnityIndex.h"
SphereCollider::SphereCollider(double r) :SphereCollider(r, Vector3::zero, 0)
{

}
SphereCollider::SphereCollider(double r, const Vector3& offset) : SphereCollider(r, offset, 0)
{

}
SphereCollider::SphereCollider(double r, const Vector3 & offset, double boundness) : offset(offset), radius(r), boundness(boundness)
{

}
Vector3 SphereCollider::GetPosition() {
	if (transform->worldNeedFlush) {
		position = transform->GetWorldMatrix()*offset;
	}
	return position;
}
Vector3 SphereCollider::GetNextPosition()
{
	if (gameObject->rigidBody == NULL) {
		return GetPosition();
	}
	return transform->GetWorldMatrix()*offset + gameObject->rigidBody->velocity;
}
void SphereCollider::Awake() {
	position = transform->GetWorldMatrix()*offset;
	if (gameObject->rigidBody == NULL) {
		mainScene.physicEngine.AddSphereCollider(this);
	}
	else {
		gameObject->rigidBody->AddSphereCollider(this);
	}
}