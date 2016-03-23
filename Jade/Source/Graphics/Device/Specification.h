#pragma once

namespace Jade
{
	namespace Graphics
	{
		// Provides further functionality for device creation.
		struct Specification
		{
			int backBufferWidth;	// Back buffer width.
			int backBufferHeight;	// Back buffer height.
			int stencilBits;		// Amount of stencil bits.
			int depthBits;			// Amount of depth bits.
			int colorBits;			// Amount of color bits.
			int samples;			// Number of samples.
			bool vsync;				// Vertical sync enabling.
		};
	};
}