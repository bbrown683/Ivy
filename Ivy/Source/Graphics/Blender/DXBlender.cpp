#include "DXBlender.h"

bool Ivy::Graphics::DXBlender::SetBlendState(unsigned int mask)
{
	// Reset the blend state before attempting to create a new one.
	if (m_pBlendState)
		m_pBlendState.Reset();

	D3D11_BLEND_DESC blendDesc;
	ZeroMemory(&blendDesc, sizeof(blendDesc));
	blendDesc.RenderTarget[0].BlendEnable = true;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = 0x0F;

	float blendFactor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

	HRESULT hr = device->GetID3D11Device()->CreateBlendState(&blendDesc, m_pBlendState.GetAddressOf());

	if(FAILED(hr))
	{
		std::cout << "BlendState failed to be created successfully..." << std::endl;
		return false;
	}

	device->GetID3D11DeviceContext()->OMSetBlendState(m_pBlendState.Get(), blendFactor, mask);
    enabled = true;

	return true;
}

bool Ivy::Graphics::DXBlender::DisableBlendState()
{
    // Set default blend state.
    device->GetID3D11DeviceContext()->OMSetBlendState(nullptr, nullptr, 0xFFFFFFFF);
    enabled = false;
    return true;
}

bool Ivy::Graphics::DXBlender::Enabled()
{
    return enabled;
}
