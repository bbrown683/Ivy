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

#include <d3dcompiler.h>
#include <iostream>

#include "Graphics/Shader/DXShader.h"

bool Jade::Graphics::DXShader::Create()
{
	long shaderResult = 0;

	switch (type)
	{
		case ShaderType::Compute:
		{
			shaderResult = device->m_pDevice->CreateComputeShader(m_pShaderBlob->GetBufferPointer(), m_pShaderBlob->GetBufferSize(), nullptr, &m_pComputeShader);
			
			if (shaderResult < 0)
			{
				if (m_pShaderBlob)
					m_pShaderBlob->Release();

				// Output compilation errors to console.
				std::cout << "ERROR: Computee shader creation failed..." << std::endl;

				// Release any data associated with the shader if it gives an error.
				Release();

				return false;
			}

			std::cout << "Compute shader was created successfully..." << std::endl;
			break;
		}
		case ShaderType::Domain:
		{
			shaderResult = device->m_pDevice->CreateDomainShader(m_pShaderBlob->GetBufferPointer(), m_pShaderBlob->GetBufferSize(), nullptr, &m_pDomainShader);
		
			if (shaderResult < 0)
			{
				if (m_pShaderBlob)
					m_pShaderBlob->Release();

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
			shaderResult = device->m_pDevice->CreateGeometryShader(m_pShaderBlob->GetBufferPointer(), m_pShaderBlob->GetBufferSize(), nullptr, &m_pGeometryShader);
			
			if (shaderResult < 0)
			{
				if (m_pShaderBlob)
					m_pShaderBlob->Release();

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
			shaderResult = device->m_pDevice->CreatePixelShader(m_pShaderBlob->GetBufferPointer(), m_pShaderBlob->GetBufferSize(), nullptr, &m_pPixelShader);

			if (shaderResult < 0)
			{
				if (m_pShaderBlob)
					m_pShaderBlob->Release();

				// Output compilation errors to console.
				std::cout << "ERROR: Pixel shader creation failed..." << std::endl;

				// Release any data associated with the shader if it gives an error.
				Release();

				return false;
			}

			device->m_pImmediateContext->PSSetShader(m_pPixelShader, nullptr, 0);

			std::cout << "Pixel shader was created successfully..." << std::endl;
			break;
		}
		case ShaderType::Tesselation:
		{
			shaderResult = device->m_pDevice->CreateHullShader(m_pShaderBlob->GetBufferPointer(), m_pShaderBlob->GetBufferSize(), nullptr, &m_pHullShader);
			
			if (shaderResult < 0)
			{
				if (m_pShaderBlob)
					m_pShaderBlob->Release();

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
			shaderResult = device->m_pDevice->CreateVertexShader(m_pShaderBlob->GetBufferPointer(), m_pShaderBlob->GetBufferSize(), nullptr, &m_pVertexShader);

			if(shaderResult < 0)
			{
				if (m_pShaderBlob)
					m_pShaderBlob->Release();

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
				//{ "TEXCOORD",	0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, 28,	D3D11_INPUT_PER_INSTANCE_DATA,	0},
			};

			// Create the input layout.
			long inputResult = device->m_pDevice->CreateInputLayout(inputLayout, ARRAYSIZE(inputLayout), m_pShaderBlob->GetBufferPointer(), m_pShaderBlob->GetBufferSize(), &device->m_pInputLayout);

			if(inputResult < 0)
			{
				if(m_pShaderBlob)
					m_pShaderBlob->Release();

				// Output compilation errors to console.
				std::cout << "ERROR: Vertex shader creation failed..." << std::endl;

				// Release any data associated with the shader if it gives an error.
				Release();

				return false;
			}

			// Set the input layout
			device->m_pImmediateContext->IASetInputLayout(device->m_pInputLayout);
			device->m_pImmediateContext->VSSetShader(m_pVertexShader, nullptr, 0);

			std::cout << "Vertex shader was created successfully..." << std::endl;
			break;
		}	
	}

	m_pShaderBlob->Release();

	return true;
}

bool Jade::Graphics::DXShader::Release()
{
	// Release only what we allocated.
	if(m_pComputeShader)
		m_pComputeShader->Release();
	if(m_pDomainShader)		
		m_pDomainShader->Release();
	if(m_pGeometryShader)	
		m_pGeometryShader->Release();
	if(m_pHullShader)		
		m_pHullShader->Release();
	if(m_pPixelShader)		
		m_pPixelShader->Release();
	if(m_pVertexShader)		
		m_pVertexShader->Release();

	m_pShaderBlob = nullptr;

	m_pComputeShader = nullptr;
	m_pDomainShader = nullptr;
	m_pGeometryShader = nullptr;
	m_pHullShader = nullptr;
	m_pPixelShader = nullptr;
	m_pVertexShader = nullptr;

	delete m_pShaderBlob;

	delete m_pComputeShader;
	delete m_pDomainShader;
	delete m_pGeometryShader;
	delete m_pHullShader;
	delete m_pPixelShader;
	delete m_pVertexShader;

	std::cout << "Shader cleaning up..." << std::endl;

	return true;
}

bool Jade::Graphics::DXShader::Compile()
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
	switch(type)
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

	if(profile != "")
	{
		ID3DBlob* l_pErrorBlob = nullptr;

		// Convert string to a wstring as D3DCompileFromFile requires it.
		wstring filepath(filename.begin(), filename.end());

		// Compile the shader
		// NOTE: Main must be used as the entrypoint of all shader files for consistency.
		long hr = D3DCompileFromFile(filepath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "Main", profile, flags, 0, &m_pShaderBlob, &l_pErrorBlob);

		if (hr < 0)
		{
			// Output compilation errors to console.
			switch (type)
			{
			case ShaderType::Compute:
				std::cout << "ERROR: Compute shader compilation failed..." << std::endl;
				break;
			case ShaderType::Domain:
				std::cout << "ERROR: Domain shader compilation failed..." << std::endl;
				break;
			case ShaderType::Geometry:
				std::cout << "ERROR: Geometry shader compilation failed..." << std::endl;
				break;
			case ShaderType::Pixel:
				std::cout << "ERROR: Pixel shader compilation failed..." << std::endl;
				break;
			case ShaderType::Tesselation:
				std::cout << "ERROR: Tesselation shader compilation failed..." << std::endl;
				break;
			case ShaderType::Vertex:
				std::cout << "ERROR: Vertex shader compilation failed..." << std::endl;
				break;
			}

			// Release any data associated with the shader if it gives an error.
			Release();

			return false;
		}

		switch(type)
		{
		case ShaderType::Pixel:
			std::cout << "Pixel shader was compiled successfully..." << std::endl;
			break;
		case ShaderType::Vertex:
			std::cout << "Vertex shader was compiled successfully..." << std::endl;
		}

		if(l_pErrorBlob)
			l_pErrorBlob->Release();

		delete l_pErrorBlob;

		return true;
	}

	return false;
}
