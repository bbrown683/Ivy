#pragma once

#include "Core/Utility.h"

namespace System
{
	class Logfile
	{
	private:

	public:

		// Initializes our log manager.
		void Initialize();

		// 
		void Destroy();
		
		// 
		void Write(string filename);

	};
}
