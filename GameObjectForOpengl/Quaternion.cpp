#include <math.h>
#include "TransformIndex.h"

Quaternion::Quaternion() :x(0), y(0), z(0), w(1) {
}
Quaternion::Quaternion(double x, double y, double z, double w) : x(x), y(y), z(z), w(w) {

}

//欧拉角
Vector3 Quaternion::EulerAngle() const {
	return Vector3(
		atan2(2 * (w*x + y*z), 1 - 2 * (x*x + y*y)),
		asin(2 * (w*y - z*x)),
		atan2(2 * (w*z + x*y), 1 - 2 * (y*y + z*z))
	);
}
//取模
double Quaternion::magnitude() {
	return sqrt(x*x + y*y + z*z + w*w);
}
double Quaternion::sqrtMagnitude()
{
	return x*x + y*y + z*z + w*w;
}
//归一化
Quaternion& Quaternion::Normalize() {
	double n = magnitude();
	x /= n;
	y /= n;
	z /= n;
	w /= n;
	return *this;
}
//用欧拉角创建四元数
Quaternion Quaternion::Euler(const Vector3 &in) {
	return Euler(in.x, in.y, in.z);
}

double InRange(double in) {
	while (in > 180)in -= 360;
	while (in < -180)in += 360;
	return in;
}
//用欧拉角创建四元数
Quaternion Quaternion::Euler(double x, double y, double z) {
	x = InRange(x);
	y = InRange(y);
	z = InRange(z);
	x /= PID;
	y /= PID;
	z /= PID;
	double
		sx = sin(x),
		cx = cos(x),
		sy = sin(y),
		cy = cos(y),
		sz = sin(z),
		cz = cos(z);
	Quaternion out(
		sx*cy*cz - cx*sy*sz,
		cx*sy*cz + sx*cy*sz,
		cx*cy*sz - sx*sy*cz,
		cx*cy*cz + sx*sy*sz
	);
	out.Normalize();
	return out;
}
//用欧拉角创建四元数
Quaternion Quaternion::EulerX(double x) {
	x /= PID;
	double
		sx = sin(x),
		cx = cos(x);
	return Quaternion(
		sx,
		0,
		0,
		cx
	);
}
//用欧拉角创建四元数
Quaternion Quaternion::EulerY(double y) {
	y /= PID;
	double
		sy = sin(y),
		cy = cos(y);
	return Quaternion(
		0,
		sy,
		0,
		cy
	);
}
//用欧拉角创建四元数
Quaternion Quaternion::EulerZ(double z) {
	z /= PID;
	double
		sz = sin(z),
		cz = cos(z);
	return Quaternion(
		0,
		0,
		sz,
		cz
	);
}
//绕定轴旋转
Quaternion Quaternion::RotationAround(Vector3 u, double angle) {
	u.Normalize();
	angle /= PID;
	double sinA = sin(angle);
	return Quaternion(
		u.x*sinA,
		u.y*sinA,
		u.z*sinA,
		cos(angle)
	);
}
Quaternion Quaternion::LookAtRotation(Vector3 forward, Vector3 up) {
	forward.Normalize();
	up.Normalize();
	Vector3 right = Vector3::Cross(forward, up);
	Matrix m = Matrix::VectorAsRow(right, up, forward);
	return m.GetRotation();
}
Quaternion Quaternion::FromToRotation(const Vector3& fromTo) {
	Vector3 forward = fromTo.normalized();
	Vector3 right = Vector3::Cross(forward, Vector3::up).normalized();
	Vector3 up = Vector3::Cross(right, forward);
	Matrix m = Matrix::VectorAsRow(right, up, forward);
	return m.GetRotation();
}
Quaternion Quaternion::FromToRotation(const Vector3& from, const Vector3& to) {
	return FromToRotation(to - from);
}
//点积
double Quaternion::Dot(const Quaternion&lhs, const Quaternion&rhs) {
	return lhs.x*rhs.x + lhs.y*rhs.y + lhs.z*rhs.z + lhs.w*rhs.w;
}
//角度
double Quaternion::Angle(const Quaternion&lhs, const Quaternion&rhs) {
	double out = acos(Dot(lhs, rhs) /*/ (lhs.Length*rhs.Length)*/);
	return out;
}
//线性插值
Quaternion Quaternion::Lerp(const Quaternion&a, const Quaternion&b, double t) {
	return Quaternion((1 - t) * a.x + t * b.x,
		(1 - t) * a.y + t * b.y,
		(1 - t) * a.z + t * b.z,
		(1 - t) * a.w + t * b.w);
}
//球形插值
Quaternion Quaternion::Slerp(const Quaternion &lhs, const Quaternion &rhs, double t)
{
	//double cos_theta = Dot(a, b);

	//// if B is on opposite hemisphere from A, use -B instead  
	//double sign;
	//if (cos_theta < 0)
	//{
	//	cos_theta = -cos_theta;
	//	sign = -1;
	//}
	//else sign = 1;

	//float c1, c2;
	//if (cos_theta > 1 - DBL_EPSILON)
	//{
	//	// if q2 is (within precision limits) the same as q1,  
	//	// just linear interpolate between A and B.  

	//	c2 = t;
	//	c1 = 1 - t;
	//}
	//else
	//{
	//	//float theta = gFloat::ArcCosTable(cos_theta);  
	//	// faster than table-based :  
	//	//const float theta = myacos(cos_theta);  
	//	double theta = acos(cos_theta);
	//	double sin_theta = sin(theta);
	//	double t_theta = t*theta;
	//	double inv_sin_theta = 1.f / sin_theta;
	//	c2 = sin(t_theta) * inv_sin_theta;
	//	c1 = sin(theta - t_theta) * inv_sin_theta;
	//}

	//c2 *= sign; // or c1 *= sign  
	//			// just affects the overrall sign of the output  

	//			// interpolate  
	//return Quaternion(a.x * c1 + b.x * c2, a.y * c1 + b.y * c2, a.z * c1 + b.z * c2, a.w * c1 + b.w * c2);
	double theta = Angle(lhs, rhs);
	double sintheta = sin(theta);
	Quaternion out = lhs*(sin((1 - t)*theta) / sintheta) + rhs*(sin(t*theta) / sintheta);
	out.Normalize();
	return out;
}
//赋值
void Quaternion::operator=(const Quaternion &rhs) {
	this->x = rhs.x;
	this->y = rhs.y;
	this->z = rhs.z;
	this->w = rhs.w;
}
//共轭
const Quaternion Quaternion::operator~() const {
	return Quaternion(-x, -y, -z, w);
}
//相加
const Quaternion Quaternion::operator+(const Quaternion&rhs) const {
	return Quaternion(
		x + rhs.x,
		y + rhs.y,
		z + rhs.z,
		w + rhs.w
	);
}
//乘积
const Quaternion Quaternion::operator*(const Quaternion&rhs) const {
	return Quaternion(
		x*rhs.w + w*rhs.x + y*rhs.z - z*rhs.y,
		y*rhs.w + w*rhs.y + z*rhs.x - x*rhs.z,
		z*rhs.w + w*rhs.z + x*rhs.y - y*rhs.x,
		w*rhs.w - x*rhs.x - y*rhs.y - z*rhs.z
	);
}
//数乘
Quaternion Quaternion::operator*(double rhs) const {
	return Quaternion(x*rhs, y*rhs, z*rhs, w*rhs);
}
//乘以向量
const Vector3 Quaternion::operator*(const Vector3&u) const {
	Vector3 v(x, y, z);
	Vector3 out = u*(2 * w*w - 1) + (Vector3::Cross(v, u)) * 2 * w + v * 2 * (Vector3::Dot(v, u));
	return out;
}


//默认值
const Quaternion Quaternion::identity = Quaternion(0, 0, 0, 1);