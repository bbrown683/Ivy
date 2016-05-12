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

namespace Jade
{
	namespace System
	{
		// Class for platform detection. 
		class Platform
		{
		public:

			enum class PlatformID : int
			{
				Unknown = 0, // Unsupported platform.
				Windows = 1, // All general Windows distributions.
				MacOSX = 2, // All general Mac distributions.
				Linux = 3, // All general Linux (not Unix) distributions.
			};

			static PlatformID GetPlatformID()
			{
				// _WIN32 is defined for both 32bit and 64bit compilations on Windows machines.
				#ifdef _WIN32
					#define JADE_PLATFORM_WINDOWS
					return PlatformID::Windows;
				#elif __APPLE__
					#define JADE_PLATFORM_APPLE
					return PlatformID::MacOSX;
				#elif __linux__
					#define JADE_PLATFORM_LINUX
					return PlatformID::Linux;
				// Unknown Operating System not supported by Jade.
				#else
					return PlatformID::Unknown;
				#endif // _WIN32
			}
		};
	}
}


