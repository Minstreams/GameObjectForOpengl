#include <GL\glew.h>
#include"UnityIndex.h"

Scene::Scene() :root(NULL),camera("MainCamera"){

}
Scene::~Scene() {
	//清空场景
	DestroyLayer(root);
}
void Scene::Render() {
	//摄像机
	Matrix m;
	m.SetIdentity();
	m.SetRotation(~camera.transform.rotation);
	glApplyMatrix(m);
	skyBox.render();
	m.SetIdentity();
	m.SetTransition(-camera.transform.localPosition);
	glApplyMatrix(m);


	//物体
	if (root == NULL)return;
	RenderGameObjects(root);
}
void Scene::SetCamera(const Vector3& pos, const Quaternion& rot) {
	camera.transform.localPosition = pos;
	camera.transform.rotation = rot;
}
GameObject* Scene::AddGameObject(GameObject* g) {
	currentGameObjectPointer = g;
	if (root == NULL) {
		root = g;
		return g;
	}
	GameObject* p = root;
	while (p->next != NULL) {
		p = p->next;
	}
	p->next = g;
	g->SetParent(NULL);
	return g;
}
//摧毁物体及其子物体
void Scene::Destroy(GameObject* g) {
	if (g == NULL)return;
	DestroyLayer(g->child);
	delete g;
}
//摧毁物体及其同级物体
void Scene::DestroyLayer(GameObject* g) {
	if (g == NULL)return;
	DestroyLayer(g->next);
	Destroy(g);
}
void Scene::Awake() {
	Awake(&camera);
	Awake(root);
}
void Scene::Start() {
	Start(&camera);
	Start(root);
}
void Scene::Update() {
	Update(&camera);
	Update(root);
}
void Scene::FixedUpdate() {
	FixedUpdate(&camera);
	FixedUpdate(root);
}
void Scene::Awake(GameObject* g) {
	if (g == NULL)return;
	MonoBehavour *p = g->componentsPointer;
	while (p != NULL) {
		p->Awake();
		p = p->next;
	}
	Awake(g->child);
	Awake(g->next);
}
void Scene::Start(GameObject* g) {
	if (g == NULL)return;
	MonoBehavour *p = g->componentsPointer;
	while (p != NULL) {
		p->Start();
		p = p->next;
	}
	Start(g->child);
	Start(g->next);
}
void Scene::Update(GameObject* g) {
	if (g == NULL)return;
	MonoBehavour *p = g->componentsPointer;
	while (p != NULL) {
		p->Update();
		p = p->next;
	}
	Update(g->child);
	Update(g->next);
}
void Scene::FixedUpdate(GameObject* g) {
	physicEngine.Contract();
	if (g == NULL)return;
	MonoBehavour *p = g->componentsPointer;
	while (p != NULL) {
		p->FixedUpdate();
		p = p->next;
	}
	FixedUpdate(g->child);
	FixedUpdate(g->next);
}
void Scene::RenderGameObjects(GameObject* g) {
	if (g == NULL)return;
	glPushMatrix();
	glApplyMatrix(g->transform.GetLocalMatrix());
	g->Render();
	MonoBehavour *p = g->componentsPointer;
	while (p != NULL) {
		p->Render();
		p = p->next;
	}
	RenderGameObjects(g->child);
	glPopMatrix();
	RenderGameObjects(g->next);
}

GameObject* AddGameObject(GameObject* g) {
	mainScene.AddGameObject(g);
	return currentGameObjectPointer;
}
GameObject * AddChild(GameObject * child)
{
	currentGameObjectPointer->AddChild(child);
	return currentGameObjectPointer;
}
MonoBehavour * AddComponent(MonoBehavour * component)
{
	return currentGameObjectPointer->AddComponent(component);
}