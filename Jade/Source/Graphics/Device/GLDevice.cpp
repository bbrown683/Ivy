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

#include "GLDevice.h"
#include <cassert>

bool Jade::Graphics::GLDevice::Create()
{
	context = SDL_GL_CreateContext(window->GetSDLWindow());

	SDL_GL_MakeCurrent(window->GetSDLWindow(), context);

	SDL_GL_SetSwapInterval(1);

	GLenum result = glewInit();

	assert(result != GLEW_OK);

	return result == GLEW_OK ? true : false;
}

bool Jade::Graphics::GLDevice::Release()
{
	SDL_GL_DeleteContext(context);

	return context == nullptr ? true : false;
}

void Jade::Graphics::GLDevice::Clear(Math::Color color)
{
	glClearColor(color.GetRed(), color.GetGreen(), color.GetBlue(), color.GetAlpha());
	glClear(GL_COLOR_BUFFER_BIT);
}

void Jade::Graphics::GLDevice::Present()
{
	SDL_GL_SwapWindow(window->GetSDLWindow());
}