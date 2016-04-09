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

	FT_Library library;

	FT_Error error = FT_Init_FreeType(&library);
	
	if (error)
		throw Core::InitializationException("Failed to initialize FreeType.");

	FT_Face face;
	error = FT_New_Face(library, filename.c_str(), 0, &face);

	if (error)
	{
		std::cout << "Failed to load face from font file " << filename << "..." << std::endl;
		return;
	}

	// We must load the font at a specified size.
	error = FT_Set_Pixel_Sizes(face, 0, pixelSize);

	if(error)
	{
		std::cout << "Failed to load face from font file " << filename << "..." << std::endl;
		return;
	}

	std::cout << "Font " << filename << " was loaded..." << std::endl;

	FT_GlyphSlot glyph = face->glyph;

	// Load each ASCII character.
	for (int i = 32; i < 256; i++)
	{
		if (FT_Load_Char(face, i, FT_LOAD_RENDER))
		{
			fprintf(stderr, "Character %c failed to load successfully...\n", i);
			continue;
		}
	}
}