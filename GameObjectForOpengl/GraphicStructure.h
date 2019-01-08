#pragma once
#include "OpenglHeader.h"
//�ײ��
#include "ModelIndex.h"
#include "UnityIndex.h"
#define SHADOW_TEX_CNT 8	//shadowmap�Ĵ洢λ��


void Initial();//��ʼ��
void BasicInitial();//������ʼ��
void SceneInitial();
void SetUpShadowMap();
//������ʼ��
void ChangeSize(int w, int h);
void RenderScene(void);
void TimerFunc(int value);
void SetScene();//�༭����
void SetLight();//���ù�Դ
void SetCursorVisible(bool visible);//���ù���Ƿ�ɼ�
void SetGameMode(bool b);//����ȫ����Ϸģʽ��ȡ��ʱ���˳���Ϸ

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

//�����Ǽ����ó������� ���ӵķ���
extern GameObject* currentGameObjectPointer;
extern GameObject* AddGameObject(GameObject* g);
extern GameObject* AddChild(GameObject *child);
extern MonoBehaviour* AddComponent(MonoBehaviour* component);