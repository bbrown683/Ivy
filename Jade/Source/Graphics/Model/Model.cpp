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

	const aiScene* scene = importer.ReadFile(filename, aiProcess_Triangulate |
		aiProcess_CalcTangentSpace |
		aiProcess_GenNormals |
		aiProcess_GenUVCoords |
		aiProcess_ConvertToLeftHanded |
		aiProcess_JoinIdenticalVertices | 
		aiProcess_SortByPType |
		aiProcess_TransformUVCoords);

	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "Assimp: Error - " << importer.GetErrorString() << std::endl;

		return;
	}
	
	if (scene->HasMeshes())
	{
		// Iterates through each mesh and assigns them their respective vertices and indices.
		for (unsigned int i = 0; i < scene->mNumMeshes; i++)
		{
			std::cout << "Mesh # : " << i + 1 << std::endl;

			// Set current mesh for assimp importer.
			const aiMesh* aMesh = scene->mMeshes[i];

			//unsigned int channels = aMesh->GetNumColorChannels();
			Math::Vertex vertex;

			std::vector<Math::Vertex> vertices;
			std::vector<unsigned int> indices;
			std::vector<Texture> textures;

			// Grab the vertex position and colors for the mesh.
			for (unsigned int j = 0; j < aMesh->mNumVertices; j++)
			{
				if (aMesh->HasPositions())
				{
					aiVector3D aPosition = aMesh->mVertices[j];
					Math::Vector3 position(aPosition.x, aPosition.y, aPosition.z);
					vertex.position = position;
				}

				if(aMesh->HasNormals())
				{
					aiVector3D aNormal = aMesh->mNormals[j];
					Math::Vector3 normal(aNormal.x, aNormal.y, aNormal.z);
					vertex.normal = normal;
				}

				if(aMesh->HasTangentsAndBitangents())
				{
					
				}

				if (aMesh->HasTextureCoords(0))
				{
					aiVector3D aTexCoord = aMesh->mTextureCoords[0][j];
					Math::Vector2 texCoord(aTexCoord.y, aTexCoord.x);
					vertex.texCoord = texCoord;
				}


				vertices.push_back(vertex);
			}

			// Grab the indices for the mesh.
			for (unsigned int j = 0; j < aMesh->mNumFaces; j++)
			{
				aiFace face = aMesh->mFaces[j];

				if (face.mNumIndices == 3)
					for (unsigned int k = 0; k < face.mNumIndices; k++)
						indices.push_back(face.mIndices[k]);
				else
					std::cout << "ERROR: Faces are not triangulated..." << std::endl;
			}

			// Check to see if mesh has a texture.
			if(aMesh->mMaterialIndex >= 0)
			{
				const aiMaterial* aMaterial = scene->mMaterials[aMesh->mMaterialIndex];

				// Iterate though each texture type if they exist.

				for (unsigned int j = 0; j < aMaterial->GetTextureCount(aiTextureType_DIFFUSE); j++)
				{
					// Get the texture for the material.
					aiString string;
					aMaterial->GetTexture(aiTextureType_DIFFUSE, j, &string);
					std::cout << "Diffuse texture " << string.C_Str() << " was found for mesh..." << std::endl;
					textures.push_back(Texture(device, string.C_Str(), Diffuse));
				}

				for (unsigned int j = 0; j < aMaterial->GetTextureCount(aiTextureType_SPECULAR); j++)
				{
					// Get the texture for the material.
					aiString string;
					aMaterial->GetTexture(aiTextureType_SPECULAR, j, &string);
					std::cout << "Specular texture " << string.C_Str() << " was found for mesh..." << std::endl;
					textures.push_back(Texture(device, string.C_Str(), Specular));
				}

				for (unsigned int j = 0; j < aMaterial->GetTextureCount(aiTextureType_HEIGHT); j++)
				{
					// Get the texture for the material.
					aiString string;
					aMaterial->GetTexture(aiTextureType_HEIGHT, j, &string);
					std::cout << "Height texture " << string.C_Str() << " was found for mesh..." << std::endl;
					textures.push_back(Texture(device, string.C_Str(), Height));
				}

				for (unsigned int j = 0; j < aMaterial->GetTextureCount(aiTextureType_OPACITY); j++)
				{
					// Get the texture for the material.
					aiString string;
					aMaterial->GetTexture(aiTextureType_OPACITY, j, &string);
					std::cout << "Opacity texture " << string.C_Str() << " was found for mesh..." << std::endl;
					textures.push_back(Texture(device, string.C_Str(), Opacity));
				}

				for (unsigned int j = 0; j < aMaterial->GetTextureCount(aiTextureType_NORMALS); j++)
				{
					// Get the texture for the material.
					aiString string;
					aMaterial->GetTexture(aiTextureType_NORMALS, j, &string);
					std::cout << "Normal texture " << string.C_Str() << " was found for mesh..." << std::endl;
					textures.push_back(Texture(device, string.C_Str(), Normal));
				}

				for (unsigned int j = 0; j < aMaterial->GetTextureCount(aiTextureType_AMBIENT); j++)
				{
					// Get the texture for the material.
					aiString string;
					aMaterial->GetTexture(aiTextureType_AMBIENT, j, &string);
					std::cout << "Ambient texture " << string.C_Str() << " was found for mesh..." << std::endl;
					textures.push_back(Texture(device, string.C_Str(), Ambient));
				}
			}

			meshes.push_back(Mesh(device, vertices, indices, textures));
		}
	}
}

void Jade::Graphics::Model::Draw()
{
	// Loop through and draw each meshes.
	for(unsigned int i = 0; i < meshes.size(); i++)
		meshes[i].Draw();
}