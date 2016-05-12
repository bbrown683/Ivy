#pragma once

#include <Core/Utility.h>
#include <Graphics/Widget/Widget.h>

namespace Jade
{
	namespace Graphics
	{
		//! Represents a surface that can contain other sub-widgets such as buttons.
		class Canvas : public Widget
		{
		public:

			Math::Point GetPosition() override;
			void SetPosition(int x, int y) override;
			void Show() override;
			void Hide() override;
			void Draw() override;
		};
	}
}