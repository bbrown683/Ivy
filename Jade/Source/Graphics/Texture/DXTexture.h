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

#ifdef _WIN32

#include <Graphics/Device/DXDevice.h>
#include <Graphics/Texture/ITexture.h>
#include <Graphics/Texture/TextureType.h>

// Have to define after due to conflictions with DirectX.
#include "FreeImage/freeimage.h"

namespace Jade
{
	namespace Graphics
	{
		class DXTexture : public ITexture
		{
		private:

			std::shared_ptr<DXDevice> device;
			std::string filename;
			TextureType type;

			ComPtr<ID3D11Texture2D> m_pTexture = nullptr;
			ComPtr<ID3D11ShaderResourceView> m_pShaderResourceView = nullptr;
			ComPtr<ID3D11SamplerState> m_pSamplerState = nullptr;

		public:

			DXTexture(std::shared_ptr<DXDevice> device, std::string filename, TextureType type)
			{
				this->device = device;
				this->filename = filename;
				this->type = type;
			}

			~DXTexture()
			{
				DXTexture::Unbind();
			}

			bool Bind() override;
			bool Unbind() override;
			ComPtr<ID3D11ShaderResourceView>& GetID3D11ShaderResourceView();
			ComPtr<ID3D11SamplerState>& GetID3D11SamplerState();
		};
	}
}

#endif // _WIN32