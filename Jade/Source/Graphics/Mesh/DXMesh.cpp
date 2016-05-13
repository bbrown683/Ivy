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

#ifdef JADE_PLATFORM_WINDOWS
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
		desc.ByteWidth = static_cast<unsigned int>(sizeof(unsigned short) * indices.size());
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
			device->GetID3D11DeviceContext()->IASetIndexBuffer(m_pIndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);

			// Create the constant buffer
			desc.Usage = D3D11_USAGE_DEFAULT;
			desc.ByteWidth = sizeof(Math::Space);
			//desc.ByteWidth = sizeof(Matrices);
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

				space.world = Math::Matrix::Identity;

				Math::Vector3 eye = Math::Vector3(0.0f, 1.0f, -5.0f);
				Math::Vector3 at = Math::Vector3(0.0, 1.0f, 0.0);
				Math::Vector3 up = Math::Vector3::Up;

				space.view = Math::Matrix::CreateLookAtLH(eye, at, up).Transpose();

				// Set our projection matrix.
				space.projection = Math::Matrix::CreatePerspectiveViewLH(
					Math::Math::PiOverTwo, static_cast<float>(device->GetIWindow()->GetWidth()),
					static_cast<float>(device->GetIWindow()->GetHeight()), 0.01f, 1000.0f).Transpose();


				// After buffer is created we can bind the textures.
				for (unsigned int i = 0; i < textures.size(); i++)
				{
					if (textures[i].CreateTextureFromFile())
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
	device->GetID3D11DeviceContext()->IASetIndexBuffer(nullptr, DXGI_FORMAT_R16_UINT, 0);

	std::cout << "Releasing mesh and cleaning up..." << std::endl;
}

void Jade::Graphics::DXMesh::Draw()
{
	// Ensure that everything was binded correctly before attempting to draw.
	if (bufferSuccess)
	{
		// Set the shaders for this mesh.
		if(shader->GetID3D11PixelShader().Get())
			device->GetID3D11DeviceContext()->PSSetShader(shader->GetID3D11PixelShader().Get(), nullptr, 0);
		if (shader->GetID3D11VertexShader().Get())
			device->GetID3D11DeviceContext()->VSSetShader(shader->GetID3D11VertexShader().Get(), nullptr, 0);

		// Rotate our cube slightly.
		space.world = Math::Matrix::RotateAlongY(device->GetIWindow()->GetTimer().GetElaspedTime()).Transpose();

		device->GetID3D11DeviceContext()->UpdateSubresource(m_pConstantBuffer.Get(), 0, nullptr, &space, 0, 0);
		device->GetID3D11DeviceContext()->VSSetConstantBuffers(0, 1, m_pConstantBuffer.GetAddressOf());

		// Update textures for each mesh.
		for (unsigned int i = 0; i < textures.size(); i++)
			textures[i].Update();

		device->GetID3D11DeviceContext()->DrawIndexed(static_cast<unsigned int>(indices.size()), 0, 0);
	}
}
#endif
