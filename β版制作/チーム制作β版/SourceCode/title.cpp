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

// =====================================================================================================================================================================
// マクロ定義
// =====================================================================================================================================================================
// パッドボタン
#define PAD_A (pad->GetTrigger(pad->JOYPADKEY_A, 1))	// ジャンプ
#define PAD_B (pad->GetTrigger(pad->JOYPADKEY_B, 1))	// 乗り物から降りる
#define PAD_X (pad->GetTrigger(pad->JOYPADKEY_X, 1))	// 弾
#define PAD_Y (pad->GetTrigger(pad->JOYPADKEY_Y, 1))	// グレネード

// =====================================================================================================================================================================
// 静的メンバ変数の初期化
// =====================================================================================================================================================================

// =====================================================================================================================================================================
// コンストラクタ
// =====================================================================================================================================================================
CTitle::CTitle()
{
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
	// タイトルUIのポインタ
	if (m_pTitleUI)
	{
		// 終了
		m_pTitleUI->Uninit();
		m_pTitleUI = nullptr;
	}
}

//==========================================================
// 更新
//==========================================================
void CTitle::Update(void)
{
	// パッド取得
	CXInputPad *pad = CManager::GetPad();

	// エンターを押したとき
	if (CHossoLibrary::PressAnyButton() ||
		PAD_X ||
		PAD_Y ||
		PAD_A ||
		PAD_B)
	{
		// ゲームモードへ状態遷移
		CManager::GetRenderer()->GetFade()->SetFade(CFADE::FADETYPE::FADETYPE_MODE, CManager::MODE_TUTORIAL);
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
