// =====================================================================================================================================================================
//
// ポーズUIの処理 [pauseUI.h]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#ifndef _PAUSEUI_H_
#define _PAUSEUI_H_

#include "main.h"
#include "scene2D.h"

// =====================================================================================================================================================================
// ポーズUIクラス
// =====================================================================================================================================================================
class CPauseUI
{
public:

	// UIの種類
	enum PAUSEUITYPE
	{
		P_UI_NONE = -1,
		P_UI_RESUME,							// 再開
		P_UI_RESTART,							// リスタート
		P_UI_TITLE,								// タイトル
		P_UI_LOGO,								// ポーズロゴ
		P_UI_MAX,
	};

	CPauseUI();									// コンストラクタ
	~CPauseUI();								// デストラクタ

	/* メンバ関数 */
	void				Init();					// 初期化
	void				Uninit();				// 終了
	void				Update();				// 更新
	void				Draw();					// 描画

	/* 静的メンバ関数 */
	static  CPauseUI	*Create();				// ポーズUIの生成
	static	HRESULT		Load();					// ロード
	static	void		Unload();				// アンロード

private:
	/* メンバ関数 */
	void						UIConfig(int nCnt);						// UIの内容設定
	/* 静的メンバ変数 */
	static	LPDIRECT3DTEXTURE9	m_apTexture[PAUSEUITYPE::P_UI_MAX];		// 共有テクスチャのポインタ
	static	int					m_nNum;									// アイコン移動のナンバー
	/* メンバ変数 */
	CScene2D					*m_apScene2D[PAUSEUITYPE::P_UI_MAX];	// シーンのポインタ
	D3DXCOLOR					m_aCol[PAUSEUITYPE::P_UI_MAX];			// 色
	int							m_nTime;								// 点滅時間
	bool						m_bFlash;								// 点滅切り替え
};
#endif
