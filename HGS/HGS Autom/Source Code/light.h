//-----------------------------------------------------------------------------
//
// ���C�g���� [light.h]
// Author : Yoshiki Hosoya
//
//-----------------------------------------------------------------------------
#ifndef _LIGHT_H_
#define _LIGHT_H_

#define _CRT_SECURE_NO_WARNINGS

//-----------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------
#include "main.h"

//-----------------------------------------------------------------------------
// �}�N��
//-----------------------------------------------------------------------------
#define MAX_LIGHT (3)
//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CLight
{
public:
	CLight();
	~CLight();
	void Init();								//������
	void Uninit();								//�I��
	void Update();								//�X�V
	void ShowLightInfo();						//imgui ���C�g���\��
	D3DXVECTOR3 GetLightDir(int nLightNum);		//���C�g�̕����擾�@�����̃��C�g��Ⴄ
	D3DXCOLOR GetLightColor(int nLightNum);		//���C�g�̕����擾�@�����̃��C�g��Ⴄ���ł���

private:
	D3DLIGHT9 m_aLight[MAX_LIGHT];		//���C�g
	D3DXVECTOR3 m_vecDir[MAX_LIGHT];	//���C�g�̌���
	D3DXCOLOR m_LightCol[MAX_LIGHT];	//���C�g�̌���

};

#endif