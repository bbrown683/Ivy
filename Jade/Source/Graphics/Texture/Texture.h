#pragma once

#include "FreeImage/FreeImage.h"

#include "Graphics/Texture/TextureType.h"

namespace Jade
{
	namespace Graphics
	{
		struct Texture
		{
			TextureType type;

			void Load()
			{
				FreeImage_Initialise(1);

				FREE_IMAGE_FORMAT format = FreeImage_GetFileType("box.dds", 0);
				FIBITMAP* bitmap = FreeImage_Load(format, "box.dds");

				
				if(FreeImage_GetBPP(bitmap) != 32)
				{
					FIBITMAP *tmp = FreeImage_ConvertTo32Bits(bitmap);
					FreeImage_Unload(bitmap);
					bitmap = tmp;
				}

				int width = FreeImage_GetWidth(bitmap);
				int height = FreeImage_GetHeight(bitmap);

				int size = sizeof(unsigned char) * width * height * 4;

				FreeImage_FlipVertical(bitmap);

				BYTE* bits = FreeImage_GetBits(bitmap);

				FreeImage_DeInitialise();
			}
		};
	}
}