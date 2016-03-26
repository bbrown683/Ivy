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

#include <Core/Input.h>
#include <Core/Time.h>
#include <Core/Utility.h>
#include <Math/Point.h>

namespace Jade
{
	namespace System
	{
		// Contains some methods that we can implement across multiple platforms to perform a task on a window.
		struct IWindow
		{
			virtual int GetWidth() = 0;
			virtual void SetWidth(int value) = 0;
			virtual int GetHeight() = 0;
			virtual void SetHeight(int value) = 0;
			virtual float GetAspectRatio() = 0;
			virtual int GetX() = 0;
			virtual void SetX(int value) = 0;
			virtual int GetY() = 0;
			virtual void SetY(int value) = 0;
			virtual std::string GetTitle() = 0;
			virtual void SetTitle(std::string value) = 0;
			virtual Math::Point GetPosition() = 0;
			virtual void SetPosition(int x, int y) = 0;
			virtual void SetIcon(std::string filename) = 0;
			virtual bool PollWindowEvents() = 0;
			virtual void Close() = 0;
			virtual void* Handle() = 0;
			virtual bool InitWindow() = 0;
			virtual void Show() = 0;
			virtual void Hide() = 0;
			virtual void Restore() = 0;
			virtual void Maximize() = 0;
			virtual bool IsMinimized() = 0;
			virtual void Minimize() = 0;
			virtual bool IsMaximized() = 0;
			virtual bool IsVisible() = 0;
			virtual bool IsOpen() = 0;
			virtual bool IsFullscreen() = 0;
			virtual bool IsActive() = 0;
			virtual Core::Time GetTime() = 0;
			virtual Core::Input GetInput() = 0;
		};
	}
}
