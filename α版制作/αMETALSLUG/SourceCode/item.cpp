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
}

// =====================================================================================================================================================================
//
// デストラクタ
//
// =====================================================================================================================================================================
CItem::~CItem()
{
#ifdef _DEBUG

	// 当たり判定の削除
	if (m_pCollision != nullptr)
	{
		delete m_pCollision;
		m_pCollision = nullptr;
	}
#endif // _DEBUG

}

// =====================================================================================================================================================================
//
// 初期化処理
//
// =====================================================================================================================================================================
HRESULT CItem::Init()
{
	// 変数初期化
	m_Type = ITEMTYPE_HEAVYMACHINEGUN;			// タイプ

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

	// マップのポインタ取得
	CMap *pMap;
	pMap = CManager::GetBaseMode()->GetMap();

	// マップモデルが存在した時
	if (pMap != nullptr)
	{
		// レイの判定
		if (m_pCollision->RayCollision(pMap))
		{
			// 弾の削除
			Rerease();
		}
		else
		{
		}
	}

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

	//CHossoLibrary::SetBillboard(&mtxView);
	// 逆行列
	m_mtxWorld._11 = mtxView._11;
	m_mtxWorld._12 = mtxView._21;
	m_mtxWorld._13 = mtxView._31;
	m_mtxWorld._21 = mtxView._12;
	m_mtxWorld._22 = mtxView._22;
	m_mtxWorld._23 = mtxView._32;

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
		//ヘビーマシンガン
	case (ITEMTYPE_HEAVYMACHINEGUN): {
		pPlayer->GetGun()->SetGunType(CGun::GUNTYPE_HEAVYMACHINEGUN);
	}break;

		//ショットガン
	case (ITEMTYPE_SHOTGUN): {
		pPlayer->GetGun()->SetGunType(CGun::GUNTYPE_SHOTGUN);
	}break;

		//レーザーガン
	case (ITEMTYPE_LASERGUN): {
		pPlayer->GetGun()->SetGunType(CGun::GUNTYPE_LASERGUN);
	}break;

		//ロケットランチャー
	case (ITEMTYPE_ROCKETLAUNCHER): {
		pPlayer->GetGun()->SetGunType(CGun::GUNTYPE_ROCKETLAUNCHER);
	}break;

		//フレイムショット
	case (ITEMTYPE_FLAMESHOT): {
		pPlayer->GetGun()->SetGunType(CGun::GUNTYPE_FLAMESHOT);
	}break;

		//熊
	case (ITEMTYPE_BEAR): {
		// スコアアップ
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
// 捕虜用生成処理
//
// =====================================================================================================================================================================
CItem * CItem::RandCreate(const D3DXVECTOR3 pos)
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

		//熊
	case (ITEMTYPE_BEAR): {
		// テクスチャの割り当て
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_BEAR));
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
