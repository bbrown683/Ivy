#pragma once

#include <Core/Utility.h>
#include <Graphics/Device/Device.h>

namespace Jade
{
	namespace Graphics
	{
		class TextureFactory
		{
		public:

			template<typename T, typename... Params>
			static std::shared_ptr<T> Generate(Device device, Params... params)
			{
				switch(device.GetGraphicsAPI())
				{
					case GraphicsAPI::Default: return nullptr;
					case GraphicsAPI::DirectX: return std::make_shared<DXTexture>(std::dynamic_pointer_cast<DXDevice>(device.GetIDevice()), params...);
					case GraphicsAPI::OpenGL: return nullptr;
					case GraphicsAPI::Vulkan: return nullptr;
					default: return nullptr;
				}
			}
		};
	}
}