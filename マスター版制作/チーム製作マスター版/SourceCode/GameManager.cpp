//------------------------------------------------------------------------------
//
//ゲームの進行管理  [GameManager.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "GameManager.h"
#include "scene2D.h"
#include "map.h"
#include "fade.h"
#include "Player.h"
#include "Playerui.h"
#include "game.h"
#include "camera.h"

//------------------------------------------------------------------------------
//静的メンバ変数の初期化
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//マクロ
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//コンストラクタ
//------------------------------------------------------------------------------
CGameManager::CGameManager()
{
	m_nTimeCnt = 0;
}
//------------------------------------------------------------------------------
//デストラクタ
//------------------------------------------------------------------------------
CGameManager::~CGameManager()
{

}

//------------------------------------------------------------------------------
//コンストラクタ
//------------------------------------------------------------------------------
void CGameManager::Update()
{
	m_nCnt++;

	CPlayer *pPlayer = CManager::GetBaseMode()->GetPlayer();

	if (pPlayer)
	{
		if(pPlayer->GetPosition().x >= 8500.0f)
		{
			CManager::GetRenderer()->GetFade()->SetFade(CFADE::FADETYPE::FADETYPE_MAPMOVE, CMap::MAP_1_BOSS);
		}
	}

	if (m_pScene2D_GoSign)
	{
		if (CManager::GetGame()->GetMap()->GetMapNum() == CMap::MAP_1_1)
		{
			if (m_nCnt % 40 == 0)
			{
				m_pScene2D_GoSign->SetDisp(m_pScene2D_GoSign->GetDisp() ^ 1);
			}
		}
	}

	// ゲームクラスのポインタ取得
	CGame *pGame = (CGame*)CManager::GetBaseMode();

	// ゲームモードでプレイ操作可能なタイミングの時
	if (pGame->GetGameMode() == CGame::GAME_MODE_NORMAL)
	{
		// カウント加算
		m_nTimeCnt++;
	}

	// 5秒経過した時
	if (m_nTimeCnt >= 300)
	{
		if (CManager::GetBaseMode()->GetPlayer()->GetPlayerUI())
		{
			// 体力が0より大きかった時
			if (CManager::GetBaseMode()->GetPlayer()->GetPlayerUI()->GetTime() > 0)
			{
				// タイマーの値を減少する
				CManager::GetBaseMode()->GetPlayer()->GetPlayerUI()->DecrementTime();
			}
			// タイマーが0以下になった時
			else
			{
			}
		}

		// タイマーカウントをリセットする
		m_nTimeCnt = 0;
	}
}

//------------------------------------------------------------------------------
//描画処理
//------------------------------------------------------------------------------
void CGameManager::Draw()
{

}

//------------------------------------------------------------------------------
//デバッグ情報表記
//------------------------------------------------------------------------------
void CGameManager::ShowDebugInfo()
{
#ifdef _DEBUG

	ImGui::End();
#endif
}

//------------------------------------------------------------------------------
//生成処理
//------------------------------------------------------------------------------
std::unique_ptr<CGameManager> CGameManager::Create()
{
	//メモリ確保
	std::unique_ptr<CGameManager> pGameManager(new CGameManager);

	//nullcheck
	if (pGameManager)
	{
		////Goサイン生成
		//pGameManager->m_pScene2D_GoSign = CScene2D::CreateSceneManagement(D3DXVECTOR3(1000.0f, 300.0f, 0.0f), D3DXVECTOR3(200.0f, 120.0f,0.0f),CScene::OBJTYPE_UI);
		//pGameManager->m_pScene2D_GoSign->BindTexture(CTexture::GetTexture(CTexture::TEX_ITEM_MEDAL));
		//pGameManager->m_pScene2D_GoSign->SetColor(WhiteColor);

		return pGameManager;
	}
	return nullptr;
}
