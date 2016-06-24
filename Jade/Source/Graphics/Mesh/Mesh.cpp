#include "Mesh.h"

void Jade::Graphics::Mesh::Draw()
{	
    // Enable shaders.
	shader.MakeActive();
	
	// Set the world matrix for the object.
	cBuffer.SetWorldMatrix(translation * rotation * scale);

	// Bind the vertex and index buffers.
	vBuffer.Bind();
	iBuffer.Bind();

	// Assign the matrix data to the buffer.
	cBuffer.UpdateMatrices();

	// Set the textures.
	for (unsigned int i = 0; i < textures.size(); i++)
			textures[i].MakeActive();

	// Draw either based on vertices or indices.
	if (device.GetDrawType() == DrawType::Default)
		vBuffer.Draw();
	else
		iBuffer.Draw();

	// After we are done drawing, reset the buffers for the next bind.
	iBuffer.Unbind();
	vBuffer.Unbind();

    // Disable shaders.
	shader.MakeInactive();
}

std::vector<Jade::Math::Vertex> Jade::Graphics::Mesh::GetVertices() const
{
	return vertices;
}

std::vector<unsigned short> Jade::Graphics::Mesh::GetIndices() const
{
	return indices;
}

std::vector<Jade::Graphics::Texture> Jade::Graphics::Mesh::GetTextures() const
{
	return textures;
}

void Jade::Graphics::Mesh::SetPosition(Math::Vector3 position)
{
	translation = translation.Translate(position.GetX(), position.GetY(), position.GetZ()).Transpose();
}

void Jade::Graphics::Mesh::SetScale(Math::Vector3 scale)
{
	this->scale = this->scale.Scale(scale).Transpose();
}

void Jade::Graphics::Mesh::SetRotation(Math::Vector3 rotation)
{
	this->rotation = (this->rotation.RotateAlongX(rotation.GetX()) * 
		this->rotation.RotateAlongY(rotation.GetY()) * 
		this->rotation.RotateAlongZ(rotation.GetZ())).Transpose();
}
