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
#include "FreeImage/FreeImage.h"

bool Jade::System::NativeWindow::PollWindowEvents()
{
	// Compute delta time.
	// Delta time computations.
	int currentTime = SDL_GetTicks();
	if (startTime == 0)
		startTime = currentTime;
	timer.SetElapsedTime(static_cast<float>(currentTime - startTime) / 1000.0f);

	// Basic event loop. Events that involves rendering 
	// such as Resizing is handled by the graphics device itself.
	SDL_Event e;

	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		// Close application.
		case SDL_QUIT:
			open = false;
			break;
		// Key press.
		case SDL_KEYDOWN:
			input.keyboard.SetKeyState(ConvertKeycode(e.key.keysym.sym), Core::InputState::Pressed);
			break;
		// Key release.
		case SDL_KEYUP:
			input.keyboard.SetKeyState(ConvertKeycode(e.key.keysym.sym), Core::InputState::Released);
			break;
		}
	}

	return true;
}

Jade::Core::Key Jade::System::NativeWindow::ConvertKeycode(SDL_Keycode keycode)
{
	switch(keycode)
	{
	case SDLK_0:
		return Core::Key::Digit0;
	case SDLK_1:
		return Core::Key::Digit1;
	case SDLK_2:
		return Core::Key::Digit2;
	case SDLK_3:
		return Core::Key::Digit3;
	case SDLK_4:
		return Core::Key::Digit4;
	case SDLK_5:
		return Core::Key::Digit5;
	case SDLK_6:
		return Core::Key::Digit6;
	case SDLK_7:
		return Core::Key::Digit7;
	case SDLK_8:
		return Core::Key::Digit8;
	case SDLK_9:
		return Core::Key::Digit9;
	case SDLK_KP_0:
		return Core::Key::NumberPad0;
	case SDLK_KP_1:
		return Core::Key::NumberPad1;
	case SDLK_KP_2:
		return Core::Key::NumberPad2;
	case SDLK_KP_3:
		return Core::Key::NumberPad3;
	case SDLK_KP_4:
		return Core::Key::NumberPad4;
	case SDLK_KP_5:				
		return Core::Key::NumberPad5;
	case SDLK_KP_6:
		return Core::Key::NumberPad6;
	case SDLK_KP_7:
		return Core::Key::NumberPad7;
	case SDLK_KP_8:
		return Core::Key::NumberPad8;
	case SDLK_KP_9:
		return Core::Key::NumberPad9;
	case SDLK_F1:
		return Core::Key::F1;
	case SDLK_F2:
		return Core::Key::F2;
	case SDLK_F3:
		return Core::Key::F3;
	case SDLK_F4:
		return Core::Key::F4;
	case SDLK_F5:
		return Core::Key::F5;
	case SDLK_F6:
		return Core::Key::F6;
	case SDLK_F7:
		return Core::Key::F7;
	case SDLK_F8:
		return Core::Key::F8;
	case SDLK_F9:
		return Core::Key::F9;
	case SDLK_F10:
		return Core::Key::F10;
	case SDLK_F11:
		return Core::Key::F11;
	case SDLK_F12:
		return Core::Key::F12;
	case SDLK_a:
		return Core::Key::A;
	case SDLK_b:
		return Core::Key::B;
	case SDLK_c:
		return Core::Key::C;
	case SDLK_d:
		return Core::Key::D;
	case SDLK_e:
		return Core::Key::E;
	case SDLK_f:
		return Core::Key::F;
	case SDLK_g:
		return Core::Key::G;
	case SDLK_h:
		return Core::Key::H;
	case SDLK_i:
		return Core::Key::I;
	case SDLK_j:
		return Core::Key::J;
	case SDLK_k:
		return Core::Key::K;
	case SDLK_l:
		return Core::Key::L;
	case SDLK_m:
		return Core::Key::M;
	case SDLK_n:
		return Core::Key::N;
	case SDLK_o:
		return Core::Key::O;
	case SDLK_p:
		return Core::Key::P;
	case SDLK_q:
		return Core::Key::Q;
	case SDLK_r:
		return Core::Key::R;
	case SDLK_s:
		return Core::Key::S;
	case SDLK_t:
		return Core::Key::T;
	case SDLK_u:
		return Core::Key::U;
	case SDLK_v:
		return Core::Key::V;
	case SDLK_w:
		return Core::Key::W;
	case SDLK_x:
		return Core::Key::X;
	case SDLK_y:
		return Core::Key::Y;
	case SDLK_z:
		return Core::Key::Z;
	case SDLK_LALT:
	case SDLK_RALT:
		return Core::Key::Alt;
	case SDLK_BACKSPACE:
		return Core::Key::Backspace;
	case SDLK_CAPSLOCK:
		return Core::Key::CapsLock;
	case SDLK_LCTRL:
	case SDLK_RCTRL:
		return Core::Key::Control;
	case SDLK_DELETE:
		return Core::Key::Delete;
	case SDLK_END:
		return Core::Key::End;
	case SDLK_RETURN:
		return Core::Key::Enter;
	case SDLK_ESCAPE:
		return Core::Key::Escape;
	case SDLK_HOME:
		return Core::Key::Home;
	case SDLK_INSERT:
		return Core::Key::Insert;
	case SDLK_PAGEUP:
		return Core::Key::PageUp;
	case SDLK_PAGEDOWN:
		return Core::Key::PageDown;
	case SDLK_LSHIFT:
	case SDLK_RSHIFT:
		return Core::Key::Shift;
	case SDLK_SPACE:
		return Core::Key::Space;
	case SDLK_TAB:
		return Core::Key::Tab;
	case SDLK_DOWN:
		return Core::Key::Down;
	case SDLK_LEFT:
		return Core::Key::Left;
	case SDLK_RIGHT:
		return Core::Key::Right;
	case SDLK_UP:
		return Core::Key::Up;
	case SDLK_PLUS:
		return Core::Key::Plus;
	case SDLK_PERIOD:
		return Core::Key::Peroid;
	case SDLK_SLASH:
		return Core::Key::Slash;
	case SDLK_ASTERISK:
		return Core::Key::Asterisk;
	case SDLK_MINUS:
		return Core::Key::Dash;
	case SDLK_LEFTBRACKET:
		return Core::Key::LeftBracket;
	case SDLK_RIGHTBRACKET:
		return Core::Key::RightBracket;
	case SDLK_LEFTPAREN:
		return Core::Key::LeftParenthesis;
	case SDLK_RIGHTPAREN:
		return Core::Key::RightParenthesis;
	case SDLK_QUOTE:
		return Core::Key::Apostrophe;
	case SDLK_QUOTEDBL:
		return Core::Key::Quote;
	default:
		return Core::Key::Unknown;
	}
}

void Jade::System::NativeWindow::SetIcon(std::string filename)
{
	// SDL is picky about icons, therefore we will use
	// FreeImage to load the icon and retrieve the bits 
	// from the image and pass it to SDL.

	// Get format of file so FreeImage knows how to load it into a bitmap.
	FREE_IMAGE_FORMAT format = FreeImage_GetFileType(filename.c_str(), 0);
	
	if(format != FIF_UNKNOWN && FreeImage_FIFSupportsReading(format))
	{
		// Load and resize image.
		FIBITMAP* bitmap = FreeImage_Load(format, filename.c_str());
		bitmap = FreeImage_Rescale(bitmap, 32, 32, FILTER_BOX);

		// Convert to a 24 bit image.
		// 8 bits per color channel.
		FIBITMAP* src = FreeImage_ConvertTo24Bits(bitmap);
		FreeImage_Unload(bitmap);

		// Create and open memory stream.
		FIMEMORY* hMemory;
		hMemory = FreeImage_OpenMemory();

		// Save to memory and gather size.
		FreeImage_SaveToMemory(FIF_BMP, src, hMemory, 0);
		FreeImage_Unload(src);

		// Acquire the bitmap from memory then close the stream.
		unsigned char* bits = nullptr;
		unsigned long size = 0;
		FreeImage_AcquireMemory(hMemory, &bits, &size);

		// Load the bits into the buffer and send it to a surface.
		SDL_RWops* buffer = SDL_RWFromMem(bits, size);
		SDL_Surface* icon = SDL_LoadBMP_RW(buffer, 1);
		
		// Close the buffer and memory since it is no longer needed.
		SDL_RWclose(buffer);
		FreeImage_CloseMemory(hMemory);

		// Set the surface as an icon.
		SDL_SetWindowIcon(m_pWindow, icon);

		// Release the surface object after setting icon.
		SDL_FreeSurface(icon);
	}
}

void Jade::System::NativeWindow::Close()
{	
	open = false;
	
	SDL_DestroyWindow(m_pWindow);
	SDL_Quit();
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

float Jade::System::NativeWindow::GetAspectRatio()
{
	return static_cast<float>(GetWidth()) / static_cast<float>(GetHeight());
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

std::string Jade::System::NativeWindow::GetTitle()
{
	return title;
}

void Jade::System::NativeWindow::SetTitle(std::string value)
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
		m_pWindow = SDL_CreateWindow(title.c_str(), x, y, width, height, SDL_WINDOW_SHOWN);
		
		if (m_pWindow)
		{
			if (fullscreen)
			{
				SDL_SetWindowFullscreen(m_pWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
			}

			// Capture window info so we can grab the window handle.
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

Jade::Core::Time Jade::System::NativeWindow::GetTime()
{
	return timer;
}

Jade::Core::Input Jade::System::NativeWindow::GetInput()
{
	return input;
}
