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
CCollision * CCollision::m_pTop = NULL;	// �擪�I�u�W�F�N�g�ւ̃|�C���^
CCollision * CCollision::m_pCur = NULL;	// ���݃I�u�W�F�N�g�ւ̃|�C���^

// ----------------------------------------
// �R���X�g���N�^
// ----------------------------------------
CCollision::CCollision()
{
	m_objtype			= OBJTYPE_PLAYER;					// �^�C�v�̏�����
	m_ppos				= NULL;								// �ʒu���
	m_posOld			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �O��̈ʒu���
	m_size				= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �T�C�Y���
	m_pmove				= NULL;								// �ړ����
	m_Debugcollision	= NULL;								// �f�o�b�O�p�����蔻��̃|�C���^
	m_bHitFlag			= false;							// �������Ă��邩�ǂ���

	/* ���݂̃|�C���^ */
	if (m_pCur != NULL)
	{
		// �O�̃I�u�W�F�N�g�̃|�C���^
		this->m_pPrey = m_pCur;
		// ���̃I�u�W�F�N�g�̃|�C���^
		m_pCur->m_pNext = this;
	}
	// ���݂̃|�C���^
	m_pCur = this;

	// �擪�I�u�W�F�N�g�̃|�C���^
	if (m_pTop == NULL)
	{
		m_pTop = this;
	}
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
	// �I�u�W�F�N�g�^�C�v���v���C���[�������瓖���蔻�����������
	m_posOld = *m_ppos;
}

// ----------------------------------------
// �����蔻��S�̂̍X�V
// ----------------------------------------
void CCollision::UpdateAll(void)
{
	// �ϐ��錾
	CCollision * pCollision = NULL;
	CCollision *pCollisionNext = NULL;	// ���̃V�[��
	// �擪�|�C���g���i�[
	pCollision = m_pTop;
	while (pCollision != NULL)
	{
		// ���̃|�C���^����
		pCollisionNext = pCollision->m_pNext;
		pCollision->Update();
		pCollision = pCollisionNext;
	}
}

// ----------------------------------------
// �����蔻��폜
// ----------------------------------------
void CCollision::Delete(CCollision *pColl)
{
	// �ϐ��錾
	CCollision * pCollision;	// �V�[��
	CCollision *pCollisionNext;	// ���̃V�[��
	// �擪�|�C���g���i�[
	pCollision = m_pTop;
	while (pCollision != NULL)
	{
		// ���̃|�C���^����
		pCollisionNext = pCollision->m_pNext;
		if (pColl == pCollision)
		{
			// �擪�ƌ��݂̃I�u�W�F�N�g�̃|�C���^�������ꍇ
			if (pCollision == m_pTop && pCollision == m_pCur)
			{
				m_pTop = NULL;
				m_pCur = NULL;
			}
			// �擪�I�u�W�F�N�g�̃|�C���^�̕ύX
			else if (pCollision == m_pTop)
			{
				m_pTop = pCollisionNext;
				m_pTop->m_pPrey = NULL;
			}
			// ���݂̃I�u�W�F�N�g�̃|�C���^�̕ύX
			else if (pCollision == m_pCur)
			{
				m_pCur = pCollision->m_pPrey;
				m_pCur->m_pNext = NULL;
			}
			// �Ԃ̃R�l�N�g
			else
			{
				// �O��̎��̏�����
				pCollision->m_pPrey->m_pNext = pCollisionNext;
				// ���̑O��̏�����
				pCollisionNext->m_pPrey = pCollision->m_pPrey;
			}
			// ���C���[�_�E��
			delete pCollision;
			pCollision = NULL;
		}
		pCollision = pCollisionNext;
	}
}

// ----------------------------------------
// �����蔻��S���폜
// ----------------------------------------
void CCollision::DeleteAll(void)
{
	// �ϐ��錾
	CCollision * pCollision;	// �V�[��
	CCollision *pCollisionNext;	// ���̃V�[��

	// �擪�|�C���g���i�[
	pCollision = m_pTop;
	while (pCollision != NULL)
	{
		// ���̃|�C���^����
		pCollisionNext = pCollision->m_pNext;
		// �擪�ƌ��݂̃I�u�W�F�N�g�̃|�C���^�������ꍇ
		if (pCollision == m_pTop && pCollision == m_pCur)
		{
			m_pTop = NULL;
			m_pCur = NULL;
		}
		// �擪�I�u�W�F�N�g�̃|�C���^�̕ύX
		else if (pCollision == m_pTop)
		{
			m_pTop = pCollisionNext;
			m_pTop->m_pPrey = NULL;
		}
		// ���݂̃I�u�W�F�N�g�̃|�C���^�̕ύX
		else if (pCollision == m_pCur)
		{
			m_pCur = pCollision->m_pPrey;
			m_pCur->m_pNext = NULL;
		}
		// �Ԃ̃R�l�N�g
		else
		{
			// �O��̎��̏�����
			pCollision->m_pPrey->m_pNext = pCollisionNext;
			// ���̑O��̏�����
			pCollisionNext->m_pPrey = pCollision->m_pPrey;
		}
		// ���C���[�_�E��
		delete pCollision;
		pCollision = NULL;
		pCollision = pCollisionNext;
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
	return pCollision;
}

// ----------------------------------------
// �ʒu�ݒ菈��
// ----------------------------------------
void CCollision::SetPos(D3DXVECTOR3 * pos)
{
	m_ppos = pos;
	m_posOld = *pos;

#ifdef _DEBUG
	if (m_Debugcollision != NULL)
	{
		m_Debugcollision->SetPos(m_ppos);
	}
#endif // _DEBUG
}

// ----------------------------------------
// �T�C�Y�ݒ菈��
// ----------------------------------------
void CCollision::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
#ifdef _DEBUG
	// �f�o�b�O�p�̃��C���𐶐�
	m_Debugcollision = CDebugcollision::Create(m_ppos, &m_size, CDebugcollision::COLLISIONTYPE_BOX);
#endif // _DEBUG
}

// ----------------------------------------
// 2d�T�C�Y�ݒ菈��
// ----------------------------------------
void CCollision::SetSize2D(D3DXVECTOR3 size)
{
	m_size = size;
#ifdef _DEBUG
	CDebugcollision::Create(m_ppos, &m_size, CDebugcollision::COLLISIONTYPE_BOARD);
#endif
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
	// �ϐ��錾
	CCollision * pCollision = NULL;
	CCollision *pCollisionNext;	// ���̃V�[��
	// �擪�|�C���g���i�[
	pCollision = m_pTop;

	while (pCollision != NULL)
	{
		// ���̃|�C���^����
		pCollisionNext = pCollision->m_pNext;

		if (pCollision != this && pCollision->m_objtype == objtype)
		{
			// �f�ނ�Y�͈�
			if (this->m_ppos->y + this->m_size.y * 0.5f > pCollision->m_ppos->y - pCollision->m_size.y * 0.5f&&
				this->m_ppos->y - this->m_size.y * 0.5f < pCollision->m_ppos->y + pCollision->m_size.y * 0.5f)
			{
				// �f�ނ�Z�͈�
				if (this->m_ppos->z + this->m_size.z * 0.5f > pCollision->m_ppos->z - pCollision->m_size.z * 0.5f&&
					this->m_ppos->z - this->m_size.z * 0.5f < pCollision->m_ppos->z + pCollision->m_size.z * 0.5f)
				{
					// �����蔻��(��)
					if (this->m_ppos->x + this->m_size.x * 0.5f > pCollision->m_ppos->x - pCollision->m_size.x * 0.5f&&
						this->m_posOld.x + this->m_size.x * 0.5f <= pCollision->m_ppos->x - pCollision->m_size.x * 0.5f)
					{
						// �f�ޏ�̍���
						this->m_ppos->x = pCollision->m_ppos->x - pCollision->m_size.x * 0.5f - this->m_size.x * 0.5f;

						// �ړ��ʂ̏�����
						this->m_pmove->x = 0.0f;

						// �I�u�W�F�N�g�ɓ��������t���O
						m_bHitFlag = true;
					}

					// �����蔻��(�E)
					else if (this->m_ppos->x - this->m_size.x * 0.5f < pCollision->m_ppos->x + pCollision->m_size.x * 0.5f&&
						m_posOld.x - this->m_size.x * 0.5f >= pCollision->m_ppos->x + pCollision->m_size.x * 0.5f)
					{
						// �f�ޏ�̍���
						this->m_ppos->x = pCollision->m_ppos->x + pCollision->m_size.x * 0.5f + this->m_size.x * 0.5f;
						// �ړ��ʂ̏�����
						this->m_pmove->x = 0.0f;
						// �I�u�W�F�N�g�ɓ��������t���O
						m_bHitFlag = true;
					}
				}

				// �f�ނ�X�͈�
				if (this->m_ppos->x + this->m_size.x * 0.5f > pCollision->m_ppos->x - pCollision->m_size.x * 0.5f&&
					this->m_ppos->x - this->m_size.x * 0.5f < pCollision->m_ppos->x + pCollision->m_size.x * 0.5f)
				{
					// �����蔻��(��O)
					if (this->m_ppos->z + this->m_size.z * 0.5f > pCollision->m_ppos->z - pCollision->m_size.z * 0.5f&&
						m_posOld.z + this->m_size.z * 0.5f <= pCollision->m_ppos->z - pCollision->m_size.z * 0.5f)
					{
						// �f�ޏ�̍���
						this->m_ppos->z = pCollision->m_ppos->z - pCollision->m_size.z * 0.5f - this->m_size.z * 0.5f;
						// �ړ��ʂ̏�����
						this->m_pmove->z = 0.0f;
						// �I�u�W�F�N�g�ɓ��������t���O
						m_bHitFlag = true;
					}

					// �����蔻��(��)
					else if (this->m_ppos->z - this->m_size.z * 0.5f < pCollision->m_ppos->z + pCollision->m_size.z * 0.5f&&
						m_posOld.z - this->m_size.z * 0.5f >= pCollision->m_ppos->z + pCollision->m_size.z * 0.5f)
					{
						// �f�ޏ�̍���
						this->m_ppos->z = pCollision->m_ppos->z +
							pCollision->m_size.z * 0.5f +
							this->m_size.z * 0.5f + 0.1f;
						// �ړ��ʂ̏�����
						this->m_pmove->z = 0.0f;
						// �I�u�W�F�N�g�ɓ��������t���O
						m_bHitFlag = true;
					}
				}
			}

			// �f�ނ�Z�͈�
			if (this->m_ppos->z + this->m_size.z * 0.5f > pCollision->m_ppos->z - pCollision->m_size.z * 0.5f&&
				this->m_ppos->z - this->m_size.z * 0.5f < pCollision->m_ppos->z + pCollision->m_size.z * 0.5f)
			{
				// �f�ނ�X�͈�
				if (this->m_ppos->x + this->m_size.x * 0.5f > pCollision->m_ppos->x - pCollision->m_size.x * 0.5f&&
					this->m_ppos->x - this->m_size.x * 0.5f < pCollision->m_ppos->x + pCollision->m_size.x * 0.5f)
				{
					// �����蔻��(��)
					if (this->m_ppos->y + this->m_size.y * 0.5f > pCollision->m_ppos->y - pCollision->m_size.y * 0.5f&&
						m_posOld.y + this->m_size.y * 0.5f <= pCollision->m_ppos->y - pCollision->m_size.y * 0.5f)
					{
						// �f�ޏ�̍���
						this->m_ppos->y = this->m_posOld.y;
						// �ړ��ʂ̏�����
						this->m_pmove->y = 0.0f;
						// �I�u�W�F�N�g�ɓ��������t���O
						m_bHitFlag = true;
					}

					// �����蔻��(��)
					else if (this->m_ppos->y - this->m_size.y * 0.5f < pCollision->m_ppos->y + pCollision->m_size.y * 0.5f&&
						m_posOld.y - this->m_size.y * 0.5f >= pCollision->m_ppos->y + pCollision->m_size.y * 0.5f)
					{
						// �f�ޏ�̍���
						this->m_ppos->y = pCollision->m_ppos->y + pCollision->m_size.y * 0.5f + this->m_size.y * 0.5f;
						// �ړ��ʂ̏�����
						this->m_pmove->y = 0.0f;
						// �I�u�W�F�N�g�ɓ��������t���O
						m_bHitFlag = true;
					}
				}
			}
		}
		pCollision = pCollisionNext;
	}
	// �������Ă��邩���Ȃ�����Ԃ�
	return m_bHitFlag;
}
