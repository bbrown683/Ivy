#include "Camera.h"

Jade::Math::Vector3 Jade::Graphics::Camera::GetCameraPosition() const
{
	return position;
}

void Jade::Graphics::Camera::SetCameraPosition(Math::Vector3 position)
{
	this->position = position;
	std::cout << "Camera Position: " << position.ToString() << std::endl;
	// Update constant buffer.
	cBuffer.SetViewMatrix(Math::Matrix::CreateLookAtLH(this->position, target, Math::Vector3::Up).Transpose());
	cBuffer.UpdateMatrices();
}

Jade::Math::Vector3 Jade::Graphics::Camera::GetTargetPosition() const
{
	return target;
}

void Jade::Graphics::Camera::SetTargetPosition(Math::Vector3 position)
{
	this->target = position;

	// Update constant buffer.
	cBuffer.SetViewMatrix(Math::Matrix::CreateLookAtLH(this->position, target, Math::Vector3::Up).Transpose());
	cBuffer.UpdateMatrices();
}
