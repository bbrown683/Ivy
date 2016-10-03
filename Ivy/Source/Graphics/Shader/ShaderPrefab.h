#pragma once

#include "Core/Include.h"

namespace Ivy
{
    class ShaderPrefab
    {
    public:

        // Error shaders are used in the event that the provided 
        // shaders do not compile or load correctly.

        static const std::string HLSLErrorVertexShader;
        static const std::string HLSLErrorPixelShader;
        static const std::string GLSLErrorVertexShader;
        static const std::string GLSLErrorPixelShader;
    };
}