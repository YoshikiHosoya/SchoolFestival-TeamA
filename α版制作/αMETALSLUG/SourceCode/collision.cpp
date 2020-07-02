//======================================================================================================================
//
// Collision�����̐���[calculation.cpp]
// Author : Fujiwara Masato
//
//======================================================================================================================

//======================================================================================================================
//
// �C���N���[�h�t�@�C��
//
//======================================================================================================================
#include "Collision.h"
#ifdef _DEBUG
#include "debugcollision.h"
#include "debugproc.h"
#endif // _DEBUG
#include "manager.h"
#include "game.h"
#include "scene.h"


// �����蔻��̂���
#include "Player.h"
#include "Enemy.h"
#include "map.h"
#include "Obstacle.h"
#include "prisoner.h"
#include "item.h"

//======================================================================================================================
//
// �}�N����`
//
//======================================================================================================================

//======================================================================================================================
//
// �ÓI�ϐ�
//
//======================================================================================================================

//======================================================================================================================
// �R���X�g���N�^
//======================================================================================================================
CCollision::CCollision()
{
	m_objtype			= COLLISION_PLAYERBULLET;				// �^�C�v�̏�����
	m_Collisiontype		= COLLISIONTYPE_NORMAL;				// �����蔻��̎��
	m_ppos				= nullptr;							// �ʒu���
	m_posOld			= nullptr;							// �O��̈ʒu���
	m_size				= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �T�C�Y���
	m_pmove				= nullptr;							// �ړ����
	m_Debugcollision	= nullptr;							// �f�o�b�O�p�����蔻��̃|�C���^
}

//======================================================================================================================
// �f�X�g���N�^
//======================================================================================================================
CCollision::~CCollision()
{
#ifdef _DEBUG

	// �f�o�b�O�p����̍폜
	if (m_Debugcollision != nullptr)
	{
		m_Debugcollision->DeleteDeCollision();
		//delete m_Debugcollision;
		m_Debugcollision = nullptr;
	}

#endif // _DEBUG

}

//======================================================================================================================
// ����������
//======================================================================================================================
void CCollision::Init(void)
{
}

//======================================================================================================================
// �I������
//======================================================================================================================
void CCollision::Uninit(void)
{
}

//======================================================================================================================
// �X�V����
//======================================================================================================================
void CCollision::Update(void)
{
//#ifdef _DEBUG
//	if (m_Debugcollision != nullptr)
//	{
//		m_Debugcollision->SetPos(m_ppos);
//	}
//#endif // _DEBUG
}

//======================================================================================================================
// ��������
//======================================================================================================================
CCollision * CCollision::Create(void)
{
	// �ϐ��錾
	CCollision * pCollision;	// �����蔻��
	// �������m��
	pCollision = new CCollision;
	// ������
	pCollision->Init();
	// �|�C���^��Ԃ�
	return pCollision;
}

//======================================================================================================================
// �f�o�b�O�p�����蔻�萶������
//======================================================================================================================
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

//======================================================================================================================
// �v���C���[�̒e���s������
//======================================================================================================================
bool CCollision::ForPlayerBulletCollision(int nEnemyDamage, int nObstacleDamage, bool Penetration)
{
	// �e�������Ƃ��Ɏg���t���O
	bool bHitFlag = false;

	// �����蔻�� ���肪�G�l�~�[��������
	// �G�̑�����
	for (int nCnt = 0; nCnt < CManager::GetBaseMode()->GetMap()->GetMaxEnemy(); nCnt++)
	{
		// �G�l�~�[�̃|�C���^�擾
		CEnemy *pEnemy = CManager::GetBaseMode()->GetMap()->GetEnemy(nCnt);
		if (pEnemy != nullptr)
		{
			// ����֐�
			if (this->OtherCollision2D(pEnemy->GetCollision()))
			{
				// �G�̃��C�t����
				pEnemy->CCharacter::AddDamage(nEnemyDamage);

				// �G�̃��C�t��0�ȉ��ɂȂ�����
				if (pEnemy->CCharacter::GetLife() <= 0)
				{
					pEnemy = nullptr;
				}

				// ������͈̓t���O��true�ɂ���
				bHitFlag = true;
			}
			else
			{
				// ������͈̓t���O��false�ɂ���
				bHitFlag = false;

				CDebugProc::Print("\n�e���G�ɓ������ĂȂ���I \n");
			}
		}
	}

	// �����蔻�� ���肪��Q����������
	// ��Q���̑�����
	for (int nCntObst = 0; nCntObst < CManager::GetBaseMode()->GetMap()->GetMaxObstacle(); nCntObst++)
	{
		CObstacle *pObstacle = CManager::GetBaseMode()->GetMap()->GetObstacle(nCntObst);
		if (pObstacle != nullptr)
		{
			if (this->Collision2D(pObstacle->GetCollision()))
			{
				// ��Q���̃��C�t����
				pObstacle->Hit(CObstacle::TYPE_BOX, nObstacleDamage);

				// �G�̃��C�t��0�ȉ��ɂȂ�����
				if (pObstacle->GetLife() <= 0)
				{
					// �|�C���^��null�ɂ���
					pObstacle = nullptr;
				}

				// ������͈̓t���O��true�ɂ���
				bHitFlag = true;
			}
			else
			{
				// ������͈̓t���O��false�ɂ���
				bHitFlag = false;

				CDebugProc::Print("\n�e����Q���ɓ������ĂȂ���I \n");
			}
		}
	}

	// �����蔻�� ���肪�ߗ���������
	// �ߗ��̑�����
	for (int nCntPriso = 0; nCntPriso < CManager::GetBaseMode()->GetMap()->GetMaxPrisoner(); nCntPriso++)
	{
		CPrisoner *pPrisoner = CManager::GetBaseMode()->GetMap()->GetPrisoner(nCntPriso);
		if (pPrisoner != nullptr)
		{
			if (pPrisoner->GetPrisonerState() == CPrisoner::PRISONER_STATE_STAY)
			{
				if (this->OtherCollision2D(pPrisoner->GetCollision()))
				{
					// �ߗ��̏�ԕω�
					pPrisoner->SetPrisonerState(CPrisoner::PRISONER_STATE_DROPITEM);
					// �|�C���^��null�ɂ���
					pPrisoner = nullptr;
					// ������͈̓t���O��true�ɂ���
					bHitFlag = true;
				}
				else
				{
					// ������͈̓t���O��false�ɂ���
					bHitFlag = false;;

					CDebugProc::Print("\n�e���ߗ��ɓ������ĂȂ���I \n");
				}
			}
		}
	}

	return bHitFlag;
}

//======================================================================================================================
// �G�l�~�[�̒e���s������
//======================================================================================================================
bool CCollision::ForEnemyCollision(int nPlayerDamage, bool Penetration)
{
	// ������m�F����t���O
	bool bHitFlag = false;

		// �����蔻�� ���肪�v���C���[��������
		// �G�l�~�[�̃|�C���^�擾
	CPlayer *pPlayer = CManager::GetBaseMode()->GetPlayer();
		if (pPlayer != nullptr)
		{
			// ����֐�
			if (this->OtherCollision2D(pPlayer->GetCollision()))
			{
				// �v���C���[�̃��C�t����
				pPlayer->CCharacter::AddDamage(nPlayerDamage);

				// �v���C���[�̃��C�t��0�ȉ��ɂȂ�����
				if (pPlayer->CCharacter::GetLife() <= 0)
				{
					// �|�C���^��null�ɂ���
					pPlayer = nullptr;
				}

				// ������͈̓t���O��true�ɂ���
				bHitFlag = true;
			}
			else
			{
				// ������͈̓t���O��false�ɂ���
				bHitFlag = false;

				CDebugProc::Print("\n�e���G�ɓ������ĂȂ���I \n");
			}
		}

	return bHitFlag;
}

//======================================================================================================================
// �v���C���[�ƃG�l�~�[�ōs������ �v���C���[�̐ڐG����
//======================================================================================================================
bool CCollision::ForPlayer_EnemyCollision(bool Penetration)
{
	// ������m�F����t���O
	bool bHitFlag = false;

	//���肪�G�l�~�[��������
	// �G�̑�����
	for (int nCnt = 0; nCnt < CManager::GetBaseMode()->GetMap()->GetMaxEnemy(); nCnt++)
	{
		CEnemy *pEnemy = CManager::GetBaseMode()->GetMap()->GetEnemy(nCnt);
		if (pEnemy != nullptr)
		{
			if (this->CharCollision2D(pEnemy->GetCollision()))
			{
				bHitFlag = true;
				CDebugProc::Print("\n���@���G�ɓ���������I\n");
			}
			else
			{
				bHitFlag = false;
				CDebugProc::Print("\n���@���G�ɓ������ĂȂ���I \n");
			}
		}
	}

	return bHitFlag;
}

//======================================================================================================================
// �v���C���[�Ə�Q���ōs������ �v���C���[�̐ڐG����
//======================================================================================================================
bool CCollision::ForPlayer_ObstacleCollision(bool Penetration)
{
	// ������m�F����t���O
	bool bHitFlag = false;
	//���肪��Q����������
	// ��Q���̂̑�����
	for (int nCntObst = 0; nCntObst < CManager::GetBaseMode()->GetMap()->GetMaxObstacle(); nCntObst++)
	{
		CObstacle *pObstacle = CManager::GetBaseMode()->GetMap()->GetObstacle(nCntObst);
		if (pObstacle != nullptr)
		{
			if (this->BlockCollision2D(pObstacle->GetCollision()))
			{
				bHitFlag = true;
				CDebugProc::Print("\n���@����Q���ɓ���������I\n");
			}
			else
			{
				bHitFlag = false;
				CDebugProc::Print("\n���@����Q���ɓ������ĂȂ���I \n");
			}
		}
	}
	return bHitFlag;
}

//======================================================================================================================
// �v���C���[�ƕߗ��ōs������ �v���C���[�̐ڐG����
//======================================================================================================================
bool CCollision::ForPlayer_PrisonerCollision(bool Penetration)
{
	// ������m�F����t���O
	bool bHitFlag = false;

	// �ߗ��̑�����
	for (int nCntPriso = 0; nCntPriso < CManager::GetBaseMode()->GetMap()->GetMaxPrisoner(); nCntPriso++)
	{
		CPrisoner *pPrisoner = CManager::GetBaseMode()->GetMap()->GetPrisoner(nCntPriso);
		if (pPrisoner != nullptr)
		{
			if (this->CharCollision2D(pPrisoner->GetCollision()))
			{
				bHitFlag = true;
				CDebugProc::Print("\n���@���ߗ��ɓ���������I\n");
			}
			else
			{
				bHitFlag = false;
				CDebugProc::Print("\n���@���ߗ��ɓ������ĂȂ���I \n");
			}
		}
	}
	return bHitFlag;
}

//======================================================================================================================
// �v���C���[�ƃA�C�e���ōs������ �v���C���[�̐ڐG����
//======================================================================================================================
bool CCollision::ForPlayer_ItemCollision(bool Penetration)
{
	// ������m�F����t���O
	bool bHitFlag = false;


	//���肪�A�C�e����������
	// �x�N�^�[�^�̕ϐ�
	std::vector<CScene*> SceneList;

	// �w�肵���I�u�W�F�N�g�̃|�C���^���擾
	CScene::GetSceneList(CScene::OBJTYPE_ITEM, SceneList);

	//�A�C�e���̑�����
	for (size_t nCnt = 0; nCnt < SceneList.size(); nCnt++)
	{
		CItem *pItem = (CItem*)SceneList[nCnt];
		if (pItem != nullptr)
		{
			if (this->OtherCollision2D(pItem->GetCollision()))
			{
				bHitFlag = true;
				// �A�C�e�����Ƃ̏�����ʂ�
				pItem->HitItem(pItem->GetItemType());
				pItem = nullptr;
			}
			else
			{
				bHitFlag = false;
			}
		}
	}
	return bHitFlag;
}

//======================================================================================================================
// �ʒu�ݒ菈��
//======================================================================================================================
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

//======================================================================================================================
// 1�t���[���O�̈ʒu�ݒ菈��
//======================================================================================================================
void CCollision::SetPosOld(D3DXVECTOR3 * posold)
{
	m_posOld = posold;
}

//======================================================================================================================
// �T�C�Y�ݒ菈��
//======================================================================================================================
void CCollision::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}

//======================================================================================================================
// 2d�T�C�Y�ݒ菈��
//======================================================================================================================
void CCollision::SetSize2D(D3DXVECTOR3 size)
{
	m_size = size;
}

//======================================================================================================================
// �ړ��ݒ菈��
//======================================================================================================================
void CCollision::SetMove(D3DXVECTOR3 * move)
{
	m_pmove = move;
}

//======================================================================================================================
// �^�C�v�ݒ菈��
//======================================================================================================================
void CCollision::SetType(COLLISION type)
{
	m_objtype = type;
}

//======================================================================================================================
// �^�̓����蔻�菈��
//======================================================================================================================
bool CCollision::Collision2D(CCollision *pCollision)
{
	// �ϐ��錾
	bool bHitFlag = false;

	if (pCollision != nullptr)
	{
		// X Y�͈̔�
		if (this->m_ppos->y + this->m_size.y * 0.5f >= pCollision->m_ppos->y - pCollision->m_size.y * 0.5f&&
			this->m_ppos->y - this->m_size.y * 0.5f <= pCollision->m_ppos->y + pCollision->m_size.y * 0.5f&&
			this->m_ppos->x + this->m_size.x * 0.5f > pCollision->m_ppos->x - pCollision->m_size.x * 0.5f&&
			this->m_ppos->x - this->m_size.x * 0.5f < pCollision->m_ppos->x + pCollision->m_size.x * 0.5f)
		{
			// �I�u�W�F�N�g�ɓ��������t���O
			bHitFlag = true;
		}

		else
		{
			bHitFlag = false;
		}
	}

	// �������Ă��邩���Ȃ�����Ԃ�
	return bHitFlag;
}

//======================================================================================================================
// �L�����N�^�[�p�^�̓����蔻�菈��
//======================================================================================================================
bool CCollision::CharCollision2D(CCollision * pCollision)
{
	// �ϐ��錾
	bool bHitFlag = false;

	if (pCollision != nullptr)
	{
		// X Y�͈̔�
		if (this->m_ppos->y + this->m_size.y >= pCollision->m_ppos->y&&
			this->m_ppos->y <= pCollision->m_ppos->y + pCollision->m_size.y&&
			this->m_ppos->x + this->m_size.x * 0.5f > pCollision->m_ppos->x - pCollision->m_size.x * 0.5f&&
			this->m_ppos->x - this->m_size.x * 0.5f < pCollision->m_ppos->x + pCollision->m_size.x * 0.5f)
		{
			// �I�u�W�F�N�g�ɓ��������t���O
			bHitFlag = true;
		}

		else
		{
			bHitFlag = false;
		}
	}

	// �������Ă��邩���Ȃ�����Ԃ�
	return bHitFlag;
}

//======================================================================================================================
// �L�����N�^�[�ƃA�C�e���A�e�̔���
//======================================================================================================================
bool CCollision::OtherCollision2D(CCollision * pCollision)
{
	// �e�������Ƃ��Ɏg���t���O
	bool bHitFlag = false;

	if (pCollision != nullptr)
	{
		// X Y�͈̔�
		if (this->m_ppos->y + this->m_size.y * 0.5f >= pCollision->m_ppos->y&&
			this->m_ppos->y - this->m_size.y * 0.5f <= pCollision->m_ppos->y + pCollision->m_size.y&&
			this->m_ppos->x + this->m_size.x * 0.5f > pCollision->m_ppos->x - pCollision->m_size.x * 0.5f&&
			this->m_ppos->x - this->m_size.x * 0.5f < pCollision->m_ppos->x + pCollision->m_size.x * 0.5f)

		{
			// �I�u�W�F�N�g�ɓ��������t���O
			bHitFlag = true;
		}

		else
		{
			bHitFlag = false;
		}
	}

	// �������Ă��邩���Ȃ�����Ԃ�
	return bHitFlag;
}

//======================================================================================================================
// �^�̃u���b�N�̓����蔻�菈��
//======================================================================================================================
bool CCollision::BlockCollision2D(CCollision * pCollision)
{
	// �e�������Ƃ��Ɏg���t���O
	bool bHitFlag = false;

		// �f�ނ�Y�͈�
		if (this->m_ppos->y + this->m_size.y > pCollision->m_ppos->y - pCollision->m_size.y * 0.5f &&
			this->m_ppos->y < pCollision->m_ppos->y + pCollision->m_size.y * 0.5f)
		{
			// �����蔻��(��)
			if (this->m_ppos->x + this->m_size.x * 0.5f > pCollision->m_ppos->x - pCollision->m_size.x * 0.5f &&
				this->m_posOld->x + this->m_size.x * 0.5f <= pCollision->m_ppos->x - pCollision->m_size.x * 0.5f)
			{
				// �f�ޏ�̍���
				this->m_ppos->x = pCollision->m_ppos->x - pCollision->m_size.x * 0.5f - this->m_size.x * 0.5f;
				// �ړ��ʂ̏�����
				this->m_pmove->x = 0.0f;
				// �I�u�W�F�N�g�ɓ��������t���O
				bHitFlag = true;
			}

			// �����蔻��(�E)
			else if (this->m_ppos->x - this->m_size.x * 0.5f < pCollision->m_ppos->x + pCollision->m_size.x * 0.5f &&
				this->m_posOld->x - this->m_size.x * 0.5f >= pCollision->m_ppos->x + pCollision->m_size.x * 0.5f)
			{
				// �f�ޏ�̍���
				this->m_ppos->x = pCollision->m_ppos->x + pCollision->m_size.x * 0.5f + this->m_size.x * 0.5f;
				// �ړ��ʂ̏�����
				this->m_pmove->x = 0.0f;
				// �I�u�W�F�N�g�ɓ��������t���O
				bHitFlag = true;
			}
		}

		// �f�ނ�X�͈�
		if (this->m_ppos->x + this->m_size.x * 0.5f > pCollision->m_ppos->x - pCollision->m_size.x * 0.5f &&
			this->m_ppos->x - this->m_size.x * 0.5f < pCollision->m_ppos->x + pCollision->m_size.x * 0.5f)
		{
			// �����蔻��(��)
			if (this->m_ppos->y + this->m_size.y > pCollision->m_ppos->y - pCollision->m_size.y * 0.5f &&
				this->m_posOld->y + this->m_size.y <= pCollision->m_ppos->y - pCollision->m_size.y * 0.5f)
			{
				// �f�ޏ�̉���
				this->m_ppos->y = this->m_posOld->y;
				// �ړ��ʂ̏�����
				this->m_pmove->y = 0.0f;
				// �I�u�W�F�N�g�ɓ��������t���O
				bHitFlag = true;
			}

			// �����蔻��(��)
			else if (this->m_ppos->y < pCollision->m_ppos->y + pCollision->m_size.y * 0.5f &&
				this->m_posOld->y >= pCollision->m_ppos->y + pCollision->m_size.y * 0.5f)
			{
				// �f�ޏ�̏��
				this->m_ppos->y = this->m_posOld->y;
				// �ړ��ʂ̏�����
				this->m_pmove->y = 0.0f;
				// �I�u�W�F�N�g�ɓ��������t���O
				bHitFlag = true;
			}
		}

	// �������Ă��邩���Ȃ�����Ԃ�
	return bHitFlag;
}