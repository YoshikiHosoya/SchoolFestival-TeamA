//------------------------------------------------------------------------------
//
//シェーダー  [Shader.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _SHADER_H_
#define _SHADER_H_
//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "main.h"

//------------------------------------------------------------------------------
//クラス定義
//------------------------------------------------------------------------------

//シェーダーのハンドルのクラス
class CShaderHandle
{
public:
	CShaderHandle() {};
	~CShaderHandle() {};
	//シェーダーのグローバル変数のハンドル
	D3DXHANDLE m_hViewMtx;				//ビューマトリックス
	D3DXHANDLE m_hProjectionMtx;		//プロジェクションマトリックス
	D3DXHANDLE m_hLightDir0;			//光源の向き
	D3DXHANDLE m_hLightDir1;			//光源の向き
	D3DXHANDLE m_hLightDir2;			//光源の向き
	D3DXHANDLE m_hLightCol0;			//光の色
	D3DXHANDLE m_hLightCol1;			//光の色
	D3DXHANDLE m_hLightCol2;			//光の色
	D3DXHANDLE m_hCount;				//カウント

};
//シェーダーのハンドルのクラス
//モデル色のハンドル
class CShaderHandle_ModelColor
{
public:
	D3DXHANDLE m_hDiffuseCol;		//拡散光
	D3DXHANDLE m_hSpecularCol;		//反射光
	D3DXHANDLE m_hEmissiveCol;		//放射光
	D3DXHANDLE m_Ambient;			//環境光
	D3DXHANDLE m_hPower;			//反射の強さ
};


class CShader
{
public:
	enum SHADER_TYPE
	{
		SHADER_NONE = -1,
		SHADER_MODELDRAW,
		SHADER_MAX,
	};

	CShader();
	~CShader();

	static void SetParamaterShader();
	static void InitStaticParam();
	static void UpdateStaticParam();
	static std::unique_ptr<CShader> Create();
	static HRESULT Load();
	static void UnLoad();
	ID3DXEffect *GetEffectPtr() { return m_pShaderEffect[m_type]; };
	static void SetModelColor(D3DXCOLOR DiffuseCol, D3DXCOLOR SpeculerCol, D3DXCOLOR EmissiveCol, D3DXCOLOR AmbientCol, float fPower);

	void SetType(SHADER_TYPE type)		{ m_type = type; };

private:
	static std::vector<ID3DXEffect*> m_pShaderEffect;								//シェーダーのエフェクトのポインタのリスト
	static std::vector<std::string> m_ShaderFileNameList;							//シェーダーのファイル名のリスト
	static std::vector<std::unique_ptr<CShaderHandle>> m_ShaderHandleList;			//シェーダーのハンドルのリスト
	static std::unique_ptr<CShaderHandle_ModelColor> m_pModelColorHandle;
	SHADER_TYPE m_type;
	static int m_nCnt;





	static void GetGlobalHandle();

};
#endif