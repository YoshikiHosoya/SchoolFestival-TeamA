//-----------------------------------------------------------------------------
//
// ���C�g���� [light.cpp]
// Author : Yosihiki Hosoya
//
//-----------------------------------------------------------------------------
#include "light.h"
#include "manager.h"
#include "renderer.h"
//-----------------------------------------------------------------------------
// �}�N����`
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------------------------
CLight::CLight()
{
}
//-----------------------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------------------
CLight::~CLight()
{
}
//-----------------------------------------------------------------------------
// ������
//-----------------------------------------------------------------------------

void CLight::Init()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	// �f�o�C�X�̎擾

	m_vecDir[0] = D3DXVECTOR3(0.20f, -0.80f, 0.40f);
	m_vecDir[1] = D3DXVECTOR3(-0.20f, 0.80f, -0.40f);
	m_vecDir[2] = D3DXVECTOR3(0.10f, -0.10f, -0.40f);


	m_LightCol[0] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_LightCol[1] = D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f);
	m_LightCol[2] = D3DXCOLOR(0.15f, 0.15f, 0.15f, 1.0f);


	//---------------------------------------------
	// ���C�g0�̐ݒ�
	//---------------------------------------------

	for (int nCnt = 0; nCnt < MAX_LIGHT; nCnt++)
	{
		// ���C�g���N���A����
		ZeroMemory(&m_aLight[nCnt], sizeof(D3DLIGHT9));

		// ���C�g�̎�ނ�ݒ�
		m_aLight[nCnt].Type = D3DLIGHT_DIRECTIONAL;

		// ���C�g�̊g�U����ݒ�
		m_aLight[nCnt].Diffuse = m_LightCol[nCnt];
		m_aLight[nCnt].Specular = m_LightCol[nCnt];		//�X�y�L�����[(���ˌ�)

		// ���C�g�̕����̐ݒ�
		D3DXVec3Normalize(&m_vecDir[nCnt], &m_vecDir[nCnt]);		//���K��
		m_aLight[nCnt].Direction = m_vecDir[nCnt];

		// ���C�g��ݒ肷��
		pDevice->SetLight(nCnt, &m_aLight[nCnt]);
		// ���C�g��L���ɂ���
		pDevice->LightEnable(nCnt, TRUE);
	}
}
//-----------------------------------------------------------------------------
// �I������
//-----------------------------------------------------------------------------
void CLight::Uninit()
{
}
//-----------------------------------------------------------------------------
// �X�V����
//-----------------------------------------------------------------------------
void CLight::Update()
{

}
//-----------------------------------------------------------------------------
// ���C�g�̏��
//-----------------------------------------------------------------------------
void CLight::ShowLightInfo()
{
	if (ImGui::CollapsingHeader("LightInfo"))
	{
		LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	// �f�o�C�X�̎擾

		if (ImGui::TreeNode("Light0"))
		{
			ImGui::SliderFloat3("direction", m_vecDir[0], -1.0f, 1.0f);

			D3DXVec3Normalize(&m_vecDir[0], &m_vecDir[0]);		//���K��
			m_aLight[0].Direction = m_vecDir[0];

			pDevice->SetLight(0, &m_aLight[0]);
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("Light1"))
		{
			ImGui::SliderFloat3("direction", m_vecDir[1], -1.0f, 1.0f);

			D3DXVec3Normalize(&m_vecDir[1], &m_vecDir[1]);		//���K��
			m_aLight[1].Direction = m_vecDir[1];

			pDevice->SetLight(1, &m_aLight[1]);
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("Light2"))
		{
			ImGui::SliderFloat3("direction", m_vecDir[2], -1.0f, 1.0f);

			D3DXVec3Normalize(&m_vecDir[2], &m_vecDir[2]);		//���K��
			m_aLight[2].Direction = m_vecDir[2];

			pDevice->SetLight(2, &m_aLight[2]);
			ImGui::TreePop();
		}
	}
}
//-----------------------------------------------------------------------------
// ���C�g�̌����擾
//-----------------------------------------------------------------------------
D3DXVECTOR3 CLight::GetLightDir(int nLightNum)
{
	return m_vecDir[nLightNum];
}
//-----------------------------------------------------------------------------
// ���C�g�F�擾
//-----------------------------------------------------------------------------
D3DXCOLOR CLight::GetLightColor(int nLightNum)
{
	return m_LightCol[nLightNum];
}
