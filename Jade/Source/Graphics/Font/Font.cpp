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
    shader.MakeActive();

    std::vector<Math::Vertex> vertices;

    for(char c : text)
    {
        // Calculate width and height.
        float x2 = static_cast<float>(x) + glyphs[c - 32].dimensions.GetX();
        float y2 = static_cast<float>(-y) - glyphs[c - 32].dimensions.GetY(); // flip y
        float w = static_cast<float>(glyphs[c - 32].dimensions.GetWidth());
        float h = static_cast<float>(glyphs[c - 32].dimensions.GetHeight());

        // Calculate cursor position.
        x += glyphs[c - 32].advanceX;
        y += glyphs[c - 32].advanceY;

        // Skip characters with no dimensions.
        if (glyphs[c - 32].dimensions.GetWidth() != 0 &&
            glyphs[c - 32].dimensions.GetHeight() != 0)
        {
            // Calculate texture coordinates and positions.
            // Lots of hard coding involved unfortunately.
            // Since quads are no longer supported, we need 6
            // vertices per character.
            Math::Vertex vertex0;
            vertex0.position = Math::Vector4(x2, -y2, 0.0f, 1.0f);
            vertex0.texture = Math::Vector2(glyphs[c - 32].texture.GetX(), glyphs[c - 32].texture.GetY());
            vertices.push_back(vertex0);

            Math::Vertex vertex1;
            vertex1.position = Math::Vector4(x2 + w, -y2, 0.0f, 1.0f);
            vertex1.texture = Math::Vector2(glyphs[c - 32].texture.GetX() +
                glyphs[c - 32].dimensions.GetWidth() / atlasWidth, glyphs[c - 32].texture.GetY());
            vertices.push_back(vertex1);

            Math::Vertex vertex2;
            vertex2.position = Math::Vector4(x2, -y2 - h, 0.0f, 1.0f);
            vertex2.texture = Math::Vector2(glyphs[c - 32].texture.GetX(), 
                glyphs[c - 32].texture.GetY() + glyphs[c - 32].dimensions.GetHeight() / atlasHeight);
            vertices.push_back(vertex2);

            Math::Vertex vertex3;
            vertex3.position = Math::Vector4(x2 + w, -y2, 0.0f, 1.0f);
            vertex3.texture = Math::Vector2(glyphs[c - 32].texture.GetX() +
                glyphs[c - 32].dimensions.GetWidth() / atlasWidth, glyphs[c - 32].texture.GetY());
            vertices.push_back(vertex3);

            Math::Vertex vertex4;
            vertex4.position = Math::Vector4(x2, -y2 - h, 0.0f, 1.0f);
            vertex4.texture = Math::Vector2(glyphs[c - 32].texture.GetX(), 
                glyphs[c - 32].texture.GetY() + glyphs[c - 32].dimensions.GetHeight() / atlasHeight);
            vertices.push_back(vertex4);

            Math::Vertex vertex5;
            vertex5.position = Math::Vector4(x2 + w, -y2 - h, 0.0f, 1.0f);
            vertex5.texture = Math::Vector2(glyphs[c - 32].texture.GetX() +
                glyphs[c - 32].dimensions.GetWidth() / atlasWidth,
                glyphs[c - 32].texture.GetY() + glyphs[c - 32].dimensions.GetHeight() 
                / atlasHeight);

            vertices.push_back(vertex5);
        }
    }

    // Initialize vertex buffer and draw.
    vBuffer.SetVertices(vertices);
    
    if (vBuffer.Create())	// Eventually we should map these.
    {
        vBuffer.Bind();

        texture.MakeActive();
        vBuffer.Draw();
        vBuffer.Unbind();
    }

    shader.MakeInactive();
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
        std::cout << "Failed to set pixel size for " << filename << "..." << std::endl;
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
        
        // MakeActive max width to 512 for simplicity.
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

    atlasWidth = w;
    atlasHeight = h;

    texture = Texture(device, nullptr, w, h, 0, 8, TextureType::Bitmap);
    texture.CreateEmptyTexture(); // Create an empty texture and fill it in with the individual bitmaps.

    // Offsets in the bitmap.
    int ox = 0;
    int oy = 0;

    rowh = 0;

    // Generate font atlas, excluding space character.
    // We only included it above to grab its data.
    for(int i = 32; i < 127; i++)
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
        
        Glyph aGlyph;
        aGlyph.advanceX = glyph->advance.x >> 6;
        aGlyph.advanceY = glyph->advance.y >> 6;
        aGlyph.character = i;

        // DirectX needs the offsets.
        Math::Rectangle rect(ox, oy, ox + glyph->bitmap.width, oy + glyph->bitmap.rows);
        aGlyph.dimensions = rect;
        aGlyph.texture.SetX(static_cast<float>(ox / w));
        aGlyph.texture.SetY(static_cast<float>(oy / h));

        // Space character has no data to fill in so it is omitted.
        if (i != 32)
        {
            texture.Fill(glyph->bitmap.buffer, glyph->bitmap.pitch, rect);
        }

        glyphs.push_back(aGlyph);

        rowh = std::max(rowh, glyph->bitmap.rows);
        ox += glyph->bitmap.width + 1;
    }

    FT_Done_Face(face);
    FT_Done_FreeType(library);
}