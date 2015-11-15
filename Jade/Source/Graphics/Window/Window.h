#pragma once

#include "IWindow.h"
#include "System/Platform.h"

#include "Win32Window.h"

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
			void SetWidth(int value)
			{
				window->SetWidth(value);
			}

			// Returns the height of the window.
			int GetHeight()
			{
				return window->GetHeight();
			}

			// Sets the height of the window.
			void SetHeight(int value)
			{
				window->SetHeight(value);
			}

			Window(int width, int height, int x, int y, string title)
			{
				this->width = width;
				this->height = height;
				this->x = x;
				this->y = y;
				this->title = title;

				window = new Win32Window(width, height, x, y, title);
				window->InitWindow();
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

			~Window()
			{
				// Cleanup resources.
				delete window;
			}
		};
	}
}



