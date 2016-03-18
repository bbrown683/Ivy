#include <iostream>

#include "Model.h"

Jade::Math::Vertex* Jade::Graphics::Model::LoadModel(string filename)
{
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(filename, aiProcess_Triangulate);

	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "Assimp: Error - " << importer.GetErrorString() << std::endl;
		
		return nullptr;
	}

	for(unsigned int i = 0; i < scene->mRootNode->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[scene->mRootNode->mMeshes[i]];
	}

	return nullptr;
}

void Jade::Graphics::Model::Draw()
{
	// Loop through and draw each mesh.
	for(unsigned int i = 0; i < buffer.size(); i++)
	{
		buffer[i].Draw();
	}
}
