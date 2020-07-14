// =====================================================================================================================================================================
//
// 戦車砲台の処理 [tankturret.cpp]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#include "tankturret.h"			// インクルードファイル
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
CTankTurret::CTankTurret(OBJ_TYPE type) :CBullet(type)
{
	SetObjType(OBJTYPE_BULLET);
}

// =====================================================================================================================================================================
//
// デストラクタ
//
// =====================================================================================================================================================================
CTankTurret::~CTankTurret()
{
}

// =====================================================================================================================================================================
//
// 初期化処理
//
// =====================================================================================================================================================================
HRESULT CTankTurret::Init()
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
void CTankTurret::Uninit(void)
{
	// 終了
	CBullet::Uninit();
}

// =====================================================================================================================================================================
//
// 更新処理
//
// =====================================================================================================================================================================
void CTankTurret::Update(void)
{
	// 更新
	CBullet::Update();
}

// =====================================================================================================================================================================
//
// 描画処理
//
// =====================================================================================================================================================================
void CTankTurret::Draw(void)
{
	// 描画
	CBullet::Draw();
}

// =====================================================================================================================================================================
//
// 弾を消す処理
//
// =====================================================================================================================================================================
void CTankTurret::DeleteBullet()
{
	CBullet::DeleteBullet();
}

// =====================================================================================================================================================================
//
// 弾の反応
//
// =====================================================================================================================================================================
void CTankTurret::BulletReaction(D3DXVECTOR3 rot)
{
}

// =====================================================================================================================================================================
//
// デバッグ
//
// =====================================================================================================================================================================
void CTankTurret::DebugInfo()
{
}

// =====================================================================================================================================================================
//
// 戦車砲台の生成
//
// =====================================================================================================================================================================
CTankTurret * CTankTurret::Create(D3DXVECTOR3 rot)
{
	// 変数
	CTankTurret *pTankTurret;

	// メモリの確保
	pTankTurret = new CTankTurret(OBJTYPE_BULLET);

	// 戦車砲台のパラメーター取得
	BULLET_PARAM *pBulletParam = pTankTurret->GetBulletParam(CGun::GUNTYPE_TANKTURRET);

	// 初期化
	pTankTurret->Init();

	// 撃つ方向に合わせる
	pTankTurret->GetMove() = D3DXVECTOR3(-sinf(rot.x) * pBulletParam->fBulletSpeed,
										cosf(rot.x) * cosf(rot.y) * pBulletParam->fBulletSpeed,
										sinf(rot.y) * cosf(rot.x) * pBulletParam->fBulletSpeed);

	// モデルタイプの設定
	pTankTurret->SetType(BULLET_MODEL);

	// モデルカウントの設定
	pTankTurret->SetModelConut(MODEL_BULLET_SPHERE);

	return pTankTurret;
}