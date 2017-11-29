#pragma once

#include <map>
#include <assimp/scene.h>


/*
* 代表一个模型 模型可以包含一个或多个Mesh
*/
class Model
{
public:
	void draw(const Shader& shader) const;
	bool loadModel(const std::string& filePath);
	Model(const std::string& filePath);
	~Model();
private:
	/*
	* 递归处理模型的结点
	*/
	bool processNode(const aiNode* node, const aiScene* sceneObjPtr);
	bool processMesh(const aiMesh* meshPtr, const aiScene* sceneObjPtr, Mesh& meshObj);
	/*
	* 获取一个材质中的纹理
	*/
	bool processMaterial(const aiMaterial* matPtr, const aiScene* sceneObjPtr,
		const aiTextureType textureType, std::vector<Texture>& textures);
private:
	std::vector<Mesh> meshes; // 保存Mesh
	std::string modelFileDir; // 保存模型文件的文件夹路径
	typedef std::map<std::string, Texture> LoadedTextMapType; // key = texture file path
	LoadedTextMapType loadedTextureMap; // 保存已经加载的纹理
};
