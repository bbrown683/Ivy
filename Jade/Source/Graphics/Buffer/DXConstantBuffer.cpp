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
bool Jade::Graphics::DXConstantBuffer::CreateProjectionMatrix()
{
	// Create the constant buffer
	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.CPUAccessFlags = 0;
	desc.ByteWidth = sizeof(Math::OnResize);

	HRESULT hr = device->GetID3D11Device()->CreateBuffer(&desc, nullptr, m_pOnResize.GetAddressOf());

	if (FAILED(hr))
		return false;

	return true;
}

bool Jade::Graphics::DXConstantBuffer::CreateViewMatrix()
{
	// Create the constant buffer
	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.ByteWidth = sizeof(Math::NeverChanges);
	
	HRESULT hr = device->GetID3D11Device()->CreateBuffer(&desc, nullptr, m_pNeverChanges.GetAddressOf());

	if (FAILED(hr))
		return false;

	return true;
}

bool Jade::Graphics::DXConstantBuffer::CreateWorldMatrix()
{
	// Create the constant buffer
	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.CPUAccessFlags = 0;
	desc.ByteWidth = sizeof(Math::PerObject);

	HRESULT hr = device->GetID3D11Device()->CreateBuffer(&desc, nullptr, m_pPerObject.GetAddressOf());

	if (FAILED(hr))
		return false;

	return true;
}

Jade::Math::Matrix Jade::Graphics::DXConstantBuffer::GetProjectionMatrix()
{
	return onResize.projection;
}

Jade::Math::Matrix Jade::Graphics::DXConstantBuffer::GetViewMatrix()
{
	return neverChanges.view;
}

Jade::Math::Matrix Jade::Graphics::DXConstantBuffer::GetWorldMatrix()
{
	return perObject.world;
}

void Jade::Graphics::DXConstantBuffer::SetProjectionMatrix(Math::Matrix matrix)
{
	onResize.projection = matrix;
}

void Jade::Graphics::DXConstantBuffer::SetViewMatrix(Math::Matrix matrix)
{
	neverChanges.view = matrix;
}

void Jade::Graphics::DXConstantBuffer::SetWorldMatrix(Math::Matrix matrix)
{
	perObject.world = matrix;
}

void Jade::Graphics::DXConstantBuffer::Update()
{
	if (m_pPerObject.Get() != nullptr)
	{
		device->GetID3D11DeviceContext()->UpdateSubresource(m_pPerObject.Get(), 0, nullptr, &perObject, 0, 0);
		device->GetID3D11DeviceContext()->VSSetConstantBuffers(0, 1, m_pPerObject.GetAddressOf()); // register b0.
	}
	if(m_pOnResize.Get() != nullptr)
	{
		device->GetID3D11DeviceContext()->UpdateSubresource(m_pOnResize.Get(), 0, nullptr, &onResize, 0, 0);
		device->GetID3D11DeviceContext()->VSSetConstantBuffers(1, 1, m_pOnResize.GetAddressOf()); // register b1.
	}
	if(m_pNeverChanges.Get() != nullptr)
	{
		device->GetID3D11DeviceContext()->UpdateSubresource(m_pNeverChanges.Get(), 0, nullptr, &neverChanges, 0, 0);
		device->GetID3D11DeviceContext()->VSSetConstantBuffers(2, 1, m_pNeverChanges.GetAddressOf()); // register b2.	
	}
}
#endif