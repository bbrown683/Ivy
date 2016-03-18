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

#include "Graphics/Device/Device.h"
#include "Graphics/Buffer/IBuffer.h"
#include "Graphics/Buffer/DXBuffer.h"
#include "Graphics/Buffer/GLBuffer.h"

//#include "Math/Vector3.h"

namespace Jade
{
	namespace Graphics
	{
		class Buffer
		{
		private:

			Math::Vertex* vertex;

			std::shared_ptr<Device> device;
			std::shared_ptr<IBuffer> buffer;

			std::shared_ptr<IBuffer> CreateBuffer();

		public:

			Buffer(Math::Vertex* vertex, std::shared_ptr<Device> device)
			{
				this->vertex = vertex;
				this->device = device;

				buffer = CreateBuffer();
			}

			void Draw()	const
			{
				buffer->Draw();
			}
		};
	}
}
