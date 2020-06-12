// =====================================================================================================================================================================
//
// ランキングUIの処理[rankingUI.h]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#ifndef _RANKINGUI_H_
#define _RANKINGUI_H_	 

#define _CRT_SECURE_NO_WARNINGS

#include "main.h"			// インクルードファイル
#include"scene2D.h"

// =====================================================================================================================================================================
// ランキングUIクラス
// =====================================================================================================================================================================
class CRankingUI : public CScene2D
{
public:

	// UIの種類
	enum RANKINGUITYPE
	{
		RK_UI_NONE = -1,
		RK_UI_RANK_1,				// 1位
		RK_UI_RANK_2,				// 2位
		RK_UI_RANK_3,				// 3位
		RK_UI_RANK_4,				// 4位
		RK_UI_RANK_5,				// 5位
		RK_UI_RANKING,				// ランキング
		RK_UI_ENTER,				// Enterキー

		RK_UI_MAX,
	};

	CRankingUI();								// コンストラクタ
	~CRankingUI();								// デストラクタ

	/* メンバ関数 */
	void				Init();					// 初期化
	void				Uninit();				// 終了
	void				Update();				// 更新
	void				Draw();					// 描画

	/* 静的メンバ関数 */
	static  CRankingUI	*Create();				// リザルトUIの生成
	static	HRESULT		Load();					// ロード				( 読み込み )
	static	void		Unload();				// アンロード			( 破棄 )

private:
	/* 静的メンバ変数 */
	static	LPDIRECT3DTEXTURE9	m_apTexture[RANKINGUITYPE::RK_UI_MAX];		// 共有テクスチャのポインタ
	/* メンバ変数 */
	CScene2D					*m_apScene2D[RANKINGUITYPE::RK_UI_MAX];		// シーン2Dのポインタ
	D3DXVECTOR3					m_UV[RANKINGUITYPE::RK_UI_MAX];				// UV
};
#endif
