struct PS_IN {
	float4 Pos : SV_POSITION;
	float3 Color : COLOR;
};


float4 main(PS_IN input) : SV_TARGET
{
	return float4(input.Color, 0);
}