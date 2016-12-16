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

#include "GLIndexBuffer.h"

void Ivy::Graphics::GLIndexBuffer::Bind()
{

}

bool Ivy::Graphics::GLIndexBuffer::Create()
{
	// Generate a buffer for the indices;
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), indices.data(), GL_STATIC_DRAW);

	return true;
}

std::vector<unsigned short> Ivy::Graphics::GLIndexBuffer::GetIndices()
{
	return indices;
}

void Ivy::Graphics::GLIndexBuffer::SetIndices(std::vector<unsigned short> indices)
{
	this->indices = indices;
}

void Ivy::Graphics::GLIndexBuffer::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &indexBuffer);
}

void Ivy::Graphics::GLIndexBuffer::Draw()
{
    glDrawElements(GL_TRIANGLE_STRIP, static_cast<GLsizei>(indices.size()),
        GL_UNSIGNED_SHORT, nullptr);
}
