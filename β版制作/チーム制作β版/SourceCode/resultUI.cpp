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

// =====================================================================================================================================================================
// マクロ定義
// =====================================================================================================================================================================
// ------- 座標 ------- //
#define RESULT_UI_BG_POS (SCREEN_CENTER_POS)
#define RESULT_UI_NAME_POS (D3DXVECTOR3(SCREEN_WIDTH * 0.5f,150.0f,0.0f))
#define RESULT_UI_1P_POS (D3DXVECTOR3(SCREEN_WIDTH * 0.25f,300.0f,0.0f))
#define RESULT_UI_2P_POS (D3DXVECTOR3(SCREEN_WIDTH * 0.75f,300.0f,0.0f))
#define RESULT_UI_EVALUATION0_POS_1P (D3DXVECTOR3(SCREEN_WIDTH * 0.25f,600.0f,0.0f))
#define RESULT_UI_EVALUATION1_POS_1P (D3DXVECTOR3(SCREEN_WIDTH * 0.25f,600.0f,0.0f))
#define RESULT_UI_EVALUATION2_POS_1P (D3DXVECTOR3(SCREEN_WIDTH * 0.25f,600.0f,0.0f))
#define RESULT_UI_EVALUATION0_POS_2P (D3DXVECTOR3(SCREEN_WIDTH * 0.75f,600.0f,0.0f))
#define RESULT_UI_EVALUATION1_POS_2P (D3DXVECTOR3(SCREEN_WIDTH * 0.75f,600.0f,0.0f))
#define RESULT_UI_EVALUATION2_POS_2P (D3DXVECTOR3(SCREEN_WIDTH * 0.75f,600.0f,0.0f))
#define RESULT_UI_MISSIONCOMP1_POS (SCREEN_CENTER_POS)
#define RESULT_UI_MISSIONCOMP2_POS (SCREEN_CENTER_POS)

#define RESULT_UI_PRISONERNUM_POS_1P (D3DXVECTOR3(SCREEN_WIDTH * 0.25f,400.0f,0.0f))
#define RESULT_UI_PRISONERNUM_POS_2P (D3DXVECTOR3(SCREEN_WIDTH * 0.75f,400.0f,0.0f))
#define RESULT_UI_BONUS_POS_1P (D3DXVECTOR3(SCREEN_WIDTH * 0.25f,500.0f,0.0f))
#define RESULT_UI_BONUS_POS_2P (D3DXVECTOR3(SCREEN_WIDTH * 0.75f,500.0f,0.0f))

// ------- サイズ ------- //
#define RESULT_UI_BG_SIZE (SCREEN_SIZE)
#define RESULT_UI_NAME_SIZE (D3DXVECTOR3(600.0f,100.0f,0.0))
#define RESULT_UI_1P_SIZE (D3DXVECTOR3(100.0f,100.0f,0.0f))
#define RESULT_UI_2P_SIZE (D3DXVECTOR3(100.0f,100.0f,0.0f))
#define RESULT_UI_EVALUATION0_SIZE_1P (D3DXVECTOR3(300.0f,100.0f,0.0f))
#define RESULT_UI_EVALUATION1_SIZE_1P (D3DXVECTOR3(300.0f,100.0f,0.0f))
#define RESULT_UI_EVALUATION2_SIZE_1P (D3DXVECTOR3(300.0f,100.0f,0.0f))
#define RESULT_UI_EVALUATION0_SIZE_2P (D3DXVECTOR3(300.0f,100.0f,0.0f))
#define RESULT_UI_EVALUATION1_SIZE_2P (D3DXVECTOR3(300.0f,100.0f,0.0f))
#define RESULT_UI_EVALUATION2_SIZE_2P (D3DXVECTOR3(300.0f,100.0f,0.0f))
#define RESULT_UI_MISSIONCOMP1_SIZE (D3DXVECTOR3(900.0f,250.0f,0.0f))
#define RESULT_UI_MISSIONCOMP2_SIZE (D3DXVECTOR3(900.0f,250.0f,0.0f))

#define RESULT_UI_PRISONERNUM_SIZE_1P (D3DXVECTOR3(100.0f,100.0f,0.0f))
#define RESULT_UI_PRISONERNUM_SIZE_2P (D3DXVECTOR3(100.0f,100.0f,0.0f))
#define RESULT_UI_BONUS_SIZE_1P (D3DXVECTOR3(200.0f,100.0f,0.0f))
#define RESULT_UI_BONUS_SIZE_2P (D3DXVECTOR3(200.0f,100.0f,0.0f))

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
	RESULT_UI_MISSIONCOMP1_POS,
	RESULT_UI_MISSIONCOMP2_POS,
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
	RESULT_UI_MISSIONCOMP1_SIZE,
	RESULT_UI_MISSIONCOMP2_SIZE,
};

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

	m_pBonusScore = nullptr;
	m_pPrisonerNum = nullptr;
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
	for (int nCnt = 25; nCnt < RESULT_UI_TEX_TYPE; nCnt++)
	{
		m_TexNum[RESULT_UI_MAX] = {
			CTexture::GetTexture((CTexture::TEX_TYPE)nCnt)};	// バインドするテクスチャの情報

	}
	// UIをまとめて生成する
	ResultUICreate();

	return S_OK;
}

// =====================================================================================================================================================================
//
// 終了処理
//
// =====================================================================================================================================================================
void CResultUI::Uninit(void)
{
	for (int nCnt = 0; nCnt < RESULT_UI::RESULT_UI_MAX; nCnt++)
	{
		if (m_apScene2D[nCnt])
		{
			// 終了
			m_apScene2D[nCnt]->Uninit();

			// デリートフラグを有効にする
			SetDeleteFlag(true);
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

	// 描画条件確認
	DrawConditions();
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

			if (nCnt == RESULT_UI_EVALUATION02P)
			{
				// テクスチャの割り当て
				m_apScene2D[nCnt]->BindTexture(CTexture::GetTexture((CTexture::TEX_TYPE)(RESULT_UI_EVALUATION01P)));
			}
			else if (nCnt == RESULT_UI_EVALUATION12P)
			{
				// テクスチャの割り当て
				m_apScene2D[nCnt]->BindTexture(CTexture::GetTexture((CTexture::TEX_TYPE)(RESULT_UI_EVALUATION11P)));
			}
			else if (nCnt == RESULT_UI_EVALUATION22P)
			{
				// テクスチャの割り当て
				m_apScene2D[nCnt]->BindTexture(CTexture::GetTexture((CTexture::TEX_TYPE)(RESULT_UI_EVALUATION21P)));
			}
			else if (nCnt >= RESULT_UI_MISSIONCOMP1)
			{
				// テクスチャの割り当て
				m_apScene2D[nCnt]->BindTexture(CTexture::GetTexture((CTexture::TEX_TYPE)(nCnt + 25 - 3)));
			}
			else
			{
				// テクスチャの割り当て
				m_apScene2D[nCnt]->BindTexture(CTexture::GetTexture((CTexture::TEX_TYPE)(nCnt + 25)));
			}
			// 最初は非表示にする
			//m_apScene2D[nCnt]->SetDisp(false);
		}
	}

	// 数字形を生成




}

// =====================================================================================================================================================================
//
// Uiの描画条件
//
// =====================================================================================================================================================================
void CResultUI::DrawConditions()
{
	// 描画許可が出た時
	/*if ()
	{
		m_apScene2D[]->SetDisp(true);
	}*/
	// 描画禁止が出た時
	/*if ()
	{
		m_apScene2D[]->SetDisp(false);
	}*/
}
