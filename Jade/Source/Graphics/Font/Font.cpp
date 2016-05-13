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

#include "Font.h"

void Jade::Graphics::Font::Draw(std::string text, float x, float y)
{
	texture.Update();
}

/*
void Jade::Graphics::Font::Load(std::string filename, float pixelSize)
{
	if (filename.empty())
		throw Core::ArgumentNullException("filename", __FILE__, __LINE__);

	std::cout << "[Font Data]" << std::endl;

	System::File file(filename);
	std::string source = file.Read();
	const unsigned char* data = reinterpret_cast<const unsigned char*>(source.c_str());

	stbtt_fontinfo fontInfo;
	if (stbtt_InitFont(&fontInfo, data, 0))
	{
		for (int i = 33; i < 127; i++)
		{
			Glyph glyph;
			auto bitmap = stbtt_GetCodepointBitmap(&fontInfo, 0.0f, stbtt_ScaleForPixelHeight(&fontInfo, pixelSize),
				(glyph.character = i), &glyph.width, &glyph.height, &glyph.xOffset, &glyph.yOffset);
			glyphs.push_back(glyph);
			Texture texture = Texture(device, bitmap, glyph.width, glyph.height, glyph.width, 8, TextureType::Bitmap);
			texture.CreateTextureFromMemory();
			textures.push_back(texture);
			stbtt_FreeBitmap(bitmap, nullptr);
		}
	}
}
*/

void Jade::Graphics::Font::Load(std::string filename, int width, int height, float pixelSize)
{
	if (filename.empty())
		throw Core::ArgumentNullException("filename", __FILE__, __LINE__);

	std::cout << "[Font Data]" << std::endl;

	// Create a bitmap of our printable characters.
	std::vector<unsigned char> temp_bitmap(width * height);

	System::File file(filename);
	std::string source = file.Read();
	const unsigned char* data = reinterpret_cast<const unsigned char*>(source.c_str());

	// Process space character even though it wont be embedded into the bitmap.
	// It should be inserted into the stbtt_bakedchar struct.
	if (stbtt_BakeFontBitmap(data, 0, pixelSize, temp_bitmap.data(), 
		width, height, 32, 95, bakedChar.data()))
	{
		// Apparently pitch is the image width.
		// stb_truetype creates a 2 bit channel bitmap, so it is only 8 bits in width.
		texture = Texture(device, temp_bitmap.data(), width, height, width, 8, TextureType::Bitmap);
		if (texture.CreateTextureFromMemory())
		{
			std::cout << "Font bitmap was successfully created." << std::endl;
		}
	}
}