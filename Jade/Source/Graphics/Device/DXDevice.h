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

#include <d3d11.h>

#include "Core/Utility.h"

#include "Graphics/Device/IDevice.h"
#include "System/Window/Window.h"

namespace Jade
{
	namespace Graphics
	{
		class DXDevice : public IDevice
		{
		private:

			// Our shaders will need access to our objects.
			friend class DXShader;
			friend class DXMesh;

			std::shared_ptr<System::IWindow> window;

			// Necessary to initialize a D3D device.

			ID3D11Device*				m_pDevice				= nullptr;
			ID3D11DeviceContext*		m_pImmediateContext		= nullptr;
			IDXGISwapChain*				m_pSwapChain			= nullptr;
			ID3D11RenderTargetView*		m_pRenderTargetView		= nullptr;
			D3D_DRIVER_TYPE				m_DriverType;
			D3D_FEATURE_LEVEL			m_FeatureLevel;
			D3D11_VIEWPORT				m_Viewport;

			// Used in DXShader class.
			ID3D11InputLayout*			m_pInputLayout			= nullptr;

			// Used in DXMesh class.
			ID3D11Buffer*				m_pVertexBuffer			= nullptr;
			ID3D11Buffer*				m_pConstantBuffer		= nullptr;
			ID3D11Buffer*				m_pIndexBuffer			= nullptr;

			bool Create() override;

			bool Release() override;

		public:

			DXDevice() : window(nullptr) { }

			// We have a window handle.
			DXDevice(std::shared_ptr<System::IWindow> window)
			{
				this->window = window;

				// Create our device.
				if(!Create())
				{
					SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Device creation error", "Failed to initialize or create a DirectX11 Device.", window->GetSDLWindow());
					
					// Dispose of any allocated memory and close the window.
					Release();
					window->Close();
				}
			}

			~DXDevice()
			{
				// Cleanup resources.
				Release();
			}

			void Clear(Math::Color color) override;
			void Present() override;
			char* DeviceInformation() override;
		};
	}
}