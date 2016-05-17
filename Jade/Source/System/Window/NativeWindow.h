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

#include "SDL2/SDL.h"
#include "SDL2/SDL_syswm.h"

#include <Core/Utility.h>
#include <Input/Input.h>
#include <System/Window/IWindow.h>
#include <System/Timer.h>

namespace Jade
{
	namespace System
	{
		class NativeWindow : public IWindow
		{
		private:

			SDL_Window* m_pWindow; // SDLs window object.
			SDL_SysWMinfo m_WindowInfo; // Contains information of our window.

			// Window parameters.
			int width;
			int height;
			int x;
			int y;
			std::string title;
			bool fullscreen;

			// Window checks.
			bool open = false;
			bool disposed = false;
			bool hidden = false;
			bool maximized = false;
			bool minimized = false;
			bool active = false;

			// Input
			Input::Input input;

			// Keeps track of our time per frames.
			Timer timer;
			int startTime = 0;

			// Test keys.
			bool escape = false;

			bool Create() override;
			bool PollWindowEvents() override;

			// Helper class for reducing code clutter.
			Input::Key ConvertKeycode(SDL_Keycode keycode);

		public:

			// IWindow overrides.

			int GetWidth() override;
			void SetWidth(int value) override;
			int GetHeight() override;
			void SetHeight(int value) override;
			float GetAspectRatio() override;
			int GetX() override;
			void SetX(int value) override;
			int GetY() override;
			void SetY(int value) override;
			std::string GetTitle() override;
			void SetTitle(std::string value) override;
			Math::Point GetPosition() override;
			void SetPosition(int x, int y) override;
			void SetIcon(std::string filename) override;
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
			System::Timer GetTimer() override;
			Input::Input GetInput() override;

			NativeWindow(int width, int height, int x, int y, std::string title, bool fullscreen) : m_pWindow(nullptr)
			{
				this->width = width;
				this->height = height;
				this->x = x;
				this->y = y;
				this->title = title;
				this->fullscreen = fullscreen;

				if (!NativeWindow::Create())
					NativeWindow::Close();
			}

			~NativeWindow()
			{
				NativeWindow::Close();

				std::cout << "Window closing..." << std::endl;
			}
		};
	}
}
