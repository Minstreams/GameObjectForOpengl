#pragma once
enum Space {
	World,
	Self
};
//�������
class MonoBehavour {
public:
	char* name;
	MonoBehavour *next;
	GameObject *gameObject;
	Transform *transform;
	MonoBehavour();
	virtual ~MonoBehavour();
	//ÿһ֡������
	virtual void Update();
	//�ڼ������ʱ������
	virtual void Awake();
	//��ʼ������
	virtual void Start();
	//�������Ⱦ
	virtual void Render();
	virtual void OnDestroy();
};