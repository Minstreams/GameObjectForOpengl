#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
//#include "GameObject.h"

/*
int vectorNum;

class GameObject {
public:
	GameObject* parent;
	GameObject* child;
	GameObject* next;

	Transform transform;

	MonoBehavour* componentsPointer;

	//构造函数
	GameObject(Vector3& position,Vector3& rotation) :parent(parent){
		GameObject();
		transform.position = position;
		transform.rotation = rotation;
	}
	GameObject(Vector3* position, Vector3* rotation) :parent(parent){
		GameObject();
		transform.position = position;
		transform.rotation = rotation;
	}
	GameObject(Vector3& position, Vector3* rotation) :parent(parent){
		GameObject();
		transform.position = position;
		transform.rotation = rotation;
	}
	GameObject() :parent(NULL), child(NULL), next(NULL), componentsPointer(NULL) {

	}
	~GameObject() {
		//清空组件
		while (componentsPointer != NULL)
			PopComponent();
	}
	//渲染
	virtual void Render() {

	}
	void SetParent(GameObject *parent) {
		this->parent = parent;
		parent->AddChild(this);
	}
	void AddChild(GameObject *child) {
		GameObject* p = child;
		while (p != NULL) {
			p = p->next;
		}
		p = child;
		child->SetParent(this);
	}
	//添加组件
	void AddComponent(MonoBehavour* component) {
		component->next = componentsPointer;
		componentsPointer = component;
	}
private:
	//删除第一个组件
	void PopComponent() {
		if (componentsPointer != NULL) {
			MonoBehavour* pointer = componentsPointer->next;
			delete componentsPointer;
			componentsPointer = pointer;
		}
	}
};

class MonoBehavour {
public:
	MonoBehavour* next;
	MonoBehavour() :next(NULL) {

	}
	virtual ~MonoBehavour() {
		OnDestroy();
	}
	virtual void Update() {

	}
	virtual void Awake() {

	}
	virtual void Start() {

	}
	virtual void OnDestroy() {

	}
};

class Transform {
public:
	Vector3 position;
	Vector3 rotation;
	Transform() {
		position = new Vector3(0, 0, 0);
		rotation = new Vector3(0, 0, 0);
	}
	Transform(Vector3* pos, Vector3* rot) {
		position = pos;
		rotation = rot;
	}
	~Transform() {

	}
	void Translate(Vector3& transition) {
		position += transition;
	}
	void Translate(float x, float y, float z) {
		position += new Vector3(x, y, z);
	}
};
class Vector3 {
public:
	float x, y, z;
	Vector3(float x, float y, float z):x(x),y(y),z(z) {
		//测试垃圾回收结果
		vectorNum++;
	}
	Vector3() :x(0), y(0), z(0) {
		//测试垃圾回收结果
		vectorNum--;
	}
	Vector3& operator=(Vector3& rhs) {
		this->x = rhs.x;
		this->y = rhs.y;
		this->z = rhs.z;
		return *this;
	}
	Vector3& operator=(Vector3* rhs) {
		this->x = rhs->x;
		this->y = rhs->y;
		this->z = rhs->z;
		delete rhs;
		return *this;
	}
	Vector3& operator+=(Vector3& rhs) {
		*this = *this + rhs;
		return *this;
	}
	Vector3& operator+=(Vector3* rhs) {
		*this = *this + rhs;
		return *this;
	}
	Vector3 operator+ (Vector3& rhs) {
		Vector3 tmp = *this;
		tmp.x += rhs.x;
		tmp.y += rhs.y;
		tmp.z += rhs.z;;
		return tmp;
	}
	Vector3 operator+ (Vector3* rhs) {
		Vector3 tmp = *this;
		tmp.x += rhs->x;
		tmp.y += rhs->y;
		tmp.z += rhs->z;
		delete rhs;
		return tmp;
	}
	Vector3& operator-=(Vector3& rhs) {
		*this = *this - rhs;
		return *this;
	}
	Vector3 operator- (Vector3& rhs) {
		Vector3 tmp = *this;
		tmp.x -= rhs.x;
		tmp.y -= rhs.y;
		tmp.z -= rhs.z;;
		return tmp;
	}
};
class Scene {
public:
	GameObject *root;
	Transform camera;
	Scene() :root(NULL) {

	}
	~Scene() {
		//清空场景
		DestroyLayer(root);
	}
	void Render() {
		//摄像机
		glRotatef(camera.rotation.y, 0, 1, 0);
		glRotatef(camera.rotation.z, 0, 0, 1);
		glRotatef(camera.rotation.x, 1, 0, 0);
		glTranslatef(camera.position.x, camera.position.y, camera.position.z);

		//物体
		RenderGameObjects(root);
	}
	void SetCamera(Vector3* pos, Vector3 rot) {
		camera.position = pos;
		camera.rotation = rot;
	}
	void AddGameObject(GameObject* g) {
		GameObject* p = root;
		while (p != NULL) {
			p = p->next;
		}
		p = g;
		g->SetParent(NULL);
	}
	//摧毁物体及其子物体
	void Destroy(GameObject* g) {
		if (g == NULL)return;
		DestroyLayer(g->child);
		delete g;
	}
	//摧毁物体及其同级物体
	void DestroyLayer(GameObject* g) {
		if (g == NULL)return;
		DestroyLayer(g->next);
		Destroy(g);
	}
	void Awake() {
		Awake(root);
	}
	void Start() {
		Start(root);
	}
	void Update() {
		Update(root);
	}
private:
	void Awake(GameObject* g) {
		MonoBehavour *p = g->componentsPointer;
		while (p != NULL) {
			p->Awake();
			p = p->next;
		}
		Awake(g->child);
		Awake(g->next);
	}
	void Start(GameObject* g) {
		MonoBehavour *p = g->componentsPointer;
		while (p != NULL) {
			p->Start();
			p = p->next;
		}
		Start(g->child);
		Start(g->next);
	}
	void Update(GameObject* g) {
		MonoBehavour *p = g->componentsPointer;
		while (p != NULL) {
			p->Update();
			p = p->next;
		}
		Update(g->child);
		Update(g->next);
	}
	void RenderGameObjects(GameObject* g) {
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
};
//*/