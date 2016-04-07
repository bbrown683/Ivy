//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------
cbuffer ConstantBuffer
{
	matrix world;
	matrix view;
	matrix projection;
}

Texture2D txDiffuse;
SamplerState samLinear;

//--------------------------------------------------------------------------------------
// Vertex Shader Variables
//--------------------------------------------------------------------------------------
struct VS_INPUT
{
	float4 Pos : POSITION;
	float2 Tex : TEXCOORD0;
	float3 Nor : NORMAL;
};

struct PS_INPUT
{
	float4 Pos : SV_POSITION;
	float2 Tex : TEXCOORD0;
	float3 Nor : NORMAL;
};

//--------------------------------------------------------------------------------------
// Vertex Shader Program
//--------------------------------------------------------------------------------------
PS_INPUT Main(VS_INPUT input)
{
	PS_INPUT output = (PS_INPUT)0;

	input.Pos.w = 1.0f;

	output.Pos = mul(input.Pos, world);
	output.Pos = mul(output.Pos, view);
	output.Pos = mul(output.Pos, projection);

	output.Tex = input.Tex;

	output.Nor = input.Nor;

	return output;
}