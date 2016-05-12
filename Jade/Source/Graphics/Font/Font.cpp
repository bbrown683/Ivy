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

	for(char c : text)
	{
		stbtt_aligned_quad q;
		stbtt_GetBakedQuad(cdata.data(), 512, 512, static_cast<int>(c - 32), &x, &y, &q, 1);
		std::cout << "X0: " << q.x0 << std::endl;
		std::cout << "X1: " << q.x1 << std::endl;
	}
}

void Jade::Graphics::Font::Load(std::string filename, int pixelSize)
{
	if (filename.empty())
		throw Core::ArgumentNullException("filename", __FILE__, __LINE__);

	std::cout << "[Font Data]" << std::endl;

	// Huge ass buffer. 1 shifted to the left 20 digits.
	std::vector<unsigned char> ttf_buffer(1 << 20);

	// Create 512 x 512 bitmap of our printable characters.
	std::vector<unsigned char> temp_bitmap(512 * 512);

	FILE* file;
	fopen_s(&file, filename.c_str(), "rb");

	fread(&ttf_buffer, 1, 1 << 20, file);
	if (stbtt_BakeFontBitmap(ttf_buffer.data(), 0, 32.0, temp_bitmap.data(), 512, 512, 32, 96, cdata.data()))
	{
		// Apparently pitch is 1.
		// Fill in everything else like normal.
		texture = Texture(device, temp_bitmap.data(), 512, 512, 1, TextureType::Bitmap);
		if (texture.CreateTextureFromMemory())
			std::cout << "Successfully created texture." << std::endl;
	}
}