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
#include "map.h"
#include "sound.h"
//------------------------------------------------------------------------------
//静的メンバ変数の初期化
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//マクロ
//------------------------------------------------------------------------------
#define GO_SIGN_POS (D3DXVECTOR3(1180.0f,200.0f,0.0f))
#define GO_SIGN_SIZE (D3DXVECTOR3(80.0f,60.0f,0.0f))
#define GAMEOVER_SIZE (D3DXVECTOR3(450.0f, 150.0f, 0.0f))

//------------------------------------------------------------------------------
//コンストラクタ
//------------------------------------------------------------------------------
CGameManager::CGameManager()
{
	m_nCnt = 0;
	m_nTimeCnt = 0;
	m_nNowWave = 0;
	m_nWaveEnemyCnt = 0;
	m_nWavePrisonerCnt = 0;
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
	CPlayer *pPlayer = CManager::GetBaseMode()->GetPlayer(CONTROLLER::P1);
	CGame *pGame = (CGame*)CManager::GetBaseMode();

	m_nCnt++;

	//nullcheck
	if (pPlayer)
	{

		//特定の座標を超えた時
		if(pPlayer->GetPosition().x >= CManager::GetGame()->GetMap()->GetTransitionPos().x)
		{
			//マップ遷移
			CManager::GetRenderer()->GetFade()->SetFade(CFADE::FADETYPE::FADETYPE_MAPMOVE, CManager::GetGame()->GetMap()->GetTransitionMapID());
		}

		//まだウェーブが残っている時
		if (m_nNowWave <= CMap::WAVE::WAVE_MAX)
		{
			//今のウェーブの情報取得
			CMap::WAVE_INFO *pWaveInfo = pGame->GetMap()->GetWaveInfo(m_nNowWave);

			//nullcheck
			if (pWaveInfo)
			{
				//現在のマップ番号とイベントが発生するマップ番号があっているかどうか
				if (pWaveInfo->EventBeginMapNum == CManager::GetGame()->GetMap()->GetMapNum())
				{
					//特定の座標を超えた時
					if (pPlayer->GetPosition().x >= pWaveInfo->EventPos.x && pPlayer->GetCharacterState() != CCharacter::CHARACTER_STATE::CHARACTER_STATE_DEATH)
					{
						//ウェーブ開始
						StartWave();
					}
				}
			}
		}
	}

	//stateに応じた処理
	switch (m_state)
	{
		//通常かウェーブ状態のとき
	case CGameManager::GAMESTATE::NORMAL:
		//GoSign更新
		UpdateGoSign();

	case CGameManager::GAMESTATE::WAVE:

		//タイマー更新
		UpdateTimer();

		//ウェーブの時
		if (m_state == CGameManager::GAMESTATE::WAVE)
		{
			//ウェーブの更新
			UpdateWave();

			//GoSign非表示
			m_pScene2D_GoSign->SetDisp(false);
			m_nCnt = 0;

		}
		break;

	case CGameManager::GAMESTATE::RESULT:

		break;

	case CGameManager::GAMESTATE::GAMEOVER:
		UpdateGameover();

		break;
	default:
		break;

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
	CDebugProc::Print("------ GameManager ----------\n");

	CDebugProc::Print("NowWaveNum >> %d\n", m_nNowWave);
	CDebugProc::Print("GameState >> %d\n", m_state);
	CDebugProc::Print("m_nCnt >> %d\n", m_nCnt);
	CDebugProc::Print("m_nWavePrisonerCnt >> %d\n", m_nWavePrisonerCnt);
	CDebugProc::Print("m_nWaveEnemyCnt >> %d\n", m_nWaveEnemyCnt);

	CDebugProc::Print("m_nWaveEnemyNum >> %d\n", m_nWaveEnemyNum);
	CDebugProc::Print("m_nWavePrisonerNum >> %d\n", m_nWavePrisonerNum);
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
		//Goサイン生成
		pGameManager->m_pScene2D_GoSign = CScene2D::CreateSceneManagement(GO_SIGN_POS, GO_SIGN_SIZE,CScene::OBJTYPE_UI);
		pGameManager->m_pScene2D_GoSign->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_GAME_GO));
		pGameManager->m_pScene2D_GoSign->SetColor(WhiteColor);

		return pGameManager;
	}
	return nullptr;
}
//------------------------------------------------------------------------------
//ステート切り替え
//------------------------------------------------------------------------------
void CGameManager::SetGameState(GAMESTATE state)
{
	m_state = state;

	if (m_state == CGameManager::GAMESTATE::GAMEOVER)
	{
		//ゲームオーバー表示されていない時
		if (!m_pScene2D_GameOver)
		{
			//ゲームオーバーUI生成
			m_pScene2D_GameOver = CScene2D::CreateSceneManagement(SCREEN_CENTER_POS, GAMEOVER_SIZE, CScene::OBJTYPE_UI);
			m_pScene2D_GameOver->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_GAME_GAMEOVER));

			m_nCnt = 0;
		}
	}

	//ゲームのステート切り替わった時の処理
	CManager::GetGame()->StateChangeReaction();
}
//------------------------------------------------------------------------------
//イベントクリア
//------------------------------------------------------------------------------
void CGameManager::EventClear()
{
	EndWave();
}

//------------------------------------------------------------------------------
//マップ遷移時にウェーブ再設定
//------------------------------------------------------------------------------
void CGameManager::MapTransitionWaveSet(int nNextID)
{
	EndWave();

	//次のマップ番号に合わせて現在のウェーブ番号を合わせる
	switch (nNextID)
	{

	case CMap::MAP_1_1:
		m_nNowWave = CMap::WAVE::WAVE_1_1_1;

			break;
	case CMap::MAP_1_2:
		m_nNowWave = CMap::WAVE::WAVE_1_2_1;

		break;
	case CMap::MAP_1_3:
		m_nNowWave = CMap::WAVE::WAVE_1_3_1;

		break;
	case CMap::MAP_1_BOSS:
		m_nNowWave = CMap::WAVE::WAVE_1_BOSS;

		//ボスマップに遷移したら無条件でウェーブ開始
		StartWave();

		break;
	case CMap::MAP_2_1:
		m_nNowWave = CMap::WAVE::WAVE_2_1_1;

		break;
	case CMap::MAP_2_2:
		m_nNowWave = CMap::WAVE::WAVE_2_2_1;

		break;
	case CMap::MAP_2_3:
		m_nNowWave = CMap::WAVE::WAVE_2_3_1;

		break;
	case CMap::MAP_2_BOSS:
		m_nNowWave = CMap::WAVE::WAVE_2_BOSS;

		//ボスマップに遷移したら無条件でウェーブ開始
		StartWave();

	default:
		break;
	}
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
	m_nCnt = 0;
	CManager::GetRenderer()->GetCamera()->SetCameraStopMove(false);
	m_nWaveEnemyCnt = 0;
	m_nWaveEnemyNum = 0;
	m_nWavePrisonerCnt = 0;
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
		EndWave();
		return;
	}

	//ウェーブのポインタ
	CMap::WAVE_INFO *pWaveInfo = CManager::GetGame()->GetMap()->GetWaveInfo(m_nNowWave);


	//まだ出てないのがいるとき
	//敵
	if (m_nWaveEnemyNum < (int)pWaveInfo->EnemyWaveInfo.size())
	{
		m_nWaveEnemyCnt++;
		//フレーム数が一緒になった時
		if (pWaveInfo->EnemyWaveInfo[m_nWaveEnemyNum]->nFrame <= m_nWaveEnemyCnt)
		{
			//敵生成
			CManager::GetGame()->GetMap()->WaveCreate(CMap::ARRANGEMENT_MODEL_ENEMY, pWaveInfo->EventPos, pWaveInfo->EnemyWaveInfo[m_nWaveEnemyNum]);
			m_nWaveEnemyNum++;
			m_nWaveEnemyCnt = 0;
		}
	}

	//まだ出てないのがいるとき
	//捕虜
	if (m_nWavePrisonerNum < (int)pWaveInfo->PrisonerWaveInfo.size())
	{
		m_nWavePrisonerCnt++;
		//フレーム数が一緒になった時
		if (pWaveInfo->PrisonerWaveInfo[m_nWavePrisonerNum]->nFrame <= m_nWavePrisonerCnt)
		{
			//敵生成
			CManager::GetGame()->GetMap()->WaveCreate(CMap::ARRANGEMENT_MODEL_PRISONER, pWaveInfo->EventPos, pWaveInfo->PrisonerWaveInfo[m_nWavePrisonerNum]);
			m_nWavePrisonerNum++;
			m_nWavePrisonerCnt = 0;
		}
	}
}

//------------------------------------------------------------------------------
//GoSign
//------------------------------------------------------------------------------
void CGameManager::UpdateGoSign()
{
	//nullcehck
	if (m_pScene2D_GoSign)
	{
		if (m_nCnt <= 300)
		{
			if (m_nCnt % 40 == 0)
			{
				//点滅
				m_pScene2D_GoSign->SetDisp(m_pScene2D_GoSign->GetDisp() ^ 1);
				if (m_pScene2D_GoSign->GetDisp())
				{
					CManager::GetSound()->Play(CSound::LABEL_SE_GO_SIGN);
				}
			}
		}
		else if (m_nCnt >= 600)
		{
			//カウント0にする
			m_nCnt = 0;
		}
		else
		{
			//非表示
			m_pScene2D_GoSign->SetDisp(false);
		}
	}
}
//------------------------------------------------------------------------------
//タイマー更新
//------------------------------------------------------------------------------
void CGameManager::UpdateTimer()
{
	// カウント加算
	m_nTimeCnt++;

	// 5秒経過した時
	if (m_nTimeCnt >= 300)
	{
		if (CManager::GetBaseMode()->GetPlayer(CONTROLLER::P1)->GetPlayerUI())
		{
			// タイマーの値を減少する
			CManager::GetBaseMode()->GetPlayer(CONTROLLER::P1)->GetPlayerUI()->DecrementTime();

			// タイムが0以下になった時
			if (CManager::GetBaseMode()->GetPlayer(CONTROLLER::P1)->GetPlayerUI()->GetTime() <= 0)
			{
				//ゲームオーバー
				SetGameState(CGameManager::GAMESTATE::GAMEOVER);
			}
		}

		// タイマーカウントをリセットする
		m_nTimeCnt = 0;
	}
}
//------------------------------------------------------------------------------
//ゲームオーバーの更新
//------------------------------------------------------------------------------
void CGameManager::UpdateGameover()
{
	m_nCnt++;

	//カウントがある程度になったら
	if (m_nCnt >= 300)
	{
		//タイトルに遷移
		CManager::GetRenderer()->GetFade()->SetFade(CFADE::FADETYPE::FADETYPE_MODE, CManager::MODE::MODE_TITLE);
		SetGameState(CGameManager::GAMESTATE::NONE);
	}
}
