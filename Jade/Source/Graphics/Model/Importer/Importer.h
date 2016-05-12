#pragma once

#include "Core/Utility.h"
#include "Graphics/Model/Importer/ModelType.h"

namespace Jade
{
	namespace Graphics
	{
		class Importer
		{
			ModelType type;

			Importer(std::string filename)
			{
				
			}

			ModelType GetModelTypeFromFilename(std::string filename)
			{
				
			}
		};
	}
}