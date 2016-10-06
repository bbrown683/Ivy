struct VS_INPUT
{
	float4 Pos : POSITION;
	float2 Tex : TEXCOORD0;
    float4 Col : COLOR;
};

struct PS_INPUT
{
	float4 Pos : SV_POSITION;
	float2 Tex : TEXCOORD0;
    float4 Col : COLOR;
};

PS_INPUT main(VS_INPUT input)
{
	PS_INPUT output = (PS_INPUT)0;

	output.Pos = input.Pos;
	output.Tex = input.Tex;
    output.Col = input.Col;

	return output;
}