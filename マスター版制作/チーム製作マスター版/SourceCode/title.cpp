// =====================================================================================================================================================================
//
// タイトルの処理 [title.h]
// Author : fujiwara masato
//
// =====================================================================================================================================================================
#include "title.h"
#include "manager.h"
#include "renderer.h"
#include "inputKeyboard.h"
#include "fade.h"
#include "UIManager.h"
#include "titleUI.h"
#include "Xinput.h"
#include "XInputPad.h"
#include "UI.h"
#include "sound.h"

// =====================================================================================================================================================================
// マクロ定義
// =====================================================================================================================================================================
#define INTERBALCOUNT (30)
// =====================================================================================================================================================================
// 静的メンバ変数の初期化
// =====================================================================================================================================================================
CTitle::PLAYER_NUM		CTitle::m_PlayerNum = PLAYER_NUM_ONE;
// =====================================================================================================================================================================
// コンストラクタ
// =====================================================================================================================================================================
CTitle::CTitle()
{
	// タイトルの初期状態
	m_TitleMode = MODE_PENDING;
	m_nStagingInterval = 0;
	m_nStagingNum = 0;
	m_bEndStaging = false;
	m_PlayerNum = PLAYER_NUM_ONE;
}

//==========================================================
// デストラクタ
//==========================================================
CTitle::~CTitle()
{
}

//==========================================================
// 初期化
//==========================================================
HRESULT CTitle::Init(void)
{
	// UI生成
	CUIManager::Create();

	// タイトルUIの生成
	m_pTitleUI = CTitleUI::Create();

	return S_OK;
}

//==========================================================
// 終了
//==========================================================
void CTitle::Uninit(void)
{

}

//==========================================================
// 更新
//==========================================================
void CTitle::Update(void)
{
	TitleMode();

	if (m_TitleMode != MODE_FADE)
	{
		// エンターを押したとき
		if (CHossoLibrary::PressAnyButton() && m_TitleMode != MODE_STAGING)
		{
			// タイトルのモードを次のモードに移行する
			TitleModeNext();
			//決定音
			CManager::GetSound()->Play(CSound::LABEL_SE_DECISION);
		}
	}
	else
	{
		if (CManager::GetRenderer()->GetFade()->GetFadeState() == CFADE::FADESTATE::FADESTATE_NONE)
		{
			// ゲームモードへ状態遷移7
			CManager::GetRenderer()->GetFade()->SetFade(CFADE::FADETYPE::FADETYPE_MODE, CManager::MODE_TUTORIAL);

			//決定音
			CManager::GetSound()->Play(CSound::LABEL_SE_DECISION);
		}
	}
}

//==========================================================
// 描画処理
//==========================================================
void CTitle::Draw(void)
{
}

//==========================================================
// デバッグ情報表記
//==========================================================
void CTitle::ShowDebugInfo(void)
{
}

//==========================================================
// タイトルのモードを次のモードに移行する
//==========================================================
void CTitle::TitleModeNext()
{
	for (int nCnt = 0; nCnt < MODE_MAX; nCnt++)
	{
		if (m_TitleMode != nCnt && m_TitleMode < nCnt)
		{
			m_TitleMode = (TITLE_MODE)nCnt;
			break;
		}
	}
}

//==========================================================
// タイトルのモードごとの処理
//==========================================================
void CTitle::TitleMode()
{
	CKeyboard *Keyboard;
	Keyboard = CManager::GetInputKeyboard();
	CXInputPad *InpudPad[MAX_CONTROLLER] = {};

	switch (m_TitleMode)
	{
	case CTitle::MODE_PENDING:
		// 次のカウントの設定
		m_nStagingInterval = INTERBALCOUNT;
		break;
	case CTitle::MODE_STAGING:
		// 演出
		TitleStaging();
		break;
	case CTitle::MODE_CHARACTERSELECT:

		if (m_bEndStaging)
		{
			m_pTitleUI->SetDrawFlag(CTitleUI::UI_START, false);

			if (m_nStagingInterval <= 0)
			{
				// 描画フラグを変更する
				for (int nCnt = 0; nCnt < 3; nCnt++)
				{
					m_pTitleUI->SetDrawFlag(static_cast<CTitleUI::TITLE_UI> (nCnt + CTitleUI::UI_PLAYER_COUNT_1), true);
				}
			}
			else
			{
				m_nStagingInterval--;
			}
		}

		for (int nCnt = 0; nCnt < MAX_CONTROLLER; nCnt++)
		{
			InpudPad[nCnt] = CManager::GetPad((TAG)nCnt);

			if (Keyboard->GetKeyboardTrigger(DIK_UP) || InpudPad[nCnt]->GetTrigger(CXInputPad::JOYPADKEY_UP, 1) ||
				Keyboard->GetKeyboardTrigger(DIK_DOWN) || InpudPad[nCnt]->GetTrigger(CXInputPad::JOYPADKEY_DOWN, 1))
			{
				if (m_PlayerNum == PLAYER_NUM_ONE)
				{
					m_PlayerNum = PLAYER_NUM_TWO;
					m_pTitleUI->SetPos(CTitleUI::UI_ARROWMARK, D3DXVECTOR3(400.0f, 650.0f, 0.0f));
					//決定音
					CManager::GetSound()->Play(CSound::LABEL_SE_SELECT);
					break;
				}
				else
				{
					m_PlayerNum = PLAYER_NUM_ONE;
					m_pTitleUI->SetPos(CTitleUI::UI_ARROWMARK, D3DXVECTOR3(400.0f, 550.0f, 0.0f));
					//決定音
					CManager::GetSound()->Play(CSound::LABEL_SE_SELECT);
					break;
				}
			}
		}
		break;
	case CTitle::MODE_FADE:
		break;
	}
}

//==========================================================
// 演出
//==========================================================
void CTitle::TitleStaging()
{
	if (m_nStagingNum < 3)
	{
		// インターバルのカウントが0以下になった時
		if (m_nStagingInterval <= 0)
		{
			// 描画フラグをtrueにする
			m_pTitleUI->SetDrawFlag(static_cast<CTitleUI::TITLE_UI> (CTitleUI::UI_BULLETHOLE_1 + m_nStagingNum), true);
			// 効果音
			CManager::GetSound()->Play(CSound::LABEL_SE_SHOT_TITLE_BULLET);
			// 次のカウントの設定
			m_nStagingInterval = INTERBALCOUNT;

			m_nStagingNum++;
		}
		m_nStagingInterval--;
	}
	else
	{
		m_bEndStaging = true;
		m_TitleMode = MODE_CHARACTERSELECT;
		m_nStagingInterval = INTERBALCOUNT;
	}

}
