#pragma once

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

#include "stb/stb_truetype.h"

#include "Core/Utility.h"
#include "Core/Exception/Exception.h"
#include "Graphics/Device/Device.h"
#include "Graphics/Font/Glyph.h"
#include "Graphics/Mesh/Mesh.h"
#include "Graphics/Texture/Texture.h"
#include "System/File.h"

namespace Jade
{
	namespace Graphics
	{
		// Class for font rendering.
		class Font
		{
			Device device;
			Shader shader;
			
			Texture texture;
			std::vector<stbtt_bakedchar> bakedChar;

		public:
 
			Font(Device device, Shader shader)
			{
				this->device = device;

				bakedChar = std::vector<stbtt_bakedchar>(95);
			}

			//! Draws the given text at the specified x and y coordinates at a certain pixel size.
			void Draw(std::string text, float x, float y);
			//! Loads the specified font file and creates individual textures for each printable character at a specified pixel size.
			//void Load(std::string filename, float pixelSize);
			
			//! Loads the specified font file and creates a bitmap with the designated width, height, and pixel size.
			void Load(std::string filename, int width, int height, float pixelSize);
		};
	}
}
