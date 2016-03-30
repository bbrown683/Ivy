#pragma once

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

#include <Core/Utility.h>
#include "Graphics/Shader/IShader.h"
#include "Graphics/Shader/ShaderType.h"
#include "Graphics/Device/DXDevice.h"

namespace Jade
{
	namespace Graphics
	{
		class DXShader : public IShader
		{
		private:

			std::shared_ptr<DXDevice> device;
			std::string filename;

			ShaderType type;

			// Holds our shader compilation information.
			ComPtr<ID3DBlob>				m_pShaderBlob		= nullptr;

			ComPtr<ID3D11ComputeShader>		m_pComputeShader	= nullptr;
			ComPtr<ID3D11DomainShader>		m_pDomainShader		= nullptr;
			ComPtr<ID3D11GeometryShader>	m_pGeometryShader	= nullptr;
			ComPtr<ID3D11HullShader>		m_pHullShader		= nullptr;
			ComPtr<ID3D11PixelShader>		m_pPixelShader		= nullptr;
			ComPtr<ID3D11VertexShader>		m_pVertexShader		= nullptr;

			bool Create(ShaderType type) override;
			bool Release() override;

			// Determines if we are using precompiled shaders.
			// Means wee can skip the compilation process.
			//bool precompiled = false;

		public:

			DXShader(std::shared_ptr<DXDevice> device, std::string filename, ShaderType type)
			{
				this->device = device;
				this->filename = filename;
				this->type = type;

				// Do not need to compile shaders that are already 
				// in a bytecode format.
				// .cso is the compiled shader file extension.
				if (filename.find(".cso") != -1)
				{
					long shaderResult = 0;

					shaderResult = D3DReadFileToBlob(Core::Utility::StringToWString(filename).c_str(), m_pShaderBlob.GetAddressOf());

					if (shaderResult < 0)
					{
						// Output compilation errors to console.
						std::cout << "ERROR: Failed to read compiled shader bytecode..." << std::endl;

						DXShader::Release();
						exit(EXIT_FAILURE);
					}

					DXShader::Create(type);
				}
			}

			~DXShader()
			{
				DXShader::Release();
			}

			//bool Compile(std::string filename, ShaderType type) override;

		};
	}
}
