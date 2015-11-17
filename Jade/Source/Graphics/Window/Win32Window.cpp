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

#include "Win32Window.h"

// Must be static as these will be used within our WndProc function.
static HWND hWnd;
static HINSTANCE hInstance = GetModuleHandle(NULL);
static bool open;
static std::queue<Jade::Graphics::Event> events;

// Creates the window.
bool Jade::Graphics::Win32Window::InitWindow()
{
	WNDCLASSEX wcex;

	wcex.cbSize			= sizeof(WNDCLASSEX);
	wcex.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, IDI_APPLICATION);
	wcex.hCursor		= LoadCursor(hInstance, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcex.lpszMenuName	= nullptr;
	wcex.lpszClassName	= "Jade";
	wcex.hIconSm		= LoadIcon(hInstance, IDI_APPLICATION);

	if (RegisterClassEx(&wcex))
	{
		hWnd = CreateWindowEx(WS_EX_CLIENTEDGE, "Jade", title.c_str(), WS_OVERLAPPEDWINDOW, x, y, width, height, nullptr, nullptr, hInstance, nullptr);

		hdc = GetDC(hWnd);

		if (!hWnd)
		{
			return false;
		}
		
		context = new GLContext(this);
		context->CreateContext();

		ShowWindow(hWnd, SW_SHOW);
		UpdateWindow(hWnd);

		return open = true;
	}

	return false;
}

// Windows 32 message loop which adds each event to a queue that is maintained by the message procedure.
bool Jade::Graphics::Win32Window::WindowEvent(Event* e)
{
	MSG msg;

	e = new Event();

	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	if (!events.empty())
	{
		// Pop events off the queue.
		&events.front();
		events.pop();
		
		// Delete or there will be a nasty memory leak 
		// each time we check for events.
		delete e;

		return true;
	}

	delete e;

	return false;
}

// Returns a boolean determining if the window is currently open.
bool Jade::Graphics::Win32Window::IsOpen()
{
	return open;
}

// Swaps buffers on the window.
bool Jade::Graphics::Win32Window::SwapWindowBuffers()
{
	if (SwapBuffers(hdc))
		return true;
	
	return false;
}

// Forcefully closes the window and cleans up.
void Jade::Graphics::Win32Window::Close()
{
	CloseWindow(hWnd);
	DestroyWindow(hWnd);
	UnregisterClass("Jade", hInstance);
	open = false;
}

// Returns the pointer of our window object which is used to create a rendering context.
void * Jade::Graphics::Win32Window::Handle()
{
	return hWnd;
}

// This function subscribes to specific events and performs various tasks on them.
LRESULT Jade::Graphics::Win32Window::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	Win32Window window(0, 0, 0, 0, "", false);

	Event event;
	event.SetEventType(Event::EventType::Unknown);

	switch (message)
	{
		case WM_CREATE:
			break;
		case WM_CLOSE:		
			CloseWindow(hWnd);
			DestroyWindow(hWnd);
			UnregisterClass("Jade", hInstance);
			open = false;
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}

	if (event.GetEventType() != Event::EventType::Unknown)
		events.push(event);

	return 0;
}
