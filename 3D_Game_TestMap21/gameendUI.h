// =====================================================================================================================================================================
//
// ゲームエンドUIの処理 [gameendtUI.h]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#ifndef _GAMEENDUI_H_
#define _GAMEENDUI_H_

#include "main.h"
#include"scene2D.h"

// =====================================================================================================================================================================
// ゲームエンドUIクラス
// =====================================================================================================================================================================
class CGameEndUI : public CScene2D
{
public:

	// UIの種類
	enum GAMEENDUITYPE
	{
		GE_UI_NONE = -1,
		GE_UI_HAZE,				// もや
		GE_UI_CLEAR,			// クリア
		GE_UI_OVER,				// ゲームオーバー
		GE_UI_MAX,
	};

	CGameEndUI();										// コンストラクタ
	~CGameEndUI();										// デストラクタ

	/* メンバ関数 */
	void						Init();					// 初期化
	void						Uninit();				// 終了
	void						Update();				// 更新
	void						Draw();					// 描画

	/* 静的メンバ関数 */
	static  CGameEndUI			*Create();				// ゲームエンドUIの生成
	static	HRESULT				Load();					// ロード
	static	void				Unload();				// アンロード

private:
	/* 静的メンバ変数 */
	static	LPDIRECT3DTEXTURE9	m_apTexture[GAMEENDUITYPE::GE_UI_MAX];		// 共有テクスチャのポインタ
	/* メンバ変数 */
	CScene2D					*m_apScene2D[GAMEENDUITYPE::GE_UI_MAX];		// シーン2Dのポインタ
	D3DXVECTOR3					m_UV[GAMEENDUITYPE::GE_UI_MAX];				// UV
};
#endif