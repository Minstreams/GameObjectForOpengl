#pragma once
#include <soil.h>

#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII
/*
纹理加载类
*/
class TextureHelper
{
public:
	/* 成功加载2D纹理则返回纹理对象Id 否则返回0
	*/
	static  GLuint load2DTexture(const char* filename, GLint internalFormat = GL_RGBA,
		GLenum picFormat = GL_RGBA, int loadChannels = SOIL_LOAD_RGBA);

	/* 使用2D纹理，若输入为0则取消使用纹理
	*/
	static void use2DTexture(GLuint textureId);

	/* 加载DDS纹理
	*/
	static GLuint loadDDS(const char * filename);
};
