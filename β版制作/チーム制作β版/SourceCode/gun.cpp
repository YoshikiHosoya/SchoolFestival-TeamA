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
#include "TexAnimation3D.h"
#include "TrackingGun.h"
#include "diffusiongun.h"
#include "sound.h"
// =====================================================================================================================================================================
// 静的メンバ変数の初期化
// =====================================================================================================================================================================

// =====================================================================================================================================================================
// マクロ定義
// =====================================================================================================================================================================
#define HEAVYMACHINEGUN_SHOT_FRAME				(3)			// ヘビーマシンガンの弾の間隔


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
			pBullet = CShotgun::Create(m_ShotRot);
			break;

		case CGun::GUNTYPE_LASERGUN:
			// レーザーガンの生成
			pBullet = CLasergun::Create(m_ShotRot);
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
			// 戦車の銃の生成
			pBullet = CTracking::Create(m_Shotvector);
			m_bMultiple = true;		// 複数発撃つフラグをオン
			break;
		case CGun::GUNTYPE_DIFFUSIONGUN:
			// 戦車の銃の生成
			pBullet = CDiffusion::Create(m_Shotvector);
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

			//ノズルフラッシュ
			CTexAnimation3D::Create(m_ShotPos, D3DXVECTOR3(30.0f, 30.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				CTexture::SEPARATE_TEX_EFFECT_SHOTFLASH, 1, CScene::OBJTYPE_EFFECT);

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

				//ノズルフラッシュ
				CTexAnimation3D::Create(m_ShotPos, D3DXVECTOR3(30.0f, 30.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					CTexture::SEPARATE_TEX_EFFECT_SHOTFLASH, 1, CScene::OBJTYPE_EFFECT);

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