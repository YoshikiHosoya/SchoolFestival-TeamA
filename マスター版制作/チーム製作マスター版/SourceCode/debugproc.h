#pragma once
#ifndef _DEBUG_H_
#define _DEBUG_H_
#include "main.h"
//レンダリングクラス
class CDebugProc
{
public:


	CDebugProc();
	~CDebugProc();
	void Init(void);
	void Uninit(void);
	static void Print_Left(char*fmt, ...);
	static void Print_Right(char*fmt, ...);
	static void Draw(void);
	static void ResetStr() { m_aStr_Left[0] = m_aStr_Right[0] = '\0'; };
private:
	static LPD3DXFONT m_pFont;
	static char m_aStr_Left[10000];
	static char m_aStr_Right[10000];
	LPDIRECT3D9 g_pD3D = NULL;				//Direc3Dオブジェクトへのポインタ

};
#endif