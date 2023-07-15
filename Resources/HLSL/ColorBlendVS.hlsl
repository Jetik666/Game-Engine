cbuffer CBuf
{
    matrix transform;
};

struct VSOut
{
    float4 color : COLOR;
    float4 pos : SV_Position;
};

VSOut main(float3 pos : POSITIONT, float4 color : Color)
{
    VSOut vso;
    vso.pos = mul(float4(pos, 1.0f), transform);
    vso.color = color;
    return vso;
}