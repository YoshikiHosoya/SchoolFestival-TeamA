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
	enum class FADESTATE
	{
		FADESTATE_NONE = -1,		// 何もない状態
		FADESTATE_IN,			// フェードイン処理
		FADESTATE_OUT,			// フェードアウト処理
	};

	enum class FADETYPE
	{
		FADETYPE_NONE = -1,			//NONE
		FADETYPE_MODE,				//モード遷移
		FADETYPE_MAPMOVE,			//マップ遷移
		FADETYPE_STAGE_CHANGE,		//ステージ遷移
	};

	void InitFade(void);
	void UninitFade(void);
	void UpdateFade(void);
	void DrawFade(void);
	void MakeVertexFade(void);
	FADESTATE GetFadeState(void);
	static CFADE *CreateFade(void);

	template <class ID> void SetFade(FADETYPE type, ID NextID);		//フェードの設定
private:
	LPDIRECT3DTEXTURE9		m_pTextureFade = NULL;		// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffFade = NULL;		// 頂点バッファへのポインタ
	FADESTATE				m_fadeState;				// フェード状態
	FADETYPE				m_fadeType;					// フェードの種類尾
	int						m_NextID;					// 次の画面（モード）

	D3DXVECTOR3				m_pos;						// 座標
	D3DXCOLOR				m_colorFade;				// フェード色

	void ResetFadeParam();								// フェードするのに必要なパラメータ初期化
	void FadeWhiteOut();
	void FadeWipe();
	void FadeOut();
	void UpdateVertex();

};



//=============================================================================
// フェードの状態設定
// テンプレートなのでインライン関数S
//=============================================================================
template<class ID>
inline void CFADE::SetFade(FADETYPE type, ID NextID)
{
	if (m_fadeState == FADESTATE::FADESTATE_NONE)
	{
		m_fadeState = FADESTATE::FADESTATE_NONE;
		m_NextID = NextID;
		m_fadeType = type;
		ResetFadeParam();
	}
}
#endif
