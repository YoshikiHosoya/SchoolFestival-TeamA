//=============================================================================
//
// ライト処理 [light.cpp]
// Author : Fujiwara Masato
//
//=============================================================================
#include "light.h"
#include "manager.h"
#include "debugproc.h"

// ------------------------------------------
//
// 静的変数宣言
//
// ------------------------------------------
LPDIRECT3DDEVICE9 CLight::m_pDevice = NULL;

// ----------------------------------------
// コンストラクタ処理
// ----------------------------------------
CLight::CLight()
{
	m_nCount = 0;
	m_pDevice = CManager::GetRenderer()->GetDevice();	// デバイスの取得
	// カウントライト
	for (int nCntLight = 0; nCntLight < LIGHT_MAX; nCntLight++)
	{
		// ライトをクリアする
		ZeroMemory(&m_light[nCntLight], sizeof(D3DLIGHT9));

		// ライトの種類を設定
		m_light[nCntLight].Type = m_lightType[nCntLight];

		// ライトの拡散光を設定
		m_light[nCntLight].Diffuse = m_col[nCntLight];

		if (m_light[nCntLight].Type == D3DLIGHT_DIRECTIONAL)
		{
			// ライトの方向の設定
			D3DXVec3Normalize(&m_VecDir[nCntLight], &m_VecDir[nCntLight]);
			m_light[nCntLight].Direction = m_VecDir[nCntLight];
		}

		else if (m_light[nCntLight].Type == D3DLIGHT_POINT)
		{
			// ライトの座標を設定
			m_light[nCntLight].Position = m_pos[m_nCount];

			// ライトの光の範囲を設定
			m_light[nCntLight].Range = m_range[m_nCount];

			m_nCount++;
		}

		// ライトを設定する
		m_pDevice->SetLight(nCntLight, &m_light[nCntLight]);

		if (m_light[nCntLight].Type == D3DLIGHT_POINT)
		{
			//// ライトの一定の逆減衰
			//m_light[nCntLight].Attenuation0 = 0.125f;

			//// .125のみの逆減衰
			//m_light[nCntLight].Attenuation1 = 0.0f;

			//// ライトの逆正方減衰
			//m_light[nCntLight].Attenuation2 = 0.0f;

			// ライトの一定の逆減衰
			m_light[nCntLight].Attenuation0 = 0.0f;

			// .125のみの逆減衰
			m_light[nCntLight].Attenuation1 = 1.0f;

			// ライトの逆正方減衰
			m_light[nCntLight].Attenuation2 = 0.0f;
		}

		// ライトを有効にする
		m_pDevice->LightEnable(nCntLight, TRUE);
	}
}

// ----------------------------------------
// デストラクタ処理
// ----------------------------------------
CLight::~CLight()
{
}

// ----------------------------------------
// 初期化処理
// ----------------------------------------
void CLight::Init(void)
{
}

// ----------------------------------------
// 終了処理
// ----------------------------------------
void CLight::Uninit(void)
{
}

// ----------------------------------------
// 更新処理
// ----------------------------------------
void CLight::Update(void)
{
	for (int nCnt = 4; nCnt < LIGHT_MAX; nCnt++)
	{
		CDebugproc::Print("ライト 座標		: %.2f,%.2f,%.2f \n", m_light[nCnt].Position.x, m_light[nCnt].Position.y, m_light[nCnt].Position.z);

		CDebugproc::Print("ライト 範囲		: %.2f \n", m_light[nCnt].Range);
	}

	//SetLight();
}

// ----------------------------------------
// 生成処理
// ----------------------------------------
CLight * CLight::Create(void)
{
	// 変数宣言
	CLight * pLight;
	// メモリの生成(初め->基本クラス,後->派生クラス)
	pLight = new CLight();
	// 初期化処理
	pLight->Init();
	// 生成したオブジェクトを返す
	return pLight;
}

// ----------------------------------------
// ライトの設定
// ----------------------------------------
void CLight::SetLight(void)
{
	if (CManager::GetMode() == CManager::MODE_TITLE)
	{
		// ライトの1番を有効にする
		m_pDevice->LightEnable(0, FALSE);
		m_pDevice->LightEnable(1, TRUE);
		m_pDevice->LightEnable(2, FALSE);
		m_pDevice->LightEnable(3, FALSE);

		m_pDevice->LightEnable(4, FALSE);
		m_pDevice->LightEnable(5, FALSE);
		m_pDevice->LightEnable(6, FALSE);
	}

	else if (CManager::GetMode() == CManager::MODE_GAME)
	{
		// ライトを有効にする
		m_pDevice->LightEnable(0, TRUE);
		m_pDevice->LightEnable(1, TRUE);
		m_pDevice->LightEnable(2, TRUE);
		m_pDevice->LightEnable(3, TRUE);

		m_pDevice->LightEnable(4, TRUE);
		m_pDevice->LightEnable(5, TRUE);
		m_pDevice->LightEnable(6, TRUE);
	}
}
