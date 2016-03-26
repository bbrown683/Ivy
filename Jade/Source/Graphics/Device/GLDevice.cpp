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

#include "GLDevice.h"
#include <iostream>

bool Jade::Graphics::GLDevice::Create()
{
#ifdef WGL
	
	std::cout << "[Device Context]" << std::endl;

	HWND dummyWND = CreateWindowW(L"NULL", L"NULL", WS_DISABLED, 0, 0, 0, 0, nullptr, nullptr, GetModuleHandle(nullptr), nullptr);
	HDC dummyDC = GetDC(dummyWND);

	PIXELFORMATDESCRIPTOR dummyPixelFormatDescriptor =
	{
		sizeof(dummyPixelFormatDescriptor), 1, PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA, static_cast<BYTE>(specification.colorBits), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, static_cast<BYTE>(specification.depthBits), static_cast<BYTE>(specification.stencilBits), 0, PFD_MAIN_PLANE,
		0, 0, 0, 0
	};

	int dummyPixelFormat = ChoosePixelFormat(dummyDC, &dummyPixelFormatDescriptor);
	SetPixelFormat(dummyDC, dummyPixelFormat, &dummyPixelFormatDescriptor);

	// Create dummy context
	HGLRC dummyGLRC = wglCreateContext(dummyDC);
	wglMakeCurrent(dummyDC, dummyGLRC);

	// Supported OpenGL version.
	int major, minor;
	glGetIntegerv(GL_MAJOR_VERSION, &major);
	glGetIntegerv(GL_MINOR_VERSION, &minor);

	// Anything below 4.5 is unsupported.
	if (major < 4 && minor < 5)
		return false;

	// Load extensions.
	GLenum result = glewInit();
	if(result != GLEW_OK)
		return false;

	// These extensions are required for the creation of a modern OpenGL context.
	if(!WGLEW_ARB_pixel_format && !WGLEW_ARB_create_context)
		return false;

	// Choose final pixel format
	const int pixelAttribs[] =
	{
		WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
		WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
		WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
		WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
		WGL_COLOR_BITS_ARB, specification.colorBits,
		WGL_DEPTH_BITS_ARB, specification.depthBits,
		WGL_STENCIL_BITS_ARB, specification.stencilBits,
		WGL_SAMPLE_BUFFERS_ARB, (specification.samples > 1) ? GL_TRUE : GL_FALSE,
		WGL_SAMPLES_ARB, (specification.samples > 1) ? specification.samples : 0,
		0
	};

	// Get the device context for the SDL window.
	dc = GetDC(reinterpret_cast<HWND>(window->Handle()));

	int pixelFormat;
	unsigned int formatCount;
	wglChoosePixelFormatARB(dc, pixelAttribs, nullptr, 1, &pixelFormat, &formatCount);

	if (!formatCount)
		return false;
	
	SetPixelFormat(dc, pixelFormat, &dummyPixelFormatDescriptor);

	int contextAttribs[] =
	{
		WGL_CONTEXT_MAJOR_VERSION_ARB, major,
		WGL_CONTEXT_MINOR_VERSION_ARB, minor,
		WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
		0
	};

	// Create OpenGL context		
	context = wglCreateContextAttribsARB(dc, nullptr, contextAttribs);

	// Failed to be created.
	if(context == nullptr)
		return false;

	// Unbind dummy context and delete.
	wglMakeCurrent(dc, nullptr);
	wglDeleteContext(dummyGLRC);
	ReleaseDC(dummyWND, dummyDC);
	DestroyWindow(dummyWND);

	// Bind main context and destroy dummy window.
	wglMakeCurrent(dc, context);

	// Handles vertical sync if supported.
	if (WGLEW_EXT_swap_control)
		wglSwapIntervalEXT(specification.vsync);

	std::cout << "Renderer: OpenGL " << major << "." << minor << std::endl;

	return true;

#elif GLX

#endif
}

bool Jade::Graphics::GLDevice::Release()
{
#ifdef WGL
	// Unbind OpenGL context.
	wglMakeCurrent(dc, nullptr);
	wglDeleteContext(context);
	ReleaseDC(reinterpret_cast<HWND>(window->Handle()), dc);

#elif GLX

#endif
	return context == nullptr ? true : false;
}

void Jade::Graphics::GLDevice::Clear(Math::Color color)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(color.GetRed(), color.GetGreen(), color.GetBlue(), color.GetAlpha());
}

void Jade::Graphics::GLDevice::Present()
{
#ifdef WGL
	SwapBuffers(dc);
#elif GLX

#endif
}

char* Jade::Graphics::GLDevice::DeviceInformation()
{
	return nullptr;
}
