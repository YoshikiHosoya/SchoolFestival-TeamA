// ----------------------------------------
//
// テロップコメント処理の説明[TelopComment.h]
// Author : Fujiwara Masato
//
// ----------------------------------------
#ifndef _TELOPCOMMENT_H_
#define _TELOPCOMMENT_H_	 // ファイル名を基準を決める

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
#define TELOP_POS (D3DXVECTOR3(640.0f, 590, 0.0f))
#define TELOP_SIZE (D3DXVECTOR2(520.0f, 40.0f))

// ----------------------------------------
//
// 前方宣言
//
// ----------------------------------------

// ------------------------------------------
//
// クラス
//
// ------------------------------------------
class CTelopComment : public CScene_TWO
{
public:

	typedef enum
	{
		TYPE_0 = 0,
		TYPE_1,
		TYPE_2,
		TYPE_3,
		TYPE_4,
		TYPE_MAX
	} TYPE;

	typedef enum
	{
		PHASE_NONE = 0,
		PHASE_ONE,
		PHASE_TWO,
		PHASE_THREE,
		PHASE_FOUR,
		PHASE_FIVE,
		PHASE_END
	} PHASE;

	typedef enum
	{
		STATE_EMERGENCE = 0,				// 出現
		STATE_DISAPPEARANCE					// 消失
	} STATE;

	/* 関数 */
	CTelopComment();
	~CTelopComment();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static HRESULT Load(void);						// 読み込み
	static void UnLoad(void);						// UnLoadする

	static CTelopComment * Create(D3DXVECTOR3 pos,
								D3DXVECTOR2 size,
								TYPE type);			// 作成

	static void CreateTelopCommnet(PHASE phase);				// 作成

	void Transparency(STATE state);					// 透明化
	static void SetPhase(void);						// 次の段階へ
	static void Phase(void);						// 各段階の処理
	static bool GetEndPhaseFlag(void);				// フラグの取得
	static PHASE GetPhase(void);					// 現在のフェイズの取得

protected:

private:

	/* 変数 */
	static LPDIRECT3DTEXTURE9	m_pTexture[TYPE_MAX];	// テクスチャー設定
	D3DXCOLOR					m_col;					// カラー
	D3DXVECTOR3					m_pos;					// 座標
	D3DXVECTOR2					m_size;					// 大きさ
	static PHASE				m_phase;				// 段階
	static bool					bEndPhase;				// コメントを全て消化したかの判定
	static int					m_nCreateCount;			//生成されるまでの時間
	bool						bDisFlag;				//消滅フラグ
};

#endif
