Texture2D texture2d : register(t0);
SamplerState samplerState : register(s0);

cbuffer cbuf
{
    float4 color;
    int useTexture;
//    int3 padding;
};

struct PSIn
{
    float4 pos : SV_Position;
    float3 normal : NORMAL;
    float2 uv : TEXCOORD0;
};

float4 main(PSIn input) : SV_Target
{
    float4 outColor = color;
    if (useTexture == 1)
        outColor *= texture2d.Sample(samplerState, input.uv);
    
    return outColor;
}