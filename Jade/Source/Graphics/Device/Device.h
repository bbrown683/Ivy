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
#include "Graphics/Device/GraphicsAPI.h"
#include "Graphics/Device/IDevice.h"
#include "Graphics/Device/DXDevice.h"
#include "Graphics/Device/GLDevice.h"
#include "Graphics/Device/Specification.h"
#include "System/Window/Window.h"

namespace Jade
{
	namespace Graphics
	{
		class Device
		{
		private:

			System::Window window;
			GraphicsAPI api;
			Specification specification;

			// Enumerates through the available devices and selects the best one available for rendering.
			std::shared_ptr<IDevice> device;
			std::shared_ptr<IDevice> Initialize();

		public:						

			// Note: Do not use this constructor as everything is set to null.
			Device() : device(nullptr) {} 

			// Default device constructor.

			Device(System::Window window, GraphicsAPI api)
			{
				this->window = window;
				this->api = api;

				// Fill some default values.
				specification.backBufferHeight = window.GetHeight();
				specification.backBufferWidth = window.GetWidth();
				specification.colorBits = 32;
				specification.depthBits = 24;
				specification.stencilBits = 8;
				specification.samples = 1;
				specification.vsync = true;

				device = Initialize();
			}

			Device(System::Window window, Specification specification) : api(GraphicsAPI::Default)
			{
				this->window = window;
				this->specification = specification;

				device = Initialize();
			}

			Device(System::Window window, GraphicsAPI api, Specification specification)
			{
				this->window = window;
				this->api = api;
				this->specification = specification;

				device = Initialize();
			}

			// Clears the buffer to the specified color.
			void Clear(Math::Color color) const
			{
				device->Clear(color);
			}

			// Hides the cursor when inside the window boundaries.
			void HideCursor(bool toggle)
			{
				SDL_ShowCursor(!toggle);
			}

			// Presents the back buffer to the front for display.
			void Present() const
			{
				device->Present();
			}

			std::shared_ptr<IDevice> GetIDevice() const
			{
				return device;
			}

			GraphicsAPI GetGraphicsAPI() const
			{
				return api;
			}
		};
	}
}

