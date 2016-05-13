#pragma once

#include "Core/Utility.h"
#include "Graphics/Texture/Texture.h"

namespace Jade
{
	namespace Graphics
	{
		struct ISprite
		{
			virtual void Draw(Texture texture, std::string filename, int x, int y, float scale) = 0;
		};
	}
}