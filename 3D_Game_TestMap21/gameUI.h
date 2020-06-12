// =====================================================================================================================================================================
//
// ゲームUIの処理 [gameUI.h]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#ifndef _GAMEUI_H_
#define _GAMEUI_H_

#include "main.h"
#include"scene2D.h"

#define LIFE_DIGIT	(2)				// 桁数

// =====================================================================================================================================================================
// 前方宣言	( ポインタだけなら使える )
// =====================================================================================================================================================================
class	CNumber;					// ナンバークラス

// =====================================================================================================================================================================
// ゲームUIクラス
// =====================================================================================================================================================================
class CGameUI : public CScene2D
{
public:

	// UIの種類
	enum GAMEUITYPE
	{
		G_UI_NONE = -1,
		G_UI_ICON,								// アイコン
		G_UI_STOP_MIN,							// 最小値
		G_UI_START_MAX,							// 最大値
		G_UI_GAGE,								// ゲージ
		G_UI_TRIANGLE,							// 斗和三角
		G_UI_MAX,
	};

	CGameUI();										// コンストラクタ
	~CGameUI();										// デストラクタ

	/* メンバ関数 */
	void				Init();						// 初期化
	void				Uninit();					// 終了
	void				Update();					// 更新
	void				Draw();						// 描画

	/* 静的メンバ関数 */
	static	void		SetLife(int nLife);			// 体力の設定
	static  CGameUI		*Create();					// ゲームUIの生成
	static	HRESULT		Load();						// ロード				( 読み込み )
	static	void		Unload();					// アンロード			( 破棄 )
	static	void		RecoveryGage();				// ゲージを回復

private:
	/* メンバ関数 */
	void						MoveTriangle(void);							// 三角の移動処理
	/* 静的メンバ変数 */
	static	LPDIRECT3DTEXTURE9	m_apTexture[GAMEUITYPE::G_UI_MAX];			// 共有テクスチャのポインタ
	static CNumber				*m_apNumber[LIFE_DIGIT];					// ナンバーのポインタ
	static	D3DXVECTOR2			m_UVsize;									// UVサイズ
	static	bool				m_bGageDecrease;							// ゲージが減少しているか
	/* メンバ変数 */
	CScene2D					*m_apScene2D[GAMEUITYPE::G_UI_MAX];			// シーン2Dのポインタ
	D3DXVECTOR3					m_UV[GAMEUITYPE::G_UI_MAX];					// 移動
	D3DXCOLOR					m_aCol[GAMEUITYPE::G_UI_MAX];				// 色
	float						m_fTriangleMoveX;							// 三角の横移動
};
#endif