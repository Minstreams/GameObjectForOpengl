#pragma once
class Shaders {
private:
	static Shaders* list;
public:
	static Shaders* List() {
		if (list == NULL) {
			list = new Shaders();
		}
		return list;
	}
	//以下是表列
	//const Shader shader1 = Shader("model.vertex", "model.frag");
	//const Shader test = Shader("Test.vert", "Test.frag");
	//const Shader testModel = Shader("TestModel.vert", "TestModel.frag");
	const Shader model4 = Shader("Model400.vert", "Model400.frag");
};

Shaders* Shaders::list = NULL;