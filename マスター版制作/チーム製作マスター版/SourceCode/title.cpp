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
#define INTERBALCOUNT (40)
// =====================================================================================================================================================================
// 静的メンバ変数の初期化
// =====================================================================================================================================================================

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

	if (m_TitleMode == MODE_STAGING && m_bEndStaging)
	{
	}
	else
	{
		// エンターを押したとき
		if (CHossoLibrary::PressAnyButton() && CManager::GetRenderer()->GetFade()->GetFadeState() == CFADE::FADESTATE::FADESTATE_NONE)
		{
			if (m_TitleMode != MODE_FADE)
			{
				// タイトルのモードを次のモードに移行する
				TitleModeNext();
				//決定音
				CManager::GetSound()->Play(CSound::LABEL_SE_DECISION);
			}
			else
			{
				// ゲームモードへ状態遷移7
				CManager::GetRenderer()->GetFade()->SetFade(CFADE::FADETYPE::FADETYPE_MODE, CManager::MODE_TUTORIAL);

				//決定音
				CManager::GetSound()->Play(CSound::LABEL_SE_DECISION);
			}
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
		else if (m_TitleMode == MODE_PENDING)
		{
			m_TitleMode = MODE_STAGING;
			break;
		}
	}
}

//==========================================================
// タイトルのモードごとの処理
//==========================================================
void CTitle::TitleMode()
{
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

			// 描画フラグを変更する
			for (int nCnt = 0; nCnt < 2; nCnt++)
			{
				m_pTitleUI->SetDrawFlag(static_cast<CTitleUI::TITLE_UI> (nCnt + CTitleUI::UI_PLAYER_COUNT_1), true);
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
			// 次のカウントの設定
			m_nStagingInterval = INTERBALCOUNT;
		}

		m_nStagingInterval--;
		m_nStagingNum++;
	}
	else
	{
		m_bEndStaging = true;
	}
}
