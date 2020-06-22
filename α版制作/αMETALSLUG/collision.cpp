//=============================================================================
//
// Collision�����̐���[calculation.cpp]
// Author : Fujiwara Masato
//
//=============================================================================

//=============================================================================
//
// �C���N���[�h�t�@�C��
//
//=============================================================================
#include "Collision.h"
#ifdef _DEBUG
#include "debugcollision.h"
#endif // _DEBUG

//=============================================================================
//
// �}�N����`
//
//=============================================================================

//=============================================================================
//
// �ÓI�ϐ�
//
//=============================================================================

// ----------------------------------------
// �R���X�g���N�^
// ----------------------------------------
CCollision::CCollision()
{
	m_objtype			= OBJTYPE_PLAYERBULLET;				// �^�C�v�̏�����
	m_Collisiontype		= COLLISIONTYPE_NORMAL;				// �����蔻��̎��
	m_ppos				= nullptr;							// �ʒu���
	m_posOld			= nullptr;							// �O��̈ʒu���
	m_size				= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �T�C�Y���
	m_pmove				= nullptr;							// �ړ����
	m_Debugcollision	= nullptr;							// �f�o�b�O�p�����蔻��̃|�C���^
	m_bHitFlag			= false;							// �������Ă��邩�ǂ���
	m_pCollision		= nullptr;							// �����蔻��̃|�C���^
}

// ----------------------------------------
// �f�X�g���N�^
// ----------------------------------------
CCollision::~CCollision()
{
}

// ----------------------------------------
// ����������
// ----------------------------------------
void CCollision::Init(void)
{
}

// ----------------------------------------
// �I������
// ----------------------------------------
void CCollision::Uninit(void)
{
}

// ----------------------------------------
// �X�V����
// ----------------------------------------
void CCollision::Update(void)
{
//#ifdef _DEBUG
//	if (m_Debugcollision != nullptr)
//	{
//		m_Debugcollision->SetPos(m_ppos);
//	}
//#endif // _DEBUG
}

// ----------------------------------------
// �����蔻��폜
// ----------------------------------------
void CCollision::ReleaseCollision(CCollision *pColl)
{
#ifdef _DEBUG
	if (pColl->m_pCollision->m_Debugcollision != nullptr)
	{
		// �f�o�b�N�p����폜
		pColl->m_pCollision->m_Debugcollision->DeleteDeCollision(pColl->m_pCollision->m_Debugcollision);
	}
#endif // _DEBUG

	if (pColl->m_pCollision == pColl)
	{
		delete pColl->m_pCollision;
		pColl->m_pCollision = nullptr;
	}
}

// ----------------------------------------
// ��������
// ----------------------------------------
CCollision * CCollision::Create(void)
{
	// �ϐ��錾
	CCollision * pCollision;	// �����蔻��
	// �������m��
	pCollision = new CCollision;
	// ������
	pCollision->Init();
	// �|�C���^������
	pCollision->m_pCollision = pCollision;
	return pCollision;
}

// ----------------------------------------
// �f�o�b�O�p�����蔻�萶������
// ----------------------------------------
void CCollision::DeCollisionCreate(COLLISIONTYPE collisiontype)
{
#ifdef _DEBUG
	switch (collisiontype)
	{
	case COLLISIONTYPE_NORMAL:{
		m_Debugcollision = CDebugcollision::Create(
			m_ppos,
			&m_size,
			CDebugcollision::COLLISIONTYPE_BOARD);
	}break;

	case COLLISIONTYPE_CHARACTER: {
		m_Debugcollision = CDebugcollision::Create(
			m_ppos,
			&m_size,
			CDebugcollision::COLLISIONTYPE_BOARDCHARA);
	}break;

	default:
		break;
	}
#endif //DEBUG
}

// ----------------------------------------
// �ʒu�ݒ菈��
// ----------------------------------------
void CCollision::SetPos(D3DXVECTOR3 * pos)
{
	m_ppos = pos;

#ifdef _DEBUG
	if (m_Debugcollision != nullptr)
	{
		m_Debugcollision->SetPos(m_ppos);
	}
#endif // _DEBUG
}

// ----------------------------------------
// 1�t���[���O�̈ʒu�ݒ菈��
// ----------------------------------------
void CCollision::SetPosOld(D3DXVECTOR3 * posold)
{
	m_posOld = posold;
}

// ----------------------------------------
// �T�C�Y�ݒ菈��
// ----------------------------------------
void CCollision::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}

// ----------------------------------------
// 2d�T�C�Y�ݒ菈��
// ----------------------------------------
void CCollision::SetSize2D(D3DXVECTOR3 size)
{
	m_size = size;
}

// ----------------------------------------
// �ړ��ݒ菈��
// ----------------------------------------
void CCollision::SetMove(D3DXVECTOR3 * move)
{
	m_pmove = move;
}

// ----------------------------------------
// �^�C�v�ݒ菈��
// ----------------------------------------
void CCollision::SetType(OBJTYPE type)
{
	m_objtype = type;
}

// ----------------------------------------
// ���^�̓����蔻�菈��
// ----------------------------------------
bool CCollision::Collision(OBJTYPE objtype)
{
	//// �ϐ��錾
	//CCollision * pCollision = NULL;
	//CCollision *pCollisionNext;	// ���̃V�[��
	//// �擪�|�C���g���i�[
	//pCollision = m_pTop;

	//while (pCollision != NULL)
	//{
	//	// ���̃|�C���^����
	//	pCollisionNext = pCollision->m_pNext;

	//	if (pCollision != this && pCollision->m_objtype == objtype)
	//	{
	//		// �f�ނ�Y�͈�
	//		if (this->m_ppos->y + this->m_size.y * 0.5f > pCollision->m_ppos->y - pCollision->m_size.y * 0.5f&&
	//			this->m_ppos->y - this->m_size.y * 0.5f < pCollision->m_ppos->y + pCollision->m_size.y * 0.5f)
	//		{
	//			// �f�ނ�Z�͈�
	//			if (this->m_ppos->z + this->m_size.z * 0.5f > pCollision->m_ppos->z - pCollision->m_size.z * 0.5f&&
	//				this->m_ppos->z - this->m_size.z * 0.5f < pCollision->m_ppos->z + pCollision->m_size.z * 0.5f)
	//			{
	//				// �����蔻��(��)
	//				if (this->m_ppos->x + this->m_size.x * 0.5f > pCollision->m_ppos->x - pCollision->m_size.x * 0.5f&&
	//					this->m_posOld.x + this->m_size.x * 0.5f <= pCollision->m_ppos->x - pCollision->m_size.x * 0.5f)
	//				{
	//					// �f�ޏ�̍���
	//					//this->m_ppos->x = pCollision->m_ppos->x - pCollision->m_size.x * 0.5f - this->m_size.x * 0.5f;

	//					// �ړ��ʂ̏�����
	//					//this->m_pmove->x = 0.0f;

	//					// �I�u�W�F�N�g�ɓ��������t���O
	//					m_bHitFlag = true;
	//				}

	//				// �����蔻��(�E)
	//				else if (this->m_ppos->x - this->m_size.x * 0.5f < pCollision->m_ppos->x + pCollision->m_size.x * 0.5f&&
	//					m_posOld.x - this->m_size.x * 0.5f >= pCollision->m_ppos->x + pCollision->m_size.x * 0.5f)
	//				{
	//					// �f�ޏ�̍���
	//					//this->m_ppos->x = pCollision->m_ppos->x + pCollision->m_size.x * 0.5f + this->m_size.x * 0.5f;
	//					// �ړ��ʂ̏�����
	//					//this->m_pmove->x = 0.0f;
	//					// �I�u�W�F�N�g�ɓ��������t���O
	//					m_bHitFlag = true;
	//				}
	//			}

	//			// �f�ނ�X�͈�
	//			if (this->m_ppos->x + this->m_size.x * 0.5f > pCollision->m_ppos->x - pCollision->m_size.x * 0.5f&&
	//				this->m_ppos->x - this->m_size.x * 0.5f < pCollision->m_ppos->x + pCollision->m_size.x * 0.5f)
	//			{
	//				// �����蔻��(��O)
	//				if (this->m_ppos->z + this->m_size.z * 0.5f > pCollision->m_ppos->z - pCollision->m_size.z * 0.5f&&
	//					m_posOld.z + this->m_size.z * 0.5f <= pCollision->m_ppos->z - pCollision->m_size.z * 0.5f)
	//				{
	//					// �f�ޏ�̍���
	//					//this->m_ppos->z = pCollision->m_ppos->z - pCollision->m_size.z * 0.5f - this->m_size.z * 0.5f;
	//					// �ړ��ʂ̏�����
	//					//this->m_pmove->z = 0.0f;
	//					// �I�u�W�F�N�g�ɓ��������t���O
	//					m_bHitFlag = true;
	//				}

	//				// �����蔻��(��)
	//				else if (this->m_ppos->z - this->m_size.z * 0.5f < pCollision->m_ppos->z + pCollision->m_size.z * 0.5f&&
	//					m_posOld.z - this->m_size.z * 0.5f >= pCollision->m_ppos->z + pCollision->m_size.z * 0.5f)
	//				{
	//					// �f�ޏ�̍���
	//					//this->m_ppos->z = pCollision->m_ppos->z +
	//						//pCollision->m_size.z * 0.5f +
	//						//this->m_size.z * 0.5f + 0.1f;
	//					// �ړ��ʂ̏�����
	//					//this->m_pmove->z = 0.0f;
	//					// �I�u�W�F�N�g�ɓ��������t���O
	//					m_bHitFlag = true;
	//				}
	//			}
	//		}

	//		// �f�ނ�Z�͈�
	//		if (this->m_ppos->z + this->m_size.z * 0.5f > pCollision->m_ppos->z - pCollision->m_size.z * 0.5f&&
	//			this->m_ppos->z - this->m_size.z * 0.5f < pCollision->m_ppos->z + pCollision->m_size.z * 0.5f)
	//		{
	//			// �f�ނ�X�͈�
	//			if (this->m_ppos->x + this->m_size.x * 0.5f > pCollision->m_ppos->x - pCollision->m_size.x * 0.5f&&
	//				this->m_ppos->x - this->m_size.x * 0.5f < pCollision->m_ppos->x + pCollision->m_size.x * 0.5f)
	//			{
	//				// �����蔻��(��)
	//				if (this->m_ppos->y + this->m_size.y * 0.5f > pCollision->m_ppos->y - pCollision->m_size.y * 0.5f&&
	//					m_posOld.y + this->m_size.y * 0.5f <= pCollision->m_ppos->y - pCollision->m_size.y * 0.5f)
	//				{
	//					// �f�ޏ�̍���
	//					//this->m_ppos->y = this->m_posOld.y;
	//					// �ړ��ʂ̏�����
	//					//this->m_pmove->y = 0.0f;
	//					// �I�u�W�F�N�g�ɓ��������t���O
	//					m_bHitFlag = true;
	//				}

	//				// �����蔻��(��)
	//				else if (this->m_ppos->y - this->m_size.y * 0.5f < pCollision->m_ppos->y + pCollision->m_size.y * 0.5f&&
	//					m_posOld.y - this->m_size.y * 0.5f >= pCollision->m_ppos->y + pCollision->m_size.y * 0.5f)
	//				{
	//					// �f�ޏ�̍���
	//					//this->m_ppos->y = pCollision->m_ppos->y + pCollision->m_size.y * 0.5f + this->m_size.y * 0.5f;
	//					// �ړ��ʂ̏�����
	//					//this->m_pmove->y = 0.0f;
	//					// �I�u�W�F�N�g�ɓ��������t���O
	//					m_bHitFlag = true;
	//				}
	//			}
	//		}
	//	}
	//	pCollision = pCollisionNext;
	//}
	// �������Ă��邩���Ȃ�����Ԃ�
	return m_bHitFlag;
}

// ----------------------------------------
// �^�̓����蔻�菈��
// ----------------------------------------
bool CCollision::Collision2D(CCollision *pCollision)
{
	// �ϐ��錾

	if (pCollision != nullptr)
	{
		// X Y�͈̔�
		if (this->m_ppos->y + this->m_size.y * 0.5f >= pCollision->m_ppos->y - pCollision->m_size.y * 0.5f&&
			this->m_ppos->y - this->m_size.y * 0.5f <= pCollision->m_ppos->y + pCollision->m_size.y * 0.5f&&
			this->m_ppos->x + this->m_size.x * 0.5f > pCollision->m_ppos->x - pCollision->m_size.x * 0.5f&&
			this->m_ppos->x - this->m_size.x * 0.5f < pCollision->m_ppos->x + pCollision->m_size.x * 0.5f)
		{
			// �I�u�W�F�N�g�ɓ��������t���O
			m_bHitFlag = true;
		}

		else
		{
			m_bHitFlag = false;
		}
	}

	// �������Ă��邩���Ȃ�����Ԃ�
	return m_bHitFlag;
}

// ----------------------------------------
// �L�����N�^�[�p�^�̓����蔻�菈��
// ----------------------------------------
bool CCollision::CharCollision2D(CCollision * pCollision)
{
	if (pCollision != nullptr)
	{
		// X Y�͈̔�
		if (this->m_ppos->y + this->m_size.y >= pCollision->m_ppos->y&&
			this->m_ppos->y <= pCollision->m_ppos->y + pCollision->m_size.y&&
			this->m_ppos->x + this->m_size.x * 0.5f > pCollision->m_ppos->x - pCollision->m_size.x * 0.5f&&
			this->m_ppos->x - this->m_size.x * 0.5f < pCollision->m_ppos->x + pCollision->m_size.x * 0.5f)
		{
			// �I�u�W�F�N�g�ɓ��������t���O
			m_bHitFlag = true;
		}

		else
		{
			m_bHitFlag = false;
		}
	}

	// �������Ă��邩���Ȃ�����Ԃ�
	return m_bHitFlag;
}

// ----------------------------------------
// �L�����N�^�[�ƃA�C�e���A�e�̔���
// ----------------------------------------
bool CCollision::OtherCollision2D(CCollision * pCollision)
{
	if (pCollision != nullptr)
	{
		// X Y�͈̔�
		if (this->m_ppos->y + this->m_size.y * 0.5f >= pCollision->m_ppos->y&&
			this->m_ppos->y - this->m_size.y * 0.5f <= pCollision->m_ppos->y + pCollision->m_size.y&&
			this->m_ppos->x + this->m_size.x * 0.5f > pCollision->m_ppos->x - pCollision->m_size.x * 0.5f&&
			this->m_ppos->x - this->m_size.x * 0.5f < pCollision->m_ppos->x + pCollision->m_size.x * 0.5f)

		{
			// �I�u�W�F�N�g�ɓ��������t���O
			m_bHitFlag = true;
		}

		else
		{
			m_bHitFlag = false;
		}
	}

	// �������Ă��邩���Ȃ�����Ԃ�
	return m_bHitFlag;
}
