#pragma once
#ifndef _DEBUG_H_
#define _DEBUG_H_
#include "main.h"
//�����_�����O�N���X
class CDebugProc
{
public:


	CDebugProc();
	~CDebugProc();
	void Init(void);
	void Uninit(void);
	static void Print(char*fmt, ...);
	static void Draw(void);
private:
	static LPD3DXFONT m_pFont;
	static char m_aStr[10000];
	LPDIRECT3D9 g_pD3D = NULL;				//Direc3D�I�u�W�F�N�g�ւ̃|�C���^

};
#endif