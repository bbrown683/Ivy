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

#include <iostream>

#include "Model.h"

std::vector<Jade::Graphics::Mesh> Jade::Graphics::Model::GetMeshes() const
{
	return meshes;
}

void Jade::Graphics::Model::Load(std::string filename)
{
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(filename, aiProcess_Triangulate | 
		aiProcess_JoinIdenticalVertices | 
		aiProcess_OptimizeMeshes | 
		aiProcess_SplitLargeMeshes);

	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "Assimp: Error - " << importer.GetErrorString() << std::endl;
		
		std::cout << "errr" << std::endl;

		return;
	}
	
	if (scene->HasMeshes())
	{
		// Iterates through each mesh and assigns them their respective vertices and indices.
		for (unsigned int i = 0; i < scene->mNumMeshes; i++)
		{
			std::cout << "Mesh # : " << i << std::endl;

			// Set current mesh for assimp importer.
			const aiMesh* aMesh = scene->mMeshes[i];

			unsigned int channels = aMesh->GetNumColorChannels();

			std::vector<Math::Vertex> vertices;
			std::vector<unsigned int> indices;

			// Grab the vertex position and colors for the mesh.
			for (unsigned int j = 0; j < aMesh->mNumVertices; j++)
			{
				const aiVector3D* aPosition = &aMesh->mVertices[j];
				//const aiColor4D* aColor = &aMesh->mColors[0][i];

				Math::Vector3 position(aPosition->x, aPosition->y, aPosition->z);
				Math::Color color(1.0f, 1.0f, 1.0f, 1.0f);

				//if (aMesh->HasVertexColors(0))
					//color = Math::Color(aColor.r, aColor.g, aColor.b, aColor.a);
				//else
					//color = Math::Color::White;

				Math::Vertex vertex;
				vertex.position = position;
				vertex.color = color;

				vertices.push_back(vertex);
			}

			// Grab the indices for the mesh.
			for (unsigned int j = 0; j < aMesh->mNumFaces; j++)
			{
				const struct aiFace* face = &aMesh->mFaces[j];

				if (face->mNumIndices == 3)
					for (unsigned int k = 0; k < face->mNumIndices; k++)
						indices.push_back(face->mIndices[k]);
				else
					std::cout << "ERROR: Faces are not triangulated..." << std::endl;
			}

			meshes.push_back(Mesh(device, vertices, indices));
		}
	}

	if(scene->HasTextures())
	{
		for (unsigned int i = 0; i < scene->mNumTextures; i++)
		{
			aiTexture* aTexture = scene->mTextures[i];

			if(aTexture->CheckFormat(aTexture->achFormatHint))
			{
				
			}
		}
	}
}

void Jade::Graphics::Model::Draw()
{
	// Loop through and draw each meshes.
	for(unsigned int i = 0; i < meshes.size(); i++)
		meshes[i].Draw();
}