// ----------------------------------------
//
// 鍵処理の説明[key.h]
// Author : Fujiwara Masato
//
// ----------------------------------------
#ifndef _KEY_H_
#define _KEY_H_	 // ファイル名を基準を決める

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

//=============================================================================
// 前方宣言
//=============================================================================

// ------------------------------------------
//
// クラス
//
// ------------------------------------------
class CKey : public CScene_X
{
public:
	/* 列挙型 */

	/* 関数 */
	CKey();
	~CKey();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPos(D3DXVECTOR3 pos);			// 位置設定
	void SetRot(D3DXVECTOR3 rot);			// 回転設定
	D3DXVECTOR3 GetPos(void);				// 位置取得
	static bool bGetFlag(void);
	static CKey * Create(void);			// 作成
	static HRESULT Load(void);				// 読み込み
	static void UnLoad(void);				// 破棄
protected:
private:
	static CModel_info	*m_pmodel_info;					// モデル情報
	static D3DXVECTOR3 m_pos;							// 位置情報
	static bool			m_bGet;				// 鍵を手に入れたかどうか
};

#endif