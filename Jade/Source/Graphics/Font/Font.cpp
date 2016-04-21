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

void Jade::Graphics::Font::Draw(std::string text, int x, int y)
{

}

void Jade::Graphics::Font::Load(std::string filename, int pixelSize)
{
	if(filename.empty())
		throw Core::ArgumentNullException("filename", __FILE__, __LINE__);


	std::cout << "[Font Data]" << std::endl;

	System::File file(filename);
	std::string contents = file.Read();

	FILE* write;
	fopen_s(&write, "test.txt", "w");
	fwrite(contents.data(), sizeof(char), sizeof contents.data(), write);
	fclose(write);

	/*
	if (buffer != nullptr)
	{
		stbtt_fontinfo fontInfo;
		if (stbtt_InitFont(&fontInfo, buffer, stbtt_GetFontOffsetForIndex(buffer, 0)))
		{
			unsigned char* bitmap = nullptr;

			// We only need the 95 printable ASCII characters.
			for (int i = 32; i < 127; i++)
			{
				Glyph glyph;
				bitmap = stbtt_GetCodepointBitmap(&fontInfo, 0, stbtt_ScaleForPixelHeight(&fontInfo, static_cast<float>(pixelSize)), i, &glyph.width, &glyph.height, &glyph.xOffset, &glyph.yOffset);

				if (bitmap == nullptr)
					std::cout << "Failed to load character " << static_cast<char>(i) << "..." << std::endl;
				else
					continue;
			}
		}
	}
	else
	{
		std::cout << "Null contents..." << std::endl;
	}
	*/
}