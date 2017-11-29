#pragma once

#include <vector>
struct ShaderFile
{
	GLenum shaderType;
	const char* filePath;
	ShaderFile(GLenum type, const char* path)
		:shaderType(type), filePath(path) {}
};

class Shader
{
public:
	Shader(const char* vertexPath, const char* fragPath);
	Shader(const char* vertexPath, const char* fragPath, const char* geometryPath);
	void use() const;
	void LoadMatrix() const;
	static void useNone();
	~Shader();
public:
	GLuint programId;
private:
	/*
	* 从文件加载顶点和片元着色器
	* 传递参数为 [(着色器文件类型，着色器文件路径)+]
	*/
	void loadFromFile(std::vector<ShaderFile>& shaderFileVec);
	/*
	* 读取着色器程序源码
	*/
	bool loadShaderSource(const char* filePath, std::string& source);
};
