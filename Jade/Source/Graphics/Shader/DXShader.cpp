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

#include "Graphics/Shader/DXShader.h"

#ifdef JADE_PLATFORM_WINDOWS
bool Jade::Graphics::DXShader::Create(std::string filename, ShaderType type)
{
	HRESULT hr;

	switch (type)
	{
		case ShaderType::Pixel:
		{
			hr = device->GetID3D11Device()->CreatePixelShader(m_pPixelShaderBlob->GetBufferPointer(), m_pPixelShaderBlob->GetBufferSize(), nullptr, m_pPixelShader.GetAddressOf());

			if (FAILED(hr))
			{
				// Output compilation errors to console.
				std::cout << "ERROR: Pixel shader creation failed..." << std::endl;
				return false;
			}

			device->GetID3D11DeviceContext()->PSSetShader(m_pPixelShader.Get(), nullptr, 0);

			std::cout << "Pixel shader was created successfully..." << std::endl;
			break;
		}
		case ShaderType::Vertex:
		{
			hr = device->GetID3D11Device()->CreateVertexShader(m_pVertexShaderBlob->GetBufferPointer(), m_pVertexShaderBlob->GetBufferSize(), nullptr, m_pVertexShader.GetAddressOf());

			if (FAILED(hr))
			{
				// Output compilation errors to console.
				std::cout << "ERROR: Vertex shader creation failed..." << std::endl;
				return false;
			}

			// Define the input layout
			D3D11_INPUT_ELEMENT_DESC inputLayout[] =
			{
				{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT	,	0,	0,	D3D11_INPUT_PER_VERTEX_DATA,	0 },
				{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT		,	0, 12,	D3D11_INPUT_PER_VERTEX_DATA,	0 },
				{ "NORMAL"  ,	0, DXGI_FORMAT_R32G32B32_FLOAT	,	0, 12,  D3D11_INPUT_PER_VERTEX_DATA,	0 },	
			};

			// Create the input layout.
			hr = device->GetID3D11Device()->CreateInputLayout(inputLayout, ARRAYSIZE(inputLayout), m_pVertexShaderBlob->GetBufferPointer(), m_pVertexShaderBlob->GetBufferSize(), m_pInputLayout.GetAddressOf());

			if (FAILED(hr))
			{
				// Output compilation errors to console.
				std::cout << "ERROR: Vertex shader creation failed..." << std::endl;
				return false;
			}

			// Set the input layout
			device->GetID3D11DeviceContext()->IASetInputLayout(m_pInputLayout.Get());
			device->GetID3D11DeviceContext()->VSSetShader(m_pVertexShader.Get(), nullptr, 0);

			std::cout << "Vertex shader was created successfully..." << std::endl;
			break;
		}
	}

	return true;
}

bool Jade::Graphics::DXShader::Compile(std::string filename, ShaderType type)
{
	return false;
}

bool Jade::Graphics::DXShader::Release()
{
	std::cout << "Shaders cleaning up..." << std::endl;

	return true;
}

bool Jade::Graphics::DXShader::CopyToBlob(ShaderType type, ComPtr<ID3DBlob> blob)
{
	HRESULT hr;

	switch(type)
	{
	case ShaderType::Pixel:
		hr = blob.CopyTo(m_pPixelShaderBlob.GetAddressOf());
		break;
	case ShaderType::Vertex:
		hr = blob.CopyTo(m_pVertexShaderBlob.GetAddressOf());
		break;
	default:
		hr = -1;
		break;
	}

	return FAILED(hr) ? false : true;
}
#endif