#include <Windows.h>
#include <iostream>
#include <GL\glew.h>
#include <math.h>
#include "TransformIndex.h"

/**
 * TODO: 待优化：去掉最后一列的无用计算
 *
 */

void glApplyMatrix(Matrix& m) {
	glMultMatrixd(m.m);
}

Matrix::Matrix() {
	m[0] = 1;m[1] = 0;m[2] = 0;m[3] = 0;
	m[4] = 0;m[5] = 1;m[6] = 0;m[7] = 0;
	m[8] = 0;m[9] = 0;m[10] = 1;m[11] = 0;
	m[12] = 0;m[13] = 0;m[14] = 0;m[15] = 1;
}
Matrix::Matrix(
	double m0, double m1, double m2, double m3,
	double m4, double m5, double m6, double m7,
	double m8, double m9, double m10, double m11,
	double m12, double m13, double m14, double m15) {
	m[0] = m0;m[1] = m1;m[2] = m2;m[3] = m3;
	m[4] = m4;m[5] = m5;m[6] = m6;m[7] = m7;
	m[8] = m8;m[9] = m9;m[10] = m10;m[11] = m11;
	m[12] = m12;m[13] = m13;m[14] = m14;m[15] = m15;
}
Matrix::~Matrix() {

}

//默认空矩阵
Matrix& Matrix::SetIdentity() {
	*this = identity;
	return *this;
}
//应用Vector作为平移矩阵
Matrix& Matrix::SetTransition(const Vector3&in) {
	m[12] = in.x;
	m[13] = in.y;
	m[14] = in.z;
	return *this;
}
//应用四元数作为旋转矩阵
Matrix& Matrix::SetRotation(const Quaternion&in) {
	double
		x2 = in.x*in.x,
		y2 = in.y*in.y,
		z2 = in.z*in.z,
		xy = in.x*in.y,
		xz = in.x*in.z,
		yz = in.y*in.z,
		wx = in.w*in.x,
		wy = in.w*in.y,
		wz = in.w*in.z;
	m[0] = 1 - 2 * (y2 + z2);
	m[4] = 2 * (xy - wz);
	m[8] = 2 * (wy + xz);
	m[1] = 2 * (xy + wz);
	m[5] = 1 - 2 * (x2 + z2);
	m[9] = 2 * (yz - wx);
	m[2] = 2 * (xz - wy);
	m[6] = 2 * (wx + yz);
	m[10] = 1 - 2 * (x2 + y2);
	return *this;
}
Matrix& Matrix::Set(const Vector3 & v, const Quaternion & q)
{
	SetTransition(v);
	SetRotation(q);
	return *this;
}
//获取四元数
Quaternion Matrix::GetRotation()const {
	double w = 0.5 * sqrt (1 + m[0] + m[5] + m[10]);
	double t = 1.0 / (4 * w);
	Quaternion out = Quaternion(
		(m[6] - m[9])*t,
		(m[8] - m[2])*t,
		(m[1] - m[4])*t,
		w
	).Normalize();

	return out;
}
Matrix Matrix::operator~() const
{
	//TODO
	exit(1);
	return Matrix();
}
//像数组一样访问矩阵(只读)
const double* Matrix::operator[](int row)const {
	const double* out = m + row * 4;
	return out;
}
//重载赋值符号
void Matrix::operator=(const Matrix&rhs) {
	for (int i = 0;i < 16;i++) {
		this->m[i] = rhs.m[i];
	}
}
//乘法
const Matrix Matrix::operator*(const Matrix&rhs)const {
	Matrix out;
	for (int r = 0;r < 4;r++) {
		for (int c = 0;c < 4;c++) {
			double tmp = 0;
			for (int i = 0;i < 4;i++) {
				tmp += (*this)[r][i] * rhs[i][c];
			}
			out.SetParam(r, c, tmp);
		}
	}
	return out;
}

const Vector3 Matrix::operator*(const Vector3 & rhs) const
{
	return Vector3(
		m[0] * rhs.x + m[4] * rhs.y + m[8] * rhs.z + m[12],
		m[1] * rhs.x + m[5] * rhs.y + m[9] * rhs.z + m[13],
		m[2] * rhs.x + m[6] * rhs.y + m[10] * rhs.z + m[14]
	);
}

const Vector3 Matrix::operator^(const Vector3 & rhs) const
{
	return Vector3(
		m[0] * rhs.x + m[4] * rhs.y + m[8] * rhs.z,
		m[1] * rhs.x + m[5] * rhs.y + m[9] * rhs.z,
		m[2] * rhs.x + m[6] * rhs.y + m[10] * rhs.z
	);
}

//单个赋值
void Matrix::SetParam(int row, int column, double value) {
	m[row * 4 + column] = value;
}
//对一行赋值
void Matrix::SetRow(int row, double v0, double v1, double v2, double v3) {
	double *mp = m + row * 4;
	mp[0] = v0;
	mp[1] = v1;
	mp[2] = v2;
	mp[3] = v3;
}
//取三个vector作为列向量
Matrix Matrix::VectorAsColumn(const Vector3& v1, const Vector3& v2, const Vector3& v3) {
	return Matrix(
		v1.x, v2.x, v3.x, 0,
		v1.y, v2.y, v3.y, 0,
		v1.z, v2.z, v3.z, 0,
		0, 0, 0, 1
	);
}
//取三个vector作为行向量
Matrix Matrix::VectorAsRow(const Vector3& v1, const Vector3& v2, const Vector3& v3) {
	return Matrix(
		v1.x, v1.y, v1.z, 0,
		v2.x, v2.y, v2.z, 0,
		v3.x, v3.y, v3.z, 0,
		0, 0, 0, 1
	);
}
void Matrix::OutPut()
{
	std::cout << "\n------------------\n" 
		<< m[0] << "\t," << m[1] << "\t," << m[2] << "\t," << m[3] << "\n" 
		<< m[4] << "\t," << m[5] << "\t," << m[6] << "\t," << m[7] << "\n"
		<< m[8] << "\t," << m[9] << "\t," << m[10] << "\t," << m[11] << "\n"
		<< m[12] << "\t," << m[13] << "\t," << m[14] << "\t," << m[15] << "\n"
		<< "\n------------------";
}
//像数组一样访问矩阵
double* Matrix::operator[](int row) {
	double* out = m + row * 4;
	return out;
}
//默认值
const Matrix Matrix::identity = Matrix();





