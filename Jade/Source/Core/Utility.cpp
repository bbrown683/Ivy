
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

// Initialize our external headers here.
#define NK_IMPLEMENTATION
#include "nuklear/nuklear.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h" 
#define STB_IMAGE_RESIZE_IMPLEMENTATION 
#include "stb/stb_image_resize.h"
#define STB_TRUETYPE_IMPLEMENTATION
#include "stb/stb_truetype.h"

#include "Utility.h"

char* Jade::Core::Utility::StringToChar(std::string string)
{
	// Returns a reference to the first index in the vector which is a char.
	return &string[0u];
}

std::string Jade::Core::Utility::GetFilePath()
{
	return std::string();
}

std::wstring Jade::Core::Utility::StringToWString(std::string string)
{
	return std::wstring(string.begin(), string.end());
}
