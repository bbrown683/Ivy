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

#include "Graphics/Buffer/IUniformBuffer.h"
#include "Graphics/Buffer/DXConstantBuffer.h"
#include "Graphics/Buffer/GLUniformBuffer.h"
#include "Graphics/Device/Device.h"

namespace Jade
{
	namespace Graphics
	{
		class ConstantBuffer
		{
			Device device;
			std::shared_ptr<IUniformBuffer> constantBuffer;

		public:

			ConstantBuffer() { }

			ConstantBuffer(Device device)
			{
				switch (device.GetGraphicsAPI())
				{
				case GraphicsAPI::DirectX:
					constantBuffer = std::make_shared<DXConstantBuffer>(std::dynamic_pointer_cast<DXDevice>(device.GetIDevice()));
					break;
				case GraphicsAPI::OpenGL:
					constantBuffer = nullptr;
					break;
				case GraphicsAPI::Vulkan:
					constantBuffer = nullptr;
					break;
				}
			}

			void Bind();
			bool Create(bool model, bool view, bool projection);
			
			Math::Matrix GetProjectionMatrix();
			Math::Matrix GetViewMatrix();
			Math::Matrix GetWorldMatrix();

			void SetProjectionMatrix(Math::Matrix matrix);
			void SetViewMatrix(Math::Matrix matrix);
			void SetWorldMatrix(Math::Matrix matrix);
			
			void Unbind();
			void Update();
		};
	}
}
