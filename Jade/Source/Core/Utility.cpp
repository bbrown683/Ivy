
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

#include "Utility.h"

#ifdef JADE_PLATFORM_WINDOWS
#include <windows.h>
#include <Shlwapi.h> // Requires linking of shlwapi.lib
#endif

std::string Jade::Core::Utility::GetExecutablePath()
{
#ifdef JADE_PLATFORM_WINDOWS
    char path[MAX_PATH];
    GetModuleFileNameA(GetModuleHandle(nullptr), path, sizeof path); // Returns path of executable.
    std::string filePath = RemoveFilenameFromPath(std::string(path));
    return filePath.append("\\");
#endif
}

std::string Jade::Core::Utility::RemoveFilenameFromPath(std::string path)
{
#ifdef JADE_PLATFORM_WINDOWS
    char* data = const_cast<char*>(path.data()); // Convert the string into a char array.
    PathRemoveFileSpecA(data);  // Removes the name.
    return std::string(data);
#endif
}

std::wstring Jade::Core::Utility::StringToWString(std::string string)
{
	return std::wstring(string.begin(), string.end());
}
