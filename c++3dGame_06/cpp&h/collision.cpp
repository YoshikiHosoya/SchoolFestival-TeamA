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
#include "line.h"
#include "player.h"

#ifdef _DEBUG
#include "debugproc.h"
#include "debugcollision.h"
#include "player.h"
#endif // _DEBUG

//=============================================================================
//
// �}�N����`
//
//=============================================================================
#define COLLISION_FILE "data/LOAD/collision.txt"

//=============================================================================
//
// �O���[�o���ϐ�
//
//=============================================================================

//=============================================================================
//
// �ÓI�ϐ�
//
//=============================================================================
int CCollision::m_nAll = 0;				// ����
int CCollision::m_nNumLoad = 0;			// ���[�h��
CCollision * CCollision::m_pTop = NULL;	// �擪�I�u�W�F�N�g�ւ̃|�C���^
CCollision * CCollision::m_pCur = NULL;	// ���݃I�u�W�F�N�g�ւ̃|�C���^
CCollision::INFO CCollision::m_Info[128] = {};			// ���

// ----------------------------------------
// �R���X�g���N�^
// ----------------------------------------
CCollision::CCollision()
{
	// ������
	m_ID = m_nAll;								// �ԍ�
	m_objtype = OBJTYPE_PLAYER;						// �^�C�v
	m_ppos = NULL;								// �ʒu���
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �O��̈ʒu���
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �T�C�Y���
	m_pmove = NULL;								// �ړ����
	/* ���݂̓z */
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
	m_nAll++;
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
	if(m_objtype == OBJTYPE_PLAYER)	Collision();

	//if(m_objtype == OBJTYPE_ENEMY)	Collision();

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
void CCollision::Delete(int ID)
{
	// �ϐ��錾
	CCollision * pCollision;	// �V�[��
	CCollision *pCollisionNext;	// ���̃V�[��
	int nCnt = 0;
	// �擪�|�C���g���i�[
	pCollision = m_pTop;
	while (pCollision != NULL)
	{
		// ���̃|�C���^����
		pCollisionNext = pCollision->m_pNext;
		if (ID == nCnt)
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
			m_nAll--;
			delete pCollision;
			pCollision = NULL;
		}
		pCollision = pCollisionNext;
		nCnt++;
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
		m_nAll--;
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
	// �Ԃ�
	return pCollision;
}

// ----------------------------------------
// �ǂݍ��񂾂��̂𐶐�
// ----------------------------------------
void CCollision::LoadCreate(void)
{
	// �ϐ��錾
	CCollision * pCollision;	// �����蔻��
	for (int nCntLoad = 0; nCntLoad < m_nNumLoad; nCntLoad++)
	{
		pCollision = CCollision::Create();
		pCollision->SetPos(&m_Info[nCntLoad].pos);
		pCollision->SetSize(m_Info[nCntLoad].size);
		pCollision->SetMove(NULL);
		pCollision->SetType(CCollision::OBJTYPE_WAIT);
	}
}

// ----------------------------------------
// �ǂݍ��񂾂��̂𐶐�
// ----------------------------------------
void CCollision::LoadCreate2D(void)
{
	// �ϐ��錾
	CCollision * pCollision;	// �����蔻��
	for (int nCntLoad = 0; nCntLoad < m_nNumLoad; nCntLoad++)
	{
		pCollision = CCollision::Create();
		pCollision->SetPos(&m_Info[nCntLoad].pos);
		pCollision->SetSize2D(m_Info[nCntLoad].size);
		pCollision->SetMove(NULL);
		pCollision->SetType(CCollision::OBJTYPE_WAIT);
	}
}

// ----------------------------------------
// �I�u�W�F�N�g��ǂݍ���Ő������鎞�ɐ�������
// ----------------------------------------
CCollision * CCollision::Create_Single(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �ϐ��錾
	CCollision * pCollision;	// �����蔻��
	pCollision = CCollision::Create();
	pCollision->SetPos(&pos);
	pCollision->SetSize2D(size);
	pCollision->SetMove(NULL);
	pCollision->SetType(CCollision::OBJTYPE_WAIT);
	return pCollision;
}

// ----------------------------------------
// �ʒu�ݒ菈��
// ----------------------------------------
void CCollision::SetPos(D3DXVECTOR3 * pos)
{
	m_ppos = pos;
	m_posOld = *pos;
}

// ----------------------------------------
// �T�C�Y�ݒ菈��
// ----------------------------------------
void CCollision::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
#ifdef _DEBUG
	CDebugcollision::Create(m_ppos, &m_size, CDebugcollision::COLLISIONTYPE_BOX);
#endif // _DEBUG
}

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
bool CCollision::Collision_Come(void)
{
	// �ϐ��錾
	CCollision * pCollision = NULL;
	CCollision *pCollisionNext;	// ���̃V�[��
	bool bOn = false;			// ��ɂ��邩�ǂ���
	// �擪�|�C���g���i�[
	pCollision = m_pTop;
	while (pCollision != NULL)
	{
		// ���̃|�C���^����
		pCollisionNext = pCollision->m_pNext;

		if (pCollision != this)
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
						bOn = true;
					}

					// �����蔻��(�E)
					else if (this->m_ppos->x - this->m_size.x * 0.5f < pCollision->m_ppos->x + pCollision->m_size.x * 0.5f&&
						m_posOld.x - this->m_size.x * 0.5f >= pCollision->m_ppos->x + pCollision->m_size.x * 0.5f)
					{
						// �f�ޏ�̍���
						this->m_ppos->x = pCollision->m_ppos->x + pCollision->m_size.x * 0.5f + this->m_size.x * 0.5f;
						bOn = true;
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
						this->m_ppos->z = pCollision->m_ppos->z -
							pCollision->m_size.z * 0.5f -
							this->m_size.z * 0.5f;
						bOn = true;
					}

					// �����蔻��(��)
					else if (this->m_ppos->z - this->m_size.z * 0.5f < pCollision->m_ppos->z + pCollision->m_size.z * 0.5f&&
						m_posOld.z - this->m_size.z * 0.5f >= pCollision->m_ppos->z + pCollision->m_size.z * 0.5f)
					{
						// �f�ޏ�̍���
						this->m_ppos->z = pCollision->m_ppos->z +
							pCollision->m_size.z * 0.5f +
							this->m_size.z * 0.5f + 0.1f;
						bOn = true;
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
						bOn = true;
					}

					// �����蔻��(��)
					else if (this->m_ppos->y - this->m_size.y * 0.5f < pCollision->m_ppos->y + pCollision->m_size.y * 0.5f&&
						m_posOld.y - this->m_size.y * 0.5f >= pCollision->m_ppos->y + pCollision->m_size.y * 0.5f)
					{
						// �f�ޏ�̍���
						this->m_ppos->y = pCollision->m_ppos->y + pCollision->m_size.y * 0.5f + this->m_size.y * 0.5f;
						// �ړ��ʂ̏�����
						this->m_pmove->y = 0.0f;
						bOn = true;
					}
				}
			}
		}
		pCollision = pCollisionNext;
	}
	return bOn;
}


// ----------------------------------------
// ���^�̓����蔻�菈�� �v���C���[�p
// ----------------------------------------
bool CCollision::Collision_Player(void)
{
	// �ϐ��錾
	CCollision * pCollision = NULL;
	CCollision *pCollisionNext;	// ���̃V�[��
	bool bOn = false;			// ��ɂ��邩�ǂ���
								// �擪�|�C���g���i�[
	pCollision = m_pTop;

	CPlayer *pPlayer = NULL;	// �v���C���[

	for (int nCntlayer = 0; nCntlayer < CScene::GetMaxLayer(CScene::LAYER_3DOBJECT); nCntlayer++)
	{
		if (pPlayer = (CPlayer *)CScene::GetActor(CScene::ACTOR_PLAYER, CScene::LAYER_3DOBJECT, nCntlayer)) break;
	}

	while (pCollision != NULL)
	{
		// ���̃|�C���^����
		pCollisionNext = pCollision->m_pNext;

		if (pCollision != this)
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
						bOn = true;
					}

					// �����蔻��(�E)
					else if (this->m_ppos->x - this->m_size.x * 0.5f < pCollision->m_ppos->x + pCollision->m_size.x * 0.5f&&
						m_posOld.x - this->m_size.x * 0.5f >= pCollision->m_ppos->x + pCollision->m_size.x * 0.5f)
					{
						// �f�ޏ�̉E��
						this->m_ppos->x = pCollision->m_ppos->x + pCollision->m_size.x * 0.5f + this->m_size.x * 0.5f;
						bOn = true;
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
						// �f�ޏ�̎�O��
						this->m_ppos->z = pCollision->m_ppos->z -
							pCollision->m_size.z * 0.5f -
							this->m_size.z * 0.5f;
						bOn = true;
					}

					// �����蔻��(��)
					else if (this->m_ppos->z - this->m_size.z * 0.5f < pCollision->m_ppos->z + pCollision->m_size.z * 0.5f&&
						m_posOld.z - this->m_size.z * 0.5f >= pCollision->m_ppos->z + pCollision->m_size.z * 0.5f)
					{
						// �f�ޏ�̉���
						this->m_ppos->z = pCollision->m_ppos->z +
							pCollision->m_size.z * 0.5f +
							this->m_size.z * 0.5f + 0.1f;
						bOn = true;
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
						// �f�ޏ�̉���
						this->m_ppos->y = this->m_posOld.y;
						// �ړ��ʂ̏�����
						this->m_pmove->y = 0.0f;
						bOn = true;
					}

					// �����蔻��(��)
					else if (this->m_ppos->y - this->m_size.y * 0.5f < pCollision->m_ppos->y + pCollision->m_size.y * 0.5f&&
						m_posOld.y - this->m_size.y * 0.5f >= pCollision->m_ppos->y + pCollision->m_size.y * 0.5f)
					{
						// �f�ޏ�̏��
						this->m_ppos->y = pCollision->m_ppos->y + pCollision->m_size.y * 0.5f + this->m_size.y * 0.5f;
						// �ړ��ʂ̏�����
						this->m_pmove->y = 0.0f;
						bOn = true;
					}
				}
			}
		}
		pCollision = pCollisionNext;
	}
	return bOn;
}

// ----------------------------------------
// ���^�̓����蔻�菈��
// ----------------------------------------
void CCollision::Collision(void)
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

		if (pCollision != this)
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
					}

					// �����蔻��(�E)
					else if (this->m_ppos->x - this->m_size.x * 0.5f < pCollision->m_ppos->x + pCollision->m_size.x * 0.5f&&
						m_posOld.x - this->m_size.x * 0.5f >= pCollision->m_ppos->x + pCollision->m_size.x * 0.5f)
					{
						// �f�ޏ�̍���
						this->m_ppos->x = pCollision->m_ppos->x + pCollision->m_size.x * 0.5f + this->m_size.x * 0.5f;
						// �ړ��ʂ̏�����
						this->m_pmove->x = 0.0f;
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
					}

					// �����蔻��(��)
					else if (this->m_ppos->y - this->m_size.y * 0.5f < pCollision->m_ppos->y + pCollision->m_size.y * 0.5f&&
						m_posOld.y - this->m_size.y * 0.5f >= pCollision->m_ppos->y + pCollision->m_size.y * 0.5f)
					{
						// �f�ޏ�̍���
						this->m_ppos->y = pCollision->m_ppos->y + pCollision->m_size.y * 0.5f + this->m_size.y * 0.5f;
						// �ړ��ʂ̏�����
						this->m_pmove->y = 0.0f;
					}
				}
			}
		}
		pCollision = pCollisionNext;
	}
}

// ----------------------------------------
// �ǂݍ��ݏ���
// ----------------------------------------
void CCollision::Load(void)
{
	// �e�L�X�g�f�[�^�̓ǂݍ���
	m_nNumLoad = TextLoad();
}

// ----------------------------------------
// �ǂݍ���
// ----------------------------------------
int CCollision::TextLoad(void)
{
	// �t�@�C���|�C���g
	FILE *pFile;

	// �ϐ��錾
	int	nCntColli = 0;		// ���f���J�E���g
	char cRaedText[128];	// �����Ƃ��ēǂݎ��p
	char cHeadText[128];	// ��r����悤
	char cDie[128];			// �s�K�v�ȕ���

	// �t�@�C���J
	pFile = fopen(COLLISION_FILE, "r");

	// �J����
	if (pFile != NULL)
	{
		// �X�N���v�g������܂Ń��[�v
		while (strcmp(cHeadText, "SCRIPT") != 0)
		{
			fgets(cRaedText, sizeof(cRaedText), pFile);	// �ꕶ��ǂݍ���
			sscanf(cRaedText, "%s", &cHeadText);		// ��r�p�e�N�X�g�ɕ�������
		}

		// �X�N���v�g��������
		if (strcmp(cHeadText, "SCRIPT") == 0)
		{
			// �G���h�X�N���v�g������܂Ń��[�v
			while (strcmp(cHeadText, "END_SCRIPT") != 0)
			{
				// ������
				cHeadText[0] = '\0';
				fgets(cRaedText, sizeof(cRaedText), pFile);
				sscanf(cRaedText, "%s", &cHeadText);
				// �R���W�����Z�b�g������
				if (strcmp(cHeadText, "COLLISION") == 0)
				{
					// �G���h�R���W�����Z�b�g������܂Ń��[�v
					while (strcmp(cHeadText, "END_COLLISION") != 0)
					{
						// ������
						cHeadText[0] = '\0';
						fgets(cRaedText, sizeof(cRaedText), pFile);
						sscanf(cRaedText, "%s", &cHeadText);
						// �e���ǂݍ���
						if (strcmp(cHeadText, "OBJTYPE") == 0)
						{
							sscanf(cRaedText, "%s %s %d", &cDie, &cDie,
								&m_Info[nCntColli].type);
						}
						// �ʒu���ǂݍ���
						else if (strcmp(cHeadText, "POS") == 0)
						{
							sscanf(cRaedText, "%s %s %f %f %f",
								&cDie, &cDie,
								&m_Info[nCntColli].pos.x,
								&m_Info[nCntColli].pos.y,
								&m_Info[nCntColli].pos.z);
						}
						// ��]���ǂݍ���
						else if (strcmp(cHeadText, "SIZE") == 0)
						{
							sscanf(cRaedText, "%s %s %f %f %f", &cDie, &cDie,
								&m_Info[nCntColli].size.x,
								&m_Info[nCntColli].size.y,
								&m_Info[nCntColli].size.z);
						}
					}
					// ���f���̍X�V
					nCntColli++;
				}
			}
		}
		// �t�@�C����
		fclose(pFile);
	}

	// �J���Ȃ�
	else
	{
		MessageBox(NULL, "�����蔻��ǂݍ��݂Ɏ��s���܂���", "�x���I", MB_ICONWARNING);
	}

	return nCntColli;
}
