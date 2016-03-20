//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------
cbuffer ConstantBuffer : register(b0)
{
	matrix World;
	matrix View;
	matrix Projection;
}

//--------------------------------------------------------------------------------------
// Vertex Shader Variables
//--------------------------------------------------------------------------------------
struct VOut
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
};

//--------------------------------------------------------------------------------------
// Vertex Shader Program
//--------------------------------------------------------------------------------------
VOut Main(float4 position : POSITION, float4 color : COLOR)
{
	VOut output;

	//output.position = position;
	output.position = mul(position, World);
	output.position = mul(output.position, View);
	output.position = mul(output.position, Projection);
	output.color = color;

	return output;
}