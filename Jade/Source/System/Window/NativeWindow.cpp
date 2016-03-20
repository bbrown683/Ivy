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

#include <iostream>

#include "System/Window/NativeWindow.h"
#include "System/Platform.h"

bool Jade::System::NativeWindow::PollWindowEvents()
{
	// Basic event loop. Events that involves rendering 
	// such as Resizing is done by the graphics device itself.
	SDL_Event e;

	//int startTime = SDL_GetTicks();

	while (SDL_PollEvent(&e))
	{
		// Delta time computations.
		//float loopedTime = static_cast<float>(SDL_GetTicks());
		//timer.SetDeltaTime(loopedTime - startTime);
		//startTime = loopedTime;

		switch (e.type)
		{
		case SDL_QUIT:
			open = false;
			break;
		}
	}

	return true;
}

void Jade::System::NativeWindow::Close()
{
	SDL_DestroyWindow(m_pWindow);
	SDL_Quit();

	open = false;
}

void* Jade::System::NativeWindow::Handle()
{
	// With OpenGL being cross platform, we have to ensure 
	// that the Window handle works for Jade's supported platforms.
#if defined(SDL_VIDEO_DRIVER_WINDOWS)
	return reinterpret_cast<void*>(m_WindowInfo.info.win.window); // Cast HWND to void*
#elif defined(SDL_VIDEO_DRIVER_X11)
	return reinterpret_cast<void*>(m_WindowInfo.info.x11.window); // Cast Window to void* 
#elif defined (SDL_VIDEO_DRIVER_COCOA)
	return reinterpret_cast<void*>(m_WindowInfo.info.cocoa.window); // Cast Window to void*
#endif
}

int Jade::System::NativeWindow::GetWidth()
{
	return width;
}

void Jade::System::NativeWindow::SetWidth(int value)
{
	SDL_SetWindowSize(m_pWindow, value, height);
	this->width = value;
}

int Jade::System::NativeWindow::GetHeight()
{
	return height;
}

void Jade::System::NativeWindow::SetHeight(int value)
{
	SDL_SetWindowSize(m_pWindow, width, value);
	this->height = value;
}

int Jade::System::NativeWindow::GetX()
{
	return x;
}

void Jade::System::NativeWindow::SetX(int value)
{
	SDL_SetWindowPosition(m_pWindow, value, x);
	this->x = value;
}

int Jade::System::NativeWindow::GetY()
{
	return y;
}

void Jade::System::NativeWindow::SetY(int value)
{
	SDL_SetWindowPosition(m_pWindow, x, value);
	this->y = value;
}

string Jade::System::NativeWindow::GetTitle()
{
	return title;
}

void Jade::System::NativeWindow::SetTitle(string value)
{
	SDL_SetWindowTitle(m_pWindow, value.c_str());
	this->title = value;
}

Jade::Math::Point Jade::System::NativeWindow::GetPosition()
{
	return Math::Point(static_cast<float>(x), static_cast<float>(y));
}

void Jade::System::NativeWindow::SetPosition(int x, int y)
{
	SDL_SetWindowPosition(m_pWindow, x, y);
	this->x = x;
	this->y = y;
}

bool Jade::System::NativeWindow::InitWindow()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		// Cleanup resources.
		Close();

		disposed = true;
	}
	else
	{
		// Windows will be using DirectX by default due to built in support.
		if(System::Platform::GetPlatformID() == System::Platform::PlatformID::Windows)
		{
			m_pWindow = SDL_CreateWindow(title.c_str(), x, y, width, height, SDL_WINDOW_SHOWN);
		}
		else
		{
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
			SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, true);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

			m_pWindow = SDL_CreateWindow(title.c_str(), x, y, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
		}

		if (m_pWindow)
		{
			if (fullscreen)
			{
				SDL_SetWindowFullscreen(m_pWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
			}

			// Capture window info so we can grab window handle.
			SDL_GetVersion(&m_WindowInfo.version);
			SDL_GetWindowWMInfo(m_pWindow, &m_WindowInfo);

			active = true;

			return open = true;
		}
	}

	return false;
}

void Jade::System::NativeWindow::Show()
{
	SDL_ShowWindow(m_pWindow);
	hidden = false;
}

void Jade::System::NativeWindow::Hide()
{
	SDL_HideWindow(m_pWindow);
	hidden = true;
}

void Jade::System::NativeWindow::Restore()
{
	SDL_RestoreWindow(m_pWindow);

	if (maximized)
		maximized = false;

	if (minimized)
		minimized = false;
}

void Jade::System::NativeWindow::Maximize()
{
	SDL_MaximizeWindow(m_pWindow);
	maximized = true;
}

bool Jade::System::NativeWindow::IsMaximized()
{
	return maximized;
}

void Jade::System::NativeWindow::Minimize()
{
	SDL_MinimizeWindow(m_pWindow);
	minimized = true;
}

bool Jade::System::NativeWindow::IsMinimized()
{
	return minimized;
}

bool Jade::System::NativeWindow::IsVisible()
{
	return !hidden;
}

bool Jade::System::NativeWindow::IsOpen()
{
	return open;
}

bool Jade::System::NativeWindow::IsFullscreen()
{
	return fullscreen;
}

bool Jade::System::NativeWindow::IsActive()
{
	return active;
}

float Jade::System::NativeWindow::GetDeltaTime()
{
	return timer.GetDeltaTime();
}

SDL_Window* Jade::System::NativeWindow::GetSDLWindow()
{
	return m_pWindow;
}
