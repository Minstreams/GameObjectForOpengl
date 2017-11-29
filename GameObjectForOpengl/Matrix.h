#pragma once

//矩阵类
class Matrix
{
public:
	//矩阵本体
	double m[16];
	//默认值
	static const Matrix identity;
	Matrix();
	Matrix(
		double m0, double m1, double m2, double m3,
		double m4, double m5, double m6, double m7,
		double m8, double m9, double m10, double m11,
		double m12, double m13, double m14, double m15);
	~Matrix();
	//默认空矩阵
	Matrix& SetIdentity();
	//应用Vector作为平移矩阵
	Matrix& SetTransition(const Vector3&in);
	//应用四元数作为旋转矩阵
	Matrix& SetRotation(const Quaternion&in);
	//设置平移矩阵与旋转矩阵
	Matrix& Set(const Vector3&v, const Quaternion&q);
	//获取四元数
	Quaternion GetRotation()const;
	//获取逆矩阵
	Matrix operator~()const; 
	//像数组一样访问矩阵(只读)
	const double* operator[](int row)const;
	//重载赋值符号
	void operator=(const Matrix&rhs);
	//乘法
	const Matrix operator*(const Matrix&rhs)const;
	//对Vector应用矩阵
	const Vector3 operator*(const Vector3&rhs)const;
	//对Vector应用旋转矩阵
	const Vector3 operator^(const Vector3&rhs)const;

	//单个赋值
	void SetParam(int row, int column, double value);
	//对一行赋值
	void SetRow(int row, double v0, double v1, double v2, double v3);
	//取三个vector作为列向量
	static Matrix VectorAsColumn(const Vector3& v1, const Vector3& v2, const Vector3& v3);
	//取三个vector作为行向量
	static Matrix VectorAsRow(const Vector3& v1, const Vector3& v2, const Vector3& v3);

	void OutPut();
private:
	//像数组一样访问矩阵
	double* operator[](int row);
};

//应用矩阵
extern void glApplyMatrix(Matrix& m);

