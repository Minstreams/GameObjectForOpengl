#pragma once
#include "OpenglHeader.h"
//底层库
#include "ModelIndex.h"
#include "UnityIndex.h"
#define SHADOW_TEX_CNT 8	//shadowmap的存储位置


void Initial();//初始化
void BasicInitial();//基本初始化
void SceneInitial();
void SetUpShadowMap();
//场景初始化
void ChangeSize(int w, int h);
void RenderScene(void);
void TimerFunc(int value);
void SetScene();//编辑场景
void SetLight();//设置光源
void SetCursorVisible(bool visible);//设置光标是否可见
void SetGameMode(bool b);//设置全屏游戏模式，取消时会退出游戏

extern GLuint depthTex;
extern Matrix shadowVPM;
extern float shadowVP[16];
extern float viewReverseMat[16];
extern bool shadowOnly;
extern GLuint shadowFBO;
extern GLuint shadowMapShader;
extern int screenWidth;
extern int screenHeight;
#define SHADOWMAP_WIDTH 8192
#define SHADOWMAP_HEIGHT 8192

extern double deltaTime;
extern Scene mainScene;

//以下是简化设置场景步骤 而加的方法
extern GameObject* currentGameObjectPointer;
extern GameObject* AddGameObject(GameObject* g);
extern GameObject* AddChild(GameObject *child);
extern MonoBehaviour* AddComponent(MonoBehaviour* component);