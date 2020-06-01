//------------------------------------------------------------------------------
//
//�V�F�[�_�[  [Shader.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "shader.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "light.h"

//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------
int CShader::m_nCnt = 0;
std::vector<ID3DXEffect*> CShader::m_pShaderEffect = {};
std::vector<std::unique_ptr<CShaderHandle>> CShader::m_ShaderHandleList = {};
std::unique_ptr<CShaderHandle_ModelColor> CShader::m_pModelColorHandle = nullptr;
std::vector<std::string> CShader::m_ShaderFileNameList =
{
	{ "data/shader/ModelDrawShader.fx" },
};
//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CShader::CShader()
{
}

//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CShader::~CShader()
{
}

//------------------------------------------------------------------------------
//�p�����[�^�ݒ�
//------------------------------------------------------------------------------
void CShader::SetParamaterShader()
{
	//nullcheck
	if (!m_pShaderEffect.empty())
	{
		//�G�t�F�N�g�̃T�C�Y��
		for (size_t nCnt = 0; nCnt < m_pShaderEffect.size(); nCnt++)
		{
			//�n���h���𗘗p���č�����
			//���ꂼ��̒l���X�V
			m_pShaderEffect[nCnt]->SetMatrix(m_ShaderHandleList[nCnt]->m_hViewMtx, &CManager::GetRenderer()->GetCamera()->GetMtxView());
			m_pShaderEffect[nCnt]->SetMatrix(m_ShaderHandleList[nCnt]->m_hProjectionMtx, &CManager::GetRenderer()->GetCamera()->GetMtxProjection());
			m_pShaderEffect[nCnt]->SetVector(m_ShaderHandleList[nCnt]->m_hLightDir0, &D3DXVECTOR4(CManager::GetRenderer()->GetLight()->GetLightDir(0), 0.0f));
			m_pShaderEffect[nCnt]->SetVector(m_ShaderHandleList[nCnt]->m_hLightDir1, &D3DXVECTOR4(CManager::GetRenderer()->GetLight()->GetLightDir(1), 0.0f));
			m_pShaderEffect[nCnt]->SetVector(m_ShaderHandleList[nCnt]->m_hLightDir2, &D3DXVECTOR4(CManager::GetRenderer()->GetLight()->GetLightDir(2), 0.0f));
			m_pShaderEffect[nCnt]->SetVector(m_ShaderHandleList[nCnt]->m_hLightCol0, &D3DXVECTOR4(CManager::GetRenderer()->GetLight()->GetLightColor(0)));
			m_pShaderEffect[nCnt]->SetVector(m_ShaderHandleList[nCnt]->m_hLightCol1, &D3DXVECTOR4(CManager::GetRenderer()->GetLight()->GetLightColor(1)));
			m_pShaderEffect[nCnt]->SetVector(m_ShaderHandleList[nCnt]->m_hLightCol2, &D3DXVECTOR4(CManager::GetRenderer()->GetLight()->GetLightColor(2)));
			m_pShaderEffect[nCnt]->SetFloat (m_ShaderHandleList[nCnt]->m_hCount, (float)m_nCnt);
		}
	}
}

//------------------------------------------------------------------------------
//�ÓI�ȃp�����[�^������ �J�E���g�Ƃ�
//------------------------------------------------------------------------------
void CShader::InitStaticParam()
{
	m_nCnt = 0;
}

//------------------------------------------------------------------------------
//�ÓI�ȃp�����[�^�X�V �J�E���g�Ƃ�
//------------------------------------------------------------------------------
void CShader::UpdateStaticParam()
{
	//�J�E���g�A�b�v
	m_nCnt++;

	//�V�F�[�_�[�Ƀp�����[�^�ݒ�
	SetParamaterShader();
}

//------------------------------------------------------------------------------
//��������
//------------------------------------------------------------------------------
std::unique_ptr<CShader> CShader::Create()
{
	//�������m��
	std::unique_ptr<CShader> pShader(new CShader);

	//nullcheck
	if (pShader)
	{
		return pShader;
	}
	return nullptr;
}

//------------------------------------------------------------------------------
//�V�F�[�_�[����
//------------------------------------------------------------------------------
HRESULT CShader::Load()
{
	//�����������ǂ���
	HRESULT hr = S_OK;

	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�G�t�F�N�g�̃|�C���^�@��
	ID3DXEffect *pEffect;
	for (int nCnt = 0; nCnt < CShader::SHADER_MAX; nCnt++)
	{
		//�V�F�[�_�[�ǂݍ���
		if (FAILED(D3DXCreateEffectFromFile(
			pDevice,
			m_ShaderFileNameList[nCnt].data(),
			NULL,
			NULL,
			D3DXSHADER_DEBUG,
			NULL,
			&pEffect,
			NULL
		)))
		{
			//���s
			std::cout << "Shader�ǂ݂��ݎ��s - " << m_ShaderFileNameList[nCnt].data() << NEWLINE;
			hr = E_FAIL;
		}
		else
		{
			//�z��ɒǉ�
			std::cout << "Shader - " << m_ShaderFileNameList[nCnt].data() << NEWLINE;
			m_pShaderEffect.emplace_back(pEffect);

			if (nCnt == CShader::SHADER_MODELDRAW)
			{
				//�������m��
				m_pModelColorHandle.reset(new CShaderHandle_ModelColor);

				//�n���h���擾
				m_pModelColorHandle->m_hDiffuseCol	= m_pShaderEffect[nCnt]->GetParameterByName(NULL, "g_DiffuseColor");		//�g�U��
				m_pModelColorHandle->m_hSpecularCol = m_pShaderEffect[nCnt]->GetParameterByName(NULL, "g_SpecularColor");	//���ˌ�
				m_pModelColorHandle->m_hEmissiveCol = m_pShaderEffect[nCnt]->GetParameterByName(NULL, "g_EmissiveColor");	//���ˌ�
				m_pModelColorHandle->m_Ambient		= m_pShaderEffect[nCnt]->GetParameterByName(NULL, "g_Ambient");			//����
				m_pModelColorHandle->m_hPower		= m_pShaderEffect[nCnt]->GetParameterByName(NULL, "g_Power");			//���˂̋�
			}
		}
	}

	GetGlobalHandle();

	return hr;
}

//------------------------------------------------------------------------------
//�V�F�[�_�[�j��
//------------------------------------------------------------------------------
void CShader::UnLoad()
{
	//for
	for (size_t nCnt = 0; nCnt < m_pShaderEffect.size(); nCnt++)
	{
		//�J��
		m_pShaderEffect[nCnt]->Release();
		m_pShaderEffect[nCnt] = nullptr;
	}

	//�z��J��
	m_pShaderEffect.clear();
}

//------------------------------------------------------------------------------
//�V�F�[�_�[�̃O���[�o���ϐ��̃n���h���擾
//------------------------------------------------------------------------------
void CShader::GetGlobalHandle()
{
	//�V�F�[�_�[�̃G�t�F�N�g����
	for (size_t nCnt = 0; nCnt < m_pShaderEffect.size(); nCnt++)
	{
		//�������m�� + �z��ɒǉ�
		m_ShaderHandleList.emplace_back(new CShaderHandle);

		//�n���h���擾
		m_ShaderHandleList[nCnt]->m_hViewMtx		= m_pShaderEffect[nCnt]->GetParameterByName(NULL, "g_ViewMatrix");			//�r���[�}�g���b�N�X
		m_ShaderHandleList[nCnt]->m_hProjectionMtx	= m_pShaderEffect[nCnt]->GetParameterByName(NULL, "g_ProjectionMatrix");	//�v���W�F�N�V�����}�g���b�N�X
		m_ShaderHandleList[nCnt]->m_hLightDir0		= m_pShaderEffect[nCnt]->GetParameterByName(NULL, "g_LightDirection[0]");	//�����̌���
		m_ShaderHandleList[nCnt]->m_hLightDir1		= m_pShaderEffect[nCnt]->GetParameterByName(NULL, "g_LightDirection[1]");	//�����̌���
		m_ShaderHandleList[nCnt]->m_hLightDir2		= m_pShaderEffect[nCnt]->GetParameterByName(NULL, "g_LightDirection[2]");	//�����̌���
		m_ShaderHandleList[nCnt]->m_hLightCol0		= m_pShaderEffect[nCnt]->GetParameterByName(NULL, "g_LightColor[0]");		//���̐F
		m_ShaderHandleList[nCnt]->m_hLightCol1		= m_pShaderEffect[nCnt]->GetParameterByName(NULL, "g_LightColor[1]");		//���̐F
		m_ShaderHandleList[nCnt]->m_hLightCol2		= m_pShaderEffect[nCnt]->GetParameterByName(NULL, "g_LightColor[2]");		//���̐F
		m_ShaderHandleList[nCnt]->m_hCount			= m_pShaderEffect[nCnt]->GetParameterByName(NULL, "g_fCount");				//�J�E���g
	}
}

//------------------------------------------------------------------------------
//���f���̐F�ݒ�
//------------------------------------------------------------------------------
void CShader::SetModelColor(D3DXCOLOR DiffuseCol, D3DXCOLOR SpecularCol, D3DXCOLOR EmissiveCol, D3DXCOLOR AmbientCol,float fPower)
{
	m_pShaderEffect[CShader::SHADER_MODELDRAW]->SetVector(m_pModelColorHandle->m_hDiffuseCol, &D3DXVECTOR4(DiffuseCol));
	m_pShaderEffect[CShader::SHADER_MODELDRAW]->SetVector(m_pModelColorHandle->m_hSpecularCol, &D3DXVECTOR4(SpecularCol));
	m_pShaderEffect[CShader::SHADER_MODELDRAW]->SetVector(m_pModelColorHandle->m_hEmissiveCol, &D3DXVECTOR4(EmissiveCol));
	m_pShaderEffect[CShader::SHADER_MODELDRAW]->SetVector(m_pModelColorHandle->m_Ambient, &D3DXVECTOR4(AmbientCol));
	m_pShaderEffect[CShader::SHADER_MODELDRAW]->SetFloat(m_pModelColorHandle->m_hPower, fPower);
}