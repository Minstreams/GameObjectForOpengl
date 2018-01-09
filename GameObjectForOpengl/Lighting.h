#pragma once
#define LIGHT_MAX_NUM 8
//光源数据格式
class LightData {
public:
	static int num;								//光源数量
	static float positions[3 * LIGHT_MAX_NUM];	//光源位置
	static float colors[4 * LIGHT_MAX_NUM];		//光源颜色
	static float itensities[LIGHT_MAX_NUM];		//光源强度
	static float distanceSqrs[LIGHT_MAX_NUM];	//点光源最大作用距离的平方
	static void FlushPositions();
	static Vector3 pos[LIGHT_MAX_NUM];
};

//TODO:新建一个cpp文件进行初始化，在SetLight函数里进行平行光的初始化