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
	m_nCnt = 0;
	m_nTimeCnt = 0;
	m_nNowWave = 0;
	m_nWaveCnt = 0;
	m_nWaveEnemyNum = 0;
	m_nWavePrisonerNum = 0;
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

	// それぞれのポインタ取得
	CPlayer *pPlayer = CManager::GetBaseMode()->GetPlayer();
	CGame *pGame = (CGame*)CManager::GetBaseMode();
	CMap::WAVE_INFO *pWaveInfo = pGame->GetMap()->GetWaveInfo(m_nNowWave);

	m_nCnt = 0;

	if (pPlayer)
	{
		if(pPlayer->GetPosition().x >= CManager::GetGame()->GetMap()->GetTransitionPos().x)
		{
			CManager::GetRenderer()->GetFade()->SetFade(CFADE::FADETYPE::FADETYPE_MAPMOVE, CManager::GetGame()->GetMap()->GetTransitionMapID());
		}

		if (pPlayer->GetPosition().x >= pWaveInfo->EventPos.x)
		{
			//ウェーブ開始
			StartWave();
		}
	}

	//stateに応じた処理
	switch (m_state)
	{
	case CGameManager::GAMESTATE::NORMAL:
		break;
	case CGameManager::GAMESTATE::WAVE:
		UpdateWave();
		break;
	case CGameManager::GAMESTATE::BOSSBUTTLE:
		break;

	}

	//GoSign更新
	UpdateGoSign();

	//タイマー更新
	UpdateTimer();
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
	CDebugProc::Print("NowWaveNum >> %d\n", m_nNowWave);

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
//------------------------------------------------------------------------------
//イベントクリア
//------------------------------------------------------------------------------
void CGameManager::EventClear()
{
	EndWave();
}

//------------------------------------------------------------------------------
//ウェーブ開始
//------------------------------------------------------------------------------
void CGameManager::StartWave()
{
	m_state = CGameManager::GAMESTATE::WAVE;
	CManager::GetRenderer()->GetCamera()->SetCameraStopMove(true);
}

//------------------------------------------------------------------------------
//ウェーブの終了
//------------------------------------------------------------------------------
void CGameManager::EndWave()
{
	m_state = CGameManager::GAMESTATE::NORMAL;
	CManager::GetRenderer()->GetCamera()->SetCameraStopMove(false);
	m_nWaveCnt = 0;
	m_nWaveEnemyNum = 0;
	m_nWavePrisonerNum = 0;
	m_nNowWave++;
}

//------------------------------------------------------------------------------
//ウェーブの更新
//------------------------------------------------------------------------------
void CGameManager::UpdateWave()
{
	if (m_nNowWave >= CMap::WAVE::WAVE_MAX)
	{
		return;
	}

	//ウェーブのポインタ
	CMap::WAVE_INFO *pWaveInfo = CManager::GetGame()->GetMap()->GetWaveInfo(m_nNowWave);

	m_nWaveCnt++;

	//まだ出てないのがいるとき
	if (m_nWaveEnemyNum < (int)pWaveInfo->EnemyWaveInfo.size())
	{
		//フレーム数が一緒になった時
		if (pWaveInfo->EnemyWaveInfo[m_nWaveEnemyNum]->nFrame == m_nWaveCnt)
		{
			//敵生成
			CManager::GetGame()->GetMap()->WaveCreate(CModel::ENEMY_MODEL, pWaveInfo->EventPos, pWaveInfo->EnemyWaveInfo[m_nWaveEnemyNum]);
			m_nWaveEnemyNum++;
			m_nWaveCnt = 0;
		}
	}
}

//------------------------------------------------------------------------------
//GoSign
//------------------------------------------------------------------------------
void CGameManager::UpdateGoSign()
{
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
}
//------------------------------------------------------------------------------
//タイマー更新
//------------------------------------------------------------------------------
void CGameManager::UpdateTimer()
{
	// ゲームモードでプレイ操作可能なタイミングの時
	if (m_state != CGameManager::GAMESTATE::RESULT)
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
