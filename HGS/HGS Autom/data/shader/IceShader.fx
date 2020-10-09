//------------------------------------------------------------------------------
//
//氷のシェーダ [IceShader.fx]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#include "ShaderFanction.h"

//------------------------------------------------------------------------------
//ピクセルシェーダ
//------------------------------------------------------------------------------
float4 mainPS(PSInput input) : COLOR
{
	//カメラのベクトル 向いてる方向
	float3 CameraVec = float3(g_ViewMatrix._31,g_ViewMatrix._32,g_ViewMatrix._33);

	//アルファ値　内積を使って外向いてる時は薄く　こっち向いてる時は濃くする
	float fAlpha = (1 - abs(dot(CameraVec, input.WorldNormal))) * 0.5;

	//return ライティングの計算します
	return float4(0.7,0.8,1.0,fAlpha) * CalcLighting(input);
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