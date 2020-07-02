#ifndef _RENDERER_H_
#define _RENDERER_H_
#include "main.h"
#include "light.h"
#include "camera.h"
#include "debugproc.h"
class CFADE;
//レンダリングクラス
class CRenderer
{
public:
	enum RENDERER_COMMAND
	{
		RENDERER_LIGHTING_ON,				//ライティングON
		RENDERER_LIGHTING_OFF,				//ライティングOFF
		RENDERER_CULLING_NONE,				//カリングしない
		RENDERER_CULLING_CCW,				//裏をカリング
		RENDERER_CULLING_CW,				//表をカリング
		RENDERER_ALPHABLEND_ADD,			//加算合成
		RENDERER_ALPHABLEND_SUB,			//減算合成
		REDNERER_ALPHABLEND_DEFAULT,		//通常状態
		RENDERER_ZTEST_OFF,					//Zテスト無効
		RENDERER_ZTEST_OFF_ZWRITING_ON,		//Zテスト無効でZライティング有効
		RENDERER_ZTEST_ON_ZWRITING_OFF,		//Zテスト有効でZライティング無効
		RENDERER_ZTEST_DEFAULT,				//Zテスト通常状態
		RENDERER_FOG_ON,					//フォグON
		RENDERER_FOG_OFF,					//フォグOFF
		RENDERER_WIRE_ON,					//ワイヤーON
		RENDERER_WIRE_OFF,					//ワイヤーOFF
	};


	CRenderer();
	~CRenderer();
	HRESULT Init(HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	LPDIRECT3DDEVICE9 GetDevice(void);
	CFADE *GetFade(void);
	CCamera *GetCamera();
	void SetShowDebug() { m_bShowDebug ^= 1; };

	void SetRendererCommand(RENDERER_COMMAND Command);		//レンダラー設定 ショートカット
	void ResetRenderer();
#ifdef _DEBUG
	void DrawFPS(void);
#endif
private:
	LPDIRECT3D9 m_pD3D = NULL;				//Direc3Dオブジェクトへのポインタ
	LPDIRECT3DDEVICE9 m_pD3DDevice = NULL;	//Direct3dデバイスへのポインタ
	D3DPRESENT_PARAMETERS m_d3dpp;			//プレゼンテーションパラメータ

	CLight *m_pLight;
	CCamera *m_pCamera;
	CDebugProc *m_pDebug;
	CFADE *m_pFade;
	bool m_bShowDebug;

	void ResetDevice();		//デバイスリセット
};
#endif
#pragma once
