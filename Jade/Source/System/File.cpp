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

#include "File.h"
#include <Core/Exception/FileNotFoundException.h>

std::string Jade::System::File::Read()
{
	std::ifstream t(filename);
	
	std::string str((std::istreambuf_iterator<char>(t)),
		std::istreambuf_iterator<char>());

	return str;

	/*
	file.open(filename.c_str(), std::fstream::in | std::fstream::binary);
	
	if (file.is_open())
	{
		std::stringstream stream;
		stream << file.rdbuf();
		file.close();

		std::string data = stream.str();

		return stream.str();
	}
	*/
	
	//throw Core::FileNotFoundException(filename);
}

void Jade::System::File::Write(std::string text)
{
	file.open(filename.c_str(), std::fstream::out | std::fstream::binary);

	if(file.is_open())
	{

	}
}
