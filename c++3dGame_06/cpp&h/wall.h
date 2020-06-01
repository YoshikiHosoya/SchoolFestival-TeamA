// ----------------------------------------
//
// 壁処理の説明[wall.h]
// Author : Fujiwara Masato
//
// ----------------------------------------
#ifndef _WALL_H_
#define _WALL_H_	 // ファイル名を基準を決める

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
#define MAX_WALLTEXTURE (2)
//=============================================================================
// 前方宣言
//=============================================================================

// ------------------------------------------
//
// クラス
//
// ------------------------------------------
class CWall : public CScene_X
{
public:
	/* 列挙型 */
	typedef enum
	{//*1枚 300*300*0
		SIZE_I = 0,								// 1枚分の大きさ
		SIZE_II,								// 2枚分の大きさ
		SIZE_III,								// 3枚分の大きさ
		SIZE_IV,								// 4枚分の大きさ
		SIZE_V,									// 5枚分の大きさ
		SIZE_VI,								// 6枚分の大きさ
		SIZE_VII,								// 7枚分の大きさ
		SIZE_VIII,								// 8枚分の大きさ
		SIZE_IX,								// 9枚分の大きさ
		SIZE_X,									// 10枚分の大きさ
		SIZE_XV,								// 15枚分の大きさ
		SIZE_XXI,								// 21枚分の大きさ
		TYPE_MAX,
	} SIZE;

	/* 関数 */
	CWall();
	~CWall();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPos(D3DXVECTOR3 pos);				// 位置設定
	void SetRot(D3DXVECTOR3 rot);				// 回転設定
	D3DXVECTOR3 GetPos(void);					// 位置取得
	static CWall * Create(	D3DXVECTOR3 pos,
							D3DXVECTOR3 rot,
							SIZE type);			// 作成
	static void CWall::LoadCreate(void);		// 読み込んだものを生成
	static HRESULT Load(void);					// 読み込み
	static void UnLoad(void);					// 破棄
protected:
private:
	static LPDIRECT3DTEXTURE9	m_pTexture[MAX_WALLTEXTURE];	// テクスチャへのポインタ
	static CLoad				*m_pload;		// ロード
	static CModel_info			*m_pmodel_info;	// モデル情報
	static int					m_nAll;			// 総数
	SIZE						m_type;			// 種類
	//D3DXVECTOR3					m_pos;			// 座標
	//D3DXVECTOR3					m_rot;			// 回転
};

#endif