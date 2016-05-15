#pragma once

#include "Math/Matrix.h"

namespace Jade
{
	namespace Math
	{
		struct Space
		{
			Matrix world;
			Matrix projection;
			Matrix view;
		};

		struct PerObject
		{
			Matrix world;
		};

		struct OnResize
		{
			Matrix projection;
		};

		struct NeverChanges
		{
			Matrix view;
		};
	}
}