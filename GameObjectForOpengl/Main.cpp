//图形框架
#include "GraphicStructure.h"
#include "Input.h"
//资源库
#include "Shaders.h"
#include "Models.h"
#include "Textures.h"
#include "GameObjects.h"
#include "Components.h"

void SetScene() {

	mainScene.SetCamera(Vector3(0, 10, 30), Quaternion::identity);	//设置相机位置
	mainScene.physicEngine.SetFloorParameters(0, 1);				//设置地面参数
	//AddComponent(new MouseRotater(0.3f, 0.3f));
	//AddComponent(new FPSMover());

	AddGameObject(new Ground("Ground", 0, 664, 724));

	AddGameObject(new Ball("Ball", 5, Vector3(10, 15, 0), Quaternion::identity));
	AddComponent(new RigidBody(5, 1));
	AddComponent(new SphereCollider(5, Vector3::zero, 1.01));
	AddComponent(new Gravity(30));

	AddChild(new Point("lPoint", 0.5, Vector3(0, 0, 10), Quaternion::identity));
	AddComponent(new LightComponent(Vector3(0.4, 0.6, 0.8), 3, 80));

	AddGameObject(new Ball("Ball", 3, Vector3(0, 15, 9), Quaternion::identity));
	AddComponent(new RigidBody(5, 1));
	AddComponent(new SphereCollider(3, Vector3::zero, 1.01));
	AddComponent(new Gravity(30));

	AddChild(new Point("lPoint", 0.5, Vector3(0, 0, 10), Quaternion::identity));
	AddComponent(new LightComponent());

	AddGameObject(new Ball("Ball", 3, Vector3(0, 15, 89), Quaternion::identity));
	AddComponent(new RigidBody(5, 1));
	AddComponent(new SphereCollider(3, Vector3::zero, 1.01));
	AddComponent(new Gravity(30));

	//AddChild(new Point("lPoint", 0.5, Vector3(0, 0, 10), Quaternion::identity));
	//AddComponent(new LightComponent(Vector3(0.9, 0.6, 0.1), 1.5, 40));

	AddGameObject(new ScaledTestModel("man", Vector3(0, 0, -80), Quaternion::identity, Vector3::one * 0.05));
	AddComponent(new SphereCollider(3, Vector3(0, 3, 0)));

	AddGameObject(new ScaledTestModel("man", Vector3(20, 0, -80), Quaternion::identity, Vector3::one * 0.5));
	AddComponent(new SphereCollider(3, Vector3(0, 3, 0)));

	AddGameObject(new ScaledTestModel("man", Vector3(40, 0, -80), Quaternion::identity, Vector3::one * 0.5));
	AddComponent(new SphereCollider(3, Vector3(0, 3, 0)));

	AddGameObject(new ScaledTestModel("man", Vector3(60, 0, -80), Quaternion::identity, Vector3::one * 0.5));
	AddComponent(new SphereCollider(3, Vector3(0, 3, 0)));

	AddGameObject(new ScaledTestModel("man", Vector3(80, 0, -80), Quaternion::identity, Vector3::one * 0.5));
	AddComponent(new SphereCollider(3, Vector3(0, 3, 0)));

	AddGameObject(new ScaledTestModel("man", Vector3(100, 0, -80), Quaternion::identity, Vector3::one * 0.5));
	AddComponent(new SphereCollider(3, Vector3(0, 3, 0)));

	AddGameObject(new ScaledTestModel("man", Vector3(120, 0, -80), Quaternion::identity, Vector3::one * 0.5));
	AddComponent(new SphereCollider(3, Vector3(0, 3, 0)));

	AddGameObject(new Earth("Earth", Vector3(80, 100, -80), Quaternion::identity, Vector3::one * 0.25));
	AddComponent(new AutoRotate(Vector3(0, 5, 0)));

	GameObject *car =
		AddGameObject(new GameObject("Car", Vector3::zero, Quaternion::identity));
	AddComponent(new RigidBody(10, 4));
	AddComponent(new SphereCollider(5, Vector3(0, 5, 0)));
	AddComponent(new Gravity(20));

	AddChild(new GameObject("ModelParent", Vector3::zero, Quaternion::identity));
	car->AddComponent(new CarController(50, &currentGameObjectPointer->transform));

	AddChild(new CarModel("Model", Vector3(0, 0, 0), Quaternion::EulerY(-90), Vector3::one * 2));


	car->AddChild(new GameObject("CamFocusPoint", Vector3(0, 4, 0), Quaternion::identity));
	AddComponent(new MouseRotater(0.3f, 0.3f));
	mainScene.camera.AddComponent(new Tracker(&currentGameObjectPointer->transform, 0.5, true, false));

	AddChild(new GameObject("CamPoint", Vector3(0, 0, 16), Quaternion::identity));
	mainScene.camera.AddComponent(new Tracker(&currentGameObjectPointer->transform));
	mainScene.camera.AddComponent(new CamVelocityRecorder());

	AddGameObject(new GameObject("Rain"));
	AddComponent(new RainComponent(&car->transform, Vector3(0.6f, 0.6f, 0.6f), 200, 80, 98, 50, 0.01f, 0.1f, 1000, 2, 1));
}

void SetLight() {
	//设定第一个光源，即平行光
	LightData::num++;

	LightData::pos[0] = Vector3(0.5, 1, 1);	//光的方向为从这个点到原点

	LightData::colors[0] = 1;
	LightData::colors[1] = 1;
	LightData::colors[2] = 1;
	LightData::colors[3] = 1;

	LightData::itensities[0] = 1;

	LightData::distanceSqrs[0] = 1;

	shadowMapShader = Shaders::List()->shadowMap.programId;
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1920, 1080);
	glutCreateWindow("Opengl作业");

	//glutGameModeString("1920x1080");
	//设置全屏模式时使用的分辨率
	/*
	格式如下:
	“WxH:Bpp@Rr”
	W - 屏幕宽度的像素
	H - 屏幕高度的像素
	Bpp - 每个像素的比特数
	Rr - 垂直刷新的速率, 单位是赫兹(hz)

	在进行下一步之前, 注意这些设置只是请求到硬件.如果指定的模式是不可用, 设置会被忽略.
	例如:
	"800x600:32@100" - 屏幕大小800x600; 32位真色彩; 100赫兹 垂直刷新
	"640x480:16@75" - 屏幕大小640x480; 16位真色彩; 75赫兹

	下面这字符串模板用来设置需要的全屏设置是允许的:
	“WxH”
	“WxH : Bpp”
	“WxH@Rr”
	“@Rr”
	“:Bpp”
	“Bpp : @Rr”*/
	SetGameMode(true);
	Initial();
	glutMainLoop();

	return 0;
}
