#include "OpenglIndex.h"
#include "TransformIndex.h"
#include "ModelIndex.h"

#include "Shaders.h"
#include "Models.h"
#include "Textures.h"
#include "GameObjects.h"
#include "Components.h"

void SetScene() {

	mainScene.SetCamera(Vector3(0, 10, 30), Quaternion::identity);	//设置相机位置
	mainScene.physicEngine.SetFloorParameters(0, 1);				//设置地面参数
	AddComponent(new MouseRotater(0.3f, 0.3f));
	AddComponent(new FPSMover());

	AddGameObject(new Ground("Ground", 0, 100, 100));

	AddGameObject(new Ball("Ball", 5, Vector3(10, 15, 0), Quaternion::identity));
	AddComponent(new RigidBody(5, 1));
	AddComponent(new SphereCollider(5, Vector3::zero, 1.01));
	AddComponent(new Gravity(30));
	//AddComponent(new LightComponent());

	AddGameObject(new Ball("Ball", 3, Vector3(0, 15, 9), Quaternion::identity));
	AddComponent(new RigidBody(5, 1));
	AddComponent(new SphereCollider(3, Vector3::zero, 1.01));
	AddComponent(new Gravity(30));
	AddComponent(new LightComponent());

	AddGameObject(new Ball("Ball", 3, Vector3(0, 15, 89), Quaternion::identity));
	AddComponent(new RigidBody(5, 1));
	AddComponent(new SphereCollider(3, Vector3::zero, 1.01));
	AddComponent(new Gravity(30));
	AddComponent(new LightComponent());

	AddGameObject(new ScaledTestModel("Model", Vector3::zero, Quaternion::identity, Vector3(0.003, 0.003, 0.003)));
	AddComponent(new mover());
}

void SetLight() {
	//设定第一个光源，即平行光
	LightData::num++;

	LightData::pos[0] = Vector3(0, 1, 0.4);	//光的方向为从这个点到原点

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
	glutCreateWindow("图形学课设");

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
	//SetGameMode(true);
	Initial();
	glutMainLoop();

	return 0;
}
