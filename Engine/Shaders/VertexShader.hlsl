cbuffer cbuf
{
    float4x4 mat;
};

float4 main( float3 pos : POSITION ) : SV_Position
{
    return mul(mat, float4(pos, 1.0f));
}