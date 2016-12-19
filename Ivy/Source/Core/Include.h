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

// Platform defines and inclusions.
#if defined(WIN32) || defined(_WIN32)
#	define IVY_PLATFORM_WINDOWS
#	ifndef WIN32_LEAN_AND_MEAN
#		define WIN32_LEAN_AND_MEAN
#	endif
#	include <Windows.h>
#	include <Windowsx.h>
typedef HDC PlatformDisplay;
typedef HWND PlatformWindow;
#elif defined(__unix__)
#	define IVY_PLATFORM_UNIX
#	include <X11/Xlib.h>
#	include <X11/Xutil.h>
#   include <X11/keysymdef.h>
#   include <X11/XKBlib.h>
typedef Display* PlatformDisplay;
typedef Window PlatformWindow;
#else
#	error Unsupported System.
#endif

// Checking for Unicode define.
#if defined(UNICODE) || defined(_UNICODE)
#	define IVY_UNICODE
#endif

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <queue>
#include <thread>
#include <memory>
#include <cassert>
#include <exception>