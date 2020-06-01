//=============================================================================
//
// �|�C���g���C�g���� [pointlight.cpp]
// Author : Fujiwara Masato
//
//=============================================================================
#include "pointlight.h"
#include "manager.h"
#include "debugproc.h"
// ------------------------------------------
//
// �ÓI�ϐ��錾
//
// ------------------------------------------
LPDIRECT3DDEVICE9 CPointLight::m_pDevice = NULL;

// ----------------------------------------
// �R���X�g���N�^����
// ----------------------------------------
CPointLight::CPointLight()
{
	// �f�o�C�X�̎擾
	m_pDevice = CManager::GetRenderer()->GetDevice();
	// �S�Ẵ|�C���g���C�g�̐ݒ�
	for (int nCntLight = 0; nCntLight < POINTLIGHT_MAX; nCntLight++)
	{
		// ���C�g���N���A����
		ZeroMemory(&m_light[nCntLight], sizeof(D3DLIGHT9));

		// ���C�g�̎�ނ�ݒ�
		m_light[nCntLight].Type = D3DLIGHT_POINT;

		// ���C�g�̊g�U����ݒ�
		m_light[nCntLight].Diffuse = m_col[nCntLight];

		// ���C�g�̍��W��ݒ�
		m_light[nCntLight].Position = m_pos[nCntLight];

		// ���C�g�̌��͈̔͂�ݒ�
		m_light[nCntLight].Range = m_range[nCntLight];

		// ���C�g�̐ݒ�
		m_pDevice->SetLight(nCntLight, &m_light[nCntLight]);

		// ���C�g�̈��̋t����
		m_light[nCntLight].Attenuation0 = 0.0f;

		// .125�݂̂̋t����
		m_light[nCntLight].Attenuation1 = 0.125f;

		// ���C�g�̋t��������
		m_light[nCntLight].Attenuation2 = 0.0f;

		// ���C�g��L���ɂ���
		m_pDevice->LightEnable(nCntLight, TRUE);
	}
}

// ----------------------------------------
// �f�X�g���N�^����
// ----------------------------------------
CPointLight::~CPointLight()
{
}

// ----------------------------------------
// ����������
// ----------------------------------------
void CPointLight::Init(void)
{
}

// ----------------------------------------
// �I������
// ----------------------------------------
void CPointLight::Uninit(void)
{
}

// ----------------------------------------
// �X�V����
// ----------------------------------------
void CPointLight::Update(void)
{
	for (int nCnt = 0; nCnt < POINTLIGHT_MAX; nCnt++)
	{
		CDebugproc::Print("���C�g ���W		: %.2f,%.2f,%.2f\n", m_pos[nCnt].x, m_pos[nCnt].y, m_pos[nCnt].z);

		CDebugproc::Print("���C�g �͈�		: %.2f \n", m_range[nCnt]);
	}
}

// ----------------------------------------
// ��������
// ----------------------------------------
CPointLight * CPointLight::Create(void)
{
	// �ϐ��錾
	CPointLight * pLight;
	// �������̐���(����->��{�N���X,��->�h���N���X)
	pLight = new CPointLight();
	// ����������
	pLight->Init();
	// ���������I�u�W�F�N�g��Ԃ�
	return pLight;
}

// ----------------------------------------
// ���C�g�̐ݒ�
// ----------------------------------------
void CPointLight::SetPointLight(void)
{
	if (CManager::GetMode() == CManager::MODE_TITLE)
	{
		for (int nCntLight = 0; nCntLight < POINTLIGHT_MAX; nCntLight++)
		{
			// ���C�g��L���ɂ���
			m_pDevice->LightEnable(nCntLight, TRUE);
		}
	}

	else if (CManager::GetMode() == CManager::MODE_GAME)
	{
		for (int nCntLight = 0; nCntLight < POINTLIGHT_MAX; nCntLight++)
		{
			// ���C�g��L���ɂ���
			m_pDevice->LightEnable(nCntLight, TRUE);
		}
	}
}
