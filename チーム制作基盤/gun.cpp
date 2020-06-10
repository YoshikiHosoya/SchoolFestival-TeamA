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

// =====================================================================================================================================================================
// 静的メンバ変数の初期化
// =====================================================================================================================================================================

// =====================================================================================================================================================================
// マクロ定義
// =====================================================================================================================================================================
#define HANDGUN_AMMO				(1)			// ハンドガンの弾薬数
#define HEAVYMACHINEGUN_AMMO		(200)		// ヘビーマシンガンの弾薬数

#define HANDGUN_POS_X				(-10)		// ハンドガンの位置X
#define HANDGUN_POS_Y				(10)		// ハンドガンの位置Y
#define HANDGUN_POS_Z				(0)			// ハンドガンの位置Z

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
	m_type = GUN_TYPE::GUNTYPE_HANDGUN;

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
	// ハンドガン以外のとき
	if (m_type != GUN_TYPE::GUNTYPE_HANDGUN)
	{
		// デクリメント
		m_nAmmo--;

		// 弾薬が無くなったとき
		if (m_nAmmo <= 0)
		{
			// 弾薬数を0にする
			m_nAmmo = 0;
			// ハンドガンに戻す
			m_type = GUN_TYPE::GUNTYPE_HANDGUN;
		}
	}

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

	D3DXVECTOR3	pos = D3DXVECTOR3(HANDGUN_POS_X, HANDGUN_POS_Y, HANDGUN_POS_Z);
	// 位置の設定
	pGun->SetPosition(pos);

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
	// 種類の設定
	m_type = type;

	// 種類ごとの弾薬数
	switch (type)
	{
	case CGun::GUNTYPE_HANDGUN:
		m_nAmmo = HANDGUN_AMMO;
		break;

	case CGun::GUNTYPE_HEAVYMACHINEGUN:
		m_nAmmo = HEAVYMACHINEGUN_AMMO;
		break;
	}
}

// =====================================================================================================================================================================
//
// 銃の発射
//
// =====================================================================================================================================================================
void CGun::Shot(D3DXVECTOR3 rot)
{
	switch (m_type)
	{
	case CGun::GUNTYPE_HANDGUN:
		// ハンドガンの生成
		CHandgun::Create(D3DXVECTOR3(m_mtx->_41, m_mtx->_42, m_mtx->_43), rot);
		break;

	case CGun::GUNTYPE_HEAVYMACHINEGUN:
		// ヘビーマシンガンの生成
		CHeavyMachinegun::Create(GetPosition(), GetRot());
		break;
	}
}