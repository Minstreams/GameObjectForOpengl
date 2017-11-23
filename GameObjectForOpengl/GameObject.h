#pragma once

//游戏物体
class GameObject {
public:
	GameObject* parent;
	GameObject* child;
	GameObject* next;

	const char* Name;

	Transform transform;
	RigidBody *rigidBody;

	MonoBehavour* componentsPointer;

	//构造函数
	GameObject(const char* name, const Vector3& position,const Quaternion& rotation);
	GameObject(const char* name);
	~GameObject();
	//渲染
	virtual void Render();
	void SetParent(GameObject *parent);
	GameObject* AddChild(GameObject *child);

	//添加组件
	void AddComponent(MonoBehavour* component);
private:
	//设置父子关系
	static void SetParent(GameObject* parent, GameObject* child);
	//删除第一个组件
	void PopComponent();
};

