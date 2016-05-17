#pragma once

#include "Graphics/Device/DXDevice.h"
#include "Graphics/Sprite/ISprite.h"
#include "Graphics/Texture/Texture.h"
#include "Math/Vector2.h"

#ifdef JADE_PLATFORM_WINDOWS
namespace Jade
{
	namespace Graphics
	{
		class DXSprite : public ISprite
		{
			std::shared_ptr<DXDevice> device;

			Math::Vector2 position;
			Math::Vector2 scale;
			float rotation;

		public:

			DXSprite(std::shared_ptr<DXDevice> device)
			{
				this->device = device;
			}

			void Draw(Texture texture, std::string filename, int x, int y, float scale) override;
		};
	}
}
#endif