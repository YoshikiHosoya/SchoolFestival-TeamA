//=============================================================================
//
// �|�C���g���C�g���� [pointlight.h]
// Author : Fujiwara Masato
//
//=============================================================================
#ifndef _POINTLIGHT_H_
#define _POINTLIGHT_H_

#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define POINTLIGHT_MAX (3)

// ------------------------------------------
//
// �N���X
//
// ------------------------------------------
class CPointLight
{
public:
	/* �֐� */
	CPointLight();
	~CPointLight();
	void Init(void);
	void Uninit(void);
	void Update(void);
	static CPointLight * Create(void);	// �쐬
	static void SetPointLight(void);
protected:

private:
	// ���C�g���
	D3DLIGHT9 m_light[POINTLIGHT_MAX];

	// �J���[
	D3DXCOLOR m_col[POINTLIGHT_MAX] =
	{
		D3DXCOLOR(0.0f,1.0f,1.0f,1.0f),
		D3DXCOLOR(1.0f,0.0f,1.0f,1.0f),
		D3DXCOLOR(1.0f,1.0f,0.0f,1.0f),
	};

	// ���̈ʒu
	D3DXVECTOR3 m_pos[POINTLIGHT_MAX] =
	{
		D3DXVECTOR3(-400.0f, 100.0f, -400.0f),
		D3DXVECTOR3(0.0f, 100.0f, -400.0f),
		D3DXVECTOR3(400.0f, 100.0f, -400.0f),
	};

	// ���͈̔�
	float m_range[POINTLIGHT_MAX] =
	{
		 400.0f,
		 400.0f,
		 400.0f
	};

	// �f�o�C�X
	static LPDIRECT3DDEVICE9 m_pDevice;
};

#endif
