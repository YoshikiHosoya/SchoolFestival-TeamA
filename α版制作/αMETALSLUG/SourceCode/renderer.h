#ifndef _RENDERER_H_
#define _RENDERER_H_
#include "main.h"
#include "light.h"
#include "camera.h"
#include "debugproc.h"
class CFADE;
//�����_�����O�N���X
class CRenderer
{
public:
	enum RENDERER_COMMAND
	{
		RENDERER_LIGHTING_ON,				//���C�e�B���OON
		RENDERER_LIGHTING_OFF,				//���C�e�B���OOFF
		RENDERER_CULLING_NONE,				//�J�����O���Ȃ�
		RENDERER_CULLING_CCW,				//�����J�����O
		RENDERER_CULLING_CW,				//�\���J�����O
		RENDERER_ALPHABLEND_ADD,			//���Z����
		RENDERER_ALPHABLEND_SUB,			//���Z����
		REDNERER_ALPHABLEND_DEFAULT,		//�ʏ���
		RENDERER_ZTEST_OFF,					//Z�e�X�g����
		RENDERER_ZTEST_OFF_ZWRITING_ON,		//Z�e�X�g������Z���C�e�B���O�L��
		RENDERER_ZTEST_ON_ZWRITING_OFF,		//Z�e�X�g�L����Z���C�e�B���O����
		RENDERER_ZTEST_DEFAULT,				//Z�e�X�g�ʏ���
		RENDERER_FOG_ON,					//�t�H�OON
		RENDERER_FOG_OFF,					//�t�H�OOFF
		RENDERER_WIRE_ON,					//���C���[ON
		RENDERER_WIRE_OFF,					//���C���[OFF
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

	void SetRendererCommand(RENDERER_COMMAND Command);		//�����_���[�ݒ� �V���[�g�J�b�g
	void ResetRenderer();
#ifdef _DEBUG
	void DrawFPS(void);
#endif
private:
	LPDIRECT3D9 m_pD3D = NULL;				//Direc3D�I�u�W�F�N�g�ւ̃|�C���^
	LPDIRECT3DDEVICE9 m_pD3DDevice = NULL;	//Direct3d�f�o�C�X�ւ̃|�C���^
	D3DPRESENT_PARAMETERS m_d3dpp;			//�v���[���e�[�V�����p�����[�^

	CLight *m_pLight;
	CCamera *m_pCamera;
	CDebugProc *m_pDebug;
	CFADE *m_pFade;
	bool m_bShowDebug;

	void ResetDevice();		//�f�o�C�X���Z�b�g
};
#endif
#pragma once
