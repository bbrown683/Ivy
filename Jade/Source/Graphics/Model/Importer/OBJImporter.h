#pragma once

#include "Graphics/Model/Importer/Importer.h"

namespace Jade
{
	namespace Graphics
	{
		class OBJImporter : public Importer
		{
			std::string filename;

		public:

			OBJImporter(std::string filename) : Importer(filename)
			{ }

			ModelProperties Parse() override;
		};
	}
}