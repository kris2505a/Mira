Texture2D diffuseTexture : register(t0);
SamplerState samplerState : register(s0);

cbuffer cbuf {
    float4 color;
    int hasTexture;
    float3 padding;
};

struct VSOut {
    float4 position: SV_POSITION;
    float3 normal : NORMAL;
    float2 uv : TEXCOORD;
};

float4 main(VSOut input) : SV_TARGET
{
    if (hasTexture == 1) {
        return diffuseTexture.Sample(
            samplerState,
            input.uv
        );
    
    }
    return color;
}