//=============================================================================
// ���C�g���� [light.cpp]
//=============================================================================
#include "light.h"
#include "manager.h"
#include "renderer.h"
#include "inputKeyboard.h"
//=============================================================================
// ���C�g�̏���������
//=============================================================================
void CLight::InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXVECTOR3 vecDir;

	// ���C�g���N���A����
	ZeroMemory(&m_light, sizeof(D3DLIGHT9));
	for (int nCnt = 0; nCnt < 3; nCnt++)
	{
		// ���C�g�̎�ނ�ݒ�
		m_light[nCnt].Type = D3DLIGHT_DIRECTIONAL;
		// ���C�g�̊g�U����ݒ�
		m_light[nCnt].Diffuse = D3DXCOLOR(1.0f - nCnt * 0.3f, 1.0f - nCnt*0.3f, 1.0f - nCnt*0.3f, 1.0f);
		m_light[nCnt].Specular = D3DXCOLOR(1.0f - nCnt * 0.3f, 1.0f - nCnt*0.3f, 1.0f - nCnt*0.3f, 1.0f);
		//���C�g�}�e���A���̐ݒ�
		m_lightmat.Diffuse = D3DXCOLOR(1.0f - nCnt * 0.3f, 1.0f - nCnt*0.3f, 1.0f - nCnt*0.3f, 1.0f);
	}
	// ���C�g�̕����̐ݒ�
	vecDir = D3DXVECTOR3(-0.40f, 0.30f, -0.80f);
	//���K���@(�l��1�ɂ���)
	D3DXVec3Normalize(&vecDir, &vecDir);
	m_light[0].Direction = vecDir;

	// ���C�g�̕����̐ݒ�
	vecDir = D3DXVECTOR3(0.20f, -0.80f, 0.40f);
	D3DXVec3Normalize(&vecDir, &vecDir);
	m_light[1].Direction = vecDir;

	// ���C�g�̕����̐ݒ�
	vecDir = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	D3DXVec3Normalize(&vecDir, &vecDir);
	m_light[2].Direction = vecDir;

	for (int nCnt = 0; nCnt < 3; nCnt++)
	{
		// ���C�g��ݒ肷��
		pDevice->SetLight(nCnt, &m_light[nCnt]);
		// ���C�g��L���ɂ���
		pDevice->LightEnable(nCnt, TRUE);
	}
}

//=============================================================================
// ���C�g�̏I������
//=============================================================================
void CLight::UninitLight(void)
{
}

//=============================================================================
// ���C�g�̍X�V����
//=============================================================================
void CLight::UpdateLight(void)
{
	CKeyboard *key;
	key = CManager::GetInputKeyboard();
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	static float rot;

	if (key->GetKeyboardPress(DIK_P))
	{
		rot += 0.1f;
	}
	else if (key->GetKeyboardPress(DIK_O))
	{
		rot -= 0.1f;
	}
	// ���C�g�̕����̐ݒ�
	//vecDir = D3DXVECTOR3(-sinf(rot),cosf(rot),tanf(rot));
	vecDir = D3DXVECTOR3(0.40f, -0.30f, 0.80f);

	D3DXVec3Normalize(&vecDir, &vecDir);
	m_light[0].Direction = vecDir;

	pDevice->SetLight(0, &m_light[0]);
	// ���C�g��L���ɂ���
	pDevice->LightEnable(0, TRUE);

	//CDebugProc::Print("���C�g[0] X:%0.2f Y:%0.2f Z:%0.2f\n", m_light[0].Direction.x, m_light[0].Direction.y, m_light[0].Direction.z);
}

