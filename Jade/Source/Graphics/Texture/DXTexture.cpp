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

#ifdef _WIN32

#include "DXTexture.h"

bool Jade::Graphics::DXTexture::Bind()
{
	// Use free image to get load the image and retrieve its bits.
	FREE_IMAGE_FORMAT fif = FreeImage_GetFIFFromFilename(filename.c_str());

	if (!FreeImage_FIFSupportsReading(fif))
		return false;

	FIBITMAP* bitmap = FreeImage_Load(fif, filename.c_str());

	// Null check.
	if (!bitmap)
		return false;

	// Ensure it is of 32 bits per pixel.
	if(FreeImage_GetBPP(bitmap) != 32)
	{
		FIBITMAP* temp = FreeImage_ConvertTo32Bits(bitmap);
		bitmap = temp;
		FreeImage_Unload(temp);
	}

	// Get bitmap attributes.
	unsigned int width = FreeImage_GetWidth(bitmap);
	unsigned int height = FreeImage_GetHeight(bitmap);
	unsigned int pitch = FreeImage_GetPitch(bitmap);
	
	// Retrieve the bits of the bitmap.
	BYTE* bits = FreeImage_GetBits(bitmap);

	// We are now done with freeimage, unload to prevent leaks.
	FreeImage_Unload(bitmap);

	// Create our texture description.
	D3D11_TEXTURE2D_DESC texDesc;
	ZeroMemory(&texDesc, sizeof(texDesc));
	texDesc.Width = width;
	texDesc.Height = height;
	texDesc.MipLevels = 1;
	texDesc.ArraySize = 1;
	texDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	texDesc.SampleDesc.Count = 1;
	texDesc.SampleDesc.Quality = 0;
	texDesc.Usage = D3D11_USAGE_DEFAULT;
	texDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
	texDesc.CPUAccessFlags = 0;
	texDesc.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS;
 
	// Pass our bitmap data.
	D3D11_SUBRESOURCE_DATA subData;
	ZeroMemory(&subData, sizeof(subData));
	subData.pSysMem = bits;
	subData.SysMemPitch = pitch;
	subData.SysMemSlicePitch = sizeof(bits);
	
	// Create the texture;
	HRESULT hr = device->GetID3D11Device()->CreateTexture2D(&texDesc, &subData, m_pTexture.GetAddressOf());

	if(FAILED(hr))
		return false;

	// We now need the resource description for our texture.
	D3D11_SHADER_RESOURCE_VIEW_DESC resDesc;
	ZeroMemory(&resDesc, sizeof(resDesc));
	resDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	resDesc.Format = texDesc.Format;
	resDesc.Texture2D.MipLevels = texDesc.MipLevels;

	// Create a resource view.
	hr = device->GetID3D11Device()->CreateShaderResourceView(m_pTexture.Get(), &resDesc, m_pShaderResourceView.GetAddressOf());

	if (FAILED(hr))
		return false;

	// Generate our mip maps.
	device->GetID3D11DeviceContext()->GenerateMips(m_pShaderResourceView.Get());

	// Create the sample state
	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	
	// Lastly create our sampler state.
	hr = device->GetID3D11Device()->CreateSamplerState(&sampDesc, m_pSamplerState.GetAddressOf());

	if (FAILED(hr))
		return false;

	return true;
}

bool Jade::Graphics::DXTexture::Unbind()
{
	std::cout << "Releasing textures..." << std::endl;

	return true;
}

#endif // _WIN32