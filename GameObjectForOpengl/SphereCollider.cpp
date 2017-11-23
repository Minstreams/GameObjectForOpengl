#include"UnityIndex.h"
SphereCollider::SphereCollider(double r) :SphereCollider(r, Vector3::zero) {

}
SphereCollider::SphereCollider(double r, const Vector3& offset) : offset(offset), radius(r) {
	if (gameObject->rigidBody == NULL) {
		mainScene.physicEngine.solidColliderNum++;
	}
}
Vector3 SphereCollider::GetPosition() {
	if (transform->worldNeedFlush) {
		position = transform->GetWorldMatrix()*offset;
	}
	return position;
}
void SphereCollider::Awake() {
	position = transform->GetWorldMatrix()*offset;
	if (gameObject->rigidBody == NULL) {
		mainScene.physicEngine.AwakeAddSolidCollider(this);
	}
	else {
		gameObject->rigidBody->colliderNum++;
	}
}
void SphereCollider::Start() {
	if (gameObject->rigidBody != NULL) {
		gameObject->rigidBody->StartAddCollider(this);
	}
}
