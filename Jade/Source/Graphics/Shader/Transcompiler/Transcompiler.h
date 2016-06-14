#pragma once

#include "Core/Utility.h"

// HLSL->GLSL
// Macro defines based off the following documentation:
// https://msdn.microsoft.com/en-us/library/windows/apps/mt187142.aspx

std::map<std::string, std::string> keywordMapping;

// Vector Types.
#define int2 "int2"
#define int3 "int3"
#define int4 "int4"
#define bool2 "bvec2"
#define bool3 "bvec3"
#define bool4 "bvec4"
#define float2 "vec2"
#define float3 "vec3"
#define float4 "vec4"

// Matrices
#define float2x2 "mat2"
#define float3x3 "mat3"
#define float4x4 "mat4"
#define matrix float4x4

// Precision types
#define min16float "mediump float"
#define min12int "mediump int"
#define min10float "lowp float"

// Keywords
#define layout(...) "layout("  (__VA_ARGS__) ")" 
#define constant "cbuffer" ? "uniform"
#define sample	"texture.Sample" ? "texture2D"
#define texture "sampler2D"

// Semantics
#define SV_Position "gl_Position"
#define SV_Target "gl_FragColor"
#define SV_IsFrontFace "gl_FrontFacing"

namespace Jade
{
    namespace Graphics
    {
        class Transcompiler
        {
            std::string HLSL2GLSL(std::string filename)
            {

            }
        };
    }
}