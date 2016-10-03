#include "ShaderPrefab.h"

const std::string Ivy::ShaderPrefab::HLSLErrorVertexShader =
R"(cbuffer PerObject : register(b0)
{
    matrix world;
}

cbuffer OnResize : register(b1)
{
    matrix projection;
}

cbuffer NeverChanges : register(b2)
{
    matrix view;
}

struct VS_INPUT
{
    float4 Pos: POSITION;
}

struct PS_INPUT
{
	float4 Pos : SV_POSITION;
}

PS_INPUT main(VS_INPUT input)
{
    PS_INPUT output = (PS_INPUT)0;
    
	output.Pos = mul(input.Pos, world);
	output.Pos = mul(output.Pos, view);
	output.Pos = mul(output.Pos, projection);

    return output;
}
)";

const std::string Ivy::ShaderPrefab::HLSLErrorPixelShader =
R"(
struct PS_INPUT
{
	float4 Pos : SV_POSITION;
}

float4 main(PS_INPUT input) : SV_TARGET
{
    return float4(1.0f, 0.5f, 8.0f, 1.0f);
}
)";