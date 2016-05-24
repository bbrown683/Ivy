//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------
cbuffer PerObject : register(b0)
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

//--------------------------------------------------------------------------------------
// Vertex Shader Variables
//--------------------------------------------------------------------------------------
struct VS_INPUT
{
	float4 Pos : POSITION;
	float2 Tex : TEXCOORD0;
	float3 Nor : NORMAL;
	float4 Col : COLOR;
};

struct PS_INPUT
{
	float4 Pos : SV_POSITION;
	float2 Tex : TEXCOORD0;
	float3 Nor : NORMAL;
	float4 Col : COLOR;
};

//--------------------------------------------------------------------------------------
// Vertex Shader Program
//--------------------------------------------------------------------------------------
PS_INPUT main(VS_INPUT input)
{
	PS_INPUT output = (PS_INPUT)0;

	output.Pos = mul(input.Pos, world);
	output.Pos = mul(output.Pos, view);
	output.Pos = mul(output.Pos, projection);

	output.Tex = input.Tex;
	output.Nor = input.Nor;
	output.Col = input.Col;

	return output;
}