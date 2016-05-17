#pragma once

#include "Math/Matrix.h"

namespace Jade
{
	namespace Math
	{
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