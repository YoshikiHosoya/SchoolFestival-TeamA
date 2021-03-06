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
#include "scene.h"

// =====================================================================================================================================================================
// マクロ定義
// =====================================================================================================================================================================
#define ITEM_FILE_NUM (2)
#define MULTIPLE_ITEM_NUM (5)// まとめて生成する際の数

// =====================================================================================================================================================================
// アイテムのデータ 共通の情報
// =====================================================================================================================================================================
struct ITEM_DATA
{
	int					nDropRate;		// アイテムのドロップ率
	int					nDeleteTime;	// 点滅するまでの時間
	int					nFlashTime;		// 点滅する時間
	D3DXVECTOR3			CollisionSize;	// 当たり判定のサイズ
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
class CItem
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
		ITEMTYPE_GOLDCOIN,			// 金貨
		ITEMTYPE_SILVERCOIN,		// 銀貨
		ITEMTYPE_BRONZESCOIN,		// 銅貨
		ITEMTYPE_DIAMOND,			// ダイアモンド
		ITEMTYPE_BEAR,				// 熊
		ITEMTYPE_LETTER,			// 手紙
		ITEMTYPE_APPLE,				// リンゴ
		ITEMTYPE_MELON,				// メロン
		ITEMTYPE_BANANA,			// バナナ
		ITEMTYPE_MEAT,				// 肉
		ITEMTYPE_RICEBALL,			// おにぎり
		ITEMTYPE_CANDY,				// 飴
		ITEMTYPE_DONUT,				// ドーナツ
		ITEMTYPE_LOLIPOP,			// ロリポップ
		ITEMTYPE_BREAD,				// パン
		ITEMTYPE_CHOCOLATE,			// チョコレート
		ITEMTYPE_ICE,				// アイス

		// ------ チャージ ------ //
		ITEMTYPE_BOMBUP,			// 爆弾の数を増やす
		ITEMTYPE_BULLETUP,			// ハンドガン以外の弾の残弾数を増やす

		// ------ アニメーションするアイテム ------ //
		// ------ スコア ------ //
		ANIM_ITEMTYPE_ROASTCHICKEN,	// ローストチキン
		ANIM_ITEMTYPE_FISH,			// 魚
		ANIM_ITEMTYPE_BEAR,			// 熊
		ANIM_ITEMTYPE_DOLL,			// 人形
		ANIM_ITEMTYPE_LETTER,		// 手紙

		ANIM_ITEMTYPE_MEDAL,		// メダル
		ANIM_ITEMTYPE_MEDAL2,		// メダル2

		ANIM_ITEMTYPE_COIN,			// コイン
		ANIM_ITEMTYPE_RUBY,			// ルビー
		ANIM_ITEMTYPE_SAPPHIRE,		// サファイア
		ANIM_ITEMTYPE_TOPAZ,		// トパーズ
		// ------ チャージ ------ //
		ANIM_ITEMTYPE_PRISONER,		// 捕虜 残機アップ

		ANIM_ITEMTYPE_DANCEMONKEY,	// 踊るサル
		ANIM_ITEMTYPE_JUMPMONKEY,	// 飛ぶサル

		ITEMTYPE_MAX				// 最大
	};

	// アイテムの範囲
	enum ITEMDROP
	{
		ITEMDROP_NONE = -1,			// ドロップしない
		ITEMDROP_WEAPON,			// 武器系
		ITEMDROP_SCORE,				// スコア系
		ITEMDROP_CHARGE,			// 弾薬系

		ITEMDROP_SCO_CHA,			// 弾薬とスコアアップ

		ITEMDROP_FRUIT,				// スコアアップ_フルーツ
		ITEMDROP_COIN,				// スコアアップ_コイン
		ITEMDROP_RARE,				// スコアアップ_レア
		ITEMDROP_FOOD,				// 食べ物
		ITEMDROP_ALL,				// 全て

		ITEMDROP_ANI_NORMAL,		// アニメーションするアイテム
		ITEMDROP_ANI_RARE,			// アニメーションするアイテム
		ITEMDROP_ANI_MONKEY,		// サル
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

	// アイテムがドロップする時の挙動
	enum ITEM_BEHAVIOR
	{
		BEHAVIOR_NONE = -1,	// 動かない
		BEHAVIOR_FREEFALL,	// 自由落下
		BEHAVIOR_BURSTS,	// 上方向にランダムに弾ける
		BEHAVIOR_FULLBURSTS,// 全方向にランダムに弾ける
	};

	// まとめてドロップする時のまとまりの種類
	enum ITEM_LIST_DROPMULTIPLE
	{
		LIST_FRUIT,			// フルーツ
		LIST_FOOD,			// 食べ物
		LIST_COIN,			// コイン
		LIST_RARE,			// レアアイテム 宝石
		LIST_WEAPON,		// 武器
		LIST_SPECIAL,		// ボスマップ用の特別なアイテム用リスト

		LIST_ANI_NORMAL,	// アニメーションするアイテム
		LIST_ANI_RARE,		// アニメーションするアイテム
		LIST_ANI_MONKEY,	// サル
	};

	// 関数
	CItem();																	// コンストラクタ
	~CItem();																	// デストラクタ

	/* メンバ関数 */
	virtual HRESULT				Init();											// 初期化
	virtual void				Uninit();										// 終了
	virtual void				Update();										// 更新
	virtual void				Draw();											// 描画
	virtual void				DebugInfo();									// デバッグ
	virtual	void				SwitchTexture(ITEMTYPE type);					// 種類別テクスチャ設定
	virtual	void				Flashing();										// 点滅処理
	virtual void				ItemCollision();								// 当たり判定系
	virtual void				ReflectionItem();								// 反射処理
	virtual void				RemainTimer();									// 滞在時間を計算し0になったら削除する
	virtual void				HitItem(ITEMTYPE type, TAG Tag);				// アイテム取得時の種類別処理
	virtual void				ItemAcquisition(ITEMTYPE type, TAG Tag);		// アイテム取得時の種類別処理

	D3DXVECTOR3					SetPosOld() { return m_PosOld; };				// 1フレーム前の座標を設定
	int							GetRemainTime() const { return m_nRemainTime; };// アイテムの残り時間を取得

	// --- 設定 取得 --- //
	ITEMTYPE					GetItemType() { return m_Type; };				// アイテムタイプの取得
	void						SetItemType(ITEMTYPE type) { m_Type = type; };	// アイテムタイプの設定
	CCollision					*GetCollision() { return m_pCollision; };		// 当たり判定
	void						SetDropPos(D3DXVECTOR3 &characterpos);			// アイテムを生成位置を設定
	void						SetMove(D3DXVECTOR3 move);						// 移動量の設定
	ITEM_DATA					GetItem_Data() const{ return m_ItemData; };		// アイテムのデータの取得 呼び出し側は書き換え不可
	void						SetBehavior(ITEM_BEHAVIOR behavior) { m_Behavior = behavior; };// アイテムの挙動の設定
	ITEM_BEHAVIOR				GetBehavior() { return m_Behavior; };			// アイテムの挙動の設定
	CPlayer						*GetPlayer(int nCnt) { return m_pPlayer[nCnt]; };	// アイテムの挙動の設定

	/* 静的メンバ関数 */
	static ITEMTYPE				RandomWeapon();									// 武器のランダム
	static ITEMTYPE				ItemRandomRange(ITEMTYPE min, ITEMTYPE max);	// ランダムの範囲選択

	static bool					DropRate();										// アイテムをドロップさせるかのフラグを返す
	static bool					DecideIfItemDrop(int nRate);					// ドロップ率を元にアイテムがドロップするかを決めて結果を返す
	static uint64_t				GetRandRange(uint64_t min_val, uint64_t max_val);// ランダム関数 範囲
	static void					InitVariable();									// 静的変数の初期化
	static void					ItemLoad();										// アイテムの情報の読み込み
	static void					DebugItemCommand(CKeyboard *key);				// デバッグ用アイテムコマンド

	/* メンバ関数 */
	ITEMTYPE					RandDropItem(ITEMDROP drop);						// アイテムの種類をランダムに計算
	ITEM_RARITY					RarityRandomRange(ITEM_RARITY min, ITEM_RARITY max);// ランダムの範囲選択

	void						DropPattern(bool fixed, ITEMTYPE type);				// アイテムのドロップパターン
	void						DropPattern_Multiple(
		ITEM_LIST_DROPMULTIPLE list,
		ITEM_BEHAVIOR behavior,
		int nNum);																	// 複数一気にドロップさせる時

	void						BehaviorType(D3DXVECTOR3 &pos);						// アイテムの挙動の種類ごとの処理
protected:
	/* メンバ関数 */

	ITEMTYPE					BoxRand();										// ボックス乱数
	void						SetMultiType(ITEM_LIST_DROPMULTIPLE list);		// 複数体のタイプ設定
	D3DXVECTOR3					RandomDropPosX(const D3DXVECTOR3 originpos, int radius);//原点から指定された指定範囲のX座標を返す

	D3DXVECTOR3					*ReflectingVectorCalculation(					// 反射ベクトルを求める
		D3DXVECTOR3 *outV,
		const D3DXVECTOR3 &ProgressV,
		const D3DXVECTOR3 &Normal);


	/* メンバ変数 */
	D3DXVECTOR3					m_PosOld;										// 1フレーム前の座標
	float						m_fGravity;										// 重力
	int							m_nHitRayCount;									// レイの判定に触れた回数
	D3DXVECTOR3					m_Move;											// 移動量
	int							m_nColCnt;										// αカラーカウント

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
	void						SetBoxRandDataList();							// ボックス乱数の母数が0以下になった時内容をリセットする
	static void					AddBoxRandList();								// アイテムのレアリティと母数を元にランダムなリストを生成する
	void						BurstsItem();									// 複数個一気にアイテムが生成される時のアイテムの挙動制御
	void						BounceItem();									// 空中にあったアイテムが床に着いた時跳ね返る処理

	/* メンバ変数 */
	CCollision					*m_pCollision;									// 当たり判定
	CPlayer						*m_pPlayer[MAX_CONTROLLER];						// プレイヤーのポインタ
	ITEMTYPE					m_Type;											// アイテムタイプ
	ITEMDROP					m_Drop;											// アイテムをドロップさせる時の種類
	ITEM_BEHAVIOR				m_Behavior;										// アイテムの挙動
	ITEM_LIST_DROPMULTIPLE		m_MultipleListType;								// 複数ドロップさせる時のまとまりの種類
	int							m_nRemainTime;									// アイテムがマップに残る時間
};
#endif