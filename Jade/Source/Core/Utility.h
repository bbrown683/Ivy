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

//==============================================
// Include some common headers.
//==============================================

// Platform define.
#include "System/Platform.h"

// I/O
#include <iostream>

// Strings.
#include <string>

// Common data structures.
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <queue>

// Multithreading.
#include <thread>

// Pointer handling
#include <memory>

// Asserting conditions.
#include <cassert>

// Exception system.
#include <exception>

#ifdef JADE_PLATFORM_WINDOWS
#include <Windows.h>
#include <Windowsx.h>
typedef HDC PlatformDisplay;
typedef HWND PlatformWindow;
#elif defined(JADE_PLATFORM_UNIX)
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysymdef.h>
#include <X11/XKBlib.h>
typedef Display* PlatformDisplay;
typedef Window PlatformWindow;
#endif

namespace Jade
{
	namespace Core
	{
		class Utility
		{

		public:

			static std::string GetExecutablePath();
            static std::string RemoveFilenameFromPath(std::string path);
			static std::wstring StringToWString(std::string string);
		};
	};
}