#pragma once

class Vector3 {
public:
	double x, y, z;
	Vector3(double x, double y, double z);
	Vector3();
	Vector3& operator=(const Vector3& rhs);
	Vector3& operator+=(const Vector3& rhs);
	Vector3& operator-=(const Vector3& rhs);
	const Vector3 operator+(const Vector3& rhs)const;
	const Vector3 operator- (const Vector3& rhs)const;
	const Vector3 operator- ()const;
	const Vector3 operator* (double rhs)const;
	const Vector3 operator/ (double rhs)const;
	Vector3& operator*=(double rhs);
	Vector3& operator/=(double rhs);
	//模
	double magnitude() const;
	//模的平方
	double sqrtMagnitude()const;
	//归一化
	Vector3& Normalize();
	//归一化后，只读
	const Vector3 normalized() const;
	//点乘
	static double Dot(const Vector3& lhs, const Vector3& rhs);
	//叉乘
	static const Vector3 Cross(const Vector3& lhs, const Vector3& rhs);
	//线性插值
	static const Vector3 Lerp(const Vector3& lhs, const Vector3& rhs, double k);


	//默认值表列
	static const Vector3 up;
	static const Vector3 down;
	static const Vector3 left;
	static const Vector3 right;
	static const Vector3 forward;
	static const Vector3 back;
	static const Vector3 zero;
	static const Vector3 one;

};
