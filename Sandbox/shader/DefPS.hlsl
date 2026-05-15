cbuffer cbuf {
    float4 color;
}

struct VSOut {
    float4 position: SV_POSITION;
    float3 normal : NORMAL;
    float2 uv : TEXCOORD;
};

float4 main(VSOut input) : SV_TARGET
{
    return color;
}