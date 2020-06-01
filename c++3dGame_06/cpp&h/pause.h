// ----------------------------------------
//
// ポーズ処理の説明[pouse.h]
// Author : Fujiwara Masato
//
// ----------------------------------------
#ifndef _PAUSE_H_
#define _PAUSE_H_	 // ファイル名を基準を決める

// ----------------------------------------
//
// インクルードファイル
//
// ----------------------------------------
#include "scene_two.h"
// ----------------------------------------
//
// マクロ定義
//
// ----------------------------------------

// ----------------------------------------
//
// 前方宣言
//
// ----------------------------------------
// ------------------------------------------
//
// クラス
//
// ------------------------------------------
class CPause : public CScene
{
public:
	/* 関数 */
	CPause();
	~CPause();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static HRESULT Load(void);			// 読み込み
	static void UnLoad(void);			// UnLoadする
	static CPause * Create(void);	// 作成

	static void SetPause(bool bPause);	// ポーズの状態設定
	static bool GetPause(void);			// ポーズの状態取得

protected:

private:
	/* 変数 */
	/* 変数 */
	static LPDIRECT3DTEXTURE9 m_pTex;		// テクスチャー設定
	static D3DXVECTOR3 m_pos;				// 位置情報
	static D3DXVECTOR2 m_size;				// サイズ情報
	static bool m_bPause;					// ポーズ状態かどうか
	CScene_TWO *m_aScene_Two;				// ポーズ用ui2D
};

#endif
