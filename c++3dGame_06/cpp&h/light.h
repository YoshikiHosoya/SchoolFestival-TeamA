//=============================================================================
//
// ライト処理 [light.h]
// Author : Fujiwara Masato
//
//=============================================================================
#ifndef _LIGHT_H_
#define _LIGHT_H_

#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define LIGHT_MAX (7)
#define LIGHT_MAX_DIRECTIONAL (4)
#define LIGHT_MAX_POINT (3)

// ------------------------------------------
//
// クラス
//
// ------------------------------------------
class CLight
{
public:
	/* 関数 */
	CLight();
	~CLight();
	void Init(void);
	void Uninit(void);
	void Update(void);
	static CLight * Create(void);	// 作成
	static void SetLight(void);
protected:

private:
	// ライト情報
	D3DLIGHT9 m_light[LIGHT_MAX];

	// 拡散光の色
	D3DXCOLOR m_col[LIGHT_MAX] =
	{
		/*D3DXCOLOR(0.6f,0.6f,0.6f,1.0f),
		D3DXCOLOR(0.5f,0.5f,0.5f,1.0f),
		D3DXCOLOR(0.7f,0.7f,0.7f,1.0f),
		D3DXCOLOR(0.5f,0.5f,0.5f,1.0f),*/

		D3DXCOLOR(0.2f,0.2f,0.2f,1.0f),
		D3DXCOLOR(0.2f,0.2f,0.2f,1.0f),
		D3DXCOLOR(0.2f,0.2f,0.2f,1.0f),
		D3DXCOLOR(0.2f,0.2f,0.2f,1.0f),

		// ポイントライトのカラー
		D3DXCOLOR(1.0f,0.0f,0.0f,1.0f),
		D3DXCOLOR(1.0f,0.0f,0.0f,1.0f),
		D3DXCOLOR(1.0f,0.0f,0.0f,1.0f),

		/*D3DXCOLOR(1.0f,1.0f,0.0f,1.0f),
		D3DXCOLOR(1.0f,0.0f,1.0f,1.0f),
		D3DXCOLOR(0.0f,1.0f,1.0f,1.0f),*/
	};

	// 光の方向
	D3DXVECTOR3 m_VecDir[LIGHT_MAX_DIRECTIONAL] =// 方向
	{
		D3DXVECTOR3(-1.0f,-0.2f,-1.0f),	// メインライト
		D3DXVECTOR3(-0.5f, -0.5, 0.0f),	// サブ１
		D3DXVECTOR3(0.5f, -0.5f, 0.5f),	// サブ２
		D3DXVECTOR3(0.0f, 0.5f, 0.0f),	// サブ２
	};

	// 点光源の位置
	D3DXVECTOR3 m_pos[LIGHT_MAX_POINT] =
	{
		D3DXVECTOR3(-1000.0f,	230.0f,		-620.0f),
		D3DXVECTOR3(0.0f,		230.0f,		-620.0f),
		D3DXVECTOR3(1250.0f,	230.0f,		-620.0f),
	};

	// 光の範囲
	float m_range[LIGHT_MAX_POINT] =
	{
		350.0f,
		350.0f,
		350.0f,
	};

	// ライトの種類
	D3DLIGHTTYPE m_lightType[LIGHT_MAX] =
	{
		D3DLIGHT_DIRECTIONAL,
		D3DLIGHT_DIRECTIONAL,
		D3DLIGHT_DIRECTIONAL,
		D3DLIGHT_DIRECTIONAL,
		D3DLIGHT_POINT,
		D3DLIGHT_POINT,
		D3DLIGHT_POINT,
	};

	// デバイス
	static LPDIRECT3DDEVICE9 m_pDevice;
	// 設定で使うカウント
	int m_nCount;
};

#endif
