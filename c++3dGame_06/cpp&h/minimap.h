// ----------------------------------------
//
// ミニマップ処理の説明[minimap.h]
// Author : Fujiwara Masato
//
// ----------------------------------------
#ifndef _MINIMAP_H_
#define _MINIMAP_H_	 // ファイル名を基準を決める

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
class CMinimap : public CScene_TWO
{
public:
	/* 列挙型 */
	typedef enum
	{
		/* ミニマップのUI種類 */
		MINIMAP_UI_MAP = 0,									//マップ本体
		MINIMAP_UI_SHARD_POS,								//欠片の座標
		MINIMAP_UI_ENEMY_POS,								//エネミーの座標
		MINIMAP_UI_PLAYER_POS,								//プレイヤーの座標
		MINIMAP_UI_FRAME,									//外枠
		MINIMAP_UI_MISSION00,								//現在の目的を表示(欠片を全て集めよ)
		MINIMAP_UI_MISSION01,								//現在の目的を表示(ゴールを目指せ)
		MINIMAP_UI_MAX
	} MINIMAP_UI_TYPE;

	/* 関数 */
	CMinimap();
	~CMinimap();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetTexture(MINIMAP_UI_TYPE type);					// テクスチャー設定
	void SetSize(D3DXVECTOR2 size);							// サイズ設定
	void SetPos(D3DXVECTOR3 pos);							// 位置設定
	void SetRot(float rot);									// 回転設定
	void SetCol(D3DXCOLOR col);								// 色設定
	void SetTex(D3DXVECTOR2 first, D3DXVECTOR2 last);		// 表示テクスチャー設定
	D3DXVECTOR2 GetSize(void);								// サイズ取得
	D3DXVECTOR3 GetPos(void);								// 位置取得

	void TexRange(void);
	void MAP_MOVE(void);

	void ExceptUI(void);									// 数を減らす

	static CMinimap * Create(void);							// 作成
	static void CMinimap::LoadCreate(void);					// 読み込んだものを生成
	static HRESULT Load(void);								// 読み込み
	static void UnLoad(void);								// 破棄
	static CLoad2D *GetLoad(void);							// ロード取得
protected:
private:
	/* 列挙型 */
	typedef enum
	{
		/* ミニマップのUI種類 */
		MINIMAP_STATE_NORMAL = 0,							//ミニマップの状態
		MINIMAP_STATE_ALLMAP,								//マップの全体表示状態
		MINIMAP_STATE_MAX
	} MINIMAP_STATE;

	/* 関数 */
	void Various(int nCnt);									// 種類別処理

	/* 変数 */
	static LPDIRECT3DTEXTURE9 m_pTexture[MINIMAP_UI_MAX];	// テクスチャー設定
	static CLoad2D		*m_pload2D;							// ロード
	static int			m_nAll;								// 総数
	float	m_fMult;										// 倍数
	float	m_fAdd;											// 加算
	int		m_nRange;										// 描画する幅
	MINIMAP_STATE m_state;
	MINIMAP_UI_TYPE m_type;
	float	m_rot;											//ミニマップの回転
	D3DXVECTOR3 m_pos;										//欠片とエネミーの座標
	D3DXVECTOR3 m_move;										//欠片とエネミーの座標

	D3DXVECTOR2	m_TexFirstMove;
	D3DXVECTOR2	m_TexLastMove;

	D3DXVECTOR2	m_TexFirst;									//ミニマップのテクスチャ座標
	D3DXVECTOR2	m_TexLast;									//ミニマップのテクスチャ座標
	//D3DXVECTOR3 m_tex;
};

#endif
