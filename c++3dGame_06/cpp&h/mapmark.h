// ----------------------------------------
//
//	マップに表示するマーク処理の説明[mapmark.h]
// Author : Fujiwara Masato
//
// ----------------------------------------
#ifndef _MAPMARK_H_
#define _MAPMARK_H_	 // ファイル名を基準を決める

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
#define MAX_SHARDMARK (54)
#define TOTAL_MARK (55)
//=============================================================================
// 前方宣言
//=============================================================================

// ------------------------------------------
//
// クラス
//
// ------------------------------------------
class CMapMark : public CScene
{
public:
	/* 列挙型 */
	typedef enum
	{
		/* マップのUI種類 */
		MAP_MARK_SHARD = 0,								// 欠片の位置を示すマーク
		MAP_MARK_PLAYER,								// プレイヤーの位置を示すマーク
		//MAP_MARK_ENEMY,									// 敵の位置を示すマーク
		MAP_MARK_MAX
	} MAP_MARK_TYPE;

	/* 関数 */
	CMapMark();
	~CMapMark();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CMapMark * Create(void);							// 作成
	static HRESULT Load(void);								// 読み込み
	static void UnLoad(void);								// 破棄
	void ReleseMaker(int nId);
	void SetMapMaker(D3DXVECTOR3 pos);

protected:
private:

	/* 関数 */
	void Various(int nCnt);									// 種類別処理
															/* 変数 */
	static D3DXVECTOR3		m_pos[TOTAL_MARK];// 位置情報
	static D3DXVECTOR2		m_size[MAP_MARK_MAX];			// サイズ情報
	static D3DXCOLOR		m_col[MAP_MARK_MAX];			// 色
	static MAP_MARK_TYPE	m_type[MAP_MARK_MAX];			// uiの種類
	CScene_TWO				*m_aScene_Two[TOTAL_MARK];		//
	D3DXVECTOR3				m_move;							// 移動
	int						m_nCount;						// ロードで使うカウント
	//static D3DXVECTOR3		m_move[TOTAL_MARK];				// 位置情報
};

#endif
