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

#include <iostream>

#include "Graphics/Device/DXDevice.h"

bool Jade::Graphics::DXDevice::Create()
{
	UINT createDeviceFlags = 0;

#ifdef _DEBUG
	// Add the debug device flag along with any other defined flags.
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};

	UINT numDriverTypes = ARRAYSIZE(driverTypes);

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
	};

	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(DXGI_SWAP_CHAIN_DESC));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = window->GetWidth();
	sd.BufferDesc.Height = window->GetHeight();
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = static_cast<HWND>(window->Handle());
	sd.Windowed = true;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	
	HRESULT result = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags, featureLevels, 
		numFeatureLevels, D3D11_SDK_VERSION, &sd, &m_pSwapChain, &m_pDevice, &m_FeatureLevel, &m_pImmediateContext);

	if(!SUCCEEDED(result))
	{
		return false;
	}

	ID3D11Texture2D* m_pBackBuffer = nullptr;
	m_pSwapChain->GetBuffer(NULL, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&m_pBackBuffer));
	m_pDevice->CreateRenderTargetView(m_pBackBuffer, nullptr, &m_pRenderTargetView);

	// Release object now that it is unneeded.
	m_pBackBuffer->Release();

	m_pImmediateContext->OMSetRenderTargets(1, &m_pRenderTargetView, nullptr);

	D3D11_VIEWPORT vp;
	ZeroMemory(&vp, sizeof(D3D11_VIEWPORT));
	vp.Width = static_cast<FLOAT>(window->GetWidth());
	vp.Height = static_cast<FLOAT>(window->GetHeight());
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;

	m_pImmediateContext->RSSetViewports(1, &vp);

	std::cout << "DirectX device was created successfully..." << std::endl;

	return true; // Successful.
}

bool Jade::Graphics::DXDevice::Release()
{
	// Remove any loose pointers.
	if(m_pImmediateContext)		m_pImmediateContext->ClearState();
	if(m_pBuffer)				m_pBuffer->Release();
	if(m_pInputLayout)			m_pInputLayout->Release();
	if(m_pRenderTargetView)		m_pRenderTargetView->Release();
	if(m_pSwapChain)			m_pSwapChain->Release();
	if(m_pImmediateContext)		m_pImmediateContext->Release();
	if(m_pDevice)				m_pDevice->Release();
	
	std::cout << "DirectX device was disposed of successfully..." << std::endl;

	return true;
}

void Jade::Graphics::DXDevice::Clear(Math::Color color)
{	
	FLOAT colorRGBA[] = { color.GetRed(), color.GetGreen(), color.GetBlue(), color.GetAlpha() };
	m_pImmediateContext->ClearRenderTargetView(m_pRenderTargetView, colorRGBA);
}

// Swaps the front and back buffers.
void Jade::Graphics::DXDevice::Present()
{
	m_pSwapChain->Present(1, 0);
}

char* Jade::Graphics::DXDevice::DeviceInformation()
{
	return nullptr;
}
