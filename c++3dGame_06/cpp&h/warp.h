// ----------------------------------------
//
// ワープゲート処理の説明[warp.h]
// Author : Fujiwara Masato
//
// ----------------------------------------
#ifndef _WARP_H_
#define _WARP_H_	 // ファイル名を基準を決める

// ----------------------------------------
//
// インクルードファイル
//
// ----------------------------------------
#include "scene_three.h"

// ----------------------------------------
//
// マクロ定義
//
// ----------------------------------------

// ------------------------------------------
//
// クラス
//
// ------------------------------------------
class CWarp : public CScene_THREE
{
public:
	/* 列挙型 */
	// タイプ
	typedef enum
	{
		TYPE_ENTRANCE = 0,	// 入口
		TYPE_EXIT,			// 出口
		TYPE_MAX
	} TYPE;

	/* 関数 */
	CWarp();
	CWarp(ACTOR actor, LAYER layer);
	~CWarp();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetTexture(TYPE type);							// テクスチャー設定
	void SetSize(D3DXVECTOR3 size);						// サイズ設定
	void SetPos(D3DXVECTOR3 pos);						// 位置設定
	void SetRot(D3DXVECTOR3 rot);						// 回転設定
	void SetCol(D3DXCOLOR col);							// 色設定
	void SetTex(D3DXVECTOR2 first, D3DXVECTOR2 last);	// 表示テクスチャー設定
	D3DXVECTOR3 GetSize(void);							// サイズ取得
	D3DXVECTOR3 GetRot(void);							// 回転取得
	D3DXVECTOR3 GetPos(void);							// 位置取得
	static CWarp * Create();				// 作成
	static void LoadCreate(void);						// アイテム生成
	static HRESULT Load(void);							// 読み込み
	static void UnLoad(void);							// 破棄
	static CLoad *GetLoad(void);						// ロード取得
protected:
private:
	static LPDIRECT3DTEXTURE9 m_pTexture[TYPE_MAX];		// テクスチャへのポインタ
	static CLoad	*m_pload;		// ロード
	static int		m_nAll;			// 番号
	D3DXMATRIX		m_mtxWorld;		// ワールドマトリックス
	TYPE			m_Type;		// タイプ
};
#endif