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

#include "Core/Exception/Exception.h"
#include "Core/Utility.h"
#include "Graphics/Device/IDevice.h"
#include "Graphics/Device/Specification.h"
#include "System/Window/Window.h"

#ifdef JADE_PLATFORM_WINDOWS
#include <wrl/client.h>
#include <d3d11.h>

// Declare to create cleaner code below.
using namespace Microsoft::WRL;

namespace Jade
{
	namespace Graphics
	{
		class DXDevice : public IDevice
		{
			std::shared_ptr<System::IWindow> window;
			Specification specification;

			// Necessary to initialize a Direct3D11 device
			D3D_DRIVER_TYPE m_DriverType;
			D3D_FEATURE_LEVEL m_FeatureLevel;
			D3D11_VIEWPORT m_Viewport;

			ComPtr<ID3D11Device> m_pDevice = nullptr;
			ComPtr<ID3D11DeviceContext> m_pImmediateContext = nullptr;
			ComPtr<IDXGISwapChain> m_pSwapChain = nullptr;
			ComPtr<ID3D11RenderTargetView> m_pRenderTargetView = nullptr;
			ComPtr<ID3D11Texture2D> m_pDepthStencil = nullptr;
			ComPtr<ID3D11DepthStencilView> m_pDepthStencilView = nullptr;
			ComPtr<ID3D11DepthStencilState> m_pDepthStencilState = nullptr;
			ComPtr<ID3D11SamplerState> m_pSamplerState = nullptr;

			bool Create() override;
			bool Release() override;
			void OnWindowResize() override;

		public:

			DXDevice() : window(nullptr) { }

			// We have a window handle.
			DXDevice(std::shared_ptr<System::IWindow> window, Specification specification)
			{
				this->window = window;
				this->specification = specification;

				// Create our device.
				if (!DXDevice::Create())
				{
					// If device fails we need to throw an exception 
					// as it can get nasty otherwise.
					throw Core::DeviceCreationException();
				}
			}

			~DXDevice()
			{
				// Cleanup resources.
				DXDevice::Release();
			}

			// Main functions inherited by Device class.
			void Clear(Math::Color color) override;
			void Present() override;
			std::shared_ptr<System::IWindow> GetIWindow() const;
			char* DeviceInformation() override;

			// Retrieval functions for DirectX related objects.
			D3D_DRIVER_TYPE GetD3DDriverType() const;
			D3D_FEATURE_LEVEL GetD3DFeatureLevel() const;
			D3D11_VIEWPORT GetD3D11Viewport() const;
			const ComPtr<ID3D11Device>& GetID3D11Device() const;
			const ComPtr<ID3D11DeviceContext>& GetID3D11DeviceContext() const;
			const ComPtr<IDXGISwapChain>& GetIDXGISwapChain() const;
			const ComPtr<ID3D11RenderTargetView>& GetID3D11RenderTargetView() const;
			const ComPtr<ID3D11Texture2D>& GetID3D11DepthStencil() const;
			const ComPtr<ID3D11DepthStencilView>& GetID3D11DepthStencilView() const;
		};
	}
}
#endif