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

#include "Graphics/Device/GLDevice.h"
#include "Graphics/Texture/ITexture.h"
#include "Graphics/Texture/TextureType.h"

#include "FreeImage.h"

namespace Jade
{
    namespace Graphics
    {
        class GLTexture : public ITexture
        {
            std::string filename;
            TextureType type;

            unsigned char* bitmap;
            unsigned int width;
            unsigned int height;
            unsigned int pitch;
            unsigned int bits;

        public:

            GLTexture(std::string filename, TextureType type)
            {
                this->filename = filename;
                this->type = type;
            }

            // Bitmap is already created, but must be transferred to D3D.
            GLTexture(unsigned char* bitmap, int width, int height, int pitch, unsigned int bits, TextureType type)
            {
                this->bitmap = bitmap;
                this->width = width;
                this->height = height;
                this->pitch = pitch;
                this->bits = bits;
                this->type = type;
            }

            ~GLTexture()
            {
                std::cout << "Texture was released successfully..." << std::endl;
            }

            //! Creates an empty texture which must be dynamically filled in using the Fill method.
            bool CreateEmptyTexture() override;
            //! Creates a texture from the file specified in the constructor and returns a bool determining if it was successful.
            bool CreateTextureFromFile() override;
            //! Creates a texture from the bits specified in the constructor and returns a bool determining if it was successful.
            bool CreateTextureFromMemory() override;
            // Updates a dynamic texture.
            void Fill(unsigned char* bitmap, unsigned pitch, Math::Rectangle rect) override;
            //! Updates the texture resources to ensure that they remain the target of the drawing operations.
            void MakeActive() override;
        };
    }
}