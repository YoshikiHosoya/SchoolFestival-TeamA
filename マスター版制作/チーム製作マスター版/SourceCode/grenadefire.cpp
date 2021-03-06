// =====================================================================================================================================================================
//
// グレネード発射の処理 [grenadefire.cpp]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#include "grenadefire.h"			// インクルードファイル
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "debugproc.h"
#include "texture.h"
#include "Player.h"
#include "grenade.h"
#include "sound.h"

// =====================================================================================================================================================================
// 静的メンバ変数の初期化
// =====================================================================================================================================================================

// =====================================================================================================================================================================
// マクロ定義
// =====================================================================================================================================================================
#define GRENADE_ADD_AMMO			(10)			// グレネードの増える弾数量
#define MAX_GRENADE_AMMO			(99)			// グレネードの残数の最大値
#define DROP_BOMB_FIRE_FRAME		(20)			// ドロップボムの間隔

// =====================================================================================================================================================================
//
// コンストラクタ
//
// =====================================================================================================================================================================
CGrenadeFire::CGrenadeFire(OBJ_TYPE type) :CScene(type)
{
	m_nAmmo			= 0;				// 残弾数
	m_nInterval		= 0;				// インターバル
	m_type			= HAND_GRENADE;		// グレネードの種類
	m_nCntFrame		= 0;				// フレームカウント
	m_nCntGrenade	= 0;				// グレネードのカウント
	m_pBulletParam	= nullptr;			// 弾(グレネード)のパラメーター
	m_rot			= ZeroVector3;		// 回転
	m_bMultiple		= false;			// 複数放つフラグをオフ
}

// =====================================================================================================================================================================
//
// デストラクタ
//
// =====================================================================================================================================================================
CGrenadeFire::~CGrenadeFire()
{
}

// =====================================================================================================================================================================
//
// 初期化処理
//
// =====================================================================================================================================================================
HRESULT CGrenadeFire::Init()
{
	SetGrenadeAmmoDefault();

	return S_OK;
}

// =====================================================================================================================================================================
//
// 終了処理
//
// =====================================================================================================================================================================
void CGrenadeFire::Uninit(void)
{
}

// =====================================================================================================================================================================
//
// 更新処理
//
// =====================================================================================================================================================================
void CGrenadeFire::Update(void)
{
	// インターバルカウントアップ
	m_nInterval++;

	// 複数撃つフラグをオンのとき
	if (m_bMultiple)
	{
		// フレームカウントアップ
		m_nCntFrame++;

		// 複数発撃つ処理
		MultipleFire();
	}

	// 残弾数の最大値
	if (m_nAmmo >= MAX_GRENADE_AMMO)
	{
		m_nAmmo = MAX_GRENADE_AMMO;
	}
}

// =====================================================================================================================================================================
//
// 描画処理
//
// =====================================================================================================================================================================
void CGrenadeFire::Draw(void)
{
}

// =====================================================================================================================================================================
//
// デバッグ
//
// =====================================================================================================================================================================
void CGrenadeFire::DebugInfo(void)
{
}

// =====================================================================================================================================================================
//
// グレネードを放つ位置の生成
//
// =====================================================================================================================================================================
CGrenadeFire * CGrenadeFire::Create()
{
	// 変数
	CGrenadeFire *pGrenadeFire;

	// メモリの確保
	pGrenadeFire = new CGrenadeFire(OBJTYPE_MODEL);

	// 初期化
	pGrenadeFire->Init();

	return pGrenadeFire;
}

// =====================================================================================================================================================================
//
// グレネード放つ
//
// =====================================================================================================================================================================
void CGrenadeFire::Fire(D3DXVECTOR3 rot)
{
	CGrenade	*pGrenade	= nullptr;

	m_rot = rot;

	// グレネードの生成
	pGrenade = CGrenade::Create(rot, m_type);

	// パラメーター取得
	switch (m_type)
	{
	case CGrenadeFire::HAND_GRENADE:
		m_pBulletParam = CBullet::GetBulletParam(CGun::GUNTYPE_HANDGRENADE);
		break;
	case CGrenadeFire::TANK_GRENADE:
		m_pBulletParam = CBullet::GetBulletParam(CGun::GUNTYPE_TANKGRENADE);
		break;
	case CGrenadeFire::DROP_BOMB:
		m_pBulletParam = CBullet::GetBulletParam(CGun::GUNTYPE_DROPBOMB);
		// 複数放つフラグをオンにする
		m_bMultiple = true;
		break;
	}

	// インターバルが経過したとき
	if (m_nInterval >= m_pBulletParam->nInterval)
	{
		// 残弾数を減らす
		m_nAmmo--;

		m_nInterval = 0;

		if (pGrenade)
		{
			// 位置の初期化
			D3DXVECTOR3 pos = ZeroVector3;
			D3DXVec3TransformCoord(&pos, &ZeroVector3, m_mtx);

			// 位置の設定
			pGrenade->SetPosition(pos);

			// タグの設定
			pGrenade->SetTag(GetTag());

			// 弾のパラメーターの設定
			switch (m_type)
			{
			case CGrenadeFire::HAND_GRENADE:
				pGrenade->SetBulletParam(CGun::GUNTYPE_HANDGRENADE);
				break;
			case CGrenadeFire::TANK_GRENADE:
				pGrenade->SetBulletParam(CGun::GUNTYPE_TANKGRENADE);
				CManager::GetSound()->Play(CSound::LABEL_SE_EXPLOSION_00);
				break;
			case CGrenadeFire::DROP_BOMB:
				pGrenade->SetBulletParam(CGun::GUNTYPE_DROPBOMB);
				break;
			}
		}
	}
}

// =====================================================================================================================================================================
//
// グレネードの弾数初期設定
//
// =====================================================================================================================================================================
void CGrenadeFire::SetGrenadeAmmoDefault()
{
	// 残弾数
	switch (m_type)
	{
	case CGrenadeFire::HAND_GRENADE:
		m_nAmmo = CBullet::GetBulletParam(CGun::GUNTYPE_HANDGRENADE)->nAmmo;
		break;
	case CGrenadeFire::TANK_GRENADE:
		m_nAmmo = CBullet::GetBulletParam(CGun::GUNTYPE_TANKGRENADE)->nAmmo;
		break;
	case CGrenadeFire::DROP_BOMB:
		m_nAmmo = CBullet::GetBulletParam(CGun::GUNTYPE_DROPBOMB)->nAmmo;
		break;
	}
}

// =====================================================================================================================================================================
//
// グレネードの弾数追加
//
// =====================================================================================================================================================================
void CGrenadeFire::GrenadeAddAmmo()
{
	m_nAmmo += GRENADE_ADD_AMMO;
}

// =====================================================================================================================================================================
//
// 複数発放つ処理
//
// =====================================================================================================================================================================
void CGrenadeFire::MultipleFire()
{
	CGrenade *pGrenade = nullptr;

	if (m_nCntGrenade < (m_pBulletParam->nTrigger))
	{
		// ドロップボムのとき
		if (m_type == GRENADE_TYPE::DROP_BOMB)
		{
			if (m_nCntFrame >= DROP_BOMB_FIRE_FRAME)
			{
				// 複数撃った弾を減らす処理
				ProcessReduceMultipleGrenade();

				// グレネードの生成
				pGrenade = CGrenade::Create(m_rot, m_type);
			}
		}

		//弾が生成された場合
		if (pGrenade)
		{
			D3DXVECTOR3 pos = ZeroVector3;
			D3DXVec3TransformCoord(&pos, &ZeroVector3, m_mtx);

			// 位置の設定
			pGrenade->SetPosition(pos);

			// タグの設定
			pGrenade->SetTag(GetTag());

			// 弾のパラメーターの設定
			if (m_type == GRENADE_TYPE::DROP_BOMB)
			{
				pGrenade->SetBulletParam(CGun::GUNTYPE_DROPBOMB);
			}
		}
	}
	else
	{
		// フレームカウント初期化
		m_nCntGrenade = 0;

		// 複数撃つフラグをオフ
		m_bMultiple = false;
	}
}

// =====================================================================================================================================================================
//
// 複数放ったグレネードを減らす処理
//
// =====================================================================================================================================================================
void CGrenadeFire::ProcessReduceMultipleGrenade()
{
	// フレームカウント初期化
	m_nCntFrame = 0;

	// グレネードのカウントアップ
	m_nCntGrenade++;
}