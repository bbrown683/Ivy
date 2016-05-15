#include "ConstantBuffer.h"

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

bool Jade::Graphics::ConstantBuffer::Create(bool model, bool view, bool projection)
{
	return constantBuffer->Create(model, view, projection);
}

void Jade::Graphics::ConstantBuffer::Bind()
{
	constantBuffer->Bind();
}

void Jade::Graphics::ConstantBuffer::Unbind()
{
	constantBuffer->Unbind();
}
