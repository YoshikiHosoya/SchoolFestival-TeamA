//------------------------------------------------------------------------------
//
//デバッグ　エフェクトビューワ用の処理  [Debug_EffectViewer.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "Debug_EffectViewer.h"
#include "../Scene.h"
#include "../manager.h"
#include "../renderer.h"
#include "../inputKeyboard.h"
#include "../camera.h"
#include "../fade.h"
#include "../particle.h"
#include "../ParticleManager.h"
//------------------------------------------------------------------------------
//静的メンバ変数の初期化
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//マクロ
//------------------------------------------------------------------------------
#define DEFAULT_PLAYER_POS (ZeroVector3)
#define DEFAULT_SCORE_POS (D3DXVECTOR3(1150.0f, 50.0f, 0.0f))

//------------------------------------------------------------------------------
//コンストラクタ
//------------------------------------------------------------------------------
CDebug_EffectViewer::CDebug_EffectViewer()
{
	//初期化
	m_nLife = 100;
	m_col = WhiteColor;
	m_fRadius = 30.0f;
	m_nNumParticle = 10;
	m_fSpeed = 30.0f;
	m_fAlphaDamping = 0.95f;
	m_fRadiusDamping = 0.95f;
	m_textype = CTexture::TEX_EFFECT_PARTICLE;

	m_bLoop = false;
	m_nLoopInterval = 60;
	m_nCnt = 0;
}
//------------------------------------------------------------------------------
//デストラクタ
//------------------------------------------------------------------------------
CDebug_EffectViewer::~CDebug_EffectViewer()
{

}

//------------------------------------------------------------------------------
//初期化処理
//------------------------------------------------------------------------------
HRESULT CDebug_EffectViewer::Init()
{
	////カメラ座標設定
	//CManager::GetRenderer()->getca()->SetCameraPos(DEFAULT_PLAYER_POS, DEFAULT_PLAYER_POS + D3DXVECTOR3(0.0f, 300.0f, -500.0f));
	//CManager::GetRenderer()->GetCamera()->SetState(CCamera::CAMERA_DEBUG);
	//CManager::GetRenderer()->GetCamera()->SetCameraRot(D3DXVECTOR3( 0.4f, 0.0f, 0.0f));

	//CMeshField::Create(ZeroVector3, D3DXVECTOR3(100.0f, 0.0f, 100.0f), INTEGER2(5, 5));

	CParticleManager::Create();

	return S_OK;
}

//------------------------------------------------------------------------------
//終了処理
//------------------------------------------------------------------------------
void CDebug_EffectViewer::Uninit()
{

	//終了処理
	//CScene::ReleaseAll();
}

//------------------------------------------------------------------------------
//更新処理
//------------------------------------------------------------------------------
void CDebug_EffectViewer::Update()
{

}

//------------------------------------------------------------------------------
//描画処理
//------------------------------------------------------------------------------
void CDebug_EffectViewer::Draw()
{

}
//------------------------------------------------------------------------------
//デバッグ情報表記
//------------------------------------------------------------------------------
void CDebug_EffectViewer::ShowDebugInfo()
{
#ifdef _DEBUG

	if (!CScene::GetStopFlag())
	{
		//カウンタ++
		m_nCnt++;
	}

	//キーボードのポインタ取得
	CKeyboard *pKeyboard = CManager::GetInputKeyboard();

	//Debug
	CDebugProc::Print("[Enter] パーティクル発生\n");
	CDebugProc::Print("[Ctrl] + [Enter] Loop %d \n",m_bLoop);

	ImGui::PushItemWidth(120);

	//パラメータ設定
	ImGui::DragInt("Life", &m_nLife, 1, 1, 300);
	ImGui::DragFloat("Radius", &m_fRadius, 0.5f, 1.0f, 250.0f);
	ImGui::DragFloat("Speed", &m_fSpeed, 0.5f, 1.0f, 250.0f);
	ImGui::DragInt("ParticleNum", &m_nNumParticle, 1, 0, 300);
	ImGui::DragFloat("RadiusDamping", &m_fRadiusDamping, 0.001f, 0.5f, 1.0f);
	ImGui::DragFloat("AlphaDamping", &m_fAlphaDamping, 0.001f, 0.5f, 1.0f);


	//軌跡の色　float型にキャスト
	float *rCol = m_col;

	ImGui::SetNextItemWidth(250);

	//色の設定
	ImGui::ColorEdit4("OrbitColor", rCol);

	//[Ctrl] + [Enter]
	if ((pKeyboard->GetKeyboardPress(DIK_LCONTROL) && pKeyboard->GetKeyboardTrigger(DIK_RETURN)))
	{
		//onoff設定
		m_bLoop ^= 1;
	}

	//[Enter]を押したとき　または　ループする時
	if (pKeyboard->GetKeyboardTrigger(DIK_RETURN) || (m_bLoop && m_nCnt % m_nLoopInterval == 0))
	{
		CParticle::DetailsCreate(D3DXVECTOR3(0.0f, 50.0f, 100.0f), m_nLife, m_fRadius, m_col, m_nNumParticle, m_fSpeed,m_fAlphaDamping,m_fRadiusDamping,m_textype);
	}

#endif
}