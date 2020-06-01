//------------------------------------------------------------------------------
//
//シェーダー  [Shader.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "shader.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "light.h"

//------------------------------------------------------------------------------
//静的メンバ変数の初期化
//------------------------------------------------------------------------------
int CShader::m_nCnt = 0;
std::vector<ID3DXEffect*> CShader::m_pShaderEffect = {};
std::vector<std::unique_ptr<CShaderHandle>> CShader::m_ShaderHandleList = {};
std::unique_ptr<CShaderHandle_ModelColor> CShader::m_pModelColorHandle = nullptr;
std::vector<std::string> CShader::m_ShaderFileNameList =
{
	{ "data/shader/ModelDrawShader.fx" },
};
//------------------------------------------------------------------------------
//マクロ
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//コンストラクタ
//------------------------------------------------------------------------------
CShader::CShader()
{
}

//------------------------------------------------------------------------------
//デストラクタ
//------------------------------------------------------------------------------
CShader::~CShader()
{
}

//------------------------------------------------------------------------------
//パラメータ設定
//------------------------------------------------------------------------------
void CShader::SetParamaterShader()
{
	//nullcheck
	if (!m_pShaderEffect.empty())
	{
		//エフェクトのサイズ分
		for (size_t nCnt = 0; nCnt < m_pShaderEffect.size(); nCnt++)
		{
			//ハンドルを利用して高速化
			//それぞれの値を更新
			m_pShaderEffect[nCnt]->SetMatrix(m_ShaderHandleList[nCnt]->m_hViewMtx, &CManager::GetRenderer()->GetCamera()->GetMtxView());
			m_pShaderEffect[nCnt]->SetMatrix(m_ShaderHandleList[nCnt]->m_hProjectionMtx, &CManager::GetRenderer()->GetCamera()->GetMtxProjection());
			m_pShaderEffect[nCnt]->SetVector(m_ShaderHandleList[nCnt]->m_hLightDir0, &D3DXVECTOR4(CManager::GetRenderer()->GetLight()->GetLightDir(0), 0.0f));
			m_pShaderEffect[nCnt]->SetVector(m_ShaderHandleList[nCnt]->m_hLightDir1, &D3DXVECTOR4(CManager::GetRenderer()->GetLight()->GetLightDir(1), 0.0f));
			m_pShaderEffect[nCnt]->SetVector(m_ShaderHandleList[nCnt]->m_hLightDir2, &D3DXVECTOR4(CManager::GetRenderer()->GetLight()->GetLightDir(2), 0.0f));
			m_pShaderEffect[nCnt]->SetVector(m_ShaderHandleList[nCnt]->m_hLightCol0, &D3DXVECTOR4(CManager::GetRenderer()->GetLight()->GetLightColor(0)));
			m_pShaderEffect[nCnt]->SetVector(m_ShaderHandleList[nCnt]->m_hLightCol1, &D3DXVECTOR4(CManager::GetRenderer()->GetLight()->GetLightColor(1)));
			m_pShaderEffect[nCnt]->SetVector(m_ShaderHandleList[nCnt]->m_hLightCol2, &D3DXVECTOR4(CManager::GetRenderer()->GetLight()->GetLightColor(2)));
			m_pShaderEffect[nCnt]->SetFloat (m_ShaderHandleList[nCnt]->m_hCount, (float)m_nCnt);
		}
	}
}

//------------------------------------------------------------------------------
//静的なパラメータ初期化 カウントとか
//------------------------------------------------------------------------------
void CShader::InitStaticParam()
{
	m_nCnt = 0;
}

//------------------------------------------------------------------------------
//静的なパラメータ更新 カウントとか
//------------------------------------------------------------------------------
void CShader::UpdateStaticParam()
{
	//カウントアップ
	m_nCnt++;

	//シェーダーにパラメータ設定
	SetParamaterShader();
}

//------------------------------------------------------------------------------
//生成処理
//------------------------------------------------------------------------------
std::unique_ptr<CShader> CShader::Create()
{
	//メモリ確保
	std::unique_ptr<CShader> pShader(new CShader);

	//nullcheck
	if (pShader)
	{
		return pShader;
	}
	return nullptr;
}

//------------------------------------------------------------------------------
//シェーダー生成
//------------------------------------------------------------------------------
HRESULT CShader::Load()
{
	//成功したかどうか
	HRESULT hr = S_OK;

	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//エフェクトのポインタ　仮
	ID3DXEffect *pEffect;
	for (int nCnt = 0; nCnt < CShader::SHADER_MAX; nCnt++)
	{
		//シェーダー読み込み
		if (FAILED(D3DXCreateEffectFromFile(
			pDevice,
			m_ShaderFileNameList[nCnt].data(),
			NULL,
			NULL,
			D3DXSHADER_DEBUG,
			NULL,
			&pEffect,
			NULL
		)))
		{
			//失敗
			std::cout << "Shader読みこみ失敗 - " << m_ShaderFileNameList[nCnt].data() << NEWLINE;
			hr = E_FAIL;
		}
		else
		{
			//配列に追加
			std::cout << "Shader - " << m_ShaderFileNameList[nCnt].data() << NEWLINE;
			m_pShaderEffect.emplace_back(pEffect);

			if (nCnt == CShader::SHADER_MODELDRAW)
			{
				//メモリ確保
				m_pModelColorHandle.reset(new CShaderHandle_ModelColor);

				//ハンドル取得
				m_pModelColorHandle->m_hDiffuseCol	= m_pShaderEffect[nCnt]->GetParameterByName(NULL, "g_DiffuseColor");		//拡散光
				m_pModelColorHandle->m_hSpecularCol = m_pShaderEffect[nCnt]->GetParameterByName(NULL, "g_SpecularColor");	//反射光
				m_pModelColorHandle->m_hEmissiveCol = m_pShaderEffect[nCnt]->GetParameterByName(NULL, "g_EmissiveColor");	//放射光
				m_pModelColorHandle->m_Ambient		= m_pShaderEffect[nCnt]->GetParameterByName(NULL, "g_Ambient");			//環境光
				m_pModelColorHandle->m_hPower		= m_pShaderEffect[nCnt]->GetParameterByName(NULL, "g_Power");			//反射の強
			}
		}
	}

	GetGlobalHandle();

	return hr;
}

//------------------------------------------------------------------------------
//シェーダー破棄
//------------------------------------------------------------------------------
void CShader::UnLoad()
{
	//for
	for (size_t nCnt = 0; nCnt < m_pShaderEffect.size(); nCnt++)
	{
		//開放
		m_pShaderEffect[nCnt]->Release();
		m_pShaderEffect[nCnt] = nullptr;
	}

	//配列開放
	m_pShaderEffect.clear();
}

//------------------------------------------------------------------------------
//シェーダーのグローバル変数のハンドル取得
//------------------------------------------------------------------------------
void CShader::GetGlobalHandle()
{
	//シェーダーのエフェクト数分
	for (size_t nCnt = 0; nCnt < m_pShaderEffect.size(); nCnt++)
	{
		//メモリ確保 + 配列に追加
		m_ShaderHandleList.emplace_back(new CShaderHandle);

		//ハンドル取得
		m_ShaderHandleList[nCnt]->m_hViewMtx		= m_pShaderEffect[nCnt]->GetParameterByName(NULL, "g_ViewMatrix");			//ビューマトリックス
		m_ShaderHandleList[nCnt]->m_hProjectionMtx	= m_pShaderEffect[nCnt]->GetParameterByName(NULL, "g_ProjectionMatrix");	//プロジェクションマトリックス
		m_ShaderHandleList[nCnt]->m_hLightDir0		= m_pShaderEffect[nCnt]->GetParameterByName(NULL, "g_LightDirection[0]");	//光源の向き
		m_ShaderHandleList[nCnt]->m_hLightDir1		= m_pShaderEffect[nCnt]->GetParameterByName(NULL, "g_LightDirection[1]");	//光源の向き
		m_ShaderHandleList[nCnt]->m_hLightDir2		= m_pShaderEffect[nCnt]->GetParameterByName(NULL, "g_LightDirection[2]");	//光源の向き
		m_ShaderHandleList[nCnt]->m_hLightCol0		= m_pShaderEffect[nCnt]->GetParameterByName(NULL, "g_LightColor[0]");		//光の色
		m_ShaderHandleList[nCnt]->m_hLightCol1		= m_pShaderEffect[nCnt]->GetParameterByName(NULL, "g_LightColor[1]");		//光の色
		m_ShaderHandleList[nCnt]->m_hLightCol2		= m_pShaderEffect[nCnt]->GetParameterByName(NULL, "g_LightColor[2]");		//光の色
		m_ShaderHandleList[nCnt]->m_hCount			= m_pShaderEffect[nCnt]->GetParameterByName(NULL, "g_fCount");				//カウント
	}
}

//------------------------------------------------------------------------------
//モデルの色設定
//------------------------------------------------------------------------------
void CShader::SetModelColor(D3DXCOLOR DiffuseCol, D3DXCOLOR SpecularCol, D3DXCOLOR EmissiveCol, D3DXCOLOR AmbientCol,float fPower)
{
	m_pShaderEffect[CShader::SHADER_MODELDRAW]->SetVector(m_pModelColorHandle->m_hDiffuseCol, &D3DXVECTOR4(DiffuseCol));
	m_pShaderEffect[CShader::SHADER_MODELDRAW]->SetVector(m_pModelColorHandle->m_hSpecularCol, &D3DXVECTOR4(SpecularCol));
	m_pShaderEffect[CShader::SHADER_MODELDRAW]->SetVector(m_pModelColorHandle->m_hEmissiveCol, &D3DXVECTOR4(EmissiveCol));
	m_pShaderEffect[CShader::SHADER_MODELDRAW]->SetVector(m_pModelColorHandle->m_Ambient, &D3DXVECTOR4(AmbientCol));
	m_pShaderEffect[CShader::SHADER_MODELDRAW]->SetFloat(m_pModelColorHandle->m_hPower, fPower);
}