#include"UnityIndex.h"
SphereCollider::SphereCollider(double r) :offset(Vector3::zero), radius(r) {

}
SphereCollider::SphereCollider(double r, const Vector3& offset) : offset(offset), radius(r) {

}
Vector3 SphereCollider::GetPosition() {
	if (transform->worldNeedFlush) {
		position = transform->GetWorldMatrix()*offset;
	}
	return position;
}
void SphereCollider::Awake(){
	position = transform->GetWorldMatrix()*offset;
}
