//=============================================================================
//
// ポイントライト処理 [pointlight.h]
// Author : Fujiwara Masato
//
//=============================================================================
#ifndef _POINTLIGHT_H_
#define _POINTLIGHT_H_

#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define POINTLIGHT_MAX (3)

// ------------------------------------------
//
// クラス
//
// ------------------------------------------
class CPointLight
{
public:
	/* 関数 */
	CPointLight();
	~CPointLight();
	void Init(void);
	void Uninit(void);
	void Update(void);
	static CPointLight * Create(void);	// 作成
	static void SetPointLight(void);
protected:

private:
	// ライト情報
	D3DLIGHT9 m_light[POINTLIGHT_MAX];

	// カラー
	D3DXCOLOR m_col[POINTLIGHT_MAX] =
	{
		D3DXCOLOR(0.0f,1.0f,1.0f,1.0f),
		D3DXCOLOR(1.0f,0.0f,1.0f,1.0f),
		D3DXCOLOR(1.0f,1.0f,0.0f,1.0f),
	};

	// 光の位置
	D3DXVECTOR3 m_pos[POINTLIGHT_MAX] =
	{
		D3DXVECTOR3(-400.0f, 100.0f, -400.0f),
		D3DXVECTOR3(0.0f, 100.0f, -400.0f),
		D3DXVECTOR3(400.0f, 100.0f, -400.0f),
	};

	// 光の範囲
	float m_range[POINTLIGHT_MAX] =
	{
		 400.0f,
		 400.0f,
		 400.0f
	};

	// デバイス
	static LPDIRECT3DDEVICE9 m_pDevice;
};

#endif
