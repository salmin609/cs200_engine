cbuffer alpha_buffer : register(b0)
{
    float alpha;
}

struct PS_INPUT
{
    float4 inPosition : SV_POSITION;
    float2 inTexcoord : TEXCOORD;
};

Texture2D objTexture : TEXTURE : register(t0);
SamplerState objSamplerState : SAMPLER : register(s0);

float4 main(PS_INPUT input) : SV_Target
{
    float3 pixel_color = objTexture.Sample(objSamplerState, input.inTexcoord);
    return float4(pixel_color , alpha);
}
