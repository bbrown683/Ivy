#pragma once

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
					return PlatformID::Windows;
				#elif __APPLE__
					return PlatformID::MacOSX;
				#elif __linux__
					return PlatformID::Linux;
				// Unknown Operating System not supported by Jade.
				#else
					return PlatformID::Unknown;
				#endif // _WIN32
			}
		};
	}
}


