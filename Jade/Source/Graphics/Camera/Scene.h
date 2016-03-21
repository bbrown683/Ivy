#pragma once

#include "Math/Matrix.h"

namespace Jade
{
	namespace Graphics
	{
		struct Scene
		{
			Math::Matrix world;
			Math::Matrix view;
			Math::Matrix projection;
		};
	}
}