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

#include "Graphics/Buffer/ConstantBuffer.h"

namespace Jade
{
	namespace Graphics
	{
		class Camera
		{
			Device device;
			ConstantBuffer cBuffer;

			Math::Vector3 position;
			Math::Vector3 target;

		public:

            Camera() { }

            Camera(Device device, Math::Vector3 position, Math::Vector3 target)
			{
				this->device = device;
				this->position = position;
				this->target = target;

				// Create View and Projection.
				cBuffer = ConstantBuffer(device);
				cBuffer.CreateProjectionMatrix();
				cBuffer.CreateViewMatrix();
				
				cBuffer.SetViewMatrix(Math::Matrix::CreateLookAtLH(position, target, Math::Vector3::Up).Transpose());
                // Note: On resizing it will still use the old aspect ratio. Need to create a workaround for this to update it.
				cBuffer.SetProjectionMatrix(Math::Matrix::CreatePerspectiveViewLH(
					Math::Math::PiOverTwo, static_cast<float>(device.GetWindow().GetWidth()),
					static_cast<float>(device.GetWindow().GetHeight()), 0.1f, 1000.0f).Transpose());

				cBuffer.UpdateMatrices();
			}

			Math::Vector3 GetCameraPosition() const;
			void SetCameraPosition(Math::Vector3 position);
			Math::Vector3 GetTargetPosition() const;
			void SetTargetPosition(Math::Vector3 position);
		};
	}
}
