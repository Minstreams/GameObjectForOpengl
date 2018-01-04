#include"UnityIndex.h"

void RigidBody::AddSphereCollider(SphereCollider * pointer)
{
	sphereColliderList.push_back(pointer);
}

void RigidBody::SetVelocity(const Vector3 & v)
{
	//TODO
	//velocity = v;

	//尝试1：直接暴力插值
	//velocity = Vector3::Lerp(velocity, v, 0.01);

	//尝试2：用加速度模拟
	Vector3 delta = v - velocity;
	double distance = delta.magnitude();
	double a = g * deltaTime;
	if (distance < a || distance < 0.00001) {
		velocity = v;
	}
	else {
		velocity += delta * (a / distance);
	}
}

RigidBody::RigidBody(double g, double mass) :g(g), Mass(mass)
{

}

void RigidBody::Init() {
	gameObject->rigidBody = this;
	mainScene.physicEngine.AddRigidBody(this);
}

void RigidBody::Update()
{

}

void RigidBody::FixedUpdate() {
	transform->Translate(velocity * deltaTime, Space::World);
}
