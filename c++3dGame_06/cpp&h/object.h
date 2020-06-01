// ----------------------------------------
//
// オブジェクト処理の説明[object.h]
// Author : Fujiwara Masato
//
// ----------------------------------------
#ifndef _OBJECT_H_
#define _OBJECT_H_	 // ファイル名を基準を決める

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
class CObject : public CScene_X
{
public:
	/*列挙*/
	typedef enum
	{
		OBJ_TYPE_CheckPoint,
		OBJ_TYPE_MAX
	} OBJ_TYPE;


	/* 関数 */
	CObject();
	~CObject();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPos(D3DXVECTOR3 pos);			// 位置設定
	void SetRot(D3DXVECTOR3 rot);			// 回転設定
	D3DXVECTOR3 GetPos(void);				// 位置取得
	static CObject * Create(void);			// 作成
	static void CObject::LoadCreate(void);	// 読み込んだものを生成
	static HRESULT Load(void);				// 読み込み
	static void UnLoad(void);				// 破棄
protected:
private:
	static CLoad		*m_pload;							// ロード
	static CModel_info	*m_pmodel_info;					// モデル情報
	static int			m_nAll;								// 総数
	OBJ_TYPE			m_type;
};

#endif
