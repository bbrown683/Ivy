#include "Utility.h"

std::wstring Jade::Core::Utility::StringToWString(std::string string)
{
	return std::wstring(string.begin(), string.end());
}
