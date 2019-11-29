cbuffer alpha_buffer : register(b0)
{
    float alpha;
}

struct PS_INPUT
{
    float4 inPosition : SV_POSITION;
    float2 inTexcoord : TEXCOORD;
	int slot : TEXSLOT;
};

Texture2D objTexture : TEXTURE : register(t0);
Texture2D anotherTexture: TEXTURE: register(t1);
Texture2D anotherTexture2: TEXTURE: register(t2);
SamplerState objSamplerState : SAMPLER : register(s0);
SamplerState objSamplerState1 : SAMPLER: register(s1);
SamplerState objSamplerState2 : SAMPLER: register(s2);

float4 main(PS_INPUT input) : SV_Target
{
	float3 pixel_color;
	if (input.slot == 0)
	{
		pixel_color = objTexture.Sample(objSamplerState, input.inTexcoord);
	}
	if (input.slot == 1)
	{
		pixel_color = anotherTexture.Sample(objSamplerState, input.inTexcoord);
	}
	if (input.slot == 2)
	{
		pixel_color = anotherTexture2.Sample(objSamplerState, input.inTexcoord);
	}

    return float4(pixel_color , alpha);
}
