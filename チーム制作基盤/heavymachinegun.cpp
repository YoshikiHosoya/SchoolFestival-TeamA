// =====================================================================================================================================================================
//
// ヘビーマシンガンの処理 [heavymachinegun.cpp]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#include "heavymachinegun.h"			// インクルードファイル
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
#define TEXTURE_FILE_HUNDGUN		"data/TEXTURE/00.png"		// 読み込むテクスチャファイル名
#define BULLET_SPEED				(3.0f)						// 弾速
#define BULLET_SIZE_X				(50)						// 弾の横のサイズ
#define BULLET_SIZE_Y				(50)						// 弾の縦のサイズ

// =====================================================================================================================================================================
//
// コンストラクタ
//
// =====================================================================================================================================================================
CHeavyMachinegun::CHeavyMachinegun(OBJ_TYPE type) :CBullet(type)
{
	SetObjType(OBJTYPE_BULLET);
}

// =====================================================================================================================================================================
//
// デストラクタ
//
// =====================================================================================================================================================================
CHeavyMachinegun::~CHeavyMachinegun()
{
}

// =====================================================================================================================================================================
//
// 初期化処理
//
// =====================================================================================================================================================================
HRESULT CHeavyMachinegun::Init()
{
	// 初期化
	CBullet::Init();

	// サイズの設定
	CBullet::SetSize(D3DXVECTOR3(BULLET_SIZE_X, BULLET_SIZE_Y, 0.0f));

	return S_OK;
}

// =====================================================================================================================================================================
//
// 終了処理
//
// =====================================================================================================================================================================
void CHeavyMachinegun::Uninit(void)
{
	// 終了
	CBullet::Uninit();
}

// =====================================================================================================================================================================
//
// 更新処理
//
// =====================================================================================================================================================================
void CHeavyMachinegun::Update(void)
{
	// 更新
	CBullet::Update();
}

// =====================================================================================================================================================================
//
// 描画処理
//
// =====================================================================================================================================================================
void CHeavyMachinegun::Draw(void)
{
	// 描画
	CBullet::Draw();
}
// =====================================================================================================================================================================
//
// デバッグ
//
// =====================================================================================================================================================================
void CHeavyMachinegun::DebugInfo()
{
}

// =====================================================================================================================================================================
//
// ヘビーマシンガンの生成
//
// =====================================================================================================================================================================
CHeavyMachinegun * CHeavyMachinegun::Create(D3DXVECTOR3 rot)
{
	// 変数
	CHeavyMachinegun *pHeavyMachinegun;

	// メモリの確保
	pHeavyMachinegun = new CHeavyMachinegun(OBJTYPE_BULLET);

	// 初期化
	pHeavyMachinegun->Init();

	// プレイヤーの向きに合わせる
	pHeavyMachinegun->GetMove() = D3DXVECTOR3(-sinf(rot.y) * cosf(rot.x) * BULLET_SPEED, sinf(rot.x) * BULLET_SPEED, -cosf(rot.y) * cosf(rot.x) * BULLET_SPEED);

	// テクスチャの割り当て
	pHeavyMachinegun->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_BULLET_HANDGUN));

	return pHeavyMachinegun;
}