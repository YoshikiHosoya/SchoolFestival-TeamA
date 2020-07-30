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
	// エンターを押したとき
	if (CHossoLibrary::PressAnyButton())
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
