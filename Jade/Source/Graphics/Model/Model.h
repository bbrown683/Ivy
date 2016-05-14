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

#include "assimp/Importer.hpp"
#include "assimp/Scene.h"
#include "assimp/postprocess.h"

#include "Core/Utility.h"
#include "Graphics/Mesh/Mesh.h"
#include <Graphics/Mesh/TestMesh.h>

namespace Jade
{
	namespace Graphics
	{
		class Model
		{
		private:

			// Needed the device for DirectX to create our mesh.
			Device device;
			Shader shader;

			// Mesh(s) used to draw our shape.
			//std::vector<Mesh> meshes;
			std::vector<TestMesh> meshes;

			Math::Vector3 position;

		public:

			Model(Device device, Shader shader)
			{
				this->device = device;
				this->shader = shader;
			}

			void Load(std::string filename);
			void Draw();
			//std::vector<Mesh> GetMeshes() const;
			std::vector<TestMesh> GetMeshes() const;

			Math::Vector3 GetPosition() const;
			void SetPosition(Math::Vector3 position);
		};
	}
}
