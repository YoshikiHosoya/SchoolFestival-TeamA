#ifndef _RENDERER_H_
#define _RENDERER_H_
#include "main.h"
#include "light.h"
#include "camera.h"
#include "debugproc.h"
//class CFADE;
//�����_�����O�N���X
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
#ifdef _DEBUG
	void DrawFPS(void);
#endif
private:
	//�O���[�o���ϐ�
	LPDIRECT3D9 g_pD3D = NULL;				//Direc3D�I�u�W�F�N�g�ւ̃|�C���^
	LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;	//Direct3d�f�o�C�X�ւ̃|�C���^
	CLight *pLight;
	CCamera *pCamera;
	CDebugProc *pDebug;
};
#endif
#pragma once
