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

#include "Graphics/Blender/Blender.h"
#include "Graphics/Buffer/ConstantBuffer.h"
#include "Graphics/Buffer/VertexBuffer.h"
#include "Graphics/Device/Device.h"
#include "Graphics/Shader/Shader.h"
#include "Graphics/Texture/Texture.h"
#include "Math/Helper.h"

namespace Ivy
{
	namespace Graphics
	{
		class Sprite
		{
			Device device;
			Shader shader;
			Texture texture;
            Blender blender;

            bool blending;

			ConstantBuffer cBuffer;
			VertexBuffer vBuffer;

			Math::Matrix mRotation;
			Math::Matrix mScale;
			Math::Matrix mTranslation;

			Math::Vector3 vPosition;
			Math::Vector3 vRotation;
			Math::Vector3 vScale;

		public:

			Sprite(Device device, Shader shader)
			{				 
				this->device = device;
				this->shader = shader;
			
                blender = Blender(device);

				vBuffer = VertexBuffer(device, PrimitiveType::TriangleList);
				cBuffer = ConstantBuffer(device);

				// All quads when in triangular form have 6 vertices.
				// For a single sprite, these should be the positions and
				// texture coordinates.
				std::vector<Math::Vertex> vertices;

				// DirectX requires us to flip the texture coordinates.
				if (device.GetGraphicsAPI() == GraphicsAPI::DirectX)
				{
                    vertices.push_back({ Math::Vector4(0.0f, 1.0f, 0.0f), Math::Vector2(0.0f, 0.0f) });
                    vertices.push_back({ Math::Vector4(1.0f, 0.0f, 0.0f), Math::Vector2(1.0f, 1.0f) });
                    vertices.push_back({ Math::Vector4(0.0f, 0.0f, 0.0f), Math::Vector2(0.0f, 1.0f) });
                    vertices.push_back({ Math::Vector4(0.0f, 1.0f, 0.0f), Math::Vector2(0.0f, 0.0f) });
                    vertices.push_back({ Math::Vector4(1.0f, 1.0f, 0.0f), Math::Vector2(1.0f, 0.0f) });
                    vertices.push_back({ Math::Vector4(1.0f, 0.0f, 0.0f), Math::Vector2(1.0f, 1.0f) });
				}
				else
				{
					vertices.push_back({ Math::Vector4(0.0f, 1.0f, 0.0f), Math::Vector2(0.0f, 1.0f) });
					vertices.push_back({ Math::Vector4(1.0f, 0.0f, 0.0f), Math::Vector2(1.0f, 0.0f) });
					vertices.push_back({ Math::Vector4(0.0f, 0.0f, 0.0f), Math::Vector2(0.0f, 0.0f) });
					vertices.push_back({ Math::Vector4(0.0f, 1.0f, 0.0f), Math::Vector2(0.0f, 1.0f) });
					vertices.push_back({ Math::Vector4(1.0f, 1.0f, 0.0f), Math::Vector2(1.0f, 1.0f) });
					vertices.push_back({ Math::Vector4(1.0f, 0.0f, 0.0f), Math::Vector2(1.0f, 0.0f) });
				}

				// Create Vertex Buffer for sprite.
				vBuffer.SetVertices(vertices);
				vBuffer.Create();

				// Create world matrix for sprite.
				cBuffer.CreateWorldMatrix();
			}

			void Draw();
            void Blending(bool blending);
			bool Load(std::string filename);

			Math::Vector3 GetPosition();
			Math::Vector3 GetRotation();
			Math::Vector3 GetScale();

			void SetPosition(Math::Vector3 position);
			void SetRotation(Math::Vector3 rotation);
			void SetScale(Math::Vector3 scale);
		};
	}
}