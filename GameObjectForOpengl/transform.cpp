#include "UnityIndex.h"

Vector3 currentObjectScale = Vector3::one;

const Vector3 Transform::eulerAngle() const {
	return rotation.EulerAngle();
}
Transform::Transform(GameObject* g) :
	gameObject(g), localNeedFlush(true), worldNeedFlush(true), worldRotationNeedFlush(true)
{
	localPosition = Vector3::zero;
	rotation = Quaternion::identity;
	localScale = Vector3::one;
	localMatrix = Matrix::identity;
}
Transform::Transform(GameObject* g, const Vector3& pos, const Quaternion& rot) : gameObject(g), localNeedFlush(true), worldNeedFlush(true), worldRotationNeedFlush(true)
{
	localPosition = pos;
	rotation = rot;
	localScale = Vector3::one;
	localMatrix = Matrix::identity;
}
Transform::Transform(GameObject* g, const Vector3& pos, const Quaternion& rot, const Vector3& scale) : gameObject(g), localNeedFlush(true), worldNeedFlush(true), worldRotationNeedFlush(true)
{
	localPosition = pos;
	rotation = rot;
	localScale = scale;
	localMatrix = Matrix::identity;
}
Transform::~Transform() {

}
void Transform::Translate(const Vector3& transition, Space space) {
	if (space == Space::Self) {
		localPosition += rotation*transition;
	}
	else {
		localPosition += ~GetParentWorldRotation()* transition;
	}
	Flush();
}
void Transform::Translate(double x, double y, double z, Space space) {
	Translate(Vector3(x, y, z), space);
	Flush();
}
void Transform::Rotate(Quaternion& rot, Space space) {
	Quaternion world;
	switch (space) {
	case Self:
		rotation = rotation * rot;
		break;
	case World:
		rotation = rot * rotation;
		break;
	}
	Flush(true);
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
	Flush(true);
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
	if (!worldNeedFlush) {
		return worldMatrix;
	}
	//向上递归
	if (gameObject->parent == NULL) {
		worldMatrix = GetLocalMatrix();
		worldNeedFlush = false;
		return worldMatrix;
	}

	worldMatrix = GetLocalMatrix() * (gameObject->parent->transform.GetWorldMatrix());
	worldNeedFlush = false;
	//printf("getWorld");
	return worldMatrix;
}

Matrix Transform::GetParentWorldMatrix()
{
	if (gameObject->parent == NULL) {
		return Matrix();
	}
	return gameObject->parent->transform.GetWorldMatrix();
}

Quaternion Transform::GetWorldRotation()
{
	if (!worldRotationNeedFlush) {
		return worldRotation;
	}
	worldRotation = GetWorldMatrix().GetRotation();
	worldRotationNeedFlush = false;
	return worldRotation;
}

Quaternion Transform::GetParentWorldRotation()
{
	if (gameObject->parent == NULL) {
		return Quaternion::identity;
	}
	return gameObject->parent->transform.GetWorldRotation();
}

Vector3 Transform::GetPosition()
{
	Matrix m = GetWorldMatrix();
	//直接取矩阵平移量返回来优化
	return Vector3(
		m.m[12],
		m.m[13],
		m.m[14]
	);
}

void Transform::Flush(bool ifRotate)
{
	localNeedFlush = true;
	FlushDown(true, ifRotate);
}

void Transform::FlushDown(bool asRoot, bool ifRotate)
{
	if (!asRoot && gameObject->next != NULL)
		gameObject->next->transform.FlushDown(false, ifRotate);
	if (worldNeedFlush) return;
	worldNeedFlush = true;
	if (ifRotate) {
		worldRotationNeedFlush = true;
	}
	if (gameObject->child != NULL)
		gameObject->child->transform.FlushDown(false, ifRotate);
}

const Vector3 Transform::forward()
{
	return (GetWorldRotation() * Vector3::forward);
}

const Vector3 Transform::right()
{
	return (GetWorldRotation() * Vector3::right);
}

const Vector3 Transform::up()
{
	return (GetWorldRotation() * Vector3::up);
}
