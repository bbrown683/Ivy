#pragma once

#include "Math/Matrix.h"

namespace Jade
{
	namespace Math
	{
		struct Space
		{
			Matrix world;
			Matrix view;
			Matrix projection;
		};
	}
}