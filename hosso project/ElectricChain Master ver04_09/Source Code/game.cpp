//------------------------------------------------------------------------------
//
//ゲーム処理  [game.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "game.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"
#include "player.h"
#include "fade.h"
#include "sound.h"
#include "keyboard.h"
#include "camera.h"
#include "Map.h"
#include "multinumber.h"
#include "pause.h"
#include "enemy.h"
#include "score.h"
#include "timer.h"
#include "ui.h"
#include "effectanimation2D.h"
#include "player_demo.h"
#include "Pad_XInput.h"
#include "miniMap.h"
#include "FrontUI.h"
//------------------------------------------------------------------------------
//静的メンバ変数の初期化
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//マクロ
//------------------------------------------------------------------------------
#define DEFAULT_PLAYER_POS	(D3DXVECTOR3(0.0f, 0.0f, -800.0f))		//プレイヤーの初期座標
#define ENEMY_MAX			(50)									//敵の最大数
#define DEFAULT_TIMER		(120)									//タイマー
#define ENEMY_POP_INTERVAL	(60)									//敵の出現のインターバル
#define ENEMY_SPAWN_NUM		(30)										//最初の敵の出現する数
#define GAMEEND_INTERVAL	(240)									//ゲーム終了してから遷移するまでのカウンタ
#define READY_COUNT			(3)										//ゲーム開始のカウントダウン
//------------------------------------------------------------------------------
//コンストラクタ
//------------------------------------------------------------------------------
CGame::CGame()
{
	//初期化
	m_pPause.reset();
	m_pMap.reset();
	m_pScore.reset();
	m_pTimer.reset();
	m_pPlayer.reset();

	m_nReadyCount = READY_COUNT + 1;
	m_nCntState = 0;
	m_nEnemyPopTime = 0;
	m_gamestate = STATE_READY;
}
//------------------------------------------------------------------------------
//デストラクタ
//------------------------------------------------------------------------------
CGame::~CGame()
{
	//開放
	m_pPause.reset();
	m_pMap.reset();
	m_pScore.reset();
	m_pTimer.reset();
	m_pPlayer.reset();

}

//------------------------------------------------------------------------------
//初期化処理
//------------------------------------------------------------------------------
HRESULT CGame::Init(HWND hWnd)
{
	//カメラ座標設定
	CManager::GetRenderer()->GetCamera()->SetCameraPos(DEFAULT_PLAYER_POS, DEFAULT_PLAYER_POS + D3DXVECTOR3(0.0f, 200, -450));
	CManager::GetRenderer()->GetCamera()->SetState(CCamera::CAMERA_GAME);

	//debug用
	if (CHossoLibrary::CheckDebugPlayer())
	{
		//プレイヤー生成
		//AI debug用
		m_pPlayer = CPlayer_Demo::Create(DEFAULT_PLAYER_POS);
	}
	else
	{
		//プレイヤー生成
		m_pPlayer = CPlayer::Create(DEFAULT_PLAYER_POS);
	}

	//マップ生成
	m_pMap = CMap::Create();

	//タイマー
	m_pTimer = CTimer::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f,95.0f,0.0f), DEFAULT_TIMER);

	//スコア
	m_pScore = CScore::Create();

	//ミニマップ生成
	CMiniMap::Create();

	//ゲームのUI読み込み
	CUI::LoadPlace(CUI::SCENE_GAME);

	//コンボパターン
	//コントローラが接続されているかどうかでテクスチャ差し替え
	CManager::GetXInput()->GetConnect() ?
		CScene2D_UI::Create(D3DXVECTOR3(170.0f, 80.0f, 0.0f), D3DXVECTOR3(300.0f, 120.0f, 0.0f), WhiteColor, CTexture::TEX_UI_GAME_X_COMBOPATTERN, CScene::OBJTYPE_2DUI) :
		CScene2D_UI::Create(D3DXVECTOR3(170.0f, 80.0f, 0.0f), D3DXVECTOR3(300.0f, 120.0f, 0.0f), WhiteColor, CTexture::TEX_UI_GAME_KEY_COMBOPATTERN, CScene::OBJTYPE_2DUI);

	//初期化
	SetGamestate(CGame::STATE_READY);

	return S_OK;
}

//------------------------------------------------------------------------------
//終了処理
//------------------------------------------------------------------------------
void CGame::Uninit()
{
	//終了処理
	CScene::ReleaseAll();
}

//------------------------------------------------------------------------------
//更新処理
//------------------------------------------------------------------------------
void CGame::Update()
{
	//ゲームの状態で処理を変える
	switch (m_gamestate)
	{
	case CGame::STATE_READY:
		if (m_nCntState % 60 == 0)
		{
			//カウンタ++
			m_nReadyCount--;

			//カウントが0になった時
			if (m_nReadyCount <= 0)
			{
				//ゲーム開始
				SetGamestate(CGame::STATE_NORMAL);
				CFrontUI::Create(SCREEN_CENTER_POS, D3DXVECTOR3(850.0f, 300.0f, 0.0f), WhiteColor, CFrontUI::GAMESTART);
				CEffectAnimation2D::Create(SCREEN_CENTER_POS, D3DXVECTOR3(1000.0f, 1000.0f, 0.0f), CTexture::SEPARATE_TEX_EFFECT_GAME_START, 0.0f, 2, CScene::OBJTYPE_2DEFFECT);
				break;
			}

			//数値生成
			std::shared_ptr<CMultiNumber> pMultiNumber = CMultiNumber::Create(SCREEN_CENTER_POS, D3DXVECTOR3(250.0f, 400.0f, 0.0f), m_nReadyCount, 1, CScene::OBJTYPE_NUMBER);
			pMultiNumber->Settype(CMultiNumber::TYPE_CENTER_DISAPPEAR);
		}

		//一番最初に処理通過させたいから後で加算
		m_nCntState++;
		break;

		//通常時
	case CGame::STATE_NORMAL:

		//敵リスポーン
		EnemyRespawn();

		//タイマー更新
		m_pTimer->Update();

		//Pでポーズ状態
		if (CHossoLibrary::CheckPause())
		{
			SetGamestate(CGame::STATE_PAUSE);
		}
		break;

		//ポーズ中
	case CGame::STATE_PAUSE:
		//nullcheck
		if (m_pPause)
		{
			//ポーズでオプションを開いていなかった場合
			if (!m_pPause->GetOptionWindow())
			{
				//Pでポーズ状態
				if (CHossoLibrary::CheckPause() || CHossoLibrary::CheckCancel())
				{
					//通常状態に戻す
					SetGamestate(CGame::STATE_NORMAL);
				}
			}
			if (CScene::CheckStop())
			{
				//更新
				//Scene側の更新が止まっているのでこっちで更新
				//描画はScene側で
				m_pPause->Update();
			}
		}
		break;
	case CGame::STATE_GAMEOVER:

		break;
		//ゲームクリア
	case CGame::STATE_GAMECLEAR:
		m_nCntState--;
		if (m_nCntState <= 0)
		{
			//スコア保存
			m_pScore->SaveScore();

			//リザルトに遷移
			CManager::GetRenderer()->GetFade()->SetModeFade(CManager::MODE_RESULT);
			SetGamestate(CGame::STATE_NONE);
		}
		break;
	}
}

//------------------------------------------------------------------------------
//描画処理
//------------------------------------------------------------------------------
void CGame::Draw()
{

}
//------------------------------------------------------------------------------
//デバッグ情報表記
//------------------------------------------------------------------------------
void CGame::ShowDebugInfo()
{
#ifdef _DEBUG
	//キーボードのポインタ
	CKeyboard *pKeyboard = CManager::GetKeyboard();

	//[0]キーを押した時
	if (pKeyboard->GetTrigger(DIK_0))
	{
		//ステート変更
		SetGamestate(CGame::STATE_GAMECLEAR);
		return;
	}

	if (ImGui::TreeNode("GameDebugCommand"))
	{
		if (ImGui::Button("AllEnemyBlueDamage"))
		{
			//Sceneのリスト
			std::vector<std::shared_ptr<CScene>> pSceneList;

			//敵のリスト取得
			CScene::GetSceneList(CScene::OBJTYPE_ENEMY, pSceneList);

			//nullcheck
			if (!pSceneList.empty())
			{
				//要素分
				for (size_t nCnt = 0; nCnt < pSceneList.size(); nCnt++)
				{
					//ポインタ取得 CMeshField型にキャスト
					CCharacter *pCharacter = ((CCharacter*)pSceneList[nCnt].get());

					//nullcheck
					if (pCharacter)
					{
						//無敵状態解除
						pCharacter->ApplyDamage(0, 999);
					}
				}
			}
		}

		if (ImGui::Button("EnemyCreate"))
		{
			CEnemy::Create(D3DXVECTOR3(float(rand() % 200), 50.0f, float(rand() % 200)), CEnemy::TYPE_NORMAL);
		}

		ImGui::TreePop();
	}
#endif //_DEBUG
}

//------------------------------------------------------------------------------
//ゲームステートセット
//------------------------------------------------------------------------------
void CGame::SetGamestate(STATE gamestate)
{
	//ステートが進んでいる場合
	if (m_gamestate != CGame::STATE_NONE)
	{
		//ステート変更
		m_gamestate = gamestate;

		switch (gamestate)
		{
		case STATE_READY:
			m_nCntState = 0;
			m_nReadyCount = READY_COUNT + 1;
			break;

		case STATE_NORMAL:
			if (m_pPause)
			{
				m_pPause->Release();
				m_pPause = nullptr;
			}
			CScene::SetStop(false);
			break;

		case STATE_PAUSE:
			if (!m_pPause)
			{
				m_pPause = CPause::Create();
			}
			CScene::SetStop(true);
			break;

		case CGame::STATE_GAMECLEAR:
			//カウンタリセット
			m_nCntState = GAMEEND_INTERVAL;

			//終了のテクスチャ
			CScene2D_UI::Create(SCREEN_CENTER_POS, SCREEN_SIZE, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.7f), CTexture::TEX_NONE, CScene::OBJTYPE_FRONT);
			CScene2D_UI::Create(SCREEN_CENTER_POS, D3DXVECTOR3(850.0f, 300.0f, 0.0f), WhiteColor, CTexture::TEX_FINISH, CScene::OBJTYPE_FRONT);

			//プレイヤーが生きてるか死んでるかで音再生
			GetPlayer()->GetAlive() ?
				CManager::GetSound()->Play(CSound::LABEL_SE_GAMECLEAR) :
				CManager::GetSound()->Play(CSound::LABEL_SE_GAMEOVER);

			//ゲームクリア
			break;

		case CGame::STATE_DEBUG:
			CScene::SetStop(true);
			break;
		}
	}
}
//------------------------------------------------------------------------------
//マップ取得
//------------------------------------------------------------------------------
CMap * CGame::GetMap()
{
	if (m_pMap)
	{
		return m_pMap.get();
	}
	return nullptr;
}
//------------------------------------------------------------------------------
//スコア取得
//------------------------------------------------------------------------------
CScore * CGame::GetScore()
{
	if (m_pScore)
	{
		return m_pScore.get();
	}
	return nullptr;
}
//------------------------------------------------------------------------------
//プレイヤー取得
//------------------------------------------------------------------------------
CPlayer * CGame::GetPlayer()
{
	if (m_pPlayer)
	{
		return m_pPlayer.get();
	}
	return nullptr;
}

//------------------------------------------------------------------------------
//敵のリスポーン
//------------------------------------------------------------------------------
void CGame::EnemyRespawn()
{
	//ある程度少なくなった時
	if (CEnemy::GetEnemyNum() <= 1 + m_nEnemuPopWave)
	{
		//カウントダウン
		m_nEnemyPopTime--;

		//カウント0のとき
		if (m_nEnemyPopTime < 0)
		{
			//ウェーブ追加
			m_nEnemuPopWave++;
			m_nEnemyPopTime = ENEMY_POP_INTERVAL + (m_nEnemuPopWave * 2);

			//出現
			CManager::GetSound()->Play(CSound::LABEL_SE_APPEAR);

			for (int nCnt = 0; nCnt < ENEMY_SPAWN_NUM + (m_nEnemuPopWave * 1.7f); nCnt++)
			{
				//最大値超えたら
				if (CEnemy::GetEnemyNum() >= ENEMY_MAX)
				{
					//抜ける
					break;
				}

				//敵の出現する座標計算
				D3DXVECTOR3 PopPos = D3DXVECTOR3(float(rand() % (200 + 45 * m_nEnemuPopWave) - rand() % (200 + 45 * m_nEnemuPopWave)),20.0f,float(rand() % (200 + 45 * m_nEnemuPopWave) - rand() % (200 + 45 * m_nEnemuPopWave)));

				//フィールドの広さ取得
				D3DXVECTOR3 FieldSize = CMap::GetFieldSize() * 0.5f;

				//フィールド外に出れないようにする
				CHossoLibrary::RangeLimit_Equal_Float(PopPos.x, -FieldSize.x, +FieldSize.x);
				CHossoLibrary::RangeLimit_Equal_Float(PopPos.z, -FieldSize.z, +FieldSize.z);

				//敵生成
				CEnemy::Create(PopPos, CEnemy::TYPE_NORMAL);

			}
		}
	}
}