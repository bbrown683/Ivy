#include "TestMesh.h"

void Jade::Graphics::TestMesh::Draw()
{	
	shader.MakeActive();
	
	// Set the world matrix for the object.
	cBuffer.SetWorldMatrix(translation * rotation * scale);

	// Bind the vertex and index buffers.
	vBuffer.Bind();
	iBuffer.Bind();
	cBuffer.Bind();

	// Assign the matrix data to the buffer.
	cBuffer.Update();

	// Set the textures.
	for (unsigned int i = 0; i < textures.size(); i++)
		textures[i].Set();

	// Draw either based on vertices or indices.
	if (device.GetDrawType() == DrawType::Default)
		vBuffer.Update();
	else
		iBuffer.Update();

	// After we are done drawing, reset the buffers for the next bind.
	cBuffer.Unbind();
	iBuffer.Unbind();
	vBuffer.Unbind();
}

void Jade::Graphics::TestMesh::SetPosition(Math::Vector3 position)
{
	translation = translation.Translate(position.GetX(), position.GetY(), position.GetZ()).Transpose();
}

void Jade::Graphics::TestMesh::SetScale(Math::Vector3 scale)
{
	this->scale = this->scale.Scale(scale).Transpose();
}

void Jade::Graphics::TestMesh::SetRotation(Math::Vector3 rotation)
{
	this->rotation = this->rotation.RotateAlongX(rotation.GetX()) * 
		this->rotation.RotateAlongY(rotation.GetY()) * 
		this->rotation.RotateAlongZ(rotation.GetZ()).Transpose();
}
