// =====================================================================================================================================================================
//
// フレイムショットの処理 [flameshot.cpp]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#include "flameshot.h"			// インクルードファイル
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "debugproc.h"
#include "texture.h"
#include "particle.h"
#include "TexAnimation3D_Collision.h"

// =====================================================================================================================================================================
// 静的メンバ変数の初期化
// =====================================================================================================================================================================

// =====================================================================================================================================================================
// マクロ定義
// =====================================================================================================================================================================
#define MOVE_RANGE_HEIGHT		(3.0f)		// 縦の移動量の範囲
#define MOVE_RESTRAIN_HEIGHT	(0.8f)		// 縦の移動量を抑制する
#define MOVE_RISE_HEIGHT		(3.5f)		// 上昇する移動量

// =====================================================================================================================================================================
//
// コンストラクタ
//
// =====================================================================================================================================================================
CFlameshot::CFlameshot(OBJ_TYPE type) :CBullet(type)
{
	SetObjType(OBJTYPE_BULLET);
}

// =====================================================================================================================================================================
//
// デストラクタ
//
// =====================================================================================================================================================================
CFlameshot::~CFlameshot()
{
}

// =====================================================================================================================================================================
//
// 初期化処理
//
// =====================================================================================================================================================================
HRESULT CFlameshot::Init()
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
void CFlameshot::Uninit(void)
{
	// 終了
	CBullet::Uninit();
}

// =====================================================================================================================================================================
//
// 更新処理
//
// =====================================================================================================================================================================
void CFlameshot::Update(void)
{
	// 移動量
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// 移動量取得
	move = D3DXVECTOR3(GetMove().x * 0.92f, GetMove().y, GetMove().z * 0.92f);

	// 一定範囲上昇したら
	if (move.y > MOVE_RANGE_HEIGHT)
	{
		// 移動を抑える
		move.y += sinf(-MOVE_RESTRAIN_HEIGHT);
	}
	// 一定範囲下降したら
	else if (move.y < -MOVE_RANGE_HEIGHT)
	{
		// 移動を抑える
		move.y += sinf(MOVE_RESTRAIN_HEIGHT);
	}
	else
	{
		// 上昇する
		move.y += sinf(-MOVE_RISE_HEIGHT);
	}

	// 移動量の設定
	SetMove(move);

	// 更新
	CBullet::Update();

	CDebugProc::Print("\n\n BulletMove (%f, %f, %f)\n\n", GetMove().x, GetMove().y, GetMove().z);

	if (CBullet::GetLife() % 3 == 0)
	{
		CParticle::CreateFromText(GetPosition() + CHossoLibrary::RandomVector3(10), ZeroVector3,
			CParticleParam::EFFECT_FIRE, GetTag(), GetBulletParam(CGun::GUNTYPE_FLAMESHOT)->nPower);
	}
}

// =====================================================================================================================================================================
//
// 描画処理
//
// =====================================================================================================================================================================
void CFlameshot::Draw(void)
{
	// 描画
	CBullet::Draw();
}

// =====================================================================================================================================================================
//
// 弾を消す処理
//
// =====================================================================================================================================================================
void CFlameshot::DeleteBullet()
{

}

// =====================================================================================================================================================================
//
// デバッグ
//
// =====================================================================================================================================================================
void CFlameshot::DebugInfo()
{
}

// =====================================================================================================================================================================
//
// フレイムショットの生成
//
// =====================================================================================================================================================================
CFlameshot * CFlameshot::Create(D3DXVECTOR3 rot)
{
	// 変数
	CFlameshot *pFlameshot;

	// メモリの確保
	pFlameshot = new CFlameshot(OBJTYPE_BULLET);

	// フレイムショットのパラメーター取得
	BULLET_PARAM *pBulletParam = pFlameshot->GetBulletParam(CGun::GUNTYPE_FLAMESHOT);

	// 初期化
	pFlameshot->Init();

	// 弾の移動量計算
	pFlameshot->CalcBulletMove(rot, CGun::GUNTYPE_FLAMESHOT);

	// モデルタイプの設定
	pFlameshot->SetType(BULLET_MODEL);

	// モデルカウントの設定
	pFlameshot->SetModelConut(MODEL_BULLET_SPHERE);

	return pFlameshot;
}