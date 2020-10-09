//------------------------------------------------------------------------------
//
//�p�[�e�B�N���̊Ǘ�����  [ParticleManager.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "ParticleManager.h"
#include "manager.h"
#include "renderer.h"
#include "particle.h"
//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------
std::vector<std::unique_ptr<CParticle>> CParticleManager::m_pParticleList = {};

//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CParticleManager::CParticleManager()
{
}

//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CParticleManager::~CParticleManager()
{
	m_pParticleList.clear();
	CParticle::ReleaseVertex();
}
//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CParticleManager::Init()
{
	return S_OK;
}
//------------------------------------------------------------------------------
//�I������
//------------------------------------------------------------------------------
void CParticleManager::Uninit()
{

}
//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CParticleManager::Update()
{
	//���_�ԍ����Z�b�g
	CParticle::ResetVertexID();

	//nullcheck
	if (!m_pParticleList.empty())
	{
		for (size_t nCnt = 0; nCnt < m_pParticleList.size(); nCnt++)
		{
			//�X�V����
			m_pParticleList[nCnt]->Update();

			//�t���O�����Ă��邩�`�F�b�N
			if(m_pParticleList[nCnt]->GetDeleteFlag())
			{
				//�I���������ă������J��
				m_pParticleList[nCnt]->Uninit();
				m_pParticleList[nCnt].reset();

				//�z�񂩂�폜
				m_pParticleList.erase(m_pParticleList.begin() + nCnt);

				//�폜���ăJ�E���g�����ꂽ���C��
				nCnt--;
			}
		}

		//���_�ԍ����Z�b�g
		CParticle::ResetVertexID();

		for (size_t nCnt = 0; nCnt < m_pParticleList.size(); nCnt++)
		{
			//���_�o�b�t�@�X�V����
			m_pParticleList[nCnt]->UpdateVertex();
		}
	}
}
//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void CParticleManager::Draw()
{

	//���_�ԍ����Z�b�g
	CParticle::ResetVertexID();

	for (size_t nCnt = 0; nCnt < m_pParticleList.size(); nCnt++)
	{
		//���_�o�b�t�@�X�V����
		m_pParticleList[nCnt]->UpdateVertex();
	}


	//���_�ԍ����Z�b�g
	CParticle::ResetVertexID();
	//nullcheck
	if (!m_pParticleList.empty())
	{
		for (size_t nCnt = 0; nCnt < m_pParticleList.size(); nCnt++)
		{
			m_pParticleList[nCnt]->Draw();
		}
	}
}

//------------------------------------------------------------------------------
//�f�o�b�O���\��
//------------------------------------------------------------------------------
void CParticleManager::ShowDebugInfo()
{
#ifdef _DEBUG

#endif // _DEBUG
}

//------------------------------------------------------------------------------
//�p�[�e�B�N������
//------------------------------------------------------------------------------
void CParticleManager::Create()
{
	//�������m�� Scene���ŊǗ�
	std::unique_ptr<CParticleManager> pParticle = std::make_unique<CParticleManager>();

	//������
	pParticle->Init();

	pParticle->SetObjType(OBJTYPE::OBJTYPE_2DEFFECT);
	pParticle->AddUniqueList(std::move(pParticle));

	//�p�[�e�B�N���̒��_�o�b�t�@�m��
	CParticle::MakeVertex();

}
//------------------------------------------------------------------------------
//�j��
//------------------------------------------------------------------------------
void CParticleManager::Release()
{

}
//------------------------------------------------------------------------------
//�p�[�e�B�N���̃��X�g
//------------------------------------------------------------------------------
void CParticleManager::AddParticleList(std::unique_ptr<CParticle> pParticle)
{
	//�z��ɒǉ�
	m_pParticleList.emplace_back(std::move(pParticle));
}

