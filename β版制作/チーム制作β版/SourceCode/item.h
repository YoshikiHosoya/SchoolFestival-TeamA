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

// =====================================================================================================================================================================
// アイテムのデータ
// =====================================================================================================================================================================
typedef struct
{
	int					nDropRate;		// アイテムのドロップ率
	int					nDeleteTime;	// 点滅するまでの時間
	int					nFlashTime;		// 点滅する時間
	int					nBearScore;		// 熊のアイテムを取った時のスコアの値
	int					nCoinScore;		// コインのアイテムを取った時のスコアの値
	int					nJewelryScore;	// 宝石のアイテムを取った時のスコアの値
	int					nMedalScore;	// メダルのアイテムを取った時のスコアの値
	D3DXVECTOR3			CollisionSize;	// 当たり判定のサイズ
}ITEM_DATA;

// =====================================================================================================================================================================
// 前方宣言
// =====================================================================================================================================================================
class CCollision;

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

	// アイテムの用途
	enum ITEMDROP
	{
		ITEMDROP_NONE = -1,			// ドロップしない
		ITEMDROP_WEAPON,			// 武器強化
		ITEMDROP_SCORE,				// スコアアップ
		ITEMDROP_CHARGE,			// 弾薬など
		ITEMDROP_ALL,				// 全て
	};

	// アイテムのドロップ形式
	enum ITEMDROP_PATTERN
	{
		ITEMDROP_PATTERN_NONE = -1,	// 何もしない
		ITEMDROP_PATTERN_DESIGNATE,	// 指定してドロップさせる
		ITEMDROP_PATTERN_RANDOM,	// ランダムでドロップさせる
	};

	/* 関数 */
	CItem(OBJ_TYPE type);														// コンストラクタ
	~CItem();																	// デストラクタ

	/* メンバ関数 */
	HRESULT						Init();											// 初期化
	void						Uninit();										// 終了
	void						Update();										// 更新
	void						Draw();											// 描画
	void						ItemType(ITEMTYPE type);						// アイテム取得時の種類別処理
	void						DebugInfo();									// デバッグ
	void						HitItem(ITEMTYPE type);							// アイテム取得時の種類別処理
	ITEMTYPE					GetItemType() { return m_Type; };				// アイテムタイプの取得
	CCollision					*GetCollision() { return m_pCollision; };		// 当たり判定
	void						SetDropPos(D3DXVECTOR3 &characterpos);			// アイテムを生成位置を設定
	void						RemainTimer();									// 滞在時間を計算し0になったら削除する
	void						Flashing();										// 点滅処理

	/* 静的メンバ関数 */
	static	CItem				*DropCreate(
		D3DXVECTOR3 pos,
		ITEMDROP drop,
		ITEMDROP_PATTERN pattern,
		ITEMTYPE type);															// キャラクターがアイテムを落とす時の生成
	static	void				SwitchTexture(ITEMTYPE type, CItem *pItem);		// 種類別テクスチャ設定
	static	bool				DropRate();										// アイテムをドロップする確率
	static	int					ItemRand(int max);								// ランダムに値を返す
	static	void				ItemLoad();										// アイテムのロード
	static	void				SetItemData();									// アイテムのデータ設定
	static  void				DebugItemCommand(CKeyboard *key);				// デバッグ用アイテムコマンド

	/* メンバ関数 */
	ITEMTYPE					RandDropItem(ITEMDROP drop);					// アイテムの種類をランダムに計算
	ITEMTYPE					RandomRange(ITEMTYPE min, ITEMTYPE max);		// ランダムの範囲選択
	void						DropPattern(
		ITEMDROP_PATTERN pattern,
		ITEMDROP drop,
		ITEMTYPE type);															// アイテムのドロップパターン

protected:
private:
	/* 静的メンバ関数 */
	static CItem				*DebugCreate(ITEMTYPE type);					// デバッグ用アイテム生成
	/* 静的メンバ変数 */
	static char					*m_ItemFileName;								// アイテムのファイル名
	static ITEM_DATA			m_ItemData;										// アイテムのデータ
	static int					m_nDropRate;									// ドロップ率
	static int					m_nDeleteTime;									// アイテムが点滅するまでの時間
	static int					m_nFlashTime;									// アイテムが点滅する時間
	static int					m_nBearScore;									// 熊のアイテムのスコア
	static int					m_nCoinScore;									// コインのアイテムのスコア
	static int					m_nJewelryScore;								// 宝石のアイテムのスコア
	static int					m_nMedalScore;									// メダルのアイテムのスコア
	static D3DXVECTOR3			m_CollisionSize;								// 当たり判定の大きさ

	/* メンバ関数 */
	uint64_t	get_rand_range(uint64_t min_val, uint64_t max_val);				// ランダム関数 範囲
	void		AddCoinScore(int &nScore);										// コインのスコアの加算

	/* メンバ変数 */
	ITEMTYPE					m_Type;											// アイテムタイプ
	ITEMDROP					m_Drop;											// アイテムをドロップさせる時の種類
	D3DXMATRIX					m_mtxWorld;										// ワールドマトリックス
	CCollision					*m_pCollision;									// 当たり判定
	int							m_nRemainTime;									// アイテムがマップに残る時間
	int							m_nColCnt;										// αカラーカウント
};
#endif