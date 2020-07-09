#include "result.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "inputKeyboard.h"
#include "fade.h"
#include "map.h"
#include "pause.h"
#include "ParticleManager.h"
#include "TexAnimation3D_Collision.h"
#include "item.h"
#include "UIManager.h"

#define _CRT_SECURE_NO_WARNINGS // 警告除去
int			CResult::m_Counter = 0;
CPlayer		*CResult::m_pPlayer = NULL;
CMap		*CResult::m_pMap = NULL;

//==========================================================
// コンストラクタ
//==========================================================
CResult::CResult()
{
}
//==========================================================
// デストラクタ
//==========================================================
CResult::~CResult()
{
}
//==========================================================
// 初期化
//==========================================================
HRESULT CResult::Init(void)
{

	m_pMap = CMap::MapCreate(CMap::MAP_1);	// マップの生成
	m_pPause->CreatePause();
	m_pPlayer = CPlayer::Create();
	m_pPlayer->SetLife(500);
	m_pPlayer->SetPosition(D3DXVECTOR3(50.0f, 100.0f, 0.0f));

	//パーティクル生成
	CParticleManager::Create();
	// UI生成
	CUIManager::Create();

	return S_OK;

}
//==========================================================
// 終了
//==========================================================
void CResult::Uninit(void)
{
}
//==========================================================
// 更新
//==========================================================
void CResult::Update(void)
{
	m_pMap->UpdateDieFlag();

	if (m_pPlayer != nullptr && m_pPlayer->GetLife() <= 0)
	{
		m_pPlayer->Rerease();
		m_pPlayer = nullptr;
	}
	//キーボード情報取得
	CKeyboard *key = CManager::GetInputKeyboard();;
	if (key->GetKeyboardTrigger(DIK_RETURN))
	{
		CManager::GetRenderer()->GetFade()->SetFade(CManager::MODE_TITLE);
	}
}
//==========================================================
// プレイヤー取得
//==========================================================
CPlayer * CResult::GetPlayer(void)
{
	return m_pPlayer;
}
//==========================================================
// マップ取得
//==========================================================
CMap * CResult::GetMap(void)
{
	if (m_pMap)
	{
		return m_pMap;
	}
	return nullptr;
}

//==========================================================
// 体力の取得
//==========================================================
void CResult::Draw(void)
{
}
//==========================================================
// デバッグ情報表記
//==========================================================
void CResult::ShowDebugInfo(void)
{
	//キーボード情報取得
	CKeyboard *key = CManager::GetInputKeyboard();;

	// マップの更新
	m_pMap->MapUpdate();
}