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
shared float4x4 g_ViewMatrix;				//カメラのビュー
shared float4x4 g_ProjectionMatrix;			//カメラのプロジェクション
shared float3 g_LightDirection[3];			//ライティングの方向
shared float4 g_LightColor[3];				//ライティングの色
shared float g_fCount;						//1ずつ加算されている

float4x4 g_WorldMatrix;				//オブジェクトのマトリックス

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
	float4 InputColor : COLOR0;				//入力色
	float4 InputColor01 : COLOR1;				//入力色
	float3 diffuse : DIFFUSE;			//ディフューズカラー
};

//頂点シェーダ　出力
struct VSOutput
{
	float4 WorldPos : POSITION;				//ワールド座標
	float3 WorldNormal : TEXCOORD1;			//ワールド法線
	float4 WorldPixelPos : TEXCOORD2;		//ローカル座標
	float4 TexUV : TEXCOORD0;				//テクスチャUV
	float4 OutputColor : COLOR;			//出力の色
	float4 DiffuseColor : COLOR1;			//ディフューズカラー
	float4 SpecularColor : COLOR2;			//スペキュラーカラー
};

//ピクセルシェーダ　入力
struct PSInput
{
	float4 WorldPixelPos : TEXCOORD2;		//ローカル座標
	float3 WorldNormal : TEXCOORD1;			//ワールド法線
	float4 TexUV : TEXCOORD0;				//テクスチャ
	float4 OutputColor : COLOR1;			//出力の色
	float4 DiffuseColor : COLOR1;			//ディフューズカラー
	float4 SpecularColor : COLOR2;			//スペキュラー
};


//------------------------------------------------------------------------------
//テクスチャ張り付ける
//------------------------------------------------------------------------------
float4 TexturePixelShader(inout PSInput input) : COLOR
{
	//テクスチャを基にピクセルの色を決める
	float4 TexColor = tex2D( TextureSampler, input.TexUV );
	return TexColor;
}

//------------------------------------------------------------------------------
//ライティングの計算
//------------------------------------------------------------------------------
float4 CalcDiffuseLighting(float3 normal : NORMAL)
{
	//ライトと法線から明るさを計算
	float LightPower[3];
	LightPower[0] = clamp( dot( normalize(-g_LightDirection[0]), normalize( normal)),0.0f,1.0f);
	LightPower[1] = clamp( dot( normalize(-g_LightDirection[1]), normalize( normal)),0.0f,1.0f);
	LightPower[2] = clamp( dot( normalize(-g_LightDirection[2]), normalize( normal)),0.0f,1.0f);

	//ライトの強さとライトの色を合成
	float4 outputLightPower = ((g_LightColor[0] * LightPower[0]) + (g_LightColor[1] * LightPower[1]) + (g_LightColor[2] * LightPower[2]));

	//a値を1にしとく
	outputLightPower.a = 1.0;

	//return
	return outputLightPower;
}

//------------------------------------------------------------------------------
//スペキュラーの計算
//------------------------------------------------------------------------------
float4 CalcSpecular(float3 normal : NORMAL)
{
	//ライトとカメラの中間のベクトル ライト3つ分
	float3 HarfVector[3];

	//スペキュラーはメインライトのみ計算
	//ライトとカメラのベクトルとの中間のベクトルを算出
	HarfVector[0] = normalize(-g_LightDirection[0] - float3(g_ViewMatrix._13,g_ViewMatrix._23,g_ViewMatrix._33));
	HarfVector[1] = normalize(-g_LightDirection[1] - float3(g_ViewMatrix._13,g_ViewMatrix._23,g_ViewMatrix._33));
	HarfVector[2] = normalize(-g_LightDirection[2] - float3(g_ViewMatrix._13,g_ViewMatrix._23,g_ViewMatrix._33));

	//スペキュラー色計算　
	//中間のベクトルと法線が近いと色濃くなる
	float4 SpecularColor =
		(g_SpecularColor * dot(HarfVector[0],normalize(normal)) * g_LightColor[0]) +
		(g_SpecularColor * dot(HarfVector[1],normalize(normal)) * g_LightColor[1]) +
		(g_SpecularColor * dot(HarfVector[2],normalize(normal)) * g_LightColor[2]);

	//return
	return pow(SpecularColor,g_Power);
}
//------------------------------------------------------------------------------
//モデルのマテリアルカラー取得
//法線を入力すればライティング系の計算全部する
//------------------------------------------------------------------------------
float4 GetModelMaterialColor(float3 normal : NORMAL)
{
	//ライティング系の計算を一通りしておく　スペキュラーも
	return (g_DiffuseColor * CalcDiffuseLighting(normal)) + g_EmissiveColor + g_Ambient + CalcSpecular(normal);
}


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

	float4 color = float4(diffuse.xyz,1.0f);

	// output.OutputColor = float4(1,1,0,1);

	//ローカル座標をワールド座標に変換
	// output.TexUV = input.TexUV;

	// output.OutputColor = GetModelMaterialColor(output.WorldNormal);

	// output.OutputColor = input.InputColor01;

	// output.DiffuseTexColor = input.diffuse;

	// float4 Color = input.DiffuseColor;

	// output.OutputColor = Color;

	// output.OutputColor = input.InputColor01;

		// input.DiffuseColor.r = 0.0;
	// output.OutputColor = float4(1.0,0.0,0.0,1.0);

	//return
	return output;
}