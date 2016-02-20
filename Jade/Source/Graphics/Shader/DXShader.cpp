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

#include "DXShader.h"
#include "Core/Utility.h"

bool Jade::Graphics::DXShader::Create()
{
	ID3DBlob* pErrorBlob = nullptr;

	m_pPSBlob->Release();
	m_pVSBlob->Release();

	return false;
}

bool Jade::Graphics::DXShader::Release()
{
	m_pPixelShader->Release();
	m_pVertexShader->Release();

	return false;
}

bool Jade::Graphics::DXShader::Compile(ShaderType type)
{
	// Compile the shader
	ID3DBlob* pShaderBlob = nullptr;

	if (type == ShaderType::Geometry)
	{
		//DXDevice::m_pDevice->CreateGeometryShader()
	}
	else if (type == ShaderType::Pixel)
	{
		//DXDevice::m_pDevice->CreatePixelShader()
	}
	else if (type == ShaderType::Tesselation)
	{
		//DXDevice::m_pDevice->CreateHullShader()
	}
	else if (type == ShaderType::Vertex)
	{
		//DXDevice::m_pDevice->CreateVertexShader()
	}

	return false;
}
