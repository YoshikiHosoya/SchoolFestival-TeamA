// ★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★
//
// Collisionヘッダー処理の説明[calculation.h]
// Author : Fujiwara Masato
//
// ★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★

#ifndef _COLLISION_H_
#define _COLLISION_H_	 // ファイル名を基準を決める

// ★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★
//
// インクルードファイル
//
// ★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★
#include "main.h"

// ★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★
//
// マクロ定義
//
// ★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★
#define COLLISION_MAX (128)

// ★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★
//
// Collision種類
//
// ★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★

// ★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★
//
// 構造体定義
//
// ★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★

// ------------------------------------------
//
// 名前定義
//
// ------------------------------------------

// ------------------------------------------
//
// 前方宣言
//
// ------------------------------------------

// ------------------------------------------
//
// クラス
//
// ------------------------------------------
class CCollision
{
public:
	/* 列挙型 */
	// オブジェクトの種類
	typedef enum
	{
		OBJTYPE_PLAYER = 0,
		OBJTYPE_ENEMY,
		OBJTYPE_ACTOR,
		OBJTYPE_ITEM,
		OBJTYPE_WAIT,
		OBJTYPE_MAX
	} OBJTYPE;
	// 当たり判定の形
	typedef enum
	{
		COLLISIONTYPE_SQUARE = 0,
		COLLISIONTYPE_CIRCLE,
		COLLISIONTYPE_MAX
	} COLLISIONTYPE;
	/* 構造体 */
	typedef struct
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 size;
		OBJTYPE type;
	} INFO;
	/* 関数 */
	CCollision();
	~CCollision();
	void Init(void);
	void Uninit(void);
	void Update(void);
	static void UpdateAll(void);		// 当たり判定更新
	static void Delete(int ID);
	static void DeleteAll(void);
	static CCollision * Create(void);
	static void LoadCreate(void);		// 読み込んだものを生成
	static void LoadCreate2D(void);

	static CCollision * Create_Single(
		D3DXVECTOR3 pos,
		D3DXVECTOR3 size);// オブジェクトを読み込み生成する時に生成

	// 設定
	void SetPos(D3DXVECTOR3 *pos);
	void SetSize(D3DXVECTOR3 size);
	void SetSize2D(D3DXVECTOR3 size);
	void SetMove(D3DXVECTOR3 *move);
	void SetType(OBJTYPE type);
	// 当たり判定
	bool Collision_Come(void);
	bool Collision_Player(void);
	static void Load(void);
	void Collision(void);

protected:

private:
	/* 関数 */
	static int TextLoad(void);
	// 当たり判定
	/* 変数 */
	static int m_nAll;					// 総数
	static int m_nNumLoad;				// ロード数
	static INFO m_Info[COLLISION_MAX];	// 情報
	int m_ID;							// 番号
	OBJTYPE m_objtype;						// タイプ
	D3DXVECTOR3 *m_ppos;				// 位置情報
	D3DXVECTOR3 m_posOld;				// 前回の位置情報
	D3DXVECTOR3 m_size;					// サイズ情報
	D3DXVECTOR3 *m_pmove;				// 移動情報
	static CCollision * m_pTop;			// 先頭オブジェクトへのポインタ
	static CCollision * m_pCur;			// 現在オブジェクトへのポインタ
	CCollision * m_pNext;				// 次のオブジェクトへのポインタ
	CCollision * m_pPrey;				// 前のオブジェクトへのポインタ
	bool m_bDeadFrag;					// フラグ
};

// ★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★
//
// プロトタイプ宣言
//
// ★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★

#endif