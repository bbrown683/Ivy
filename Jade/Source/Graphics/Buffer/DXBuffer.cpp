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

#include "Graphics/Buffer/DXBuffer.h"

void Jade::Graphics::DXBuffer::Bind()
{
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Math::Vertex) * 3;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = vertex;

	HRESULT hr = device->m_pDevice->CreateBuffer(&bd, &InitData, &device->m_pBuffer);
	
	if(FAILED(hr))
	{
		device->m_pBuffer->Release();
	}
}

void Jade::Graphics::DXBuffer::Unbind()
{
	// Unbind vertex buffer.
	device->m_pImmediateContext->IASetVertexBuffers(0, 0, nullptr, nullptr, nullptr);
}

void Jade::Graphics::DXBuffer::Draw()
{
	UINT stride = sizeof(Math::Vertex);
	UINT offset = 0;

	device->m_pImmediateContext->IASetVertexBuffers(0, 1, &device->m_pBuffer, &stride, &offset);

	device->m_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// Drawing using triangular meshes so we will be using 3 vertices.
	device->m_pImmediateContext->Draw(3, 0);
}
