#include"UnityIndex.h"

void RigidBody::StartAddCollider(SphereCollider *pointer) {
	colliders[startAddColliderPointer] = pointer;
	startAddColliderPointer++;
}

void RigidBody::SetVelocity(const Vector3 & v)
{
	//Vector3 = 
	//TODO
	velocity = v;
}

RigidBody::RigidBody(double g) :g(g) {
	mainScene.physicEngine.rigidBodyNum++;
}
RigidBody::~RigidBody() {
	if (colliders != NULL) {
		delete colliders;
	}
}
void RigidBody::Init() {
	gameObject->rigidBody = this;
}

void RigidBody::Awake() {
	mainScene.physicEngine.AwakeAddRigidBody(this);
}

void RigidBody::FixedUpdate() {
	transform->Translate(velocity, Space::World);
	//printf_s("x: %.2f,y:%.2f,z:%.2f\n", velocity.x, velocity.y, velocity.z);
}
