#pragma once

#include <vector>

#include "assimp/Importer.hpp"
#include "assimp/Scene.h"
#include "assimp/postprocess.h"

#include "Core/Utility.h"
#include "Math/Vertex.h"
#include "Graphics/Buffer/Buffer.h"

namespace Jade
{
	namespace Graphics
	{
		class Model
		{
		private:

			// Buffer(s) used to draw our shape.
			std::vector<Buffer> buffer;

			// Each model will have an array of vertices.
			Math::Vertex* vertex;

		public:

			Model(string filename)
			{
				vertex = LoadModel(filename);
			}

			Math::Vertex* LoadModel(string filename);
			void Draw();
		};
	}
}
