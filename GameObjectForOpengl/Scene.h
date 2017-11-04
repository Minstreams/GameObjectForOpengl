#pragma once
#include"SkyBox.h"
//����
class Scene {
public:
	GameObject *root;
	GameObject camera;
	CSkyBox skyBox;
	Scene();
	~Scene();
	void Render();
	void SetCamera(Vector3& pos, Quaternion& rot);
	GameObject* AddGameObject(GameObject* g);
	//�ݻ����弰��������
	void Destroy(GameObject* g);
	//�ݻ����弰��ͬ������
	void DestroyLayer(GameObject* g);
	void Awake();
	void Start();
	void Update();
private:
	void Awake(GameObject* g);
	void Start(GameObject* g);
	void Update(GameObject* g);
	void RenderGameObjects(GameObject* g);
};