#pragma once

#include "Graphics/Model/Importer/MeshMaterial.h"
#include "Math/Color.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"

namespace Jade
{
	namespace Graphics
	{
		struct ModelMesh
		{
			// Vectors are very cache friendly, as all of its data
			// is stored contiguously. This is why we will be using
			// them instead of a standard list type.

			std::vector<Math::Vector3> positions;
			std::vector<Math::Color> colors;
			std::vector<Math::Vector2> uvs;
			std::vector<Math::Vector3> normals;
			std::vector<Math::Vector3> tangents;
			std::vector<Math::Vector3> bitangents;
			std::vector<std::string> textures;
			std::vector<MeshMaterial> materials;
		};
	}
}