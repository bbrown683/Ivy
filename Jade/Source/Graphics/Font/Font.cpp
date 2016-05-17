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
	shader.MakeActive();
	texture.Set();
}

void Jade::Graphics::Font::Load(std::string filename, int pixelSize)
{
	if (filename.empty())
		throw Core::ArgumentNullException("filename", __FILE__, __LINE__);

	std::cout << "[Font Data]" << std::endl;

	FT_Library library;

	FT_Error error = FT_Init_FreeType(&library);
	if (error)
	{
		std::cout << "Failed to initialize FreeType..." << std::endl;
		return;
	}

	FT_Face face;
	error = FT_New_Face(library, filename.c_str(), 0, &face);

	if (error)
	{
		std::cout << "Failed to load face from font file " << filename << "..." << std::endl;
		return;
	}

	error = FT_Set_Pixel_Sizes(face, 0, pixelSize);

	if (error)
	{
		std::cout << "Failed to load face from font file " << filename << "..." << std::endl;
		return;
	}

	std::cout << "Font " << filename << " was loaded..." << std::endl;

	// The following code below uses a portion of the following:
	// https://en.wikibooks.org/wiki/OpenGL_Programming/Modern_OpenGL_Tutorial_Text_Rendering_02
	// It was converted into Direct3D11's form of inserting a bitmap into an existing texture.

	FT_GlyphSlot glyph = face->glyph;

	// Determine the width of the bitmap we need.
	unsigned int roww = 0;
	unsigned int rowh = 0;
	unsigned int w = 0;
	unsigned int h = 0;

	// Load only the printable ASCII characters.
	for (int i = 32; i < 127; i++)
	{
		if (FT_Load_Char(face, i, FT_LOAD_RENDER)) 
		{
			printf("Loading character %c failed!\n", i);
			continue;
		}
		
		// Set max width to 512 for simplicity.
		if (roww + glyph->bitmap.width + 1 >= 512) 
		{
			w = std::max(w, roww);
			h += rowh;
			roww = 0;
			rowh = 0;
		}

		roww += glyph->bitmap.width + 1;
		rowh = std::max(rowh, glyph->bitmap.rows);
	}

	w = std::max(w, roww);
	h += rowh;

	texture = Texture(device, nullptr, w, h, 0, 8, TextureType::Bitmap);
	texture.CreateEmptyTexture(); // Create an empty texture and fill it in with the individual bitmaps.

	// Offsets in the bitmap.
	int ox = 0;
	int oy = 0;

	rowh = 0;

	// Generate font atlas, excluding space character.
	// We only included it above to grab its data.
	for(int i = 33; i < 127; i++)
	{
		if (FT_Load_Char(face, i, FT_LOAD_RENDER))
		{
			printf("Loading character %c failed!\n", i);
			continue;
		}

		if (ox + glyph->bitmap.width + 1 >= 512) 
		{
			oy += rowh;
			rowh = 0;
			ox = 0;
		}
		
		Math::Rectangle rect(ox, oy, ox + glyph->bitmap.width, oy + glyph->bitmap.rows);
		texture.Fill(glyph->bitmap.buffer, glyph->bitmap.pitch, rect);

		rowh = std::max(rowh, glyph->bitmap.rows);
		ox += glyph->bitmap.width + 1;
	}
}