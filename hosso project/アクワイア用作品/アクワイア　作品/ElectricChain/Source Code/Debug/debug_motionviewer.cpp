//------------------------------------------------------------------------------
//
//デバッグ　モーションビューワ用の処理  [debug_motionviewer.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "debug_motionviewer.h"
#include "debug_character.h"
#include "../manager.h"
#include "../renderer.h"
#include "../keyboard.h"
#include "../camera.h"
#include "../orbit.h"
#include "../fade.h"
#include "../Map.h"
//------------------------------------------------------------------------------
//静的メンバ変数の初期化
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//マクロ
//------------------------------------------------------------------------------
#define DEFAULT_PLAYER_POS (ZeroVector3)
#define DEFAULT_SCORE_POS (D3DXVECTOR3(1150.0f, 50.0f, 0.0f))

//------------------------------------------------------------------------------
//コンストラクタ
//------------------------------------------------------------------------------
CDebug_MotionViewer::CDebug_MotionViewer()
{
	m_nCntState = 0;
	m_State = CDebug_MotionViewer::STATE_NORMAL;
	SetGamestate(CDebug_MotionViewer::STATE_NORMAL);
	m_nModelType = 0;
	m_nParamText = 0;
}
//------------------------------------------------------------------------------
//デストラクタ
//------------------------------------------------------------------------------
CDebug_MotionViewer::~CDebug_MotionViewer()
{

}

//------------------------------------------------------------------------------
//初期化処理
//------------------------------------------------------------------------------
HRESULT CDebug_MotionViewer::Init(HWND hWnd)
{
	//初期化
	m_State = STATE_NORMAL;
	m_nCntState = 0;

	//カメラ座標設定
	CManager::GetRenderer()->GetCamera()->SetCameraPos(DEFAULT_PLAYER_POS, DEFAULT_PLAYER_POS + D3DXVECTOR3(0.0f, 300.0f, -500.0f));
	CManager::GetRenderer()->GetCamera()->SetState(CCamera::CAMERA_DEBUG);
	//マップ
	CMap::Create();

	return S_OK;
}

//------------------------------------------------------------------------------
//終了処理
//------------------------------------------------------------------------------
void CDebug_MotionViewer::Uninit()
{

	if (m_pCharacter)
	{
		m_pCharacter->Release();
		m_pCharacter = nullptr;
	}

	//終了処理
	CScene::ReleaseAll();
}

//------------------------------------------------------------------------------
//更新処理
//------------------------------------------------------------------------------
void CDebug_MotionViewer::Update()
{
	//debug処理
	DebugCommand();

	// キーボードのポインタ
	CKeyboard *pKeyboard = CManager::GetKeyboard();

	//ゲームの状態で処理を変える
	switch (m_State)
	{
		//通常時
	case CDebug_MotionViewer::STATE_NORMAL:


		break;

	}
}

//------------------------------------------------------------------------------
//描画処理
//------------------------------------------------------------------------------
void CDebug_MotionViewer::Draw()
{

}
//------------------------------------------------------------------------------
//デバッグ情報表記
//------------------------------------------------------------------------------
void CDebug_MotionViewer::ShowDebugInfo()
{
#ifdef _DEBUG
	CDebugProc::Print(CDebugProc::PLACE_LEFT, "------------ MotionViewer ----------------\n");
	CDebugProc::Print(CDebugProc::PLACE_LEFT, "ImGuiウィンドウでモデル選択\n");
	CDebugProc::Print(CDebugProc::PLACE_LEFT, "[F5] : MotionViewer起動\n");

	//モデルの種類
	if (ImGui::InputInt("ModelType", &m_nModelType))
	{
		CHossoLibrary::RangeLimit_Equal_Int(m_nModelType, 0, MODEL_MAX - 1);
	}
	//パラメータ
	if (ImGui::InputInt("ParamText", &m_nParamText))
	{
		CHossoLibrary::RangeLimit_Equal_Int(m_nParamText, 0, CCharacter::PARAM_MAX - 1);
	}

#endif
}

//------------------------------------------------------------------------------
//ゲームステートセット
//------------------------------------------------------------------------------
void CDebug_MotionViewer::SetGamestate(STATE gamestate)
{
	//ステートが進んでいる場合
	if (m_State != CDebug_MotionViewer::STATE_NONE)
	{
		//ステート変更
		m_State = gamestate;

		switch (gamestate)
		{
		case STATE_NORMAL:
			if (m_pCharacter)
			{
				m_pCharacter->Release();
				m_pCharacter = nullptr;
			}
			CScene::SetStop(false);
			break;

		case CDebug_MotionViewer::STATE_DEBUG:
			CScene::SetStop(true);

			m_pCharacter = CDebug_Character::Create((MODEL_TYPE)m_nModelType,(CCharacter::PARAM_TYPE)m_nParamText);

			break;
		}
	}
}
//------------------------------------------------------------------------------
//ゲームステート取得
//------------------------------------------------------------------------------
CDebug_MotionViewer::STATE CDebug_MotionViewer::GetGamestate()
{
	return m_State;
}

//------------------------------------------------------------------------------
//デバッグ処理
//------------------------------------------------------------------------------
void CDebug_MotionViewer::DebugCommand()
{
#ifdef _DEBUG

	CKeyboard *pKeyboard = CManager::GetKeyboard();

	//[ENTER]キーを押した時
	if (pKeyboard->GetPress(DIK_9))
	{
		//ステート変更
		CManager::GetRenderer()->GetFade()->SetModeFade(CManager::MODE_GAME);
		return;

	}

	//Debug
	if (pKeyboard->GetTrigger(DIK_F5))
	{
		if (m_State == STATE_DEBUG)
		{
			CDebug_MotionViewer::SetGamestate(STATE_NORMAL);
		}
		else
		{
			CDebug_MotionViewer::SetGamestate(STATE_DEBUG);
		}
	}
#endif // _DEBUG

}