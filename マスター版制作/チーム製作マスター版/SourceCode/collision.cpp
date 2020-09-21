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
#include "playertank.h"
#include "BattlePlane.h"
#include "Character.h"
#include "scoremanager.h"
#include "player.h"
#include "playerui.h"
#include "shield.h"
#include "boss_One.h"
#include "ModelSet.h"
#include "bullet.h"

//======================================================================================================================
//
// �}�N����`
//
//======================================================================================================================
#define MAX_RAY_LENGTH  (60)		//Ray�̍ő�̒���
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
	m_Collisiontype		= COLLISIONTYPE_NORMAL;				// �����蔻��̎��
	m_ppos				= nullptr;							// �ʒu���
	m_posOld			= nullptr;							// �O��̈ʒu���
	m_size				= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �T�C�Y���
	m_pmove				= nullptr;							// �ړ����
	m_Debugcollision	= nullptr;							// �f�o�b�O�p�����蔻��̃|�C���^
	m_fHeight			= 30;								// ���̍����̏�����
	m_bCanCollision		= true;
	m_pGameObject		= nullptr;							// �Q�[���I�u�W�F�N�g( �^�O )�̃|�C���^
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
		m_Debugcollision->Rerease();
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
#ifdef _DEBUG
	if (m_Debugcollision != nullptr)
	{
		m_Debugcollision->SetPos(m_ppos);
	}
#endif // _DEBUG
}

//======================================================================================================================
// �f�o�b�O���\�L
//======================================================================================================================
void CCollision::ShowDebugInfo()
{
	if(ImGui::TreeNode("CollisionInfo"))
	{
		ImGui::Text("Pos >> %.2f %.2f %.2f", m_ppos->x, m_ppos->y, m_ppos->z);
		ImGui::Text("Size >> %.2f %.2f %.2f", m_size.x, m_size.y, m_size.z);
		ImGui::Text("CanCollision >> %d", m_bCanCollision);

		ImGui::TreePop();
	}

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
			CDebugcollision::COLLISIONTYPE_BOX);
	}break;

	case COLLISIONTYPE_CHARACTER: {
		m_Debugcollision = CDebugcollision::Create(
			m_ppos,
			&m_size,
			CDebugcollision::COLLISIONTYPE_BOX_CHARA);
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
	std::vector<CScene*> pSceneList, pSceneList_Bullet;

	// �v���C���[�̃|�C���^�擾
	CPlayer *pPlayer = CManager::GetBaseMode()->GetPlayer(m_pGameObject->GetTag());

	CScene::GetSceneList(CScene::OBJTYPE_SHIELD, pSceneList);
	CScene::GetSceneList(CScene::OBJTYPE_BULLET, pSceneList_Bullet);

	//�����蔻�菈��

	// �v���C���[�̒e�ƓG�̓���̃O���l�[�h�̔���
	//if (!pSceneList_Bullet.empty())
	//{
	//	for (size_t nCnt = 0; nCnt < pSceneList_Bullet.size(); nCnt++)
	//	{
	//		CBullet *pBullet = (CBullet*)pSceneList_Bullet[nCnt];

	//		// �o���b�g���G�̓���̃O���l�[�h��������
	//		if (pBullet->GetBullePoint() == )
	//		{
	//			if (this->Collision2D(pBullet->GetCollision()))
	//			{
	//				// �G�̃O���l�[�h�Ƀ_���[�W��^����
	//				pBullet->AddDamage(nEnemyDamage);

	//				// ������͈̓t���O��true�ɂ���
	//				bHitFlag = true;

	//				if (!Penetration)
	//				{
	//					return bHitFlag;
	//				}
	//			}
	//		}
	//	}
	//}

	//������̏ꍇ
	if (!pSceneList.empty())
	{
		for (size_t nCnt = 0; nCnt < pSceneList.size(); nCnt++)
		{
			CShield *pShield = (CShield*)pSceneList[nCnt];
			if (pShield)
			{
				if (this->Collision2D(pShield->GetCollision()))
				{
					pShield->AddDamage(nEnemyDamage);

					// ������͈̓t���O��true�ɂ���
					bHitFlag = true;

					if (!Penetration)
					{
						return bHitFlag;
					}
				}
			}
		}
	}


	// �����蔻�� ���肪�G�l�~�[��������
	// �G�̑�����
	for (int nCnt = 0; nCnt < CManager::GetBaseMode()->GetMap()->GetMaxEnemy(); nCnt++)
	{
		// �G�l�~�[�̃|�C���^�擾
		CEnemy *pEnemy = CManager::GetBaseMode()->GetMap()->GetEnemy(nCnt);

		if (pEnemy != nullptr)
		{
			if (pEnemy->GetModelSet()->GetCharacterType() == CModelSet::CHARACTER_TYPE_BOSS_ONE)
			{
				CBoss_One *pBoss_One = (CBoss_One*)pEnemy;

				if (pBoss_One->GetCollision() &&
					pBoss_One->GetPostureType() == CBoss_One::POSTURETYPE_STAND &&
					pBoss_One->GetBossOneType() == CBoss_One::ATTACKTYPE_FLAMERADIATION)
				{
					//���肪����Ƃ�
					if (pBoss_One->GetCollision()->GetCanCollison())
					{
						// ����֐�
						if (this->OtherCollision2D(pBoss_One->GetCollision()))
						{
							if (pPlayer != nullptr)
							{
								if (pPlayer->GetPlayerUI())
								{
									pPlayer->GetPlayerUI()->SetScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_DAMAGE_BULLET));
								}
							}

							// �G�̃��C�t����
							pBoss_One->CCharacter::AddDamage(nEnemyDamage);

							// ������͈̓t���O��true�ɂ���
							bHitFlag = true;

							if (Penetration == false)
							{
								return bHitFlag;
							}
						}
					}
				}

			}
			if (pEnemy->GetCollision())
			{
				//���肪����Ƃ�
				if (pEnemy->GetCollision()->GetCanCollison())
				{
					// ����֐�
					if (this->OtherCollision2D(pEnemy->GetCollision()))
					{
						if (pPlayer != nullptr)
						{
							if (pPlayer->GetPlayerUI())
							{
								pPlayer->GetPlayerUI()->SetScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_DAMAGE_BULLET));
							}
						}

						// �G�̃��C�t����
						pEnemy->CCharacter::AddDamage(nEnemyDamage);

						// ������͈̓t���O��true�ɂ���
						bHitFlag = true;

						if (Penetration == false)
						{
							return bHitFlag;
						}
					}
				}
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
					pObstacle->SetDieFlag(true);
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
		}
	}
	// ��Q���̑�����
	for (int nCntObst = 0; nCntObst < CManager::GetBaseMode()->GetMap()->GetMaxObstacle(); nCntObst++)
	{
		CObstacle *pObstacle = CManager::GetBaseMode()->GetMap()->GetObstacle(nCntObst);
		if (pObstacle != nullptr)
		{
			//���肪����Ƃ�
			if (pObstacle->GetCollision()->GetCanCollison())
			{
				if (this->Collision2D(pObstacle->GetCollision()))
				{
					// ��Q���̃��C�t����
					pObstacle->Hit(CObstacle::TYPE_BOX, nObstacleDamage);

					// ������͈̓t���O��true�ɂ���
					bHitFlag = true;

					if (Penetration == false)
					{
						return bHitFlag;
					}
				}
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
			//���肪����Ƃ�
			if (pPrisoner->GetCollision()->GetCanCollison())
			{
				if (this->OtherCollision2D(pPrisoner->GetCollision()))
				{
					if (pPlayer != nullptr)
					{
						if (pPlayer->GetPlayerUI())
						{
							pPlayer->GetPlayerUI()->SetScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_RESCUE_PRISONER));
							// �̗͂̉��Z
							pPlayer->SetLife(pPlayer->GetLife() + 1);
						}
					}

					// �ߗ��̏�ԕω�
					pPrisoner->SetPrisonerState(CPrisoner::PRISONER_STATE_THINKING);
					// �|�C���^��null�ɂ���
					pPrisoner = nullptr;
					// ������͈̓t���O��true�ɂ���
					bHitFlag = true;
					if (Penetration == false)
					{
						return bHitFlag;
					}
				}
			}
		}
	}
	return bHitFlag;
}

//======================================================================================================================
// �G�l�~�[�̒e���s������
//======================================================================================================================
bool CCollision::ForEnemyCollision(int nPlayerDamage, int nPlayerTankDamage, bool Penetration)
{
	// ������m�F����t���O
	bool bHitFlag = false;
	// �v���C���[�̃|�C���^
	CPlayer *pPlayer[MAX_CONTROLLER] = {};

	for (int nCntPlayer = 0; nCntPlayer < MAX_CONTROLLER; nCntPlayer++)
	{
		pPlayer[nCntPlayer] = CManager::GetBaseMode()->GetPlayer((TAG)nCntPlayer);

		if (pPlayer[nCntPlayer] != nullptr)
		{
			if (pPlayer[nCntPlayer]->GetRideFlag())
			{
				// �����蔻�� ���肪�v���C���[�p��Ԃ�������
				for (int nCntTank = 0; nCntTank < CManager::GetBaseMode()->GetMap()->GetMaxPlayerTank(); nCntTank++)
				{
					CPlayertank *pPlayertank = CManager::GetBaseMode()->GetMap()->GetPlayertank(nCntTank);
					if (pPlayertank != nullptr)
					{
						// ����֐�
						if (this->OtherCollision2D(pPlayertank->GetCollision()))
						{
							//// �v���C���[�̃��C�t����
							//pPlayertank->CVehicle::AddDamage(nPlayerTankDamage);

							//// �v���C���[�̃��C�t��0�ȉ��ɂȂ�����
							//if (pPlayertank->CVehicle::GetLife() <= 0)
							//{
							//	pPlayertank->SetDieFlag(true);
							//	// �|�C���^��null�ɂ���
							//	pPlayertank = nullptr;
							//}

							// ������͈̓t���O��true�ɂ���
							bHitFlag = true;
						}
						else
						{
							// ������͈̓t���O��false�ɂ���
							bHitFlag = false;
						}
					}
				}
			}
			else
			{
				// �����蔻�� ���肪�v���C���[��������
				if (pPlayer[nCntPlayer] != nullptr)
				{
					if (pPlayer[nCntPlayer]->GetCollision()->GetCanCollison())
					{
						// ����֐�
						if (this->OtherCollision2D(pPlayer[nCntPlayer]->GetCollision()))
						{
							// �v���C���[�̃��C�t����
							pPlayer[nCntPlayer]->CCharacter::AddDamage(nPlayerDamage);

							// ������͈̓t���O��true�ɂ���
							bHitFlag = true;
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
	}
	return bHitFlag;
}

//======================================================================================================================
// �v���C���[�ƃG�l�~�[�ōs������ �v���C���[�̐ڐG���� �t���O��Ԃ�
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
			if (pEnemy->GetCollision())
			{
				if (pEnemy->GetModelSet()->GetCharacterType() == CModelSet::CHARACTER_TYPE_BOSS_ONE)
				{
					CBoss_One *pBoss_One = (CBoss_One*)pEnemy;

					if (pBoss_One->GetCollision() &&
						pBoss_One->GetPostureType() == CBoss_One::POSTURETYPE_SQUAT)
					{
						if (this->BoxCollision2D_Character(pBoss_One->GetCollision()))
						{
							bHitFlag = true;
						}
					}
				}
				else
				{
					//�ʏ�̎G���I�̎�
					if (pEnemy->GetEnemyType() == CEnemy::ENEMY_TYPE::ENEMY_NORMAL ||
						pEnemy->GetEnemyType() == CEnemy::ENEMY_TYPE::ENEMY_SHIELD)
					{
						//���肪����Ƃ�
						if (pEnemy->GetCollision()->GetCanCollison())
						{
							if (this->CharCollision2D(pEnemy->GetCollision()))
							{
								bHitFlag = true;
							}
						}
					}
					//�G�̏�蕨�̏ꍇ
					else if (pEnemy->GetEnemyType() == CEnemy::ENEMY_TYPE::ENEMY_HELICOPTER ||
						pEnemy->GetEnemyType() == CEnemy::ENEMY_TYPE::ENEMY_MELTYHONEY ||
						pEnemy->GetEnemyType() == CEnemy::ENEMY_TYPE::ENEMY_ZYCOCCA)
					{
						//�Փ˔���
						if (this->BoxCollision2D_Vehicle(pEnemy->GetCollision()))
						{
							//������ڐG�����v���C���[�Ƀ_���[�W����
							CManager::GetGame()->GetPlayer(m_pGameObject->GetTag())->AddDamage(1);
						}
					}
				}
			}
		}
	}

	return bHitFlag;
}

//======================================================================================================================
// �v���C���[�Ɛ�Ԃōs������ �v���C���[�̐ڐG���� �|�C���^��Ԃ�
//======================================================================================================================
CPlayertank * CCollision::ForPlayer_TankCollision()
{
	CPlayertank *pPlayertank = nullptr;

	// ��Ԃ̑�����
	for (int nCntTank = 0; nCntTank < CManager::GetBaseMode()->GetMap()->GetMaxPlayerTank(); nCntTank++)
	{
		// ��Ԃ̃|�C���^���擾
		pPlayertank = CManager::GetBaseMode()->GetMap()->GetPlayertank(nCntTank);

		if (pPlayertank != nullptr)
		{
			if (this->ForPlayer_VehicleCollision(pPlayertank->GetCollision()))
			{
				// �������s������Ԃ̃|�C���^��Ԃ�
				return pPlayertank;
			}
		}

		// null��������null��Ԃ�
		else if (pPlayertank == nullptr)
		{
			return nullptr;
		}
	}

	// �|�C���^��Ԃ�
	return pPlayertank;
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
			if (this->BlockNotUpsideCollision2D(pObstacle->GetCollision()))
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
			//���肪����Ƃ�
			if (pPrisoner->GetCollision()->GetCanCollison())
			{
				if (this->CharCollision2D(pPrisoner->GetCollision()))
				{
					bHitFlag = true;
				}
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
	// �ߗ��̑�����
	for (int nCntPriso = 0; nCntPriso < CManager::GetBaseMode()->GetMap()->GetMaxPrisoner(); nCntPriso++)
	{
		// �ߗ��̃|�C���^���擾
		pPrisoner = CManager::GetBaseMode()->GetMap()->GetPrisoner(nCntPriso);

		if (pPrisoner != nullptr)
		{
			if (this->CharCollision2D(pPrisoner->GetCollision()))
			{
				if (pPrisoner->GetPrisonerState() == CPrisoner::PRISONER_STATE_STAY)
				{
					// �������s�����ߗ��̃|�C���^��Ԃ�
					return pPrisoner;
				}
			}
		}

		// null��������null��Ԃ�
		else if (pPrisoner == nullptr)
		{
			return nullptr;
		}
	}

	// �|�C���^��Ԃ�
	return pPrisoner;
}

//======================================================================================================================
// �v���C���[����蕨�ɏ�鎞�̔���
//======================================================================================================================
bool CCollision::ForPlayer_VehicleCollision(CCollision * pCollision)
{
	// ������m�F����t���O
	bool bHitFlag = false;

	if (this->VehicleCollision(pCollision))
	{
		bHitFlag = true;
	}
	return bHitFlag;
}

//======================================================================================================================
// �v���C���[����蕨�ɏ�鎞�̔���
//======================================================================================================================
CVehicle *CCollision::ForPlayer_VehicleCollision()
{
	CPlayertank *pPlayertank = nullptr;

	// ��Ԃ̑�����
	for (int nCntTank = 0; nCntTank < CManager::GetBaseMode()->GetMap()->GetMaxPlayerTank(); nCntTank++)
	{
		// ��Ԃ̃|�C���^���擾
		pPlayertank = CManager::GetBaseMode()->GetMap()->GetPlayertank(nCntTank);

		if (pPlayertank != nullptr)
		{
			if (pPlayertank->GetRideerTag() == TAG::NONE)
			{
				if (this->VehicleCollision(pPlayertank->GetCollision()))
				{
					return pPlayertank;
				}
			}
		}
	}
	return nullptr;
}

//======================================================================================================================
// ��蕨���s������
//======================================================================================================================
bool CCollision::ForVehicleCollision()
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
			//if (pItem->GetItemType() == CItem::ITEMTYPE_BEAR ||
				//pItem->GetItemType() == CItem::ITEMTYPE_ENERGYUP||
				//pItem->GetItemType() == CItem::ITEMTYPE_BOMBUP||
				//pItem->GetItemType() == CItem::ITEMTYPE_BULLETUP)
		//	{
				if (pItem->GetCollision()->OtherCollision2D(this))
				{
					bHitFlag = true;
					// �A�C�e�����Ƃ̏�����ʂ�
					pItem->HitItem(pItem->GetItemType(), TAG::PLAYER_1);
					pItem = nullptr;
				}
			//}
		}
	}

	return bHitFlag;
}

//======================================================================================================================
// ��Ԃ��s������
//======================================================================================================================
bool CCollision::ForTankCollision()
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
				pEnemy->AddDamage(1);
			}
		}
	}

	return false;
}


//======================================================================================================================
// �{�X���s������
//======================================================================================================================
void CCollision::ForBossOne_PlayerCollision()
{
	//���肪�G�l�~�[��������
	// �G�̑�����
	for (int nCnt = 0; nCnt < CManager::GetBaseMode()->GetMap()->GetMaxEnemy(); nCnt++)
	{
		CEnemy *pEnemy = CManager::GetBaseMode()->GetMap()->GetEnemy(nCnt);
		if (pEnemy != nullptr)
		{
			if (pEnemy->GetEnemyType() == CEnemy::ENEMY_TYPE::ENEMY_NORMAL)
			{
				CBoss_One *pBoss_One = (CBoss_One*)pEnemy;

			}
		}
	}
}

//======================================================================================================================
// �{�X���s������
//======================================================================================================================
bool CCollision::BossOne_PlayerCollision()
{
	// ������m�F����t���O
	bool bHitFlag = false;
	// �v���C���[�̃|�C���^
	CPlayer *pPlayer[MAX_CONTROLLER] = {};

	//���肪�G�l�~�[��������
	// �G�̑�����
	for (int nCnt = 0; nCnt < CManager::GetBaseMode()->GetMap()->GetMaxEnemy(); nCnt++)
	{
		CEnemy *pEnemy = CManager::GetBaseMode()->GetMap()->GetEnemy(nCnt);
		if (pEnemy != nullptr)
		{
			if (pEnemy->GetModelSet()->GetCharacterType() == CModelSet::CHARACTER_TYPE_BOSS_ONE)
			{
				CBoss_One *pBoss_One = (CBoss_One*)pEnemy;

				if (pBoss_One->GetCollision() &&
					pBoss_One->GetIntermediateSquat())
				{
					for (int nCntPlayer = 0; nCntPlayer < MAX_CONTROLLER; nCntPlayer++)
					{
						// �v���C���[�̃|�C���^�擾
						pPlayer[nCntPlayer] = CManager::GetBaseMode()->GetPlayer((TAG)nCntPlayer);

						if (pPlayer[nCntPlayer] != nullptr)
						{
							if (this->BlockCollision2D_Bottom(pPlayer[nCntPlayer]->GetCollision()))
							{
								// �G�̃��C�t����
								pPlayer[nCntPlayer]->CCharacter::AddDamage(1);

								bHitFlag = true;
							}
						}
					}
				}
			}
		}
	}

	return bHitFlag;
}

//======================================================================================================================
// �i�C�t�ƃL�����N�^�[�̔���
//======================================================================================================================
bool CCollision::KnifeCollision(D3DXVECTOR3 Knifepos, CCollision *pCollision)
{
	// �e�������Ƃ��Ɏg���t���O
	bool bHitFlag = false;

	if (pCollision != nullptr)
	{
		// X Y�͈̔�
		if (Knifepos.y + this->m_size.y * 0.5f >= pCollision->m_ppos->y&&
			Knifepos.y - this->m_size.y * 0.5f <= pCollision->m_ppos->y + pCollision->m_size.y&&
			Knifepos.x + this->m_size.x * 0.5f > pCollision->m_ppos->x - pCollision->m_size.x * 0.5f&&
			Knifepos.x - this->m_size.x * 0.5f < pCollision->m_ppos->x + pCollision->m_size.x * 0.5f)

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
// ���[�U�[�̔���
//======================================================================================================================
bool CCollision::LazerCollisionGetLength(D3DXVECTOR3 ShotPos, float &fLength)
{
	bool bHitFlag = false;								//�t���O
	float fValue = 0.0f;								//�v�Z�����l
	CShield *pShield = nullptr;							//���̃|�C���^
	CObstacle *pObstacle = nullptr;						//�I�u�W�F�N�g�̃|�C���^
	CEnemy *pEnemy = nullptr;						//�G�̃|�C���^

	CGameObject *pMostNearObject = nullptr;				//��ԋ߂��I�u�W�F�N�g�̃|�C���^
	std::vector<CScene*> pSceneList = {};				//Scene�̃��X�g

	//���̃��X�g�擾
	CScene::GetSceneList(CScene::OBJTYPE_SHIELD, pSceneList);

	//�����蔻�菈��
	//������̏ꍇ
	if (!pSceneList.empty())
	{
		for (size_t nCnt = 0; nCnt < pSceneList.size(); nCnt++)
		{
			//pShield�^�ɃL���X�g
			pShield = (CShield*)pSceneList[nCnt];

			//nullcheck
			if (!pShield)
			{
				continue;
			}
			//���肪���݂��鎞
			if (!pShield->GetCollision())
			{
				continue;
			}
			//���肪����Ƃ�
			if (!pShield->GetCollision()->GetCanCollison())
			{
				continue;
			}
			//�ڐG���Ă邩����
			if (this->Collision2D(pShield->GetCollision()))
			{
				//���������߂�
				fValue = (fabsf(ShotPos.x - pShield->GetShieldPos().x) / 2) - pShield->GetCollision()->GetSize().x * 0.4f;

				//���X�̒��������Z�������ꍇ
				if (fValue <= fLength)
				{
					//�Z������ݒ�
					fLength = fValue;

					//�|�C���^�ۑ�
					pMostNearObject = (CGameObject*)pShield;
				}
				bHitFlag = true;
			}
		}
	}


	//�I�u�W�F�N�g�̃��X�g�擾
	CScene::GetSceneList(CScene::OBJTYPE_OBSTACLE, pSceneList);

	//�����蔻�菈��
	//������̏ꍇ
	if (!pSceneList.empty())
	{
		for (size_t nCnt = 0; nCnt < pSceneList.size(); nCnt++)
		{
			//Obstacle�^�ɃL���X�g
			pObstacle = (CObstacle*)pSceneList[nCnt];

			//nullcheck
			if (!pObstacle)
			{
				continue;
			}
			//���肪���݂��鎞
			if (!pObstacle->GetCollision())
			{
				continue;
			}
			//���肪����Ƃ�
			if (!pObstacle->GetCollision()->GetCanCollison())
			{
				continue;
			}
			//�ڐG���Ă邩����
			if (this->Collision2D(pObstacle->GetCollision()))
			{
				//���������߂�
				fValue = (fabsf(ShotPos.x - pObstacle->GetCollision()->GetPos().x) / 2) - pObstacle->GetCollision()->GetSize().x * 0.4f;

				//���X�̒��������Z�������ꍇ
				if (fValue <= fLength)
				{
					//�Z������ݒ�
					fLength = fValue;

					//�|�C���^�ۑ�
					pMostNearObject = (CGameObject*)pObstacle;
				}
				bHitFlag = true;
			}
		}
	}


	//�I�u�W�F�N�g�̃��X�g�擾
	CScene::GetSceneList(CScene::OBJTYPE_ENEMY, pSceneList);

	//�����蔻�菈��
	//������̏ꍇ
	if (!pSceneList.empty())
	{
		for (size_t nCnt = 0; nCnt < pSceneList.size(); nCnt++)
		{
			//Obstacle�^�ɃL���X�g
			pEnemy = (CEnemy*)pSceneList[nCnt];
			bool bHit = false;

			//nullcheck
			if (!pEnemy)
			{
				continue;
			}
			//���肪���݂��鎞
			if (!pEnemy->GetCollision())
			{
				continue;
			}
			//���肪����Ƃ�
			if (!pEnemy->GetCollision()->GetCanCollison())
			{
				continue;
			}

			switch (pEnemy->GetEnemyType())
			{
			case::CEnemy::ENEMY_TYPE::ENEMY_HELICOPTER:
			case::CEnemy::ENEMY_TYPE::ENEMY_MELTYHONEY:
			case::CEnemy::ENEMY_TYPE::ENEMY_ZYCOCCA:
				bHit = this->OtherCollision2D(pEnemy->GetCollision());
				break;

			case::CEnemy::ENEMY_TYPE::ENEMY_BOSS_DRAGON_NOSUKE:
			case::CEnemy::ENEMY_TYPE::ENEMY_BOSS_SOL_DE_ROCA:
				bHit = this->CharCollision2D(pEnemy->GetCollision());
				break;
			}

			//�ڐG���Ă邩����
			if (bHit)
			{
				//���������߂�
				fValue = (fabsf(ShotPos.x - pEnemy->GetCollision()->GetPos().x) / 2) - pEnemy->GetCollision()->GetSize().x * 0.4f;

				//���X�̒��������Z�������ꍇ
				if (fValue <= fLength)
				{
					//�Z������ݒ�
					fLength = fValue;

					//�|�C���^�ۑ�
					pMostNearObject = (CGameObject*)pEnemy;
				}
				bHitFlag = true;
			}
		}
	}
	//�������Ă��ꍇ
	if (bHitFlag)
	{
		//nullcheck
		if (pMostNearObject)
		{
			switch (pMostNearObject->GetTag())
			{
			case TAG::SHIELD:
				pShield = (CShield*)pMostNearObject;
				pShield->AddDamage(1);

				break;
			case TAG::OBSTACLE:
				pObstacle = (CObstacle*)pMostNearObject;
				pObstacle->Hit(CObstacle::TYPE_BOX, 1);

				break;
			case TAG::ENEMY:
				pEnemy = (CEnemy*)pMostNearObject;
				pEnemy->AddDamage(1);

				break;
			default:
				break;
			}

		}
	}
	return bHitFlag;
}

//======================================================================================================================
// �v���C���[����蕨�ɏ�鎞�̔���
//======================================================================================================================
bool CCollision::VehicleCollision(CCollision * pCollision)
{
	// �ϐ��錾
	bool bHitFlag = false;

	// �f�ނ�X�͈�
	if (this->m_ppos->x + this->m_size.x * 0.5f > pCollision->m_ppos->x - pCollision->m_size.x * 0.5f &&
		this->m_ppos->x - this->m_size.x * 0.5f < pCollision->m_ppos->x + pCollision->m_size.x * 0.5f)
	{
		// �����蔻��(��)
		if (this->m_ppos->y < pCollision->m_ppos->y + pCollision->m_size.y * 0.5f &&
			this->m_posOld->y >= pCollision->m_ppos->y + pCollision->m_size.y * 0.5f)
		{
			// �f�ޏ�̏��
			//this->m_ppos->y = this->m_posOld->y;
			// �ړ��ʂ̏�����
			//this->m_pmove->y = 0.0f;
			// �I�u�W�F�N�g�ɓ��������t���O
			bHitFlag = true;
		}
	}

	// �������Ă��邩���Ȃ�����Ԃ�
	return bHitFlag;
}

//======================================================================================================================
// �v���C���[�ƃA�C�e���ōs������ �v���C���[�̐ڐG����
//======================================================================================================================
bool CCollision::ForPlayer_ItemCollision(TAG Tag)
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
			if (pItem->GetCollision()->OtherCollision2D(this))
			{
				bHitFlag = true;
				// �A�C�e�����Ƃ̏�����ʂ�
				pItem->HitItem(pItem->GetItemType(), Tag);
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
#ifdef _DEBUG
	if (m_Debugcollision != nullptr)
	{
		m_Debugcollision->SetSize(&m_size);
	}
#endif // _DEBUG

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
			this->m_ppos->y						<= pCollision->m_ppos->y + pCollision->m_size.y&&
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
// �^�̃u���b�N�̓����蔻�菈��(��̔���Ȃ�)
//======================================================================================================================
bool CCollision::BlockNotUpsideCollision2D(CCollision * pCollision)
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
	}

	// �������Ă��邩���Ȃ�����Ԃ�
	return bHitFlag;
}

//======================================================================================================================
// �u���b�N�̉��̔����Ԃ� �{�X�p
//======================================================================================================================
bool CCollision::BlockCollision2D_Bottom(CCollision * pCollision)
{
	// �e�������Ƃ��Ɏg���t���O
	bool bHitFlag = false;

	//// �f�ނ�Y�͈�
	//if (this->m_ppos->y + this->m_size.y * 0.5f > pCollision->m_ppos->y &&
	//	this->m_ppos->y < pCollision->m_ppos->y + pCollision->m_size.y)
	//{
	//	// �����蔻��(��)
	//	if (this->m_ppos->x + this->m_size.x * 0.5f > pCollision->m_ppos->x - pCollision->m_size.x * 0.5f &&
	//		this->m_posOld->x + this->m_size.x * 0.5f <= pCollision->m_ppos->x - pCollision->m_size.x * 0.5f)
	//	{
	//		// �f�ޏ�̍���
	//		//this->m_ppos->x = pCollision->m_ppos->x - pCollision->m_size.x * 0.5f - this->m_size.x * 0.5f;
	//		// �ړ��ʂ̏�����
	//		//this->m_pmove->x = 0.0f;
	//		// �I�u�W�F�N�g�ɓ��������t���O
	//		//bHitFlag = true;
	//	}

	//	// �����蔻��(�E)
	//	else if (this->m_ppos->x - this->m_size.x * 0.5f < pCollision->m_ppos->x + pCollision->m_size.x * 0.5f &&
	//		this->m_posOld->x - this->m_size.x * 0.5f >= pCollision->m_ppos->x + pCollision->m_size.x * 0.5f)
	//	{
	//		// �f�ޏ�̉E��
	//		//this->m_ppos->x = pCollision->m_ppos->x + pCollision->m_size.x * 0.5f + this->m_size.x * 0.5f;
	//		// �ړ��ʂ̏�����
	//		//this->m_pmove->x = 0.0f;
	//		// �I�u�W�F�N�g�ɓ��������t���O
	//		//bHitFlag = true;
	//	}
	//}

	// �f�ނ�X�͈�
	if (this->m_ppos->x + this->m_size.x * 0.5f > pCollision->m_ppos->x - pCollision->m_size.x * 0.5f &&
		this->m_ppos->x - this->m_size.x * 0.5f < pCollision->m_ppos->x + pCollision->m_size.x * 0.5f)
	{
		// �����蔻��(��)
		if (this->m_posOld->y + 50.0f > pCollision->m_ppos->y + pCollision->m_size.y &&
			this->m_ppos->y + 50.0f <= pCollision->m_ppos->y + pCollision->m_size.y)
		{
			// �f�ޏ�̉���
			//this->m_ppos->y = this->m_posOld->y;
			pCollision->m_ppos->x = pCollision->m_ppos->x - pCollision->m_size.x * 0.5f - this->m_size.x * 0.5f;
			// �ړ��ʂ̏�����
			//this->m_pmove->y = 0.0f;
			// �I�u�W�F�N�g�ɓ��������t���O
			bHitFlag = true;
		}

		//// �����蔻��(��)
		//else if (this->m_ppos->y < pCollision->m_ppos->y + pCollision->m_size.y * 0.5f &&
		//	this->m_posOld->y >= pCollision->m_ppos->y + pCollision->m_size.y * 0.5f)
		//{
		//	// �f�ޏ�̏��
		//	this->m_ppos->y = this->m_posOld->y;
		//	// �ړ��ʂ̏�����
		//	this->m_pmove->y = 0.0f;
		//	// �I�u�W�F�N�g�ɓ��������t���O
		//	bHitFlag = true;
		//}
	}

	// �������Ă��邩���Ȃ�����Ԃ�
	return bHitFlag;
}

//======================================================================================================================
// �L�����N�^�[���m�̃{�b�N�X���� �{�X�p
//======================================================================================================================
bool CCollision::BoxCollision2D_Character(CCollision * pCollision)
{
	// �e�������Ƃ��Ɏg���t���O
	bool bHitFlag = false;

	// �f�ނ�Y�͈�
	if (this->m_ppos->y + this->m_size.y > pCollision->m_ppos->y - pCollision->m_size.y * 2.0f &&
		this->m_ppos->y < pCollision->m_ppos->y + pCollision->m_size.y * 2.0f)
	{
		// �����蔻��(��)
		if (this->m_ppos->x + this->m_size.x > pCollision->m_ppos->x - pCollision->m_size.x &&
			this->m_posOld->x + this->m_size.x  <= pCollision->m_ppos->x - pCollision->m_size.x)
		{
			// �f�ޏ�̍���
			this->m_ppos->x = pCollision->m_ppos->x - pCollision->m_size.x - this->m_size.x;
			// �I�u�W�F�N�g�ɓ��������t���O
			bHitFlag = true;
		}

		// �����蔻��(�E)
		else if (this->m_ppos->x - this->m_size.x < pCollision->m_ppos->x + pCollision->m_size.x &&
			this->m_posOld->x - this->m_size.x >= pCollision->m_ppos->x + pCollision->m_size.x)
		{
			// �f�ޏ�̉E��
			this->m_ppos->x = pCollision->m_ppos->x + pCollision->m_size.x + this->m_size.x;
			// �I�u�W�F�N�g�ɓ��������t���O
			bHitFlag = true;
		}
	}

	// �������Ă��邩���Ȃ�����Ԃ�
	return bHitFlag;
}

//======================================================================================================================
// �G��蕨�ƃv���C���[�̔���
// �����瓖����ƃv���C���[�_���[�W
// ��͒e�����
//======================================================================================================================
bool CCollision::BoxCollision2D_Vehicle(CCollision * pCollision)
{
	// ������Փ˂����Ƃ��̃t���O
	bool bHitFlag = false;

	// �f�ނ�Y�͈�
	if (this->m_ppos->y + this->m_size.y	> pCollision->m_ppos->y&&
		this->m_ppos->y						< pCollision->m_ppos->y + pCollision->m_size.y)
	{
		// �����蔻��(��)
		if ((this->m_ppos->x + this->m_size.x * 0.5f > pCollision->m_ppos->x - pCollision->m_size.x * 0.5f &&
				this->m_posOld->x + this->m_size.x * 0.5f <= pCollision->m_posOld->x - pCollision->m_size.x * 0.5f))

		{
			// �f�ޏ�̍���
			this->m_ppos->x = pCollision->m_ppos->x - pCollision->m_size.x * 0.5f - this->m_size.x * 0.5f;

			// �I�u�W�F�N�g�ɓ��������t���O
			bHitFlag = true;
		}

		// �����蔻��(�E)
		else if ((this->m_ppos->x - this->m_size.x * 0.5f < pCollision->m_ppos->x + pCollision->m_size.x * 0.5f &&
				this->m_posOld->x - this->m_size.x * 0.5f >= pCollision->m_posOld->x + pCollision->m_size.x * 0.5f))
		{
			// �f�ޏ�̍���
			this->m_ppos->x = pCollision->m_ppos->x + pCollision->m_size.x * 0.5f + this->m_size.x * 0.5f;

			// �I�u�W�F�N�g�ɓ��������t���O
			bHitFlag = true;
		}
	}

	// �f�ނ�X�͈�
	if (this->m_ppos->x + this->m_size.x * 0.5f > pCollision->m_ppos->x - pCollision->m_size.x * 0.5f &&
		this->m_ppos->x - this->m_size.x * 0.5f < pCollision->m_ppos->x + pCollision->m_size.x * 0.5f)
	{
		// �����蔻��(��)
		if (this->m_ppos->y < pCollision->m_ppos->y + pCollision->m_size.y * 0.8f &&
			this->m_posOld->y >= pCollision->m_ppos->y + pCollision->m_size.y * 0.8f)
		{
			// �f�ޏ�̏��
			// �ړ��ʂ̏�����
			this->m_pmove->y = 10.0f;
			this->m_pmove->x *= -1.0f;
		}
	}

	// �������Ă��邩���Ȃ�����Ԃ�
	return bHitFlag;
}

//======================================================================================================================
// ���C�̔���
//======================================================================================================================
bool CCollision::RayBlockCollision(CMap *pMap, D3DXMATRIX *pMat)
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
		D3DXVec3TransformCoord(&m_posBefore, &D3DXVECTOR3(this->m_ppos->x, pMat->_42, this->m_ppos->z), &invmat);
		//	���C�I�_����ϊ�
		D3DXVec3TransformCoord(&m_posAfter, &D3DXVECTOR3(this->m_ppos->x , this->m_ppos->y - 1, this->m_ppos->z), &invmat);
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
	// �I�u�W�F�N�g�̍ő吔���J��Ԃ�
	for (int nCnt = 0; nCnt < CManager::GetGame()->GetMap()->GetMaxObstacle(); nCnt++)
	{
		//	�t�s��̎擾
		D3DXMatrixInverse(&invmat, NULL, CManager::GetGame()->GetMap()->GetObstacle(nCnt)->GetMatrix());
		//	�t�s����g�p���A���C�n�_����ϊ��@�ʒu�ƌ����ŕϊ�����֐����قȂ�̂ŗv����
		D3DXVec3TransformCoord(&m_posBefore, &D3DXVECTOR3(this->m_ppos->x, pMat->_42, this->m_ppos->z), &invmat);
		//	���C�I�_����ϊ�
		D3DXVec3TransformCoord(&m_posAfter, &D3DXVECTOR3(this->m_ppos->x, this->m_ppos->y - 1, this->m_ppos->z), &invmat);
		//	���C��������ϊ�
		D3DXVec3Normalize(&direction, &(m_posAfter - m_posBefore));
		//Ray���΂�
		D3DXIntersect(CManager::GetGame()->GetMap()->GetObstacle(nCnt)->GetMesh(), &m_posBefore, &direction, &bHitFlag, &dwHitIndex, &fHitU, &fHitV, &fLandDistance, NULL, NULL);
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
		if (fData < m_fHeight)//Ray�̒����̎w�����
		{
			this->m_ppos->y = this->m_ppos->y - fData + m_fHeight;
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

	//�z�����ɂ��Ă���
	vDistance.clear();

	// ����t���O��Ԃ�
	return bLand;
}

//======================================================================================================================
// ���C�̔���
//======================================================================================================================
bool CCollision::RayCollision(CMap *pMap)
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

	//�z�����ɂ��Ă���
	vDistance.clear();

	// ����t���O��Ԃ�
	return bJudg;
}
//======================================================================================================================
// ���C�̔��� �n�_�ƏI�_��ݒ肵�ċ�����Ԃ�
//======================================================================================================================
bool CCollision::RayCollisionGetLength(D3DXVECTOR3 posOrigin,D3DXVECTOR3 posEndPoint, float &fLength)
{
	// �n�`���� �ϐ��錾
	BOOL				bHitFlag = false;			// ���肪�o�����̃t���O
	bool				bJudg = false;				// ���肪�o�����̃t���O
	float				fLandDistance = 0;			// ����
	DWORD				dwHitIndex = -1;			// �C���f�b�N�X
	float				fHitU = 0;					// U
	float				fHitV = 0;					// V
	D3DXMATRIX			invmat;						// �t�s����i�[����ϐ�
	D3DXVECTOR3			direction;					// �ϊ���̈ʒu�A�������i�[����ϐ��F
	std::vector<float>	vDistance;					// �����̔z��ۑ�

	//�}�b�v���擾
	CMap *pMap = CManager::GetBaseMode()->GetMap();

	//nullcheck
	if (!pMap)
	{
		//null�������烊�^�[��
		return false;
	}

	// �}�b�v���f���̍ő吔���J��Ԃ�
	for (int nCnt = 0; nCnt < pMap->GetMaxModel(); nCnt++)
	{
		//������
		bHitFlag = false;

		//	�t�s��̎擾
		D3DXMatrixInverse(&invmat, NULL, pMap->GetModel(nCnt)->GetMatrix());
		//	�t�s����g�p���A���C�n�_����ϊ��@�ʒu�ƌ����ŕϊ�����֐����قȂ�̂ŗv����
		D3DXVec3TransformCoord(&posOrigin, &posOrigin, &invmat);
		//	���C�I�_����ϊ�
		D3DXVec3TransformCoord(&posEndPoint, &posEndPoint, &invmat);
		//	���C��������ϊ�
		D3DXVec3Normalize(&direction, &(posEndPoint - posOrigin));
		//Ray���΂�
		D3DXIntersect(pMap->GetMesh(nCnt), &posOrigin, &direction, &bHitFlag, &dwHitIndex, &fHitU, &fHitV, &fLandDistance, NULL, NULL);

		//�Ȃ񂩂���ɓ������Ă�����
		if (bHitFlag)
		{
			//�����̕ۑ��ǉ�
			vDistance.emplace_back(fLandDistance * 0.5f);
		}

	}
	//Ray�̃q�b�g���������������Ƃ�
	if (!vDistance.empty())
	{
		for (unsigned int nCnt = 0; vDistance.size() > nCnt; nCnt++)
		{
			if (vDistance[nCnt] < fLength)
			{
				//��r�Ώۂ���������������
				fLength = vDistance[nCnt];
				bJudg = true;
			}
		}
	}

	//�z�����ɂ��Ă���
	vDistance.clear();

	// ����t���O��Ԃ�
	return bJudg;
}


bool CCollision::RayFloorCollision(CMap * pMap, D3DXMATRIX * pMat, D3DXVECTOR3 pdirection,D3DXVECTOR3 ppos)
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
		D3DXVec3TransformCoord(&m_posBefore, &D3DXVECTOR3(ppos.x, pMat->_42, ppos.z), &invmat);
		//	���C�I�_����ϊ�
		D3DXVec3TransformCoord(&m_posAfter, &D3DXVECTOR3(ppos.x ,ppos.y+ pdirection.y, ppos.z), &invmat);
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
		if (fData < RAY_FIRST_POINT+30)//Ray�̒����̎w�����
		{
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
	//�z�����ɂ��Ă���
	vDistance.clear();

	// ����t���O��Ԃ�
	return bJudg;
}
