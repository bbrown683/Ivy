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

#include "Graphics/Shader/TestDXShader.h"

bool Jade::Graphics::TestDXShader::Create(ShaderType type)
{
	long shaderResult = 0;

	switch (type)
	{
		case ShaderType::Compute:
		{
			shaderResult = device->m_pDevice->CreateComputeShader(m_pComputeShaderBlob->GetBufferPointer(), m_pComputeShaderBlob->GetBufferSize(), nullptr, m_pComputeShader.GetAddressOf());

			if (shaderResult < 0)
			{
				// Output compilation errors to console.
				std::cout << "ERROR: Compute shader creation failed..." << std::endl;

				// Release any data associated with the shader if it gives an error.
				Release();

				return false;
			}

			std::cout << "Compute shader was created successfully..." << std::endl;
			break;
		}
		case ShaderType::Domain:
		{
			shaderResult = device->m_pDevice->CreateDomainShader(m_pDomainShaderBlob->GetBufferPointer(), m_pDomainShaderBlob->GetBufferSize(), nullptr, m_pDomainShader.GetAddressOf());

			if (shaderResult < 0)
			{
				// Output compilation errors to console.
				std::cout << "ERROR: Domain shader creation failed..." << std::endl;

				// Release any data associated with the shader if it gives an error.
				Release();

				return false;
			}

			std::cout << "Domain shader was created successfully..." << std::endl;
			break;
		}
		case ShaderType::Geometry:
		{
			shaderResult = device->m_pDevice->CreateGeometryShader(m_pGeometryShaderBlob->GetBufferPointer(), m_pGeometryShaderBlob->GetBufferSize(), nullptr, m_pGeometryShader.GetAddressOf());

			if (shaderResult < 0)
			{
				// Output compilation errors to console.
				std::cout << "ERROR: Geometry shader creation failed..." << std::endl;

				// Release any data associated with the shader if it gives an error.
				Release();

				return false;
			}

			std::cout << "Geometry shader was created successfully..." << std::endl;
			break;
		}
		case ShaderType::Pixel:
		{
			shaderResult = device->m_pDevice->CreatePixelShader(m_pPixelShaderBlob->GetBufferPointer(), m_pPixelShaderBlob->GetBufferSize(), nullptr, m_pPixelShader.GetAddressOf());

			if (shaderResult < 0)
			{
				// Output compilation errors to console.
				std::cout << "ERROR: Pixel shader creation failed..." << std::endl;

				// Release any data associated with the shader if it gives an error.
				Release();

				return false;
			}

			device->m_pImmediateContext->PSSetShader(m_pPixelShader.Get(), nullptr, 0);

			std::cout << "Pixel shader was created successfully..." << std::endl;
			break;
		}
		case ShaderType::Tesselation:
		{
			shaderResult = device->m_pDevice->CreateHullShader(m_pHullShaderBlob->GetBufferPointer(), m_pHullShaderBlob->GetBufferSize(), nullptr, m_pHullShader.GetAddressOf());

			if (shaderResult < 0)
			{
				// Output compilation errors to console.
				std::cout << "ERROR: Tesselation shader creation failed..." << std::endl;

				// Release any data associated with the shader if it gives an error.
				Release();

				return false;
			}

			std::cout << "Tesselation shader was created successfully..." << std::endl;
			break;
		}
		case ShaderType::Vertex:
		{
			shaderResult = device->m_pDevice->CreateVertexShader(m_pVertexShaderBlob->GetBufferPointer(), m_pVertexShaderBlob->GetBufferSize(), nullptr, m_pVertexShader.GetAddressOf());

			if (shaderResult < 0)
			{
				// Output compilation errors to console.
				std::cout << "ERROR: Vertex shader creation failed..." << std::endl;

				// Release any data associated with the shader if it gives an error.
				Release();

				return false;
			}

			// Define the input layout
			D3D11_INPUT_ELEMENT_DESC inputLayout[] =
			{
				{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT	,	0, 0,	D3D11_INPUT_PER_VERTEX_DATA,	0 },
				{ "COLOR"	,	0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, 16,	D3D11_INPUT_PER_VERTEX_DATA,	0 },
				//{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,	0, 12,	D3D11_INPUT_PER_INSTANCE_DATA,	0},

			};

			// Create the input layout.
			long inputResult = device->m_pDevice->CreateInputLayout(inputLayout, ARRAYSIZE(inputLayout), m_pVertexShaderBlob->GetBufferPointer(), m_pVertexShaderBlob->GetBufferSize(), device->m_pInputLayout.GetAddressOf());

			if (inputResult < 0)
			{
				// Output compilation errors to console.
				std::cout << "ERROR: Vertex shader creation failed..." << std::endl;

				// Release any data associated with the shader if it gives an error.
				Release();

				return false;
			}

			// Set the input layout
			device->m_pImmediateContext->IASetInputLayout(device->m_pInputLayout.Get());
			device->m_pImmediateContext->VSSetShader(m_pVertexShader.Get(), nullptr, 0);

			std::cout << "Vertex shader was created successfully..." << std::endl;
			break;
		}
	}

	return true;
}

bool Jade::Graphics::TestDXShader::Release()
{
	std::cout << "Shader cleaning up..." << std::endl;

	return true;
}

bool Jade::Graphics::TestDXShader::CopyToBlob(ShaderType type, ComPtr<ID3DBlob> blob)
{
	long hr = -1;

	switch(type)
	{
	case ShaderType::Compute:
		hr = blob.CopyTo(m_pComputeShaderBlob.GetAddressOf());
		break;
	case ShaderType::Domain:
		hr = blob.CopyTo(m_pDomainShaderBlob.GetAddressOf());
		break;
	case ShaderType::Geometry:
		hr = blob.CopyTo(m_pGeometryShaderBlob.GetAddressOf());
		break;
	case ShaderType::Pixel:
		hr = blob.CopyTo(m_pPixelShaderBlob.GetAddressOf());
		break;
	case ShaderType::Vertex:
		hr = blob.CopyTo(m_pVertexShaderBlob.GetAddressOf());
		break;
	case ShaderType::Tesselation:
		hr = blob.CopyTo(m_pHullShader.GetAddressOf());
		break;
	}

	return hr < 0 ? false : true;
}

/*
bool Jade::Graphics::TestDXShader::Compile(std::string filename, ShaderType type)
{
	unsigned int flags = D3DCOMPILE_ENABLE_STRICTNESS;

#if defined( DEBUG ) || defined( _DEBUG )
	// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
	// Setting this flag improves the shader debugging experience, but still allows 
	// the shaders to be optimized and to run exactly the way they will run in 
	// the release configuration of this program.
	flags |= D3DCOMPILE_DEBUG;

	// Disable optimizations to further improve shader debugging
	flags |= D3DCOMPILE_SKIP_OPTIMIZATION;

#endif

	// Prefer higher shader profile when possible as 5.0 provides better performance on 11-class hardware.
	LPCSTR profile = "";

	D3D_FEATURE_LEVEL featureLevel = device->m_pDevice->GetFeatureLevel();

	// Setting correct profile for the shader compilation.
	switch (type)
	{
	case ShaderType::Compute:
		profile = (featureLevel >= D3D_FEATURE_LEVEL_11_0) ? "cs_5_0" : "cs_4_0";
		break;
	case ShaderType::Domain:
		profile = (featureLevel >= D3D_FEATURE_LEVEL_11_0) ? "ds_5_0" : "ds_4_0";
		break;
	case ShaderType::Geometry:
		profile = (featureLevel >= D3D_FEATURE_LEVEL_11_0) ? "gs_5_0" : "gs_4_0";
		break;
	case ShaderType::Pixel:
		profile = (featureLevel >= D3D_FEATURE_LEVEL_11_0) ? "ps_5_0" : "ps_4_0";
		break;
	case ShaderType::Tesselation:
		profile = (featureLevel >= D3D_FEATURE_LEVEL_11_0) ? "hs_5_0" : "hs_4_0";
		break;
	case ShaderType::Vertex:
		profile = (featureLevel >= D3D_FEATURE_LEVEL_11_0) ? "vs_5_0" : "vs_4_0";
		break;
	}

	if (profile != "")
	{
		ComPtr<ID3DBlob> l_pErrorBlob = nullptr;

		// Compile the shader
		// NOTE: Main must be used as the entrypoint of all shader files for consistency.
		long hr = -1;

		// Output compilation errors to console.
		switch (type)
		{
			case ShaderType::Compute:
			{
				hr = D3DCompileFromFile(Core::Utility::StringToWString(filename).c_str(), nullptr,
					D3D_COMPILE_STANDARD_FILE_INCLUDE, "Main", profile, flags,
					0, m_pComputeShaderBlob.GetAddressOf(), l_pErrorBlob.GetAddressOf());

				if (hr < 0)
				{
					std::cout << "ERROR: Compute shader compilation failed..." << std::endl;

					return false;
				}

				std::cout << "Compute shader was compiled successfully..." << std::endl;
				return true;
			}
			case ShaderType::Domain:
			{
				hr = D3DCompileFromFile(Core::Utility::StringToWString(filename).c_str(), nullptr,
					D3D_COMPILE_STANDARD_FILE_INCLUDE, "Main", profile, flags,
					0, m_pDomainShaderBlob.GetAddressOf(), l_pErrorBlob.GetAddressOf());

				if (hr < 0)
				{
					std::cout << "ERROR: Domain shader compilation failed..." << std::endl;

					return false;
				}

				std::cout << "Domain shader was compiled successfully..." << std::endl;

				return true;
			}
			case ShaderType::Geometry:
				std::cout << "ERROR: Geometry shader compilation failed..." << std::endl;
				return true;
			case ShaderType::Pixel:
			{
				hr = D3DCompileFromFile(Core::Utility::StringToWString(filename).c_str(), nullptr,
					D3D_COMPILE_STANDARD_FILE_INCLUDE, "Main", profile, flags,
					0, m_pPixelShaderBlob.GetAddressOf(), l_pErrorBlob.GetAddressOf());

				if (hr < 0)
				{
					std::cout << "ERROR: Pixel shader compilation failed..." << std::endl;

					return false;
				}

				std::cout << "Pixel shader was compiled successfully..." << std::endl;

				return true;
			}
			case ShaderType::Tesselation:
				std::cout << "ERROR: Tesselation shader compilation failed..." << std::endl;
				break;
			case ShaderType::Vertex:
			{
				hr = D3DCompileFromFile(Core::Utility::StringToWString(filename).c_str(), nullptr,
					D3D_COMPILE_STANDARD_FILE_INCLUDE, "Main", profile, flags,
					0, m_pVertexShaderBlob.GetAddressOf(), l_pErrorBlob.GetAddressOf());

				if (hr < 0)
				{
					std::cout << "ERROR: Vertex shader compilation failed..." << std::endl;

					return false;
				}

				std::cout << "Vertex shader was compiled successfully..." << std::endl;
				return true;
			}
		}
	}

	return false;
}
*/