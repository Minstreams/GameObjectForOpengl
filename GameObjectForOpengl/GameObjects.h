#pragma once
#include"UnityIndex.h"
class Earth :public GameObject {
public:
	float rEarth;
	Earth(const char* name, float r, Vector3& pos, Quaternion& rot) : GameObject(name, pos, rot), rEarth(r) {

	}
	Earth(const char* name) :GameObject(name), rEarth(5) {

	}
	void Render() override {
		GLfloat earth_mat_ambient[] = { 0.0f, 0.0f, 0.5f, 1.0f };
		GLfloat earth_mat_diffuse[] = { 0.2f, 0.2f, 0.5f, 1.0f };
		GLfloat earth_mat_specular[] = { 0.1f, 0.1f, 0.1f, 1.0f };
		GLfloat earth_mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		GLfloat earth_mat_shininess = 30.0f;
		glMaterialfv(GL_FRONT, GL_AMBIENT, earth_mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, earth_mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, earth_mat_specular);
		glMaterialfv(GL_FRONT, GL_EMISSION, earth_mat_emission);
		glMaterialf(GL_FRONT, GL_SHININESS, earth_mat_shininess);

		glutSolidSphere(rEarth, 15, 15);
	}
};
class Sun :public GameObject {
public:
	float rSun;
	Sun(const char* name, float r, Vector3& pos, Quaternion& rot) : GameObject(name, pos, rot), rSun(r) {

	}
	Sun(const char* name) :GameObject(name), rSun(50) {

	}
	void Render() override {
		GLfloat sun_mat_ambient[] = { 0.0f, 0.0f, 0.3f, 1.0f };
		GLfloat sun_mat_diffuse[] = { 0.5f, 0.5f, 0.0f, 1.0f };
		GLfloat sun_mat_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		GLfloat sun_mat_emission[] = { 0.8f, 0.8f, 0.0f, 1.0f };
		GLfloat sun_mat_shininess = 0.0f;
		glMaterialfv(GL_FRONT, GL_AMBIENT, sun_mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, sun_mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, sun_mat_specular);
		glMaterialfv(GL_FRONT, GL_EMISSION, sun_mat_emission);
		glMaterialf(GL_FRONT, GL_SHININESS, sun_mat_shininess);

		GLUquadric *obj = gluNewQuadric();
		gluSphere(obj, rSun, 30, 30);
	}
};
class Moon :public GameObject {
public:
	float rMoon;
	Moon(const char* name, float r, Vector3& pos, Quaternion& rot) : GameObject(name, pos, rot), rMoon(r) {

	}
	Moon(const char* name) :GameObject(name), rMoon(2) {

	}
	void Render() override {
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

		GLUquadric *obj = gluNewQuadric();
		gluSphere(obj, rMoon, 30, 30);
	}
};