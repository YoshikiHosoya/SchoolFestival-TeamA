//------------------------------------------------------------------------------
//
//円を描くシェーダ [CircleShader.fx]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#include "ShaderFanction.h"

//------------------------------------------------------------------------------
//ピクセルシェーダ
//------------------------------------------------------------------------------
float4 mainPS(PSInput input) : COLOR
{
	//テクスチャの色　ライティングの分も含める
	ModelMaterialColor(input);

	//ライティング計算
	CalcLighting(input);

	//	スペキュラー計算
	CalcSpecular(input);

	//サークルシェーダー
	float4 TexColor = OverrideDrawCircle(input);

	//return
	return TexColor;
	
	// return input.Color;
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