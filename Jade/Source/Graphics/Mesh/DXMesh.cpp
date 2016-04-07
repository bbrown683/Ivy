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

#include "Graphics/Mesh/DXMesh.h"

void Jade::Graphics::DXMesh::Bind()
{
	HRESULT hr;
	
	// Create the vertex buffer;
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
	hr = device->GetID3D11Device()->CreateBuffer(&desc, &InitData, m_pVertexBuffer.GetAddressOf());
	
	// Ensure it was created successfully.
	if(FAILED(hr))
	{
		bufferSuccess = false;

		std::cout << "ERROR: Vertex buffer creation failed..." << std::endl;
	}
	else
	{
		std::cout << "Vertex buffer was created successfully..." << std::endl;

		unsigned int stride = sizeof(Math::Vertex);
		unsigned int offset = 0;

		// Set the vertices buffer.
		device->GetID3D11DeviceContext()->IASetVertexBuffers(0, 1, m_pVertexBuffer.GetAddressOf(), &stride, &offset);

		// Set the primitive topology.
		device->GetID3D11DeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		// Set up the index buffer now.
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = static_cast<unsigned int>(sizeof(unsigned int) * indices.size());
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		desc.CPUAccessFlags = 0;
		InitData.pSysMem = indices.data();

		// Create index buffer.
		hr = device->GetID3D11Device()->CreateBuffer(&desc, &InitData, m_pIndexBuffer.GetAddressOf());

		// Ensure it was created successfully.
		if (FAILED(hr))
		{
			bufferSuccess = false;

			std::cout << "ERROR: Index buffer creation failed..." << std::endl;
		}
		else
		{
			std::cout << "Index buffer was created successfully..." << std::endl;

			// Assign index buffer.
			device->GetID3D11DeviceContext()->IASetIndexBuffer(m_pIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);

			// Create the constant buffer
			desc.Usage = D3D11_USAGE_DEFAULT;
			desc.ByteWidth = sizeof(Matrices);
			desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			desc.CPUAccessFlags = 0;
			
			hr = device->GetID3D11Device()->CreateBuffer(&desc, nullptr, m_pConstantBuffer.GetAddressOf());

			if (FAILED(hr))
			{
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

				space.view = XMMatrixTranspose(view);

				// Set our projection matrix.
				projection = DirectX::XMMatrixPerspectiveFovLH(DirectX::XM_PIDIV2, device->GetIWindow()->GetAspectRatio(), 0.01f, 1000.0f);

				space.projection = XMMatrixTranspose(projection);

				// After buffer is created we can bind the textures.
				for (int i = 0; i < textures.size(); i++)
				{
					if(textures[i].CreateTextureFromFile())				  
						std::cout << "Texture " << textures[i].GetFilename() << " was bound successfully..." << std::endl;
					else
						std::cout << "Texture " << textures[i].GetFilename() << " failed to bind to mesh..." << std::endl;
				}

				bufferSuccess = true;
			}
		}
	}
}

void Jade::Graphics::DXMesh::Unbind()
{
	// Unbind buffers.
	device->GetID3D11DeviceContext()->IASetVertexBuffers(0, 0, nullptr, nullptr, nullptr);
	device->GetID3D11DeviceContext()->IASetIndexBuffer(nullptr, DXGI_FORMAT_R32_UINT, 0);

	std::cout << "Releasing mesh and cleaning up..." << std::endl;
}

void Jade::Graphics::DXMesh::Draw()
{
	// Ensure that everything was binded correctly before attempting to draw.
	if (bufferSuccess)
	{
		// Rotate our cube slightly.
		world = DirectX::XMMatrixRotationY(device->GetIWindow()->GetTimer().GetElaspedTime());// *DirectX::XMMatrixRotationX(device->GetIWindow()->GetTimer().GetElaspedTime());

		space.world = XMMatrixTranspose(world);

		device->GetID3D11DeviceContext()->UpdateSubresource(m_pConstantBuffer.Get(), 0, nullptr, &space, 0, 0);
		device->GetID3D11DeviceContext()->VSSetConstantBuffers(0, 1, m_pConstantBuffer.GetAddressOf());
		device->GetID3D11DeviceContext()->DrawIndexed(static_cast<unsigned int>(indices.size()), 0, 0);
	}
}
