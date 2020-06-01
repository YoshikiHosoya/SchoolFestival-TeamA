// ----------------------------------------
//
// タイル床処理の説明[floartile.h]
// Author : Fujiwara Masato
//
// ----------------------------------------
#ifndef _FLOARTILE_H_
#define _FLOARTILE_H_	 // ファイル名を基準を決める

// ----------------------------------------
//
// インクルードファイル
//
// ----------------------------------------
#include "scene_X.h"

// ----------------------------------------
//
// マクロ定義
//
// ----------------------------------------
#define MAX_TILENUMBER (713)		// 全てのマスの総数
#define MAX_WALKTILENUMBER (228)	// 進行できるタイルの総数
#define MAX_VERTICALNUM (31)		// タイルの縦の数-2
#define MAX_HORIZONTALNUM (23)		// タイルの横の数-2

//=============================================================================
// 前方宣言
//=============================================================================
class CEnemy;
// ------------------------------------------
//
// クラス
//
// ------------------------------------------
class CFloarTile : public CScene_X
{
public:
	/* 列挙型 */
	// タイルの種類
	typedef enum
	{
		TILE_TYPE_WALL = 0,		// 歩行不可能マス
		TILE_TYPE_TILE_NOR,		// 歩行可能な通常マス
		TILE_TYPE_TILE_SP,		// 敵と判定を取るためのマス
		TILE_TYPE_MAX			// タイルの種類の総数
	} TILE_TYPE;

	// 方向
	typedef enum
	{
		DIRECTION_FORWARD = 0,	// 前方
		DIRECTION_BACKWARD,		// 後方
		DIRECTION_LEFT,			// 左
		DIRECTION_RIGHT,		// 右
		DIRECTION_ALL			// 全方位
	} DIRECTION;


	/* 関数 */
	CFloarTile();
	~CFloarTile();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPos(D3DXVECTOR3 pos);									// 位置設定
	void SetRot(D3DXVECTOR3 rot);									// 回転設定
	D3DXVECTOR3 GetPos(void);										// 位置取得

	static CFloarTile * Create(void);								// 作成
	static void CFloarTile::LoadCreate(void);						// 読み込んだものを生成

	void PlayerJudg();												// 判定
	void EnemyJudg();												// 判定
	void EnemyAi();													// 敵の進行を決める計算
	static HRESULT Load(void);										// 読み込み
	static void UnLoad(void);										// 破棄
	static HRESULT LoadTileNum(const char * filename);				// 読み込み

protected:
private:
	static LPDIRECT3DTEXTURE9	m_pTexture;							// テクスチャへのポインタ
	static CLoad				*m_pload;							// ロード
	static CModel_info			*m_pmodel_info;						// モデル情報
	static CFloarTile			*m_paFloarTile[MAX_WALKTILENUMBER]; // 歩行可能タイル用変数
	static int					m_aTileType[MAX_TILENUMBER];		// タイルの種類
	static int					m_aTileNum[MAX_TILENUMBER];			// タイルの数
	static int					m_nPlayerSavepos;					// プレイヤーが踏んだマスを保存

	TILE_TYPE					m_type;								// タイルの種類
	DIRECTION					m_Dire;								// 進行方向
	CEnemy					    *m_pEnemy;							// エネミーのポインタ
	CFloarTile					*m_pFloarTile;						// タイルのポインタ
	int							m_nEnemySavepos;					// エネミーーが踏んだマスを保存
	int							m_nTileNum;							// タイルのmyNumber
	int							m_nSaveArrayNumber;					// 配列の番号を保存
	int							m_nDirection;						// 向き
	bool						m_bLand_Enemy;						// 敵がマスを踏んでいるかどうか
	bool						m_bFlag[4];							// 敵が進行できるかのフラグ
	int							m_nDirEnemyBackward;
};

#endif