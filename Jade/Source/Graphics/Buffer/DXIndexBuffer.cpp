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

#ifdef _WIN32

#include "DXIndexBuffer.h"

std::vector<unsigned short> Jade::Graphics::DXIndexBuffer::GetIndices()
{
	return indices;
}

void Jade::Graphics::DXIndexBuffer::SetIndices(std::vector<unsigned short> indices)
{
	this->indices = indices;
}

void Jade::Graphics::DXIndexBuffer::Update()
{

}

bool Jade::Graphics::DXIndexBuffer::Bind()
{	
	if (m_pIndexBuffer)
		m_pIndexBuffer.Reset();

	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = static_cast<unsigned int>(sizeof(unsigned short) * indices.size());
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	desc.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	
	InitData.pSysMem = indices.data();

	// Create index buffer.
	HRESULT hr = device->GetID3D11Device()->CreateBuffer(&desc, &InitData, m_pIndexBuffer.GetAddressOf());

	if (FAILED(hr))
		return false;

	// Assign index buffer.
	device->GetID3D11DeviceContext()->IASetIndexBuffer(m_pIndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);

	return true;
}

bool Jade::Graphics::DXIndexBuffer::Unbind()
{
	device->GetID3D11DeviceContext()->IASetIndexBuffer(nullptr, DXGI_FORMAT_R16_UINT, 0);

	return true;
}

#endif // _WIN32