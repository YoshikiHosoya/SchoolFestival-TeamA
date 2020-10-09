//------------------------------------------------------------------------------
//
//氷のシェーダ [MeshFieldShader.fx]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#include "ShaderFanction.h"

//------------------------------------------------------------------------------
//ピクセルシェーダ
//------------------------------------------------------------------------------
float4 mainPS(PSInput input) : COLOR
{
	//テクスチャの色設定
	TexturePixelShader(input);

	//ライティング計算
	CalcLighting(input);

	//サークルシェーダー
	float4 TexColor = OverrideDrawCircle(input);

	//return
	return TexColor;
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
		VertexShader = compile vs_3_0 BaseVertexShader();

		//ピクセルシェーダ
		PixelShader = compile ps_3_0 mainPS();
	}
}