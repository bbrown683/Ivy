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

Jade::Math::Vertex* Jade::Graphics::Model::LoadModel(std::string filename)
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
	// Loop through and draw each meshes.
	for(unsigned int i = 0; i < meshes.size(); i++)
	{
		meshes[i].Draw();
	}
}