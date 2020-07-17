// =====================================================================================================================================================================
//
// アイテム処理の説明[item.cpp]
// Author : Fujiwara Masato
//
// =====================================================================================================================================================================
#include "item.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "texture.h"
#include "collision.h"
#include "debugproc.h"
#include "player.h"
#include "playerui.h"
#include "gun.h"

// =====================================================================================================================================================================
// 静的メンバ変数の初期化
// =====================================================================================================================================================================

// =====================================================================================================================================================================
// マクロ定義
// =====================================================================================================================================================================
#define ITEM_SIZE_XY				(D3DXVECTOR3(20.0f,20.0f,0.0f))				// アイテムのサイズ
#define ITEM_COLLISION_SIZE_XY		(D3DXVECTOR3(40.0f,40.0f,0.0f))				// アイテムのサイズ

// =====================================================================================================================================================================
//
// コンストラクタ
//
// =====================================================================================================================================================================
CItem::CItem(OBJ_TYPE type) :CScene3D(type)
{
	m_pCollision = nullptr;

	// アイテムがマップに残る時間
	m_nRemainTime = 240;
}

// =====================================================================================================================================================================
//
// デストラクタ
//
// =====================================================================================================================================================================
CItem::~CItem()
{
	// 当たり判定の削除
	if (m_pCollision != nullptr)
	{
		delete m_pCollision;
		m_pCollision = nullptr;
	}
}

// =====================================================================================================================================================================
//
// 初期化処理
//
// =====================================================================================================================================================================
HRESULT CItem::Init()
{
	// タイプの初期化
	m_Type = ITEMTYPE_HEAVYMACHINEGUN;

	// 初期化
	CScene3D::Init();

	// 当たり判定生成
	m_pCollision = CCollision::Create();
	m_pCollision->SetPos(&GetPosition());
	m_pCollision->SetSize2D(ITEM_COLLISION_SIZE_XY);
	m_pCollision->SetMove(nullptr);
	m_pCollision->DeCollisionCreate(CCollision::COLLISIONTYPE_NORMAL);

	return S_OK;
}

// =====================================================================================================================================================================
//
// 終了処理
//
// =====================================================================================================================================================================
void CItem::Uninit(void)
{
	// 終了処理
	CScene3D::Uninit();
}

// =====================================================================================================================================================================
//
// 更新処理
//
// =====================================================================================================================================================================
void CItem::Update(void)
{
	// 当たり判定
	if (m_pCollision != nullptr)
	{
		// 座標の更新 pos
		m_pCollision->SetPos(&GetPosition());
	}

	// アイテムの滞在時間管理
	RemainTimer();

	// 更新
	CScene3D::Update();
}

// =====================================================================================================================================================================
//
// 描画処理
//
// =====================================================================================================================================================================
void CItem::Draw(void)
{
	// 変数宣言
	LPDIRECT3DDEVICE9 pDevice =									// デバイスの取得
		CManager::GetRenderer()->GetDevice();

	// アルファテストの設定に変更
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);		// アルファテスト有効
	pDevice->SetRenderState(D3DRS_ALPHAREF, 200);				// アルファ値の基準設定(基準より大きいと描画する)
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);	// 状況に応じてアルファテストを実行する(新ピクセル > 現在のピクセル)
	pDevice->SetRenderState(D3DRS_LIGHTING, false);				// ライティングoff
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// ビルボード
	// ビューマトリックスの代入用
	D3DXMATRIX mtxView;
	// 現在のビューマトリックスを取得
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	// ビルボード処理
	CHossoLibrary::SetBillboard(&mtxView);

	// 描画
	CScene3D::Draw();

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	// アルファテストの設定を戻す
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);		// アルファテスト無効
	pDevice->SetRenderState(D3DRS_LIGHTING, true);				// ライティングon
}

// =====================================================================================================================================================================
//
// アイテム取得時の種類別処理
//
// =====================================================================================================================================================================
void CItem::ItemType(ITEMTYPE type)
{
	CPlayer *pPlayer = CManager::GetBaseMode()->GetPlayer();

	switch (type)
	{
		// ヘビーマシンガン
	case (ITEMTYPE_HEAVYMACHINEGUN): {
		pPlayer->GetGun()->SetGunType(CGun::GUNTYPE_HEAVYMACHINEGUN);
	}break;

		// ショットガン
	case (ITEMTYPE_SHOTGUN): {
		pPlayer->GetGun()->SetGunType(CGun::GUNTYPE_SHOTGUN);
	}break;

		// レーザーガン
	case (ITEMTYPE_LASERGUN): {
		pPlayer->GetGun()->SetGunType(CGun::GUNTYPE_LASERGUN);
	}break;

		// ロケットランチャー
	case (ITEMTYPE_ROCKETLAUNCHER): {
		pPlayer->GetGun()->SetGunType(CGun::GUNTYPE_ROCKETLAUNCHER);
	}break;

		// フレイムショット
	case (ITEMTYPE_FLAMESHOT): {
		pPlayer->GetGun()->SetGunType(CGun::GUNTYPE_FLAMESHOT);
	}break;

		// エネミーチェイサー
	case (ITEMTYPE_ENEMYCHASER): {
		//pPlayer->GetGun()->SetGunType(CGun::GUNTYPE_FLAMESHOT);
	}break;

		// アイアンリザード
	case (ITEMTYPE_IRONLIZARD): {
		//pPlayer->GetGun()->SetGunType(CGun::GUNTYPE_FLAMESHOT);
	}break;

		// 熊
	case (ITEMTYPE_BEAR): {
		// スコアアップ
		CPlayer *pPlayer = CManager::GetBaseMode()->GetPlayer();
		pPlayer->GetPlayerUI()->SetScore(100);
	}break;

		// 爆弾の数を増やす
	case (ITEMTYPE_BOMBUP): {
	}break;

		// 乗り物の耐久値を回復する
	case (ITEMTYPE_ENERGYUP): {
	}break;

		// ハンドガン以外の弾の残弾数を増やす
	case (ITEMTYPE_BULLETUP): {
	}break;

	default:
		break;
	}
}
// =====================================================================================================================================================================
//
// デバッグ
//
// =====================================================================================================================================================================
void CItem::DebugInfo()
{
}

// =====================================================================================================================================================================
//
// アイテムが判定をもらった時
//
// =====================================================================================================================================================================
void CItem::HitItem(ITEMTYPE type)
{
	// 種類ごとの処理
	ItemType(type);
	// 削除
	Rerease();
}

// =====================================================================================================================================================================
//
// アイテムを落とす位置の設定
//
// =====================================================================================================================================================================
void CItem::SetDropPos(D3DXVECTOR3 &characterpos)
{
	// プレイヤーのポインタ取得
	CPlayer *pPlayer = CManager::GetBaseMode()->GetPlayer();
	// プレイヤーが存在した時
	if (pPlayer != nullptr)
	{
		// プレイヤーの向きを取得
		if (pPlayer->GetCharacterDirection() == CPlayer::CHARACTER_LEFT)
		{
			characterpos.x -= 50;
		}
		else if(pPlayer->GetCharacterDirection() == CPlayer::CHARACTER_RIGHT)
		{
			characterpos.x += 50;
		}

		characterpos.y += 50;
	}
}

// =====================================================================================================================================================================
//
// 滞在時間を計算し0になったら削除する
//
// =====================================================================================================================================================================
void CItem::RemainTimer()
{
	// アイテムの滞在時間を減少
	m_nRemainTime--;

	// 残り時間が0以下になったら削除
	if (m_nRemainTime <= 0)
	{
		Rerease();
	}
}

// =====================================================================================================================================================================
//
// 生成処理
//
// =====================================================================================================================================================================
CItem * CItem::Create(D3DXVECTOR3 pos, ITEMTYPE type)
{
	// 変数
	CItem *pItem;

	// メモリの確保
	pItem = new CItem(OBJTYPE_ITEM);

	// 初期化
	pItem->Init();

	// サイズの設定
	pItem->SetSize(ITEM_SIZE_XY);

	// アイテムの位置の設定
	pItem->SetPosition(pos);

	// アイテムのタイプを設定
	pItem->m_Type = type;

	// 種類別にテクスチャを設定
	pItem->SwitchTexture(type,	pItem);

	return pItem;
}

// =====================================================================================================================================================================
//
// キャラクターがアイテムを落とすときの生成処理
//
// =====================================================================================================================================================================
CItem * CItem::DropCreate(D3DXVECTOR3 pos)
{
	// 変数
	CItem *pItem;

	// メモリの確保
	pItem = new CItem(OBJTYPE_ITEM);

	// 初期化
	pItem->Init();

	// サイズの設定
	pItem->SetSize(ITEM_SIZE_XY);

	// アイテムが生成される位置の調整
	pItem->SetDropPos(pos);

	// アイテムの位置の設定
	pItem->SetPosition(pos);

	// アイテムのタイプをランダムに設定
	pItem->m_Type = RandDropItem();

	// 種類別にテクスチャを設定
	pItem->SwitchTexture(pItem->m_Type, pItem);

	return pItem;
}

// =====================================================================================================================================================================
//
// 種類別テクスチャバインド処理
//
// =====================================================================================================================================================================
void CItem::SwitchTexture(ITEMTYPE type, CItem *pItem)
{
	switch (type)
	{
		//ヘビーマシンガン
	case (ITEMTYPE_HEAVYMACHINEGUN):{
		// テクスチャの割り当て
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_HEAVYMACHINEGUN));
	}break;

		//ショットガン
	case (ITEMTYPE_SHOTGUN): {
		// テクスチャの割り当て
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_SHOTGUN));
	}break;

		//レーザーガン
	case (ITEMTYPE_LASERGUN): {
		// テクスチャの割り当て
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_LASERGUN));
	}break;

		//ロケットランチャー
	case (ITEMTYPE_ROCKETLAUNCHER): {
		// テクスチャの割り当て
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_ROCKETLAUNCHER));
	}break;

		//フレイムショット
	case (ITEMTYPE_FLAMESHOT): {
		// テクスチャの割り当て
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_FLAMESHOT));
	}break;

		// エネミーチェイサー
	case (ITEMTYPE_ENEMYCHASER): {
		// テクスチャの割り当て
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_ENEMYCHASER));
	}break;

		// アイアンリザード
	case (ITEMTYPE_IRONLIZARD): {
		// テクスチャの割り当て
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_IRONLIZARD));
	}break;

		//熊
	case (ITEMTYPE_BEAR): {
		// テクスチャの割り当て
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_BEAR));
	}break;

		// 爆弾の数を増やす
	case (ITEMTYPE_BOMBUP): {
		// テクスチャの割り当て
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_BOMBUP));
	}break;

		// 乗り物の耐久値を回復する
	case (ITEMTYPE_ENERGYUP): {
		// テクスチャの割り当て
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_ENERGYUP));
	}break;

		// ハンドガン以外の弾の残弾数を増やす
	case (ITEMTYPE_BULLETUP): {
		// テクスチャの割り当て
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_BULLETUP));
	}break;

	default:
		break;
	}
}

// =====================================================================================================================================================================
//
// ドロップするアイテムのランダム処理
//
// =====================================================================================================================================================================
CItem::ITEMTYPE CItem::RandDropItem()
{
	return ITEMTYPE(rand() % ITEMTYPE_MAX);
}

// =====================================================================================================================================================================
//
// アイテムをドロップする確率を求める
//
// =====================================================================================================================================================================
bool CItem::DropRate()
{
	// アイテムをドロップするかのフラグ
	bool bDrop = false;

	// 求めたドロップ率を格納する変数
	int nDrop = 0;

	// ドロップ率を表す変数
	int nRate = 4;

	// 基準を求める
	int nAdjusted_max = (RAND_MAX + 1) - (RAND_MAX + 1) % nRate;

	// ランダムに求めた値を格納する比較用変数
	int nRandom = 0;

	// RAND_MAX + 1 が nRate で割り切れない場合、乱数がその端数分の範囲になったら捨ててやり直す
	do {
		// ランダムに値を求める
		nRandom = rand();
	} while (nRandom >= nAdjusted_max);

	//
	nDrop = (int)(((float)nRandom / nAdjusted_max) * nRate);

	// 結果が0ならアイテムをドロップする許可を出す
	if (nDrop == 0)
	{
		bDrop = true;
	}

	// 結果がそれ以外ならアイテムをドロップする許可を出さない
	else
	{
		bDrop = false;
	}

	// 結果を返す
	return bDrop;
}
