#include"UnityIndex.h"

void Physics::AddRigidBody(RigidBody * pointer)
{
	rigidBodyList.push_back(pointer);
}

void Physics::AddSphereCollider(SphereCollider * pointer)
{
	sphereColliderList.push_back(pointer);
}

//Contract方法用于进行碰撞，并根据结果复写rigidBody的速度
void Physics::Contract() {
	//对每一个rigidBody
	for (unsigned int r = 0;r < rigidBodyList.size();r++) {
		//与静态碰撞箱检测
		for each(SphereCollider* s in sphereColliderList) {
			Contract(rigidBodyList[r], s);
		}
		//与其他rigidBody检测
		for (unsigned i = r + 1;i < rigidBodyList.size();i++) {
			Contract(rigidBodyList[r], rigidBodyList[i]);
		}
	}
}

void Physics::Contract(RigidBody* rigidBody, SphereCollider *solidCollider) {
	Vector3 pos = solidCollider->GetPosition();
	for each (SphereCollider* sp in rigidBody->sphereColliderList)
	{
		Vector3 delta = sp->GetPosition() - pos;
		double r = sp->radius + solidCollider->radius;

		double distance = delta.sqrtMagnitude();
		if (distance < r*r) {
			distance = sqrt(distance);
			//挤出
			rigidBody->transform->Translate(delta*((r - distance) / distance), Space::World);

			//printf_s("Contract!");

			//反弹
			delta /= distance;
			rigidBody->velocity -= delta * Vector3::Dot(rigidBody->velocity, delta) * ((solidCollider->boundness + sp->boundness) / 2 + 1);
		}
	}
}

//与其他rigidBody进行碰撞检测
void Physics::Contract(RigidBody* lhs, RigidBody* rhs) {
	for each (SphereCollider* rCollider in rhs->sphereColliderList)
	{
		for each (SphereCollider* lCollider in lhs->sphereColliderList)
		{
			Vector3 delta = rCollider->GetPosition() - lCollider->GetPosition();
			double r = lCollider->radius + rCollider->radius;
			double distance = delta.magnitude();

			if (distance < r) {
				double squeeze = (r - distance) / (2 * distance);
				Vector3 squeezeVec = delta * squeeze;

				//两边挤出
				lhs->transform->Translate(-squeezeVec, Space::World);
				rhs->transform->Translate(squeezeVec, Space::World);

				//反弹
				delta /= distance;

				double lv = Vector3::Dot(lhs->velocity, delta);
				double rv = Vector3::Dot(rhs->velocity, delta);

				double mSum = lhs->Mass + rhs->Mass;
				double lm = lhs->Mass / mSum;
				double rm = rhs->Mass / mSum;

				double lvResult = lv * (lm - rm - 1) + 2 * rm * rv;
				double rvResult = rv * (rm - lm - 1) + 2 * lm * lv;

				lhs->velocity += delta * lvResult;
				rhs->velocity += delta * rvResult;
			}
		}
	}
}
