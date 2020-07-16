// =====================================================================================================================================================================
//
// 戦闘機の銃の処理 [planegun.cpp]
// Author : fujiwara masato
//
// =====================================================================================================================================================================
#include "planegun.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "debugproc.h"
#include "texture.h"

// =====================================================================================================================================================================
// 静的メンバ変数の初期化
// =====================================================================================================================================================================

// =====================================================================================================================================================================
// マクロ定義
// =====================================================================================================================================================================
// =====================================================================================================================================================================
//
// コンストラクタ
//
// =====================================================================================================================================================================
CPlaneGun::CPlaneGun(OBJ_TYPE type) :CBullet(type)
{
	SetObjType(OBJTYPE_BULLET);
}

// =====================================================================================================================================================================
//
// デストラクタ
//
// =====================================================================================================================================================================
CPlaneGun::~CPlaneGun()
{
}

// =====================================================================================================================================================================
//
// 初期化処理
//
// =====================================================================================================================================================================
HRESULT CPlaneGun::Init()
{
	// 初期化
	CBullet::Init();

	return S_OK;
}

// =====================================================================================================================================================================
//
// 終了処理
//
// =====================================================================================================================================================================
void CPlaneGun::Uninit(void)
{
	// 終了
	CBullet::Uninit();
}

// =====================================================================================================================================================================
//
// 更新処理
//
// =====================================================================================================================================================================
void CPlaneGun::Update(void)
{
	// 更新
	CBullet::Update();
}

// =====================================================================================================================================================================
//
// 描画処理
//
// =====================================================================================================================================================================
void CPlaneGun::Draw(void)
{
	// 描画
	CBullet::Draw();
}

// =====================================================================================================================================================================
//
// 弾を消す処理
//
// =====================================================================================================================================================================
void CPlaneGun::DeleteBullet()
{
	CBullet::DeleteBullet();
}

// =====================================================================================================================================================================
//
// 弾の反応
//
// =====================================================================================================================================================================
void CPlaneGun::BulletReaction(D3DXVECTOR3 rot)
{
}

// =====================================================================================================================================================================
//
// デバッグ
//
// =====================================================================================================================================================================
void CPlaneGun::DebugInfo()
{
}

// =====================================================================================================================================================================
//
// 戦車の銃の生成
//
// =====================================================================================================================================================================
CPlaneGun * CPlaneGun::Create(D3DXVECTOR3 rot)
{
	// 変数
	CPlaneGun *pPlaneGun;

	// メモリの確保
	pPlaneGun = new CPlaneGun(OBJTYPE_BULLET);

	// 戦車の銃のパラメーター取得
	BULLET_PARAM *pBulletParam = pPlaneGun->GetBulletParam(CGun::GUNTYPE_PLANEGUN);

	// 初期化
	pPlaneGun->Init();

	// 撃つ方向に合わせる
	pPlaneGun->GetMove() = D3DXVECTOR3(-sinf(rot.x) * pBulletParam->fBulletSpeed,
		cosf(rot.x) * cosf(rot.y) * pBulletParam->fBulletSpeed,
		sinf(rot.y) * cosf(rot.x) * pBulletParam->fBulletSpeed);

	// モデルタイプの設定
	pPlaneGun->SetType(BULLET_MODEL);

	// モデルカウントの設定
	pPlaneGun->SetModelConut(MODEL_BULLET_SPHERE);

	return pPlaneGun;
}