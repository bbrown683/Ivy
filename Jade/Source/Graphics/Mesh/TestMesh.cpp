#include "TestMesh.h"

void Jade::Graphics::TestMesh::Initialize()
{
	vBuffer = VertexBuffer(device);
	iBuffer = IndexBuffer(device);
	cBuffer = ConstantBuffer(device);

	vBuffer.SetVertices(vertices);
	iBuffer.SetIndices(indices);

	for (int i = 0; i < textures.size(); i++)
	{

	}
}
