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

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"

namespace Jade
{
	namespace Graphics
	{
		/*! \brief This class is used to draw to the buffers we have instantiated.
		*
		*  Due to the current engine implementation, while we set the engine buffers,
		*  we do not actually have a way to draw these to the buffer in an abstract
		*  manner, hence the existence of this class to use the data from the vertex,
		*  index, and constant buffers to draw to the buffer.
		*/
		class DrawBuffer
		{
			//! Vertex buffer object. We will need the vertex data from this object.
			VertexBuffer vBuffer;
			//! Index buffer object. We will be grabbing the index data from this object.
			IndexBuffer iBuffer;
			//! Contant buffer object. This holds matrix data that we will need.
			ConstantBuffer cBuffer;

			DrawBuffer(VertexBuffer vBuffer, IndexBuffer iBuffer, ConstantBuffer cBuffer)
			{
				this->vBuffer = vBuffer;
				this->iBuffer = iBuffer;
				this->cBuffer = cBuffer;
			}

			//! Draws to the current buffers.
			void DrawToBuffer();
		};
	}
}
