#pragma once
#include <windows.h>
#include <iostream>
#include <GL\glew.h>
#include <GL\glut.h>
#include "UnityIndex.h"
#include "Input.h"
#include "Texture.h"
#include "Shader.h"
#include "SkyBox.h"
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
void ShowWarnMessage(const char* message, const char* title = "警告");//显示警告信息

extern GLuint depthTex;
extern float shadowVP[16];
extern float viewReverseMat[16];
extern bool shadowOnly;
extern GLuint shadowFBO;
extern GLuint shadowMapShader;
extern int screenWidth;
extern int screenHeight;
#define SHADOWMAP_WIDTH 8192
#define SHADOWMAP_HEIGHT 8192

