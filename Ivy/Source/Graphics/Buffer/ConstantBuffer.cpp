#include "ConstantBuffer.h"

bool Ivy::Graphics::ConstantBuffer::CreateProjectionMatrix()
{
	return constantBuffer->CreateProjectionMatrix();
}

bool Ivy::Graphics::ConstantBuffer::CreateViewMatrix()
{
	return constantBuffer->CreateViewMatrix();
}

bool Ivy::Graphics::ConstantBuffer::CreateWorldMatrix()
{
	return constantBuffer->CreateWorldMatrix();
}

Ivy::Math::Matrix Ivy::Graphics::ConstantBuffer::GetProjectionMatrix()
{
	return constantBuffer->GetProjectionMatrix();
}

Ivy::Math::Matrix Ivy::Graphics::ConstantBuffer::GetViewMatrix()
{
	return constantBuffer->GetViewMatrix();
}

Ivy::Math::Matrix Ivy::Graphics::ConstantBuffer::GetWorldMatrix()
{
	return constantBuffer->GetWorldMatrix();
}

void Ivy::Graphics::ConstantBuffer::SetProjectionMatrix(Math::Matrix matrix)
{
	constantBuffer->SetProjectionMatrix(matrix);
}

void Ivy::Graphics::ConstantBuffer::SetViewMatrix(Math::Matrix matrix)
{
	constantBuffer->SetViewMatrix(matrix);
}

void Ivy::Graphics::ConstantBuffer::SetWorldMatrix(Math::Matrix matrix)
{
	constantBuffer->SetWorldMatrix(matrix);
}

void Ivy::Graphics::ConstantBuffer::UpdateMatrices()
{
	constantBuffer->UpdateMatrices();
}