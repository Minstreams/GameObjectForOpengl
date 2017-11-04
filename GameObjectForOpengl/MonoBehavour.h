#pragma once
enum Space {
	World,
	Self
};
//组件父类
class MonoBehavour {
public:
	char* name;
	MonoBehavour *next;
	GameObject *gameObject;
	Transform *transform;
	MonoBehavour();
	virtual ~MonoBehavour();
	//每一帧被调用
	virtual void Update();
	//于加载组件时被调用
	virtual void Awake();
	//开始被调用
	virtual void Start();
	//额外的渲染
	virtual void Render();
	virtual void OnDestroy();
};