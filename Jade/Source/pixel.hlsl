Texture2D txDiffuse : register(t0);
SamplerState samLinear;

struct PS_INPUT
{
	float4 Pos : SV_POSITION;
	float2 Tex : TEXCOORD0;
	float3 Nor : NORMAL;
	float4 Col : COLOR;
};

//--------------------------------------------------------------------------------------
// Pixel Shader Program
//--------------------------------------------------------------------------------------
float4 Main(PS_INPUT input) : SV_TARGET
{
	return txDiffuse.Sample(samLinear, input.Tex);
}