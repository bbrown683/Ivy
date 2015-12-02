#pragma once

/*
The MIT License (MIT)

Copyright (c) 2015 Ben Brown

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "Core/Utility.h"

#include "Graphics/Window/Window.h"
#include "Graphics/Device/IGraphicsDevice.h"
#include "DXGraphicsDevice.h"
#include "GLGraphicsDevice.h"

namespace Jade
{
	namespace Graphics
	{
		class GraphicsDeviceManager
		{
		private:

			std::shared_ptr<IGraphicsDevice> graphicsDevice;	// Do not allow to be set, but can be retrieved.
			std::shared_ptr<IWindow> window;	// Do not allow to be set or retrieved.

			int backBufferWidth;	// back buffer width.
			int backBufferHeight;	// back buffer height.
			int stencilBits;		// amount of stencil bits.
			int depthBits;			// amount of depth bits.
			int colorBits;			// amount of color bits.
			bool sampling;			// using sampling?
			int samples;			// how many samples if using sampling?
			bool vsync;				// enable vertical sync?

		public:						

			// Note: Do not use this constructor as everything is set to null.
			GraphicsDeviceManager() : graphicsDevice(nullptr), window(nullptr), backBufferWidth(0), backBufferHeight(0), 
				stencilBits(0), depthBits(0), colorBits(0), sampling(false), samples(0), vsync(false) { }

			
			GraphicsDeviceManager(Window* window) : backBufferWidth(window->GetWidth()), backBufferHeight(window->GetHeight()),
				stencilBits(24), depthBits(8), colorBits(32), sampling(false), samples(1), vsync(false)
			{
				this->window = window->Interface(); // Retrieve the interface object.

				SelectDevice();
			}

			GraphicsDeviceManager(Window* window, int backBufferWidth, int backBufferHeight, int stencilBits, 
				int depthBits, int colorBits, bool sampling, int samples, bool vsync)
			{
				this->window = window->Interface();	// Retrieve the interface object.
				this->backBufferWidth = backBufferWidth;
				this->backBufferHeight = backBufferHeight;
				this->stencilBits = stencilBits;
				this->depthBits = depthBits;
				this->colorBits = colorBits;
				this->sampling = sampling;
				this->samples = samples;
				this->vsync = vsync;

				SelectDevice();
			}

			// Returns the GraphicsDevice that is ready to draw.
			std::shared_ptr<IGraphicsDevice> GetGraphicsDevice() const
			{
				return graphicsDevice;
			}

			// Enumerates through the available devices and selects the best one available for rendering.
			bool SelectDevice();
		};
	}
}

