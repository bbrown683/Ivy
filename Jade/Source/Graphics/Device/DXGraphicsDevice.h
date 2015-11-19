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

#include "IGraphicsDevice.h"
#include "Graphics/Window/IWindow.h"

#include <d3d11.h>

namespace Jade
{
	namespace Graphics
	{
		class DXGraphicsDevice : public IGraphicsDevice
		{
		private:

			std::shared_ptr<IWindow> window;

			// Necessary to initialize a D3D graphicsDevice.

			std::shared_ptr<ID3D11Device>				m_pDevice;				
			std::shared_ptr<ID3D11DeviceContext>		m_pImmediateContext;
			std::shared_ptr<IDXGISwapChain>				m_pSwapChain;
			std::shared_ptr<ID3D11RenderTargetView>		m_pRenderTargetView;
			D3D_DRIVER_TYPE								m_DriverType;
			D3D_FEATURE_LEVEL							m_FeatureLevel;
			D3D11_VIEWPORT								m_Viewport;

			bool CreateDevice() override;

			bool ReleaseDevice() override;

		public:

			DXGraphicsDevice() : window(nullptr) { }

			// We have a window handle.
			DXGraphicsDevice(std::shared_ptr<IWindow> window)
			{
				this->window = window;
			}

			void Clear(Math::Color color) override;
			void Present() override;
		};
	}
}