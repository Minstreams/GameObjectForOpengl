#include "OpenglPrefab.h"

int vectorNum;

Vector3::Vector3(float x, float y, float z) :x(x), y(y), z(z) {
	//测试垃圾回收结果
	vectorNum++;
}
Vector3::Vector3() : x(0), y(0), z(0) {
	//测试垃圾回收结果
	vectorNum--;
}
Vector3& Vector3::operator=(Vector3& rhs) {
	this->x = rhs.x;
	this->y = rhs.y;
	this->z = rhs.z;
	return *this;
}
Vector3& Vector3::operator=(Vector3* rhs) {
	this->x = rhs->x;
	this->y = rhs->y;
	this->z = rhs->z;
	delete rhs;
	return *this;
}
Vector3& Vector3::operator+=(Vector3& rhs) {
	*this = *this + rhs;
	return *this;
}
Vector3& Vector3::operator+=(Vector3* rhs) {
	*this = *this + rhs;
	return *this;
}
Vector3 Vector3::operator+ (Vector3& rhs) {
	Vector3 tmp = *this;
	tmp.x += rhs.x;
	tmp.y += rhs.y;
	tmp.z += rhs.z;;
	return tmp;
}
Vector3 Vector3::operator+ (Vector3* rhs) {
	Vector3 tmp = *this;
	tmp.x += rhs->x;
	tmp.y += rhs->y;
	tmp.z += rhs->z;
	delete rhs;
	return tmp;
}
Vector3& Vector3::operator-=(Vector3& rhs) {
	*this = *this - rhs;
	return *this;
}
Vector3 Vector3::operator- (Vector3& rhs) {
	Vector3 tmp = *this;
	tmp.x -= rhs.x;
	tmp.y -= rhs.y;
	tmp.z -= rhs.z;;
	return tmp;
}
Vector3 Vector3::operator* (float rhs) {
	Vector3 tmp = *this;
	tmp.x *= rhs;
	tmp.y *= rhs;
	tmp.z *= rhs;
	return tmp;
}
Vector3 Vector3::operator/ (float rhs) {
	Vector3 tmp = *this;
	tmp.x /= rhs;
	tmp.y /= rhs;
	tmp.z /= rhs;
	return tmp;
}
Vector3& Vector3::operator*=(float rhs) {
	*this = *this * rhs;
	return *this;
}
Vector3& Vector3::operator/=(float rhs) {
	*this = *this / rhs;
	return *this;
}

Transform::Transform() {
	position = new Vector3(0, 0, 0);
	rotation = new Vector3(0, 0, 0);
}
Transform::Transform(Vector3* pos, Vector3* rot) {
	position = pos;
	rotation = rot;
}
Transform::~Transform() {

}
void Transform::Translate(Vector3& transition) {
	position += transition;
}
void Transform::Translate(float x, float y, float z) {
	position += new Vector3(x, y, z);
}
void Transform::Rotate(Vector3& rot) {
	rotation += rot;
}
void Transform::Rotate(float x, float y, float z) {
	rotation += new Vector3(x, y, z);
}
Vector3 Transform::forward() {
	Vector3 out(0, 0, 0);
	return out;
}
Vector3 Transform::right() {
	Vector3 out(0, 0, 0);
	return out;
}
Vector3 Transform::up() {
	Vector3 out(0, 0, 0);
	return out;
}


MonoBehavour::MonoBehavour() :next(NULL) {

}
MonoBehavour::~MonoBehavour() {
	OnDestroy();
}
void MonoBehavour::Update() {

}
void MonoBehavour::Awake() {

}
void MonoBehavour::Start() {

}
void MonoBehavour::OnDestroy() {

}


//构造函数
GameObject::GameObject(Vector3& position, Vector3& rotation) :parent(parent) {
	GameObject();
	transform.position = position;
	transform.rotation = rotation;
}
GameObject::GameObject(Vector3* position, Vector3* rotation) : parent(parent) {
	GameObject();
	transform.position = position;
	transform.rotation = rotation;
}
GameObject::GameObject(Vector3& position, Vector3* rotation) : parent(parent) {
	GameObject();
	transform.position = position;
	transform.rotation = rotation;
}
GameObject::GameObject() : parent(NULL), child(NULL), next(NULL), componentsPointer(NULL) {

}
GameObject::~GameObject() {
	//清空组件
	while (componentsPointer != NULL)
		PopComponent();
}
//渲染
void GameObject::Render() {

}
void GameObject::SetParent(GameObject *parent) {
	SetParent(parent, this);
}
GameObject* GameObject::AddChild(GameObject *child) {
	SetParent(this, child);
	return child;
}

//添加组件
void GameObject::AddComponent(MonoBehavour* component) {
	component->next = componentsPointer;
	componentsPointer = component;
	component->gameObject = this;
	component->transform = &transform;
	component->Awake();
}
//设置父子关系
void GameObject::SetParent(GameObject* parent, GameObject* child) {
	child->parent = parent;
	if (parent == NULL) return;
	if (parent->child == NULL) {
		parent->child = child;
		return;
	}
	GameObject* pc = parent->child;
	while (pc->next != NULL) {
		pc = pc->next;
	}
	pc->next = child;
}
//删除第一个组件
void GameObject::PopComponent() {
	if (componentsPointer != NULL) {
		MonoBehavour* pointer = componentsPointer->next;
		delete componentsPointer;
		componentsPointer = pointer;
	}
}




Scene::Scene() :root(NULL) {

}
Scene::~Scene() {
	//清空场景
	DestroyLayer(root);
}
void Scene::Render() {
	//摄像机
	glRotatef(camera.transform.rotation.x, -1, 0, 0);
	glRotatef(camera.transform.rotation.z, 0, 0, -1);
	glRotatef(camera.transform.rotation.y, 0, -1, 0);
	skyBox.render();
	glTranslatef(-camera.transform.position.x, -camera.transform.position.y, -camera.transform.position.z);


	//物体
	if (root == NULL)return;
	RenderGameObjects(root);
}
void Scene::SetCamera(Vector3* pos, Vector3 *rot) {
	camera.transform.position = pos;
	camera.transform.rotation = rot;
}
GameObject* Scene::AddGameObject(GameObject* g) {
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
void Scene::RenderGameObjects(GameObject* g) {
	if (g == NULL)return;
	glPushMatrix();
	glTranslatef(g->transform.position.x, g->transform.position.y, g->transform.position.z);
	glRotatef(g->transform.rotation.x, 1, 0, 0);
	glRotatef(g->transform.rotation.z, 0, 0, 1);
	glRotatef(g->transform.rotation.y, 0, 1, 0);
	g->Render();
	RenderGameObjects(g->child);
	glPopMatrix();
	RenderGameObjects(g->next);
}
