#include <iostream>
#include <sstream>
#include <vector>
#include <GL\glew.h>
#include "TransformIndex.h"
#include "ModelIndex.h"



void Mesh::draw(const Shader& shader) const// ����Mesh
{
	if (VAOId == 0
		|| VBOId == 0
		|| EBOId == 0)
	{
		return;
	}
	//shader.use();
	glBindVertexArray(this->VAOId);
	int diffuseCnt = 0, specularCnt = 0, texUnitCnt = 0;
	for (std::vector<Texture>::const_iterator it = this->textures.begin();
		this->textures.end() != it; ++it)
	{
		switch (it->type)
		{
		case aiTextureType_DIFFUSE:
		{
			glActiveTexture(GL_TEXTURE0 + texUnitCnt);
			glBindTexture(GL_TEXTURE_2D, it->id);
			std::stringstream samplerNameStr;
			samplerNameStr << "texture_diffuse" << diffuseCnt++;
			glUniform1i(glGetUniformLocation(shader.programId,
				samplerNameStr.str().c_str()), texUnitCnt++);
		}
		break;
		case aiTextureType_SPECULAR:
		{
			glActiveTexture(GL_TEXTURE0 + texUnitCnt);
			glBindTexture(GL_TEXTURE_2D, it->id);
			std::stringstream samplerNameStr;
			samplerNameStr << "texture_specular" << specularCnt++;
			glUniform1i(glGetUniformLocation(shader.programId,
				samplerNameStr.str().c_str()), texUnitCnt++);
		}
		break;
		default:
			std::cerr << "Warning::Mesh::draw, texture type" << it->type
				<< " current not supported." << std::endl;
			break;
		}
	}
	glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
	//glBindVertexArray(0);
	//glUseProgram(0);
}
Mesh::Mesh() :VAOId(0), VBOId(0), EBOId(0) {}
Mesh::Mesh(const std::vector<Vertex>& vertData,
	const std::vector<Texture> & textures,
	const std::vector<GLuint>& indices) : VAOId(0), VBOId(0), EBOId(0) // ����һ��Mesh
{
	setData(vertData, textures, indices);
}
void Mesh::setData(const std::vector<Vertex>& vertData,
	const std::vector<Texture> & textures,
	const std::vector<GLuint>& indices)
{
	this->vertData = vertData;
	this->indices = indices;
	this->textures = textures;
	if (!vertData.empty() && !indices.empty())
	{
		this->setupMesh();
	}
}
void Mesh::final() const
{
	glDeleteVertexArrays(1, &this->VAOId);
	glDeleteBuffers(1, &this->VBOId);
	glDeleteBuffers(1, &this->EBOId);
}
Mesh::~Mesh()
{
	// ��Ҫ�������ͷ�VBO�ȿռ� ��ΪMesh���󴫵�ʱ ��ʱ�������ٺ����������VBO�ȿռ�
}
void Mesh::setupMesh()  // ����VAO,VBO�Ȼ�����
{
	glGenVertexArrays(1, &this->VAOId);
	glGenBuffers(1, &this->VBOId);
	glGenBuffers(1, &this->EBOId);

	glBindVertexArray(this->VAOId);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBOId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * this->vertData.size(),
		&this->vertData[0], GL_STATIC_DRAW);
	// ����λ������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
		sizeof(Vertex), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// ������������
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
		sizeof(Vertex), (GLvoid*)(3 * sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(1);
	// ���㷨��������
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE,
		sizeof(Vertex), (GLvoid*)(5 * sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(2);
	// ��������
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBOId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)* this->indices.size(),
		&this->indices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}