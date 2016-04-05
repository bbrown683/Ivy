Texture2D txDiffuse;
SamplerState samLinear;

struct PS_INPUT
{
	float4 Pos : SV_POSITION;
	float2 Tex : TEXCOORD0;
};

//--------------------------------------------------------------------------------------
// Pixel Shader Program
//--------------------------------------------------------------------------------------
float4 Main(PS_INPUT input) : SV_TARGET
{
	// Sample the pixel color from the texture using the sampler at this texture coordinate location.
	return txDiffuse.Sample(samLinear, input.Tex);
}