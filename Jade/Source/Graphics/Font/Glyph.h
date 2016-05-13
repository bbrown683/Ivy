#pragma once

namespace Jade
{
	namespace Graphics
	{
		// Information that is specific to a single character in a font face.
		struct Glyph
		{
			char character;
			int width, height;
			int xOffset, yOffset;
			int advance;
			float u, v;
		};
	}
}