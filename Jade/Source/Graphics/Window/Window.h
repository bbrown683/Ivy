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

#include "IWindow.h"
#include "System/Platform.h"

#include "Win32Window.h"
#include "X11Window.h"

namespace Jade
{
	namespace Graphics
	{
		// Multi-platform window implementation.
		class Window
		{
			int width;
			int height;
			int x;
			int y;
			string title;
			bool fullscreen;

			// All of our windows use this interface for their general implementations 
			// to create interoperability for multiple operating systems.
			IWindow* window;

		public:

			// Returns a boolean determining if the window is still active.
			bool IsOpen()
			{
				return window->IsOpen();
			}

			// Returns the width of the window.
			int GetWidth()
			{
				return window->GetWidth();
			}

			// Sets the width of the window.
			void SetWidth(int width)
			{
				window->SetWidth(width);
			}

			// Returns the height of the window.
			int GetHeight()
			{
				return window->GetHeight();
			}

			// Sets the height of the window.
			void SetHeight(int height)
			{
				window->SetHeight(height);
			}

			// Returns a boolean determining if the window is in fullscreen mode.
			bool isFullscreen()
			{
				window->IsFullscreen();
			}

			Window(int width, int height, int x, int y, string title, bool fullscreen)
			{
				this->width = width;
				this->height = height;
				this->x = x;
				this->y = y;
				this->title = title;
				this->fullscreen;

				// Factory implementation to create the correct window at runtime.
				CreateNativeWindow();
			}

			bool PollEvents(Event* e)
			{
				return window->WindowEvent(e);
			}

			void SwapBuffers()
			{
				window->SwapWindowBuffers();
			}

			// Closes the window and exits the application.
			void Close()
			{
				window->Close();
				this->~Window();
			}

		private:

			void CreateNativeWindow()
			{
				switch (Jade::System::Platform::GetPlatformID())
				{
				case System::Platform::PlatformID::Windows:
					window = new Win32Window(width, height, x, y, title, fullscreen);
					break;
				case System::Platform::PlatformID::MacOSX:
				case System::Platform::PlatformID::Linux:
					window = new X11Window(width, height, x, y, title, fullscreen);
					break;
				case System::Platform::PlatformID::Unknown:
					window = nullptr;
					break;
				}

				// If our window exists, initialize it.
				if (window)
				{
					window->InitWindow();
				}	
			}

			~Window()
			{
				// Cleanup resources.
				delete window;
			}
		};
	}
}



