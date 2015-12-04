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

#include "DXWindow.h"

bool Jade::Graphics::DXWindow::PollWindowEvents()
{
	// Basic event loop. Events that involves rendering 
	// such as Resizing is done by the graphics device itself.

	SDL_Event e;

	while(SDL_PollEvent(&e))
	{
		switch(e.type)
		{
		case SDL_QUIT:
			open = false;
			break;
		case SDL_WINDOW_MOUSE_FOCUS:
			if (SDL_GetMouseFocus())
				active = true;
			else
				active = false;
			break;
		}
	}

	return true;
}

void Jade::Graphics::DXWindow::Close()
{
	SDL_DestroyWindow(m_pWindow);
	SDL_Quit();

	open = false;
}

void* Jade::Graphics::DXWindow::Handle()
{
	return reinterpret_cast<void*>(windowInfo.info.win.window); // Cast HWND to void*
}

int Jade::Graphics::DXWindow::GetWidth()
{
	return width;
}

void Jade::Graphics::DXWindow::SetWidth(int value)
{
	SDL_SetWindowSize(m_pWindow, value, height);
}

int Jade::Graphics::DXWindow::GetHeight()
{
	return height;
}

void Jade::Graphics::DXWindow::SetHeight(int value)
{
	SDL_SetWindowSize(m_pWindow, width, value);
}

int Jade::Graphics::DXWindow::GetX()
{
	return x;
}

void Jade::Graphics::DXWindow::SetX(int value)
{
	SDL_SetWindowPosition(m_pWindow, value, x);
}

int Jade::Graphics::DXWindow::GetY()
{
	return y;
}

void Jade::Graphics::DXWindow::SetY(int value)
{
	SDL_SetWindowPosition(m_pWindow, x, value);
}

string Jade::Graphics::DXWindow::GetTitle()
{
	return title;
}

void Jade::Graphics::DXWindow::SetTitle(string value)
{
	SDL_SetWindowTitle(m_pWindow, value.c_str());
}

Jade::Math::Point Jade::Graphics::DXWindow::GetPosition()
{
	return Math::Point(static_cast<float>(x), static_cast<float>(y));
}

void Jade::Graphics::DXWindow::SetPosition(int x, int y)
{
	SDL_SetWindowPosition(m_pWindow, x, y);
}

bool Jade::Graphics::DXWindow::InitWindow()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		// Cleanup resources.
		Close();

		disposed = true;
	}
	else
	{
		m_pWindow = SDL_CreateWindow(title.c_str(), x, y, width, height, SDL_WINDOW_SHOWN);

		if (m_pWindow)
		{
			if (fullscreen)
			{
				SDL_SetWindowFullscreen(m_pWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
			}

			// Capture window info so we can grab window handle.
			SDL_GetVersion(&windowInfo.version);
			SDL_GetWindowWMInfo(m_pWindow, &windowInfo);

			active = true;

			return open = true;
		}
	}
	
	return false;
}

void Jade::Graphics::DXWindow::Show()
{
	SDL_ShowWindow(m_pWindow);
	hidden = false;
}

void Jade::Graphics::DXWindow::Hide()
{
	SDL_HideWindow(m_pWindow);
	hidden = true;
}

void Jade::Graphics::DXWindow::Restore()
{
	SDL_RestoreWindow(m_pWindow);

	if (maximized)
		maximized = false;

	if (minimized)
		minimized = false;
}

void Jade::Graphics::DXWindow::Maximize()
{
	SDL_MaximizeWindow(m_pWindow);
	maximized = true;
}

bool Jade::Graphics::DXWindow::IsMaximized()
{
	return maximized;
}

void Jade::Graphics::DXWindow::Minimize()
{
	SDL_MinimizeWindow(m_pWindow);
	minimized = true;
}

bool Jade::Graphics::DXWindow::IsMinimized()
{
	return minimized;
}

bool Jade::Graphics::DXWindow::IsVisible()
{
	return !hidden;
}

bool Jade::Graphics::DXWindow::IsOpen()
{
	return open;
}

bool Jade::Graphics::DXWindow::IsFullscreen()
{
	return fullscreen;
}

bool Jade::Graphics::DXWindow::IsActive()
{
	return active;
}
