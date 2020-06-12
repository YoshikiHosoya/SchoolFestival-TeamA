// =====================================================================================================================================================================
//
// アイテムの処理 [item.cpp]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#include "item.h"			// インクルードファイル
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "debugproc.h"
#include "player.h"
#include "fade.h"
#include "effect.h"
#include "gameUI.h"
#include "score.h"
#include "particle.h"
#include "sound.h"

// =====================================================================================================================================================================
// 静的メンバ変数の初期化
// =====================================================================================================================================================================
LPDIRECT3DTEXTURE9	CItem::m_apTexture[ITEMTYPE::ITEMTYPE_MAX]	= {};			// テクスチャ情報
CEffect				*CItem::m_pEffect[MAX_EFFECT]				= {};			// エフェクト情報
int					CItem::m_nID								= 0;			// 番号

// =====================================================================================================================================================================
// マクロ定義
// =====================================================================================================================================================================
#define TEXTURE_FILE01		"data/TEXTURE/drunk.png"		// 読み込むテクスチャファイル名			( スピードアップ )
#define TEXTURE_FILE02		"data/TEXTURE/jewel02.png"		// 読み込むテクスチャファイル名			( ダイヤ )
#define TEXTURE_FILE03		"data/TEXTURE/jewel01.png"		// 読み込むテクスチャファイル名			( 宝石 )
#define TEXTURE_FILE04		"data/TEXTURE/gold.png"			// 読み込むテクスチャファイル名			( 金貨 )
#define TEXTURE_FILE05		"data/TEXTURE/key.png"			// 読み込むテクスチャファイル名			( 鍵 )
#define TEXTURE_FILE06		"data/TEXTURE/Dlunker.png"		// 読み込むテクスチャファイル名			( 1UP )
#define TEXTURE_FILE07		"data/TEXTURE/treasure.png"		// 読み込むテクスチャファイル名			( 財宝 )
#define TEXTURE_FILE08		"data/TEXTURE/energy.png"		// 読み込むテクスチャファイル名			( エネルギー )

#define ITEM_SIZEX			(20 / 2)						// 座標の幅
#define ITEM_SIZEY			(30 / 2)						// 座標の高さ

#define JUWEL_SIZEX			(30/ 2)							// 宝石の幅
#define JUWEL_SIZEY			(30 / 2)						// 宝石の高さ

#define TREASURE_SIZEX		(100/ 2)						// 宝の幅
#define TREASURE_SIZEY		(100 / 2)						// 宝の高さ

#define ENERGY_SIZEX		(40 / 2)						// エネルギーの幅
#define ENERGY_SIZEY		(50 / 2)						// エネルギーの高さ

#define MAX_PARTICLE		(100)							// パーティクル数
#define MAX_PARTICLE_SHORT	(20)							// 小さいパーティクル数

#define HIT_ITEM_SIZE		(10.0f)							// アイテムの当たり判定のサイズ拡張

// =====================================================================================================================================================================
//
// コンストラクタ
//
// =====================================================================================================================================================================
CItem::CItem() :CScene3D(PRIORITY_ITEM)
{
}

// =====================================================================================================================================================================
//
// デストラクタ
//
// =====================================================================================================================================================================
CItem::~CItem()
{
}

// =====================================================================================================================================================================
//
// 初期化処理
//
// =====================================================================================================================================================================
void CItem::Init()
{
	// 変数初期化
	m_pos			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 位置
	m_size			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// サイズ
	m_col			= D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		// 色
	m_ItemType		= ITEMTYPE::ITEMTYPE_NONE;					// アイテムの種類
	m_bHit			= false;									// ヒットフラグ

	// 初期化
	CScene3D::Init();
	//色の設定
	CScene3D::SetColor(m_col);
}

// =====================================================================================================================================================================
//
// 終了処理
//
// =====================================================================================================================================================================
void CItem::Uninit(void)
{
	CScene3D::Uninit();
}

// =====================================================================================================================================================================
//
// 更新処理
//
// =====================================================================================================================================================================
void CItem::Update(void)
{
	// プレイヤーの情報取得
	CPlayer *pPlayer = CManager::GetGame()->GetPlayer();

	// 位置の取得
	D3DXVECTOR3 pos = CScene3D::GetPos();

	// プレイヤーとの当たり判定
	if (CollisionPlayer() == true)
	{
		switch (m_ItemType)
		{
		case CItem::ITEMTYPE_SPEED:			// スピードアップ
			//	アイテム取得音
			CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_ITEM);
			// スコア加算
			CScore::AddScore(100);
			for (int nCnt = 0; nCnt < MAX_PARTICLE_SHORT; nCnt++)
			{
				// パーティクルの生成
				CParticle::Create(pos, CParticle::PARTICLE_BLUE);
			}
			break;

		case CItem::ITEMTYPE_DIAMOND:		// ダイヤ
			//	アイテム取得音
			CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_ITEM);
			// スコア加算
			CScore::AddScore(5000);
			for (int nCnt = 0; nCnt < MAX_PARTICLE_SHORT; nCnt++)
			{
				// パーティクルの生成
				CParticle::Create(pos, CParticle::PARTICLE_BLUE);
			}
			break;

		case CItem::ITEMTYPE_JEWEL:			// 宝石
			//	アイテム取得音
			CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_ITEM);
			// スコア加算
			CScore::AddScore(2000);
			for (int nCnt = 0; nCnt < MAX_PARTICLE_SHORT; nCnt++)
			{
				// パーティクルの生成
				CParticle::Create(pos, CParticle::PARTICLE_BLUE);
			}
			break;

		case CItem::ITEMTYPE_GOLD:			// 金貨
			//	アイテム取得音
			CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_ITEM);
			// スコア加算
			CScore::AddScore(300);
			for (int nCnt = 0; nCnt < MAX_PARTICLE_SHORT; nCnt++)
			{
				// パーティクルの生成
				CParticle::Create(pos, CParticle::PARTICLE_BLUE);
			}
			break;

		case CItem::ITEMTYPE_KEY:			// 鍵
			break;

		case CItem::ITEMTYPE_1UP:			// 1UP
			//	アイテム取得音
			CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_ITEM);
			// プレイヤーの残機アップ
			CManager::GetGame()->GetPlayer()->PlayerRecovery(1);
			for (int nCnt = 0; nCnt < MAX_PARTICLE_SHORT; nCnt++)
			{
				// パーティクルの生成
				CParticle::Create(pos, CParticle::PARTICLE_BLUE);
			}
			break;

		case CItem::ITEMTYPE_TREASURE:		// 財宝
			//	アイテム取得音
			CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_ITEM);
			// スコア加算
			CScore::AddScore(10000);
			for (int nCnt = 0; nCnt < MAX_PARTICLE_SHORT; nCnt++)
			{
				// パーティクルの生成
				CParticle::Create(pos, CParticle::PARTICLE_BLUE);
			}
			for (int nCnt = 0; nCnt < MAX_PARTICLE; nCnt++)
			{
				// パーティクルの生成
				CParticle::Create(pos, CParticle::PARTICLE_RED);
			}
			// ゲーム終了(クリア)
			CManager::GetGame()->SetGameMode(CGame::GAME_MODE_CLEAR);
			break;

		case CItem::ITEMTYPE_ENERGY:		// エネルギー
			// 当たっていないとき
			if (!m_bHit)
			{
				//	エネルギー回復音
				CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_HEAL);

				for (int nCnt = 0; nCnt < MAX_PARTICLE; nCnt++)
				{
					// パーティクルの生成
					CParticle::Create(pos, CParticle::PARTICLE_RED);
				}
				// 再開地点の設定
				pPlayer->SetRestartPos(pos);
			}
			// エネルギーゲージの回復
			CGameUI::RecoveryGage();
			break;
		}
		// 当たっている状態
		m_bHit = true;
	}
	else
	{
		// ヒットフラグを戻す
		m_bHit = false;
	}

	// 位置の設定
	CScene3D::SetPos(pos);

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
	LPDIRECT3DDEVICE9 pDevice = *CManager::GetRenderer()->GetDevice();	// デバイスの取得

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);						 // アルファテストを有効にする
	pDevice->SetRenderState(D3DRS_ALPHAREF, 30);								 // 基準値を指定する
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);					 // 基準値より大きいと描画する

	// 描画
	CScene3D::Draw();

	// アルファテストを無効にする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

// =====================================================================================================================================================================
//
// アイテムの生成
//
// =====================================================================================================================================================================
CItem * CItem::Create(D3DXVECTOR3 pos, ITEMTYPE type)
{
	// 変数
	CItem *pItem;

	// メモリの確保
	pItem = new CItem();

	// 初期化
	pItem->Init();

	// アイテムの位置の設定
	pItem->SetPos(pos);
	// アイテムの種類の設定
	pItem->m_ItemType = type;
	// ビルボードの設定
	pItem->SetBillboard(true);

	switch (type)
	{
	case CItem::ITEMTYPE_SPEED:			// スピードアップ

		pItem->m_size = D3DXVECTOR3(ITEM_SIZEX, ITEM_SIZEY, 0.0f);
		break;

	case CItem::ITEMTYPE_DIAMOND:		// ダイヤ

		pItem->m_size = D3DXVECTOR3(JUWEL_SIZEX, JUWEL_SIZEY, 0.0f);
		break;

	case CItem::ITEMTYPE_JEWEL:			// 宝石

		pItem->m_size = D3DXVECTOR3(JUWEL_SIZEX, JUWEL_SIZEY, 0.0f);
		break;

	case CItem::ITEMTYPE_GOLD:			// 金貨

		pItem->m_size = D3DXVECTOR3(JUWEL_SIZEX, JUWEL_SIZEY, 0.0f);
		break;

	case CItem::ITEMTYPE_KEY:			// 鍵

		pItem->m_size = D3DXVECTOR3(JUWEL_SIZEX, JUWEL_SIZEY, 0.0f);
		break;

	case CItem::ITEMTYPE_1UP:			// 1UP

		pItem->m_size = D3DXVECTOR3(JUWEL_SIZEX, JUWEL_SIZEY, 0.0f);
		break;

	case CItem::ITEMTYPE_TREASURE:		// 財宝

		pItem->m_size = D3DXVECTOR3(TREASURE_SIZEX, TREASURE_SIZEY, 0.0f);
		break;

	case CItem::ITEMTYPE_ENERGY:		// エネルギー

		pItem->m_size = D3DXVECTOR3(ENERGY_SIZEX, ENERGY_SIZEY, 0.0f);
		break;
	}

	// テクスチャの割り当て
	pItem->BindTexture(m_apTexture[type]);

	// サイズの設定
	pItem->SetSize(pItem->m_size);

	//// エフェクト生成
	//m_pEffect[m_nID] = CEffect::Create(pos, CEffect::EFFECTTYPE_ITEM);

	// インクリメント
	m_nID++;

	return pItem;
}

// =====================================================================================================================================================================
//
// ロード
//
// =====================================================================================================================================================================
HRESULT CItem::Load(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = *CManager::GetRenderer()->GetDevice();

	// テクスチャファイル名
	char *sTextureFileName[ITEMTYPE_MAX]
	{
		{ TEXTURE_FILE01 },		// ITEMTYPE_SPEED		( スピードアップ
		{ TEXTURE_FILE02 },		// ITEMTYPE_DIAMOND		( ダイヤ
		{ TEXTURE_FILE03 },		// ITEMTYPE_JEWEL		( 宝石
		{ TEXTURE_FILE04 },		// ITEMTYPE_GOLD		( 金貨
		{ TEXTURE_FILE05 },		// ITEMTYPE_KEY			( 鍵
		{ TEXTURE_FILE06 },		// ITEMTYPE_1UP			( 1UP
		{ TEXTURE_FILE07 },		// ITEMTYPE_TREASURE	( 財宝
		{ TEXTURE_FILE08 },		// ITEMTYPE_ENERGY		( エネルギー
	};

	for (int nCntItem = 0; nCntItem < ITEMTYPE_MAX; nCntItem++)
	{
		// テクスチャ読み込み
		D3DXCreateTextureFromFile(pDevice, sTextureFileName[nCntItem], &m_apTexture[nCntItem]);
	}

	return S_OK;
}

// =====================================================================================================================================================================
//  
// アンロード
//
// =====================================================================================================================================================================
void CItem::Unload(void)
{
	for (int nCntTex = 0; nCntTex < ITEMTYPE::ITEMTYPE_MAX; nCntTex++)
	{
		// テクスチャの開放
		if (m_apTexture[nCntTex] != NULL)
		{
			m_apTexture[nCntTex]->Release();
			m_apTexture[nCntTex] = NULL;
		}
	}
}

// =====================================================================================================================================================================
//  
// アイテムの種類の設定
//
// =====================================================================================================================================================================
void CItem::SetItemType(ITEMTYPE type)
{
	m_ItemType = type;

	// テクスチャの割り当て
	BindTexture(m_apTexture[type]);

	// サイズの設定
	SetSize(D3DXVECTOR3(m_size.x, m_size.y, m_size.z));
}

// =====================================================================================================================================================================
//  
// プレイヤーとの当たり判定
//
// =====================================================================================================================================================================
bool CItem::CollisionPlayer(void)
{
	bool bHit = false;		// ヒットフラグ

	CPlayer * pPlayer = CManager::GetGame()->GetPlayer();			// プレイヤーの取得

	if (pPlayer != NULL)
	{
		D3DXVECTOR3 posPlayer = pPlayer->GetPos();					// プレイヤーの位置取得
		D3DXVECTOR3 sizePlayer = pPlayer->GetSize();				// プレイヤーのサイズ取得
		D3DXVECTOR3 posItem = CScene3D::GetPos();					// アイテムの位置

		// ブロックの範囲 ( 横 )
		if (posItem.x - m_size.x - HIT_ITEM_SIZE< posPlayer.x + sizePlayer.x &&
			posItem.x + m_size.x + HIT_ITEM_SIZE> posPlayer.x - sizePlayer.x)
		{
			// ブロックの範囲 ( 縦 )
			if (posItem.z - m_size.z - HIT_ITEM_SIZE< posPlayer.z + sizePlayer.z &&
				posItem.z + m_size.z + HIT_ITEM_SIZE> posPlayer.z - sizePlayer.z)
			{
				// ブロックの範囲 ( 高さ )
				if (posItem.y - m_size.y - HIT_ITEM_SIZE <= posPlayer.y + sizePlayer.y &&
					posItem.y + m_size.y + HIT_ITEM_SIZE> posPlayer.y)
				{
					// エネルギーじゃないとき
					if (m_ItemType != ITEMTYPE_ENERGY)
					{
						// リリース
						Release();
					}
					// 当たったとき
					bHit = true;
				}
			}
		}
	}
	return bHit;
}