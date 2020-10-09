//------------------------------------------------------------------------------
//
//シェーダーの機能 [ShaderFanction.h]
//共通でつかう変数や関数を格納しておく
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

////------------------------------------------------------------------------------
//グローバル宣言
//------------------------------------------------------------------------------
float4x4 g_ViewMatrix;				//カメラのビュー
float4x4 g_ProjectionMatrix;		//カメラのプロジェクション
float4x4 g_WorldMatrix;				//オブジェクトのマトリックス
float3 g_LightDirection[3];			//ライティングの方向
float4 g_LightColor[3];				//ライティングの色
float g_fCount;						//1ずつ加算されている
float4 g_DiffuseColor;				//デフューズカラー	拡散光
float4 g_SpecularColor;				//スペキュラーカラー	反射光
float4 g_EmissiveColor;				//エミッションカラー	放射光
float4 g_Ambient;					//アンビエントカラー	環境光
float g_Power;						//パワー			反射の強さ

//テクスチャ 外からセットされる
texture pTex;

//サンプラーのテクスチャ　これに変換しないと描画できない
sampler TextureSampler = sampler_state
{
	texture = <pTex>;
};

//------------------------------------------------------------------------------
//構造体宣言
//------------------------------------------------------------------------------
//頂点シェーダ　入力
struct VSInput
{
	float4 LocalPos : POSITION;				//ローカル座標
	float3 LocalNormal : NORMAL;			//ローカル法線
	float4 TexUV : TEXCOORD0;				//テクスチャ
};

//頂点シェーダ　出力
struct VSOutput
{
	float4 WorldPos : POSITION;				//ワールド座標
	float3 WorldNormal : TEXCOORD1;			//ワールド法線 ピクセルシェーダに渡す用
	float4 WorldPixelPos : TEXCOORD2;		//ローカル座標
	float4 TexUV : TEXCOORD0;				//テクスチャ
};

//ピクセルシェーダ　入力
struct PSInput
{
	float4 WorldPixelPos : TEXCOORD2;		//ローカル座標
	float3 WorldNormal : TEXCOORD1;			//ワールド法線
	float4 TexUV : TEXCOORD0;				//テクスチャ
	float4 Color : COLOR;					//色
};

//------------------------------------------------------------------------------
//ベース処理
//座標を射影座標に変換
//法線設定
//テクスチャUV設定
//------------------------------------------------------------------------------
VSOutput BaseVertexShader(VSInput input)
{
	//変数宣言　初期化
	VSOutput output = (VSOutput)0;

	//ワールドマトリックスをビューマトリックスに変換
	float4x4 ViewMatrix = mul(g_WorldMatrix,g_ViewMatrix);

	//射影行列変換
	output.WorldPos = mul( float4(input.LocalPos.xyz, 1.0), ViewMatrix );

	//プロジェクションマトリックス計算
	output.WorldPos = mul( output.WorldPos, g_ProjectionMatrix );

	//法線設定
	output.WorldNormal = mul(input.LocalNormal,g_WorldMatrix);

	//ローカル座標
	output.WorldPixelPos = mul( float4(input.LocalPos.xyz, 1.0), g_WorldMatrix );

	//ローカル座標をワールド座標に変換
	output.TexUV = input.TexUV;

	//return
	return output;
}
//------------------------------------------------------------------------------
//テクスチャ張り付ける
//------------------------------------------------------------------------------
float4 TexturePixelShader(inout PSInput input) : COLOR
{
	//テクスチャを基にピクセルの色を決める
	float4 TexColor = tex2D( TextureSampler, input.TexUV );
	input.Color = TexColor;
	return TexColor;
}

//------------------------------------------------------------------------------
//ライティングの計算
//------------------------------------------------------------------------------
float4 CalcLighting(inout PSInput input) : COLOR
{
	//ライトと法線から明るさを計算
	float LightPower[3];
	LightPower[0] = clamp( dot( normalize(-g_LightDirection[0]), normalize( input.WorldNormal)),0.0f,1.0f);
	LightPower[1] = clamp( dot( normalize(-g_LightDirection[1]), normalize( input.WorldNormal)),0.0f,1.0f);
	LightPower[2] = clamp( dot( normalize(-g_LightDirection[2]), normalize( input.WorldNormal)),0.0f,1.0f);

	//ライトの強さとライトの色を合成
	float4 outputLightPower = ((g_LightColor[0] * LightPower[0]) + (g_LightColor[1] * LightPower[1]) + (g_LightColor[2] * LightPower[2]));

	//a値を1にしとく
	outputLightPower.a = 1.0;

	//inputの値に乗算
	input.Color *= outputLightPower;

	//return
	return outputLightPower;
}

//------------------------------------------------------------------------------
//スペキュラーの計算
//------------------------------------------------------------------------------
float4 CalcSpecular(inout PSInput input) : COLOR
{

	//スペキュラーはメインライトのみ計算
	//ライトとカメラのベクトルとの中間のベクトルを算出
	float3 HarfVector = normalize(-g_LightDirection[0] - float3(g_ViewMatrix._13,g_ViewMatrix._23,g_ViewMatrix._33));

	//スペキュラー色計算　
	//中間のベクトルと法線が近いと色濃くなる
	float4 SpecularColor = clamp( (g_SpecularColor * 1.98) * dot(HarfVector,normalize(input.WorldNormal)),0.0,1.0);

	//inputの値に加算
	input.Color += pow(SpecularColor,g_Power);

	//return
	return SpecularColor;
}
//------------------------------------------------------------------------------
//ベースカラーで出力
//------------------------------------------------------------------------------
float4 ModelMaterialColor(inout PSInput input) : COLOR
{
	//DiffuseColor + EmissionColor　マテリアルの色設定
	input.Color = g_DiffuseColor + g_EmissiveColor + g_Ambient;
	return g_DiffuseColor;
}
//------------------------------------------------------------------------------
//サークルの計算用 0か1かを返すだけ
//------------------------------------------------------------------------------
float CalcCircleRange(PSInput input)
{
	//サークル
	float dist = distance(float3(0.0,0.0,0.0), input.WorldPixelPos.xyz) * 0.1;	//ピクセルの頂点と原点の距離　　円の広がる速度
	float distCycle = dist + g_fCount * -1.0;									//Countを加算 円を動いているように見せる -をかけたら外側に広がっていく　+なら内側に集まっていく
	float Value = sin(distCycle * 0.005f);										//Sin関数で-1～1の間に収める 波 円の間隔
	float ColorPower = step(0.5, Value);										//0か1に変換 	円の太さ

	//return
	return ColorPower;
}
//------------------------------------------------------------------------------
//サークルを描く
//オーバーライド用
//------------------------------------------------------------------------------
float4 OverrideDrawCircle(inout PSInput input) : COLOR
{
	//テクスチャの色　ライティングの分も含める
	float4 TexColor = input.Color;

	//計算処理　0か1かが入っている
	float ColorPower = CalcCircleRange(input);

	//円の色
	// float4 CircleColor = float4(0.8,1.0,0.0,1.0);

	//テクスチャの色と合成
	// TexColor += (CircleColor * ColorPower);

	//反転
	TexColor = ColorPower <= 0 ?
			TexColor:
			1.0 - TexColor;

	TexColor.a = 1.0;

	//return
	return TexColor;
}

