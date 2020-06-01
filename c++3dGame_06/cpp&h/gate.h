// ----------------------------------------
//
// ゲート処理の説明[gate.h]
// Author : Fujiwara Masato
//
// ----------------------------------------
#ifndef _GATE_H_
#define _GATE_H_	 // ファイル名を基準を決める

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
class CGate : public CScene_THREE
{
public:
	/* 列挙型 */
	// タイプ
	typedef enum
	{
		TYPE_TURN_R = 0,	// 右回転 奥
		TYPE_TURN_L,		// 左回転 手前
		TYPE_MAX
	} TYPE;

	typedef enum
	{
		USETYPE_TITLE = 0,	// タイトルで使う
		USETYPE_GAME,		// ゲームで使う
		USETYPE_MAX
	} USETYPE;

	/* 関数 */
	CGate();
	~CGate();
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
	static CGate * Create();							// 作成
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
	TYPE			m_Type;			// タイプ
	USETYPE			m_UseType;
};
#endif