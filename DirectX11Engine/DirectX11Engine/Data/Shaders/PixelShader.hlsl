struct PS_INPUT
{
    float4 inPos : SV_POSITION;
    float4 inColor : COLOR;
};

float4 main(PS_INPUT input) : SV_Target {
    return input.inColor;
}