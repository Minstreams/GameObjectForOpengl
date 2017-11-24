#pragma once
class LightComponent : public MonoBehavour {
public:
	int lightFlag;
	LightComponent(int lightFlag = GL_LIGHT0) :lightFlag(lightFlag)
	{

	}
	void Start() {
		GLfloat sun_light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		GLfloat sun_light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		GLfloat sun_light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		glLightfv(lightFlag, GL_AMBIENT, sun_light_ambient);
		glLightfv(lightFlag, GL_DIFFUSE, sun_light_diffuse);
		glLightfv(lightFlag, GL_SPECULAR, sun_light_specular);
	}
	void Render() {
		GLfloat sun_light_position[] = { 0, 0, 0, 1.0f };
		glLightfv(lightFlag, GL_POSITION, sun_light_position);
	}

};