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
#include "GL/GL.h"
#include "GLGraphicsDevice.h"

bool Jade::Graphics::GLGraphicsDevice::CreateDevice()
{
	// Create a graphicsDevice.

	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		32,
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		24,
		8,
		0,
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};

	hdc = GetDC(static_cast<HWND>(window->Handle()));

	int iPixelFormat = ChoosePixelFormat(hdc, &pfd);
	SetPixelFormat(hdc, iPixelFormat, &pfd);

	renderingContext = wglCreateContext(hdc);
	wglMakeCurrent(hdc, renderingContext);

	return true;

	/*
	HWND dummyWND = CreateWindow("Dummy", "Dummy", WS_POPUP | WS_DISABLED, 0, 0, 0, 0, nullptr, nullptr, nullptr, nullptr);

	PIXELFORMATDESCRIPTOR dummyPFD =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		32,
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		24,
		8,
		0,
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};

	HDC dummyDC = GetDC(dummyWND);

	int iPixelFormat = ChoosePixelFormat(dummyDC, &dummyPFD);
	SetPixelFormat(dummyDC, iPixelFormat, &dummyPFD);

	HGLRC dummyContext = wglCreateContext(dummyDC);
	wglMakeCurrent(dummyDC, dummyContext);

	int major, minor;
		
	glGetIntegerv(GL_MAJOR_VERSION, &major);
	glGetIntegerv(GL_MINOR_VERSION, &minor);
		
	// We only want to render using OpenGL 4+
	if (major < 4)
		return false;

	if (glewInit() != GLEW_OK)
		return false;


	return true;
	*/
}

bool Jade::Graphics::GLGraphicsDevice::ReleaseDevice()
{
	wglDeleteContext(renderingContext);
	return true;
}

void Jade::Graphics::GLGraphicsDevice::Clear(Math::Color color)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(color.GetRed(), color.GetGreen(), color.GetBlue(), color.GetAlpha());
}

void Jade::Graphics::GLGraphicsDevice::Present()
{
	SwapBuffers(hdc);
}
