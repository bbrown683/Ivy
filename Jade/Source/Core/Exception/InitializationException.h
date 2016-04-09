#pragma once

#include <Core/Utility.h>

namespace Jade
{
	namespace Core
	{
		class InitializationException : public std::exception
		{
		private:

			std::string message;

		public:

			InitializationException(std::string message)
			{
				this->message = message;
			}

			const char* what() const throw() override
			{
				return message.c_str();
			}
		};
	}
}