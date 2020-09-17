// =====================================================================================================================================================================
//
// アイテム処理の説明[item.h]
// Author : Fujiwara Masato
//
// =====================================================================================================================================================================
#ifndef _ITEM_H_
#define _ITEM_H_	 // ファイル名を基準を決める

// =====================================================================================================================================================================
// インクルードファイル
// =====================================================================================================================================================================
#include "scene3D.h"

// =====================================================================================================================================================================
// マクロ定義
// =====================================================================================================================================================================
#define ITEM_FILE_NUM (2)
// =====================================================================================================================================================================
// アイテムのデータ
// =====================================================================================================================================================================
struct ITEM_DATA
{
	int					nDropRate;		// アイテムのドロップ率
	int					nDeleteTime;	// 点滅するまでの時間
	int					nFlashTime;		// 点滅する時間
	D3DXVECTOR3			CollisionSize;	// 当たり判定のサイズ
	unsigned int		Rarity[12];		// 全アイテムのレアリティ[★1から★3まで]
};
// =====================================================================================================================================================================
// アイテムガチャのデータ
// =====================================================================================================================================================================
struct ITEM_GACHA
{
	unsigned int BoxRand_TotalNum;					// ボックス乱数の母数
	unsigned int BoxRandDefault_RarityNum[3];		// ボックス乱数のデフォルトのレアリティの数
};
// =====================================================================================================================================================================
// 前方宣言
// =====================================================================================================================================================================
class CCollision;
class CPlayer;

// =====================================================================================================================================================================
// アイテムクラス
// =====================================================================================================================================================================
class CItem : public CScene3D
{
public:
	/* 列挙型 */
	// 種類
	enum ITEMTYPE
	{
		ITEMTYPE_NONE = -1,			// 未選択
		// ------ 武器 ------ //
		ITEMTYPE_HEAVYMACHINEGUN,	// ヘビーマシンガン
		ITEMTYPE_SHOTGUN,			// ショットガン
		ITEMTYPE_LASERGUN,			// レーザーガン
		ITEMTYPE_ROCKETLAUNCHER,	// ロケットランチャー
		ITEMTYPE_FLAMESHOT,			// フレイムショット

		// ------ スコア ------ //
		ITEMTYPE_BEAR,				// 熊
		ITEMTYPE_COIN,				// コイン
		ITEMTYPE_JEWELRY,			// 宝石
		ITEMTYPE_MEDAL,				// メダル

		// ------ チャージ ------ //
		ITEMTYPE_BOMBUP,			// 爆弾の数を増やす
		ITEMTYPE_ENERGYUP,			// 乗り物の耐久値を回復する
		ITEMTYPE_BULLETUP,			// ハンドガン以外の弾の残弾数を増やす

		ITEMTYPE_MAX
	};

	// アイテムの範囲
	enum ITEMDROP
	{
		ITEMDROP_NONE = -1,			// ドロップしない
		ITEMDROP_WEAPON,			// 武器系
		ITEMDROP_SCORE,				// スコアアップ
		ITEMDROP_CHARGE,			// 弾薬など
		ITEMDROP_WEA_SCO,			// 武器強化とスコアアップ
		ITEMDROP_ALL,				// 全て
	};

	// アイテムのドロップ形式
	enum ITEMDROP_PATTERN
	{
		ITEMDROP_PATTERN_NONE = -1,	// 何もしない
		ITEMDROP_PATTERN_DESIGNATE,	// 指定してドロップさせる
		ITEMDROP_PATTERN_RANDOM,	// ランダムでドロップさせる
	};

	// アイテムのレアリティ_星が多いほどレアリティが高い
	enum ITEM_RARITY
	{
		ITEM_RARITY_STAR_1,	// ★
		ITEM_RARITY_STAR_2,	// ★★
		ITEM_RARITY_STAR_3,	// ★★★
		ITEM_RARITY_TOTAL	// 総数
	};

	/* 関数 */
	CItem(OBJ_TYPE type);														// コンストラクタ
	~CItem();																	// デストラクタ

	/* メンバ関数 */
	HRESULT						Init();											// 初期化
	void						Uninit();										// 終了
	void						Update();										// 更新
	void						Draw();											// 描画
	void						DebugInfo();									// デバッグ

	void						ItemAcquisition(ITEMTYPE type, TAG Tag);		// アイテム取得時の種類別処理
	void						HitItem(ITEMTYPE type, TAG Tag);				// アイテム取得時の種類別処理
	void						RemainTimer();									// 滞在時間を計算し0になったら削除する
	void						Flashing();										// 点滅処理

	ITEMTYPE					GetItemType() { return m_Type; };				// アイテムタイプの取得
	CCollision					*GetCollision() { return m_pCollision; };		// 当たり判定
	void						SetDropPos(D3DXVECTOR3 &characterpos);			// アイテムを生成位置を設定

	/* 静的メンバ関数 */
	static	CItem				*DropItem(
		D3DXVECTOR3 pos,
		ITEMDROP drop,
		ITEMDROP_PATTERN pattern,
		ITEMTYPE type);															// キャラクターがアイテムを落とす時の生成


	static	CItem				*DropCreate_TEST();								// テスト用クリエイト処理


	static	void				SwitchTexture(ITEMTYPE type, CItem *pItem);		// 種類別テクスチャ設定
	static	bool				DropRate();										// アイテムをドロップさせるかのフラグを返す
	static	bool				DecideIfItemDrop(int nRate);					// ドロップ率を元にアイテムがドロップするかを決めて結果を返す
	static	uint64_t			GetRandRange(uint64_t min_val, uint64_t max_val);// ランダム関数 範囲

	static	void				InitVariable();									// 静的変数の初期化
	static	void				ItemLoad();										// アイテムの情報の読み込み
	static  void				DebugItemCommand(CKeyboard *key);				// デバッグ用アイテムコマンド

	/* メンバ関数 */
	ITEMTYPE					RandDropItem(ITEMDROP drop);						// アイテムの種類をランダムに計算
	ITEMTYPE					ItemRandomRange(ITEMTYPE min, ITEMTYPE max);		// ランダムの範囲選択
	ITEM_RARITY					RarityRandomRange(ITEM_RARITY min, ITEM_RARITY max);// ランダムの範囲選択

	void						DropPattern(
		ITEMDROP_PATTERN pattern,
		ITEMDROP drop,
		ITEMTYPE type);															// アイテムのドロップパターン

protected:
private:
	/* 静的メンバ関数 */
	static CItem				*DebugCreate(ITEMTYPE type);					// デバッグ用アイテム生成
	static void					SetRarityList();								// レアリティの生成
	static ITEMTYPE				ItemWhichOnePick(std::vector<std::vector<CItem::ITEMTYPE>> list,int line);	// リストの中から1つを選ぶ

	/* 静的メンバ変数 */
	static char					*m_ItemFileName;								// アイテムのファイル名

	static ITEM_DATA			m_ItemData;										// アイテムのデータ
	static ITEM_GACHA			m_ItemGachaData;								// アイテムガチャのデータ
	static int					m_nAddCoin;										// コインの加算用

	// --- アイテムガチャ --- //
	static std::vector<unsigned int>	m_nSaveHitItem;							// 完全乱数でアイテムをドロップさせた時の結果を保存
	static std::vector<ITEM_RARITY>		m_nBoxRandRarityDataList;				// ボックス乱数で使うアイテムのレアリティの一覧を保存

	static std::vector<ITEM_RARITY>		m_nDefaultRarityList;					// 取得した★から★★★の情報をまとめて保存する
	static std::vector<std::vector<ITEMTYPE>> m_nBoxRandDefaultRarityData;		// デフォルトのボックス乱数用のレアリティごとのアイテムの種類

	/* メンバ関数 */
	int							AddCoinScore(int nScore);						// コインのスコアを計算し結果を返す

	ITEMTYPE					FullRand();										// 完全乱数 // 未完成
	ITEMTYPE					BoxRand();										// ボックス乱数

	void						SetBoxRandDataList();							// ボックス乱数の母数が0以下になった時内容をリセットする
	static void					AddBoxRandList();								// アイテムのレアリティと母数を元にランダムなリストを生成する

	/* メンバ変数 */
	CCollision					*m_pCollision;									// 当たり判定
	CPlayer						*m_pPlayer[MAX_CONTROLLER];						// プレイヤーのポインタ

	ITEMTYPE					m_Type;											// アイテムタイプ
	ITEMDROP					m_Drop;											// アイテムをドロップさせる時の種類
	int							m_nRemainTime;									// アイテムがマップに残る時間
	int							m_nColCnt;										// αカラーカウント
};
#endif