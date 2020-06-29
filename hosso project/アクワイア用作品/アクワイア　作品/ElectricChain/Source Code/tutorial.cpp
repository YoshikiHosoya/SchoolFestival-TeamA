//------------------------------------------------------------------------------
//
//チュートリアル処理  [tutorial.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "tutorial.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"
#include "fade.h"
#include "Map.h"
#include "miniMap.h"
#include "UI.h"
#include "Pad_XInput.h"
#include "player.h"
#include "enemy.h"
#include "keyboard.h"
#include "camera.h"
#include "effectanimation2D.h"
//------------------------------------------------------------------------------
//マクロ
//------------------------------------------------------------------------------
#define DEFAULT_PLAYER_POS				(D3DXVECTOR3(0.0f, 0.0f, -800.0f))	//初期座標
#define TUTORIAL_STEP_INTERVAL			(60)								//チュートリアルの項目をクリアしてから次の項目に入るまでのインターバル
#define ENEMY_POP_INTERVAL				(65)								//敵出現までのインターバル
#define ENEMY_SPACE						(400)								//チュートリアル用の敵の感覚
#define ENEMY_LINE						(INTEGER2(6,6))						//チュートリアル用の敵の列
//------------------------------------------------------------------------------
//静的メンバ変数の初期化
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//コンストラクタ
//------------------------------------------------------------------------------
CTutorial::CTutorial()
{
	//初期化
	m_pPlayer.reset();
	m_pTutorialStep.reset();
	m_pOK.reset();

	m_bEnemyPop = false;
	m_bClear = false;
	m_nEnemyPopTime = ENEMY_POP_INTERVAL;
	m_nCntStep = 0;
	m_step = CTutorial::TUTORIAL_NONE;
}
//------------------------------------------------------------------------------
//デストラクタ
//------------------------------------------------------------------------------
CTutorial::~CTutorial()
{
	m_pPlayer.reset();
	m_pTutorialStep.reset();
}
//------------------------------------------------------------------------------
//初期化処理
//------------------------------------------------------------------------------
HRESULT CTutorial::Init(HWND hWnd)
{
	//マップ生成
	CMap::Create();

	//チュートリアルの2D生成
	m_pTutorialStep = CScene2D::Create_Shared(D3DXVECTOR3(640.0f, 80.0f, 0.0f), D3DXVECTOR3(600.0f, 120.0f, 0.0f), CScene::OBJTYPE_UI);

	//プレイヤー生成
	m_pPlayer = CPlayer::Create(DEFAULT_PLAYER_POS);

	//ミニマップ生成
	CMiniMap::Create();

	//カメラ座標設定
	CManager::GetRenderer()->GetCamera()->SetCameraPos(DEFAULT_PLAYER_POS, DEFAULT_PLAYER_POS + D3DXVECTOR3(0.0f, 200, -600));
	CManager::GetRenderer()->GetCamera()->SetState(CCamera::CAMERA_GAME);

	//SKIPコマンド
	//コントローラが接続されているかどうかでテクスチャ差し替え
	CManager::GetXInput()->GetConnect() ?
		CScene2D_UI::Create(D3DXVECTOR3(1100.0f, 230.0f, 0.0f), D3DXVECTOR3(300.0f, 80.0f, 0.0f), WhiteColor, CTexture::TEX_UI_TUTORIAL_X_SKIP, CScene::OBJTYPE_2DUI):
		CScene2D_UI::Create(D3DXVECTOR3(1100.0f, 230.0f, 0.0f), D3DXVECTOR3(300.0f, 80.0f, 0.0f), WhiteColor, CTexture::TEX_UI_TUTORIAL_KEY_SKIP, CScene::OBJTYPE_2DUI);

	//ステップ進行
	NextStep();

	return S_OK;
}

//------------------------------------------------------------------------------
//終了処理
//------------------------------------------------------------------------------
void CTutorial::Uninit()
{
	//終了処理
	CScene::ReleaseAll();
}

//------------------------------------------------------------------------------
//更新処理
//------------------------------------------------------------------------------
void CTutorial::Update()
{
	//敵の総数が亡くなって敵が出現可能状態のとき
	if (CEnemy::GetEnemyNum() <= 0 && m_bEnemyPop)
	{
		//敵出現カウンタ
		m_nEnemyPopTime--;

		//カウンタが0になった時
		if (m_nEnemyPopTime < 0)
		{
			//カウンタリセット
			m_nEnemyPopTime = ENEMY_POP_INTERVAL;

			//敵生成
			CEnemy::Create(D3DXVECTOR3(100.0f, 0.0f, 200.0f),CEnemy::TYPE_NORMAL);
			CEnemy::Create(D3DXVECTOR3(-100.0f, 0.0f, 200.0f), CEnemy::TYPE_NORMAL);
			CEnemy::Create(D3DXVECTOR3(0.0f, 0.0f, 300.0f), CEnemy::TYPE_STRONG);
			CEnemy::Create(D3DXVECTOR3(100.0f, 0.0f, 400.0f), CEnemy::TYPE_NORMAL);
			CEnemy::Create(D3DXVECTOR3(-100.0f, 0.0f, 400.0f), CEnemy::TYPE_NORMAL);
		}
	}

	//クリア状態のとき
	if (m_bClear)
	{
		//カウントダウン
		m_nCntStep--;

		//カウントが0になった時
		if (m_nCntStep <= 0)
		{
			//OK! を消す
			m_pOK->Release();
			m_pOK.reset();

			//次のステップへ
			NextStep();
		}
	}
	else
	{
		//チュートリアルのアクションチェック
		CheckTutorialAction();
	}

	//チュートリアルスキップボタン押された
	if (CHossoLibrary::CheckSkipTutorial() && m_step != TUTORIAL_END)
	{
		m_step = TUTORIAL_END;
		m_pTutorialStep->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_TUTORIAL_END));
		CManager::GetSound()->Play(CSound::LABEL_SE_DECISION);
	}


}

//------------------------------------------------------------------------------
//描画処理
//------------------------------------------------------------------------------
void CTutorial::Draw()
{
}

//------------------------------------------------------------------------------
//デバッグ用
//------------------------------------------------------------------------------
void CTutorial::ShowDebugInfo()
{
#ifdef _DEBUG
	CKeyboard *pKeyboard = CManager::GetKeyboard();

	//debug
	if (pKeyboard->GetTrigger(DIK_L))
	{
		NextStep();
	}
#endif //_DEBUG
}

//------------------------------------------------------------------------------
//チュートリアル
//------------------------------------------------------------------------------
void CTutorial::NextStep()
{
	//次のステップに移行
	switch (m_step)
	{
	case CTutorial::TUTORIAL_NONE:
		m_step = TUTORIAL_MOVE;

		//コントローラが接続されているかどうかでテクスチャ差し替え
		CManager::GetXInput()->GetConnect() ?
			m_pTutorialStep->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_TUTORIAL_X_MOVE)) :
			m_pTutorialStep->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_TUTORIAL_KEY_MOVE));

		break;
	case CTutorial::TUTORIAL_MOVE:
		m_step = TUTORIAL_DASH;

		//コントローラが接続されているかどうかでテクスチャ差し替え
		CManager::GetXInput()->GetConnect() ?
			m_pTutorialStep->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_TUTORIAL_X_DASH)) :
			m_pTutorialStep->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_TUTORIAL_KEY_DASH));

		break;

	case CTutorial::TUTORIAL_DASH:
		m_step = TUTORIAL_CAMERAMOVE;

		//コントローラが接続されているかどうかでテクスチャ差し替え
		CManager::GetXInput()->GetConnect() ?
			m_pTutorialStep->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_TUTORIAL_X_CAMERAMOVE)) :
			m_pTutorialStep->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_TUTORIAL_KEY_CAMERAMOVE));

		break;

	case CTutorial::TUTORIAL_CAMERAMOVE:
		m_step = TUTORIAL_CAMERARESET;

		//コントローラが接続されているかどうかでテクスチャ差し替え
		CManager::GetXInput()->GetConnect() ?
			m_pTutorialStep->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_TUTORIAL_X_CAMERARESET)) :
			m_pTutorialStep->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_TUTORIAL_KEY_CAMERARESET));

		break;

	case CTutorial::TUTORIAL_CAMERARESET:
		m_step = TUTORIAL_JUMP;

		//コントローラが接続されているかどうかでテクスチャ差し替え
		CManager::GetXInput()->GetConnect() ?
			m_pTutorialStep->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_TUTORIAL_X_JUMP)) :
			m_pTutorialStep->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_TUTORIAL_KEY_JUMP));

		break;

	case CTutorial::TUTORIAL_JUMP:
		m_step = TUTORIAL_ATTACK;

		//コンボパターン
		//コントローラが接続されているかどうかでテクスチャ差し替え
		CManager::GetXInput()->GetConnect() ?
			CScene2D_UI::Create(D3DXVECTOR3(170.0f, 80.0f, 0.0f), D3DXVECTOR3(300.0f, 120.0f, 0.0f), WhiteColor, CTexture::TEX_UI_GAME_X_COMBOPATTERN, CScene::OBJTYPE_2DUI) :
			CScene2D_UI::Create(D3DXVECTOR3(170.0f, 80.0f, 0.0f), D3DXVECTOR3(300.0f, 120.0f, 0.0f), WhiteColor, CTexture::TEX_UI_GAME_KEY_COMBOPATTERN, CScene::OBJTYPE_2DUI);

		//敵生成
		CEnemy::Create(D3DXVECTOR3(0.0f, 0.0f, 300.0f), CEnemy::TYPE_NORMAL);

		//コントローラが接続されているかどうかでテクスチャ差し替え
		CManager::GetXInput()->GetConnect() ?
			m_pTutorialStep->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_TUTORIAL_X_ATTACK)) :
			m_pTutorialStep->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_TUTORIAL_KEY_ATTACK));

		break;

	case CTutorial::TUTORIAL_ATTACK:
		m_step = TUTORIAL_START_CHAIN;

		//コントローラが接続されているかどうかでテクスチャ差し替え
		CManager::GetXInput()->GetConnect() ?
			m_pTutorialStep->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_TUTORIAL_X_STARTCHAIN)) :
			m_pTutorialStep->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_TUTORIAL_KEY_STARTCHAIN));

		break;

	case CTutorial::TUTORIAL_START_CHAIN:
		m_step = TUTORIAL_CHAINTHUNDER;

		//コントローラが接続されているかどうかでテクスチャ差し替え
		CManager::GetXInput()->GetConnect() ?
			m_pTutorialStep->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_TUTORIAL_X_CHAINTHUNDER)) :
			m_pTutorialStep->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_TUTORIAL_KEY_CHAINTHUNDER));

		//チュートリアル用のスタン状態の敵出現
		TutorialEnemyPop();

		break;

	case CTutorial::TUTORIAL_CHAINTHUNDER:
		m_pTutorialStep->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_TUTORIAL_FREE));
		m_step = TUTORIAL_FREE;
		m_bEnemyPop = true;

		break;

	case CTutorial::TUTORIAL_FREE:
		m_pTutorialStep->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_TUTORIAL_END));
		m_step = TUTORIAL_END;

		break;

	case CTutorial::TUTORIAL_END:

		break;
	case CTutorial::TUTORIAL_MAX:

		break;
	default:
		break;
	}

	//クリア状態をfalseに
	m_bClear = false;
}
//------------------------------------------------------------------------------
//チュートリアル用の敵出現
//------------------------------------------------------------------------------
void CTutorial::TutorialEnemyPop()
{
	//敵生成
	for (int nCntH = 0; nCntH < ENEMY_LINE.x; nCntH++)
	{
		for (int nCntV = 0; nCntV < ENEMY_LINE.y; nCntV++)
		{
			//敵を並べて生成
			CEnemy::Create(D3DXVECTOR3(
				-ENEMY_LINE.x * 0.5f * ENEMY_SPACE + nCntH * ENEMY_SPACE,
				0.0f,
				-ENEMY_LINE.y * 0.5f * ENEMY_SPACE + nCntV * ENEMY_SPACE), CEnemy::TYPE_TUTORIAL_STANING);
		}
	}

}
//------------------------------------------------------------------------------
//プレイヤーの情報取得
//------------------------------------------------------------------------------
CPlayer * CTutorial::GetPlayer()
{
	if (m_pPlayer)
	{
		return m_pPlayer.get();
	}
	return nullptr;
}
//------------------------------------------------------------------------------
//チュートリアルのアクションチェック
//------------------------------------------------------------------------------
void CTutorial::CheckTutorialAction()
{
	//それぞれのステップで条件
	switch (m_step)
	{
	case CTutorial::TUTORIAL_MOVE:
		//歩くモーションになった
		if (m_pPlayer->GetNowMotion() == CMotion::PLAYER_WALK)
		{
			ActionClear();
		}
		break;
	case CTutorial::TUTORIAL_DASH:
		//ダッシュモーションになった
		if (m_pPlayer->GetNowMotion() == CMotion::PLAYER_DASH)
		{
			ActionClear();
		}
		break;
		//カメラがある程度動いた
	case CTutorial::TUTORIAL_CAMERAMOVE:
		if (fabsf(CManager::GetRenderer()->GetCamera()->GetCameraRot().y) > 1.0f)
		{
			ActionClear();
		}
		break;
		//カメラリセットボタンが押された
	case CTutorial::TUTORIAL_CAMERARESET:
		if (CHossoLibrary::CheckCameraReset(CHossoLibrary::TRIGGER))
		{
			ActionClear();
		}
		break;
		//ジャンプモーションになった
	case CTutorial::TUTORIAL_JUMP:
		if (m_pPlayer->GetNowMotion() == CMotion::PLAYER_JUMP)
		{
			ActionClear();
		}
		break;
		//敵が全員青になった
	case CTutorial::TUTORIAL_ATTACK:
		if (CEnemy::GetEnemyNum() == CEnemy::GetStanEnemyNum())
		{
			ActionClear();
		}
		break;
		//敵がいなくなった
	case CTutorial::TUTORIAL_START_CHAIN:
		if (CEnemy::GetEnemyNum() <= 0)
		{
			ActionClear();
		}
		break;
		//敵がいなくなった
	case CTutorial::TUTORIAL_CHAINTHUNDER:
		if (CEnemy::GetEnemyNum() <= 0)
		{
			ActionClear();
		}
		break;
	case CTutorial::TUTORIAL_FREE:

		break;
	case CTutorial::TUTORIAL_END:
		//ゲームに遷移
		CManager::GetRenderer()->GetFade()->SetModeFade(CManager::MODE_GAME);
		break;
	}

}
//------------------------------------------------------------------------------
//アクションクリア
//------------------------------------------------------------------------------
void CTutorial::ActionClear()
{
	//クリア状態
	m_bClear = true;

	//次のアクションが出るまでのインターバル設定
	m_nCntStep = TUTORIAL_STEP_INTERVAL;

	//OK! を表示
	m_pOK = CScene2D::Create_Shared(D3DXVECTOR3(870.0f, 120.0f, 0.0f), D3DXVECTOR3(250.0f, 120.0f, 0.0f),CScene::OBJTYPE_2DUI);
	m_pOK->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_TUTORIAL_OK));

	//音再生
	CManager::GetSound()->Play(CSound::LABEL_SE_SLASH_STAN);

	//エフェクト
	CEffectAnimation2D::Create(D3DXVECTOR3(870.0f, 120.0f, 0.0f), D3DXVECTOR3(250.0f, 250.0f, 0.0f), CTexture::SEPARATE_TEX_EFFECT_HIT_STAN, 0.0f, 1, CScene::OBJTYPE_2DEFFECT);
}
