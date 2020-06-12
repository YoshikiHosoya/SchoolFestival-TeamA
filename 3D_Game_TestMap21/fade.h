// =====================================================================================================================================================================
//
// フェードの処理 [fade.h]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#ifndef _FADE_H_
#define _FADE_H_

#define _CRT_SECURE_NO_WARNINGS

#include "main.h"			// インクルードファイル
#include "manager.h"

// =====================================================================================================================================================================
// フェードクラス
// =====================================================================================================================================================================
class CFade
{
public:

	// フェードの状態
	enum FADE
	{
		FADE_NONE = -1,
		FADE_IN,			// フェードイン処理
		FADE_OUT,			// フェードアウト処理
		FADE_MAX
	};

	CFade();				// コンストラクタ
	~CFade();				// デストラクタ

	/* メンバ関数 */
	void Init();					// 初期化
	void Uninit();					// 終了
	void Update();					// 更新
	void Draw();					// 描画

	/* 静的メンバ関数 */
	static	CFade		*Create();								// ゲームクラスの生成
	static	void		SetFade(CManager::MODE modeNext);		// フェードの設定
	static	FADE		GetFadeState()		{ return m_fade; };	// フェードの状態取得

private:
	/* メンバ関数 */
	void MakeVertexFade(LPDIRECT3DDEVICE9 pDevice);				// 頂点の作成
	/* メンバ変数 */
	LPDIRECT3DTEXTURE9				m_pTextureFade = NULL;		// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9			m_pVtxBuffFade = NULL;		// 頂点バッファへのポインタ
	static	FADE					m_fade;						// フェード状態
	static	CManager::MODE			m_modeNext;					// 次の画面（モード）
	static	D3DXCOLOR				m_colorFade;				// フェード色

};
#endif