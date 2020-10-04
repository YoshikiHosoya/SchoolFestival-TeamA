// =====================================================================================================================================================================
//
// skydrone��AI�̏��� [skydroneAI.cpp]
// Author : FujiwaraMasato
//
// =====================================================================================================================================================================
#include "skydroneAI.h"		// �C���N���[�h�t�@�C��
#include "renderer.h"
#include "WeakEnemy.h"
#include "Player.h"
#include "manager.h"
#include "BaseMode.h"
#include "map.h"
#include "gun.h"
#include "ModelSet.h"
#include "texture.h"
#include "particle.h"
#include "enemy.h"
#include "boss_one.h"

// =====================================================================================================================================================================
// �ÓI�����o�ϐ��̏�����
// =====================================================================================================================================================================

// =====================================================================================================================================================================
// �}�N����`
// =====================================================================================================================================================================
#define SHOT_COOLTIME				(230)					// ���܂ł̎���
#define MOVE_STOP_TIME				(120)					// �~�܂�܂ł̎���
#define MOVE_SPEED					(3.0f)					// �ړ��X�s�[�h

// =====================================================================================================================================================================
//
// �R���X�g���N�^
//
// =====================================================================================================================================================================
CSkyDroneAI::CSkyDroneAI()
{
	m_pEnemyPass = nullptr;
	m_nRotCnt = 0;
	m_nWorkTime = 0;
}

// =====================================================================================================================================================================
//
// �f�X�g���N�^
//
// =====================================================================================================================================================================
CSkyDroneAI::~CSkyDroneAI()
{
}

// =====================================================================================================================================================================
//
// ����������
//
// =====================================================================================================================================================================
HRESULT CSkyDroneAI::Init(void)
{
	m_nCntShotFrame = 0;						// ���܂ł̃J�E���g
	m_nCntMoveStopFrame = 0;					// �~�܂�܂ł̃J�E���g
	m_StateAI = DRONEAI_STATE::APPEARANCE;		// AI�̏��
	m_LeaveState = DRONEAI_LEAVESTATE::FIRST;
	return S_OK;
}

// =====================================================================================================================================================================
//
// �I������
//
// =====================================================================================================================================================================
void CSkyDroneAI::Uninit(void)
{
}

// =====================================================================================================================================================================
//
// �X�V����
//
// =====================================================================================================================================================================
void CSkyDroneAI::Update(void)
{
	// �h���[����AI�̏��
	SkyDroneAIState();

	for (int nCnt = 0; nCnt < CManager::GetBaseMode()->GetMap()->GetMaxEnemy(); nCnt++)
	{
		// �G�l�~�[�̃|�C���^�擾
		CEnemy *pEnemy = CManager::GetBaseMode()->GetMap()->GetEnemy(nCnt);

		if (pEnemy != nullptr)
		{
			if (pEnemy->GetModelSet()->GetCharacterType() == CModelSet::CHARACTER_TYPE_BOSS_ONE)
			{
				CBoss_One *pBoss_One = (CBoss_One*)pEnemy;

				if (pBoss_One->GetCharacterState() == CBoss_One::CHARACTER_STATE_DEATH)
				{
					m_pEnemyPass->SetDieFlag(true);
				}
			}
		}
	}
}

// =====================================================================================================================================================================
//
// �`�揈��
//
// =====================================================================================================================================================================
void CSkyDroneAI::Draw(void)
{
}

// =====================================================================================================================================================================
//
// �f�o�b�O���\�L
//
// =====================================================================================================================================================================
void CSkyDroneAI::DebugInfo(void)
{
}

// =====================================================================================================================================================================
//
// AI�̐���
//
// =====================================================================================================================================================================
CSkyDroneAI * CSkyDroneAI::CreateAI(CWeakEnemy *pEnemy)
{
	// �ϐ�
	CSkyDroneAI	*pSkyDroneAI;

	// �������̊m��
	pSkyDroneAI = new CSkyDroneAI();

	// ������
	pSkyDroneAI->Init();

	// �G�l�~�[�̏��
	pSkyDroneAI->m_pEnemyPass = pEnemy;

	return pSkyDroneAI;
}

// =====================================================================================================================================================================
//
// AI�̏�Ԏ擾
//
// =====================================================================================================================================================================
CSkyDroneAI::DRONEAI_STATE CSkyDroneAI::GetAIType(void)
{
	return m_StateAI;
}

// =====================================================================================================================================================================
//
// �h���[����AI�̏��
//
// =====================================================================================================================================================================
void CSkyDroneAI::SkyDroneAIState()
{
	if (m_StateAI == DRONEAI_STATE::STOP ||
		m_StateAI == DRONEAI_STATE::MOVEROT)
	{
		// �����J�n������Z
		m_nWorkTime++;
	}

	// �v���C���[�̃|�C���^�擾
	CPlayer *pPlayer[MAX_CONTROLLER];

	for (int nCnt = 0; nCnt < MAX_CONTROLLER; nCnt++)
	{
		pPlayer[nCnt] = CManager::GetBaseMode()->GetPlayer((TAG)nCnt);
	}

	switch (m_StateAI)
	{
	case CSkyDroneAI::DRONEAI_STATE::APPEARANCE:

		if (m_pEnemyPass->GetPosition().y >= 400.0f)
		{
			m_pEnemyPass->GetPosition().y -= 1.5f;
 			if (m_pEnemyPass->GetPosition().y <= 400.0f)
			{
				m_pEnemyPass->GetPosition().y = 400.0f;
				m_StateAI = DRONEAI_STATE::STOP;
			}

			m_pEnemyPass->SetPosition(m_pEnemyPass->GetPosition());
		}

		break;
	case CSkyDroneAI::DRONEAI_STATE::STOP:

		if (m_nWorkTime >= 30)
		{
			m_StateAI = DRONEAI_STATE::MOVEROT;
		}

		break;
	case CSkyDroneAI::DRONEAI_STATE::MOVEROT:
		// ���E�ړ�
		float temp;
		m_nAngle += 2;

		temp = cosf(m_nAngle*D3DX_PI / 200);
		m_pEnemyPass->GetPosition().x += temp *3.0f;

		if (m_nWorkTime >= (180 + 300))
		{
			m_nAngle = 0;
			m_StateAI = DRONEAI_STATE::LEAVE;
		}
		break;

	case CSkyDroneAI::DRONEAI_STATE::LEAVE:

		// ���E�ړ�
		float Temp;
		m_nAngle += 2;
		Temp = sinf(m_nAngle*D3DX_PI / 200);
		m_pEnemyPass->GetPosition().y += Temp *5.0f;

		if (m_nAngle >= 240)
		{
			m_pEnemyPass->SetDieFlag(true);
		}

		break;
	default:
		break;
	}

	// �ʏ�s�����ɂ̂ݍU��
	if (m_StateAI != DRONEAI_STATE::APPEARANCE &&
		m_StateAI != DRONEAI_STATE::STOP &&
		m_StateAI != DRONEAI_STATE::LEAVE)
	{
		// �J�E���g�A�b�v
		m_nCntShotFrame++;

		// 2�l�v���C�̎�
		if (CPlayer::GetTwoPPlayFlag())
		{
			// ��b���Ƃɒe������
			if (m_nCntShotFrame >= 100)
			{
				if (m_nCntShotFrame > 100)
				{
					if (CHossoLibrary::Random(10) >= 0)
					{
						if (pPlayer[0])
						{
							D3DXVECTOR3 RandPos = pPlayer[0]->GetPosition();

							RandPos.x += CHossoLibrary::Random(150.0f);

							//�ˌ������̌v�Z
							D3DXVECTOR3 ShotVec = RandPos - m_pEnemyPass->GetPosition();
							//�l�̐��K��
							D3DXVec3Normalize(&ShotVec, &ShotVec);
							//�������̐ݒ�
							m_pEnemyPass->GetGunPtr()->SetShotRot(D3DXVECTOR3(0.0f, 0.0f, atan2f(-ShotVec.x, ShotVec.y)));
						}
					}
					else
					{
						if (pPlayer[1])
						{
							D3DXVECTOR3 RandPos = pPlayer[1]->GetPosition();

							RandPos.x += CHossoLibrary::Random(150.0f);

							//�ˌ������̌v�Z
							D3DXVECTOR3 ShotVec = RandPos - m_pEnemyPass->GetPosition();
							//�l�̐��K��
							D3DXVec3Normalize(&ShotVec, &ShotVec);
							//�������̐ݒ�
							m_pEnemyPass->GetGunPtr()->SetShotRot(D3DXVECTOR3(0.0f, 0.0f, atan2f(-ShotVec.x, ShotVec.y)));
						}
					}

					// ����
					m_pEnemyPass->GetGunPtr()->Shot();
					m_nCntShotFrame = 0;
				}
				else
				{
					//�p�[�e�B�N������ �O�Ղ݂�����
					CParticle::CreateFromText(m_pEnemyPass->GetPosition(), m_pEnemyPass->GetRot(), CParticleParam::EFFECT_CHARGE);
				}
			}
		}
		// 1�l�v���C�̎�
		else
		{
			// ��b���Ƃɒe������
			if (m_nCntShotFrame >= 120)
			{
				if (m_nCntShotFrame > 120)
				{
					if (pPlayer[0])
					{
						D3DXVECTOR3 RandPos = pPlayer[0]->GetPosition();

						RandPos.x += CHossoLibrary::Random(150.0f);

						//�ˌ������̌v�Z
						D3DXVECTOR3 ShotVec = RandPos - m_pEnemyPass->GetPosition();
						//�l�̐��K��
						D3DXVec3Normalize(&ShotVec, &ShotVec);
						//�������̐ݒ�
						m_pEnemyPass->GetGunPtr()->SetShotRot(D3DXVECTOR3(0.0f, 0.0f, atan2f(-ShotVec.x, ShotVec.y)));
					}

					// ����
					m_pEnemyPass->GetGunPtr()->Shot();
					m_nCntShotFrame = 0;
				}
				else
				{
					//�p�[�e�B�N������ �O�Ղ݂�����
					CParticle::CreateFromText(m_pEnemyPass->GetPosition(), m_pEnemyPass->GetRot(), CParticleParam::EFFECT_CHARGE);
				}
			}
		}
	}
}