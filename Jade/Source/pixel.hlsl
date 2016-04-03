Texture2D txDiffuse : register(t0);
SamplerState samLinear : register(s0);

struct PS_INPUT
{
	float4 pos : SV_POSITION;
	float3 nor : NORMAL;
	float2 tex : TEXCOORD;
};

//--------------------------------------------------------------------------------------
// Pixel Shader Program
//--------------------------------------------------------------------------------------
float4 Main(PS_INPUT input) : SV_TARGET
{
	return txDiffuse.Sample(samLinear, input.tex);
}