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

#include "GLRasterizer.h"

bool Jade::Graphics::GLRasterizer::SetRasterizerState(CullMode cullMode, FillMode fillMode, WindMode windMode)
{	
	// MakeActive variables.
	this->cullMode = cullMode;
	this->fillMode = fillMode;
	this->windMode = windMode;

	if (disabled && cullMode != CullMode::None)
	{
		glEnable(GL_CULL_FACE);
		disabled = false;
	}

	// OpenGL modifications.
	switch(cullMode)
	{
	case CullMode::None: glDisable(GL_CULL_FACE); disabled = true; break;
	case CullMode::Front: glCullFace(GL_FRONT);	break;
	case CullMode::Back: glCullFace(GL_BACK); break;
	}
	
	glPolygonMode(GL_FRONT_AND_BACK, fillMode == FillMode::Solid ? GL_FILL : GL_LINE);
	glFrontFace(windMode == WindMode::CounterClockwise ? GL_CCW : GL_CW);

	return true;
}

Jade::Graphics::CullMode Jade::Graphics::GLRasterizer::GetCullMode()
{
	return cullMode;
}

Jade::Graphics::FillMode Jade::Graphics::GLRasterizer::GetFillMode()
{
	return fillMode;
}

Jade::Graphics::WindMode Jade::Graphics::GLRasterizer::GetWindMode()
{
	return windMode;
}
