// ----------------------------------------
//
// 爆発エフェクト処理の説明[lighteffect.h]
// Author : Fujiwara Masato
//
// ----------------------------------------
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_	 // ファイル名を基準を決める

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
class CExplosion : public CScene_THREE
{
public:
	/* 列挙型 */
	// タイプ
	typedef enum
	{
		TYPE_SMOKE = 0,		//煙
		TYPE_EXPLOSION,		//爆発
		TYPE_MAX
	} TYPE;

	/* 関数 */
	CExplosion();
	~CExplosion();
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
	void SetAnim(void);									// アニメーション再生
	D3DXVECTOR3 GetSize(void);							// サイズ取得
	D3DXVECTOR3 GetRot(void);							// 回転取得
	D3DXVECTOR3 GetPos(void);							// 位置取得
	static CExplosion * Create(D3DXVECTOR3 pos,
								D3DXVECTOR3 size,
								TYPE type);		// 作成
	static HRESULT Load(void);							// 読み込み
	static void UnLoad(void);							// 破棄
protected:
private:
	static LPDIRECT3DTEXTURE9 m_pTexture[TYPE_MAX];			// テクスチャへのポインタ
	D3DXMATRIX		m_mtxWorld;							// ワールドマトリックス
	float			m_fLengh;							// 長さ
	float			m_fAngle;							// 角度
	TYPE			m_Type;								// 照明の種類
	bool			m_bBillboard;						// ビルボード状態
	int				m_nCntAnim;							// 1フレームあたりのカウント
	int				m_nPatternAnim;						// パターン数
	static D3DXVECTOR2		m_Tex[TYPE_MAX];								// テクスチャ座標
	D3DXVECTOR2		m_TexFirst;							// テクスチャ座標
	D3DXVECTOR2		m_TexFirstSMO;							// テクスチャ座標
	D3DXVECTOR2		m_TexLast;							// テクスチャ座標
	D3DXVECTOR2		m_TexLastSMO;							// テクスチャ座標
	D3DXCOLOR		m_Col;								// 色
	D3DXVECTOR3		m_Size;								// 大きさ
};
#endif
