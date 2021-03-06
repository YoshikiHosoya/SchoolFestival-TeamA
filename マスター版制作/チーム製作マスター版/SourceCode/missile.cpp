// =====================================================================================================================================================================
//
// ミサイルの処理 [missile.cpp]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#include "missile.h"			// インクルードファイル
#include "manager.h"
#include "renderer.h"
#include "particle.h"

// =====================================================================================================================================================================
// 静的メンバ変数の初期化
// =====================================================================================================================================================================

// =====================================================================================================================================================================
// マクロ定義
// =====================================================================================================================================================================
#define GRAVITY					(0.25f)		// 重力
#define MOVE_STRAIGHT_CNT		(69)		// 直進するまでのカウント
#define MOVE_STRAIGHT			(0.4f)		// 直進する移動量
#define MOVE_FALL_CNT			(20)		// 下降するまでのカウント
#define MISSILE_UP_ROT			(0.05f)		// ミサイルが上昇するときの回転量

// =====================================================================================================================================================================
//
// コンストラクタ
//
// =====================================================================================================================================================================
CMissile::CMissile(OBJ_TYPE type) :CBullet(type)
{
	// 初期化
	m_nCntFrame = 0;								// フレームカウント
	m_move		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 移動量

	SetObjType(OBJTYPE_BULLET);
}

// =====================================================================================================================================================================
//
// デストラクタ
//
// =====================================================================================================================================================================
CMissile::~CMissile()
{
}

// =====================================================================================================================================================================
//
// 初期化処理
//
// =====================================================================================================================================================================
HRESULT CMissile::Init()
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
void CMissile::Uninit(void)
{
	// 終了
	CBullet::Uninit();
}

// =====================================================================================================================================================================
//
// 更新処理
//
// =====================================================================================================================================================================
void CMissile::Update(void)
{
	// フレームカウントアップ
	m_nCntFrame++;
	// 重力
	m_move.y -= GRAVITY;

	// ミサイルの回転処理
	MissileRotation();

	// ミサイルの移動処理
	MissileMove();

	// 移動量の設定
	SetMove(m_move);

	// 回転の計算
	CHossoLibrary::CalcRotation(GetRot().z);

	// 更新
	CBullet::Update();

	//パーティクル発生 軌跡みたいな
	CParticle::CreateFromText(GetPosition(), D3DXVECTOR3(0.0f, 0.0f, CHossoLibrary::Random_PI()), CParticleParam::EFFECT_SMOKE,CBullet::GetTag());
}

// =====================================================================================================================================================================
//
// 描画処理
//
// =====================================================================================================================================================================
void CMissile::Draw(void)
{
	// 描画
	CBullet::Draw();
}

// =====================================================================================================================================================================
//
// 弾を消す処理
//
// =====================================================================================================================================================================
void CMissile::DeleteBullet()
{
	CBullet::DeleteBullet();

	CParticle::CreateFromText(GetPosition(), ZeroVector3, CParticleParam::EFFECT_EXPLOSION_ROCKETLANCHAR, GetTag(), GetBulletParam(CGun::GUNTYPE_ROCKETLAUNCHER)->nPower);

}

// =====================================================================================================================================================================
//
// 弾の反応
//
// =====================================================================================================================================================================
void CMissile::BulletReaction(D3DXVECTOR3 rot)
{
	//エフェクト生成
	CParticle::CreateFromText(GetPosition(), ZeroVector3, CParticleParam::EFFECT_FIRE_BULLET,TAG::NONE,0,WhiteColor,GetPositionPtr());

}

// =====================================================================================================================================================================
//
// デバッグ
//
// =====================================================================================================================================================================
void CMissile::DebugInfo()
{
}

// =====================================================================================================================================================================
//
// ミサイルの生成
//
// =====================================================================================================================================================================
CMissile * CMissile::Create(D3DXVECTOR3 rot)
{
	// 変数
	CMissile *pMissile;

	// メモリの確保
	pMissile = new CMissile(OBJTYPE_BULLET);

	// ミサイルのパラメーター取得
	BULLET_PARAM *pBulletParam = pMissile->GetBulletParam(CGun::GUNTYPE_ROCKETLAUNCHER);

	// 初期化
	pMissile->Init();

	//回転量設定
	pMissile->SetRot(D3DXVECTOR3(0.0f,0.0f, rot.z - D3DX_PI));

	// 弾の移動量計算
	pMissile->CalcBulletMove(rot, CGun::GUNTYPE_ROCKETLAUNCHER);

	// モデルタイプの設定
	pMissile->SetType(BULLET_MODEL);

	// モデルカウントの設定
	pMissile->SetModelID(MODEL_BULLET_ROCKETLAUNCHER);

	if (rot.z < 0)
	{
		pMissile->m_move = D3DXVECTOR3(1.0f, 8.0f, 0.0f);	// 移動量
	}
	else if(rot.z > 0)
	{
		pMissile->m_move = D3DXVECTOR3(-1.0f, 8.0f, 0.0f);	// 移動量
	}

	return pMissile;
}

// =====================================================================================================================================================================
//
// ミサイルの回転処理
//
// =====================================================================================================================================================================
void CMissile::MissileRotation()
{
	if (m_move.x > 0)
	{
		if (m_nCntFrame < MOVE_FALL_CNT)
		{
			GetRot().z = D3DX_PI * 0.9f;
		}
		else if (m_nCntFrame > MOVE_FALL_CNT)
		{
			GetRot().z -= MISSILE_UP_ROT;
		}
	}
	else if (m_move.x < 0)
	{
		if (m_nCntFrame < MOVE_FALL_CNT)
		{
			GetRot().z = -D3DX_PI * 0.9f;
		}
		else if (m_nCntFrame > MOVE_FALL_CNT)
		{
			GetRot().z += MISSILE_UP_ROT;
		}

	}
}

// =====================================================================================================================================================================
//
// ミサイルの移動処理
//
// =====================================================================================================================================================================
void CMissile::MissileMove()
{
	// 一定時間経過したら直進する
	if (m_nCntFrame > MOVE_STRAIGHT_CNT)
	{
		if (GetRot().z > 0)
		{
			GetRot().z = D3DX_PI / 2;

			// 横移動
			m_move.x += MOVE_STRAIGHT;
		}
		else if (GetRot().z < 0)
		{
			GetRot().z = -D3DX_PI / 2;

			// 横移動
			m_move.x -= MOVE_STRAIGHT;
		}
		// 落下を止める
		m_move.y = 0.0f;
	}
}