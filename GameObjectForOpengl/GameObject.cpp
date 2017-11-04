#include"UnityIndex.h"

//构造函数
GameObject::GameObject(const char* name, const Vector3& position, const Quaternion& rotation) 
	:Name(name), parent(NULL), child(NULL), next(NULL), componentsPointer(NULL), transform(this) 
{
	transform.localPosition = position;
	transform.rotation = rotation;
}
GameObject::GameObject(const char* name)
	: Name(name), parent(NULL), child(NULL), next(NULL), componentsPointer(NULL), transform(this)
{

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
