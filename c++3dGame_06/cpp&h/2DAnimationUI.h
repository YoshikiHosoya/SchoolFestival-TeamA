// ----------------------------------------
//
// 2Dのアニメーション処理の説明[2DAnimation.h]
// Author : Fujiwara Masato
//
// ----------------------------------------
#ifndef _2DANIMATION_H_
#define _2DANIMATION_H_	 // ファイル名を基準を決める

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

// ------------------------------------------
//
// クラス
//
// ------------------------------------------
class C2DAnimation : public CScene_TWO
{
public:
	/* 列挙型 */
	// タイプ
	typedef enum
	{
		TYPE_KEY = 0,	// 鍵
		TYPE_1,			//
		TYPE_2,			//
		TYPE_MAX
	} TYPE;

	/* 関数 */
	C2DAnimation();
	~C2DAnimation();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetTexture(TYPE type);								// テクスチャー設定
	void SetSize(D3DXVECTOR2 size);							// サイズ設定
	void SetPos(D3DXVECTOR3 pos);							// 位置設定
	void SetRot(float rot);									// 回転設定
	void SetCol(D3DXCOLOR col);								// 色設定
	void SetTex(D3DXVECTOR2 first, D3DXVECTOR2 last);		// 表示テクスチャー設定
	void SetAnim(void);										// アニメーション再生
	D3DXVECTOR2 GetSize(void);								// サイズ取得
	float GetRot(void);										// 回転取得
	D3DXVECTOR3 GetPos(void);								// 位置取得
	static C2DAnimation * Create(D3DXVECTOR3 pos,
								D3DXVECTOR2 size,
								D3DXVECTOR2 texf,
								D3DXVECTOR2 texr,
								TYPE type);					// 作成
	static HRESULT Load(void);								// 読み込み
	static void UnLoad(void);								// 破棄
protected:
private:
	static LPDIRECT3DTEXTURE9	m_pTexture[TYPE_MAX];		// テクスチャへのポインタ
	TYPE						m_Type;						// タイプ
	int							m_nCntAnim;					// 1フレームあたりのカウント
	int							m_nPatternAnim;				// パターン数
	D3DXVECTOR2					m_TexFirst;					// テクスチャ座標
	D3DXVECTOR2					m_TexLast;					// テクスチャ座標
};
#endif