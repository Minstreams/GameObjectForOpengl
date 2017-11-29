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
	const Shader shader1 = Shader("model.vertex", "model.frag");
};

Shaders* Shaders::list = NULL;