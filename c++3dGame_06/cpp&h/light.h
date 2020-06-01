//=============================================================================
//
// ���C�g���� [light.h]
// Author : Fujiwara Masato
//
//=============================================================================
#ifndef _LIGHT_H_
#define _LIGHT_H_

#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define LIGHT_MAX (7)
#define LIGHT_MAX_DIRECTIONAL (4)
#define LIGHT_MAX_POINT (3)

// ------------------------------------------
//
// �N���X
//
// ------------------------------------------
class CLight
{
public:
	/* �֐� */
	CLight();
	~CLight();
	void Init(void);
	void Uninit(void);
	void Update(void);
	static CLight * Create(void);	// �쐬
	static void SetLight(void);
protected:

private:
	// ���C�g���
	D3DLIGHT9 m_light[LIGHT_MAX];

	// �g�U���̐F
	D3DXCOLOR m_col[LIGHT_MAX] =
	{
		/*D3DXCOLOR(0.6f,0.6f,0.6f,1.0f),
		D3DXCOLOR(0.5f,0.5f,0.5f,1.0f),
		D3DXCOLOR(0.7f,0.7f,0.7f,1.0f),
		D3DXCOLOR(0.5f,0.5f,0.5f,1.0f),*/

		D3DXCOLOR(0.2f,0.2f,0.2f,1.0f),
		D3DXCOLOR(0.2f,0.2f,0.2f,1.0f),
		D3DXCOLOR(0.2f,0.2f,0.2f,1.0f),
		D3DXCOLOR(0.2f,0.2f,0.2f,1.0f),

		// �|�C���g���C�g�̃J���[
		D3DXCOLOR(1.0f,0.0f,0.0f,1.0f),
		D3DXCOLOR(1.0f,0.0f,0.0f,1.0f),
		D3DXCOLOR(1.0f,0.0f,0.0f,1.0f),

		/*D3DXCOLOR(1.0f,1.0f,0.0f,1.0f),
		D3DXCOLOR(1.0f,0.0f,1.0f,1.0f),
		D3DXCOLOR(0.0f,1.0f,1.0f,1.0f),*/
	};

	// ���̕���
	D3DXVECTOR3 m_VecDir[LIGHT_MAX_DIRECTIONAL] =// ����
	{
		D3DXVECTOR3(-1.0f,-0.2f,-1.0f),	// ���C�����C�g
		D3DXVECTOR3(-0.5f, -0.5, 0.0f),	// �T�u�P
		D3DXVECTOR3(0.5f, -0.5f, 0.5f),	// �T�u�Q
		D3DXVECTOR3(0.0f, 0.5f, 0.0f),	// �T�u�Q
	};

	// �_�����̈ʒu
	D3DXVECTOR3 m_pos[LIGHT_MAX_POINT] =
	{
		D3DXVECTOR3(-1000.0f,	230.0f,		-620.0f),
		D3DXVECTOR3(0.0f,		230.0f,		-620.0f),
		D3DXVECTOR3(1250.0f,	230.0f,		-620.0f),
	};

	// ���͈̔�
	float m_range[LIGHT_MAX_POINT] =
	{
		350.0f,
		350.0f,
		350.0f,
	};

	// ���C�g�̎��
	D3DLIGHTTYPE m_lightType[LIGHT_MAX] =
	{
		D3DLIGHT_DIRECTIONAL,
		D3DLIGHT_DIRECTIONAL,
		D3DLIGHT_DIRECTIONAL,
		D3DLIGHT_DIRECTIONAL,
		D3DLIGHT_POINT,
		D3DLIGHT_POINT,
		D3DLIGHT_POINT,
	};

	// �f�o�C�X
	static LPDIRECT3DDEVICE9 m_pDevice;
	// �ݒ�Ŏg���J�E���g
	int m_nCount;
};

#endif
