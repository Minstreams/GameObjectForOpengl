#pragma once
extern int vectorNum;
class Vector3;
class Transform;
class MonoBehavour;
class GameObject;
class Scene;
//三位数组
class Vector3 {
public:
	float x, y, z;
	Vector3(float x, float y, float z);
	Vector3();
	Vector3& operator=(Vector3& rhs);
	Vector3& operator=(Vector3* rhs);
	Vector3& operator+=(Vector3& rhs);
	Vector3& operator+=(Vector3* rhs);
	Vector3 operator+ (Vector3& rhs);
	Vector3 operator+ (Vector3* rhs);
	Vector3& operator-=(Vector3& rhs);
	Vector3 operator- (Vector3& rhs);
	Vector3 operator* (float rhs);
	Vector3 operator/ (float rhs);
	Vector3& operator*=(float rhs);
	Vector3& operator/=(float rhs);
};

//变换组件
class Transform {
public:
	Vector3 position;
	Vector3 rotation;
	Transform();
	Transform(Vector3* pos, Vector3* rot);
	~Transform();
	void Translate(Vector3& transition);
	void Translate(float x, float y, float z);
	void Rotate(Vector3& rot);
	void Rotate(float x, float y, float z);

	//看来不可避免地要写矩阵了呢。。。
	Vector3 forward();
	Vector3 right();
	Vector3 up();
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
	virtual void OnDestroy();
};

//游戏物体
class GameObject {
public:
	GameObject* parent;
	GameObject* child;
	GameObject* next;

	Transform transform;

	MonoBehavour* componentsPointer;

	//构造函数
	GameObject(Vector3& position, Vector3& rotation);
	GameObject(Vector3* position, Vector3* rotation);
	GameObject(Vector3& position, Vector3* rotation);
	GameObject();
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

//场景
class Scene {
public:
	GameObject *root;
	GameObject camera;
	CSkyBox skyBox;
	Scene();
	~Scene();
	void Render();
	void SetCamera(Vector3* pos, Vector3 *rot);
	GameObject* AddGameObject(GameObject* g);
	//摧毁物体及其子物体
	void Destroy(GameObject* g);
	//摧毁物体及其同级物体
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