#include "UnityIndex.h"

const Vector3 Transform::eulerAngle() const {
	return rotation.EulerAngle();
}
Transform::Transform(GameObject* g) :gameObject(g), localNeedFlush(true), worldNeedFlush(true) {
	localPosition = Vector3::zero;
	rotation = Quaternion::identity;
	localMatrix = Matrix::identity;
}
Transform::Transform(Vector3 pos, Quaternion rot) : localNeedFlush(true), worldNeedFlush(true) {
	localPosition = pos;
	rotation = rot;
	localMatrix = Matrix::identity;
}
Transform::~Transform() {

}
void Transform::Translate(const Vector3& transition) {
	localPosition += transition;
	Flush();
}
void Transform::Translate(double x, double y, double z) {
	localPosition += Vector3(x, y, z);
	Flush();
}
void Transform::Rotate(Quaternion& rot, Space space) {
	Quaternion world;
	switch (space) {
	case Self:
		world = GetWorldMatrix().GetRotation();
		rotation = world * rot * ~world * rotation;
		break;
	case World:
		rotation = rot * rotation;
		break;
	}
	Flush();
	//rotation = rot * rotation;
}
void Transform::Rotate(double x, double y, double z, Space space) {
	Rotate(Quaternion::Euler(x, y, z), space);
}
void Transform::SetLocalPosition(const Vector3 & pos)
{
	localPosition = pos;
	Flush();
}
void Transform::SetLocalPosition(double x, double y, double z)
{
	SetLocalPosition(Vector3(x, y, z));
}
void Transform::SetRotation(Quaternion & rot)
{
	rotation = rot;
	Flush();
}
Matrix& Transform::GetLocalMatrix()
{
	if (!localNeedFlush)return localMatrix;
	localMatrix.Set(localPosition, rotation);
	localNeedFlush = false;
	return localMatrix;
}

Matrix& Transform::GetWorldMatrix()
{
	if (!worldNeedFlush)return worldMatrix;
	//ÏòÉÏµÝ¹é
	if (gameObject->parent == NULL)return GetLocalMatrix();
	worldMatrix = (gameObject->parent->transform.GetWorldMatrix()) * GetLocalMatrix();
	worldNeedFlush = false;
	//printf("getWorld");
	return worldMatrix;
}

void Transform::Flush()
{
	localNeedFlush = true;
	FlushDown();
}

void Transform::FlushDown()
{
	rotation.Normalize();
	if (worldNeedFlush) return;
	worldNeedFlush = true;
	if (gameObject->next != NULL)
		gameObject->next->transform.FlushDown();
	if (gameObject->next != NULL)
		gameObject->child->transform.FlushDown();
}

const Vector3 Transform::forward()
{
	return -(rotation * Vector3::forward);
}

const Vector3 Transform::right()
{
	return (rotation * Vector3::right);

}

const Vector3 Transform::up()
{
	return (rotation * Vector3::up);
}
