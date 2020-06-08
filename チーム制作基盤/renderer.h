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

	CRenderer();
	~CRenderer();
	HRESULT Init(HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	LPDIRECT3DDEVICE9 GetDevice(void);
	CFADE *GetFade(void);
#ifdef _DEBUG
	void DrawFPS(void);
#endif
private:
	//グローバル変数
	LPDIRECT3D9 g_pD3D = NULL;				//Direc3Dオブジェクトへのポインタ
	LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;	//Direct3dデバイスへのポインタ
	D3DPRESENT_PARAMETERS m_d3dpp;			//プレゼンテーションパラメータ

	CLight *pLight;
	CCamera *pCamera;
	CDebugProc *pDebug;
	CFADE *pFade;
	void ResetDevice();		//デバイスリセット
};
#endif
#pragma once
