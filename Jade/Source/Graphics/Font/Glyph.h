#pragma once

namespace Jade
{
	namespace Graphics
	{
		// Information that is specific to a single character in a font face.
		struct Glyph
		{
			int width;
			int height;
			int xOffset;
			int yOffset;
		};
	}
}