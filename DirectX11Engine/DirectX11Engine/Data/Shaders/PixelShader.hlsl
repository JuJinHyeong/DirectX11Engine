cbuffer lightBuffer : register(b0)
{
    float3 ambientLightColor;
    float ambientLightStrength;
    
    float3 dynamicLightColor;
    float dynamicLightStrength;
    float3 dynamicLightPosition;
    
    float dynamicLightAttenuationConstant;
    float dynamicLightAttenuationLinear;
    float dynamicLightAttenuationExp;
}

struct PS_INPUT
{
    float4 inPosition : SV_POSITION;
    float2 inTexCoord : TEXCOORD;
    float3 inNormal : NORMAL;
    float3 inWorldPosition : WORLD_POSITION;
};

Texture2D objTexture : TEXTURE : register(t0);
SamplerState objSamplerState : SAMPLER : register(s0);

float4 main(PS_INPUT input) : SV_Target
{
    float3 sampleColor = objTexture.Sample(objSamplerState, input.inTexCoord);
    
    float3 ambientLight = ambientLightColor * ambientLightStrength;
    
    float3 vectorToLight = normalize(dynamicLightPosition - input.inWorldPosition);
    
    float3 diffuseLightIntensity = max(dot(vectorToLight, input.inNormal), 0);
    
    float dist = distance(dynamicLightPosition, input.inWorldPosition);
    
    float attneuationFactor = 1 / (dynamicLightAttenuationConstant + dynamicLightAttenuationLinear * dist + dynamicLightAttenuationExp * dist * dist);
    
    diffuseLightIntensity *= attneuationFactor;
    
    float3 diffuseLight = diffuseLightIntensity * dynamicLightStrength * dynamicLightColor;
    
    float3 appliedLight = ambientLight + diffuseLight;
    
    float3 finalColor = sampleColor * appliedLight;
    
    return float4(finalColor, 1.0f);
}