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

#include "GLUniformBuffer.h"

void Jade::Graphics::GLUniformBuffer::Bind()
{

}

bool Jade::Graphics::GLUniformBuffer::Create(bool model, bool view, bool projection)
{
	return false;
}

Jade::Math::Matrix Jade::Graphics::GLUniformBuffer::GetProjectionMatrix()
{
	return Math::Matrix();
}

Jade::Math::Matrix Jade::Graphics::GLUniformBuffer::GetViewMatrix()
{
	return Math::Matrix();
}

Jade::Math::Matrix Jade::Graphics::GLUniformBuffer::GetWorldMatrix()
{
	return Math::Matrix();
}

void Jade::Graphics::GLUniformBuffer::SetProjectionMatrix(Math::Matrix matrix)
{
}

void Jade::Graphics::GLUniformBuffer::SetViewMatrix(Math::Matrix matrix)
{
}

void Jade::Graphics::GLUniformBuffer::SetWorldMatrix(Math::Matrix matrix)
{
}

void Jade::Graphics::GLUniformBuffer::Unbind()
{

}

void Jade::Graphics::GLUniformBuffer::Update()
{

}
