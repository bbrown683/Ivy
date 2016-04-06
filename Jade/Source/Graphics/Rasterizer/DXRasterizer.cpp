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

#include "DXRasterizer.h"

bool Jade::Graphics::DXRasterizer::SetState()
{
	D3D11_RASTERIZER_DESC rasterDesc;
	ZeroMemory(&rasterDesc, sizeof(rasterDesc));
	
	// Set culling mode.
	switch(rasterizerSetting.cullMode)
	{
	case CullMode::Front: rasterDesc.CullMode = D3D11_CULL_FRONT; break;
	case CullMode::Back: rasterDesc.CullMode = D3D11_CULL_BACK; break;
	default: rasterDesc.CullMode = D3D11_CULL_NONE; break;
	}

	// Set everything else.
	rasterDesc.AntialiasedLineEnable = false;
	rasterDesc.DepthBias = 0;
	rasterDesc.DepthBiasClamp = 0.0f;
	rasterDesc.DepthClipEnable = true;
	rasterDesc.FillMode = (rasterizerSetting.fillMode == FillMode::Solid) ? D3D11_FILL_SOLID : D3D11_FILL_WIREFRAME;
	rasterDesc.FrontCounterClockwise = false;
	rasterDesc.MultisampleEnable = false;
	rasterDesc.ScissorEnable = false;
	rasterDesc.SlopeScaledDepthBias = 0.0f;

	// Create the state.
	HRESULT hr = device->GetID3D11Device()->CreateRasterizerState(&rasterDesc, m_pRasterizerState.GetAddressOf());

	if (FAILED(hr))
		return false;

	// If state creation succeeds we can set the state.
	device->GetID3D11DeviceContext()->RSSetState(m_pRasterizerState.Get());

	std::cout << "Rasterizer state was created successfully..." << std::endl;

	return true;
}