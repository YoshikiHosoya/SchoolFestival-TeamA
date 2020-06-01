//=============================================================================
//
// ポイントライト処理 [pointlight.cpp]
// Author : Fujiwara Masato
//
//=============================================================================
#include "pointlight.h"
#include "manager.h"
#include "debugproc.h"
// ------------------------------------------
//
// 静的変数宣言
//
// ------------------------------------------
LPDIRECT3DDEVICE9 CPointLight::m_pDevice = NULL;

// ----------------------------------------
// コンストラクタ処理
// ----------------------------------------
CPointLight::CPointLight()
{
	// デバイスの取得
	m_pDevice = CManager::GetRenderer()->GetDevice();
	// 全てのポイントライトの設定
	for (int nCntLight = 0; nCntLight < POINTLIGHT_MAX; nCntLight++)
	{
		// ライトをクリアする
		ZeroMemory(&m_light[nCntLight], sizeof(D3DLIGHT9));

		// ライトの種類を設定
		m_light[nCntLight].Type = D3DLIGHT_POINT;

		// ライトの拡散光を設定
		m_light[nCntLight].Diffuse = m_col[nCntLight];

		// ライトの座標を設定
		m_light[nCntLight].Position = m_pos[nCntLight];

		// ライトの光の範囲を設定
		m_light[nCntLight].Range = m_range[nCntLight];

		// ライトの設定
		m_pDevice->SetLight(nCntLight, &m_light[nCntLight]);

		// ライトの一定の逆減衰
		m_light[nCntLight].Attenuation0 = 0.0f;

		// .125のみの逆減衰
		m_light[nCntLight].Attenuation1 = 0.125f;

		// ライトの逆正方減衰
		m_light[nCntLight].Attenuation2 = 0.0f;

		// ライトを有効にする
		m_pDevice->LightEnable(nCntLight, TRUE);
	}
}

// ----------------------------------------
// デストラクタ処理
// ----------------------------------------
CPointLight::~CPointLight()
{
}

// ----------------------------------------
// 初期化処理
// ----------------------------------------
void CPointLight::Init(void)
{
}

// ----------------------------------------
// 終了処理
// ----------------------------------------
void CPointLight::Uninit(void)
{
}

// ----------------------------------------
// 更新処理
// ----------------------------------------
void CPointLight::Update(void)
{
	for (int nCnt = 0; nCnt < POINTLIGHT_MAX; nCnt++)
	{
		CDebugproc::Print("ライト 座標		: %.2f,%.2f,%.2f\n", m_pos[nCnt].x, m_pos[nCnt].y, m_pos[nCnt].z);

		CDebugproc::Print("ライト 範囲		: %.2f \n", m_range[nCnt]);
	}
}

// ----------------------------------------
// 生成処理
// ----------------------------------------
CPointLight * CPointLight::Create(void)
{
	// 変数宣言
	CPointLight * pLight;
	// メモリの生成(初め->基本クラス,後->派生クラス)
	pLight = new CPointLight();
	// 初期化処理
	pLight->Init();
	// 生成したオブジェクトを返す
	return pLight;
}

// ----------------------------------------
// ライトの設定
// ----------------------------------------
void CPointLight::SetPointLight(void)
{
	if (CManager::GetMode() == CManager::MODE_TITLE)
	{
		for (int nCntLight = 0; nCntLight < POINTLIGHT_MAX; nCntLight++)
		{
			// ライトを有効にする
			m_pDevice->LightEnable(nCntLight, TRUE);
		}
	}

	else if (CManager::GetMode() == CManager::MODE_GAME)
	{
		for (int nCntLight = 0; nCntLight < POINTLIGHT_MAX; nCntLight++)
		{
			// ライトを有効にする
			m_pDevice->LightEnable(nCntLight, TRUE);
		}
	}
}
