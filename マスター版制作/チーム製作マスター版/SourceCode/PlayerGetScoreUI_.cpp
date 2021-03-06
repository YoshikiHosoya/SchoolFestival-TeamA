// =====================================================================================================================================================================
//
// 取得スコアの表示処理 [playergetscoreui.cpp]
// Author : Fujiwara Masato
//
// =====================================================================================================================================================================
#include "main.h"			// インクルードファイル
#include "playerGetScoreUI.h"
#include "debugproc.h"
#include "3Dmultinumber.h"
#include "UIManager.h"
#include "Manager.h"
#include "player.h"
#include "basemode.h"

// =====================================================================================================================================================================
// 静的メンバ変数の初期化
// =====================================================================================================================================================================
int					CPlayerGSUI::m_nDigits = 0;							// 桁数
int					CPlayerGSUI::m_nGetScore = 0;						// スコア
// =====================================================================================================================================================================
// マクロ定義
// =====================================================================================================================================================================
#define PGSUI_X		(20) // 横の大きさ
#define PGSUI_Y		(20) // 縦の大きさ

// =====================================================================================================================================================================
//
// コンストラクタ
//
// =====================================================================================================================================================================
CPlayerGSUI::CPlayerGSUI()
{
	m_pGetScore = nullptr;
	// 変数初期化
	m_nGetScore			 = NULL;		// 得点を取得した際の点数
	m_nTime = 120;			// 存在できる時間
	m_nCalCnt = NULL;		// 点滅用時間
	m_fmove = 0.0f;
	m_nNumPlayer = false;
}

// =====================================================================================================================================================================
//
// デストラクタ
//
// =====================================================================================================================================================================
CPlayerGSUI::~CPlayerGSUI()
{
}

// =====================================================================================================================================================================
//
// 初期化処理
//
// =====================================================================================================================================================================
HRESULT CPlayerGSUI::Init(void)
{
	GetScoreUICreate();					// スコア表示UIの生成
	return S_OK;
}

// =====================================================================================================================================================================
//
// 終了処理
//
// =====================================================================================================================================================================
void CPlayerGSUI::Uninit(void)
{
	// スコアの解放
	if (m_pGetScore)
	{
		m_pGetScore->Rerease();
		m_pGetScore = nullptr;
	}
}

// =====================================================================================================================================================================
//
// 更新処理
//
// =====================================================================================================================================================================
void CPlayerGSUI::Update(void)
{
	// 滞在時間の減少
	m_nTime--;

	// nullじゃないか確認
	if (m_pGetScore)
	{
		// 点滅処理
		Flashing(m_pGetScore);
		// UIの移動
		Move();
		// 滞在時間が0以下になった時
		if (m_nTime <= 0)
		{
			// 解放
			m_pGetScore->Rerease();
			m_pGetScore = nullptr;

			// デリートフラグを有効にする
			SetDeleteFlag(true);
		}
	}

	CDebugProc::Print_Left("uiポインタ------------------------------------------------ %d\n", m_nTime);
}

// =====================================================================================================================================================================
//
// 描画処理
//
// =====================================================================================================================================================================
void CPlayerGSUI::Draw(void)
{
}

// =====================================================================================================================================================================
//
// プレイヤーUIの生成
//
// =====================================================================================================================================================================
CPlayerGSUI * CPlayerGSUI::Create(int nScore, int NumPlayer)
{
	//メモリの確保
	CPlayerGSUI *pPlayerGSUI = new CPlayerGSUI();
	// スコア取得
	Set_Get_Score(nScore);
	// プレイヤーが1p2pどちらなのか
	pPlayerGSUI->m_nNumPlayer = NumPlayer;
	// 初期化
	pPlayerGSUI->Init();
	//オブジェタイプ設定してSceneに所有権を渡す
	CUIManager::AddUIList(std::move(pPlayerGSUI));
	// ポインタを返す
	return pPlayerGSUI;
}


// =====================================================================================================================================================================
//
// 得点を取得した際の表示する点数の設定
//
// =====================================================================================================================================================================
void CPlayerGSUI::Set_Get_Score(int nScore)
{
	// 獲得したスコアの値を取得
	m_nGetScore = nScore;
	Set_Score_Value(m_nGetScore);
}

// =====================================================================================================================================================================
//
// スコアの桁数を取得
//
// =====================================================================================================================================================================
void CPlayerGSUI::Set_Score_Value(int nValue)
{
	if (nValue <= 99 && nValue >= 10)
	{
		m_nDigits = 2;
	}
	if (nValue <= 999 && nValue >= 100)
	{
		m_nDigits = 3;
	}
	else if (nValue <= 9999 && nValue >= 1000)
	{
		m_nDigits = 4;
	}
	else if (nValue <= 99999 && nValue >= 10000)
	{
		m_nDigits = 5;
	}
	else if (nValue <= 999999 && nValue >= 100000)
	{
		m_nDigits = 6;
	}
}


// =====================================================================================================================================================================
//
// スコアデータの構造体の初期化
//
// =====================================================================================================================================================================
void CPlayerGSUI::ScoreDataInitialize()
{
	this->m_nTime = 120;			// 存在できる時間
	this->m_nCalCnt = NULL;		// 点滅用時間
}

// =====================================================================================================================================================================
//
// 既にスコアが表示されているのかの確認
//
// =====================================================================================================================================================================
void CPlayerGSUI::GetScoreUICreate()
{
	CPlayer *pPlayer[CPlayer::PLAYER_NUM_TWO];

	// プレイヤーのポインタを取得
	for (int nCnt = 0; nCnt < CPlayer::PLAYER_NUM_MAX; nCnt++)
	{
		pPlayer[nCnt] = CManager::GetBaseMode()->GetPlayer((TAG)nCnt);
	}

	if (pPlayer)
	{
		if (m_nNumPlayer == 0)
		{
			// 生成
			m_pGetScore = C3DMultiNumber::Create(
				D3DXVECTOR3(
					pPlayer[0]->GetPosition().x,
					pPlayer[0]->GetPosition().y + 200,
					-100.0f),
				D3DXVECTOR3(PGSUI_X, PGSUI_Y, 0.0f),
				m_nGetScore,
				m_nDigits,
				CScene::OBJTYPE_UI);

			m_pGetScore->SetCol(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
		}
		else
		{
			// 生成
			m_pGetScore = C3DMultiNumber::Create(
				D3DXVECTOR3(
					pPlayer[1]->GetPosition().x,
					pPlayer[1]->GetPosition().y + 200,
					-100.0f),
				D3DXVECTOR3(PGSUI_X, PGSUI_Y, 0.0f),
				m_nGetScore,
				m_nDigits,
				CScene::OBJTYPE_UI);

			m_pGetScore->SetCol(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
		}
	}
}

// =====================================================================================================================================================================
//
// 更新処理
//
// =====================================================================================================================================================================
void CPlayerGSUI::Move()
{
	// 座標に移動量を加算
	this->m_pGetScore->SetPos(D3DXVECTOR3(m_pGetScore->GetPos().x, m_pGetScore->GetPos().y + m_fmove, m_pGetScore->GetPos().z));

	// 移動量の加算
	m_fmove += cosf(m_fmove * -D3DX_PI) * 1.5f;
}

// =====================================================================================================================================================================
//
// 点滅処理
//
// =====================================================================================================================================================================
void CPlayerGSUI::Flashing(C3DMultiNumber *m_pMultiNumber)
{
	// カウント加算
	m_nCalCnt++;
	// 余りが0の時透明にする
	if (m_nCalCnt % 30 == 0)
	{
		m_pMultiNumber->SetCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	}
	// 余りが0の時通常状態にする
	else if (m_nCalCnt % 15 == 0)
	{
		m_pMultiNumber->SetCol(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	}
}
