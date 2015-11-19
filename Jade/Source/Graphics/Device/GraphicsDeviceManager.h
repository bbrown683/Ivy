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

#include "Graphics/Window/IWindow.h"
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

		public:
			
			// Some graphicsDevice information
			//int backBufferWidth = window->GetWidth();			// back buffer width.
			//int backBufferHeight = window->GetHeight();		// back buffer height.
			//int stencilBits = 8;								// amount of stencil bits.
			//int depthBits = 24;								// amount of depth bits.
			//int colorBits = 32;								// amount of color bits.
			//bool sampling = false;							// using sampling?
			//int samplesCount = 0;								// how many samples if using sampling?

			GraphicsDeviceManager() : graphicsDevice(nullptr), window(nullptr)  { }

			GraphicsDeviceManager(IWindow* window)
			{
				this->window = std::shared_ptr<IWindow>(window);
			}

			std::shared_ptr<IGraphicsDevice> RetrieveDevice() const
			{
				return graphicsDevice;
			}

			// Enumerates through the available devices and selects the best one available for rendering.
			bool SelectDevice();
		};
	}
}

