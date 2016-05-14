#pragma once

#include "Core/Utility.h"
#include "Graphics/Model/Importer/ModelProperties.h"

namespace Jade
{
	namespace Graphics
	{
		/*! \brief Abstract class for implementing various importers. */
		class Importer
		{
			std::string filename;
			
		public:

			Importer(std::string filename)
			{
				this->filename = filename;
			}

			virtual ModelProperties Parse() = 0;
		};
	}
}