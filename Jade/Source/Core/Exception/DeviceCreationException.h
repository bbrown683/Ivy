#pragma once

namespace Jade
{
	namespace Core
	{
		class DeviceCreationException : public std::exception
		{
		public:

			DeviceCreationException() { }

			const char* what() const throw() override
			{
				return "Jade::Core::DeviceCreationException : Failed to create rendering device.";
			}
		};
	}
}