#pragma once

#include "Math/Rectangle.h"
#include "Math/Vector2.h"

namespace Jade
{
    namespace Graphics
    {
        // Information that is specific to a single character in a font face.
        struct Glyph
        {
            int advanceX;
            int advanceY;
            char character;
            Math::Rectangle dimensions;
            Math::Vector2 texture;
        };
    }
}