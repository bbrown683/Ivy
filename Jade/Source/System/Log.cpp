#include "System/Log.h"

void Jade::System::Log::Write(std::string text)
{
// With debug we write to the console stream.
#ifdef _DEBUG
	std::cout << text << std::endl;
#else
// Otherwise we write to a filestream.
	File file(__TIMESTAMP__);
	
#endif
}
