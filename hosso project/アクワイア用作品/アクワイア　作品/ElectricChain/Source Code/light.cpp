//-----------------------------------------------------------------------------
//
// ライト処理 [light.cpp]
// Author : Yosihiki Hosoya
//
//-----------------------------------------------------------------------------
#include "light.h"
#include "manager.h"
#include "renderer.h"
//-----------------------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// コンストラクタ
//-----------------------------------------------------------------------------
CLight::CLight()
{
}
//-----------------------------------------------------------------------------
// デストラクタ
//-----------------------------------------------------------------------------
CLight::~CLight()
{
}
//-----------------------------------------------------------------------------
// 初期化
//-----------------------------------------------------------------------------

void CLight::Init()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	// デバイスの取得

	m_vecDir[0] = D3DXVECTOR3(0.20f, -0.80f, 0.40f);
	m_vecDir[1] = D3DXVECTOR3(-0.20f, 0.80f, -0.40f);
	m_vecDir[2] = D3DXVECTOR3(0.10f, -0.10f, -0.40f);

	D3DXCOLOR Diffuse[MAX_LIGHT] =
	{
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f),
		D3DXCOLOR(0.15f, 0.15f, 0.15f, 1.0f)
	};


	//---------------------------------------------
	// ライト0の設定
	//---------------------------------------------

	for (int nCnt = 0; nCnt < MAX_LIGHT; nCnt++)
	{
		// ライトをクリアする
		ZeroMemory(&m_aLight[nCnt], sizeof(D3DLIGHT9));

		// ライトの種類を設定
		m_aLight[nCnt].Type = D3DLIGHT_DIRECTIONAL;

		// ライトの拡散光を設定
		m_aLight[nCnt].Diffuse = Diffuse[nCnt];
		m_aLight[nCnt].Specular = Diffuse[nCnt];		//スペキュラー(反射光)

		// ライトの方向の設定
		D3DXVec3Normalize(&m_vecDir[nCnt], &m_vecDir[nCnt]);		//正規化
		m_aLight[nCnt].Direction = m_vecDir[nCnt];

		// ライトを設定する
		pDevice->SetLight(nCnt, &m_aLight[nCnt]);
		// ライトを有効にする
		pDevice->LightEnable(nCnt, TRUE);
	}
}
//-----------------------------------------------------------------------------
// 終了処理
//-----------------------------------------------------------------------------
void CLight::Uninit()
{
}
//-----------------------------------------------------------------------------
// 更新処理
//-----------------------------------------------------------------------------
void CLight::Update()
{

}
//-----------------------------------------------------------------------------
// ライトの情報
//-----------------------------------------------------------------------------
void CLight::ShowLightInfo()
{
	if (ImGui::CollapsingHeader("LightInfo"))
	{
		LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	// デバイスの取得

		if (ImGui::TreeNode("Light0"))
		{
			ImGui::SliderFloat3("direction", m_vecDir[0], -1.0f, 1.0f);

			D3DXVec3Normalize(&m_vecDir[0], &m_vecDir[0]);		//正規化
			m_aLight[0].Direction = m_vecDir[0];

			pDevice->SetLight(0, &m_aLight[0]);
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("Light1"))
		{
			ImGui::SliderFloat3("direction", m_vecDir[1], -1.0f, 1.0f);

			D3DXVec3Normalize(&m_vecDir[1], &m_vecDir[1]);		//正規化
			m_aLight[1].Direction = m_vecDir[1];

			pDevice->SetLight(1, &m_aLight[1]);
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("Light2"))
		{
			ImGui::SliderFloat3("direction", m_vecDir[2], -1.0f, 1.0f);

			D3DXVec3Normalize(&m_vecDir[2], &m_vecDir[2]);		//正規化
			m_aLight[2].Direction = m_vecDir[2];

			pDevice->SetLight(2, &m_aLight[2]);
			ImGui::TreePop();
		}
	}
}
//-----------------------------------------------------------------------------
// ライト情報取得
//-----------------------------------------------------------------------------
D3DXVECTOR3 CLight::GetLightDir()
{
	return m_vecDir[0];
}
