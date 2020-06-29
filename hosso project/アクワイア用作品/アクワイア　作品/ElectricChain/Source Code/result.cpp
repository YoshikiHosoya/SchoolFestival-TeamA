//------------------------------------------------------------------------------
//
//リザルト処理  [result.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "scene.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "fade.h"
#include "result.h"
#include "UI.h"
#include "Map.h"
#include "multinumber.h"
#include "score.h"
#include "player.h"
#include "sound.h"
#include "effectanimation2D.h"
//------------------------------------------------------------------------------
//マクロ
//------------------------------------------------------------------------------
#define ITEM_COMBO_POP		(40)									//コンボ数が表示するカウンタ
#define ITEM_KILL_POP		(80)									//キル数が表示されるカウンタ
#define ITEM_TOTAL_POP		(150)									//トータルが表示されるカウンタ
#define DEFAULT_PLAYER_POS	(D3DXVECTOR3(0.0f, 0.0f, 1000.0f))		//プレイヤー初期座標
//------------------------------------------------------------------------------
//静的メンバ変数の初期化
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//コンストラクタ
//------------------------------------------------------------------------------
CResult::CResult()
{
	m_nCntResult = 0;
}

//------------------------------------------------------------------------------
//デストラクタ
//------------------------------------------------------------------------------
CResult::~CResult()
{
}

//------------------------------------------------------------------------------
//初期化処理
//------------------------------------------------------------------------------
HRESULT CResult::Init(HWND hWnd)
{
	//UI生成
	CUI::LoadPlace(CUI::SCENE_RESULT);

	//マップ生成
	CMap::Create();

	//プレイヤー生成
	CPlayer::Create(DEFAULT_PLAYER_POS);

	//カメラ座標設定
	CManager::GetRenderer()->GetCamera()->SetCameraPos(DEFAULT_PLAYER_POS + D3DXVECTOR3(130.0f,100.0f,0.0f), DEFAULT_PLAYER_POS + D3DXVECTOR3(-80.0f, 40.0f, -300.0f));
	CManager::GetRenderer()->GetCamera()->SetState(CCamera::CAMERA_RESULT);

	return S_OK;
}

//------------------------------------------------------------------------------
//終了処理
//------------------------------------------------------------------------------
void CResult::Uninit()
{
	//終了処理
	CScene::ReleaseAll();
}

//------------------------------------------------------------------------------
//更新処理
//------------------------------------------------------------------------------
void CResult::Update()
{
	//カウンタ++
	m_nCntResult++;

	//カウンタに応じてリザルトの項目表示
	PopResultItem();

	//フェードしてない時
	if (CManager::GetRenderer()->GetFade()->GetFade() == CFade::FADE_NONE)
	{
		//何かボタン押したとき
		if (CHossoLibrary::CheckAnyButton())
		{
			//項目が全部表示されてない時
			if (m_nCntResult <= ITEM_TOTAL_POP)
			{
				//全部表示されるとこまでカウンタを飛ばす
				m_nCntResult = ITEM_TOTAL_POP;
			}
			//項目が全部表示されていた時
			else
			{
				//ステート変更
				CManager::GetRenderer()->GetFade()->SetModeFade(CManager::MODE_RANKING);
				CManager::GetSound()->Play(CSound::LABEL_SE_DECISION);
			}
		}
	}
}

//------------------------------------------------------------------------------
//描画処理
//------------------------------------------------------------------------------
void CResult::Draw()
{

}

//------------------------------------------------------------------------------
//カウンタに応じて項目を表示
//------------------------------------------------------------------------------
void CResult::PopResultItem()
{

	if (m_nCntResult > ITEM_COMBO_POP && m_pNumberList.size() <= CResult::RESULT_COMBO)
	{
		//Combo
		m_pNumberList.emplace_back(CMultiNumber::Create(
			D3DXVECTOR3(720.0f, 270.0f, 0.0f),
			D3DXVECTOR3(40.0f, 80.0f, 0.0f),
			CScore::GetCombo(),
			4,
			CScene::OBJTYPE_NUMBER));

		//雷のエフェクト
		CEffectAnimation2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 270.0f, 0.0f),
			D3DXVECTOR3(SCREEN_WIDTH, 200.0f, 0.0f), CTexture::SEPARATE_TEX_EFFECT_LINETHUNDER, 0.0f, 3, CScene::OBJTYPE_2DEFFECT);

		CManager::GetSound()->Play(CSound::LABEL_SE_RANKING_THUNDER);
	}
	if (m_nCntResult > ITEM_KILL_POP && m_pNumberList.size() <= CResult::REUSLT_KILL)
	{
		//Kill
		m_pNumberList.emplace_back(CMultiNumber::Create(
			D3DXVECTOR3(720.0f, 390.0f, 0.0f),
			D3DXVECTOR3(40.0f, 80.0f, 0.0f),
			CScore::GetKill(),
			4,
			CScene::OBJTYPE_NUMBER));
		//雷のエフェクト
		CEffectAnimation2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 390.0f, 0.0f),
			D3DXVECTOR3(SCREEN_WIDTH, 200.0f, 0.0f), CTexture::SEPARATE_TEX_EFFECT_LINETHUNDER, 0.0f, 3, CScene::OBJTYPE_2DEFFECT);

		CManager::GetSound()->Play(CSound::LABEL_SE_RANKING_THUNDER);

	}
	if (m_nCntResult > ITEM_TOTAL_POP && m_pNumberList.size() <= CResult::RESULT_TOTAL)
	{
		//Total
		m_pNumberList.emplace_back(CMultiNumber::Create(
			D3DXVECTOR3(1020.0f, 520.0f, 0.0f),
			D3DXVECTOR3(55.0f, 120.0f, 0.0f),
			CScore::GetScore(),
			6,
			CScene::OBJTYPE_NUMBER));
		//雷のエフェクト
		CEffectAnimation2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 520.0f, 0.0f),
			D3DXVECTOR3(SCREEN_WIDTH, 500.0f, 0.0f), CTexture::SEPARATE_TEX_EFFECT_LINETHUNDER, 0.0f, 4, CScene::OBJTYPE_2DEFFECT);

		CManager::GetSound()->Play(CSound::LABEL_SE_RANKING_THUNDER);

		//点滅させる
		m_pNumberList[RESULT_TOTAL]->Settype(CMultiNumber::TYPE_FLASHING);

	}

}
