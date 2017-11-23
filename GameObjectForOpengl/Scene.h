#pragma once
#include"SkyBox.h"
//场景
class Scene {
public:
	GameObject *root;
	GameObject camera;
	CSkyBox skyBox;
	Scene();
	~Scene();
	void Render();
	void SetCamera(const Vector3& pos, const Quaternion& rot);
	GameObject* AddGameObject(GameObject* g);
	//摧毁物体及其子物体
	void Destroy(GameObject* g);
	//摧毁物体及其同级物体
	void DestroyLayer(GameObject* g);
	void Awake();
	void Start();
	void Update();
	void FixedUpdate();
private:
	void Awake(GameObject* g);
	void Start(GameObject* g);
	void Update(GameObject* g);
	void FixedUpdate(GameObject* g);
	void RenderGameObjects(GameObject* g);
};
