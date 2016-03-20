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
		if(device->m_pVertexBuffer)
			device->m_pVertexBuffer->Release();

		bufferSuccess = false;

		std::cout << "ERROR: Vertex buffer creation failed..." << std::endl;
	}
	else
	{
		std::cout << "Vertex buffer was created successfully..." << std::endl;

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
			if(device->m_pIndexBuffer)
				device->m_pIndexBuffer->Release();

			bufferSuccess = false;

			std::cout << "ERROR: Index buffer creation failed..." << std::endl;
		}
		else
		{
			std::cout << "Index buffer was created successfully..." << std::endl;

			// Assign index buffer.
			device->m_pImmediateContext->IASetIndexBuffer(device->m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

			// Set the primitive topology.
			device->m_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

			// Create the constant buffer
			desc.Usage = D3D11_USAGE_DEFAULT;
			desc.ByteWidth = sizeof(ConstantBuffer);
			desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			desc.CPUAccessFlags = 0;
			
			hr = device->m_pDevice->CreateBuffer(&desc, nullptr, &device->m_pConstantBuffer);
			
			if (hr < 0)
			{
				if(device->m_pConstantBuffer)
					device->m_pConstantBuffer->Release();

				bufferSuccess = false;

				std::cout << "ERROR: Constant buffer creation failed." << std::endl;
			}
			else
			{
				std::cout << "Constant buffer was created successfully..." << std::endl;

				space.world = DirectX::XMMatrixIdentity();

				// Initialize the view matrix
				DirectX::XMVECTOR Eye = DirectX::XMVectorSet(0.0f, 1.0f, -5.0f, 0.0f);
				DirectX::XMVECTOR At = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
				DirectX::XMVECTOR Up = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
				view = DirectX::XMMatrixLookAtLH(Eye, At, Up);
				
				// Set our projection matrix.
				projection = DirectX::XMMatrixPerspectiveFovLH(DirectX::XM_PIDIV2, static_cast<float>(device->window->GetWidth()) / static_cast<float>(device->window->GetHeight()), 0.01f, 100.0f);

				bufferSuccess = true;
			}
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
	// Ensure that everything was binded correctly before attempting to draw.
	if (bufferSuccess)
	{
		// Update our time
		static float t = 0.0f;
		if (device->m_DriverType == D3D_DRIVER_TYPE_REFERENCE)
		{
			t += (float)DirectX::XM_PI * 0.0125f;
		}
		else
		{
			static ULONGLONG timeStart = 0;
			ULONGLONG timeCur = GetTickCount64();
			if (timeStart == 0)
				timeStart = timeCur;
			t = (timeCur - timeStart) / 1000.0f;
		}

		// Rotate our cube slightly.
		world = DirectX::XMMatrixRotationX(-t) * DirectX::XMMatrixRotationY(t);

		space.world = DirectX::XMMatrixTranspose(world);
		space.view = DirectX::XMMatrixTranspose(view);
		space.projection = DirectX::XMMatrixTranspose(projection);

		device->m_pImmediateContext->UpdateSubresource(device->m_pConstantBuffer, 0, nullptr, &space, 0, 0);
		device->m_pImmediateContext->VSSetConstantBuffers(0, 1, &device->m_pConstantBuffer);

		device->m_pImmediateContext->DrawIndexed(static_cast<unsigned int>(indices.size()), 0, 0);
	}
}
