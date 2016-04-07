#pragma once

namespace Jade
{
	namespace Graphics
	{
		// Contains the data of our character
		struct Glyph
		{
			unsigned short code;  // unicode value
			unsigned short index; // freetype glyph index
			unsigned char width;  // width of the glyph in pixels
			unsigned char height; // height of the glyph in pixels
			unsigned char advance; // number of pixels to advance on x axis
			char bearingX; // x offset of top-left corner from x axis
			char bearingY; // y offset of top-left corner from y axis
			unsigned char textureX; // x pixel coord of the bitmap's bottom-left corner
			unsigned short textureY;// y pixel coord of the bitmap's bottom-left corner
		};
	}
}