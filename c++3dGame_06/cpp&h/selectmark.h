// ----------------------------------------
//
// 印処理の説明[selectmark.h]
// Author : Fujiwara Masato
//
// ----------------------------------------
#ifndef _SELECTMARK_H_
#define _SELECTMARK_H_	 // ファイル名を基準を決める

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
class CSelectMark : public CScene_TWO
{
public:
	/* 列挙型 */
	// タイプ
	typedef enum
	{
		MARK_ARROW = 0,		// 矢印
		MARK_SHAPE,			// 図形
		MARK_MAX
	} MARK;

	/* 関数 */
	CSelectMark();
	~CSelectMark();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetSize(D3DXVECTOR2 size);						// サイズ設定
	void SetPos(D3DXVECTOR3 pos);						// 位置設定
	void SetRot(float rot);								// 回転設定
	void SetCol(D3DXCOLOR col);							// 色設定
	void SetTexure(MARK type);							// テクスチャー設定
	void SetCount(int nCnt);							// カウンター設定
	void CalculationCount(int nCnt);					// カウンター設定
	void ResetCount(void);								// カウントをリセット
	void ReleaseSelMark(void);							// マークの削除
	void Transparency(void);							// 透明化

	int			GetCount(void);							// カウントを取得
	D3DXVECTOR2 GetSize(void);							// サイズ取得
	D3DXVECTOR3 GetPos(void);							// 位置取得
	static CSelectMark * Create(D3DXVECTOR3 pos,		// 作成
		float rot,
		D3DXVECTOR2 size,
		D3DXCOLOR col,
		MARK type);

	static HRESULT Load(void);							// 読み込み
	static void UnLoad(void);							// 破棄

protected:
private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MARK_MAX];		// テクスチャへのポインタ
	float			m_fLengh;							// 長さ
	float			m_fAngle;							// 角度
	MARK			m_type;								// 照明の種類
	D3DXVECTOR3		m_pos;								// 座標
	float			m_frot;								// 回転
	D3DXVECTOR2		m_size;								// 大きさ
	D3DXCOLOR		m_col;								// 色
	int				m_nSelectCount;						// 印を移動させた回数
};
#endif

