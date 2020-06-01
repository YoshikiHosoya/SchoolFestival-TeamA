// ----------------------------------------
//
// 天井処理の説明[ceiling.h]
// Author : Fujiwara Masato
//
// ----------------------------------------
#ifndef _CEILING_H_
#define _CEILING_H_	 // ファイル名を基準を決める

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
#define MAX_CEILINGTEXTURE (2)
//=============================================================================
// 前方宣言
//=============================================================================

// ------------------------------------------
//
// クラス
//
// ------------------------------------------
class CCeiling : public CScene_X
{
public:
	/* 列挙型 */
	typedef enum
	{//*1枚 300*300*0
		SIZE_NORMAL = 0,						// 通常の天井
		SIZE_GIMMICK,							// 穴が開いてる天井
		TYPE_MAX,
	} SIZE;

	/* 関数 */
	CCeiling();
	~CCeiling();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPos(D3DXVECTOR3 pos);				// 位置設定
	void SetRot(D3DXVECTOR3 rot);				// 回転設定
	D3DXVECTOR3 GetPos(void);					// 位置取得
	static CCeiling * Create(D3DXVECTOR3 pos,
		D3DXVECTOR3 rot,
		SIZE type);			// 作成
	static void CCeiling::LoadCreate(void);		// 読み込んだものを生成
	static HRESULT Load(void);					// 読み込み
	static void UnLoad(void);					// 破棄
protected:
private:
	static LPDIRECT3DTEXTURE9	m_pTexture[MAX_CEILINGTEXTURE];	// テクスチャへのポインタ
	static CLoad				*m_pload;		// ロード
	static CModel_info			*m_pmodel_info;	// モデル情報
	static int					m_nAll;			// 総数
	SIZE						m_type;			// 種類
};

#endif