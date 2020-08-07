// =====================================================================================================================================================================
//
// グレネードの処理 [grenade.cpp]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#include "grenade.h"			// インクルードファイル
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "debugproc.h"
#include "texture.h"
#include "Player.h"
#include "TexAnimation3D_Collision.h"
#include "particle.h"
// =====================================================================================================================================================================
// 静的メンバ変数の初期化
// =====================================================================================================================================================================

// =====================================================================================================================================================================
// マクロ定義
// =====================================================================================================================================================================
#define GRENADE_GRAVITY				(0.8f)								// グレネードの重力
#define GRENADE_MOVE				(D3DXVECTOR3(10.0f, 15.0f, 0.0f))	// グレネードの移動量
#define ROT_DIVISION_Z				(7)									// 回転の分割数	( 縦 )

// =====================================================================================================================================================================
//
// コンストラクタ
//
// =====================================================================================================================================================================
CGrenade::CGrenade(OBJ_TYPE type) :CBullet(type)
{
	SetObjType(OBJTYPE_BULLET);
}

// =====================================================================================================================================================================
//
// デストラクタ
//
// =====================================================================================================================================================================
CGrenade::~CGrenade()
{
}

// =====================================================================================================================================================================
//
// 初期化処理
//
// =====================================================================================================================================================================
HRESULT CGrenade::Init()
{
	m_move		= GRENADE_MOVE;							// 移動値
	m_rot		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 回転

	// 初期化
	CBullet::Init();

	return S_OK;
}

// =====================================================================================================================================================================
//
// 終了処理
//
// =====================================================================================================================================================================
void CGrenade::Uninit(void)
{
	// 終了
	CBullet::Uninit();
}

// =====================================================================================================================================================================
//
// 更新処理
//
// =====================================================================================================================================================================
void CGrenade::Update(void)
{
	// 重力
	GetMove().y -= GRENADE_GRAVITY;

	// 縦回転
	m_rot.z += (D3DX_PI / ROT_DIVISION_Z);

	// 回転の設定
	SetRot(m_rot);

	// 更新
	CBullet::Update();
}

// =====================================================================================================================================================================
//
// 描画処理
//
// =====================================================================================================================================================================
void CGrenade::Draw(void)
{
	// 描画
	CBullet::Draw();
}

// =====================================================================================================================================================================
//
// 弾を消す処理
//
// =====================================================================================================================================================================
void CGrenade::DeleteBullet()
{
	CParticle::CreateFromText(GetPosition(), ZeroVector3, CParticleParam::EFFECT_EXPLOSION, GetTag(), GetBulletParam(CGun::GUNTYPE_ROCKETLAUNCHER)->nPower);

	CBullet::DeleteBullet();
}

// =====================================================================================================================================================================
//
// グレネードの生成
//
// =====================================================================================================================================================================
CGrenade * CGrenade::Create(D3DXVECTOR3 rot)
{
	// 変数
	CGrenade *pGrenade;

	// メモリの確保
	pGrenade = new CGrenade(OBJTYPE_BULLET);

	// グレネードのパラメーター取得
	BULLET_PARAM *pBulletParam = pGrenade->GetBulletParam(CGun::GUNTYPE_GRENADE);

	// 初期化
	pGrenade->Init();

	// 放つ方向に合わせる
	pGrenade->GetMove() = D3DXVECTOR3(-sinf(rot.z)  * pGrenade->m_move.x, pGrenade->m_move.y, 0.0f);

	// モデルタイプの設定
	pGrenade->SetType(BULLET_MODEL);

	// モデルカウントの設定
	pGrenade->SetModelConut(MODEL_BULLET_GRENADE);

	return pGrenade;
}