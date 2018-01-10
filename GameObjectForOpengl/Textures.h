#pragma once
class TexID {
public:
	int id;
	TexID(const char *fileName) {
		char filePath[128];
		sprintf_s(filePath, "data/Textures/%s", fileName);
		id = TextureHelper::load2DTexture(filePath);
	}
};

class Textures {
private:
	static Textures* list;
public:
	static Textures* List() {
		if (list == NULL) {
			list = new Textures();
		}
		return list;
	}
	//以下是表列
	const TexID tex1 = TexID("test.png");
};

Textures* Textures::list = NULL;