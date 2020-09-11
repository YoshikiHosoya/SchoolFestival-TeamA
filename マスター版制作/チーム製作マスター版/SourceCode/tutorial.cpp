// =====================================================================================================================================================================
//
// チュートリアルの処理 [tutorial.h]
// Author : fujiwara masato
//
// =====================================================================================================================================================================
#include "tutorial.h"
#include "manager.h"
#include "renderer.h"
#include "UIManager.h"
#include "tutorialUI.h"
#include "tutorialmanager.h"
#include "player.h"
#include "map.h"
#include "ParticleManager.h"
#include "title.h"

// =====================================================================================================================================================================
// マクロ定義
// =====================================================================================================================================================================
#define _CRT_SECURE_NO_WARNINGS // 警告除去

// =====================================================================================================================================================================
// 静的メンバ変数の初期化
// =====================================================================================================================================================================
CMap		*CTutorial::m_pMap = nullptr;
CPlayer		*CTutorial::m_pPlayer[MAX_CONTROLLER] = {};

//==========================================================
// コンストラクタ
//==========================================================
CTutorial::CTutorial()
{
	m_pTutorialManager = nullptr;
}

//==========================================================
// デストラクタ
//==========================================================
CTutorial::~CTutorial()
{
	for (int nCnt = 0; nCnt < MAX_CONTROLLER; nCnt++)
	{
		if (m_pPlayer[nCnt])
		{
			m_pPlayer[nCnt] = nullptr;
		}
	}
}

//==========================================================
// 初期化
//==========================================================
HRESULT CTutorial::Init(void)
{
	m_pMap = CMap::MapCreate();				// マップの生成
	m_pMap->MapLoad(CMap::MAP_TUTORIAL);	// マップのロード

	// プレイヤー1の生成
	m_pPlayer[(int)TAG::PLAYER_1] = CPlayer::Create(TAG::PLAYER_1);

	if (CPlayer::GetTwoPPlayFlag() && !m_pPlayer[(int)TAG::PLAYER_2])
	{
		// プレイヤー2の配置
		m_pPlayer[(int)TAG::PLAYER_2] = CPlayer::Create(TAG::PLAYER_2);
		m_pPlayer[(int)TAG::PLAYER_2]->SetPosition(m_pPlayer[(int)TAG::PLAYER_2]->GetPosition() + D3DXVECTOR3(100.0f, 0.0f, 0.0f));
		m_pPlayer[(int)TAG::PLAYER_2]->ChangeColor(true, D3DXCOLOR(0.5f, -0.5f, 1.0f, 0.0f));
	}

	// UI生成
	CUIManager::Create();

	//パーティクル生成
	CParticleManager::Create();

	// チュートリアルマネージャーの生成
	m_pTutorialManager = CTutorialManager::Create();

	return S_OK;
}

//==========================================================
// 終了
//==========================================================
void CTutorial::Uninit(void)
{
	if (m_pTutorialManager != nullptr)
	{
		// ランキングマネジャーの破棄
		delete m_pTutorialManager;
		m_pTutorialManager = nullptr;
	}
	if (m_pMap)
	{
		delete m_pMap;
		m_pMap = nullptr;
	}
}

//==========================================================
// 更新
//==========================================================
void CTutorial::Update(void)
{
	// 死亡判定が出ているかの確認
	m_pMap->UpdateDieFlag();
	m_pTutorialManager->Update();
}

//==========================================================
// 描画処理
//==========================================================
void CTutorial::Draw(void)
{
}

//==========================================================
// デバッグ情報表記
//==========================================================
void CTutorial::ShowDebugInfo(void)
{
}