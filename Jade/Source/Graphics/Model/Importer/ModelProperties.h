#pragma once

#include "Graphics/Model/Importer/ModelMesh.h"
#include "Graphics/Model/Importer/ModelType.h"


namespace Jade
{
	namespace Graphics
	{
		struct ModelProperties
		{
			std::string filename;
			ModelType type;
			std::vector<ModelMesh> meshes;
		};
	}
}
