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
	void ResetRenderer();									//�����_���[�ݒ胊�Z�b�g

	D3DXMATRIX *CalcInvMtx(D3DXMATRIX *pOutInvMtx,int nScreen_Width, int nScreen_Height, D3DXMATRIX* pMtxView, D3DXMATRIX* pMtxPrj);		//�X�N���[�����W�����[���h���W�ɕϊ�
	D3DXVECTOR3 *CalcScreenToWorld(D3DXVECTOR3* pout, int nScreenPos_X, int nScreenPos_Y, float fScreenPos_Z, D3DXMATRIX *pInvMtx);

	D3DXVECTOR3 &GetMinScreenPos() { return m_MinScreenPos; };
	D3DXVECTOR3 &GetMaxScreenPos() { return m_MaxScreenPos; };


	bool CheckScreenRange(D3DXVECTOR3 const &pos);
	void ScreenLimitRange(D3DXVECTOR3 & pos);

private:
	LPDIRECT3D9 m_pD3D = NULL;				//Direc3D�I�u�W�F�N�g�ւ̃|�C���^
	LPDIRECT3DDEVICE9 m_pD3DDevice = NULL;	//Direct3d�f�o�C�X�ւ̃|�C���^
	D3DPRESENT_PARAMETERS m_d3dpp;			//�v���[���e�[�V�����p�����[�^
	D3DXCOLOR m_BackColor;

	CLight *m_pLight;
	CCamera *m_pCamera;
	CDebugProc *m_pDebug;
	CFADE *m_pFade;
	bool m_bShowDebug;

	D3DXVECTOR3 m_MinScreenPos;				//��ʂ̍��W�@�ŏ��l
	D3DXVECTOR3 m_MaxScreenPos;				//��ʂ̍��W�@�ő�l

	void ResetDevice();				//�f�o�C�X���Z�b�g
	void RendererDebugInfo();		//�����_���[�Ɋւ��鎖�̃f�o�b�O���
	void CalcScreenPos();			//�X�N���[���̍ő咸�_�ƍŏ����_���߂�
};
#endif
#pragma once
