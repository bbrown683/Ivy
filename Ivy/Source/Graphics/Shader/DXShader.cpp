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

#ifdef IVY_PLATFORM_WINDOWS
bool Ivy::Graphics::DXShader::Create(istring filename, ShaderType type)
{
	// Note: Doesnt actually use the filename, but for consistency 
	// across multiple graphics API's, the interface requires it.
 
	HRESULT hr;

	switch (type)
	{
		case ShaderType::Pixel:
		{
			hr = device->GetID3D11Device()->CreatePixelShader(m_pPixelShaderBlob->GetBufferPointer(), 
				m_pPixelShaderBlob->GetBufferSize(), nullptr, m_pPixelShader.GetAddressOf());

			if (FAILED(hr))
			{
				// Output compilation errors to console.
				std::cout << "ERROR: Pixel shader creation failed..." << std::endl;
				return false;
			}

			std::cout << "Pixel shader was created successfully..." << std::endl;
			break;
		}
		case ShaderType::Vertex:
		{
			hr = device->GetID3D11Device()->CreateVertexShader(m_pVertexShaderBlob->GetBufferPointer(), 
				m_pVertexShaderBlob->GetBufferSize(), nullptr, m_pVertexShader.GetAddressOf());

			if (FAILED(hr))
			{
				// Output compilation errors to console.
				std::cout << "ERROR: Vertex shader creation failed..." << std::endl;
				return false;
			}

			if (!CreateVertexInputLayout())
				return false;
			
			std::cout << "Vertex shader was created successfully..." << std::endl;
			break;
		}
	}

	return true;
}

bool Ivy::Graphics::DXShader::Compile(istring filename, ShaderType type)
{
	unsigned int flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_PACK_MATRIX_COLUMN_MAJOR;

#if defined(DEBUG) || defined(_DEBUG)
	// MakeActive the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
	// Setting this flag improves the shader debugging experience, but still allows 
	// the shaders to be optimized and to run exactly the way they will run in 
	// the release configuration of this program.
	flags |= D3DCOMPILE_DEBUG;
	// Disable optimizations to further improve shader debugging
	flags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	D3D_FEATURE_LEVEL featureLevel = device->GetID3D11Device()->GetFeatureLevel();

	ComPtr<ID3DBlob> l_pErrorBlob = nullptr;

#ifdef IVY_UNICODE
	HRESULT hr = D3DCompileFromFile(filename.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"main", GetCompilerTarget(featureLevel, type).c_str(), flags, 0, const_cast<ID3DBlob**>(GetShaderBlob(type).GetAddressOf()), 
		l_pErrorBlob.GetAddressOf());
#else
    HRESULT hr = D3DCompileFromFile(Core::StringToWString(filename).c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
        "main", GetCompilerTarget(featureLevel, type).c_str(), flags, 0, const_cast<ID3DBlob**>(GetShaderBlob(type).GetAddressOf()),
        l_pErrorBlob.GetAddressOf());
#endif

	if (FAILED(hr))
	{
        // Notify of shader error if one exists.
		if(l_pErrorBlob.Get() != nullptr)
			std::cout << reinterpret_cast<const char*>(l_pErrorBlob->GetBufferPointer()) << std::endl;
		
        // Use error shader in the event of failure.
        if (type == ShaderType::Pixel)
        {
            std::cout << "Trying prefab Pixel Shader..." << std::endl;
            std::cout << Ivy::ShaderPrefab::HLSLErrorPixelShader << std::endl;
            hr = D3DCompile(Ivy::ShaderPrefab::HLSLErrorPixelShader.c_str(), Ivy::ShaderPrefab::HLSLErrorPixelShader.size(),
                nullptr, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "main", GetCompilerTarget(featureLevel, type).c_str(), flags, 0,
                const_cast<ID3DBlob**>(GetShaderBlob(type).GetAddressOf()), l_pErrorBlob.GetAddressOf());
            if (FAILED(hr))
                return false;
        }
        else
        {
            std::cout << "Trying prefab Vertex Shader..." << std::endl;
            std::cout << Ivy::ShaderPrefab::HLSLErrorVertexShader << std::endl;
            hr = D3DCompile(Ivy::ShaderPrefab::HLSLErrorVertexShader.c_str(), Ivy::ShaderPrefab::HLSLErrorVertexShader.size(),
                nullptr, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "main", GetCompilerTarget(featureLevel, type).c_str(), flags, 0,
                const_cast<ID3DBlob**>(GetShaderBlob(type).GetAddressOf()), l_pErrorBlob.GetAddressOf());
            if (FAILED(hr))
                return false;
        }
        
        std::cout << "Prefab shader was compiled successfully..." << std::endl;
        return true;
    }

#ifdef IVY_UNICODE
    std::wcout << "Shader " << filename << " was compiled successfully..." << std::endl;
#else
    std::cout << "Shader " << filename << " was compiled successfully..." << std::endl;
#endif

	return true;
}

bool Ivy::Graphics::DXShader::Release()
{
	std::cout << "Shaders cleaning up..." << std::endl;

	return true;
}

void Ivy::Graphics::DXShader::MakeActive()
{
	// Set the shaders for this mesh if they are not null.
	if (m_pPixelShader.Get() != nullptr)
		device->GetID3D11DeviceContext()->PSSetShader(m_pPixelShader.Get(), nullptr, 0);
	if (m_pVertexShader.Get() != nullptr)
	{
		device->GetID3D11DeviceContext()->VSSetShader(m_pVertexShader.Get(), nullptr, 0);
		// Set the input layout. This is required since multiple shaders may have a different layout.
		device->GetID3D11DeviceContext()->IASetInputLayout(m_pInputLayout.Get());
	}
}

void Ivy::Graphics::DXShader::MakeInactive()
{
	// Unbind shaders.
	if (m_pPixelShader.Get() != nullptr)
		device->GetID3D11DeviceContext()->PSSetShader(nullptr, nullptr, 0);
	if (m_pVertexShader.Get() != nullptr)
		device->GetID3D11DeviceContext()->VSSetShader(nullptr, nullptr, 0);
}

// The following code below is from:
// https://takinginitiative.wordpress.com/2011/12/11/directx-1011-basic-shader-reflection-automatic-input-layout-creation/ 
// I wrapped the code with ComPtr's to ensure no leaks occur.
// This creates the input layout associated with a vertex shader at runtime
// through shader reflection.
bool Ivy::Graphics::DXShader::CreateVertexInputLayout() const
{
	// Reflect shader info
	ComPtr<ID3D11ShaderReflection> l_pVertexShaderReflection;
	
	HRESULT hr = D3DReflect(m_pVertexShaderBlob->GetBufferPointer(), m_pVertexShaderBlob->GetBufferSize(), 
		IID_ID3D11ShaderReflection, reinterpret_cast<void**>(l_pVertexShaderReflection.GetAddressOf()));
		
	if(FAILED(hr))
		return false;

	// Get shader info
	D3D11_SHADER_DESC shaderDesc;
	l_pVertexShaderReflection->GetDesc(&shaderDesc);

	// Read input layout description from shader info
	std::vector<D3D11_INPUT_ELEMENT_DESC> inputLayoutDesc;
	for (unsigned int i = 0; i < shaderDesc.InputParameters; i++)
	{
		D3D11_SIGNATURE_PARAMETER_DESC paramDesc;
		l_pVertexShaderReflection->GetInputParameterDesc(i, &paramDesc);

		// Fill out input element desc
		D3D11_INPUT_ELEMENT_DESC elementDesc;
		elementDesc.SemanticName = paramDesc.SemanticName;
		elementDesc.SemanticIndex = paramDesc.SemanticIndex;
		elementDesc.InputSlot = 0;
		elementDesc.AlignedByteOffset = (i == 0) ? 0 : D3D11_APPEND_ALIGNED_ELEMENT;
		elementDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		elementDesc.InstanceDataStepRate = 0;

		// Determine DXGI format
		if (paramDesc.Mask == 1)
		{
			if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) 
				elementDesc.Format = DXGI_FORMAT_R32_UINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) 
				elementDesc.Format = DXGI_FORMAT_R32_SINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) 
				elementDesc.Format = DXGI_FORMAT_R32_FLOAT;
		}
		else if (paramDesc.Mask <= 3)
		{
			if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) 
				elementDesc.Format = DXGI_FORMAT_R32G32_UINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) 
				elementDesc.Format = DXGI_FORMAT_R32G32_SINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) 
				elementDesc.Format = DXGI_FORMAT_R32G32_FLOAT;
		}
		else if (paramDesc.Mask <= 7)
		{
			if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) 
				elementDesc.Format = DXGI_FORMAT_R32G32B32_UINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) 
				elementDesc.Format = DXGI_FORMAT_R32G32B32_SINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
				elementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
		}
		else if (paramDesc.Mask <= 15)
		{
			if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) 
				elementDesc.Format = DXGI_FORMAT_R32G32B32A32_UINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) 
				elementDesc.Format = DXGI_FORMAT_R32G32B32A32_SINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) 
				elementDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		}

		// Save element desc
		inputLayoutDesc.push_back(elementDesc);
	}

	// Try to create Input Layout
	hr = device->GetID3D11Device()->CreateInputLayout(inputLayoutDesc.data(), static_cast<unsigned>(inputLayoutDesc.size()),
		m_pVertexShaderBlob->GetBufferPointer(), m_pVertexShaderBlob->GetBufferSize(), 
		const_cast<ID3D11InputLayout**>(m_pInputLayout.GetAddressOf()));

	if (FAILED(hr))
		return false;

	std::cout << "Input Layout was created successfully..." << std::endl;

	return true;
}

std::string Ivy::Graphics::DXShader::GetCompilerTarget(D3D_FEATURE_LEVEL featureLevel, ShaderType type)
{
	switch(type)
	{
	case ShaderType::Pixel: return featureLevel == D3D_FEATURE_LEVEL_11_0 ? "ps_5_0" : "ps_4_0";
	case ShaderType::Vertex: return featureLevel == D3D_FEATURE_LEVEL_11_0 ? "vs_5_0" : "vs_4_0";
	default: return "";
	}
}

const ComPtr<ID3DBlob>& Ivy::Graphics::DXShader::GetShaderBlob(ShaderType type)
{
	if (type == ShaderType::Pixel)
		return m_pPixelShaderBlob;

	return m_pVertexShaderBlob;
}

const ComPtr<ID3D11InputLayout>& Ivy::Graphics::DXShader::GetID3D11InputLayout() const
{
	return m_pInputLayout;
}
const ComPtr<ID3D11PixelShader>& Ivy::Graphics::DXShader::GetID3D11PixelShader() const
{
	return m_pPixelShader;
}
const ComPtr<ID3D11VertexShader>& Ivy::Graphics::DXShader::GetID3D11VertexShader() const
{
	return m_pVertexShader;
}
#endif