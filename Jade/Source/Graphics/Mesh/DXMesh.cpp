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

#include <iostream>

#include "Graphics/Mesh/DXMesh.h"

void Jade::Graphics::DXMesh::Bind()
{
	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = static_cast<unsigned int>(sizeof(Math::Vertex) * vertices.size());
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	desc.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));

	// Pass the data to the Direct3D11 object.
	InitData.pSysMem = vertices.data();

	// Creaate vertices buffer.
	long hr = device->m_pDevice->CreateBuffer(&desc, &InitData, &device->m_pVertexBuffer);
	
	// Ensure it was created successfully.
	if(hr < 0)
	{
		device->m_pVertexBuffer->Release();

		std::cout << "Vertex buffer creation failed." << std::endl;
	}
	else
	{
		std::cout << "Vertex buffer was created successfully." << std::endl;

		unsigned int stride = sizeof(Math::Vertex);
		unsigned int offset = 0;

		// Set the vertices buffer.
		device->m_pImmediateContext->IASetVertexBuffers(0, 1, &device->m_pVertexBuffer, &stride, &offset);

		// Set up the index buffer now.
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = static_cast<unsigned int>(sizeof(unsigned int) * indices.size());
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		desc.CPUAccessFlags = 0;
		InitData.pSysMem = indices.data();

		// Create index buffer.
		hr = device->m_pDevice->CreateBuffer(&desc, &InitData, &device->m_pIndexBuffer);

		// Ensure it was created successfully.
		if (hr < 0)
		{
			device->m_pIndexBuffer->Release();

			std::cout << "Index buffer creation failed." << std::endl;
		}
		else
		{
			std::cout << "Index buffer was created successfully." << std::endl;

			// Assign index buffer.
			device->m_pImmediateContext->IASetIndexBuffer(device->m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

			// Set the primitive topology.
			device->m_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		}
	}
}

void Jade::Graphics::DXMesh::Unbind()
{
	// Unbind vertices buffer.
	device->m_pImmediateContext->IASetVertexBuffers(0, 0, nullptr, nullptr, nullptr);
}

void Jade::Graphics::DXMesh::Draw()
{
	device->m_pImmediateContext->DrawIndexed(static_cast<unsigned int>(indices.size()), 0, 0);
}
