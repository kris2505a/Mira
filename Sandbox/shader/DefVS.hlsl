cbuffer cb : register(b0)
{
    float4x4 invModel;
    float4x4 mvp;
};

struct VSIn
{
    float3 pos : POSITION;
    float3 normal : NORMAL;
    float2 uv : TEXCOORD0;
};

struct VSOut
{
    float4 pos : SV_Position;
    float3 normal : NORMAL;
    float2 uv : TEXCOORD0;
};

VSOut main(VSIn input) {
    VSOut output;
    output.pos = mul(float4(input.pos, 1.0f), mvp);
    output.normal = normalize(mul(input.normal, (float3x3) invModel));
    output.uv = input.uv;
    
    return output;
}