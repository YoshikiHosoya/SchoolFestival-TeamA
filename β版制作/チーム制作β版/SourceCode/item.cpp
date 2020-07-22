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
#include <random>
#include "inputKeyboard.h"

// =====================================================================================================================================================================
// 静的メンバ変数の初期化
// =====================================================================================================================================================================
ITEM_DATA	CItem::m_ItemData		 = {};
int			CItem::m_nDropRate		 = 0;
int			CItem::m_nDeleteTime	 = 0;
int			CItem::m_nFlashTime		 = 0;
int			CItem::m_nBearScore		 = 0;
int			CItem::m_nCoinScore		 = 0;
int			CItem::m_nJewelryScore	 = 0;
int			CItem::m_nMedalScore	 = 0;
D3DXVECTOR3 CItem::m_CollisionSize	 = D3DXVECTOR3(0,0,0);
int			CItem::m_nAddCnt		 = 0;
// =====================================================================================================================================================================
// テキストファイル名
// =====================================================================================================================================================================
char *CItem::m_ItemFileName =
{
	"data/Load/Item/ItemData.txt" 			// アイテムの情報
};

// =====================================================================================================================================================================
// マクロ定義
// =====================================================================================================================================================================

// =====================================================================================================================================================================
//
// コンストラクタ
//
// =====================================================================================================================================================================
CItem::CItem(OBJ_TYPE type) :CScene3D(type)
{
	// 当たり判定のポインタ
	m_pCollision = nullptr;

	// アイテムがマップに残る時間
	m_nRemainTime = m_nDeleteTime;

	// αカラーカウント
	m_nColCnt = 0;

	// アイテムの種類
	m_Type = ITEMTYPE_HEAVYMACHINEGUN;

	// アイテムをドロップさせる種類
	m_Drop = ITEMDROP_WEAPON;
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
	// 初期化
	CScene3D::Init();

	// 当たり判定生成
	m_pCollision = CCollision::Create();
	m_pCollision->SetPos(&GetPosition());
	m_pCollision->SetSize2D(m_CollisionSize);
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
	// プレイヤーのポインタを取得
	CPlayer *pPlayer = CManager::GetBaseMode()->GetPlayer();

	// アイテムの種類ごとの処理
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

		// 熊
	case (ITEMTYPE_BEAR): {
		// スコアアップ
		pPlayer->GetPlayerUI()->SetScore(m_nBearScore);
	}break;

		// コイン
	case (ITEMTYPE_COIN): {
		// コインを取るたびにコインのスコアアップ
		pPlayer->GetPlayerUI()->SetScore(AddCoinScore(m_nCoinScore));
	}break;
		// 宝石
	case (ITEMTYPE_JEWELRY): {
		// スコアアップ
		pPlayer->GetPlayerUI()->SetScore(m_nJewelryScore);
	}break;
		// メダル
	case (ITEMTYPE_MEDAL): {
		// スコアアップ
		pPlayer->GetPlayerUI()->SetScore(m_nMedalScore);
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
		// 点滅させる
		Flashing();
	}
}

// =====================================================================================================================================================================
//
// 点滅処理
//
// =====================================================================================================================================================================
void CItem::Flashing()
{
	// カウント加算
	m_nColCnt++;
	// 余りが0の時透明にする
	if (m_nColCnt % 30 == 0)
	{
		this->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	}
	// 余りが0の時通常状態にする
	else if(m_nColCnt % 15 == 0)
	{
		this->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	// 3秒以上経過したらアイテムを削除する
	if (m_nColCnt >= m_nFlashTime)
	{
		// 変数の初期化
		m_nColCnt = 0;
		// 削除
		Rerease();
	}
}

// =====================================================================================================================================================================
//
// アイテムの情報の設定
//
// =====================================================================================================================================================================
void CItem::SetItemData()
{
	// ドロップ率の設定
	m_nDropRate		 = m_ItemData.nDropRate;
	// アイテムが点滅するまでの時間
	m_nDeleteTime	 = m_ItemData.nDeleteTime;
	// アイテムが点滅する時間
	m_nFlashTime	 = m_ItemData.nFlashTime;
	// 熊のアイテムのスコア
	m_nBearScore	 = m_ItemData.nBearScore;
	// コインのアイテムのスコア
	m_nCoinScore	 = m_ItemData.nCoinScore;
	// 宝石のアイテムのスコア
	m_nJewelryScore	 = m_ItemData.nJewelryScore;
	// メダルのアイテムのスコア
	m_nMedalScore	 = m_ItemData.nMedalScore;
	// 当たり判定の大きさ
	m_CollisionSize	 = m_ItemData.CollisionSize;
}

// =====================================================================================================================================================================
//
// ランダム生成
//
// =====================================================================================================================================================================
uint64_t CItem::get_rand_range(uint64_t min_val, uint64_t max_val)
{
	// メルセンヌ・ツイスター法による擬似乱数生成器を、
	// ハードウェア乱数をシードにして初期化
	std::random_device seed_gen;
	std::mt19937 engine(seed_gen());

	// 乱数生成器
	static std::mt19937_64 mt64(seed_gen());

	// [min_val, max_val] の一様分布整数 (int) の分布生成器
	std::uniform_int_distribution<uint64_t> get_rand_uni_int(min_val, max_val);

	// 乱数を生成
	return get_rand_uni_int(mt64);
	// 乱数を生成
	//return get_rand_uni_int(engine);
}

// =====================================================================================================================================================================
//
// コインのスコアを加算する処理
//
// =====================================================================================================================================================================
int CItem::AddCoinScore(int nScore)
{
	// コインを取得するごとにコインのスコアを倍にする
	for (int nAdd = 0; nAdd < m_nAddCnt;nAdd++)
	{
		// 一回目は処理しない
		if (m_nAddCnt == 0)
		{
			// スキップ
			continue;
		}

		// スコアの値を倍にする
		nScore += nScore;
	}

	// カウント加算
	m_nAddCnt++;

	// スコアの値を返す
	return nScore;
}

// =====================================================================================================================================================================
//
// ランダム　範囲指定
//
// =====================================================================================================================================================================
CItem::ITEMTYPE CItem::RandomRange(ITEMTYPE min, ITEMTYPE max)
{
	// 範囲でランダムに値を求め値を返す
	//return (ITEMTYPE)(min + (int)(rand()*(max - min + 1.0) / (1.0 + RAND_MAX)));

	//return (ITEMTYPE)(min + (int)(rand()*(max - min) / (RAND_MAX)));

	return (ITEMTYPE)get_rand_range(min, max);
}

// =====================================================================================================================================================================
//
// アイテムをドロップする時のパターン
//
// =====================================================================================================================================================================
void CItem::DropPattern(ITEMDROP_PATTERN pattern , ITEMDROP drop, ITEMTYPE type)
{
	// 条件ごとにドロップさせる条件を変える
	switch (pattern)
	{
		// ドロップするアイテムを指定する
	case CItem::ITEMDROP_PATTERN_DESIGNATE:
		m_Type = type;
		break;

		// ドロップするアイテムをランダムにする
	case CItem::ITEMDROP_PATTERN_RANDOM:
		// アイテムのタイプをランダムに設定
		m_Type = RandDropItem(drop);
		break;
	default:
		break;
	}
}

// =====================================================================================================================================================================
//
// デバッグ用アイテムコマンド
//
// =====================================================================================================================================================================
void CItem::DebugItemCommand(CKeyboard *key)
{
	//使い方説明
	CDebugProc::Print("\n---------Debug ItemCommand----------\n");

	CDebugProc::Print("[LShift] + テンキー [0] : ヘビーマシンガン\n");
	CDebugProc::Print("[LShift] + テンキー [1] : ショットガン\n");
	CDebugProc::Print("[LShift] + テンキー [2] : レーザーガン\n");
	CDebugProc::Print("[LShift] + テンキー [3] : ロケットランチャー\n");
	CDebugProc::Print("[LShift] + テンキー [4] : フレイムショット\n");
	CDebugProc::Print("[LShift] + テンキー [5] : 熊\n");
	CDebugProc::Print("[LShift] + テンキー [6] : コイン\n");
	CDebugProc::Print("[LShift] + テンキー [7] : 宝石\n");
	CDebugProc::Print("[LShift] + テンキー [8] : メダル\n");
	CDebugProc::Print("[LShift] + テンキー [9] : BomUp\n");
	CDebugProc::Print("[LShift] + テンキー [-] : ガソリン\n");
	CDebugProc::Print("[LShift] + テンキー [+] : BulletUp\n");

	//LShift押しながら
	if (key->GetKeyboardPress(DIK_LSHIFT))
	{
		// ヘビーマシンガンの生成
		if (key->GetKeyboardTrigger(DIK_NUMPAD0))
		{
			CItem::DebugCreate(ITEMTYPE_HEAVYMACHINEGUN);
		}
		// ショットガン生成
		else if (key->GetKeyboardTrigger(DIK_NUMPAD1))
		{
			CItem::DebugCreate(ITEMTYPE_SHOTGUN);
		}
		// レーザーガン生成
		else if (key->GetKeyboardTrigger(DIK_NUMPAD2))
		{
			CItem::DebugCreate(ITEMTYPE_LASERGUN);
		}
		// ロケットランチャー生成
		else if (key->GetKeyboardTrigger(DIK_NUMPAD3))
		{
			CItem::DebugCreate(ITEMTYPE_ROCKETLAUNCHER);
		}
		// フレイムショット生成
		else if (key->GetKeyboardTrigger(DIK_NUMPAD4))
		{
			CItem::DebugCreate(ITEMTYPE_FLAMESHOT);
		}
		// 熊の生成
		else 	if (key->GetKeyboardTrigger(DIK_NUMPAD5))
		{
			CItem::DebugCreate(ITEMTYPE_BEAR);
		}
		// コインの生成
		else 	if (key->GetKeyboardTrigger(DIK_NUMPAD6))
		{
			CItem::DebugCreate(ITEMTYPE_COIN);
		}
		// 宝石の生成
		else 	if (key->GetKeyboardTrigger(DIK_NUMPAD7))
		{
			CItem::DebugCreate(ITEMTYPE_JEWELRY);
		}
		// メダルの生成
		else 	if (key->GetKeyboardTrigger(DIK_NUMPAD8))
		{
			CItem::DebugCreate(ITEMTYPE_MEDAL);
		}
		// BomUp生成
		else if (key->GetKeyboardTrigger(DIK_NUMPAD9))
		{
			CItem::DebugCreate(ITEMTYPE_BOMBUP);
		}
		// ガソリン生成
		else if (key->GetKeyboardTrigger(DIK_NUMPADMINUS))
		{
			CItem::DebugCreate(ITEMTYPE_ENERGYUP);
		}
		// BulletUp生成
		else if (key->GetKeyboardTrigger(DIK_NUMPADPLUS))
		{
			CItem::DebugCreate(ITEMTYPE_BULLETUP);
		}
	}
}

// =====================================================================================================================================================================
//
// 静的変数の初期化 game終了時
//
// =====================================================================================================================================================================
void CItem::InitVariable()
{
	// コインのカウント加算用変数の初期化
	m_nAddCnt = 0;
}

// =====================================================================================================================================================================
//
// デバッグ用アイテム生成
//
// =====================================================================================================================================================================
CItem * CItem::DebugCreate(ITEMTYPE type)
{
	// 変数
	CItem *pItem;

	// メモリの確保
	pItem = new CItem(OBJTYPE_ITEM);

	// 初期化
	pItem->Init();

	// サイズの設定
	pItem->SetSize(D3DXVECTOR3(
		m_CollisionSize.x / 2,
		m_CollisionSize.y / 2,
		m_CollisionSize.z / 2));


	CPlayer *pPlayer = CManager::GetBaseMode()->GetPlayer();

	if (pPlayer != nullptr)
	{
		D3DXVECTOR3 pos = pPlayer->GetPosition();
		// アイテムが生成される位置の調整
		pItem->SetDropPos(pos);

		// アイテムの位置の設定
		pItem->SetPosition(pos);

		pItem->m_Type = type;
	}

	// 種類別にテクスチャを設定
	pItem->SwitchTexture(pItem->m_Type, pItem);

	return pItem;
}

// =====================================================================================================================================================================
//
// ランダム関数
//
// =====================================================================================================================================================================
int CItem::ItemRand(int max)
{
	// 基準を求める
	int nAdjusted_max = (RAND_MAX + 1) - (RAND_MAX + 1) % max;

	// ランダムに求めた値を格納する比較用変数
	int nRandom = 0;

	// RAND_MAX + 1 が max で割り切れない場合、乱数がその端数分の範囲になったら捨ててやり直す
	do {
		// ランダムに値を求める
		nRandom = rand();
	} while (nRandom >= nAdjusted_max);

	// 値を返す
	return (int)(((float)nRandom / nAdjusted_max) * max);
}

// =====================================================================================================================================================================
//
// アイテムのデータの読み込み
//
// =====================================================================================================================================================================
void CItem::ItemLoad()
{
	// ファイルポイント
	FILE *pFile;

	char cReadText[128];			// 文字として読み取る
	char cHeadText[128];			// 比較用
	char cDie[128];					// 不要な文字

	// ファイルを開く
	pFile = fopen(m_ItemFileName, "r");

	// 開いているとき
	if (pFile != NULL)
	{
		// SCRIPTが来るまでループ
		while (strcmp(cHeadText, "SCRIPT") != 0)
		{
			fgets(cReadText, sizeof(cReadText), pFile); // 一文読み込み
			sscanf(cReadText, "%s", &cHeadText);		// 比較用テキストに文字を代入
		}

		// SCRIPTが来たら
		if (strcmp(cHeadText, "SCRIPT") == 0)
		{
			// END_SCRIPTが来るまでループ
			while (strcmp(cHeadText, "END_SCRIPT") != 0)
			{
				fgets(cReadText, sizeof(cReadText), pFile); // 一文読み込み
				sscanf(cReadText, "%s", &cHeadText);		// 比較用テキストに文字を代入

															// ITEMSETが来たら
				if (strcmp(cHeadText, "ITEMSET") == 0)
				{
					// END_ITEMSETが来るまでループ
					while (strcmp(cHeadText, "END_ITEMSET") != 0)
					{
						fgets(cReadText, sizeof(cReadText), pFile); // 一文読み込み
						sscanf(cReadText, "%s", &cHeadText);		// 比較用テキストに文字を代入

																	// SPEEDが来たら
						if (strcmp(cHeadText, "RATE") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_ItemData.nDropRate);		// 比較用テキストにRATEを代入
						}
						// LIFEが来たら
						else if (strcmp(cHeadText, "DELETE") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_ItemData.nDeleteTime);	// 比較用テキストにDELETEを代入
						}
						// FLASHが来たら
						else if (strcmp(cHeadText, "FLASH") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_ItemData.nFlashTime);	// 比較用テキストにFLASHを代入
						}
						// BEARが来たら
						else if (strcmp(cHeadText, "BEAR") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_ItemData.nBearScore);	// 比較用テキストにBEARを代入
						}
						// BEARが来たら
						else if (strcmp(cHeadText, "COIN") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_ItemData.nCoinScore);	// 比較用テキストにCOINを代入
						}
						// BEARが来たら
						else if (strcmp(cHeadText, "JEWELRY") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_ItemData.nJewelryScore);	// 比較用テキストにJEWELRYを代入
						}
						// BEARが来たら
						else if (strcmp(cHeadText, "MEDAL") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_ItemData.nMedalScore);	// 比較用テキストにMEDALを代入
						}
						// COLLISIONSIZEが来たら
						else if (strcmp(cHeadText, "COLLISIONSIZE") == 0)
						{
							sscanf(cReadText, "%s %s %f %f %f", &cDie, &cDie,
								&m_ItemData.CollisionSize.x,
								&m_ItemData.CollisionSize.y,
								&m_ItemData.CollisionSize.z);										// 比較用テキストにCOLLISIONSIZEを代入
						}
						else if (strcmp(cHeadText, "END_ITEMSET") == 0)
						{
						}
					}
				}
			}
		}
		// ファイルを閉じる
		fclose(pFile);
	}
	else
	{
		MessageBox(NULL, "アイテムのデータ読み込み失敗", "警告", MB_ICONWARNING);
	}

	// 読み込んだ情報の代入
	SetItemData();
}

// =====================================================================================================================================================================
//
// キャラクターがアイテムを落とすときの生成処理
//
// =====================================================================================================================================================================
CItem * CItem::DropCreate(D3DXVECTOR3 pos, ITEMDROP drop , ITEMDROP_PATTERN pattern ,ITEMTYPE type)
{
	// 変数
	CItem *pItem;

	// メモリの確保
	pItem = new CItem(OBJTYPE_ITEM);

	// 初期化
	pItem->Init();

	// サイズの設定
	pItem->SetSize(D3DXVECTOR3(
		m_CollisionSize.x /2,
		m_CollisionSize.y /2,
		m_CollisionSize.z /2));

	// アイテムが生成される位置の調整
	pItem->SetDropPos(pos);

	// アイテムの位置の設定
	pItem->SetPosition(pos);

	// アイテムのドロップをパターンごとに変える
	pItem->DropPattern(pattern, drop, type);

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
		//コイン
	case (ITEMTYPE_COIN): {
		// テクスチャの割り当て
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_COIN));
	}break;
		//宝石
	case (ITEMTYPE_JEWELRY): {
		// テクスチャの割り当て
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_JEWELRY));
	}break;
		//メダル
	case (ITEMTYPE_MEDAL): {
		// テクスチャの割り当て
		pItem->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_ITEM_MEDAL));
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
CItem::ITEMTYPE CItem::RandDropItem(ITEMDROP drop)
{
	// 値を返すための変数
	ITEMTYPE type;
	// 条件によってドロップさせるアイテムの種類に制限をかける
	switch (drop)
	{
		// 武器のみの場合
	case CItem::ITEMDROP_WEAPON:
		// ランダムの範囲を武器のみに選択
		type = RandomRange(ITEMTYPE_HEAVYMACHINEGUN, ITEMTYPE_FLAMESHOT);
		break;

		// スコアアップのみの場合
	case CItem::ITEMDROP_SCORE:
		// ランダムの範囲をスコアアイテムのみに選択
		type = RandomRange(ITEMTYPE_BEAR, ITEMTYPE_MEDAL);
		break;

		// 弾薬などのみの場合
	case CItem::ITEMDROP_CHARGE:
		// ランダムの範囲をスコアアイテムのみに選択
		type = RandomRange(ITEMTYPE_BOMBUP, ITEMTYPE_BULLETUP);
		break;

		// 全てのアイテム
	case CItem::ITEMDROP_ALL:
		type = (ITEMTYPE)ItemRand(ITEMTYPE_MAX);
		break;
	default:
		break;
	}

	return type;
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
	int nRate = m_nDropRate;

	// ランダムにドロップするかを求める
	nDrop = ItemRand(nRate);

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
