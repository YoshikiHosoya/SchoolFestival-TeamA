// ----------------------------------------
//
// 照明エフェクト処理の説明[lighteffect.h]
// Author : Fujiwara Masato
//
// ----------------------------------------
#ifndef _LIGHTEFFECT_H_
#define _LIGHTEFFECT_H_	 // ファイル名を基準を決める

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
class CLightEffect : public CScene_THREE
{
public:
	/* 列挙型 */
	// タイプ
	typedef enum
	{
		TYPE_S_LIGHT = 0,	//
		TYPE_P_LIGHT,		//
		TYPE_MAX
	} TYPE;

	/* 関数 */
	CLightEffect();
	~CLightEffect();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetSize(D3DXVECTOR3 size);						// サイズ設定
	void SetPos(D3DXVECTOR3 pos);						// 位置設定
	void SetRot(D3DXVECTOR3 rot);						// 回転設定
	void SetCol(D3DXCOLOR col);							// 色設定
	void SetTex(D3DXVECTOR2 first, D3DXVECTOR2 last);	// テクスチャー座標設定
	void SetTexure(TYPE type);							// テクスチャー設定

	void Transparency(void);							// 透明


	D3DXVECTOR3 GetSize(void);							// サイズ取得
	D3DXVECTOR3 GetRot(void);							// 回転取得
	D3DXVECTOR3 GetPos(void);							// 位置取得
	static CLightEffect * Create(D3DXVECTOR3 pos,		// 作成
		D3DXVECTOR3 rot,
		D3DXVECTOR3 size,
		D3DXCOLOR col,
		TYPE type,
		bool bBill);

	static HRESULT Load(void);							// 読み込み
	static void UnLoad(void);							// 破棄
	static void ReleaseLight(TYPE type);							// エフェクトの削除

protected:
private:
	static LPDIRECT3DTEXTURE9 m_pTexture[TYPE_MAX];		// テクスチャへのポインタ
	static int		m_nAll;			// 番号
	D3DXMATRIX		m_mtxWorld;		// ワールドマトリックス
	float			m_fLengh;		// 長さ
	float			m_fAngle;		// 角度
	TYPE			m_type;			// 照明の種類
	bool			m_bBillboard;	// ビルボード状態
	D3DXVECTOR3		m_pos;			// 座標
	D3DXVECTOR3		m_rot;			// 回転
	D3DXVECTOR3		m_size;			// 大きさ
	D3DXCOLOR		m_col;			// 色
};
#endif
