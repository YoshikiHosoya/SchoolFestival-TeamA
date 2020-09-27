// =====================================================================================================================================================================
//
// リザルトUIの処理 [resultUI.cpp]
// Author : fujiwara masato
//
// =====================================================================================================================================================================
#include "main.h"			// インクルードファイル
#include "resultUI.h"
#include "debugproc.h"
#include "UIManager.h"
#include "scene2D.h"
#include "game.h"
#include "basemode.h"
#include "manager.h"
#include "multinumber.h"
#include "player.h"
#include "playerui.h"
#include "resultmanager.h"
#include "rankingui.h"
#include "scoremanager.h"
#include "sound.h"
#include "ResultManager.h"
#include "map.h"
// =====================================================================================================================================================================
// マクロ定義
// =====================================================================================================================================================================
// ------- 座標 ------- //
#define RESULT_UI_BG_POS (SCREEN_CENTER_POS)
#define RESULT_UI_NAME_POS (D3DXVECTOR3(SCREEN_WIDTH * 0.5f,80.0f,0.0f))
#define RESULT_UI_1P_POS (D3DXVECTOR3(SCREEN_WIDTH * 0.25f,200.0f,0.0f))
#define RESULT_UI_2P_POS (D3DXVECTOR3(SCREEN_WIDTH * 0.75f,200.0f,0.0f))
#define RESULT_UI_EVALUATION0_POS_1P (D3DXVECTOR3(SCREEN_WIDTH * 0.25f,650.0f,0.0f))
#define RESULT_UI_EVALUATION1_POS_1P (D3DXVECTOR3(SCREEN_WIDTH * 0.25f,650.0f,0.0f))
#define RESULT_UI_EVALUATION2_POS_1P (D3DXVECTOR3(SCREEN_WIDTH * 0.25f,650.0f,0.0f))
#define RESULT_UI_EVALUATION0_POS_2P (D3DXVECTOR3(SCREEN_WIDTH * 0.75f,650.0f,0.0f))
#define RESULT_UI_EVALUATION1_POS_2P (D3DXVECTOR3(SCREEN_WIDTH * 0.75f,650.0f,0.0f))
#define RESULT_UI_EVALUATION2_POS_2P (D3DXVECTOR3(SCREEN_WIDTH * 0.75f,650.0f,0.0f))
#define RESULT_UI_MISSIONCOMPLAYER_1_POS (SCREEN_CENTER_POS)
#define RESULT_UI_MISSIONCOMPLAYER_2_POS (SCREEN_CENTER_POS)

#define RESULT_UI_PRISONERNUM_POS_1P (D3DXVECTOR3(SCREEN_WIDTH * 0.25f,350.0f,0.0f))
#define RESULT_UI_PRISONERNUM_POS_2P (D3DXVECTOR3(SCREEN_WIDTH * 0.75f,350.0f,0.0f))
#define RESULT_UI_BONUS_POS_1P (D3DXVECTOR3(SCREEN_WIDTH * 0.25f,500.0f,0.0f))
#define RESULT_UI_BONUS_POS_2P (D3DXVECTOR3(SCREEN_WIDTH * 0.75f,500.0f,0.0f))

// ------- サイズ ------- //
#define RESULT_UI_BG_SIZE (SCREEN_SIZE)
#define RESULT_UI_NAME_SIZE (D3DXVECTOR3(600.0f,50.0f,0.0))
#define RESULT_UI_1P_SIZE (D3DXVECTOR3(80.0f,60.0f,0.0f))
#define RESULT_UI_2P_SIZE (D3DXVECTOR3(80.0f,60.0f,0.0f))
#define RESULT_UI_EVALUATION0_SIZE_1P (D3DXVECTOR3(300.0f,40.0f,0.0f))
#define RESULT_UI_EVALUATION1_SIZE_1P (D3DXVECTOR3(300.0f,40.0f,0.0f))
#define RESULT_UI_EVALUATION2_SIZE_1P (D3DXVECTOR3(300.0f,40.0f,0.0f))
#define RESULT_UI_EVALUATION0_SIZE_2P (D3DXVECTOR3(300.0f,40.0f,0.0f))
#define RESULT_UI_EVALUATION1_SIZE_2P (D3DXVECTOR3(300.0f,40.0f,0.0f))
#define RESULT_UI_EVALUATION2_SIZE_2P (D3DXVECTOR3(300.0f,40.0f,0.0f))
#define RESULT_UI_MISSIONCOMPLAYER_1_SIZE (D3DXVECTOR3(500.0f,200.0f,0.0f))
#define RESULT_UI_MISSIONCOMPLAYER_2_SIZE (D3DXVECTOR3(500.0f,200.0f,0.0f))

#define RESULT_UI_PRISONERNUM_SIZE_1P (D3DXVECTOR3(70.0f,70.0f,0.0f))
#define RESULT_UI_PRISONERNUM_SIZE_2P (D3DXVECTOR3(70.0f,70.0f,0.0f))
#define RESULT_UI_BONUS_SIZE_1P (D3DXVECTOR3(80.0f,80.0f,0.0f))
#define RESULT_UI_BONUS_SIZE_2P (D3DXVECTOR3(80.0f,80.0f,0.0f))

// ------- 桁数 ------- //
#define RESULT_UI_PRISONERNUM_DIGIT (2)
#define RESULT_UI_BONUS_DIGIT (6)

// ------- 追加得点 ------- //
#define RESULT_UI_CONVERSION (1000)

#define RESULT_UI_TEX_TYPE (9)
// =====================================================================================================================================================================
// 静的メンバ変数の初期化
// =====================================================================================================================================================================
LPDIRECT3DTEXTURE9		CResultUI::m_TexNum[RESULT_UI_MAX] = {};					// バインドするテクスチャの情報

D3DXVECTOR3				CResultUI::m_Pos[RESULT_UI_MAX] = {
	RESULT_UI_BG_POS,
	RESULT_UI_NAME_POS,
	RESULT_UI_1P_POS,
	RESULT_UI_2P_POS,
	RESULT_UI_EVALUATION0_POS_1P,
	RESULT_UI_EVALUATION1_POS_1P,
	RESULT_UI_EVALUATION2_POS_1P,
	RESULT_UI_EVALUATION0_POS_2P,
	RESULT_UI_EVALUATION1_POS_2P,
	RESULT_UI_EVALUATION2_POS_2P,
	RESULT_UI_MISSIONCOMPLAYER_1_POS,
	RESULT_UI_MISSIONCOMPLAYER_2_POS,
};

D3DXVECTOR3				CResultUI::m_Size[RESULT_UI_MAX] = {
	RESULT_UI_BG_SIZE,
	RESULT_UI_NAME_SIZE,
	RESULT_UI_1P_SIZE,
	RESULT_UI_2P_SIZE,
	RESULT_UI_EVALUATION0_SIZE_1P,
	RESULT_UI_EVALUATION1_SIZE_1P,
	RESULT_UI_EVALUATION2_SIZE_1P,
	RESULT_UI_EVALUATION0_SIZE_2P,
	RESULT_UI_EVALUATION1_SIZE_2P,
	RESULT_UI_EVALUATION2_SIZE_2P,
	RESULT_UI_MISSIONCOMPLAYER_1_SIZE,
	RESULT_UI_MISSIONCOMPLAYER_2_SIZE,
};

int				CResultUI::m_nTotalScore[CPlayer::PLAYER_NUM_TWO] = {};
int				CResultUI::m_nBonusScore[CPlayer::PLAYER_NUM_TWO] = {};
int				CResultUI::m_PlayerScore[CPlayer::PLAYER_NUM_TWO] = {};

// =====================================================================================================================================================================
//
// コンストラクタ
//
// =====================================================================================================================================================================
CResultUI::CResultUI()
{
	for (int nCnt = 0; nCnt < RESULT_UI::RESULT_UI_MAX; nCnt++)
	{
		// ポインタの初期化
		m_apScene2D[nCnt] = nullptr;
	}

	for (int nCnt = 0; nCnt < 3; nCnt++)
	{
		m_bUseUIFlag[nCnt] = false;
		m_bUse_One[nCnt] = false;
	}

	for (int nCnt = 0; nCnt < CPlayer::PLAYER_NUM_MAX; nCnt++)
	{
		m_pBonusScore[nCnt] = nullptr;
		m_pPrisonerNum[nCnt] = nullptr;
		m_nPrisonerNum[nCnt] = 0;
	}

	m_nBonusScore[CPlayer::PLAYER_NUM_TWO] = {};
	m_bPrisonerNum = false;
	m_bBonusScore = false;
	m_bEvaluation = false;
	m_nWaitTime = 0;
	m_bWaitFlag = false;
	m_nColCnt = 0;
	m_nTotalScore[CPlayer::PLAYER_NUM_TWO] = {};
	m_PlayerScore[CPlayer::PLAYER_NUM_TWO] = {};
}

// =====================================================================================================================================================================
//
// デストラクタ
//
// =====================================================================================================================================================================
CResultUI::~CResultUI()
{
}

// =====================================================================================================================================================================
//
// 初期化処理
//
// =====================================================================================================================================================================
HRESULT CResultUI::Init(void)
{
	// ゲームクラスのポインタ取得
	CGame *pGame = (CGame*)CManager::GetBaseMode();

	if (CPlayer::GetTwoPPlayFlag())
	{
		for (int nCnt = 0; nCnt < CPlayer::PLAYER_NUM_MAX; nCnt++)
		{
			if (pGame->GetPlayer((TAG)nCnt) && pGame->GetPlayer((TAG)nCnt)->GetPlayerUI())
			{
				// スコアの取得
				m_PlayerScore[nCnt] = pGame->GetPlayer((TAG)nCnt)->GetPlayerUI()->GetScore();
			}
		}
	}
	else
	{
		if (pGame->GetPlayer((TAG)0) && pGame->GetPlayer((TAG)0)->GetPlayerUI())
		{
			// スコアの取得
			m_PlayerScore[0] = pGame->GetPlayer((TAG)0)->GetPlayerUI()->GetScore();
		}
	}

	// UIをまとめて生成する
	ResultUICreate();
	// α値を設定
	m_apScene2D[RESULT_UI_BG]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.6f));
	// 出現フラグの0番目を許可
	m_bUseUIFlag[0] = true;
	// 待ち時間の設定
	SetWaitTime(120);

	return S_OK;
}

// =====================================================================================================================================================================
//
// 終了処理
//
// =====================================================================================================================================================================
void CResultUI::Uninit(void)
{
	// uiの解放
	for (int nCnt = 0; nCnt < RESULT_UI::RESULT_UI_MAX; nCnt++)
	{
		if (m_apScene2D[nCnt])
		{
			// 終了
			m_apScene2D[nCnt]->Rerease();
			m_apScene2D[nCnt] = nullptr;

			// デリートフラグを有効にする
			SetDeleteFlag(true);
		}
	}

	for (int nCnt = 0; nCnt < CPlayer::PLAYER_NUM_MAX; nCnt++)
	{
		// ナンバー形の解放
		if (m_pBonusScore[nCnt] != nullptr)
		{
			m_pBonusScore[nCnt]->Rerease();
			m_pBonusScore[nCnt] = nullptr;
		}
		if (m_pPrisonerNum[nCnt] != nullptr)
		{
			m_pPrisonerNum[nCnt]->Rerease();
			m_pPrisonerNum[nCnt] = nullptr;
		}
	}
}

// =====================================================================================================================================================================
//
// 更新処理
//
// =====================================================================================================================================================================
void CResultUI::Update(void)
{
	for (int nCnt = 0; nCnt < RESULT_UI::RESULT_UI_MAX; nCnt++)
	{
		if (m_apScene2D[nCnt])
		{
			// 更新
			m_apScene2D[nCnt]->Update();
		}
	}

	// ゲームモードだった時
	if (CManager::GetMode() == CManager::MODE_GAME)
	{
		// ゲームクラスのポインタ取得
		CGame *pGame = (CGame*)CManager::GetBaseMode();
		if (pGame != nullptr && pGame->GetResultManager() != nullptr)
		{
			// 描画条件確認
			DrawConditions();
			// 待ち時間の設定
			ResultUiOrder(m_bUseUIFlag[0], m_bUseUIFlag[1], m_bUseUIFlag[2]);
			// 条件ごとの処理
			Conditions();
		}
	}
}

// =====================================================================================================================================================================
//
// 描画処理
//
// =====================================================================================================================================================================
void CResultUI::Draw(void)
{
	for (int nCnt = 0; nCnt < RESULT_UI::RESULT_UI_MAX; nCnt++)
	{
		if (m_apScene2D[nCnt])
		{
			// 描画
			m_apScene2D[nCnt]->Draw();
		}
	}
}

// =====================================================================================================================================================================
//
// タイトルUIの生成
//
// =====================================================================================================================================================================
CResultUI * CResultUI::Create()
{
	//メモリの確保
	CResultUI *pResultUI = new CResultUI();

	// 初期化
	pResultUI->Init();

	//オブジェタイプ設定してSceneに所有権を渡す
	CUIManager::AddUIList(std::move(pResultUI));

	return pResultUI;
}

// =====================================================================================================================================================================
//
// Uiをまとめて生成する
//
// =====================================================================================================================================================================
void CResultUI::ResultUICreate()
{
	// 数字以外をまとめて生成する
	for (int nCnt = 0; nCnt < RESULT_UI::RESULT_UI_MAX; nCnt++)
	{
		if (!m_apScene2D[nCnt])
		{
			// シーン2Dの生成
			m_apScene2D[nCnt] = CScene2D::Create(m_Pos[nCnt], m_Size[nCnt]);
			// 一旦全て非表示にする
			m_apScene2D[nCnt]->SetDisp(false);


			if (nCnt >= RESULT_UI_EVALUATION02P)
			{
				// テクスチャの割り当て
				m_apScene2D[nCnt]->BindTexture(CTexture::GetTexture((CTexture::TEX_TYPE)(nCnt + CTexture::TEX_UI_RESULT_BG -3)));
			}
			else
			{
				// テクスチャの割り当て
				m_apScene2D[nCnt]->BindTexture(CTexture::GetTexture((CTexture::TEX_TYPE)(nCnt + CTexture::TEX_UI_RESULT_BG)));
			}
		}
	}

	D3DXVECTOR3 pos[2];
	D3DXVECTOR3 size[2];
	pos[0] = RESULT_UI_PRISONERNUM_POS_1P;
	pos[1] = RESULT_UI_PRISONERNUM_POS_2P;
	size[0] = RESULT_UI_PRISONERNUM_SIZE_1P;
	size[1] = RESULT_UI_PRISONERNUM_SIZE_2P;
	D3DXVECTOR3 Scorepos[2];
	D3DXVECTOR3 Scoresize[2];
	Scorepos[0] = RESULT_UI_BONUS_POS_1P;
	Scorepos[1] = RESULT_UI_BONUS_POS_2P;
	Scoresize[0] = RESULT_UI_BONUS_SIZE_1P;
	Scoresize[1] = RESULT_UI_BONUS_SIZE_2P;


	for (int nCnt = 0; nCnt < CPlayer::PLAYER_NUM_MAX; nCnt++)
	{
		// 残りの捕虜の数用UI
		m_pPrisonerNum[nCnt] = CMultiNumber::Create(
			pos[nCnt],
			size[nCnt],
			m_nPrisonerNum[nCnt],
			RESULT_UI_PRISONERNUM_DIGIT,
			CScene::OBJTYPE_UI);

		// 追加得点用UI
		m_pBonusScore[nCnt] = CMultiNumber::Create(
			Scorepos[nCnt],
			Scoresize[nCnt],
			m_nBonusScore[nCnt],
			RESULT_UI_BONUS_DIGIT,
			CScene::OBJTYPE_UI);
	}
}

// =====================================================================================================================================================================
//
// 全て描画させる
//
// =====================================================================================================================================================================
void CResultUI::AllDraw()
{
	for (int nCnt = 0; nCnt < RESULT_UI_MAX; nCnt++)
	{
		if (m_apScene2D[nCnt] != nullptr)
		{
			m_apScene2D[nCnt]->SetDisp(true);
		}
	}

	for (int nCnt = 0; nCnt < CPlayer::PLAYER_NUM_MAX; nCnt++)
	{
		if (m_pPrisonerNum[nCnt] != nullptr && m_pBonusScore[nCnt] != nullptr)
		{
			m_pPrisonerNum[nCnt]->SetDisp(true);
			m_pBonusScore[nCnt]->SetDisp(true);
		}
	}
}
// =====================================================================================================================================================================
//
// 全て描画させない
//
// =====================================================================================================================================================================
void CResultUI::AllNotDraw()
{
	for (int nCnt = 0; nCnt < RESULT_UI_MAX; nCnt++)
	{
		if (m_apScene2D[nCnt] != nullptr)
		{
			m_apScene2D[nCnt]->SetDisp(false);
		}
	}

	for (int nCnt = 0; nCnt < CPlayer::PLAYER_NUM_MAX; nCnt++)
	{
		if (m_pPrisonerNum[nCnt] != nullptr && m_pBonusScore[nCnt] != nullptr)
		{
			m_pPrisonerNum[nCnt]->SetDisp(false);
			m_pBonusScore[nCnt]->SetDisp(false);
		}
	}
}

// =====================================================================================================================================================================
//
// 0番目のリザルトで表示するUIの設定
//
// =====================================================================================================================================================================
void CResultUI::Result0Draw()
{
	// 描画する列挙型を指定
	if (m_apScene2D[RESULT_UI_BG] != nullptr &&
		m_apScene2D[RESULT_UI_NAME] != nullptr &&
		m_apScene2D[RESULT_UI_1P] != nullptr&&
		m_apScene2D[RESULT_UI_2P] != nullptr)
	{
		m_apScene2D[RESULT_UI_BG]->SetDisp(true);
		m_apScene2D[RESULT_UI_NAME]->SetDisp(true);
		m_apScene2D[RESULT_UI_1P]->SetDisp(true);

		if (CPlayer::GetTwoPPlayFlag())
		{
			m_apScene2D[RESULT_UI_2P]->SetDisp(true);
		}
	}
}

// =====================================================================================================================================================================
//
// 1番目のリザルトで表示するUIの設定
//
// =====================================================================================================================================================================
void CResultUI::Result1Draw()
{
	// 描画する列挙型を指定
	if (m_apScene2D[RESULT_UI_MISSIONCOMPLAYER_1] != nullptr &&
		m_apScene2D[RESULT_UI_MISSIONCOMPLAYER_2] != nullptr)
	{
		//AllNotDraw();
		for (int nCnt = 0; nCnt < RESULT_UI_MAX; nCnt++)
		{
			if (m_apScene2D[nCnt] != nullptr)
			{
				m_apScene2D[nCnt]->SetDisp(false);
			}
		}

		for (int nCnt = 0; nCnt < CPlayer::PLAYER_NUM_MAX; nCnt++)
		{
			if (m_pPrisonerNum[nCnt] != nullptr && m_pBonusScore[nCnt] != nullptr)
			{
				m_pPrisonerNum[nCnt]->SetDisp(false);
				m_pBonusScore[nCnt]->SetDisp(false);
			}
		}

		if (CManager::GetGame()->GetMap()->GetMapNum() == CMap::MAP_1_BOSS)
		{
			m_apScene2D[RESULT_UI_MISSIONCOMPLAYER_1]->SetDisp(true);
			Flashing(m_apScene2D[RESULT_UI_MISSIONCOMPLAYER_1]);
		}
		else if (CManager::GetGame()->GetMap()->GetMapNum() == CMap::MAP_2_BOSS)
		{
			m_apScene2D[RESULT_UI_MISSIONCOMPLAYER_2]->SetDisp(true);
			Flashing(m_apScene2D[RESULT_UI_MISSIONCOMPLAYER_2]);
		}

		// ゲームモードだった時
		if (CManager::GetMode() == CManager::MODE_GAME)
		{
			// ゲームクラスのポインタ取得
			CGame *pGame = (CGame*)CManager::GetBaseMode();
			if (pGame != nullptr && pGame->GetResultManager() != nullptr)
			{
				if (pGame->GetResultManager()->GetResultState() == CResultManager::RESULT_STATE::RESULT_STATE_1)
				{
					// リザルトモードを次のモードに移行するためのフラグをtrueにする
					pGame->GetResultManager()->SetNextFlag(true);
				}
			}
		}
	}
}

// =====================================================================================================================================================================
//
// マルチナンバーに値を代入
//
// =====================================================================================================================================================================
void CResultUI::ScoreCal()
{
	CPlayer *pPlayer[CPlayer::PLAYER_NUM_TWO];

	if (CPlayer::GetTwoPPlayFlag())
	{
		// プレイヤーのポインタを取得
		for (int nCnt = 0; nCnt < CPlayer::PLAYER_NUM_MAX; nCnt++)
		{
			pPlayer[nCnt] = CManager::GetBaseMode()->GetPlayer((TAG)nCnt);

			if (pPlayer[nCnt] != nullptr)
			{
				// 描画許可が出たら処理を通す
				if (m_bPrisonerNum)
				{
					// 数字の描画許可
					if (m_pPrisonerNum[nCnt] != nullptr)
					{
						m_pPrisonerNum[nCnt]->SetDisp(true);
					}
					// 目標の値になるまで値を計算
					TargetValue(pPlayer[nCnt]->GetLife(), m_nPrisonerNum[nCnt], 1, m_pPrisonerNum[nCnt]);
				}
				// 描画許可が出たら処理を通す
				if (m_bBonusScore)
				{
					// 数字の描画許可
					if (m_pBonusScore[nCnt] != nullptr)
					{
						m_pBonusScore[nCnt]->SetDisp(true);
					}

					if (m_nBonusScore[nCnt] >= 100000)
					{
						// 目標の値になるまで値を計算
						TargetValue(pPlayer[nCnt]->GetLife() * CScoreManager::GetScorePoint(CScoreManager::SCORE_BONUS), m_nBonusScore[nCnt], 10000, m_pBonusScore[nCnt]);
					}
					else
					{
						// 目標の値になるまで値を計算
						TargetValue(pPlayer[nCnt]->GetLife() * CScoreManager::GetScorePoint(CScoreManager::SCORE_BONUS), m_nBonusScore[nCnt], 1000, m_pBonusScore[nCnt]);
					}
				}
			}
		}
	}
	else
	{
		pPlayer[0] = CManager::GetBaseMode()->GetPlayer((TAG)0);

		if (pPlayer[0] != nullptr)
		{
			// 描画許可が出たら処理を通す
			if (m_bPrisonerNum)
			{
				// 数字の描画許可
				if (m_pPrisonerNum[0] != nullptr)
				{
					m_pPrisonerNum[0]->SetDisp(true);
					m_pPrisonerNum[1]->SetMultiNumber(0);
					m_pPrisonerNum[1]->SetDisp(false);
				}
				// 目標の値になるまで値を計算
				TargetValue(pPlayer[0]->GetLife(), m_nPrisonerNum[0], 1, m_pPrisonerNum[0]);
			}
			// 描画許可が出たら処理を通す
			if (m_bBonusScore)
			{
				// 数字の描画許可
				if (m_pBonusScore[0] != nullptr)
				{
					m_pBonusScore[0]->SetDisp(true);
					m_pBonusScore[1]->SetMultiNumber(0);
					m_pBonusScore[1]->SetDisp(false);
				}

				if (m_nBonusScore[0] >= 100000)
				{
					// 目標の値になるまで値を計算
					TargetValue(pPlayer[0]->GetLife() * CScoreManager::GetScorePoint(CScoreManager::SCORE_BONUS), m_nBonusScore[0], 10000, m_pBonusScore[0]);
				}
				else
				{
					// 目標の値になるまで値を計算
					TargetValue(pPlayer[0]->GetLife() * CScoreManager::GetScorePoint(CScoreManager::SCORE_BONUS), m_nBonusScore[0], 1000, m_pBonusScore[0]);

				}
			}
		}
	}
}

// =====================================================================================================================================================================
//
// 条件によって処理を進める
//
// =====================================================================================================================================================================
void CResultUI::Conditions()
{
	// ゲームモードだった時
	if (CManager::GetMode() == CManager::MODE_GAME)
	{
		// ゲームクラスのポインタ取得
		CGame *pGame = (CGame*)CManager::GetBaseMode();
		if (pGame != nullptr && pGame->GetResultManager() != nullptr)
		{
			if (pGame->GetResultManager()->GetResultState() == CResultManager::RESULT_STATE::RESULT_STATE_0)
			{
				// マルチナンバーに値を代入
				ScoreCal();

				// 描画許可が出た時
				if (m_bEvaluation == true)
				{
					// 捕虜の数によって結果が変わる
					// 条件によって描画する 評価
					if (m_apScene2D[RESULT_UI_EVALUATION01P] != nullptr&&
						m_apScene2D[RESULT_UI_EVALUATION02P] != nullptr)
					{
						m_apScene2D[RESULT_UI_EVALUATION01P]->SetDisp(true);

						if (CPlayer::GetTwoPPlayFlag())
						{
							m_apScene2D[RESULT_UI_EVALUATION02P]->SetDisp(true);
						}

						m_apScene2D[RESULT_UI_EVALUATION01P]->Flashing();
						m_apScene2D[RESULT_UI_EVALUATION02P]->Flashing();
					}

					// リザルトモードを次のモードに移行するためのフラグをtrueにする
					pGame->GetResultManager()->SetNextFlag(true);
				}
			}
		}
	}
}

// =====================================================================================================================================================================
//
// 目標の値になるまで値を計算
//
// =====================================================================================================================================================================
void CResultUI::TargetValue(const int &Target, int &Value, int Add , CMultiNumber *pMultiNumber)
{
	// 目標値より値が小さかった時
	if (Target > Value)
	{
		// 値を加算
		Value += Add;

		//音の再生　ﾄｩﾙﾙﾙ
		CManager::GetSound()->Play(CSound::LABEL_SE_ADD_SCORE00);

		// 値が目標値を超えた時
		if (Target < Value)
		{
			// 値に目標値の値を代入
			Value = Target;
		}

		// マルチナンバーに値を代入
		pMultiNumber->SetMultiNumber((int)Value);
	}

	else
	{
		for (int nCnt = 0; nCnt < CPlayer::PLAYER_NUM_MAX; nCnt++)
		{
			if (pMultiNumber == m_pPrisonerNum[nCnt])
			{
				// 出現フラグの1番目を許可
				m_bUseUIFlag[1] = true;
			}
			if (pMultiNumber == m_pBonusScore[nCnt])
			{
				// 出現フラグの2番目を許可
				m_bUseUIFlag[2] = true;
			}
		}
	}
}

// =====================================================================================================================================================================
//
// 待ち時間が終わった時に結果を返す
//
// =====================================================================================================================================================================
void CResultUI::WaitTime(int nTime ,bool &bFlag, bool &bUse)
{
	//static std::once_flag flag;
	//std::call_once(flag, SetWaitTime(nTime));

	// 1度だけ処理を通す
	//CALL_ONCE(SetWaitTime(nTime));

	// 待機時間を減少させる
	m_nWaitTime--;

	//時間が0以下になった時
	if (m_nWaitTime <= 0)
	{
		// フラグをtrueにする
		if (!bFlag)
		{
			bFlag = true;
			bUse = true;
		}
		SetWaitTime(nTime);
	}
}

// =====================================================================================================================================================================
//
// リザルトUIの表示順番
//
// =====================================================================================================================================================================
void CResultUI::ResultUiOrder(bool bUse0, bool bUse1, bool bUse2)
{
	if (bUse0)
	{
		// 待ち時間の設定
		if (m_bUse_One[0] == false)
		{
			WaitTime(120, m_bPrisonerNum, m_bUse_One[0]);
		}
	}
	if (bUse1)
	{
		// 待ち時間の設定
		if (m_bUse_One[1] == false)
		{
			WaitTime(120, m_bBonusScore, m_bUse_One[1]);
		}
	}
	if (bUse2)
	{
		// 待ち時間の設定
		if (m_bUse_One[2] == false)
		{
			WaitTime(120, m_bEvaluation, m_bUse_One[2]);
		}
	}
}

// =====================================================================================================================================================================
//
// Uiの描画条件
//
// =====================================================================================================================================================================
void CResultUI::DrawConditions()
{
	// 一度全てのリザルトUIを非表示にしてから次に表示するUIを決める
	AllNotDraw();

	CResultManager::RESULT_STATE state = CManager::GetGame()->GetResultManager()->GetResultState();

	switch (state)
	{
	case CResultManager::RESULT_STATE::RESULT_STATE_0:
		// リザルト0用のUIを表示
		Result0Draw();
		break;

	case CResultManager::RESULT_STATE::RESULT_STATE_1:
		// リザルト1用のUIを表示
		Result1Draw();
		break;
	}
}

// =====================================================================================================================================================================
//
// 点滅処理
//
// =====================================================================================================================================================================
void CResultUI::Flashing(CScene2D *m_apScene2D)
{
	// カウント加算
	m_nColCnt++;
	// 余りが0の時透明にする
	if (m_nColCnt % 60 == 0)
	{
		m_apScene2D->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	}
	// 余りが0の時通常状態にする
	else if (m_nColCnt % 30 == 0)
	{
		m_apScene2D->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
}

// =====================================================================================================================================================================
//
// トータルスコア計算処理
//
// =====================================================================================================================================================================
void CResultUI::TotalScoreCalculation()
{
	for (int nCnt = 0; nCnt < CPlayer::PLAYER_NUM_MAX; nCnt++)
	{
		// ゲームスコアとボーナススコアの計算
		m_nTotalScore[nCnt] = m_nBonusScore[nCnt] + m_PlayerScore[nCnt];
	}
	// スコアのセーブ
	CRankingUI::PlayerScoreSave();
}
