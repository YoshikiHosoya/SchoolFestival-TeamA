// =====================================================================================================================================================================
//
// タイトルUIの処理 [titleUI.h]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#ifndef _TITLEUI_H_
#define _TITLEUI_H_

#include "main.h"
#include "scene2D.h"
#include "title.h"

// =====================================================================================================================================================================
// タイトルUIクラス
// =====================================================================================================================================================================
class CTitleUI : public CScene2D
{
public:

	// UIの種類
	enum TYTLEUITYPE
	{
		T_UI_NONE = -1,
		T_UI_LOGO,								// タイトルロゴ
		T_UI_ENTER,								// エンター
		T_UI_MAX,
	};

	CTitleUI();									// コンストラクタ
	~CTitleUI();								// デストラクタ

	/* メンバ関数 */
	void				Init();					// 初期化
	void				Uninit();				// 終了
	void				Update();				// 更新
	void				Draw();					// 描画

	/* 静的メンバ関数 */
	static  CTitleUI	*Create();				// タイトルUIの生成
	static	HRESULT		Load();					// ロード
	static	void		Unload();				// アンロード

private:
	/* メンバ関数 */
	void						UIConfig(int nCnt);						// UIの内容設定
	/* 静的メンバ変数 */
	static	LPDIRECT3DTEXTURE9	m_apTexture[TYTLEUITYPE::T_UI_MAX];		// 共有テクスチャのポインタ
	static	int					m_nNum;									// アイコン移動のナンバー
	/* メンバ変数 */
	CScene2D					*m_apScene2D[TYTLEUITYPE::T_UI_MAX];	// シーン2Dのポインタ
	D3DXCOLOR					m_aCol[TYTLEUITYPE::T_UI_MAX];			// 色
	int							m_nTime;								// 点滅時間
	bool						m_bFlash;								// 点滅切り替え
};
#endif
