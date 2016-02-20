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
#include "Graphics/Device/DXDevice.h"

namespace Jade
{
	namespace Graphics
	{
		class DXShader : IShader
		{
		private:

			std::shared_ptr<DXDevice> device;

			ID3DBlob* m_pVSBlob;
			ID3DBlob* m_pPSBlob;

			ID3D11VertexShader*     m_pVertexShader;
			ID3D11PixelShader*      m_pPixelShader;
			ID3D11InputLayout*      m_pVertexLayout;
			ID3D11Buffer*           m_pVertexBuffer;

			bool Create() override;
			bool Release() override;

		public:

			DXShader(std::shared_ptr<DXDevice> device)
			{	
				this->device = device;

				Create();
			}

			~DXShader()
			{
				Release();

				delete m_pPSBlob;
				delete m_pVSBlob;
				delete m_pPixelShader;
				delete m_pVertexShader;

				delete m_pVertexLayout;
				delete m_pVertexBuffer;
			}

			bool Compile(ShaderType type) override;

		};
	}
}
