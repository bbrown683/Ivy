#include "Utility.h"

std::string Jade::Core::Utility::GetFilePath()
{
	return std::string();
}

std::wstring Jade::Core::Utility::StringToWString(std::string string)
{
	return std::wstring(string.begin(), string.end());
}
