#pragma once
#include <assimp\material.h>
#include "Vector3.h"

struct vec2 {
	vec2() :vec2(0, 0)
	{
	}
	vec2(float x, float y) :x(x), y(y) {
	}
	float x;
	float y;
};
struct vec3 {
	vec3() :vec3(0, 0, 0)
	{
	}
	vec3(float x, float y, float z) :x(x), y(y), z(z) {
	}
	float x;
	float y;
	float z;
};

// 表示一个顶点属性
struct Vertex
{
	vec3 position;
	vec2 texCoords;
	vec3 normal;
	vec3 tangent;
};

// 表示一个Texture
struct Texture
{
	int id;
	aiTextureType type;
	std::string path;
};
// 表示一个用于渲染的最小实体
class Mesh
{
public:
	void draw(const Shader& shader) const;// 绘制Mesh
	Mesh();
	Mesh(const std::vector<Vertex>& vertData,
		const std::vector<Texture> & textures,
		const std::vector<GLuint>& indices); // 构造一个Mesh
	void setData(const std::vector<Vertex>& vertData,
		const std::vector<Texture> & textures,
		const std::vector<GLuint>& indices);
	void final() const;
	~Mesh();
private:
	std::vector<Vertex> vertData;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;
	GLuint VAOId, VBOId, EBOId;

	void setupMesh();  // 建立VAO,VBO等缓冲区
};
