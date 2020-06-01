// ----------------------------------------
//
// テロップ処理の説明[telop.h]
// Author : Fujiwara Masato
//
// ----------------------------------------
#ifndef _TELOP_H_
#define _TELOP_H_	 // ファイル名を基準を決める

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
class CTelop : public CScene_TWO
{
public:

	typedef enum
	{
		STATE_EMERGENCE = 0,				// 出現
		STATE_DISAPPEARANCE					// 消失
	} STATE;

	/* 関数 */
	CTelop();
	~CTelop();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static HRESULT Load(void);				// 読み込み
	static void UnLoad(void);				// UnLoadする
	static CTelop * Create(void);			// 作成
	void Transparency(STATE state);			// 透明化
	bool GetTelopFlag(void);				// フラグの取得

protected:

private:

	/* 変数 */
	static LPDIRECT3DTEXTURE9 m_pTexture;	// テクスチャー設定
	static D3DXVECTOR3 m_pos;				// 座標
	static D3DXVECTOR2 m_size;				// 大きさ
	static D3DXCOLOR m_Col;					// カラー

	int		m_nCntCol;						// カラーカウント
	bool	m_bTelopFlag;					// 完全に出現したかのフラグ
	bool	m_bCommentFlag;					// コメントが生成された時にtrue
	int		m_nCommentCount;				// 次のコメントに移行できるまでのカウント
};

#endif