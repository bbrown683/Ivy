#include "ConstantBuffer.h"

bool Jade::Graphics::ConstantBuffer::Bind()
{
	return constantBuffer->Bind();
}

bool Jade::Graphics::ConstantBuffer::Unbind()
{
	return constantBuffer->Unbind();
}
