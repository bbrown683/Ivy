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

#include <Core/Utility.h>
#include "Graphics/Shader/IShader.h"
#include "Graphics/Shader/ShaderType.h"
#include "Graphics/Device/DXDevice.h"

#ifdef JADE_PLATFORM_WINDOWS
#include <d3dcompiler.h>

namespace Jade
{
	namespace Graphics
	{
		class DXShader : public IShader
		{
			std::shared_ptr<DXDevice> device;
			std::map<std::string, ShaderType> shaders;

			// Holds our shader compilation information.
			ComPtr<ID3DBlob>				m_pPixelShaderBlob = nullptr;
			ComPtr<ID3DBlob>				m_pVertexShaderBlob = nullptr;

			// Contains the input layout for the vertex buffer.
			ComPtr<ID3D11InputLayout>		m_pInputLayout = nullptr;

			// Different shader objects.
			ComPtr<ID3D11PixelShader>		m_pPixelShader = nullptr;
			ComPtr<ID3D11VertexShader>		m_pVertexShader = nullptr;

			bool Create(std::string filename, ShaderType type) override;
			bool Compile(std::string filename, ShaderType type) override;
			bool Release() override;
			bool CopyToBlob(ShaderType type, ComPtr<ID3DBlob> blob);

		public:

			DXShader(std::shared_ptr<DXDevice> device, std::map<std::string, ShaderType> shaders)
			{
				this->device = device;
				this->shaders = shaders;

				for (auto iterator = shaders.begin(); iterator != shaders.end(); ++iterator)
				{
					std::string iString = iterator->first;
					ShaderType iType = iterator->second;

					// Temporary blob for getting blob data.
					ComPtr<ID3DBlob> m_pTemporaryBlob = nullptr;

					long shaderResult = D3DReadFileToBlob(Core::Utility::StringToWString(iString).c_str(), m_pTemporaryBlob.GetAddressOf());
						
					if (shaderResult < 0)
					{
						// Output compilation errors to console.
						std::cout << "ERROR: Failed to read compiled shader bytecode..." << std::endl;

						exit(EXIT_FAILURE);
					}
					// Copys the reference of the temporary blob to the specified shader blob.
					// If it succeeds we can create the shader.
					if (CopyToBlob(iType, m_pTemporaryBlob))
					{
						if (!DXShader::Create("", iType))
							DXShader::Release();
					}
					else
						DXShader::Release();
				}
			}

			void MakeActive() override;

			// Helper methods for other classes that require a DXTexture.
			const ComPtr<ID3D11InputLayout>& GetID3D11InputLayout() const;
			const ComPtr<ID3D11PixelShader>& GetID3D11PixelShader() const;
			const ComPtr<ID3D11VertexShader>& GetID3D11VertexShader() const;

			~DXShader()
			{
				DXShader::Release();
			}
		};
	}
}
#endif