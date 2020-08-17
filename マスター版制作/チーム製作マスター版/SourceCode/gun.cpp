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
#include "tankgun.h"
#include "planegun.h"
#include "Character.h"
#include "TrackingGun.h"
#include "diffusiongun.h"
#include "sound.h"
#include "particle.h"
#include "balkan.h"
#include "incendiary.h"
#include "flamethrower.h"
// =====================================================================================================================================================================
// 静的メンバ変数の初期化
// =====================================================================================================================================================================

// =====================================================================================================================================================================
// マクロ定義
// =====================================================================================================================================================================
#define HEAVYMACHINEGUN_SHOT_FRAME				(3)			// ヘビーマシンガンの弾の間隔
#define MAX_AMMO								(999)		// 残弾数の最大値

// =====================================================================================================================================================================
//
// コンストラクタ
//
// =====================================================================================================================================================================
CGun::CGun()
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
	m_GunType		= GUN_TYPE::GUNTYPE_HANDGUN;					// ハンドガンに設定
	m_GunTypeOld	= GUN_TYPE::GUNTYPE_HANDGUN;					// 前回の銃の種類
	m_nCntFrame		= 0;											// フレームカウント
	m_nCntBullet	= 0;											// 弾のカウント
	m_nAmmo			= CBullet::GetBulletParam(m_GunType)->nAmmo;	// 残弾数
	m_nInterval		= 0;											// 次に撃つためのインターバル
	m_ShotPos		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 発射位置
	m_ShotOffsetPos	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 発射位置のオフセット
	m_ShotRot		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 撃つときの回転の向き
	m_bDraw			= false;										// 描画フラグ

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

	// 弾薬が無くなったとき
	if (m_nAmmo <= 0)
	{
		// 弾薬数を0にする
		m_nAmmo = 0;
		// ハンドガンに戻す
		m_GunType = GUN_TYPE::GUNTYPE_HANDGUN;
	}

	// 残弾数の最大値
	if (m_nAmmo >= MAX_AMMO)
	{
		m_nAmmo = MAX_AMMO;
	}

	// 更新
	CModel::Update();
}

// =====================================================================================================================================================================
//
// 描画処理
//
// =====================================================================================================================================================================
void CGun::Draw(void)
{
	// 乗り物に乗っていたら描画しない
	if (m_bDraw == false)
	{
		// 描画
		CModel::Draw(*m_HasHandMtx);
	}
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
	pGun = new CGun();

	// 初期化
	pGun->Init();

	// マトリックス代入
	pGun->m_HasHandMtx = mtx;

	// モデルタイプの設定
	pGun->SetType(GUN_MODEL);

	// モデルカウントの設定
	pGun->SetModelConut(MODEL_GUN_HANDGUN);

	return pGun;
}

// =====================================================================================================================================================================
//
// マトリックスの計算だけする
//
// =====================================================================================================================================================================
void CGun::NoDrawCalcMatrixOnly()
{
	CModel::NotDrawCalcMtxOnly(m_HasHandMtx);
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

	// 前回の銃の種類を保存
	m_GunTypeOld = m_GunType;

	// 種類の設定
	m_GunType = type;

	// 前回と種類が違うとき
	if (m_GunType != m_GunTypeOld)
	{
		// 弾薬数
		m_nAmmo = pBulletParam->nAmmo;
	}
	else
	{
		// 弾薬数補充
		m_nAmmo += pBulletParam->nAmmo;
	}
}

// =====================================================================================================================================================================
//
// 弾数の加算
//
// =====================================================================================================================================================================
void CGun::GunAddAmmo(int nAmmo)
{
	m_nAmmo += nAmmo;
}

// =====================================================================================================================================================================
//
// 銃の発射
//
// =====================================================================================================================================================================
void CGun::Shot()
{
	D3DXVec3TransformCoord(&m_ShotPos, &m_ShotOffsetPos, GetMatrix());

	//画面外から発射不可
	if (!CManager::GetRenderer()->CheckScreenRange(m_ShotPos))
	{
		return;
	}

	CBullet *pBullet = nullptr;

	// ハンドガンと戦車の銃以外のとき
	if (m_GunType != GUNTYPE_HANDGUN && m_GunType != GUNTYPE_TANKGUN)
	{
		// 残弾数を減らす
		m_nAmmo--;
	}

	// インターバルが経過したとき
	if (m_nInterval >= CBullet::GetBulletParam(m_GunType)->nInterval)
	{
		m_nInterval = 0;

		switch (m_GunType)
		{
		case CGun::GUNTYPE_HANDGUN:
			// ハンドガンの生成
			pBullet = CHandgun::Create(m_ShotRot);
			break;

		case CGun::GUNTYPE_HEAVYMACHINEGUN:
			// ヘビーマシンガンの生成
			pBullet = CHeavyMachinegun::Create(m_ShotRot);
			m_bMultiple = true;		// フラグをオン
			break;

		case CGun::GUNTYPE_SHOTGUN:
			// ショットガンの生成
			CParticle::CreateFromText(m_ShotPos, m_ShotRot, CParticleParam::EFFECT_SHOTGUN, GetTag(), CBullet::GetBulletParam(CGun::GUNTYPE_SHOTGUN)->nPower);

			break;

		case CGun::GUNTYPE_LASERGUN:
			// レーザーガンの生成
			CParticle::CreateFromText(m_ShotPos, m_ShotRot, CParticleParam::EFFECT_LAZER, GetTag(), CBullet::GetBulletParam((int)CGun::GUNTYPE_LASERGUN)->nPower, D3DXCOLOR(0.0f,0.0f,0.0f,-1.0f),GetShotPosPtr());
			m_bMultiple = true;		// フラグをオン
			break;

		case CGun::GUNTYPE_ROCKETLAUNCHER:
			// ロケットランチャーの生成
			pBullet = CRocketlauncher::Create(m_ShotRot);
			break;

		case CGun::GUNTYPE_FLAMESHOT:
			// フレイムショットの生成
			pBullet = CFlameshot::Create(m_ShotRot);
			break;

		case CGun::GUNTYPE_TANKGUN:
			// 戦車の銃の生成
			pBullet = CTankGun::Create(m_ShotRot);
			m_bMultiple = true;		// 複数発撃つフラグをオン
			break;

		case CGun::GUNTYPE_PLANEGUN:
			// 戦車の銃の生成
			pBullet = CPlaneGun::Create(m_ShotRot);
			m_bMultiple = true;		// 複数発撃つフラグをオン
			break;
		case CGun::GUNTYPE_TRACKINGGUN:
			// 追従弾
			pBullet = CTracking::Create(m_ShotRot);
			break;
		case CGun::GUNTYPE_DIFFUSIONGUN:
			// 拡散弾
			pBullet = CDiffusion::Create(m_ShotRot);
			break;
		case CGun::GUNTYPE_BOSSLASERGUN:
			// 拡散弾
			CParticle::CreateFromText(m_ShotPos, m_ShotRot, CParticleParam::EFFECT_BOSSLAZER, GetTag(), CBullet::GetBulletParam((int)CGun::GUNTYPE_BOSSLASERGUN)->nPower, D3DXCOLOR(0.0f, 0.0f, 0.0f, -1.0f), GetShotPosPtr());
			break;

		case CGun::GUNTYPE_BALKAN:
			//
			pBullet = CBalkan::Create(m_ShotRot);
			m_bMultiple = true;		// 複数発撃つフラグをオン
			break;
		case CGun::GUNTYPE_FLAMETHROWER:
			//
			pBullet = CFlamethrower::Create(m_ShotRot);
			m_bMultiple = true;		// 複数発撃つフラグをオン
			break;
		case CGun::GUNTYPE_INCENDIARY:
			//
			pBullet = CIncendiary::Create(m_ShotRot);
			m_bMultiple = true;		// 複数発撃つフラグをオン
			break;

		}
		if (pBullet)
		{
			// 位置の設定
			pBullet->SetPosition(m_ShotPos);

			// タグの設定
			pBullet->SetTag(m_Tag);

			// 弾のパラメーターの設定
			pBullet->SetBulletParam(m_GunType);

			// 弾発砲時のリアクション
			pBullet->BulletReaction(m_ShotRot);

			////ノズルフラッシュ
			CParticle::CreateFromText(m_ShotPos, ZeroVector3, CParticleParam::EFFECT_SHOTFLASH);

			//音再生
			CManager::GetSound()->Play(CSound::LABEL_SE_SHOT);
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

			// 残弾数を減らす
			m_nAmmo--;

			// ヘビーマシンガンのとき
			if (m_GunType == GUNTYPE_HEAVYMACHINEGUN)
			{
				// 弾の生成
				pBullet = CHeavyMachinegun::Create(m_ShotRot);
			}
			// フレイムショットのとき
			if (m_GunType == GUNTYPE_FLAMESHOT)
			{
				// 弾の生成
				pBullet = CFlameshot::Create(m_ShotRot);
			}
			// 戦車の銃のとき
			if (m_GunType == GUNTYPE_TANKGUN)
			{
				// 弾の生成
				pBullet = CTankGun::Create(m_ShotRot);
			}

			// 弾のカウントアップ
			m_nCntBullet++;

			if (pBullet)
			{
				D3DXVec3TransformCoord(&m_ShotPos, &m_ShotOffsetPos, GetMatrix());

				// 位置の設定
				pBullet->SetPosition(D3DXVECTOR3(m_ShotPos.x, m_ShotPos.y + randPos_y, m_ShotPos.z));

				// 弾の種類の設定
				pBullet->SetTag(m_Tag);

				// 弾のパラメーターの設定
				pBullet->SetBulletParam(m_GunType);

				// 弾の反応
				pBullet->BulletReaction(m_ShotRot);

				//音再生
				CManager::GetSound()->Play(CSound::LABEL_SE_SHOT);

				////ノズルフラッシュ
				CParticle::CreateFromText(m_ShotPos, ZeroVector3, CParticleParam::EFFECT_SHOTFLASH);


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