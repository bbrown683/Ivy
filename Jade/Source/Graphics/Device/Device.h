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
#include "Graphics/Device/IDevice.h"

namespace Jade
{
	namespace Graphics
	{
		class Device
		{
		private:

			std::shared_ptr<IDevice> device;
			std::shared_ptr<IWindow> window;

			// Planned to be functional in future iterations, but for now we will not mess with these.
			
			int backBufferWidth;	// Back buffer width.
			int backBufferHeight;	// Back buffer height.
			int stencilBits;		// Amount of stencil bits.
			int depthBits;			// Amount of depth bits.
			int colorBits;			// Amount of color bits.
			bool sampling;			// Using sampling?
			int samples;			// How many samples if using sampling?
			bool vsync;				// Enable vertical sync?

			enum class ColorBits : int
			{
				R8G8B8A8, // 32 bits of color, 8 for each component.
			};

			// Enumerates through the available devices and selects the best one available for rendering.
			std::shared_ptr<IDevice> SelectDevice();

		public:						

			// Note: Do not use this constructor as everything is set to null.
			Device() : device(nullptr), window(nullptr), backBufferWidth(0), backBufferHeight(0), 
				stencilBits(0), depthBits(0), colorBits(0), sampling(false), samples(0), vsync(false) { }

			// Default device constructor.
			Device(std::shared_ptr<Window> window) : backBufferWidth(window->GetWidth()), backBufferHeight(window->GetHeight()),
				stencilBits(24), depthBits(8), colorBits(32), sampling(false), samples(1), vsync(false)
			{
				this->window = window->Instance(); // Retrieve the interface object.

				device = SelectDevice();
			}

			Device(std::shared_ptr<Window> window, int backBufferWidth, int backBufferHeight, int stencilBits,
				int depthBits, int colorBits, bool sampling, int samples, bool vsync)
			{
				this->window = window->Instance();	// Retrieve the interface object.
				this->backBufferWidth = backBufferWidth;
				this->backBufferHeight = backBufferHeight;
				this->stencilBits = stencilBits;
				this->depthBits = depthBits;
				this->colorBits = colorBits;
				this->sampling = sampling;
				this->samples = samples;
				this->vsync = vsync;

				device = SelectDevice();
			}

			// Clears the buffer to the specified color.
			void Clear(Math::Color color) const
			{
				device->Clear(color);
			}

			// Presents the back buffer to the front for display.
			void Present() const
			{
				device->Present();
			}
		};
	}
}

