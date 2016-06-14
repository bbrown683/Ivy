#pragma once

#include "Math/Point.h"

namespace Jade
{
	namespace Graphics
	{
		// Abstract class for Widget implementation.
		class Widget
		{
		public:

			virtual Math::Point<float> GetPosition() = 0;
			virtual void SetPosition(int x, int y) = 0;
			virtual void Show() = 0;
			virtual void Hide() = 0;
			//! Submits the widget information to the current device for rendering.
			virtual void Draw() = 0;
		};
	}
}
