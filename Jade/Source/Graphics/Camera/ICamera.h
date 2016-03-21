#pragma once

#include "Math/Vector3.h"

namespace Jade
{
	namespace Graphics
	{
		struct ICamera
		{
			virtual void LookAt(Math::Vector3 position, Math::Vector3 target, Math::Vector3 direction) = 0;
		};
	}
}