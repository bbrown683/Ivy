//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------
cbuffer ConstantBuffer : register(b0)
{
	matrix world;
	matrix view;
	matrix projection;
}

Texture2D txDiffuse : register(t0);
SamplerState samLinear : register(s0);

//--------------------------------------------------------------------------------------
// Vertex Shader Variables
//--------------------------------------------------------------------------------------
struct VS_INPUT
{
	float4 pos : POSITION;
	float3 nor : NORMAL;
	float2 tex : TEXCOORD;
};

struct PS_INPUT
{
	float4 pos : SV_POSITION;
	float3 nor : NORMAL;
	float2 tex : TEXCOORD;
};

//--------------------------------------------------------------------------------------
// Vertex Shader Program
//--------------------------------------------------------------------------------------
PS_INPUT Main(VS_INPUT input)
{
	PS_INPUT output = (PS_INPUT)0;

	output.pos = mul(input.pos, world);
	output.pos = mul(output.pos, view);
	output.pos = mul(output.pos, projection);

	// Calculate the normal vector against the world matrix only and then normalize the final value.
	output.nor = mul(input.nor, (float3x3)world);
	output.nor = normalize(output.nor);

	output.tex = input.tex;

	return output;
}