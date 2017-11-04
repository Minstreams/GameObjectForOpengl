#pragma once
class Quaternion {
public:
	double x, y, z, w;
	Quaternion();
	Quaternion(double x, double y, double z, double w);

	//欧拉角
	Vector3 EulerAngle() const;
	//取模
	double magnitude();
	//取模平方
	double sqrtMagnitude();
	//归一化
	Quaternion& Normalize();
	//用欧拉角创建四元数
	static Quaternion Euler(const Vector3 &in);
	//用欧拉角创建四元数
	static Quaternion Euler(double x, double y, double z);
	static Quaternion Quaternion::EulerX(double x);
	//用欧拉角创建四元数
	static Quaternion Quaternion::EulerY(double y);
	//用欧拉角创建四元数
	static Quaternion Quaternion::EulerZ(double z);
	//绕定轴旋转
	static Quaternion RotationAround(Vector3 u, double angle);
	static Quaternion LookAtRotation(Vector3 forward, Vector3 up);
	static Quaternion FromToRotation(const Vector3& fromTo);
	static Quaternion FromToRotation(const Vector3& from, const Vector3& to);
	//点积
	static double Dot(const Quaternion&lhs, const Quaternion&rhs);
	//角度
	static double Angle(const Quaternion&lhs, const Quaternion&rhs);
	//线性插值
	static Quaternion Lerp(const Quaternion&a, const Quaternion&b, double t);
	//球形插值
	static Quaternion Slerp(const Quaternion &lhs, const Quaternion &rhs, double t);
	//赋值
	void operator=(const Quaternion &rhs);
	//共轭
	const Quaternion operator~() const;
	//相加
	const Quaternion operator+(const Quaternion&rhs) const;
	//乘积
	const Quaternion operator*(const Quaternion&rhs) const;
	//数乘
	Quaternion operator*(double rhs) const;
	//乘以向量
	const Vector3 operator*(const Vector3&u) const;


	//默认值
	static const Quaternion identity;
};

