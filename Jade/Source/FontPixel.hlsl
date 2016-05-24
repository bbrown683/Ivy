Texture2D fontTexture;
SamplerState fontSampler;

struct PS_INPUT
{
	float4 Pos : SV_POSITION;
	float2 Tex : TEXCOORD0;
};

float4 main(PS_INPUT input) : SV_TARGET
{
	return fontTexture.Sample(fontSampler, input.Tex);
}