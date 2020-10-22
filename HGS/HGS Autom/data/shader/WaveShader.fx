//------------------------------------------------------------------------------
//
//氷のシェーダ [IceShader.fx]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#include "ShaderFanction.h"

//------------------------------------------------------------------------------
//頂点シェーダ
//------------------------------------------------------------------------------
VSOutput mainVS(VSInput input)
{
	VSOutput output = (VSOutput)0;

	output = BaseVertexShader(input);

	float amp = 100 * sin(g_fCount * 0.05 + (output.WorldPixelPos.x * 0.01f));

	output.WorldPos.y += amp;

	return output;
}

//------------------------------------------------------------------------------
//ピクセルシェーダ
//------------------------------------------------------------------------------
float4 mainPS(PSInput input) : COLOR
{
	return TexturePixelShader(input);
}

//------------------------------------------------------------------------------
//テクニック
//------------------------------------------------------------------------------
technique technique0
{
	//パス0
	pass p0
	{
		//カリングモード
		CullMode = CCW;

		//頂点シェーダ
		VertexShader = compile vs_3_0 mainVS();

		//ピクセルシェーダ
		PixelShader = compile ps_3_0 mainPS();
	}
}