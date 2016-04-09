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

#include "Graphics/Device/Device.h"
#include "Graphics/Mesh/IMesh.h"
#include "Graphics/Mesh/DXMesh.h"
#include "Graphics/Mesh/GLMesh.h"
#include "Graphics/Texture/Texture.h"

namespace Jade
{
	namespace Graphics
	{
		class Mesh
		{
		private:

			Device device;
			std::vector<Math::Vertex> vertices;
			std::vector<unsigned int> indices;
			std::vector<Texture> textures;

			std::shared_ptr<IMesh> mesh;

		public:

			Mesh(Device device, std::vector<Math::Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
			{
				this->device = device;
				this->vertices = vertices;
				this->indices = indices;
				this->textures = textures;

				switch (device.GetGraphicsAPI())
				{
				case GraphicsAPI::DirectX:
					mesh = std::make_shared<DXMesh>(std::dynamic_pointer_cast<DXDevice>(device.GetIDevice()), vertices, indices, textures);
					break;
				case GraphicsAPI::OpenGL:
					// OpenGL uses a state machine so we dont need to pass a device.
					mesh = std::make_shared<GLMesh>(vertices, indices);
					break;
				case GraphicsAPI::Vulkan:
					mesh = nullptr;
					break;
				}
			}


			Mesh(int null, Device device, std::vector<Math::Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
			{
				this->device = device;
				this->vertices = vertices;
				this->indices = indices;
				this->textures = textures;
			}

			void Initialize();

			void Draw()	const
			{
				mesh->Draw();
			}

			std::vector<Math::Vertex> GetVertices()	const
			{
				return vertices;
			}

			std::vector<unsigned int> GetIndices() const
			{
				return indices;
			}

			std::vector<Texture> GetTextures() const
			{
				return textures;
			}
		};
	}
}
