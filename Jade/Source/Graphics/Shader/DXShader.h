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

#include "Core/Utility.h"

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

			string filename;
			ShaderType type;
			std::shared_ptr<DXDevice> device;

			// Holds our shader compilation information.
			ID3DBlob*				m_pShaderBlob		= nullptr;

			ID3D11ComputeShader*	m_pComputeShader	= nullptr;
			ID3D11DomainShader*		m_pDomainShader		= nullptr;
			ID3D11GeometryShader*	m_pGeometryShader	= nullptr;
			ID3D11HullShader*		m_pHullShader		= nullptr;
			ID3D11PixelShader*		m_pPixelShader		= nullptr;
			ID3D11VertexShader*		m_pVertexShader		= nullptr;

			bool Create() override;
			bool Release() override;

		public:

			DXShader(string filename, ShaderType type, std::shared_ptr<DXDevice> device)
			{	
				this->filename = filename;
				this->device = device;
				this->type = type;

				// If our shaders compile correctly, we can create them.
				if(Compile())
					Create();
			}

			~DXShader()
			{
				Release();

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
			}

			bool Compile() override;

		};
	}
}
