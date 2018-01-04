#pragma once
#include"UnityIndex.h"
class Earth :public GameObject {
public:
	float rEarth;
	Earth(const char* name, float r, const Vector3& pos, const Quaternion& rot) : GameObject(name, pos, rot), rEarth(r) {
	}
	Earth(const char* name) :GameObject(name), rEarth(5) {
	}
	void Render() override {
		Shaders::List()->shader1.use();
		Shaders::List()->shader1.LoadMatrix();

		//GLfloat earth_mat_ambient[] = { 0.0f, 0.0f, 0.5f, 1.0f };
		//GLfloat earth_mat_diffuse[] = { 0.2f, 0.2f, 0.5f, 1.0f };
		//GLfloat earth_mat_specular[] = { 0.1f, 0.1f, 0.1f, 1.0f };
		//GLfloat earth_mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		//GLfloat earth_mat_shininess = 30.0f;
		//glMaterialfv(GL_FRONT, GL_AMBIENT, earth_mat_ambient);
		//glMaterialfv(GL_FRONT, GL_DIFFUSE, earth_mat_diffuse);
		//glMaterialfv(GL_FRONT, GL_SPECULAR, earth_mat_specular);
		//glMaterialfv(GL_FRONT, GL_EMISSION, earth_mat_emission);
		//glMaterialf(GL_FRONT, GL_SHININESS, earth_mat_shininess);

		GLUquadric* qobj = gluNewQuadric();
		gluQuadricTexture(qobj, GL_TRUE);
		gluSphere(qobj, rEarth, 15, 15);
		Shader::useNone();
	}
};
class Sun :public GameObject {
public:
	float rSun;
	Sun(const char* name, float r, const Vector3& pos, const Quaternion& rot) : GameObject(name, pos, rot), rSun(r) {

	}
	Sun(const char* name) :GameObject(name), rSun(50) {

	}
	void Render() override {
		Shaders::List()->shader1.use();
		Shaders::List()->shader1.LoadMatrix();

		//GLfloat sun_mat_ambient[] = { 0.0f, 0.0f, 0.3f, 1.0f };
		//GLfloat sun_mat_diffuse[] = { 0.5f, 0.5f, 0.0f, 1.0f };
		//GLfloat sun_mat_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		//GLfloat sun_mat_emission[] = { 0.8f, 0.8f, 0.0f, 1.0f };
		//GLfloat sun_mat_shininess = 0.0f;
		//glMaterialfv(GL_FRONT, GL_AMBIENT, sun_mat_ambient);
		//glMaterialfv(GL_FRONT, GL_DIFFUSE, sun_mat_diffuse);
		//glMaterialfv(GL_FRONT, GL_SPECULAR, sun_mat_specular);
		//glMaterialfv(GL_FRONT, GL_EMISSION, sun_mat_emission);
		//glMaterialf(GL_FRONT, GL_SHININESS, sun_mat_shininess);

		//gluSphere(gluNewQuadric(), rSun, 30, 30);
		glutSolidSphere(rSun, 30, 30);

		Shader::useNone();
	}
};
class Moon :public GameObject {
public:
	float rMoon;
	Moon(const char* name, float r, const Vector3& pos, const Quaternion& rot) : GameObject(name, pos, rot), rMoon(r) {

	}
	Moon(const char* name) :GameObject(name), rMoon(2) {

	}
	void Render() override {
		Shaders::List()->shader1.use();
		Shaders::List()->shader1.LoadMatrix();
		/*
				GLfloat mat_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
				GLfloat mat_diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };
				GLfloat mat_specular[] = { 0.2f, 0.2f, 0.2f, 1.0f };
				GLfloat mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };
				GLfloat mat_shininess = 0.0f;
				glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
				glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
				glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
				glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);
		*/
		GLUquadric *obj = gluNewQuadric();
		gluSphere(obj, rMoon, 30, 30);

		Shader::useNone();
	}
};

class TestModel :public GameObject {
public:
	TestModel(const char* name) :GameObject(name) {}
	TestModel(const char* name, const Vector3& pos, const Quaternion& rot) : GameObject(name, pos, rot) {}
	void Render() override {
		Models::List()->model1.draw(Shaders::List()->shader1);
	}
};

class ScaledTestModel :public GameObject {
public:
	ScaledTestModel(const char* name, const Vector3& pos, const Quaternion& rot, const Vector3& scale)
		: GameObject(name, pos, rot, scale) {}
	void Render() override {
		Models::List()->model1.draw(Shaders::List()->shader1);
	}
};

class Ground :public GameObject {
public:
	Ground(const char* name, double height) :GameObject(name) {
		transform.localPosition.y = height - 1;
		transform.localScale = Vector3(2, 0.01, 2);
	}
	void Render()override {
		Shaders::List()->shader1.use();
		Shaders::List()->shader1.LoadMatrix();
		glutSolidCube(100);
		Shader::useNone();
	}
};

class Ball :public GameObject {
public:
	double r;
	Ball(const char* name, double r, const Vector3& pos, const Quaternion& rot, const Vector3& scale)
		: GameObject(name, pos, rot, scale), r(r) {}
	Ball(const char* name, double r, const Vector3& pos, const Quaternion& rot) : GameObject(name, pos, rot), r(r) {}
	Ball(const char* name, double r) :GameObject(name), r(r) {}
	void Render() override {
		Shaders::List()->shader1.use();
		Shaders::List()->shader1.LoadMatrix();
		glutSolidSphere(r, 15, 15);
		Shader::useNone();
	}
};