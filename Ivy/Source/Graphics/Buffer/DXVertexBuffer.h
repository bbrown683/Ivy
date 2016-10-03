#pragma once

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

#include "Graphics/Buffer/IVertexBuffer.h"
#include "Graphics/Buffer/PrimitiveType.h"
#include "Graphics/Device/DXDevice.h"
#include "Math/Vertex.h"

#ifdef IVY_PLATFORM_WINDOWS
namespace Ivy
{
	namespace Graphics
	{
		class DXVertexBuffer : public IVertexBuffer
		{
			std::shared_ptr<DXDevice> device;
			std::vector<Math::Vertex> vertices;
			PrimitiveType primitiveType;
			ComPtr<ID3D11Buffer> m_pVertexBuffer;

			bool Create() override;
			void Bind() override;
			void Unbind() override;

		public:

			DXVertexBuffer(std::shared_ptr<DXDevice> device, PrimitiveType primitiveType)
			{
				this->device = device;
			}

			~DXVertexBuffer()
			{
				DXVertexBuffer::Unbind();
			}

			std::vector<Math::Vertex> GetVertices() override;
			void SetVertices(std::vector<Math::Vertex> vertices) override;

			void Draw() override;
		};
	}
}
#endif