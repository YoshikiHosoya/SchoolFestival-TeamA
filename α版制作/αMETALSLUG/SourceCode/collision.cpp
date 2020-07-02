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
#define MAX_RAY_LENGTH  (40)		//Ray�̍ő�̒���
#define RAY_FIRST_POINT (30.0f)		//Ray�̎n�_

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

				if (Penetration == false)
				{
					return bHitFlag;
				}
			}
			else
			{
				// ������͈̓t���O��false�ɂ���
				bHitFlag = false;
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

				if (Penetration == false)
				{
					return bHitFlag;
				}
			}
			else
			{
				// ������͈̓t���O��false�ɂ���
				bHitFlag = false;
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
					if (Penetration == false)
					{
						return bHitFlag;
					}
				}
				else
				{
					// ������͈̓t���O��false�ɂ���
					bHitFlag = false;
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
// �v���C���[�Ə�Q���ōs������ �v���C���[�̐ڐG����
//======================================================================================================================
bool CCollision::ForPlayer_ObstacleCollision()
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
// �v���C���[�ƕߗ��ōs������ �v���C���[�̐ڐG����
//======================================================================================================================
CPrisoner *CCollision::ForPlayer_PrisonerCollision()
{
	CPrisoner *pPrisoner = nullptr;
	CPrisoner *pSavePointer = nullptr;
	// �ߗ��̑�����
	for (int nCntPriso = 0; nCntPriso < CManager::GetBaseMode()->GetMap()->GetMaxPrisoner(); nCntPriso++)
	{
		pPrisoner = CManager::GetBaseMode()->GetMap()->GetPrisoner(nCntPriso);

		if (pPrisoner != pSavePointer)
		{
			if (pPrisoner != nullptr)
			{
				if (this->CharCollision2D(pPrisoner->GetCollision()))
				{
					if (pPrisoner->GetPrisonerState() == CPrisoner::PRISONER_STATE_STAY)
					{
						pPrisoner->SetPrisonerState(CPrisoner::PRISONER_STATE_DROPITEM);
						// ���̕ߗ��̃|�C���^�͎擾�ł��Ȃ��悤�ɂ���
						pSavePointer = pPrisoner;

						return pPrisoner;
					}

				}
			}

			else if (pPrisoner == nullptr)
			{
				return nullptr;
			}
		}
	}

	return pPrisoner;
}

//======================================================================================================================
// �v���C���[�ƃG�l�~�[�ōs������ �v���C���[�̐ڐG����
//======================================================================================================================
CEnemy * CCollision::ForPlayer_EnemyCollision()
{
	CEnemy *pEnemy = nullptr;
	// �ߗ��̑�����
	for (int nCntEnemy = 0; nCntEnemy < CManager::GetBaseMode()->GetMap()->GetMaxEnemy(); nCntEnemy++)
	{
		pEnemy = CManager::GetBaseMode()->GetMap()->GetEnemy(nCntEnemy);
		if (pEnemy != nullptr)
		{
			if (this->CharCollision2D(pEnemy->GetCollision()))
			{
			}
		}

		else if (pEnemy == nullptr)
		{
			return nullptr;
		}
	}

	return pEnemy;
}

//======================================================================================================================
// �v���C���[�ƃA�C�e���ōs������ �v���C���[�̐ڐG����
//======================================================================================================================
bool CCollision::ForPlayer_ItemCollision()
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

//======================================================================================================================
// ���C�̔���
//======================================================================================================================
bool CCollision::RayBlockCollision(CMap *pMap)
{
	// �n�`���� �ϐ��錾
	BOOL				bHitFlag			= false;	// ���肪�o�����̃t���O
	bool				bLand				= false;	// ���肪�o�����̃t���O
	float				fLandDistance		= 0;		// ����
	DWORD				dwHitIndex			= -1;		// �C���f�b�N�X
	float				fHitU				= 0;		// U
	float				fHitV				= 0;		// V
	D3DXMATRIX			invmat;							// �t�s����i�[����ϐ�
	D3DXVECTOR3			m_posAfter;						// �t�s��ŏo�����I�_�����i�[����
	D3DXVECTOR3			m_posBefore;					// �I�_�����i�[����
	D3DXVECTOR3			direction;						// �ϊ���̈ʒu�A�������i�[����ϐ��F
	std::vector<float>	vDistance;						// �����̔z��ۑ�
	float				fData				= 0.0f;		// �f�[�^

	// �}�b�v���f���̍ő吔���J��Ԃ�
	for (int nCnt = 0; nCnt < pMap->GetMaxModel(); nCnt++)
	{
		//	�t�s��̎擾
		D3DXMatrixInverse(&invmat, NULL, pMap->GetModel(nCnt)->GetMatrix());
		//	�t�s����g�p���A���C�n�_����ϊ��@�ʒu�ƌ����ŕϊ�����֐����قȂ�̂ŗv����
		D3DXVec3TransformCoord(&m_posBefore, &D3DXVECTOR3(this->m_ppos->x, this->m_ppos->y + RAY_FIRST_POINT, this->m_ppos->z), &invmat);
		//	���C�I�_����ϊ�
		D3DXVec3TransformCoord(&m_posAfter, &D3DXVECTOR3(this->m_ppos->x, this->m_ppos->y, this->m_ppos->z), &invmat);
		//	���C��������ϊ�
		D3DXVec3Normalize(&direction, &(m_posAfter - m_posBefore));
		//Ray���΂�
		D3DXIntersect(pMap->GetMesh(nCnt), &m_posBefore, &direction, &bHitFlag, &dwHitIndex, &fHitU, &fHitV, &fLandDistance, NULL, NULL);
		if (bHitFlag == TRUE)
		{
			//�����̕ۑ��ǉ�
			vDistance.emplace_back(fLandDistance);
		}
		else
		{
		}
	}
	//Ray�̃q�b�g���������������Ƃ�
	if (!vDistance.empty())
	{
		//�ŏ��̔�r�Ώ�
		fData = vDistance[0];
		for (unsigned int nCnt = 0; vDistance.size() > nCnt; nCnt++)
		{
			if (vDistance[nCnt] < fData)
			{
				//��r�Ώۂ���������������
				fData = vDistance[nCnt];
			}
		}
		if (fData < MAX_RAY_LENGTH)//Ray�̒����̎w�����
		{
			this->m_ppos->y = this->m_ppos->y - fData + MAX_RAY_LENGTH;
			bLand = true;
		}
		//Ray�̔��茗������Ȃ�������W�����v�ł��Ȃ�
		else
		{
			bLand = false;
		}
	}
	//Ray�ɔ��肪�Ȃ�������W�����v�ł��Ȃ�
	else
	{
		bLand = false;
	}

	// ����t���O��Ԃ�
	return bLand;
}

//======================================================================================================================
// ���C�̔���
//======================================================================================================================
bool CCollision::RayCollision(CMap * pMap)
{
	// �n�`���� �ϐ��錾
	BOOL				bHitFlag = false;			// ���肪�o�����̃t���O
	bool				bJudg = false;				// ���肪�o�����̃t���O
	float				fLandDistance = 0;			// ����
	DWORD				dwHitIndex = -1;			// �C���f�b�N�X
	float				fHitU = 0;					// U
	float				fHitV = 0;					// V
	D3DXMATRIX			invmat;						// �t�s����i�[����ϐ�
	D3DXVECTOR3			m_posAfter;					// �t�s��ŏo�����I�_�����i�[����
	D3DXVECTOR3			m_posBefore;				// �I�_�����i�[����
	D3DXVECTOR3			direction;					// �ϊ���̈ʒu�A�������i�[����ϐ��F
	std::vector<float>	vDistance;					// �����̔z��ۑ�
	float				fData = 0.0f;				// �f�[�^

													// �}�b�v���f���̍ő吔���J��Ԃ�
	for (int nCnt = 0; nCnt < pMap->GetMaxModel(); nCnt++)
	{
		//	�t�s��̎擾
		D3DXMatrixInverse(&invmat, NULL, pMap->GetModel(nCnt)->GetMatrix());
		//	�t�s����g�p���A���C�n�_����ϊ��@�ʒu�ƌ����ŕϊ�����֐����قȂ�̂ŗv����
		D3DXVec3TransformCoord(&m_posBefore, &D3DXVECTOR3(this->m_ppos->x, this->m_ppos->y + RAY_FIRST_POINT, this->m_ppos->z), &invmat);
		//	���C�I�_����ϊ�
		D3DXVec3TransformCoord(&m_posAfter, &D3DXVECTOR3(this->m_ppos->x, this->m_ppos->y, this->m_ppos->z), &invmat);
		//	���C��������ϊ�
		D3DXVec3Normalize(&direction, &(m_posAfter - m_posBefore));
		//Ray���΂�
		D3DXIntersect(pMap->GetMesh(nCnt), &m_posBefore, &direction, &bHitFlag, &dwHitIndex, &fHitU, &fHitV, &fLandDistance, NULL, NULL);
		if (bHitFlag == TRUE)
		{
			//�����̕ۑ��ǉ�
			vDistance.emplace_back(fLandDistance);
		}
		else
		{
		}
	}
	//Ray�̃q�b�g���������������Ƃ�
	if (!vDistance.empty())
	{
		//�ŏ��̔�r�Ώ�
		fData = vDistance[0];
		for (unsigned int nCnt = 0; vDistance.size() > nCnt; nCnt++)
		{
			if (vDistance[nCnt] < fData)
			{
				//��r�Ώۂ���������������
				fData = vDistance[nCnt];
			}
		}
		if (fData < MAX_RAY_LENGTH)//Ray�̒����̎w�����
		{
			//this->m_ppos->y = this->m_ppos->y - fData + MAX_RAY_LENGTH;
			bJudg = true;
		}
		//Ray�̔��茗������Ȃ�������W�����v�ł��Ȃ�
		else
		{
			bJudg = false;
		}
	}
	//Ray�ɔ��肪�Ȃ�������W�����v�ł��Ȃ�
	else
	{
		bJudg = false;
	}

	// ����t���O��Ԃ�
	return bJudg;
}
