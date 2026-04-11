cbuffer cbuf {
	float4x4 mat;
};

struct VSIn {
	float3 pos : POSITION;
	float2 uv : TEXCOORD;
};

struct VSOut
{
    float4 pos : SV_POSITION;
    float2 uvCoord : TEXCOORD;
};


VSOut main(VSIn input) {
	VSOut output;
	output.pos = mul(mat, float4(input.pos, 1.0f));
	output.uvCoord = input.uv;

	return output;
}