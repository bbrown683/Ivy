#pragma once

#include "Core/Utility.h"

namespace Jade
{
	namespace Graphics
	{
		struct MeshMaterial
		{
			std::string name;
			std::vector<std::string> textures;
			bool culling;
			bool smoothness;
			float opacity;
		};
	}
}