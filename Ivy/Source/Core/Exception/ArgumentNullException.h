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

#include <sstream>

#include "Core/Include.h"

namespace Ivy
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
				message << "Ivy::Core::ArgumentNullException : Value cannot be null.";
			}

			// Passes the parameter which caused the exception.
			ArgumentNullException(std::string parameter)
			{
				this->parameter = parameter;

				message << "Ivy::Core::ArgumentNullException : " << parameter << " cannot be null.";
			}

			// Passes the file and line number of where the exception was thrown along with the parameter which caused it.
			ArgumentNullException(std::string parameter, std::string filename, int line)
			{
				std::cout << filename << ", " << line << std::endl;

				message << "Ivy::Core::ArgumentNullException : Exception was thrown at line " << line << " in " << filename << ". " << parameter << " cannot be null.";
			}

			const char* what() const throw() override
			{
				return "Ivy::Core::ArgumentNullException : Value cannot be null.";
			}

			std::string GetParameter()
			{
				return parameter;
			}
		};
	}
}