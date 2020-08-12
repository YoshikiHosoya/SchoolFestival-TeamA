// ===================================================================
//
// shieldの処理 [shield.cpp]
// Author : のりさん
//
// ===================================================================
#include "shield.h"
#include "bullet.h"
#include "collision.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "debugproc.h"
#include "collision.h"
#include "Player.h"
#include "Enemy.h"
#include "map.h"
#include "Obstacle.h"
#include "particle.h"
// ===================================================================
// 静的メンバ変数の初期化
// ===================================================================

// ===================================================================
// マクロ定義
// ===================================================================
#define SHIELD_LIFE				(20)			// shieldの体力
#define SHIELD_SIZE				(D3DXVECTOR3(100.0f,100.0f,0.0f))
// ===================================================================
// コンストラクタ
// ===================================================================
CShield::CShield(OBJ_TYPE type) :CObstacle(type)
{
}

// ===================================================================
// デストラクタ
// ===================================================================
CShield::~CShield()
{
}

// ===================================================================
// 初期化処理
// ===================================================================
HRESULT CShield::Init()
{
	CModel::Init();
	// 変数初期化
	m_nLife = SHIELD_LIFE;				// 体力
	// 初期化
	SetPosition(D3DXVECTOR3(200,100,0));
	// 当たり判定生成
	GetCollision()->SetPos(&GetPosition());
	GetCollision()->SetSize2D(SHIELD_SIZE);
//	GetCollision()->SetMove(&GetMove());
	GetCollision()->DeCollisionCreate(CCollision::COLLISIONTYPE_NORMAL);

	return S_OK;
}

// ===================================================================
// 終了処理
// ===================================================================
void CShield::Uninit(void)
{
	CModel::Uninit();
}

// ===================================================================
// 更新処理
// ===================================================================
void CShield::Update(void)
{
	// 更新
	CModel::Update();
}
// ===================================================================
// 描画処理
// ===================================================================
void CShield::Draw(void)
{
	CModel::Draw();
}
//====================================================================
//モデルのクリエイト
//====================================================================
CShield *CShield::Create(D3DXMATRIX *mtx)
{
	CShield*pShield;
	pShield = new CShield(OBJTYPE_SHIELD);
	pShield->Init();
	// マトリックス代入
	pShield->m_HasHandMtx = mtx;
	// モデルタイプの設定
	pShield->SetType(WEPON_MODEL);
	// モデルカウントの設定
	pShield->SetModelConut(MODEL_WEPON_SHIELD);

	return pShield;
}