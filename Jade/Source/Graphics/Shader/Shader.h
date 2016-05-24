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

#include "Graphics/Device/Device.h"
#include "Graphics/Device/GraphicsAPI.h"
#include "Graphics/Shader/DXShader.h"
#include "Graphics/Shader/GLShader.h"
#include "Graphics/Shader/IShader.h"
#include "Graphics/Shader/ShaderType.h"


namespace Jade
{
	namespace Graphics
	{
		class Shader
		{
			Device device;
			std::map<std::string, ShaderType> shaders;
			std::string filename;
			ShaderType type;

			std::shared_ptr<IShader> shader;

		public:

			// Note: Do not use this constructor as everything is set to null.
			Shader() : shader(nullptr) { }

			Shader(Device device, std::map<std::string, ShaderType> shaders)
			{
				this->device = device;
				this->shaders = shaders;

				switch (device.GetGraphicsAPI())
				{
				case GraphicsAPI::DirectX:
					shader = std::make_shared<DXShader>(std::dynamic_pointer_cast<DXDevice>(device.GetIDevice()), shaders);
					break;
				case GraphicsAPI::OpenGL:
					shader = std::make_shared<GLShader>(shaders);
					break;
				case GraphicsAPI::Vulkan:
					shader = nullptr;
					break;
				}
			}

			// Makes the shader current.
			void MakeActive() const
			{
				shader->MakeActive();
			}

			void MakeInactive() const
			{
				shader->MakeInactive();
			}

			std::shared_ptr<IShader> GetIShader() const
			{
				return shader;
			}
		};
	}
}
