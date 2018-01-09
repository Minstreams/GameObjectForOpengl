#include "OpenglIndex.h"
#include "Lighting.h"

int LightData::num = 0;
float LightData::positions[3 * LIGHT_MAX_NUM] = {};	//光源位置
float LightData::colors[4 * LIGHT_MAX_NUM] = {};		//光源颜色
float LightData::itensities[LIGHT_MAX_NUM] = {};		//光源强度
float LightData::distanceSqrs[LIGHT_MAX_NUM] = {};	//点光源最大作用距离的平方
Vector3 LightData::pos[LIGHT_MAX_NUM] = {};
void LightData::FlushPositions()
{
	Quaternion rot = ~mainScene.camera.transform.rotation;
	Vector3 trans = mainScene.camera.transform.localPosition;
	Vector3 directLight = rot * pos[0];
	float *p = positions;
	p[0] = (float)directLight.x;
	p[1] = (float)directLight.y;
	p[2] = (float)directLight.z;
	for (int i = 1;i < num;i++) {
		p += 3;
		Vector3 posT = rot *(pos[i] - trans);
		p[0] = (float)posT.x;
		p[1] = (float)posT.y;
		p[2] = (float)posT.z;
	}
}
