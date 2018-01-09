#pragma once
#include"UnityIndex.h"
//class Earth :public GameObject {
//public:
//	float rEarth;
//	Earth(const char* name, float r, const Vector3& pos, const Quaternion& rot) : GameObject(name, pos, rot), rEarth(r) {
//	}
//	Earth(const char* name) :GameObject(name), rEarth(5) {
//	}
//	void Render() override {
//		Shaders::List()->shader1.use();
//		Shaders::List()->shader1.LoadUniform();
//
//		//GLfloat earth_mat_ambient[] = { 0.0f, 0.0f, 0.5f, 1.0f };
//		//GLfloat earth_mat_diffuse[] = { 0.2f, 0.2f, 0.5f, 1.0f };
//		//GLfloat earth_mat_specular[] = { 0.1f, 0.1f, 0.1f, 1.0f };
//		//GLfloat earth_mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };
//		//GLfloat earth_mat_shininess = 30.0f;
//		//glMaterialfv(GL_FRONT, GL_AMBIENT, earth_mat_ambient);
//		//glMaterialfv(GL_FRONT, GL_DIFFUSE, earth_mat_diffuse);
//		//glMaterialfv(GL_FRONT, GL_SPECULAR, earth_mat_specular);
//		//glMaterialfv(GL_FRONT, GL_EMISSION, earth_mat_emission);
//		//glMaterialf(GL_FRONT, GL_SHININESS, earth_mat_shininess);
//
//		GLUquadric* qobj = gluNewQuadric();
//		gluQuadricTexture(qobj, GL_TRUE);
//		gluSphere(qobj, rEarth, 15, 15);
//		Shader::useNone();
//	}
//};
class ScaledTestModel :public GameObject {
public:
	ScaledTestModel(const char* name, const Vector3& pos, const Quaternion& rot, const Vector3& scale)
		: GameObject(name, pos, rot, scale) {}
	void Render() override {
		Models::List()->model1.draw(Shaders::List()->model4);
	}
};

class Ground :public GameObject {
public:
	Ground(const char* name, double height) :GameObject(name) {
		transform.localPosition.y = height - 1;
		transform.localScale = Vector3(2, 0.01, 2);
	}
	void Render()override {
		Shaders::List()->model4.use();
		Shaders::List()->model4.LoadUniform();
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
		//glDisable(GL_CULL_FACE);
		glColor3f(1, 1, 1);
		Shaders::List()->model4.use();
		Shaders::List()->model4.LoadUniform();
		glUniform1i(glGetUniformLocation(Shaders::List()->model4.programId,
				"texture_diffuse0"), 0);
		GLUquadric* qobj = gluNewQuadric();
		gluQuadricTexture(qobj, GL_TRUE);
		gluSphere(qobj, r, 30, 30);
		Shader::useNone();
		//glEnable(GL_CULL_FACE);
	}
};