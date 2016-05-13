#include "DXBlender.h"

bool Jade::Graphics::DXBlender::SetBlendState(unsigned int mask)
{
	// Reset the blend state before attempting to create a new one.
	if (m_pBlendState)
		m_pBlendState.Reset();

	D3D11_BLEND_DESC blendDesc;
	ZeroMemory(&blendDesc, sizeof(blendDesc));
	blendDesc.RenderTarget[0].BlendEnable = true;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = 0x0F;

	float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

	//d3dDevice_->CreateBlendState(&blendDesc, &alphaBlendState_);
	//d3dContext_->OMSetBlendState(alphaBlendState_, blendFactor, 0xFFFFFFFF);
	/*
	D3D11_BLEND_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.RenderTarget[0].BlendEnable = true;
	desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	*/

	HRESULT hr = device->GetID3D11Device()->CreateBlendState(&blendDesc, m_pBlendState.GetAddressOf());

	if(FAILED(hr))
	{
		std::cout << "BlendState failed to be created successfully..." << std::endl;
		return false;
	}

	device->GetID3D11DeviceContext()->OMSetBlendState(m_pBlendState.Get(), blendFactor, mask);

	return true;
}
