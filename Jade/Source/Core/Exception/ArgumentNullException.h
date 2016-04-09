#pragma once

#include <Core/Utility.h>

#include <sstream>

namespace Jade
{
	namespace Core
	{
		class ArgumentNullException : public std::exception
		{
			std::string parameter;
			std::stringstream message;

		public:

			ArgumentNullException()
			{
				message << "Jade::Core::ArgumentNullException : Value cannot be null.";
			}

			// Passes the parameter which caused the exception.
			ArgumentNullException(std::string parameter)
			{
				this->parameter = parameter;

				message << "Jade::Core::ArgumentNullException : " << parameter << " cannot be null.";
			}

			// Passes the file and line number of where the exception was thrown along with the parameter which caused it.
			ArgumentNullException(std::string parameter, std::string filename, int line)
			{
				std::cout << filename << ", " << line << std::endl;

				message << "Jade::Core::ArgumentNullException : Exception was thrown at line " << line << " in " << filename << ". " << parameter << " cannot be null.";
			}

			const char* what() const throw() override
			{
				return "Jade::Core::ArgumentNullException : Value cannot be null.";
			}

			std::string GetParameter()
			{
				return parameter;
			}
		};
	}
}