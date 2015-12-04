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

#include "GLWindow.h"

bool Jade::Graphics::GLWindow::PollWindowEvents()
{
	// Basic event loop. Events that involves rendering 
	// such as Resizing is done by the graphics device itself.

	SDL_Event e;

	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_QUIT:
			open = false;
			break;
		case SDL_WINDOWEVENT_HIDDEN:
			active = false;
			break;
		case SDL_WINDOWEVENT_SHOWN:
			active = true;
			break;
		}
	}

	return true;
}

void Jade::Graphics::GLWindow::Close()
{
	SDL_DestroyWindow(m_pWindow);
	SDL_Quit();

	open = false;
}

void* Jade::Graphics::GLWindow::Handle()
{
	// With OpenGL being cross platform, we have to ensure 
	// that the Window handle works for Jade's supported platforms.
#if defined(SDL_VIDEO_DRIVER_WINDOWS)
	return reinterpret_cast<void*>(m_WindowInfo.info.win.window); // Cast HWND to void*
#elif defined(SDL_VIDEO_DRIVER_X11)
	return reinterpret_cast<void*>(m_WindowInfo.info.x11.window); // Cast Window to void* 
#endif
}

int Jade::Graphics::GLWindow::GetWidth()
{
	return width;
}

void Jade::Graphics::GLWindow::SetWidth(int value)
{
	SDL_SetWindowSize(m_pWindow, value, height);
}

int Jade::Graphics::GLWindow::GetHeight()
{
	return height;
}

void Jade::Graphics::GLWindow::SetHeight(int value)
{
	SDL_SetWindowSize(m_pWindow, width, value);
}

int Jade::Graphics::GLWindow::GetX()
{
	return x;
}

void Jade::Graphics::GLWindow::SetX(int value)
{
	SDL_SetWindowPosition(m_pWindow, value, x);
}

int Jade::Graphics::GLWindow::GetY()
{
	return y;
}

void Jade::Graphics::GLWindow::SetY(int value)
{
	SDL_SetWindowPosition(m_pWindow, x, value);
}

string Jade::Graphics::GLWindow::GetTitle()
{
	return title;
}

void Jade::Graphics::GLWindow::SetTitle(string value)
{
	SDL_SetWindowTitle(m_pWindow, value.c_str());
}

Jade::Math::Point Jade::Graphics::GLWindow::GetPosition()
{
	return Math::Point(static_cast<float>(x), static_cast<float>(y));
}

void Jade::Graphics::GLWindow::SetPosition(int x, int y)
{
	SDL_SetWindowPosition(m_pWindow, x, y);
}

bool Jade::Graphics::GLWindow::InitWindow()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		// Cleanup resources.
		Close();

		disposed = true;
	}
	else
	{
		// Necessary for setting up an OpenGL window.
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 5);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		m_pWindow = SDL_CreateWindow(title.c_str(), x, y, width, height, SDL_WINDOW_OPENGL);

		if (m_pWindow)
		{
			if (fullscreen)
			{
				SDL_SetWindowFullscreen(m_pWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
			}

			// Capture window info.
			SDL_GetVersion(&m_WindowInfo.version);
			SDL_GetWindowWMInfo(m_pWindow, &m_WindowInfo);

			return open = true;
		}
	}

	return false;
}

void Jade::Graphics::GLWindow::Show()
{
	SDL_ShowWindow(m_pWindow);
	hidden = false;
}

void Jade::Graphics::GLWindow::Hide()
{
	SDL_HideWindow(m_pWindow);
	hidden = true;
}

void Jade::Graphics::GLWindow::Restore()
{
	SDL_RestoreWindow(m_pWindow);

	if (maximized)
		maximized = false;

	if (minimized)
		minimized = false;
}

void Jade::Graphics::GLWindow::Maximize()
{
	SDL_MaximizeWindow(m_pWindow);
	maximized = true;
}

bool Jade::Graphics::GLWindow::IsMaximized()
{
	return maximized;
}

void Jade::Graphics::GLWindow::Minimize()
{
	SDL_MinimizeWindow(m_pWindow);
	minimized = true;
}

bool Jade::Graphics::GLWindow::IsMinimized()
{
	return minimized;
}

bool Jade::Graphics::GLWindow::IsVisible()
{
	return !hidden;
}

bool Jade::Graphics::GLWindow::IsOpen()
{
	return open;
}

bool Jade::Graphics::GLWindow::IsFullscreen()
{
	return fullscreen;
}

bool Jade::Graphics::GLWindow::IsActive()
{
	return active;
}
