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

#include <Graphics/Buffer/IVertexBuffer.h>
#include <Graphics/Buffer/DXVertexBuffer.h>
#include <Graphics/Buffer/GLVertexBuffer.h>
#include <Graphics/Device/Device.h>

namespace Jade
{
	namespace Graphics
	{
		class VertexBuffer
		{
		private:

			Device device;

			std::shared_ptr<IVertexBuffer> vertexBuffer;

		public:

			VertexBuffer() { }

			VertexBuffer(Device device)
			{
				switch (device.GetGraphicsAPI())
				{
				case GraphicsAPI::DirectX:
					vertexBuffer = std::make_shared<DXVertexBuffer>(std::dynamic_pointer_cast<DXDevice>(device.GetIDevice()));
					break;
				case GraphicsAPI::OpenGL:
					// OpenGL uses a state machine so we dont need to pass a device.
					vertexBuffer = std::make_shared<GLVertexBuffer>();
					break;
				case GraphicsAPI::Vulkan:
					vertexBuffer = nullptr;
					break;
				}
			}

			std::vector<Math::Vertex> GetVertices();
			void SetVertices(std::vector<Math::Vertex> vertices);
			bool Bind();
			bool Unbind();
		};
	}
}
