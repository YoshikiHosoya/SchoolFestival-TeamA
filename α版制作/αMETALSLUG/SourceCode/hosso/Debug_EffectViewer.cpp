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
	m_bLoop = false;
	m_nLoopInterval = 60;
	m_nCnt = 0;
	m_pParticleParam.reset();
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

	//パーティクルのパラメータのメモリ確保
	m_pParticleParam.reset(new CParticleParam);

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

	//CParticleParam::PARTICLE_TYPE type = ;

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
	ImGui::DragInt("Life", &m_pParticleParam->GetLife(), 1, 1, 300);
	ImGui::DragFloat("Radius", &m_pParticleParam->GetRadius(), 0.5f, 1.0f, 250.0f);
	ImGui::DragFloat("Speed", &m_pParticleParam->GetSpeed(), 0.5f, 1.0f, 250.0f);
	ImGui::DragInt("ParticleNum", &m_pParticleParam->GetNumber(), 1, 0, 300);
	ImGui::DragFloat("RadiusDamping", &m_pParticleParam->GetRadiusDamping(), 0.001f, 0.5f, 1.0f);
	ImGui::DragFloat("AlphaDamping", &m_pParticleParam->GetAlphaDamping(), 0.001f, 0.5f, 1.0f);


	//軌跡の色　float型にキャスト
	float *rCol = m_pParticleParam->GetCol();

	ImGui::SetNextItemWidth(250);

	//色の設定
	ImGui::ColorEdit4("Color", rCol);

	//パーティクル情報保存
	if(ImGui::Button("Save"))
	{
		//セーブ
		CParticleParam::SaveParticleDefaultParam(m_pParticleParam.get());
	}

	////コンボボックス表示
	//if (CParticleParam::ShowParamConboBox(m_pParticleParam->GetType()))
	//{
	//	CParticleParam *pParam = new CParticleParam;

	//	//情報設定
	//	//Uniqueptrを使うとオペレータできなかったから普通のポインタ同士でオペレータ
	//	*pParam = *CParticleParam::GetDefaultParam(type);
	//}

	//[Ctrl] + [Enter]
	if ((pKeyboard->GetKeyboardPress(DIK_LCONTROL) && pKeyboard->GetKeyboardTrigger(DIK_RETURN)))
	{
		//onoff設定
		m_bLoop ^= 1;
	}

	//[Enter]を押したとき　または　ループする時
	if (pKeyboard->GetKeyboardTrigger(DIK_RETURN) || (m_bLoop && m_nCnt % m_nLoopInterval == 0))
	{
		CParticle::DetailsCreate(D3DXVECTOR3(0.0f, 50.0f, 100.0f),
			m_pParticleParam->GetLife(), m_pParticleParam->GetRadius(), m_pParticleParam->GetCol(), m_pParticleParam->GetNumber(),
			m_pParticleParam->GetSpeed(), m_pParticleParam->GetAlphaDamping(), m_pParticleParam->GetRadiusDamping(), m_pParticleParam->GetTex());
	}

#endif
}