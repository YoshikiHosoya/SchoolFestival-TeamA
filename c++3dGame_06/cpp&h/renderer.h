// ------------------------------------------
//
// レンダリング処理の説明[renderer.h]
// Author : Fujiwara Masato
//
// ------------------------------------------

#ifndef _RENDERER_H_
#define _RENDERER_H_	 // ファイル名を基準を決める

// ------------------------------------------
//
// インクルードファイル
//
// ------------------------------------------
#include "main.h"

// ------------------------------------------
//
// マクロ関数
//
// ------------------------------------------

// ------------------------------------------
//
// 前方宣言
//
// ------------------------------------------
class CDebugproc;
class CCamera;
class CLight;
class CPointLight;

// ------------------------------------------
//
// クラス
//
// ------------------------------------------
class CRenderer
{
public:
	/* 関数 */
	CRenderer();
	~CRenderer();
	HRESULT  Init(HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	// 情報取得
	LPDIRECT3DDEVICE9 GetDevice(void);	// デバイス
	static CCamera * GetCamera(void);			// カメラ
	CLight * GetLight(void);			// ライト
protected:

private:
	/* 変数 */
	LPDIRECT3D9 m_pD3D;				// Direct3Dオブジェクトのポインタ
	LPDIRECT3DDEVICE9 m_pDevice;	// Direct3Dデバイスのポインタ
	static CCamera * m_pCamera;		// カメラ情報
	CLight * m_pLight;				// ライト情報
	CPointLight * m_pPointLight;	// ライト情報

#ifdef _DEBUG
	static CDebugproc * m_debugproc;		// デバッグ表示
	void DrawFPS(void);				// FPS関数
#endif
};

#endif // !_RENDERER_H_