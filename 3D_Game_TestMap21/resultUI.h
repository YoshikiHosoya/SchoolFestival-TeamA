// =====================================================================================================================================================================
//
// リザルトUIの処理 [resultUI.h]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#ifndef _RESULTUI_H_
#define _RESULTUI_H_

#include "main.h"
#include"scene2D.h"

// =====================================================================================================================================================================
// リザルトUIクラス
// =====================================================================================================================================================================
class CResultUI : public CScene2D
{
public:

	// UIの種類
	enum RESULTUITYPE
	{
		R_UI_NONE = -1,
		R_UI_LOGO,					// ロゴ
		R_UI_ENTER,					// Enterキー
		R_UI_MAOU,					// 魔王魂
		R_UI_MAX,
	};

	CResultUI();								// コンストラクタ
	~CResultUI();								// デストラクタ

	/* メンバ関数 */
	void				Init();					// 初期化
	void				Uninit();				// 終了
	void				Update();				// 更新
	void				Draw();					// 描画

	/* 静的メンバ関数 */
	static  CResultUI	*Create();				// リザルトUIの生成
	static	HRESULT		Load();					// ロード
	static	void		Unload();				// アンロード

private:
	/* 静的メンバ変数 */
	static	LPDIRECT3DTEXTURE9	m_apTexture[RESULTUITYPE::R_UI_MAX];		// 共有テクスチャのポインタ
	/* メンバ変数 */
	CScene2D					*m_apScene2D[RESULTUITYPE::R_UI_MAX];		// シーン2Dのポインタ
	D3DXVECTOR3					m_UV[RESULTUITYPE::R_UI_MAX];				// UV
};
#endif