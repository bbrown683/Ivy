#pragma once

/*
The MIT License (MIT)

Copyright (c) 2015 Ben Brown

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

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