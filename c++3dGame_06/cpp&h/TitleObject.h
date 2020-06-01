// ----------------------------------------
//
// オブジェクト処理の説明[object.h]
// Author : Fujiwara Masato
//
// ----------------------------------------
#ifndef _TITLEOBJECT_H_
#define _TITLEOBJECT_H_	 // ファイル名を基準を決める

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
// -----------------------------------
#define MAX_TITLEOBJ (2)
//=============================================================================
// 前方宣言
//=============================================================================

// ------------------------------------------
//
// クラス
//
// ------------------------------------------
class CTitleObject : public CScene_X
{
public:
	/* 関数 */
	CTitleObject();
	~CTitleObject();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPos(D3DXVECTOR3 pos);			// 位置設定
	void SetRot(D3DXVECTOR3 rot);			// 回転設定
	D3DXVECTOR3 GetPos(void);				// 位置取得
	static CTitleObject * Create(void);			// 作成
	static void CTitleObject::LoadCreate(void);	// 読み込んだものを生成
	static HRESULT Load(void);				// 読み込み
	static void UnLoad(void);				// 破棄
protected:
private:
	static CLoad		*m_pload;							// ロード
	static CModel_info	*m_pmodel_info;					// モデル情報
	static int			m_nAll;								// 総数
};

#endif

