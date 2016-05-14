#include "TestMesh.h"

void Jade::Graphics::TestMesh::Draw()
{	
	// Mock rotation.
	rotation += 0.015f;

	Math::Vector3 eye = Math::Vector3(0.0f, 1.0f, -5.0f);
	Math::Vector3 at = Math::Vector3(0.0, 1.0f, 0.0);
	Math::Vector3 up = Math::Vector3::Up;

	cBuffer.SetViewMatrix(Math::Matrix::CreateLookAtLH(eye, at, up).Transpose());

	cBuffer.SetProjectionMatrix(Math::Matrix::CreatePerspectiveViewLH(
		Math::Math::PiOverTwo, static_cast<float>(1080),
		static_cast<float>(720), 0.01f, 1000.0f).Transpose());

	shader.MakeActive();

	// Test the rotation.
	Math::Matrix rotated;
	rotated = rotated.RotateAlongY(rotation) * rotated.RotateAlongX(rotation);
	cBuffer.SetWorldMatrix(rotated);

	// Bind the vertex and index buffers.
	vBuffer.Bind();
	iBuffer.Bind();
	cBuffer.Bind();

	// Assign the matrix data to the buffer.
	cBuffer.Update();

	// Update the textures.
	for (unsigned int i = 0; i < textures.size(); i++)
		textures[i].Update();
	
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
	
}
