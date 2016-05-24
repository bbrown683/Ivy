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

#include "System/Window/NativeWindow.h"

bool Jade::System::NativeWindow::PollWindowEvents()
{
	// Compute elapsed time.
	int currentTime = SDL_GetTicks();
	if (startTime == 0)
		startTime = currentTime;
	timer.SetElapsedTime(static_cast<float>(currentTime - startTime) / 1000.0f);

#if !defined(_DEBUG) && !defined(DEBUG)
	// Anti-debugger check every render frame
	// if not in debug configuration.
	if (IsDebuggerPresent())
		Close();
#endif

	// Basic event loop. Events that involves rendering 
	// such as Resizing is handled by the graphics device itself.
	SDL_Event e;

	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		// Close application.
		case SDL_QUIT:
			Close();
			break;
		// Key press.
		case SDL_KEYDOWN:
			input.keyboard.SetKeyState(ConvertKeycode(e.key.keysym.sym), Input::InputState::Pressed);
			break;
		// Key release.
		case SDL_KEYUP:
			input.keyboard.SetKeyState(ConvertKeycode(e.key.keysym.sym), Input::InputState::Released);
			break;
		}
	}

	return true;
}

Jade::Input::Key Jade::System::NativeWindow::ConvertKeycode(SDL_Keycode keycode)
{
	switch(keycode)
	{
	case SDLK_0:
		return Input::Key::Digit0;
	case SDLK_1:
		return Input::Key::Digit1;
	case SDLK_2:
		return Input::Key::Digit2;
	case SDLK_3:
		return Input::Key::Digit3;
	case SDLK_4:
		return Input::Key::Digit4;
	case SDLK_5:
		return Input::Key::Digit5;
	case SDLK_6:
		return Input::Key::Digit6;
	case SDLK_7:
		return Input::Key::Digit7;
	case SDLK_8:
		return Input::Key::Digit8;
	case SDLK_9:
		return Input::Key::Digit9;
	case SDLK_KP_0:
		return Input::Key::NumberPad0;
	case SDLK_KP_1:
		return Input::Key::NumberPad1;
	case SDLK_KP_2:
		return Input::Key::NumberPad2;
	case SDLK_KP_3:
		return Input::Key::NumberPad3;
	case SDLK_KP_4:
		return Input::Key::NumberPad4;
	case SDLK_KP_5:				
		return Input::Key::NumberPad5;
	case SDLK_KP_6:
		return Input::Key::NumberPad6;
	case SDLK_KP_7:
		return Input::Key::NumberPad7;
	case SDLK_KP_8:
		return Input::Key::NumberPad8;
	case SDLK_KP_9:
		return Input::Key::NumberPad9;
	case SDLK_F1:
		return Input::Key::F1;
	case SDLK_F2:
		return Input::Key::F2;
	case SDLK_F3:
		return Input::Key::F3;
	case SDLK_F4:
		return Input::Key::F4;
	case SDLK_F5:
		return Input::Key::F5;
	case SDLK_F6:
		return Input::Key::F6;
	case SDLK_F7:
		return Input::Key::F7;
	case SDLK_F8:
		return Input::Key::F8;
	case SDLK_F9:
		return Input::Key::F9;
	case SDLK_F10:
		return Input::Key::F10;
	case SDLK_F11:
		return Input::Key::F11;
	case SDLK_F12:
		return Input::Key::F12;
	case SDLK_a:
		return Input::Key::A;
	case SDLK_b:
		return Input::Key::B;
	case SDLK_c:
		return Input::Key::C;
	case SDLK_d:
		return Input::Key::D;
	case SDLK_e:
		return Input::Key::E;
	case SDLK_f:
		return Input::Key::F;
	case SDLK_g:
		return Input::Key::G;
	case SDLK_h:
		return Input::Key::H;
	case SDLK_i:
		return Input::Key::I;
	case SDLK_j:
		return Input::Key::J;
	case SDLK_k:
		return Input::Key::K;
	case SDLK_l:
		return Input::Key::L;
	case SDLK_m:
		return Input::Key::M;
	case SDLK_n:
		return Input::Key::N;
	case SDLK_o:
		return Input::Key::O;
	case SDLK_p:
		return Input::Key::P;
	case SDLK_q:
		return Input::Key::Q;
	case SDLK_r:
		return Input::Key::R;
	case SDLK_s:
		return Input::Key::S;
	case SDLK_t:
		return Input::Key::T;
	case SDLK_u:
		return Input::Key::U;
	case SDLK_v:
		return Input::Key::V;
	case SDLK_w:
		return Input::Key::W;
	case SDLK_x:
		return Input::Key::X;
	case SDLK_y:
		return Input::Key::Y;
	case SDLK_z:
		return Input::Key::Z;
	case SDLK_LALT:
	case SDLK_RALT:
		return Input::Key::Alt;
	case SDLK_BACKSPACE:
		return Input::Key::Backspace;
	case SDLK_CAPSLOCK:
		return Input::Key::CapsLock;
	case SDLK_LCTRL:
	case SDLK_RCTRL:
		return Input::Key::Control;
	case SDLK_DELETE:
		return Input::Key::Delete;
	case SDLK_END:
		return Input::Key::End;
	case SDLK_RETURN:
		return Input::Key::Enter;
	case SDLK_ESCAPE:
		return Input::Key::Escape;
	case SDLK_HOME:
		return Input::Key::Home;
	case SDLK_INSERT:
		return Input::Key::Insert;
	case SDLK_PAGEUP:
		return Input::Key::PageUp;
	case SDLK_PAGEDOWN:
		return Input::Key::PageDown;
	case SDLK_LSHIFT:
	case SDLK_RSHIFT:
		return Input::Key::Shift;
	case SDLK_SPACE:
		return Input::Key::Space;
	case SDLK_TAB:
		return Input::Key::Tab;
	case SDLK_DOWN:
		return Input::Key::Down;
	case SDLK_LEFT:
		return Input::Key::Left;
	case SDLK_RIGHT:
		return Input::Key::Right;
	case SDLK_UP:
		return Input::Key::Up;
	case SDLK_PLUS:
		return Input::Key::Plus;
	case SDLK_PERIOD:
		return Input::Key::Peroid;
	case SDLK_SLASH:
		return Input::Key::Slash;
	case SDLK_ASTERISK:
		return Input::Key::Asterisk;
	case SDLK_MINUS:
		return Input::Key::Dash;
	case SDLK_LEFTBRACKET:
		return Input::Key::LeftBracket;
	case SDLK_RIGHTBRACKET:
		return Input::Key::RightBracket;																															 
	case SDLK_LEFTPAREN:
		return Input::Key::LeftParenthesis;
	case SDLK_RIGHTPAREN:
		return Input::Key::RightParenthesis;
	case SDLK_QUOTE:
		return Input::Key::Apostrophe;
	case SDLK_QUOTEDBL:
		return Input::Key::Quote;
	default:
		return Input::Key::Unknown;
	}
}

void Jade::System::NativeWindow::SetIcon(std::string filename)
{
	// Deprecating this due to attempting to reduce library clutter.
#ifdef USE_FREEIMAGE
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
#endif
	/*
	// Load image without grabbing irrelevant information.
	int width, height, bpp;
	unsigned char* bits = stbi_load(filename.c_str(), &width, &height, &bpp, STBI_rgb_alpha);

	if (bits)
	{	
		// We need to resize the image.
		unsigned char* resizedBits = static_cast<unsigned char*>(malloc(32 * 32 * 4));
		if (stbir_resize_uint8(bits, width, height, 0, resizedBits, 32, 32, 0, 4))
		{
			// Free the old image.
			stbi_image_free(bits);

			// Load the bits into the buffer and send it to a surface.
			SDL_RWops* buffer = SDL_RWFromMem(resizedBits, sizeof resizedBits);
			SDL_Surface* icon = SDL_LoadBMP_RW(buffer, 1);

			// Close the buffer and memory since it is no longer needed.
			SDL_RWclose(buffer);

			// MakeActive the surface as an icon.
			SDL_SetWindowIcon(m_pWindow, icon);

			// Release the surface object after setting icon.
			SDL_FreeSurface(icon);
		}

		// Release the resized image.
		free(resizedBits);
	}
	*/
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

bool Jade::System::NativeWindow::Create()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		// Cleanup resources.
		Close();
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

Jade::System::Timer Jade::System::NativeWindow::GetTimer()
{
	return timer;
}

Jade::Input::Input Jade::System::NativeWindow::GetInput()
{
	return input;
}
