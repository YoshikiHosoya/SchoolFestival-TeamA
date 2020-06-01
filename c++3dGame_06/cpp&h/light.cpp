//=============================================================================
//
// ���C�g���� [light.cpp]
// Author : Fujiwara Masato
//
//=============================================================================
#include "light.h"
#include "manager.h"
#include "debugproc.h"

// ------------------------------------------
//
// �ÓI�ϐ��錾
//
// ------------------------------------------
LPDIRECT3DDEVICE9 CLight::m_pDevice = NULL;

// ----------------------------------------
// �R���X�g���N�^����
// ----------------------------------------
CLight::CLight()
{
	m_nCount = 0;
	m_pDevice = CManager::GetRenderer()->GetDevice();	// �f�o�C�X�̎擾
	// �J�E���g���C�g
	for (int nCntLight = 0; nCntLight < LIGHT_MAX; nCntLight++)
	{
		// ���C�g���N���A����
		ZeroMemory(&m_light[nCntLight], sizeof(D3DLIGHT9));

		// ���C�g�̎�ނ�ݒ�
		m_light[nCntLight].Type = m_lightType[nCntLight];

		// ���C�g�̊g�U����ݒ�
		m_light[nCntLight].Diffuse = m_col[nCntLight];

		if (m_light[nCntLight].Type == D3DLIGHT_DIRECTIONAL)
		{
			// ���C�g�̕����̐ݒ�
			D3DXVec3Normalize(&m_VecDir[nCntLight], &m_VecDir[nCntLight]);
			m_light[nCntLight].Direction = m_VecDir[nCntLight];
		}

		else if (m_light[nCntLight].Type == D3DLIGHT_POINT)
		{
			// ���C�g�̍��W��ݒ�
			m_light[nCntLight].Position = m_pos[m_nCount];

			// ���C�g�̌��͈̔͂�ݒ�
			m_light[nCntLight].Range = m_range[m_nCount];

			m_nCount++;
		}

		// ���C�g��ݒ肷��
		m_pDevice->SetLight(nCntLight, &m_light[nCntLight]);

		if (m_light[nCntLight].Type == D3DLIGHT_POINT)
		{
			//// ���C�g�̈��̋t����
			//m_light[nCntLight].Attenuation0 = 0.125f;

			//// .125�݂̂̋t����
			//m_light[nCntLight].Attenuation1 = 0.0f;

			//// ���C�g�̋t��������
			//m_light[nCntLight].Attenuation2 = 0.0f;

			// ���C�g�̈��̋t����
			m_light[nCntLight].Attenuation0 = 0.0f;

			// .125�݂̂̋t����
			m_light[nCntLight].Attenuation1 = 1.0f;

			// ���C�g�̋t��������
			m_light[nCntLight].Attenuation2 = 0.0f;
		}

		// ���C�g��L���ɂ���
		m_pDevice->LightEnable(nCntLight, TRUE);
	}
}

// ----------------------------------------
// �f�X�g���N�^����
// ----------------------------------------
CLight::~CLight()
{
}

// ----------------------------------------
// ����������
// ----------------------------------------
void CLight::Init(void)
{
}

// ----------------------------------------
// �I������
// ----------------------------------------
void CLight::Uninit(void)
{
}

// ----------------------------------------
// �X�V����
// ----------------------------------------
void CLight::Update(void)
{
	for (int nCnt = 4; nCnt < LIGHT_MAX; nCnt++)
	{
		CDebugproc::Print("���C�g ���W		: %.2f,%.2f,%.2f \n", m_light[nCnt].Position.x, m_light[nCnt].Position.y, m_light[nCnt].Position.z);

		CDebugproc::Print("���C�g �͈�		: %.2f \n", m_light[nCnt].Range);
	}

	//SetLight();
}

// ----------------------------------------
// ��������
// ----------------------------------------
CLight * CLight::Create(void)
{
	// �ϐ��錾
	CLight * pLight;
	// �������̐���(����->��{�N���X,��->�h���N���X)
	pLight = new CLight();
	// ����������
	pLight->Init();
	// ���������I�u�W�F�N�g��Ԃ�
	return pLight;
}

// ----------------------------------------
// ���C�g�̐ݒ�
// ----------------------------------------
void CLight::SetLight(void)
{
	if (CManager::GetMode() == CManager::MODE_TITLE)
	{
		// ���C�g��1�Ԃ�L���ɂ���
		m_pDevice->LightEnable(0, FALSE);
		m_pDevice->LightEnable(1, TRUE);
		m_pDevice->LightEnable(2, FALSE);
		m_pDevice->LightEnable(3, FALSE);

		m_pDevice->LightEnable(4, FALSE);
		m_pDevice->LightEnable(5, FALSE);
		m_pDevice->LightEnable(6, FALSE);
	}

	else if (CManager::GetMode() == CManager::MODE_GAME)
	{
		// ���C�g��L���ɂ���
		m_pDevice->LightEnable(0, TRUE);
		m_pDevice->LightEnable(1, TRUE);
		m_pDevice->LightEnable(2, TRUE);
		m_pDevice->LightEnable(3, TRUE);

		m_pDevice->LightEnable(4, TRUE);
		m_pDevice->LightEnable(5, TRUE);
		m_pDevice->LightEnable(6, TRUE);
	}
}
