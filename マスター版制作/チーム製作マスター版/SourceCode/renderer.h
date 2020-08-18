//=========================================================================
//Author : Hosoya
//[rendere.h]
//=========================================================================
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
	void ResetRenderer();									//レンダラー設定リセット

	D3DXMATRIX *CalcInvMtx(D3DXMATRIX *pOutInvMtx,int nScreen_Width, int nScreen_Height, D3DXMATRIX* pMtxView, D3DXMATRIX* pMtxPrj);		//スクリーン座標をワールド座標に変換
	D3DXVECTOR3 *CalcScreenToWorld(D3DXVECTOR3* pout, int nScreenPos_X, int nScreenPos_Y, float fScreenPos_Z, D3DXMATRIX *pInvMtx);

	D3DXVECTOR3 &GetMinScreenPos() { return m_MinScreenPos; };
	D3DXVECTOR3 &GetMaxScreenPos() { return m_MaxScreenPos; };


	bool CheckScreenRange(D3DXVECTOR3 const &pos);
	void ScreenLimitRange(D3DXVECTOR3 & pos);

private:
	LPDIRECT3D9 m_pD3D = NULL;				//Direc3Dオブジェクトへのポインタ
	LPDIRECT3DDEVICE9 m_pD3DDevice = NULL;	//Direct3dデバイスへのポインタ
	D3DPRESENT_PARAMETERS m_d3dpp;			//プレゼンテーションパラメータ
	D3DXCOLOR m_BackColor;

	CLight *m_pLight;
	CCamera *m_pCamera;
	CDebugProc *m_pDebug;
	CFADE *m_pFade;
	bool m_bShowDebug;

	D3DXVECTOR3 m_MinScreenPos;				//画面の座標　最小値
	D3DXVECTOR3 m_MaxScreenPos;				//画面の座標　最大値

	void ResetDevice();				//デバイスリセット
	void RendererDebugInfo();		//レンダラーに関する事のデバッグ情報
	void CalcScreenPos();			//スクリーンの最大頂点と最少頂点求める
};
#endif
#pragma once
