//=============================================================================
// AI���� [BossAI.cpp] Hanzawa
//=============================================================================
#include "BossAI.h"
#include "renderer.h"
#include "inputKeyboard.h"
#include "Boss.h"
#include "Player.h"
#include "manager.h"
#include "BaseMode.h"
#include "collision.h"
#include "gun.h"
#include "particle.h"

#define CENTER_POS		(D3DXVECTOR3(0.0f,450.0f,0.0f))
#define RIGHT_POS		(D3DXVECTOR3(400.0f,400.0f,0.0f))
#define LEFT_POS		(D3DXVECTOR3(-400.0f,400.0f,0.0f))
#define BOSS_UNDER_POS	(D3DXVECTOR3(0.0f,180.0f,0.0f))
#define MOVE_SPEED		(0.1f)
#define MAX_RECASTTIME (60)
#define LAZER_MOVE_SPEED (4.5f)
CBossAI::CBossAI()
{
}

CBossAI::~CBossAI()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CBossAI::Init(void)
{
	m_recast = 60;
	m_castcount = 0;
	m_LaserRandom = 0;
	m_bShot = false;
	m_random = 0;
	m_BossAItype = AI_NONE;
	m_ShotVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Attack = false;
	m_AttackCastCnt = 0;
	m_AttackCnt = 0;
	m_MoveCnt = 0;
	m_Attacks = 0;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CBossAI::Uninit(void)
{
}

//=============================================================================
// �X�V����
//=============================================================================
void CBossAI::Update(void)
{
	CPlayer *pPlayer = CManager::GetBaseMode()->GetPlayer();
	D3DXVECTOR3 Distance;

	if (pBossPass != nullptr || pPlayer != nullptr)
	{
		D3DXVECTOR3 MoveVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_BossAItypeOld = m_BossAItype;	//�O��̍U���̊i�[
		if (m_bShot == false)
		{
		m_castcount++;
		}
		else
		{
		m_castcount = 0;
		}
		if (m_castcount == m_recast && m_bReStartFlag == false)
		{
			m_recast = (rand() % MAX_RECASTTIME) + 30;	//30�t���[�����̃��L���X�g
			m_random = (rand() % AI_MAX);				//�s���̃����_��
			m_BossAItype = (AI_BOSS_STATE)m_random;		//�����_���̌`����AI_STATE�ɕϊ�
			m_castcount = 0;
			m_bShot = false;
		}
		else if (m_bReStartFlag == true)
		{
			m_random = (rand() % AI_MAX);				//�s���̃����_��
			m_BossAItype = (AI_BOSS_STATE)m_random;		//�����_���̌`����AI_STATE�ɕϊ�
			m_recast = (rand() % MAX_RECASTTIME) + 30;	//30�t���[�����̃��L���X�g
			if (m_BossAItype != m_BossAItypeOld)
			{
				m_bReStartFlag = false;
				m_castcount = 0;
				m_AttackCnt = 0;
				m_AttackCastCnt = 0;
				m_Attacks = 0;
				m_Attack = false;
				m_bShot = false;
			}
		}
	}
	CDebugProc::Print("�{�X�̃X�e�[�g�F%d\n", m_BossAItype);
	CDebugProc::Print("�{�X�̃L���X�g�^�C���F%d\n", m_castcount);
	CDebugProc::Print("�{�X�̃��L���X�g�^�C���F%d\n", m_recast);

	UpdateMoveAI();
	UpdateAttackAI();
}
//=============================================================================
// �ړ�AI�X�V����
//=============================================================================
void CBossAI::UpdateMoveAI(void)
{
	D3DXVECTOR3 MoveVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	CPlayer *pPlayer = CManager::GetBaseMode()->GetPlayer();
	if (pBossPass != nullptr || pPlayer != nullptr)
	{
		if (AI_CENTER == m_BossAItype) //����
		{
			MoveVec = CENTER_POS - pBossPass->GetPosition();
			//�����̐��K��
			if (m_bShot == false )
			{
				pBossPass->GetPosition() += MoveVec*MOVE_SPEED;
			}
		}
		else if (AI_LEFT == m_BossAItype)//��
		{
			MoveVec = LEFT_POS - pBossPass->GetPosition();
			//�����̐��K��
			if (m_bShot == false)
			{
				pBossPass->GetPosition() += MoveVec*MOVE_SPEED;
			}
		}
		else if (AI_RIGHT == m_BossAItype)//�E
		{
			MoveVec = RIGHT_POS - pBossPass->GetPosition();
			//�����̐��K��
			if (m_bShot == false)
			{
				pBossPass->GetPosition() += MoveVec*MOVE_SPEED;
			}
		}
		else if (AI_ONPLAYER == m_BossAItype)
		{
			m_MoveCnt++;
			MoveVec = pPlayer->GetPosition() - pBossPass->GetPosition();
			//�����̐��K��
			if (m_bShot == false && m_MoveCnt < 30)
			{
				pBossPass->GetPosition() += D3DXVECTOR3(MoveVec.x*MOVE_SPEED,0.0f,0.0f);
			}
			else if (m_bShot == false && m_MoveCnt == 35)
			{
				m_MoveCnt = 0;
				m_BossAItype = AI_NONE;
			}
		}
	}
}
//=============================================================================
// �U��AI�X�V����
//=============================================================================
void CBossAI::UpdateAttackAI(void)
{
	D3DXVECTOR3 MoveVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	CPlayer *pPlayer = CManager::GetBaseMode()->GetPlayer();
	float fAngle = 0.0f;
	if (pBossPass != nullptr && pPlayer != nullptr)
	{
		if (AI_TRACKING == m_BossAItype)//�v���C���[�Ǐ]�e
		{
			//�K���̃^�C�v�ύX
			pBossPass->GetGunPtr()->SetGunType(pBossPass->GetGunPtr()->GUNTYPE_TRACKINGGUN);

			m_ShotVec = pPlayer->GetPosition() - pBossPass->GetPosition();//�ˌ������̌v�Z
			D3DXVec3Normalize(&m_ShotVec, &m_ShotVec);//�l�̐��K��

			//�������̐ݒ�
			pBossPass->GetGunPtr()->SetShotRot(D3DXVECTOR3(0.0f, 0.0f, atan2f(-m_ShotVec.x, m_ShotVec.y)));

			//����
			CParticle::CreateFromText(pBossPass->GetPosition(), D3DXVECTOR3(0.0f, 0.0f, CHossoLibrary::Random_PI()), CParticleParam::EFFECT_FLASSHING, TAG::TAG_PLAYER, 0, D3DXCOLOR(0.7f,0.02f, 0.02f,1.0f));

			m_AttackCastCnt++;
			m_bShot = true;
			if (m_AttackCastCnt == 60)//�U���ɓ���܂ł̎���
			{
				m_Attack = true;//�U�����\�ɂ���
			}
			//�U�����\�ɂȂ�����
			if (m_Attack == true)
			{
				m_AttackCnt++;
				//120�t���[����菬�����Ƃ��ˌ�
				if (m_AttackCnt < 60 && m_Attacks < 3 && m_AttackCnt % 10 == 0)
				{
					pBossPass->GetGunPtr()->Shot();
				}
				else if (m_AttackCnt == 140)
				{
					m_AttackCnt = 0;
					m_Attacks++;
				}
				//120�t���[�����U���񐔂ɒB�����珉����
				if (m_AttackCnt > 120 && m_Attacks >= 3)
				{
					SetRestartFlag(true);
				}
			}
		}

		else if (AI_DIFFUSION == m_BossAItype)//�g�U�ˌ�
		{
			//����
			CParticle::CreateFromText(pBossPass->GetPosition(), D3DXVECTOR3(0.0f, 0.0f, CHossoLibrary::Random_PI()), CParticleParam::EFFECT_FLASSHING, TAG::TAG_PLAYER, 0, D3DXCOLOR(0.7f, 0.7f, 0.01f, 0.2f));

			//�K���̃^�C�v�ύX
			pBossPass->GetGunPtr()->SetGunType(pBossPass->GetGunPtr()->GUNTYPE_DIFFUSIONGUN);

			//-1.57����1.57�͈̔͂Ń����_���Ȓl��ݒ�
			fAngle = CHossoLibrary::Random(1.57f);

			//�������̐ݒ�
			pBossPass->GetGunPtr()->SetShotRot(D3DXVECTOR3(0.0f, 0.0f, D3DX_PI + fAngle));

			m_AttackCastCnt++;
			m_bShot = true;
			if (m_AttackCastCnt == 60)//�U���ɓ���܂ł̎���
			{
				m_Attack = true;//�U�����\�ɂ���
			}
			//�U�����\�ɂȂ�����
			if (m_Attack == true)
			{
				m_AttackCnt++;
				//120�t���[����菬�����Ƃ��ˌ�
				if (m_AttackCnt < 180 && m_AttackCnt % 5 == 0)
				{
					pBossPass->GetGunPtr()->Shot();
				}
				//120�t���[���ɂȂ����珉����
				else if (m_AttackCnt > 230)
				{
					SetRestartFlag(true);
				}
			}
		}
		else if (AI_LASER == m_BossAItype)//���[�U�[
		{
			//�K���̃^�C�v�ύX
			pBossPass->GetGunPtr()->SetGunType(pBossPass->GetGunPtr()->GUNTYPE_BOSSLASERGUN);

			//�������̐ݒ�
			pBossPass->GetGunPtr()->SetShotRot(D3DXVECTOR3(0.0f, 0.0f, D3DX_PI));

			m_AttackCastCnt++;
			m_bShot = true;
			if (m_AttackCastCnt == 60)//�U���ɓ���܂ł̎���
			{
				m_Attack = true;//�U�����\�ɂ���
				m_LaserRandom = (rand() % 2);
			}
			//�U�����\�ɂȂ�����
			if (m_Attack == true)
			{
				m_AttackCnt++;
				if (m_LaserRandom == 0)
				{
					if (m_AttackCnt > 30)
					{
						pBossPass->GetPosition().x += LAZER_MOVE_SPEED;
						pBossPass->GetGunPtr()->Shot();
					}
					else
					{
						MoveVec = LEFT_POS - pBossPass->GetPosition();
						pBossPass->GetPosition() += MoveVec*MOVE_SPEED;
					}
				}
				else
				{
					if (m_AttackCnt > 30)
					{
						pBossPass->GetPosition().x -= LAZER_MOVE_SPEED;
						pBossPass->GetGunPtr()->Shot();
					}
					else
					{
						MoveVec = RIGHT_POS - pBossPass->GetPosition();
						pBossPass->GetPosition() += MoveVec*MOVE_SPEED;
					}
				}
				//180�t���[���ɂȂ����珉����(3�b)
				if (m_AttackCnt > 180)
				{
					SetRestartFlag(true);
				}
			}
			else
			{
				if (m_AttackCastCnt % 5 == 0)
				{
					CParticle::CreateFromText(pBossPass->GetPosition() - BOSS_UNDER_POS, D3DXVECTOR3(0.0f, 0.0f, CHossoLibrary::Random_PI()), CParticleParam::EFFECT_CHARGE_PARTICLE);
					CParticle::CreateFromText(pBossPass->GetPosition() - BOSS_UNDER_POS, D3DXVECTOR3(0.0f, 0.0f, CHossoLibrary::Random_PI()), CParticleParam::EFFECT_CHARGE_CIRCLE);
				}
			}
		}
	}
	CDebugProc::Print("�{�X�̍U����   :%d\n", m_Attacks);
}
//=============================================================================
// �`��
//=============================================================================
void CBossAI::Draw(void)
{
}
//=============================================================================
// �f�o�b�O
//=============================================================================
void CBossAI::DebugInfo(void)
{
	CKeyboard *pkeyBoard = CManager::GetInputKeyboard();

	if (pkeyBoard->GetKeyboardTrigger(DIK_9))
	{
		m_BossAItype = AI_LASER;
	}

}
D3DXVECTOR3 CBossAI::GetTrackingShotRot(void)
{
	return m_ShotVec;
}
//=============================================================================
// AI�̃N���G�C�g
//=============================================================================
CBossAI * CBossAI::CreateAI(CBoss *pBoss)
{
	CBossAI*pBossAI;
	pBossAI = new CBossAI();
	pBossAI->Init();
	pBossAI->pBossPass = pBoss;
	return pBossAI;
}
//=============================================================================
// AI�̍U���^�C�v�擾
//=============================================================================
CBossAI::AI_BOSS_STATE CBossAI::GetBossAIType(void)
{
	return m_BossAItype;
}
//=============================================================================
//
//=============================================================================
bool CBossAI::GetShot(void)
{
	return m_bShot;
}
void CBossAI::SetShot(bool shot)
{
	m_bShot = shot;
}
void CBossAI::SetRestartFlag(bool flag)
{
	m_bReStartFlag = flag;
}
//=============================================================================
// AI�̍s���^�C�v�ݒ�
//=============================================================================
void CBossAI::SetBossAI(AI_BOSS_STATE attack)
{
	m_BossAItype = attack;
}
