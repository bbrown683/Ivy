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

#include "glew.h"
#include <gl/GL.h>

#include "Graphics/Buffer/GLBuffer.h"

void Jade::Graphics::GLMesh::Bind()
{
	GLuint vertexArray;
	GLuint vertexBuffer;

	// Generate our vertex array and Bind it to the first element.
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);

	// Generate our vertex buffer and bind it.
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLuint) * sizeof(vertices) / sizeof(Math::Vector3), vertices, GL_STATIC_DRAW);
}

void Jade::Graphics::GLMesh::Unbind()
{
	// Unbind the vertex buffer.
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Jade::Graphics::GLMesh::Draw()
{
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 0, GL_FLOAT, false, 0, nullptr);
	glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / sizeof(Math::Vector3));
	glDisableVertexAttribArray(0);
}
