#include "Script.h"

void Jade::Graphics::Script::Execute(std::string filename)
{ 
	luaL_dofile(lua, filename.c_str());
}
