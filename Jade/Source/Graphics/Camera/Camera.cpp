#include "Camera.h"

std::shared_ptr<Jade::Graphics::ICamera> Jade::Graphics::Camera::CreateCamera() const
{
	switch (device->GetGraphicsAPI())
	{
		case GraphicsAPI::DirectX:
		{
			return std::make_shared<DXCamera>(0.1f, 100.0f, std::dynamic_pointer_cast<DXDevice>(device->GetIDevice()));
		}
		case GraphicsAPI::OpenGL:
		{
			// OpenGL uses a state machine so we dont need to pass a device.
			break;
		}
		case GraphicsAPI::Vulkan:
		{
			break;
		}
	}

	return nullptr;
}
