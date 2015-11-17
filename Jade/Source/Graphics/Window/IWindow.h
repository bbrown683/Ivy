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

#include "Event.h"
#include "Math/Point.h"

// Contains some methods that we can implement across multiple platforms to perform a task on a window.
struct IWindow
{	
	virtual bool IsOpen() = 0;
	virtual bool IsFullscreen() = 0;
	virtual bool WindowEvent(Jade::Graphics::Event* e) = 0;
	virtual bool SwapWindowBuffers() = 0;
	virtual void Close() = 0;
	virtual void* Handle() = 0;
	virtual bool InitWindow() = 0;
	virtual int GetWidth() = 0;
	virtual void SetWidth(int value) = 0;
	virtual int GetHeight() = 0;
	virtual void SetHeight(int value) = 0;
	virtual int GetX() = 0;
	virtual void SetX(int value) = 0;
	virtual int GetY() = 0;
	virtual void SetY(int value) = 0;
	virtual Jade::Math::Point GetPosition() = 0;
	virtual void SetPosition(int x, int y) = 0;
};