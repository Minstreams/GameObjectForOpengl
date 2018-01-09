#pragma once

//变换组件
class Transform {
public:
	//本地坐标
	Vector3 localPosition;
	//旋转四元数
	Quaternion rotation;
	//本地缩放向量
	Vector3 localScale;
	//世界旋转四元数
	Quaternion worldRotation;
	bool worldRotationNeedFlush;

	//欧拉角
	const Vector3 eulerAngle()const;
	//连接的游戏物体
	GameObject* gameObject;
	//本地变换矩阵
	Matrix localMatrix;
	//本地变换矩阵是否需要刷新
	bool localNeedFlush;
	//世界变换矩阵
	Matrix worldMatrix;
	//世界变换矩阵是否需要刷新
	bool worldNeedFlush;

	Transform(GameObject* g);
	Transform(GameObject* g, const Vector3& pos, const Quaternion& rot);
	Transform(GameObject* g, const Vector3& pos, const Quaternion& rot, const Vector3& scale);
	~Transform();
	//平移
	void Translate(double x, double y, double z, Space space = Space::Self);
	//平移
	void Translate(const Vector3& transition, Space space = Space::Self);
	//旋转
	void Rotate(Quaternion& rot, Space space = Space::Self);
	//欧拉旋转
	void Rotate(double x, double y, double z, Space space = Space::Self);
	//设置位置
	void SetLocalPosition(const Vector3& pos);
	//设置位置
	void SetLocalPosition(double x, double y, double z);
	//设置旋转
	void SetRotation(Quaternion& rot);
	//获取并刷新本地变换矩阵
	Matrix& GetLocalMatrix();
	//获取并刷新世界变换矩阵
	Matrix& GetWorldMatrix();
	//获取父世界变换矩阵
	Matrix GetParentWorldMatrix();

	Quaternion GetWorldRotation();
	Quaternion GetParentWorldRotation();
	//获取世界坐标
	Vector3 GetPosition();
	//刷新矩阵
	void Flush(bool ifRotate = false);
	//向下更新世界矩阵
	void FlushDown(bool asRoot, bool ifRotate);
	const Vector3 forward();
	const Vector3 right();
	const Vector3 up();
};