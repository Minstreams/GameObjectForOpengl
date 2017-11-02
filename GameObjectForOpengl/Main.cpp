#include "OpenglPrefab.h"
#include "Input.h"

#include "GameObjects.h"
#include "Components.h"

void SetScene() {

	mainScene.SetCamera(new Vector3(0, 150, -300), new Vector3(-30, 180, 0));
	mainScene.camera.AddComponent(new MouseRotater(0.3f,0.3f));

	GameObject *g = mainScene.AddGameObject(new Sun());
	g->AddComponent(new AutoRotate(new Vector3(0, 5, 0)));//公转速度
	g = g->AddChild(new GameObject(new Vector3(80, 0, 0), new Vector3(0, 0, 0)));
	g->AddComponent(new AutoRotate(new Vector3(0, -5, 0)));//抵消公转速度
	g = g->AddChild(new GameObject(new Vector3(0, 0, 0), new Vector3(0, 0, 30)));
	g->AddComponent(new AutoRotate(new Vector3(0, 60, 0)));//自转速度
	GameObject *earth = g->AddChild(new Earth());
	g->AddComponent(new AutoRotate(new Vector3(0, 20, 0)));//月球公转速度
	g = g->AddChild(new Moon(2, new Vector3(20, 0, 0), new Vector3(0, 0, 0)));
}

void SetLight() {
	GLfloat sun_light_position[] = { 0.0f, 0, -300, 1.0f };
	GLfloat sun_light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat sun_light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat sun_light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, sun_light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, sun_light_specular);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1280, 720);
	glutCreateWindow("日地月模型");

	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);
	Input::Init();
	glutTimerFunc(100, TimerFunc, 1);

	Initial();
	glutMainLoop();

	return 0;
}
