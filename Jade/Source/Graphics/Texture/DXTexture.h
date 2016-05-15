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

#include "stb/stb_image.h"

#include <Graphics/Device/DXDevice.h>
#include <Graphics/Texture/ITexture.h>
#include <Graphics/Texture/TextureType.h>

// Include after other headers.
#include "FreeImage.h"

#ifdef JADE_PLATFORM_WINDOWS
namespace Jade
{
	namespace Graphics
	{
		class DXTexture : public ITexture
		{
			std::shared_ptr<DXDevice> device;
			std::string filename;
			TextureType type;

			unsigned char* bitmap;
			int width;
			int height;
			int pitch;
			unsigned int bits;

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

			DXTexture(std::shared_ptr<DXDevice> device, unsigned char* bitmap, int width, int height, int pitch, unsigned int bits, TextureType type)
			{
				this->device = device;
				this->bitmap = bitmap;
				this->width = width;
				this->height = height;
				this->pitch = pitch;
				this->bits = bits;
				this->type = type;
			}

			~DXTexture()
			{
				std::cout << "Texture was released successfully..." << std::endl;
			}

			//! Creates a texture from the file specified in the constructor and returns a bool determining if it was successful.
			bool CreateTextureFromFile() override;
			//! Creates a texture from the bits specified in the constructor and returns a bool determining if it was successful.
			bool CreateTextureFromMemory() override;
			//! Updates the texture resources to ensure that they remain the target of the drawing operations.
			void Update() override;

			const ComPtr<ID3D11ShaderResourceView>& GetID3D11ShaderResourceView() const;
		};
	}
}

#endif // _WIN32