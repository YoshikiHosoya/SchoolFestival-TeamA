#pragma once
//=============================================================================
//
// フェード処理 [fade.h]
//
//=============================================================================
#ifndef _FADE_H_
#define _FADE_H_
#define _CRT_SECURE_NO_WARNINGS
//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "manager.h"

class CManager;
//=============================================================================
// プロトタイプ宣言
//=============================================================================
class CFADE
{
public:
	typedef enum
	{
		FADE_NONE = 0,		// 何もない状態
		FADE_IN,			// フェードイン処理
		FADE_OUT,			// フェードアウト処理
		FADE_MAX
	} FADE;

	void InitFade(void);
	void UninitFade(void);
	void UpdateFade(void);
	void DrawFade(void);
	void MakeVertexFade(void);
	void SetFade(CManager::GAME_MODE modeNext);
	FADE GetFadeState(void);
	static CFADE *CreateFade(void);
private:
	LPDIRECT3DTEXTURE9		m_pTextureFade = NULL;		// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffFade = NULL;		// 頂点バッファへのポインタ
	FADE					m_fadeState;				// フェード状態
	CManager::GAME_MODE		m_modeNext;					// 次の画面（モード）
	D3DXCOLOR				m_colorFade;				// フェード色
};

#endif
