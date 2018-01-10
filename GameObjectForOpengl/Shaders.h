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
	const Shader model4 = Shader("Model400.vert", "Model400.frag");
	const Shader basic4 = Shader("Basic400.vert", "Basic400.frag");
	const Shader unit4 = Shader("Unit400.vert", "Unit400.frag");
	const Shader texture4 = Shader("Texture400.vert", "Texture400.frag");
};

Shaders* Shaders::list = NULL;