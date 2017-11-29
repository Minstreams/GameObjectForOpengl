#pragma once
enum Space;
#include<iostream>
#include"TransformIndex.h"
#include<GL\glut.h>

class MonoBehavour;
class GameObject;
class Transform;
class SphereCollider;
class RigidBody;
class Physics;
class Scene;
extern Scene mainScene;
extern double deltaTime;

//以下是简化设置场景步骤 而加的方法
extern GameObject* currentGameObjectPointer;
extern GameObject* AddGameObject(GameObject* g);
extern GameObject* AddChild(GameObject *child);
extern MonoBehavour* AddComponent(MonoBehavour* component);

#include"MonoBehavour.h"
#include"transform.h"
#include"GameObject.h"
#include"SphereCollider.h"
#include"RigidBody.h"
#include"Physics.h"
#include"Scene.h"

