cbuffer my_buffer : register(b0)
{
    float4x4 mat;
};

struct VS_INPUT
{
    float3 inPos : POSITION;
    float2 inTexCoord : TEXCOORD;
	int slot : SLOT;
	float3 inColor : COLOR;
	int isColor : ISCOLOR;
};

struct VS_OUTPUT
{
    float4 outPosition : SV_POSITION;
    float2 outTexCoord : TEXCOORD;
	int texslot : TEXSLOT;
	float3 outColor : COLOR;
	int isColor : ISCOLOR;
};

VS_OUTPUT main(VS_INPUT input, uint instance_id : SV_InstanceID)
{
    VS_OUTPUT output;
    output.outPosition = mul(float4(input.inPos.x + (instance_id % 100), input.inPos.y + (instance_id / 100), input.inPos.z, 1.0f), mat);
    output.outTexCoord = input.inTexCoord;
	output.texslot = input.slot;
	output.outColor = input.inColor;
	output.isColor = input.isColor;

    return output;
}