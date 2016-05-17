#include "ConstantBuffer.h"

bool Jade::Graphics::ConstantBuffer::CreateProjectionMatrix()
{
	return constantBuffer->CreateProjectionMatrix();
}

bool Jade::Graphics::ConstantBuffer::CreateViewMatrix()
{
	return constantBuffer->CreateViewMatrix();
}

bool Jade::Graphics::ConstantBuffer::CreateWorldMatrix()
{
	return constantBuffer->CreateWorldMatrix();
}

Jade::Math::Matrix Jade::Graphics::ConstantBuffer::GetProjectionMatrix()
{
	return constantBuffer->GetProjectionMatrix();
}

Jade::Math::Matrix Jade::Graphics::ConstantBuffer::GetViewMatrix()
{
	return constantBuffer->GetViewMatrix();
}

Jade::Math::Matrix Jade::Graphics::ConstantBuffer::GetWorldMatrix()
{
	return constantBuffer->GetWorldMatrix();
}

void Jade::Graphics::ConstantBuffer::SetProjectionMatrix(Math::Matrix matrix)
{
	constantBuffer->SetProjectionMatrix(matrix);
}

void Jade::Graphics::ConstantBuffer::SetViewMatrix(Math::Matrix matrix)
{
	constantBuffer->SetViewMatrix(matrix);
}

void Jade::Graphics::ConstantBuffer::SetWorldMatrix(Math::Matrix matrix)
{
	constantBuffer->SetWorldMatrix(matrix);
}

void Jade::Graphics::ConstantBuffer::Update()
{
	constantBuffer->Update();
}