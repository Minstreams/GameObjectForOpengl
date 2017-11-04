#pragma once
class LightComponent : public MonoBehavour {
public:
	LightComponent() {
		lightPosSeted = false;
	}
	bool lightPosSeted;
	void Start() {
		GLfloat sun_light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		GLfloat sun_light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		GLfloat sun_light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		glLightfv(GL_LIGHT0, GL_AMBIENT, sun_light_ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_light_diffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, sun_light_specular);
	}
	void Render() {
		GLfloat sun_light_position[] = { 0, 0, 0, 1.0f };
		glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position);
	}

};