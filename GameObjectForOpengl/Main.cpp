#include "OpenglIndex.h"
#include "TransformIndex.h"
#include "UnityIndex.h"
#include "GameObjects.h"
#include "Components.h"

void SetScene() {

	mainScene.SetCamera(Vector3(0, 0, -300), Quaternion::EulerY(180));
	mainScene.camera.AddComponent(new MouseRotater(0.05f, 0.05f));
	mainScene.camera.AddComponent(new FPSMover());

	mainScene.AddGameObject(new Sun("t1", 6, Vector3(0, 0, 100), Quaternion::identity));

	GameObject *g = mainScene.AddGameObject(new Sun("Sun!"));
	g->AddComponent(new AutoRotate(Vector3(0, 12, 0)));//公转速度

	g = g->AddChild(new GameObject("Sun's Son", Vector3(80, 0, 0), Quaternion::identity));
	g->AddComponent(new AutoRotate(Vector3(0, -5, 0)));//抵消公转速度

	g = g->AddChild(new GameObject("Earth's parent", Vector3(0, 0, 0), Quaternion::Euler(Vector3(0, 0, 30))));
	g->AddComponent(new AutoRotate(Vector3(0, 10, 0)));//自转速度

	GameObject *earth = g->AddChild(new Earth("Earth"));
	earth->AddComponent(new LightComponent());
	earth->AddComponent(new PressLToShowPosition());

	g->AddComponent(new AutoRotate(Vector3(0, 60, 0)));//月球公转速度
	g = g->AddChild(new Moon("Moon", 2, Vector3(20, 0, 0), Quaternion::Euler(Vector3(0, 0, 0))));
	//g->AddComponent(new PressLToShowPosition());
}

void SetLight() {
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1280, 720);
	glutCreateWindow("日地月模型");

	Initial();
	glutMainLoop();

	return 0;
}
