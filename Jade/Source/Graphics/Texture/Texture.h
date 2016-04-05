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

			std::shared_ptr<ITexture> texture;

		public:

			Texture() : texture(nullptr) { }

			Texture(Device device, std::string filename, TextureType type)
			{
				this->device = device;
				this->filename = filename;
				this->type = type;

				switch (device.GetGraphicsAPI())
				{
				case GraphicsAPI::DirectX:
					texture = std::make_shared<DXTexture>(std::dynamic_pointer_cast<DXDevice>(device.GetIDevice()), filename, type);
					break;
				case GraphicsAPI::OpenGL:
					texture = nullptr;
					break;
				case GraphicsAPI::Vulkan:
					texture = nullptr;
					break;
				default: texture = nullptr;
					break;
				}
			}
			
			bool Bind()	const
			{
				return texture->Bind();
			}

			std::string GetFilename()
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
