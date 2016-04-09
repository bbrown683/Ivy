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

bool Jade::Graphics::ConstantBuffer::Bind()
{
	return constantBuffer->Bind();
}

bool Jade::Graphics::ConstantBuffer::Unbind()
{
	return constantBuffer->Unbind();
}
