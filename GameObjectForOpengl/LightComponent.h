#pragma once
//Opengl Lighting
//class LightComponent : public MonoBehavour {
//public:
//	static int flag;
//	int lightFlag;
//	LightComponent()
//	{
//		lightFlag = GL_LIGHT0 + flag;
//		flag++;
//	}
//	void Start() {
//		glEnable(lightFlag);
//		GLfloat sun_light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
//		GLfloat sun_light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
//		GLfloat sun_light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
//		glLightfv(lightFlag, GL_AMBIENT, sun_light_ambient);
//		glLightfv(lightFlag, GL_DIFFUSE, sun_light_diffuse);
//		glLightfv(lightFlag, GL_SPECULAR, sun_light_specular);
//	}
//	void Render() {
//		GLfloat sun_light_position[] = { 0,0,0,1 };
//		glLightfv(lightFlag, GL_POSITION, sun_light_position);
//	}
//
//};
//int LightComponent::flag = 0;

//自制Lighting
class LightComponent : public MonoBehaviour {
public:
	int id;
	Vector3 color;	//颜色
	float itensity;	//光照强度
	float distance;	//衰减距离
	LightComponent(const Vector3& color, float itensity, float distance) :color(color), itensity(itensity), distance(distance) {}
	LightComponent() :color(Vector3::one), itensity(1), distance(30) {}
	void Init() override {
		//确定id
		id = LightData::num;
		if (id >= LIGHT_MAX_NUM) {
			ShowWarnMessage("光源数量超过限制！！");
			gameObject->DestroyComponent(this);
			return;
		}
		LightData::num++;
	}
	void Start() override {
		//赋值
		FlushPosition();
		FlushParameters();
	}
	void Update() override {
		FlushPosition();
	}
private:
	//刷新位置信息
	void FlushPosition() {
		LightData::pos[id] = transform->GetPosition();
	}
	//刷新其他属性
	void FlushParameters() {
		float *pColor = LightData::colors + id * 4;
		pColor[0] = (float)color.x;
		pColor[1] = (float)color.y;
		pColor[2] = (float)color.z;
		pColor[3] = 1;
		LightData::itensities[id] = itensity;
		LightData::distanceSqrs[id] = distance * distance;
	}
};