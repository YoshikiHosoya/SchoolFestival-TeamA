// ----------------------------------------
//
// 3DItem処理の説明[3DItem.h]
// Author : Fujiwara Masato
//
// ----------------------------------------
#ifndef _3DITEM_H_
#define _3DITEM_H_	 // ファイル名を基準を決める

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

//=============================================================================
// 前方宣言
//=============================================================================

// ------------------------------------------
//
// クラス
//
// ------------------------------------------
class C3DItem : public CScene_X
{
public:
	/* 列挙型 */
	// タイプ
	typedef enum
	{
		TYPE_SHARD = 0,	// クリア条件
		TYPE_MAX
	} TYPE;

	/* 関数 */
	C3DItem();
	C3DItem(ACTOR actor, LAYER layer);
	~C3DItem();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPos(D3DXVECTOR3 pos);					// 位置設定
	void SetRot(D3DXVECTOR3 rot);					// 回転設定
	D3DXVECTOR3 GetPos(void);						// 位置取得
	static int GetShardNum(void);					// 欠片の総数
	bool ShardFlag(void);							// 欠片が全てなくなった時の判定

	static void Except3DItem(void);					// 3Dアイテムの総数を減らす
	static C3DItem * Create(void);					// 作成
	static void C3DItem::LoadCreate(void);			// 読み込んだものを生成
	static HRESULT Load(void);						// 読み込み
	static void UnLoad(void);						// 破棄

protected:
private:
	typedef struct
	{
		// アイテムのId
		int nId;
	} ItemID;



	static LPDIRECT3DTEXTURE9 m_pTexture[1];		// テクスチャへのポインタ
	static CLoad		*m_pload;					// ロード
	static CModel_info	*m_pmodel_info;				// モデル情報
	static int			m_nAll;						// 総数
	TYPE				m_Type;						// タイプ
	D3DXMATRIX			m_mtxWorld;					// 行列
	bool				m_bShard;					// 欠片の数が0以下になったらtrue
	static int			m_nShardNum;				// 欠片の総数
	//int					m_nId;						// アイテムを識別する番号
	ItemID				m_ID;
};

#endif
