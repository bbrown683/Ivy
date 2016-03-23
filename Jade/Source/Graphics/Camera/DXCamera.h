#pragma once

#include "Core/Utility.h"
#include "Graphics/Camera/ICamera.h"
#include "Graphics/Camera/Scene.h"
#include "Graphics/Device/DXDevice.h"

namespace Jade
{
	namespace Graphics
	{
		class DXCamera : public ICamera
		{
		private:

			std::shared_ptr<DXDevice> device;
			std::shared_ptr<Scene> scene;

			Math::Matrix world;
			Math::Matrix view;
			Math::Matrix projection;

			float nearPlaneDistance, farPlaneDistance;

		public:

			DXCamera(float nearPlaneDistance, float farPlaneDistance, std::shared_ptr<DXDevice> device)
			{
				this->nearPlaneDistance = nearPlaneDistance;
				this->farPlaneDistance = farPlaneDistance;

				this->device = device;
			}

			void LookAt(Math::Vector3 position, Math::Vector3 target, Math::Vector3 direction) override;
		};
	}
}
