// ----------------------------------------
//
//	マップ処理の説明[map.h]
// Author : Fujiwara Masato
//
// ----------------------------------------
#ifndef _MAP_H_
#define _MAP_H_	 // ファイル名を基準を決める

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

//=============================================================================
// 前方宣言
//=============================================================================

// ------------------------------------------
//
// クラス
//
// ------------------------------------------
class CMap : public CScene
{
public:
	/* 列挙型 */
	typedef enum
	{
		/* ミニマップのUI種類 */
		MAP_UI_MAP = 0,									//マップ本体
		MAP_UI_FRAME,									//外枠
		MAP_UI_MISSION00,								//現在の目的を表示(欠片を全て集めよ)
		MAP_UI_MAX
	} MAP_UI_TYPE;

	/* 関数 */
	CMap();
	~CMap();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CMap * Create(void);								// 作成
	static HRESULT Load(void);								// 読み込み
	static void UnLoad(void);								// 破棄
protected:
private:
	static LPDIRECT3DTEXTURE9 m_pTex[MAP_UI_MAX];			// テクスチャー設定
	static D3DXVECTOR3 m_pos[MAP_UI_MAX];					// 位置情報
	static D3DXVECTOR2 m_size[MAP_UI_MAX];					// サイズ情報
	static MAP_UI_TYPE m_type[MAP_UI_MAX];					// uiの種類
	CScene_TWO *m_aScene_Two[MAP_UI_MAX];					// ポーズ用ui2D
};

#endif
