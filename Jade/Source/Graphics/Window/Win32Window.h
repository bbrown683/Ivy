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

#pragma once

// We only need specific headers from this.
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <queue>

#include "IWindow.h"
#include "Event.h"

#include "Core/Utility.h"
#include "Graphics/Device/GraphicsDeviceManager.h"

#include "Math/Point.h"

namespace Jade
{
	namespace Graphics
	{
		class Win32Window : public IWindow
		{
		private:

			int width;
			int height;
			int x;
			int y;
			string title;
			bool fullscreen;

			HDC hdc;

			std::shared_ptr<GraphicsDeviceManager> graphicsDevice;

		public:

			// All set methods are currently placeholders.

			int GetWidth() override
			{
				return width;
			}

			void SetWidth(int width) override
			{
				this->width = width;
			}

			int GetHeight() override
			{
				return height;
			}

			void SetHeight(int height) override
			{
				this->height = height;
			}

			int GetX() override
			{
				return x;
			}

			void SetX(int x) override
			{
				this->x = x;
			}

			int GetY() override
			{
				return y;
			}

			void SetY(int y) override
			{
				this->y = y;
			}

			Math::Point GetPosition() override
			{
				return Math::Point(0, 0);
			}

			void SetPosition(int x, int y) override
			{
				this->x = x;
				this->y = y;
			}

			bool IsFullscreen() override
			{
				return fullscreen;
			}

			Win32Window(int width, int height, int x, int y, string title, bool fullscreen)
			{
				this->width = width;
				this->height = height;
				this->x = x;
				this->y = y;
				this->title = title;
			}

			bool IsOpen() override;
			bool SwapWindowBuffers() override;
			void Close() override;
			void* Handle() override;

		private:

			bool InitWindow() override;
			bool WindowEvent(std::shared_ptr<Event> e) override;
			static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
		};
	}
}