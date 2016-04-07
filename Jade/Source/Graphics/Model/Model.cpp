/*
The MIT License (MIT)

Copyright (c) 2015 Ben Brown

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "Model.h"

std::vector<Jade::Graphics::Mesh> Jade::Graphics::Model::GetMeshes() const
{
	return meshes;
}

void Jade::Graphics::Model::Load(std::string filename)
{
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(filename, aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_GenUVCoords |
		aiProcess_GenNormals |
		aiProcess_FlipUVs);

	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "Assimp: Error - " << importer.GetErrorString() << std::endl;

		return;
	}

	// Process ASSIMP's root node recursively
	this->ProcessNode(scene->mRootNode, scene);
}

void Jade::Graphics::Model::ProcessNode(aiNode * node, const aiScene * scene)
{
	// Process each mesh located at the current node
	for (GLuint i = 0; i < node->mNumMeshes; i++)
	{
		// The node object only contains indices to index the actual objects in the scene. 
		// The scene contains all the data, node is just to keep stuff organized (like relations between nodes).
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		this->meshes.push_back(this->ProcessMesh(mesh, scene));
	}
	// After we've processed all of the meshes (if any) we then recursively process each of the children nodes
	for (GLuint i = 0; i < node->mNumChildren; i++)
	{
		this->ProcessNode(node->mChildren[i], scene);
	}
}

Jade::Graphics::Mesh Jade::Graphics::Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{	
	std::cout << "[Mesh Data]" << std::endl;

	Math::Vertex vertex;

	std::vector<Math::Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	// Grab the vertex position and colors for the mesh.
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		if (mesh->HasPositions())
		{
			aiVector3D aPosition = mesh->mVertices[i];
			Math::Vector3 position(aPosition.x, aPosition.y, aPosition.z);
			vertex.position = position;
		}

		if (mesh->HasNormals())
		{
			aiVector3D aNormal = mesh->mNormals[i];
			Math::Vector3 normal(aNormal.x, aNormal.y, aNormal.z);
			vertex.normal = normal;
		}

		if (mesh->HasTangentsAndBitangents())
		{
			aiVector3D aTangent = mesh->mTangents[i];
			Math::Vector3 tangent(aTangent.x, aTangent.y, aTangent.z);

			aiVector3D aBitangent = mesh->mBitangents[i];
			Math::Vector3 bitangent(aBitangent.x, aBitangent.y, aBitangent.z);
		}

		if (mesh->HasTextureCoords(0))
		{
			aiVector3D aTexCoord = mesh->mTextureCoords[0][i];
			Math::Vector2 texCoord(aTexCoord.x, aTexCoord.y);
			vertex.texCoord = texCoord;
		}

		vertices.push_back(vertex);
	}

	// Grab the indices for the mesh.
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];

		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	// Check to see if mesh has a texture.
	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* aMaterial = scene->mMaterials[mesh->mMaterialIndex];

		// Iterate though each texture type if they exist.
		for (unsigned int i = 0; i < aMaterial->GetTextureCount(aiTextureType_DIFFUSE); i++)
		{
			// Get the texture for the material.
			aiString string;
			aMaterial->GetTexture(aiTextureType_DIFFUSE, i, &string);
			std::cout << "Diffuse texture " << string.C_Str() << " was found..." << std::endl;
			textures.push_back(Texture(device, string.C_Str(), TextureType::Diffuse));
		}

		for (unsigned int i = 0; i < aMaterial->GetTextureCount(aiTextureType_SPECULAR); i++)
		{
			// Get the texture for the material.
			aiString string;
			aMaterial->GetTexture(aiTextureType_SPECULAR, i, &string);
			std::cout << "Specular texture " << string.C_Str() << " was found..." << std::endl;
			textures.push_back(Texture(device, string.C_Str(), TextureType::Specular));
		}

		for (unsigned int i = 0; i < aMaterial->GetTextureCount(aiTextureType_NORMALS); i++)
		{
			// Get the texture for the material.
			aiString string;
			aMaterial->GetTexture(aiTextureType_NORMALS, i, &string);
			std::cout << "Normal texture " << string.C_Str() << " was found..." << std::endl;
			textures.push_back(Texture(device, string.C_Str(), TextureType::Normal));
		}

		for (unsigned int i = 0; i < aMaterial->GetTextureCount(aiTextureType_AMBIENT); i++)
		{
			// Get the texture for the material.
			aiString string;
			aMaterial->GetTexture(aiTextureType_DIFFUSE, i, &string);
			std::cout << "Diffuse texture " << string.C_Str() << " was found..." << std::endl;
			textures.push_back(Texture(device, string.C_Str(), TextureType::Ambient));
		}
	}

	return Mesh(device, vertices, indices, textures);
}

void Jade::Graphics::Model::Draw()
{
	// Loop through and draw each mesh.
	for (unsigned int i = 0; i < meshes.size(); i++)
		meshes[i].Draw();
}