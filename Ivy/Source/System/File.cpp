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
#include "Core/Exception/FileNotFoundException.h"

std::string Ivy::System::File::Read()
{
	// Uses the C API for reading files.

	// MSVC wants use to use the secure alternative.
#ifdef _MSC_VER
	fopen_s(&file, filename.c_str(), "rb");
#else
	file = fopen(filename.c_str(), "rb");
#endif

	if (!file)
		throw Core::FileNotFoundException(filename);

	// Get the size of the file so we can preallocate 
	// the correct amount for the vector.
	long pos = ftell(file);
	fseek(file, 0, SEEK_END);
	long size = ftell(file);
	fseek(file, pos, SEEK_SET);

	std::vector<char> buffer(size + 1);
	fread(buffer.data(), size, 1, file);
	buffer[size] = 0;
	fclose(file);
	
	// Return string after assignment.
	return content = std::string(buffer.begin(), buffer.end());
}

void Ivy::System::File::Write(std::string text)
{

}
