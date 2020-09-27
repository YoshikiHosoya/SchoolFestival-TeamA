// =====================================================================================================================================================================
//
// チュートリアルマネージャーの処理 [tutorialmanager.h]
// Author : fujiwara masato
//
// =====================================================================================================================================================================
#include "main.h"
#include "tutorialmanager.h"
#include "basemode.h"
#include "manager.h"
#include "tutorialui.h"
#include "renderer.h"
#include "fade.h"
#include "inputKeyboard.h"
#include "player.h"
#include "debugproc.h"
#include "Xinput.h"
#include "XInputPad.h"

// =====================================================================================================================================================================
// 静的メンバ変数の初期化
// =====================================================================================================================================================================

// =====================================================================================================================================================================
// マクロ定義
// =====================================================================================================================================================================
// パッドボタン
#define PAD_A (m_pPad->GetTrigger(m_pPad->JOYPADKEY_A, 1))			// ジャンプ
#define PAD_B (m_pPad->GetTrigger(m_pPad->JOYPADKEY_B, 1))			// 乗り物から降りる
#define PAD_X (m_pPad->GetTrigger(m_pPad->JOYPADKEY_X, 1))			// 弾
#define PAD_Y (m_pPad->GetTrigger(m_pPad->JOYPADKEY_Y, 1))			// グレネード
#define PAD_START (m_pPad->GetTrigger(m_pPad->JOYPADKEY_START, 1))	// チュートリアルをスキップする

// キーボード
#define KEY_A (m_pKey->GetKeyboardPress(DIK_A))					// 移動左
#define KEY_D (m_pKey->GetKeyboardPress(DIK_D))					// 移動右
#define KEY_O (m_pKey->GetKeyboardPress(DIK_O))					// グレネード
#define KEY_U (m_pKey->GetKeyboardPress(DIK_U))					// 弾
#define KEY_SPACE (m_pKey->GetKeyboardTrigger(DIK_SPACE))			// ジャンプ

#define WAITTIME (180)											// ステート間の待ち時間

// =====================================================================================================================================================================
//
// コンストラクタ
//
// =====================================================================================================================================================================
CTutorialManager::CTutorialManager()
{
	m_TutorialState		= TUTORIAL_STATE_NONE;
	m_OldState			= TUTORIAL_STATE_NONE;
	m_pTutorialUI		= nullptr;
	m_nWaitTime			= 0;
	m_bOneFlag			= false;
	m_bPushButton		= false;
	m_pKey				= nullptr;
	m_pPad				= nullptr;
}

// =====================================================================================================================================================================
//
// デストラクタ
//
// =====================================================================================================================================================================
CTutorialManager::~CTutorialManager()
{

}

// =====================================================================================================================================================================
//
// 初期化処理
//
// =====================================================================================================================================================================
HRESULT CTutorialManager::Init(void)
{
	// チュートリアルUIの生成
	m_pTutorialUI = CTutorialUI::Create();
	// カメラを固定する
	CRenderer *pRenderer = CManager::GetRenderer();
	pRenderer->GetCamera()->SetCameraStopMove(true);
	m_pKey = CManager::GetInputKeyboard();
	m_pPad = CManager::GetPad(TAG::PLAYER_1);
	return S_OK;
}

// =====================================================================================================================================================================
//
// 終了処理
//
// =====================================================================================================================================================================
void CTutorialManager::Uninit(void)
{
}

// =====================================================================================================================================================================
//
// 更新処理
//
// =====================================================================================================================================================================
void CTutorialManager::Update(void)
{
	// エンターを押したとき
	if (CHossoLibrary::PressStartButton() || PAD_START)
	{
		// ゲームモードへステート遷移
		CManager::GetRenderer()->GetFade()->SetFade(CFADE::FADETYPE::FADETYPE_MODE, CManager::MODE_GAME);
	}

	// デバッグ用
#ifdef _DEBUG
#endif // DEBUG

	// 各ステートごとの関数を管理する
	StateManager();
	// チュートリアルの順番管理
	TutorialState();

	// 最初の1回目は無条件に通す
	if (m_TutorialState == TUTORIAL_STATE_NONE)
	{
		// 現在のステートを保存
		m_OldState = m_TutorialState;
		// タイマー開始
		WaitTime();
	}

	// 1回目以降
	else
	{
		// 今のステートと1つ前のステートが別だった時
		if (m_TutorialState != static_cast<TUTORIAL_STATE>(m_OldState - 1))
		{
			// ボタンが押されているかチェック
			JudgPushButton();
			// プレイヤーがチュートリアル通りにボタンを押したら
			if (m_bPushButton)
			{
				// タイマー開始
				WaitTime();
			}
		}
	}
}

// =====================================================================================================================================================================
//
// 生成
//
// =====================================================================================================================================================================
CTutorialManager * CTutorialManager::Create()
{
	//メモリの確保
	CTutorialManager *pTutorialManager = new CTutorialManager();

	// 初期化
	pTutorialManager->Init();

	// ポインタを返す
	return pTutorialManager;
}

// =====================================================================================================================================================================
//
// Uiの出現順番
//
// =====================================================================================================================================================================
void CTutorialManager::TutorialState()
{
	// 順番
	switch (m_TutorialState)
	{
	case CTutorialManager::TUTORIAL_STATE_FIRST:
		break;
	case CTutorialManager::TUTORIAL_STATE_1:
		break;
	case CTutorialManager::TUTORIAL_STATE_2:
		break;
	case CTutorialManager::TUTORIAL_STATE_3:
		break;
	case CTutorialManager::TUTORIAL_STATE_4:
		break;
	case CTutorialManager::TUTORIAL_STATE_5:
		break;
	case CTutorialManager::TUTORIAL_STATE_6:
		break;
	case CTutorialManager::TUTORIAL_STATE_FINAL:
		break;
	}
}

// =====================================================================================================================================================================
//
// ステートを切り替える際の時間の設定
//
// =====================================================================================================================================================================
void CTutorialManager::WaitTime()
{
	// 時間の減少
	m_nWaitTime--;

	// 時間が0以下になった時
	if (m_nWaitTime <= 0)
	{
		// 次のステートに移行する
		NextState();
		//
		m_bPushButton = false;
		// 現在のステートを保存
		m_OldState = m_TutorialState;
	}
}

// =====================================================================================================================================================================
//
// ステートを切り替える際の時間の管理
//
// =====================================================================================================================================================================
void CTutorialManager::SetWaitTime(int Time)
{
	// 待ち時間を設定する
	m_nWaitTime = Time;
}

// =====================================================================================================================================================================
//
// ステートを切り替える際の時間の設定
//
// =====================================================================================================================================================================
void CTutorialManager::NextState()
{
	// 次のステートに移行する
	if (m_TutorialState != TUTORIAL_STATE_FINAL)
	{
		m_TutorialState = static_cast<TUTORIAL_STATE>(m_TutorialState + 1);
		m_bOneFlag = false;

		if (m_pTutorialUI)
		{
			m_pTutorialUI->SetDrawDisp(m_pTutorialUI->GetTutorialUiType());
		}
	}
	else
	{
		// ゲームモードへステート遷移
		CManager::GetRenderer()->GetFade()->SetFade(CFADE::FADETYPE::FADETYPE_MODE, CManager::MODE_GAME);
	}
}

// =====================================================================================================================================================================
//
// 各ステートごとの関数を管理する
//
// =====================================================================================================================================================================
void CTutorialManager::StateManager()
{
	// この処理がまだ通っていなかった時
	if (!m_bOneFlag)
	{
		// 一番最初のステートだった時
		if (m_TutorialState == TUTORIAL_STATE_NONE)
		{
			// 次のステートに移行するまでの時間の設定
			SetWaitTime(120);
		}
		// それ以外だった時
		else
		{
			// 次のステートに移行するまでの時間の設定
			SetWaitTime(WAITTIME);
		}

		// この処理を次に許可が出るまで通さない
		m_bOneFlag = true;
	}
}

// =====================================================================================================================================================================
//
// 指定したボタンを押されたかどうか
//
// =====================================================================================================================================================================
void CTutorialManager::JudgPushButton()
{
	// スティックの値を初期化
	D3DXVECTOR3 InputValue = ZeroVector3;
	// 値の正規化
	InputValue.x /= STICK_MAX_RANGE;
	InputValue.y /= STICK_MAX_RANGE;
	// 左スティックの入力値を取得
	m_pPad->GetStickLeft(&InputValue.x, &InputValue.y);
	// プレイヤーのポインタを取得
	CPlayer *pPlayer = CManager::GetBaseMode()->GetPlayer(TAG::PLAYER_1);

	// 各ステート時のボタンを押したかどうか
	switch (m_TutorialState)
	{
		// padX,Y,A,BまたはkeyDで開始
	case CTutorialManager::TUTORIAL_STATE_FIRST:
		m_bPushButton = true;
		break;
		// padLSTICKまたはkeyADで移動
	case CTutorialManager::TUTORIAL_STATE_1:
		if (InputValue.x < -1.0f || InputValue.x > 1.0f ||
			KEY_A ||
			KEY_D)
		{
			m_bPushButton = true;
		}
		break;
		// padXまたはkeySPACEでジャンプ
	case CTutorialManager::TUTORIAL_STATE_2:
		if (PAD_X ||
			KEY_SPACE)
		{
			m_bPushButton = true;
		}
		break;
		// padAまたはkeyPで弾発射
	case CTutorialManager::TUTORIAL_STATE_3:
		if (PAD_A ||
			KEY_U)
		{
			m_bPushButton = true;
		}
		break;
		// padYまたはkeyOでグレネード
	case CTutorialManager::TUTORIAL_STATE_4:
		if (PAD_Y ||
			KEY_O)
		{
			m_bPushButton = true;
		}
		break;
		// 戦車の近くでpadXまたはkeySPACEでジャンプし乗る
	case CTutorialManager::TUTORIAL_STATE_5:
		// nullチェック
		if (pPlayer != nullptr)
		{
			// 乗り物に乗っている時
			if (pPlayer->GetRideFlag())
			{
				m_bPushButton = true;
			}
		}
		break;
		// 戦車に乗っている時padBまたはkeySPACEでジャンプし降りる
	case CTutorialManager::TUTORIAL_STATE_6:
		// 戦車から降りる
		// nullチェック
		if (pPlayer != nullptr)
		{
			// 乗り物に乗っている時
			if (!pPlayer->GetRideFlag())
			{
				m_bPushButton = true;
			}
		}
		break;
	case CTutorialManager::TUTORIAL_STATE_FINAL:
			m_bPushButton = true;
		break;
	}
}
