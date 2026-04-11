cbuffer cb {
	int useTexture;
	float3 padding;
}

Texture2D tex : register(t0);
SamplerState samp : register(s0);

struct VSOut
{
    float4 pos : SV_POSITION;
    float2 uvCoord : TEXCOORD;
};

float4 main(VSOut input) : SV_TARGET {
	if(useTexture == 0) {
		return float4(1.0f, 0.0f, 0.0f, 1.0f);
	}
	return tex.Sample(samp, input.uvCoord);

}