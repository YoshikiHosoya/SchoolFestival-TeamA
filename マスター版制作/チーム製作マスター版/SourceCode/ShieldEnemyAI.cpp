//=============================================================================
// AI���� [ShieldEnemyAI.cpp] Hanzawa
//=============================================================================
#include "ShieldEnemyAI.h"
#include "renderer.h"
#include "inputKeyboard.h"
#include "WeakEnemy.h"
#include "Player.h"
#include "manager.h"
#include "BaseMode.h"
#include "map.h"
#include "collision.h"
#include "gun.h"
#include "Knife.h"
#define MAX_RECASTTIME (120)
#define MAX_DISTANCE (180)
#define MAX_ATTACKDISTANCE (70)
CShieldEnemyAI::CShieldEnemyAI()
{
}

CShieldEnemyAI::~CShieldEnemyAI()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CShieldEnemyAI::Init(void)
{
	m_recast = 60;
	m_castcount = 0;
	m_bAttack = false;
	m_bKnifeAttack = false;
	m_random = 0;
	m_AItype = AI_NONE;
	m_Distance = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fDistance = 0.0f;
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CShieldEnemyAI::Uninit(void)
{
}

//=============================================================================
// �X�V����
//=============================================================================
void CShieldEnemyAI::Update(void)
{
	CPlayer *pPlayer = CManager::GetBaseMode()->GetPlayer(TAG::PLAYER_1);
	// �}�b�v�̃|�C���^�擾
	CMap *pMap;
	pMap = CManager::GetBaseMode()->GetMap();
	CKeyboard *key;
	key = CManager::GetInputKeyboard();

	if (pEnemyPass != nullptr)
	{
		// �}�b�v���f�������݂�����
		if (pMap != nullptr)
		{
			if (pPlayer != nullptr)
			{
				m_Distance = pEnemyPass->GetPosition() - pPlayer->GetPosition();
				m_fDistance = D3DXVec2Length(&D3DXVECTOR2(m_Distance.x, m_Distance.y));
				if (m_fDistance < MAX_ATTACKDISTANCE)
				{
					m_bAttack = true;
					m_castcount++;
				}
				else
				{
					m_bAttack = false;
					m_castcount = 0;
				}
				if (m_bKnifeAttack == false)
				{
					//�v���C���[�����ɂ���Ƃ�
					if (pEnemyPass->GetPosition().x > pPlayer->GetPosition().x)
					{
						pEnemyPass->GetRotDest().y = D3DX_PI * 0.5f;
						pEnemyPass->SetCharacterDirection(DIRECTION::LEFT);
						//Ray�̔��肪����Ƃ�
						if (GetCollision()->RayFloorCollision(pMap, pEnemyPass->GetCharacterModelPartsList(0)->GetMatrix(),
							D3DXVECTOR3(0.0f, -1.0f, 0.0f),
							D3DXVECTOR3(pEnemyPass->GetPosition().x - 30, pEnemyPass->GetPosition().y, pEnemyPass->GetPosition().z)))
						{
							if (pEnemyPass->GetPosition().x - pPlayer->GetPosition().x > MAX_DISTANCE)
							{
								m_AItype = AI_WALK_LEFT;
							}
							else
							{
								m_AItype = AI_STOP;
							}

						}
						//Ray�̔��肪�Ȃ��Ƃ�
						else
						{
							m_AItype = AI_STOP;
						}
					}
					//�v���C���[���E�ɂ���Ƃ�
					else if (pEnemyPass->GetPosition().x < pPlayer->GetPosition().x)
					{
						pEnemyPass->GetRotDest().y = D3DX_PI * -0.5f;
						pEnemyPass->SetCharacterDirection(DIRECTION::RIGHT);
						//Ray�̔��肪����Ƃ�
						if (GetCollision()->RayFloorCollision(pMap, pEnemyPass->GetCharacterModelPartsList(0)->GetMatrix(),
							D3DXVECTOR3(0.0f, -1.0f, 0.0f),
							D3DXVECTOR3(pEnemyPass->GetPosition().x + 30, pEnemyPass->GetPosition().y, pEnemyPass->GetPosition().z)))
						{
							if (pEnemyPass->GetPosition().x - pPlayer->GetPosition().x < -MAX_DISTANCE)
							{
								m_AItype = AI_WALK_RIGHT;
							}
							else
							{
								m_AItype = AI_STOP;
							}

						}
						//Ray�̔��肪�Ȃ��Ƃ�
						else
						{
							m_AItype = AI_STOP;
						}
					}
				}
			}
		}
		if (pPlayer != nullptr)
		{
			switch (m_AItype)
			{
			case AI_NONE://�s���Ȃ�
				pEnemyPass->SetMotion(CCharacter::ENEMY_MOTION_NORMAL);
				break;
			case AI_ATTACK://�ߐڍU��
				pEnemyPass->SetMotion(CCharacter::ENEMY_MOTION_KNIFEATTACK);
				break;
			case AI_STOP://�ړ����Ȃ�
				pEnemyPass->SetMotion(CCharacter::ENEMY_MOTION_NORMAL);
				break;
			case AI_WALK_LEFT://���ړ�
				pEnemyPass->GetMove().x -= 1.0f;
				pEnemyPass->GetRotDest().y = D3DX_PI * 0.5f;
				pEnemyPass->SetCharacterDirection(DIRECTION::LEFT);
				pEnemyPass->SetMotion(CCharacter::ENEMY_MOTION_WALK);
				break;
			case AI_WALK_RIGHT://�E�ړ�
				pEnemyPass->GetMove().x += 1.0f;
				pEnemyPass->GetRotDest().y = D3DX_PI * -0.5f;
				pEnemyPass->SetCharacterDirection(DIRECTION::RIGHT);
				pEnemyPass->SetMotion(CCharacter::ENEMY_MOTION_WALK);

				break;
			}
		}
		AttackUpdate();
	}
}
//=============================================================================
// �U���X�V
//=============================================================================
void CShieldEnemyAI::AttackUpdate(void)
{
	if (m_bAttack == true&& m_bKnifeAttack == false && m_castcount == 30)
	{
		m_bKnifeAttack = true;
	}
	if(m_bKnifeAttack == true)
	{
		m_AItype = AI_ATTACK;
		if (pEnemyPass->GetMotionType() == CCharacter::ENEMY_MOTION_KNIFEATTACK &&pEnemyPass->GetKeySet() == 4 && pEnemyPass->GetFram() == 0)
		{
			pEnemyPass->GetKnifePtr()->StartMeleeAttack();
		}
	}
	if(pEnemyPass->GetMotionType() == CCharacter::ENEMY_MOTION_KNIFEATTACK &&pEnemyPass->GetKeySet() == 7 && m_bKnifeAttack == true&& pEnemyPass->GetFram() == 0)
	{
		m_bKnifeAttack = false;
		m_AItype = AI_STOP;
		pEnemyPass->GetKnifePtr()->EndMeleeAttack();
		m_castcount = 0;
	}
}
//=============================================================================
// �`��
//=============================================================================
void CShieldEnemyAI::Draw(void)
{
}
//=============================================================================
// �f�o�b�O
//=============================================================================
void CShieldEnemyAI::DebugInfo(void)
{
}
//=============================================================================
// AI�̃N���G�C�g
//=============================================================================
CShieldEnemyAI * CShieldEnemyAI::CreateAI(CWeakEnemy *pEnemy)
{
	CShieldEnemyAI*pEnemyAI;
	pEnemyAI = new CShieldEnemyAI();
	pEnemyAI->Init();
	pEnemyAI->pEnemyPass = pEnemy;
	return pEnemyAI;
}
//=============================================================================
// AI�̃^�C�v�擾
//=============================================================================
CShieldEnemyAI::AI_STATE CShieldEnemyAI::GetAIType(void)
{
	return m_AItype;
}