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

#include "DXTexture.h"

#ifdef JADE_PLATFORM_WINDOWS
bool Jade::Graphics::DXTexture::CreateEmptyTexture()
{
    D3D11_TEXTURE2D_DESC texDesc;
	ZeroMemory(&texDesc, sizeof(texDesc));
	texDesc.Width = width;
	texDesc.Height = height;
	texDesc.MipLevels = 1;
	texDesc.ArraySize = 1;
	texDesc.Format = DetermineTextureFormat();
	texDesc.SampleDesc.Count = 1;
	texDesc.SampleDesc.Quality = 0;
	texDesc.Usage = D3D11_USAGE_DEFAULT;
	texDesc.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS; // Generate the mip maps we need.
	texDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
	texDesc.CPUAccessFlags = 0;

	// Create the texture.
	HRESULT hr = device->GetID3D11Device()->CreateTexture2D(&texDesc, nullptr, m_pTexture.GetAddressOf());

	if (FAILED(hr))
	{
		std::cout << "Texture2D failed to be created..." << std::endl;
		return false;
	}

	// We now need the resource description for our texture.
	D3D11_SHADER_RESOURCE_VIEW_DESC resDesc;
	ZeroMemory(&resDesc, sizeof(resDesc));
	resDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D; // TODO: Add multisampling support for textures.
	resDesc.Format = texDesc.Format;
	resDesc.Texture2D.MipLevels = texDesc.MipLevels;
	resDesc.Texture2D.MostDetailedMip = texDesc.MipLevels - 1;

	// Create a resource view.
	hr = device->GetID3D11Device()->CreateShaderResourceView(m_pTexture.Get(), &resDesc, m_pShaderResourceView.GetAddressOf());

	if (FAILED(hr))
	{
		std::cout << "ShaderResourceView failed to be created..." << std::endl;
		return false;
	}

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
	{
		std::cout << "SamplerState failed to be created..." << std::endl;
		return false;
	}

	std::cout << "Texture was created successfully..." << std::endl;

	return true;
}

bool Jade::Graphics::DXTexture::CreateTextureFromFile()
{
	// We need to get a direct path to the location of the texture from our executable.
	// Temporary path for now.
	std::string filepath = ".\\resources\\models\\";
	filepath.append(filename.c_str());

	// Use free image to get load the image and retrieve its bits.
	FREE_IMAGE_FORMAT fif = FreeImage_GetFIFFromFilename(filepath.c_str());

	if (!FreeImage_FIFSupportsReading(fif))
		return false;

	FIBITMAP* aBitmap = FreeImage_Load(fif, filepath.c_str());

	// Null check.
	if (!aBitmap)
	{
		std::cout << "Failed to load file " << filename << " successfully..." << std::endl;
		return false;
	}

	// Needs to be a 32 bit bitmap.
	if(FreeImage_GetBPP(aBitmap) != 32)
	{
		FIBITMAP* temp = aBitmap;
		aBitmap = FreeImage_ConvertTo32Bits(aBitmap);
		FreeImage_Unload(temp);
	}

	// We have to flip the bitmap for it to appear properly.
	FreeImage_FlipVertical(aBitmap);

	// Get bitmap attributes.
	unsigned int aWidth = FreeImage_GetWidth(aBitmap);
	unsigned int aHeight = FreeImage_GetHeight(aBitmap);
	unsigned int aPitch = FreeImage_GetPitch(aBitmap);

	// Retrieve the bits of the bitmap.
	BYTE* aBits = FreeImage_GetBits(aBitmap);

	// Create our texture description.
	D3D11_TEXTURE2D_DESC texDesc;
	ZeroMemory(&texDesc, sizeof(texDesc));
	texDesc.Width = aWidth;
	texDesc.Height = aHeight;
	texDesc.MipLevels = 1;
	texDesc.ArraySize = 1;
	texDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM; // FreeType uses this format.
	texDesc.SampleDesc.Count = 1;
	texDesc.SampleDesc.Quality = 0;
	texDesc.Usage = D3D11_USAGE_DEFAULT;
	texDesc.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS; // Generate the mip maps we need.
	texDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
	texDesc.CPUAccessFlags = 0;

	// Pass our bitmap data.
	D3D11_SUBRESOURCE_DATA subData;
	ZeroMemory(&subData, sizeof(subData));
	subData.pSysMem = aBits;
	subData.SysMemPitch = aPitch;

	// Create the texture;
	HRESULT hr = device->GetID3D11Device()->CreateTexture2D(&texDesc, &subData, m_pTexture.GetAddressOf());

	if (FAILED(hr))
	{
		std::cout << "Texture2D failed to be created..." << std::endl;
		return false;
	}

	// We now need the resource description for our texture.
	D3D11_SHADER_RESOURCE_VIEW_DESC resDesc;
	ZeroMemory(&resDesc, sizeof(resDesc));
	resDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	resDesc.Format = texDesc.Format;
	resDesc.Texture2D.MipLevels = texDesc.MipLevels;
	resDesc.Texture2D.MostDetailedMip = texDesc.MipLevels - 1;

	// Create a resource view.
	hr = device->GetID3D11Device()->CreateShaderResourceView(m_pTexture.Get(), &resDesc, m_pShaderResourceView.GetAddressOf());

	if (FAILED(hr))
	{
		std::cout << "ShaderResourceView failed to be created..." << std::endl;
		return false;
	}

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
	{
		std::cout << "SamplerState failed to be created..." << std::endl;
		return false;
	}

	// We are now done with bitmap, unload to prevent leaks.
	FreeImage_Unload(aBitmap);

	std::cout << "Texture " << filename << " was created successfully..." << std::endl;

	return true;
}

// Used for texturing bits contained in memory such as bitmaps from FreeType.
bool Jade::Graphics::DXTexture::CreateTextureFromMemory()
{
	// Create our texture description.
	D3D11_TEXTURE2D_DESC texDesc;
	ZeroMemory(&texDesc, sizeof(texDesc));
	texDesc.Width = width;
	texDesc.Height = height;
	texDesc.MipLevels = 1;
	texDesc.ArraySize = 1;
	texDesc.Format = DetermineTextureFormat();
	texDesc.SampleDesc.Count = 1;
	texDesc.SampleDesc.Quality = 0;
	texDesc.Usage = D3D11_USAGE_DEFAULT;
	texDesc.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS; // Generate the mip maps we need.
	texDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
	texDesc.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA subData;
	ZeroMemory(&subData, sizeof(subData));
	subData.pSysMem = bitmap;
	subData.SysMemPitch = pitch;

	// Create the texture.
	HRESULT hr = device->GetID3D11Device()->CreateTexture2D(&texDesc, &subData, m_pTexture.GetAddressOf());
	
	if (FAILED(hr))
	{
		std::cout << "Texture2D failed to be created..." << std::endl;
		return false;
	}

	// We now need the resource description for our texture.
	D3D11_SHADER_RESOURCE_VIEW_DESC resDesc;
	ZeroMemory(&resDesc, sizeof(resDesc));
	resDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	resDesc.Format = texDesc.Format;
	resDesc.Texture2D.MipLevels = texDesc.MipLevels;
	resDesc.Texture2D.MostDetailedMip = texDesc.MipLevels - 1;

	// Create a resource view.
	hr = device->GetID3D11Device()->CreateShaderResourceView(m_pTexture.Get(), &resDesc, m_pShaderResourceView.GetAddressOf());

	if (FAILED(hr))
	{
		std::cout << "ShaderResourceView failed to be created..." << std::endl;
		return false;
	}

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
	{
		std::cout << "SamplerState failed to be created..." << std::endl;
		return false;
	}

	std::cout << "Texture was created successfully..." << std::endl;

	return true;
}

DXGI_FORMAT Jade::Graphics::DXTexture::DetermineTextureFormat()
{
	if (bits == 8)
		return DXGI_FORMAT_R8_UNORM;
	if (bits == 16)
		return DXGI_FORMAT_R8G8_UNORM;
	if (bits == 32)
		return DXGI_FORMAT_R8G8B8A8_UNORM;

	// Need to throw an exception here...
	return DXGI_FORMAT_UNKNOWN;
}

void Jade::Graphics::DXTexture::Fill(unsigned char * bitmap, unsigned pitch, Math::Rectangle rect)
{
	D3D11_BOX box;
	box.left = rect.GetX();
	box.right = rect.GetWidth();
	box.top = rect.GetY();
	box.bottom = rect.GetHeight();
	box.front = 0;
	box.back = 1;

	device->GetID3D11DeviceContext()->UpdateSubresource(m_pTexture.Get(), 0, &box, bitmap, pitch, 0);
}

void Jade::Graphics::DXTexture::MakeActive()
{
	// MakeActive the sampler and resource view.
	if(m_pShaderResourceView.Get() != nullptr)
		device->GetID3D11DeviceContext()->PSSetShaderResources(0, 1, m_pShaderResourceView.GetAddressOf());
	if(m_pSamplerState.Get() != nullptr)
		device->GetID3D11DeviceContext()->PSSetSamplers(0, 1, m_pSamplerState.GetAddressOf());
}
#endif