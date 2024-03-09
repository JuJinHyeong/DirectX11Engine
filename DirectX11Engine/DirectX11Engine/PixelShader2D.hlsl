struct PS_INPUT
{
    float4 inPosition : SV_Position;
    float2 inTexCoord : TEXCOORD;
};

Texture2D objTexture : TEXTURE : register(t0);
SamplerState objSamplerState : SAMPLER : register(s0);

float4 main(PS_INPUT input) : SV_TARGET
{
    float4 samplerColor = objTexture.Sample(objSamplerState, input.inTexCoord);
    return samplerColor;
}