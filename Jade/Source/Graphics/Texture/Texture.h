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

#include <Graphics/Device/Device.h>
#include <Graphics/Texture/DXTexture.h>
#include "Graphics/Texture/GLTexture.h"
#include <Graphics/Texture/ITexture.h>
#include "TextureFactory.h"

namespace Jade
{
	namespace Graphics
	{
		class Texture
		{
		private:

			Device device;
			std::string filename;
			TextureType type;

			unsigned char* bitmap; 
			int width;
			int height; 
			unsigned int bits;

			std::shared_ptr<ITexture> texture;

		public:

			Texture() : texture(nullptr) { }

			Texture(Device device, std::string filename, TextureType type)
			{
				this->device = device;
				this->filename = filename;
				this->type = type;

				texture = TextureFactory::Generate<ITexture>(device, filename, type);
			
			}

			Texture(Device device, unsigned char* bitmap, int width, int height, int pitch, unsigned int bits, TextureType type)
			{
				this->device = device;
				this->bitmap = bitmap;
				this->width = width;
				this->height = height;
				this->bits = bits;
				this->type = type;
				
				texture = TextureFactory::Generate<ITexture>(device, bitmap, width, height, pitch, bits, type);
			}

			bool CreateTextureFromFile() const
			{
				return texture->CreateTextureFromFile();
			}

			bool CreateTextureFromMemory() const
			{
				return texture->CreateTextureFromMemory();
			}

			void Update() const
			{
				return texture->Update();
			}

			std::string GetFilename() const
			{
				return filename;
			}

			std::shared_ptr<ITexture> GetITexture() const
			{
				return texture;
			}
		};
	}
}
