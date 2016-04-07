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

#include <Graphics/Buffer/IBuffer.h>
#include <Graphics/Buffer/Usage.h>
#include <Graphics/Device/DXDevice.h>
#include <Math/Vertex.h>

#include <directxmath.h>

namespace Jade
{
	namespace Graphics
	{
		class DXConstantBuffer : public IBuffer
		{
		private:

			std::shared_ptr<DXDevice> device;
			Usage usage;

			typedef struct ConstantBuffer
			{
				DirectX::XMMATRIX world;
				DirectX::XMMATRIX view;
				DirectX::XMMATRIX projection;
			} Space;

			Space space;
			DirectX::XMMATRIX world;
			DirectX::XMMATRIX view;
			DirectX::XMMATRIX projection;

			ComPtr<ID3D11Buffer> m_pConstantBuffer;

		public:

			DXConstantBuffer(std::shared_ptr<DXDevice> device, Usage usage)
			{
				this->device = device;
				this->usage = usage;
			}

			bool Bind() override;
			bool Unbind() override;
		};
	}
}

#endif // _WIN32