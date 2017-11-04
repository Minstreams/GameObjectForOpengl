#pragma once
#include <windows.h>
#include <iostream>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
#include "UnityIndex.h"
#include "Input.h"
#include "CBMPLoader.h"
#include "SkyBox.h"
////////////////////////////////////////////////////////////////////////////
//实验要求：(1)理解OpenGL中的变换过程√                                   //
//          (2)理解透视投影与平行投影的不同√                             // 
//          (3)添加代码实现太阳、地球和月亮的运动模型√                   //
//          (4)了解深度测试√                                             //
//          (5)通过变换调整观察的位置与方向√                             //
//          (6)加入光照模型                                               //
////////////////////////////////////////////////////////////////////////////



void Initial();//初始化
void ChangeSize(int w, int h);
void RenderScene(void);
void TimerFunc(int value);
void SetScene();//编辑场景
void SetLight();//设置光源
void Keyboard(unsigned char key, int x, int y);