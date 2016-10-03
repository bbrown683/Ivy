#include "System/Log.h"

void Ivy::System::Log::Write(std::string text)
{
// With debug we write to the console stream.
#ifdef _DEBUG
	std::cout << text << std::endl;
#else
// Otherwise we write to a file stream.
	File file(__TIMESTAMP__);
#endif
}
