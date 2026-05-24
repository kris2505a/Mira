struct VSIn {
    float3 pos : POSITION;
    float3 normal : NORMAL;
    float2 uv : TEXCOORD;
};

struct VSOut {
    float4 position: SV_POSITION;
    float3 normal : NORMAL;
    float2 uv : TEXCOORD;
};

cbuffer cbuf {
    column_major float4x4 mvp;
    column_major float4x4 model;
}

VSOut main(VSIn input) {
    VSOut output;
    output.position = mul(mvp, float4(input.pos, 1.0f));
    output.normal = input.normal;
    output.uv = input.uv;

    return output;
}
