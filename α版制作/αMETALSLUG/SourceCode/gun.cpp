// =====================================================================================================================================================================
//
// ガンの処理 [gun.cpp]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#include "gun.h"			// インクルードファイル
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "debugproc.h"
#include "handgun.h"
#include "heavymachinegun.h"
#include "shotgun.h"
#include "lasergun.h"
#include "rocketlauncher.h"
#include "flameshot.h"
#include "Character.h"

// =====================================================================================================================================================================
// 静的メンバ変数の初期化
// =====================================================================================================================================================================

// =====================================================================================================================================================================
// マクロ定義
// =====================================================================================================================================================================
#define HEAVYMACHINEGUN_SHOT_FRAME				(3)			// ヘビーマシンガンの弾の間隔

#define SHOT_BULLET_POS_Z						(20.0f)		// 弾の発射位置Z

// =====================================================================================================================================================================
//
// コンストラクタ
//
// =====================================================================================================================================================================
CGun::CGun(OBJ_TYPE type) :CModel(type)
{
}

// =====================================================================================================================================================================
//
// デストラクタ
//
// =====================================================================================================================================================================
CGun::~CGun()
{
}

// =====================================================================================================================================================================
//
// 初期化処理
//
// =====================================================================================================================================================================
HRESULT CGun::Init()
{
	m_bMultiple		= false;										// フラグをオフ
	m_GunType		= GUN_TYPE::GUNTYPE_HEAVYMACHINEGUN;			// ハンドガンに設定
	m_nCntFrame		= 0;											// フレームカウント
	m_nCntBullet	= 0;											// 弾のカウント
	m_nAmmo			= CBullet::GetBulletParam(m_GunType)->nAmmo;	// 残弾数
	m_nInterval		= 0;											// 次に撃つためのインターバル
	m_ShotPos		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 発射位置
	// 初期化
	CModel::Init();

	return S_OK;
}

// =====================================================================================================================================================================
//
// 終了処理
//
// =====================================================================================================================================================================
void CGun::Uninit(void)
{
	// 終了
	CModel::Uninit();
}

// =====================================================================================================================================================================
//
// 更新処理
//
// =====================================================================================================================================================================
void CGun::Update(void)
{
	// インターバルカウントアップ
	m_nInterval++;

	// 複数撃つフラグをオンのとき
	if (m_bMultiple)
	{
		// フレームカウントアップ
		m_nCntFrame++;

		// 複数発撃つ処理
		MultipleShot();
	}

	//// 弾薬が無くなったとき
	//if (m_nAmmo <= 0)
	//{
	//	// 弾薬数を0にする
	//	m_nAmmo = 0;
	//	// ハンドガンに戻す
	//	m_GunType = GUN_TYPE::GUNTYPE_HANDGUN;
	//}

	// 更新
	CModel::Update();
	CDebugProc::Print("\n\nHGPos %.1f, %.1f, %.1f\n\n", GetPosition().x, GetPosition().y, GetPosition().z);
}

// =====================================================================================================================================================================
//
// 描画処理
//
// =====================================================================================================================================================================
void CGun::Draw(void)
{
	// 描画
	CModel::Draw(*m_mtx);
}
// =====================================================================================================================================================================
//
// デバッグ
//
// =====================================================================================================================================================================
void CGun::DebugInfo()
{
}

// =====================================================================================================================================================================
//
// 銃の生成
//
// =====================================================================================================================================================================
CGun * CGun::Create(D3DXMATRIX *mtx)
{
	// 変数
	CGun *pGun;

	// メモリの確保
	pGun = new CGun(OBJTYPE_MODEL);

	// 初期化
	pGun->Init();
	
	// マトリックス代入
	pGun->m_mtx = mtx;

	// モデルタイプの設定
	pGun->SetType(GUN_MODEL);

	// モデルカウントの設定
	pGun->SetModelConut(MODEL_GUN_HANDGUN);

	return pGun;
}

// =====================================================================================================================================================================
//
// 銃の種類の設定
//
// =====================================================================================================================================================================
void CGun::SetGunType(GUN_TYPE type)
{
	BULLET_PARAM *pBulletParam = CBullet::GetBulletParam(type);

	// モデルの差し替え
	SetModelConut(type);

	// 種類の設定
	m_GunType = type;

	// 弾薬数
	m_nAmmo = pBulletParam->nAmmo;
}

// =====================================================================================================================================================================
//
// 銃の発射
//
// =====================================================================================================================================================================
void CGun::Shot(D3DXVECTOR3 rot)
{
	CBullet *pBullet = nullptr;

	m_rot = rot;	// 回転情報

	// ハンドガン以外のとき
	if (m_GunType != GUNTYPE_HANDGUN)
	{
		// 残弾数を減らす
		m_nAmmo--;
	}

	// インターバルが0のとき
	if (m_nInterval >= CBullet::GetBulletParam(m_GunType)->nInterval)
	{
		m_nInterval = 0;

		switch (m_GunType)
		{
		case CGun::GUNTYPE_HANDGUN:
			// ハンドガンの生成
			pBullet = CHandgun::Create(rot);
			break;

		case CGun::GUNTYPE_HEAVYMACHINEGUN:
			// ヘビーマシンガンの生成
			pBullet = CHeavyMachinegun::Create(rot);
			m_bMultiple = true;		// フラグをオン
			break;

		case CGun::GUNTYPE_SHOTGUN:
			// ショットガンの生成
			pBullet = CShotgun::Create(rot);
			break;

		case CGun::GUNTYPE_LASERGUN:
			// レーザーガンの生成
			pBullet = CLasergun::Create(rot);
			break;

		case CGun::GUNTYPE_ROCKETLAUNCHER:
			// ロケットランチャーの生成
			pBullet = CRocketlauncher::Create(rot);
			break;

		case CGun::GUNTYPE_FLAMESHOT:
			// フレイムショットの生成
			pBullet = CFlameshot::Create(rot);
			break;
		}
		if (pBullet)
		{
			D3DXVec3TransformCoord(&m_ShotPos, &D3DXVECTOR3(0.0f, 0.0f, -SHOT_BULLET_POS_Z), GetMatrix());

			// 位置の設定
			pBullet->SetPosition(m_ShotPos);

			// 弾の種類の設定
			pBullet->SetBulletType((CBullet::BULLET_TYPE)m_BulletType);

			// 弾のパラメーターの設定
			pBullet->SetBulletParam(m_GunType);
		}
	}
}

// =====================================================================================================================================================================
//
// 複数発撃つ処理
//
// =====================================================================================================================================================================
void CGun::MultipleShot()
{
	CBullet *pBullet = nullptr;

	float randPos_y = (float)(rand() % 10 - 5);

	if (m_nCntBullet < CBullet::GetBulletParam(m_GunType)->nTrigger)
	{
		if (m_nCntFrame >= HEAVYMACHINEGUN_SHOT_FRAME)
		{
		// フレームカウント初期化
		m_nCntFrame = 0;

		// ヘビーマシンガンのとき
		if (m_GunType == GUNTYPE_HEAVYMACHINEGUN)
		{
			// 弾の生成
			pBullet = CHeavyMachinegun::Create(m_rot);
		}
		// フレイムショットのとき
		if (m_GunType == GUNTYPE_FLAMESHOT)
		{
			// 弾の生成
			pBullet = CFlameshot::Create(m_rot);
		}

		// 残弾数を減らす
		m_nAmmo--;

		// 弾のカウントアップ
		m_nCntBullet++;

		if (pBullet)
		{
			D3DXVec3TransformCoord(&m_ShotPos, &D3DXVECTOR3(0.0f, 0.0f, -SHOT_BULLET_POS_Z), GetMatrix());

			// 位置の設定
			pBullet->SetPosition(D3DXVECTOR3(m_ShotPos.x, m_ShotPos.y + randPos_y, m_ShotPos.z));

			// 弾の種類の設定
			pBullet->SetBulletType((CBullet::BULLET_TYPE)m_BulletType);

			// 弾のパラメーターの設定
			pBullet->SetBulletParam(m_GunType);
		}
		}
	}
	else
	{
		// フレームカウント初期化
		m_nCntBullet = 0;

		// 複数撃つフラグをオフ
		m_bMultiple = false;
	}
}