#pragma once

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

#include "Graphics/Window/IWindow.h"

#include "SDL.h"
#include "SDL_syswm.h"
#include "Core/Utility.h"

namespace Jade
{
	namespace Graphics
	{
		class NativeWindow : public IWindow
		{
		private:

			SDL_Window* m_pWindow; // SDLs window object.
			SDL_SysWMinfo m_WindowInfo; // Contains information of our window.

			int width;
			int height;
			int x;
			int y;
			string title;
			bool fullscreen;

			bool open = false;
			bool disposed = false;
			bool hidden = false;
			bool maximized = false;
			bool minimized = false;
			bool active = false;

			bool InitWindow() override;
			bool PollWindowEvents() override;

		public:

			// IWindow overrides.

			int GetWidth() override;
			void SetWidth(int value) override;
			int GetHeight() override;
			void SetHeight(int value) override;
			int GetX() override;
			void SetX(int value) override;
			int GetY() override;
			void SetY(int value) override;
			string GetTitle() override;
			void SetTitle(string value) override;
			Math::Point GetPosition() override;
			void SetPosition(int x, int y) override;
			void Close() override;
			void* Handle() override;
			void Show() override;
			void Hide() override;
			void Restore() override;
			void Maximize() override;
			bool IsMinimized() override;
			void Minimize() override;
			bool IsMaximized() override;
			bool IsVisible() override;
			bool IsOpen() override;
			bool IsFullscreen() override;
			bool IsActive() override;
			SDL_Window* GetSDLWindow() override;

			NativeWindow(int width, int height, int x, int y, string title, bool fullscreen) : m_pWindow(nullptr)
			{
				this->width = width;
				this->height = height;
				this->x = x;
				this->y = y;
				this->title = title;
				this->fullscreen = fullscreen;
			}

			~NativeWindow()
			{
				// Ensure that we do not dispose SDL when it is unnecessary.
				if (!disposed)
				{
					Close();
				}
			}
		};
	}
}
