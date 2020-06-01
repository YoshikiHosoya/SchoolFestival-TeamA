// ------------------------------------------
//
// タイトル処理 [title.cpp]
// Author : Fujiwara Masato
//
// ------------------------------------------
#include "title.h"
/* 描画 */
#include "tlybg.h"
#include "title_ui.h"
#include "fade.h"
#include "floor.h"
#include "player.h"
#include "titleobject.h"
#include "lighteffect.h"
#include "item.h"
#include "gate.h"
#include "explosion.h"
#include "titleEnemy.h"
#include "telop.h"
#include "TelopComment.h"
#include "bulletinboard.h"
#include "2DAnimationUI.h"
#include "key.h"
#include "map.h"
#include "camera.h"
#include "pause.h"
#include "manual.h"
// ------------------------------------------
//
// マクロ定義
//
// ------------------------------------------
// ------------------------------------------
//
// 静的変数宣言
//
// ------------------------------------------
CTitle_ui * CTitle::m_pTitle_ui = NULL;
CTitleEnemy * CTitle::m_pTitleEnemy = NULL;
CLightEffect * CTitle::m_pLightEffect = NULL;
CTelop * CTitle::m_pTelop = NULL;
bool CTitle::m_bFlag = false;
bool CTitle::m_bStartFlag = false;
bool CTitle::m_bTelopFlag = false;
// ------------------------------------------
// コンストラクタ
// ------------------------------------------
CTitle::CTitle()
{
	m_Mode = TITLEMODE_TITLE;
	m_CreateCnt = 0;
	m_Enterflag = true;
	m_PhaseCount = 0;
	m_Phaseflag = false;
}

// ------------------------------------------
// デストラクタ
// ------------------------------------------
CTitle::~CTitle()
{
}

// ------------------------------------------
// 初期化
// ------------------------------------------
void CTitle::Init(void)
{
	//使うオブジェクトの生成
	CreateTitleObj();

	CPause::Create();
	CManual::Create();
}

// ------------------------------------------
// 終了
// ------------------------------------------
void CTitle::Uninit(void)
{
	m_pTitle_ui = NULL;
	m_pTitleEnemy = NULL;
	m_pLightEffect = NULL;
	m_pTelop = NULL;
	m_bFlag = false;
	m_bStartFlag = false;
	m_bTelopFlag = false;
	CScene::ReleaseAll();
}

// ------------------------------------------
// 更新
// ------------------------------------------
void CTitle::Update(void)
{
	// キーボードでENTERを押した瞬間
	if (CManager::GetKeyboard()->GetKeyboardTrigger(DIK_RETURN))
	{
		//モードの設定
		SetMode();
		// ENTERを押した際のフラグをtrueにする
		m_Enterflag = true;
	}

	if (CManager::GetKeyboard()->GetKeyboardTrigger(DIK_SPACE))
	{
		CManager::GetFade()->SetFade(CManager::MODE_GAME);
	}

	if (m_Mode == TITLEMODE_FREE && CManager::GetKeyboard()->GetKeyboardTrigger(DIK_P))
	{
		if (CPause::GetPause() == false)
		{
			CPause::SetPause(true);
		}
		else
		{
			CPause::SetPause(false);
		}
	}

	if (CManager::GetJoy()->GetTrigger(0, CJoypad::KEY_A) || CManager::GetJoy()->GetTrigger(0, CJoypad::KEY_B))
	{
		//モードの設定
		SetMode();
		// ENTERを押した際のフラグをtrueにする
		m_Enterflag = true;
	}

	//モードごとの処理
	Mode();
}

// ------------------------------------------
// 描画
// ------------------------------------------
void CTitle::Draw(void)
{
}

// ------------------------------------------
// タイトルで使うオブジェクトの生成
// ------------------------------------------
void CTitle::CreateTitleObj(void)
{
	// 背景
	CTlyBg::Create(CManager::MODE_TITLE);
	// UI
	m_pTitle_ui = CTitle_ui::Create();

	//床
	CFloor::Create(
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(500.0f, 0.0f, 400.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		10, 10);

	// タイトル用のオブジェクト
	CTitleObject::LoadCreate();

	// プレイヤー
	CPlayer *pPlayer = CPlayer::Create();
	CManager::GetRenderer()->GetCamera()->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// タイトル用の敵
	m_pTitleEnemy = CTitleEnemy::Create();

	// ライトエフェクト
	CLightEffect::Create(D3DXVECTOR3(-20.000, 100.000, -1700.000),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(500.000, 500.000, 0.000),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f),
		CLightEffect::TYPE_P_LIGHT,
		false);

	// 鍵
	//CKey::Create();
}

// ------------------------------------------
// タイトルのモード設定
// ------------------------------------------
void CTitle::SetMode(void)
{
	// 画面遷移の状態が遷移していない状態だったら
	if (CManager::GetFade()->GetFade() == CFade::FADE_NONE)
	{
		// タイトルの初期画面で選んだモードがNEWGAMEだったら
		if (m_pTitle_ui->GetSelect() == CTitle_ui::TITLESELECT_NEWGAME)
		{
			//タイトルの状態からチュートリアルモードへ
			if (m_Mode == TITLEMODE_TITLE)
			{
				// ライトエフェクトを削除
				CLightEffect::ReleaseLight(CLightEffect::TYPE_P_LIGHT);
				// タイトルのモードをチュートリアルに移行
				m_Mode = TITLEMODE_TUTORIAL;
			}
		}

		// チュートリアル中だったら
		if (m_Mode == TITLEMODE_TUTORIAL)
		{
			// チュートリアルが終わったら
			if (CTelopComment::GetEndPhaseFlag() == true)
			{
				// ライトエフェクトを削除
				CLightEffect::ReleaseLight(CLightEffect::TYPE_S_LIGHT);
				// タイトル用の敵を削除
				m_pTitleEnemy->Release();
				// 爆発を生成
				CExplosion::Create(D3DXVECTOR3(0.000f, 250.000f, -1700.000f), D3DXVECTOR3(300.0f, 300.0f, 0.0f), CExplosion::TYPE_EXPLOSION);
				// タイトルのモードを操作可能状態に移行
				m_Mode = TITLEMODE_FREE;
			}
		}
	}
}

// ------------------------------------------
// タイトルのモードごとの処理
// ------------------------------------------
void CTitle::Mode(void)
{
	switch (m_Mode)
	{
	case TITLEMODE_TITLE:
		break;

	case TITLEMODE_TUTORIAL:
		// タイトルuiが消えたら通る
		if (CTitle_ui::GetFlag() == true)
		{
			// まだ生成されていなかったら
			if (m_bFlag == false)
			{
				//生成までの時間をカウント
				//m_CreateCnt++;
				//if (m_CreateCnt >= ONEMIN / 2)
				//{
					//ライトエフェクトを一度だけ生成
					CLightEffect::Create(D3DXVECTOR3(-20.000, 400.000, -1700.000),
						D3DXVECTOR3(0.0f, 0.0f, 0.0f),
						D3DXVECTOR3(200.000, 500.000, 0.000),
						D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f),
						CLightEffect::TYPE_S_LIGHT,
						false);

					// 生成までの時間を初期化
					m_CreateCnt = 0;
					// 出現したのでフラグをtrueにする
					m_bFlag = true;
				//}
			}

			// 出現していなかったら
			else if (m_bTelopFlag == false)
			{
				//生成までの時間をカウント
				m_CreateCnt++;

				// 生成するカウント数になったら
				if (m_CreateCnt >= ONEMIN * 0.5f)
				{
					//テロップを一度だけ生成
					m_pTelop = CTelop::Create();
					//生成までの時間をリセット
					m_CreateCnt = 0;
					// 出現したのでフラグをtrueにする
					m_bTelopFlag = true;
				}
			}

			// 出現したら
			else if (m_bTelopFlag == true)
			{
				// 徐々に不透明度を上げる
				m_pTelop->Transparency(CTelop::STATE_EMERGENCE);
			}
			m_pTitleEnemy->SetMotion();
		}

		break;

	case TITLEMODE_FREE:
		if (m_bStartFlag == false)
		{
			// 生成までの時間をカウント
			m_CreateCnt++;
			// 2秒経ったら
			if (m_CreateCnt >= ONEMIN * 2)
			{
				// ゲームモードに移行するためのゲートを作成
				CGate::LoadCreate();
				// 説明用の掲示板作成
				//CBulletinBoard::LoadCreate();
				// 鍵
				//CKey::Create();
				// 2DAnimation
				//C2DAnimation::Create(D3DXVECTOR3(1200.0f, 80, 0.0f), D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.2f, 0.25f), C2DAnimation::TYPE_KEY);
				// 生成までの時間を初期化
				m_CreateCnt = 0;
				// ゲートが生成されたのでフラグをtrueにする
				m_bStartFlag = true;
			}
		}

		// ゲートが出現してテロップが存在していたら
		else if (m_pTelop != NULL)
		{
			// テロップを削除
			m_pTelop->Transparency(CTelop::STATE_DISAPPEARANCE);
		}

		break;

	default:
		break;
	}
}

// ------------------------------------------
// タイトルのモードの取得
// ------------------------------------------
CTitle::TITLEMODE CTitle::GetMode(void)
{
	return m_Mode;
}

// ------------------------------------------
// フラグを元に戻す
// ------------------------------------------
void CTitle::SetEnterflag()
{
	m_Enterflag = false;
}

// ------------------------------------------
// フラグの取得
// ------------------------------------------
bool CTitle::GetEnterflag()
{
	return m_Enterflag;
}
