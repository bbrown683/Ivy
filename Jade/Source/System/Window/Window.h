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

#include "System/Window/IWindow.h"
#include "System/Window/NativeWindow.h"

namespace Jade
{
	namespace System
	{
		// Multi-platform window implementation.
		class Window
		{
		private:

			int width;
			int height;
			int x;
			int y;
			string title;
			bool fullscreen;

			// All of our windows use this interface for their general implementations 
			// to create interoperability for multiple operating systems.
			std::shared_ptr<IWindow> window;

		public:

			// Returns a boolean determining if the window is still active.
			bool IsOpen() const
			{
				return window->IsOpen();
			}

			// Returns the width of the window.
			int GetWidth() const
			{
				return window->GetWidth();
			}

			// Sets the width of the window.
			void SetWidth(int width) const
			{
				window->SetWidth(width);
			}

			// Returns the height of the window.
			int GetHeight() const
			{
				return window->GetHeight();
			}

			// Sets the height of the window.
			void SetHeight(int height) const
			{
				window->SetHeight(height);
			}

			// Retrieves the handle of the window.
			void* Handle() const
			{
				return window->Handle();
			}

			// Returns the title of the window.
			string GetTitle() const
			{
				return window->GetTitle();
			}

			// Sets the title of the window.
			void SetTitle(string title) const
			{
				window->SetTitle(title);
			}

			// Returns a boolean determining if the window is in fullscreen mode.
			bool IsFullscreen() const
			{
				return window->IsFullscreen();
			}

			// Returns a boolean determining if the window has focus.
			bool IsActive() const
			{
				return window->IsActive();
			}

			// Returns a boolean determining if a key was pressed.
			bool IsKeyDown(Key key) const
			{
				return window->IsKeyDown(key);
			}

			// Returns a boolean determining if a key was not pressed.
			bool IsKeyUp(Key key) const
			{
				return window->IsKeyUp(key);
			}

			std::shared_ptr<IWindow> GetWindowInterface() const
			{
				return window;
			}

			Window(int width, int height, int x, int y, string title, bool fullscreen)
			{
				this->width = width;
				this->height = height;
				this->x = x;
				this->y = y;
				this->title = title;
				this->fullscreen = fullscreen;

				window = std::make_shared<NativeWindow>(width, height, x, y, title, fullscreen);

				// If our window exists, initialize it.
				if (window)
					window->InitWindow();
			}

			~Window()
			{
				Close();
			}

			bool PollEvents() const
			{
				return window->PollWindowEvents();
			}

			// Closes the window and exits the application.
			void Close() const
			{
				window->Close();
			}

			float GetDeltaTime() const
			{
				return window->GetDeltaTime();
			}
		};
	}
}



