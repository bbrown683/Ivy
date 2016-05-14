/*
The MIT License (MIT)

Copyright (c) 2015 Ben Brown

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/


#include "DXConstantBuffer.h"

#ifdef JADE_PLATFORM_WINDOWS
void Jade::Graphics::DXConstantBuffer::Bind()
{

}

bool Jade::Graphics::DXConstantBuffer::Create()
{
	if (m_pConstantBuffer)
		m_pConstantBuffer.Reset();

	// Create the constant buffer
	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = sizeof(Math::Space);
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.CPUAccessFlags = 0;

	HRESULT hr = device->GetID3D11Device()->CreateBuffer(&desc, nullptr, m_pConstantBuffer.GetAddressOf());

	if (FAILED(hr))
		return false;

	return true;
}

Jade::Math::Matrix Jade::Graphics::DXConstantBuffer::GetProjectionMatrix()
{
	return space.projection;
}

Jade::Math::Matrix Jade::Graphics::DXConstantBuffer::GetViewMatrix()
{
	return space.view;
}

Jade::Math::Matrix Jade::Graphics::DXConstantBuffer::GetWorldMatrix()
{
	return space.world;
}

void Jade::Graphics::DXConstantBuffer::SetProjectionMatrix(Math::Matrix matrix)
{
	space.projection = matrix;
}

void Jade::Graphics::DXConstantBuffer::SetViewMatrix(Math::Matrix matrix)
{
	space.view = matrix;
}

void Jade::Graphics::DXConstantBuffer::SetWorldMatrix(Math::Matrix matrix)
{
	space.world = matrix;
}

void Jade::Graphics::DXConstantBuffer::Unbind()
{

}

void Jade::Graphics::DXConstantBuffer::Update()
{
	device->GetID3D11DeviceContext()->UpdateSubresource(m_pConstantBuffer.Get(), 0, nullptr, &space, 0, 0);
	device->GetID3D11DeviceContext()->VSSetConstantBuffers(0, 1, m_pConstantBuffer.GetAddressOf());
}


#endif // _WIN32