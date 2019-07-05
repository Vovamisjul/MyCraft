#pragma once
#include "Shader.h"
#include "Mesh.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

class Model
{
public:
	Model(string path);
	void DrawVertices(Shader* shader);
	string directory;
	bool gammaCorrection;
private:
	vector<Mesh> meshes;
	vector<Texture> textures_loaded;

	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);
	unsigned int TextureFromFile(const char *path, const string &directory);
	
};