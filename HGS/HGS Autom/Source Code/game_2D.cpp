//------------------------------------------------------------------------------
//
//ゲーム処理  [game.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "game_2D.h"
#include "manager.h"
#include "renderer.h"
#include "player_2D.h"
#include "fade.h"
#include "keyboard.h"
#include "camera.h"
#include "Way.h"
#include "ParticleManager.h"
//------------------------------------------------------------------------------
//静的メンバ変数の初期化
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//マクロ
//------------------------------------------------------------------------------
#define DEFAULT_CREATE_POS (1000.0f)
#define WAY_SIZE (400.0f)
#define BENDING_TIME (4)
//------------------------------------------------------------------------------
//コンストラクタ
//------------------------------------------------------------------------------
CGame_2D::CGame_2D()
{
	m_nSpeed = 10;
	m_direction = DIRECTION::UP;
	m_nCnt = 0;
	m_nScoreDistance = 0;
	SetScore(0);
	m_bBendingFlag = false;
	m_pWayList = {};
}
//------------------------------------------------------------------------------
//デストラクタ
//------------------------------------------------------------------------------
CGame_2D::~CGame_2D()
{

}

//------------------------------------------------------------------------------
//初期化処理
//------------------------------------------------------------------------------
HRESULT CGame_2D::Init(HWND hWnd)
{
	//カメラ座標設定
	CManager::GetRenderer()->GetCamera()->SetState(CCamera::CAMERA_DEBUG);

	CGame::SetPlayerPtr(CPlayer_2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 650.0f, 0.0f)));

	//パーティクルのマネージャ
	CParticleManager::Create();

	for (int nCnt = 0; nCnt < 8; nCnt++)
	{
		m_pWayList.emplace_back(CWay::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, nCnt * 400.0f - DEFAULT_CREATE_POS, 0.0f), CWay::UP));
	}

	return S_OK;
}

//------------------------------------------------------------------------------
//終了処理
//------------------------------------------------------------------------------
void CGame_2D::Uninit()
{
	//終了処理
	CScene::ReleaseAll();
}

//------------------------------------------------------------------------------
//更新処理
//------------------------------------------------------------------------------
void CGame_2D::Update()
{



	m_nScoreDistance += m_nSpeed;

	m_nBendingTime--;

	if (m_nBendingTime < 0)
	{
		m_direction = DIRECTION::UP;
	}

	//次の曲がり角までの差分
	float fNextBendingDistance = m_fNextBendingPoint - m_nScoreDistance;

	CDebugProc::Print(CDebugProc::PLACE_LEFT, "m_nScoreDistance >> %.2f\n", m_nScoreDistance);
	CDebugProc::Print(CDebugProc::PLACE_LEFT, "m_fNextBendingPoint >> %.2f\n", m_fNextBendingPoint);
	CDebugProc::Print(CDebugProc::PLACE_LEFT, "fNextBendingDistance >> %.2f\n", fNextBendingDistance);
	CDebugProc::Print(CDebugProc::PLACE_LEFT, "NextDirection >> %d\n", m_NextBendingDirection);

	if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN))
	{
		GameEnd();
	}

	if (CManager::GetKeyboard()->GetTrigger(DIK_L))
	{
		m_nSpeed += 5;
	}

	if (CManager::GetKeyboard()->GetTrigger(DIK_LEFT))
	{
		Bending();
		m_NextBendingDirection = DIRECTION::LEFT;

	}

	if (CManager::GetKeyboard()->GetTrigger(DIK_RIGHT))
	{
		Bending();
		m_NextBendingDirection = DIRECTION::RIGHT;

	}


	if (m_pWayList[m_pWayList.size() - 1]->GetPos().y >= -600.0f)
	{
		if (fNextBendingDistance <= 1200 && m_bBendingFlag)
		{
			switch (m_NextBendingDirection)
			{
			case DIRECTION::LEFT:
				m_pWayList.emplace_back(CWay::Create(m_pWayList[m_pWayList.size() - 1]->GetPos() + D3DXVECTOR3(0.0f, -WAY_SIZE, 0.0f), CWay::LEFT_01));
				m_pWayList.emplace_back(CWay::Create(m_pWayList[m_pWayList.size() - 1]->GetPos() + D3DXVECTOR3(-WAY_SIZE, 0.0f, 0.0f), CWay::LEFT_02));
				m_bBendingFlag = false;
				break;

			case DIRECTION::RIGHT:
				m_pWayList.emplace_back(CWay::Create(m_pWayList[m_pWayList.size() - 1]->GetPos() + D3DXVECTOR3(0.0f, -WAY_SIZE, 0.0f), CWay::RIGHT_01));
				m_pWayList.emplace_back(CWay::Create(m_pWayList[m_pWayList.size() - 1]->GetPos() + D3DXVECTOR3(WAY_SIZE, 0.0f, 0.0f), CWay::RIGHT_02));
				m_bBendingFlag = false;
				break;

			default:
				break;
			}
		}
		else
		{
			m_pWayList.emplace_back(CWay::Create(m_pWayList[m_pWayList.size() - 1]->GetPos() + D3DXVECTOR3(0.0f, -WAY_SIZE, 0.0f), CWay::UP));
		}
	}
	for (size_t nCnt = 0; nCnt < m_pWayList.size(); nCnt++)
	{
		if (m_pWayList[nCnt]->GetPos().y >= 1200.0f)
		{
			m_pWayList[nCnt]->Release();
			m_pWayList.erase(m_pWayList.begin() + nCnt);
		}
	}
}

//------------------------------------------------------------------------------
//描画処理
//------------------------------------------------------------------------------
void CGame_2D::Draw()
{

}
//------------------------------------------------------------------------------
//デバッグ情報表記
//------------------------------------------------------------------------------
void CGame_2D::ShowDebugInfo()
{
#ifdef _DEBUG
	//キーボードのポインタ
	CKeyboard *pKeyboard = CManager::GetKeyboard();

	//[0]キーを押した時
	if (pKeyboard->GetTrigger(DIK_0))
	{
		//ステート変更
		SetGamestate(CGame_2D::STATE_GAMECLEAR);
		return;
	}

#endif //_DEBUG
}

//------------------------------------------------------------------------------
//プレイヤーの曲がる処理
//------------------------------------------------------------------------------
void CGame_2D::PlayerBending(DIRECTION Direction)
{
	m_direction = Direction;
	m_nBendingTime = BENDING_TIME;;

	Bending();
}

//------------------------------------------------------------------------------
//ゲーム終了
//------------------------------------------------------------------------------
void CGame_2D::GameEnd()
{
	CGame::SetScore(m_nScoreDistance);
	CManager::GetRenderer()->GetFade()->SetModeFade(CManager::MODE_RANKING);

}

//------------------------------------------------------------------------------
//曲がる処理
//------------------------------------------------------------------------------
void CGame_2D::Bending()
{
	m_NextBendingDirection = (DIRECTION)(rand() % 2);
	m_fNextBendingPoint = m_nScoreDistance + 2500.0f;

	m_bBendingFlag = true;

}
