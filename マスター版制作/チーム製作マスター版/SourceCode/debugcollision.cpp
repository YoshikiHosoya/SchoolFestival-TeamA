// ----------------------------------------
//
// �f�o�b�O�p�̓����蔻��\������[debugcollision.cpp]
// Author : Fujiwara Masato
//
// ----------------------------------------

// ----------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ----------------------------------------
/* �`�� */
#include "debugcollision.h"
#include "meshbox.h"

// ----------------------------------------
//
// �ÓI�ϐ��錾
//
// ----------------------------------------

// ----------------------------------------
// �R���X�g���N�^����
// ----------------------------------------
CDebugcollision::CDebugcollision(OBJ_TYPE type) :CScene(type)
{
	m_pos = nullptr;										// ���W�|�C���^�̏�����
	m_size = nullptr;										// �T�C�Y�|�C���^�̏�����
	m_type = COLLISIONTYPE_BOX;							// �^�C�v�̏�����
	m_pMeshBox = nullptr;
}

// ----------------------------------------
// �f�X�g���N�^����
// ----------------------------------------
CDebugcollision::~CDebugcollision()
{
	if (m_pMeshBox)
	{
		this->m_pMeshBox->Rerease();
		this->m_pMeshBox = nullptr;
	}
}

// ----------------------------------------
// ����������
// ----------------------------------------
HRESULT CDebugcollision::Init(void)
{
	switch (m_type)
	{
	case COLLISIONTYPE_BOX:
		BoxCollision();
		break;

	case COLLISIONTYPE_BOX_CHARA:
		Box_CharaCollision();
		break;

	default:
		break;
	}

	return S_OK;
}

// ----------------------------------------
// ���̓����蔻�菈��
// ----------------------------------------
void CDebugcollision::BoxCollision(void)
{
	m_pMeshBox = CMeshBox::Create(*m_pos,*m_size, CMeshBox::TYPE_CENTER);
}
// ----------------------------------------
// ���̓����蔻�菈��
// ----------------------------------------
void CDebugcollision::Box_CharaCollision(void)
{
	m_pMeshBox = CMeshBox::Create(*m_pos, *m_size, CMeshBox::TYPE_GROUND);
}

// ----------------------------------------
// �I������
// ----------------------------------------
void CDebugcollision::Uninit(void)
{
	m_pos = nullptr;										// ���W�|�C���^�̏�����
	m_size = nullptr;										// �T�C�Y�|�C���^�̏�����
}

// ----------------------------------------
// �X�V����
// ----------------------------------------
void CDebugcollision::Update(void)
{
	// ����̎�ނ����^��������ʂ�
	if (m_type == COLLISIONTYPE_BOX)
	{
		if (m_pMeshBox)
		{
			m_pMeshBox->SetPos(*m_pos);
		}
	}

	// ����̎�ނ��^��������ʂ�
	else if (m_type == COLLISIONTYPE_BOX_CHARA)
	{
		if (m_pMeshBox)
		{
			m_pMeshBox->SetPos(*m_pos);
		}
	}

}

// ----------------------------------------
// �`�揈��
// ----------------------------------------
void CDebugcollision::Draw(void)
{
}
// ----------------------------------------
// �f�o�b�O
// ----------------------------------------
void CDebugcollision::DebugInfo(void)
{
}

// ----------------------------------------
// ��������
// ----------------------------------------
CDebugcollision * CDebugcollision::Create(
	D3DXVECTOR3 * pos,
	D3DXVECTOR3 * size,
	COLLISIONTYPE type
)
{
	// �ϐ��錾
	CDebugcollision * pDebugcollision;
	// �������m��
	pDebugcollision = new CDebugcollision(OBJTYPE_DEBUGCOLLISION);
	// ���W�̐ݒ�
	pDebugcollision->m_pos = pos;
	// �T�C�Y�̐ݒ�
	pDebugcollision->m_size = size;
	// ��ނ̐ݒ�
	pDebugcollision->m_type = type;
	// ������
	pDebugcollision->Init();
	return pDebugcollision;
}

// ----------------------------------------
// �ʒu�ݒ菈��
// ----------------------------------------
void CDebugcollision::SetPos(D3DXVECTOR3 * pos)
{
	// ���W�̃|�C���^��nullptr����Ȃ�������ʂ�

	if (pos != nullptr)
	{
		// ���W������
		m_pos = pos;

		// ����̎�ނ����^��������ʂ�
		if (m_type == COLLISIONTYPE_BOX)
		{
			if (m_pMeshBox)
			{
				m_pMeshBox->SetPos(*m_pos);
			}
		}

		// ����̎�ނ��^��������ʂ�
		else if (m_type == COLLISIONTYPE_BOX_CHARA)
		{
			if (m_pMeshBox)
			{
				m_pMeshBox->SetPos(*m_pos);
			}
		}
	}
}

// ----------------------------------------
// �T�C�Y�ݒ菈��
// ----------------------------------------
void CDebugcollision::SetSize(D3DXVECTOR3 * size)
{
	m_size = size;
	m_pMeshBox->SetSize(*m_size);
}

// ----------------------------------------
// ���C���̍폜
// ----------------------------------------
void CDebugcollision::DeleteDeCollision()
{
	if (m_pMeshBox)
	{
		this->m_pMeshBox->Rerease();
		this->m_pMeshBox = nullptr;
	}
}
