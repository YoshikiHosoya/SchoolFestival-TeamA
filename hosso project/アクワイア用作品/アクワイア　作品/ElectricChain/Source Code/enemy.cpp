//------------------------------------------------------------------------------
//
//�G�l�~�[����  [enemy.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "enemy.h"
#include "manager.h"
#include "renderer.h"
#include "collision.h"
#include "gauge_3D.h"
#include "sphere_explosion.h"
#include "game.h"
#include "particle.h"
#include "player.h"
#include "sound.h"
#include "score.h"
#include "effectanimation3D.h"
#include "frontUI.h"
#include "chainelectric.h"
//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------
int CEnemy::m_nNumEnemy = 0;
int CEnemy::m_nNumStanEnemy = 0;
bool CEnemy::m_bChain = false;

//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------
#define KNOCK_BACK_SPEED (25.0f)			//�m�b�N�o�b�N�̗�
#define MAX_ONE_CHAIN (3)					//�PF������̘A���łȂ���ő吔
#define ENEMY_PLAYER_FOUND_RANGE (800.0f)	//�v���C���[�������鋗��
#define ENEMY_ATTACK_RANGE (250.0f)			//�v���C���[�ɍU�����鋗��

//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CEnemy::CEnemy()
{
	m_bStan = false;
	m_bContact = false;
	m_bChain = false;
	m_AIMove = AI_NEUTRAL;
	m_enemytype = CEnemy::TYPE_NORMAL;
	m_nNumEnemy++;
	m_fMoveAngle = 0.0f;
	m_nCntAIMove = rand() % 1000;
}

//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CEnemy::~CEnemy()
{
	m_pGauge = nullptr;
	m_nNumEnemy--;
	m_nNumStanEnemy--;
}
//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CEnemy::Init()
{
	CCharacter::Init();

	//����
	return S_OK;
}
//------------------------------------------------------------------------------
//�I������
//------------------------------------------------------------------------------
void CEnemy::Uninit()
{
	CCharacter::Uninit();
}
//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CEnemy::Update()
{
	//�A�����false
	m_bChain = false;

	//�����Ă���Ƃ�
	if (GetAlive())
	{
		//���݂̃��[�V����
		switch (GetNowMotion())
		{
			//�j���[�g�����������Ă���Ƃ�
		case CMotion::ENEMY_ARMOR_NEUTRAL:
		case CMotion::ENEMY_ARMOR_WALK:

			//�U����ԉ���
			SetAttack(false);
			break;
		}

		//��e��
		if (GetState() == CCharacter::STATE_DAMAGE)
		{

		}
		//�X�^����Ԃł���Ȃ�
		else if (m_bStan)
		{
			//�X�^�����[�V����
			ChangeMotion(CMotion::ENEMY_ARMOR_STAN);
			SetState(CCharacter::STATE_STAN);
		}
		else
		{
			//�Q�[����
			if (CManager::GetMode() == CManager::MODE_GAME)
			{
				//�Q�[���N���A��
				if (CManager::GetGame()->GetGamestate() == CGame::STATE_GAMECLEAR)
				{
					//�j���[�g�����ɂ��Ƃ�
					ChangeMotion(CMotion::ENEMY_ARMOR_NEUTRAL);
				}
				else
				{
					//AI�ňړ�
					AIMove();
				}
			}
			//�f���v���C��
			if (CManager::GetMode() == CManager::MODE_DEMOPLAY)
			{
				//AI�ňړ�
				AIMove();
			}
		}
	}
	//�X�V
	CCharacter::Update();

	//�Q�[�W�p�̃}�g���b�N�X�ݒ�
	m_pGauge->SetMtx(*GetMtx());
}
//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void CEnemy::Draw()
{
	CCharacter::Draw();
}

//------------------------------------------------------------------------------
//�f�o�b�O���\�L
//------------------------------------------------------------------------------
void CEnemy::ShowDebugInfo()
{
#ifdef _DEBUG
	//�v���C���[�����
	if (ImGui::TreeNode("EnemyInfo"))
	{
		//�L�����N�^�[���\��
		ShowCharacterInfo();

		ImGui::TreePop();
	}
#endif //DEBUG
}
//------------------------------------------------------------------------------
//�_���[�W�󂯂����̏���
//------------------------------------------------------------------------------
void CEnemy::DamageAction()
{
	//�Q�[�W�X�V
	m_pGauge->SetLife(GetLife(), GetBlueLife());

	//���Đ�
	CManager::GetSound()->Play(CSound::LABEL_SE_SLASH);

	//��HP��0�ȉ��ɂȂ�����
	if (GetBlueLife() <= 0)
	{
		//�܂��X�^�����ĂȂ�������
		if (!m_bStan)
		{
			//�X�^���J�n
			StartStan();

			//�q�b�g�G�t�F�N�g�@�X�^�����킩��₷���悤��
			CEffectAnimation3D::Create(GetCenterPos(), D3DXVECTOR3(350.0f, 350.0f, 0.0f), CTexture::SEPARATE_TEX_EFFECT_HIT_STAN, D3DXCOLOR(0.2f, 0.4f, 1.0f, 0.8f), 0.0f, 2);
			CEffectAnimation3D::Create(GetCenterPos(), D3DXVECTOR3(350.0f, 350.0f, 0.0f), CTexture::SEPARATE_TEX_EFFECT_STANING, D3DXCOLOR(0.1f, 0.3f, 1.0f, 1.0f), 0.0f, 3);

			//���������
			HyperKnockBack();

			//�X�^�����
			SetState(CCharacter::STATE_STAN);

			//���Đ�
			CManager::GetSound()->Play(CSound::LABEL_SE_SLASH_STAN);
		}
	}

	//�e�N�X�`���A�j���[�V�����̐���
	CEffectAnimation3D::Create(GetCenterPos(), D3DXVECTOR3(300.0f, 300.0f, 0.0f), CTexture::SEPARATE_TEX_EFFECT_HIT_SLASH, WhiteColor, CHossoLibrary::Random_PI(), 5);
	CEffectAnimation3D::Create(GetCenterPos(), D3DXVECTOR3(150.0f, 150.0f, 0.0f), CTexture::SEPARATE_TEX_EFFECT_HIT_SPARK, WhiteColor, CHossoLibrary::Random_PI(), 1);

	//��e���[�V����
	ChangeMotion(CMotion::ENEMY_ARMOR_HIT);

	//�Q�[����
	if (CManager::GetMode() == CManager::MODE_GAME)
	{
		//�R���{���Z
		CManager::GetGame()->GetScore()->AddCombo(1);
	}
}
//------------------------------------------------------------------------------
//���S���̃��A�N�V����
//------------------------------------------------------------------------------
void CEnemy::DeathAction()
{
	//�����G�t�F�N�g
	CSphere_Explosion::Create(GetCenterPos(), 120.0f, 150);
	CParticle::Create(GetCenterPos(), 60, 450.0f, OrangeColor, 2,1.0f);

	//�L�������Z
	if (CManager::GetMode() == CManager::MODE_GAME)
	{
		CManager::GetGame()->GetScore()->AddKill(1);
	}

	//�A����������
	ChainExplosion(GetPos());

	//�J��
	Release();
}
//------------------------------------------------------------------------------
//�U�����ɐ���
//------------------------------------------------------------------------------
void CEnemy::AttackTurning()
{
}
//------------------------------------------------------------------------------
//�����蔻��n
//------------------------------------------------------------------------------
void CEnemy::Collision()
{
	CCharacter::Collision();
}

//------------------------------------------------------------------------------
//��������
//------------------------------------------------------------------------------
std::shared_ptr<CEnemy> CEnemy::Create(D3DXVECTOR3 pos, ENEMY_TYPE enemytype)
{
	//�ϐ��錾
	std::shared_ptr<CEnemy> pEnemy = std::make_shared<CEnemy>();

	//nullcheck
	if (pEnemy)
	{
		//������7
		pEnemy->Init();

		//���W�ݒ�
		pEnemy->SetPos(pos);

		//�G�̎�ސݒ�
		pEnemy->m_enemytype = enemytype;

		switch (enemytype)
		{
		case CEnemy::TYPE_NORMAL:
			//�p�����[�^�ݒ�
			pEnemy->SetParameter(MODEL_TYPE::MODEL_ENEMY, CCharacter::PARAM_ENEMY, pEnemy);
			break;

		case CEnemy::TYPE_TUTORIAL_STANING:
			//�p�����[�^�ݒ�
			pEnemy->SetParameter(MODEL_TYPE::MODEL_ENEMY, CCharacter::PARAM_ENEMY, pEnemy);
			break;

		case CEnemy::TYPE_SPEEDY:
			//�p�����[�^�ݒ�
			pEnemy->SetParameter(MODEL_TYPE::MODEL_ENEMY, CCharacter::PARAM_ENEMY, pEnemy);

			break;
		case CEnemy::TYPE_STRONG:
			//�p�����[�^�ݒ�
			pEnemy->SetParameter(MODEL_TYPE::MODEL_ENEMY, CCharacter::PARAM_ENEMY, pEnemy);

			break;
		}

		//���[���h�}�g���b�N�X�̌v�Z
		CHossoLibrary::CalcMatrix(pEnemy->GetMtx(), pEnemy->GetPos(), pEnemy->GetRot());

		//�Q�[�W����
		pEnemy->m_pGauge = CGauge_3D::Create(pEnemy->GetPos(), D3DXVECTOR3(50.0f, 4.0f, 0.0f), D3DXVECTOR3(0.0f, 110.0f, 0.0f), pEnemy->GetDefaultParam(PARAM_ENEMY)->GetMaxLife(), *pEnemy->GetMtx());

		if (enemytype == CEnemy::TYPE_TUTORIAL_STANING)
		{
			//�̃��C�t��0�ɂ��ăX�^����Ԃɂ��Ă���
			pEnemy->SetBlueLife(0);
			pEnemy->m_pGauge->SetLife(pEnemy->GetLife(), pEnemy->GetBlueLife());
			pEnemy->StartStan();
		}

		//�G�t�F�N�g����
		CEffectAnimation3D::Create(pEnemy->GetCenterPos(), D3DXVECTOR3(350.0f, 350.0f, 0.0f), CTexture::SEPARATE_TEX_EFFECT_ENEMY_RESPAWN, WhiteColor, 0.0f, 2);

		//�I�u�W�F�N�g�^�C�v�ݒ�
		pEnemy->SetObjType(OBJTYPE_ENEMY);

		//���X�g�ɒǉ�
		pEnemy->AddSharedList(pEnemy);

		//�����������
		return pEnemy;
	}

	//���s
	return nullptr;
}
//------------------------------------------------------------------------------
//�A������
//------------------------------------------------------------------------------
void CEnemy::ChainExplosion(D3DXVECTOR3 pos)
{
	//�܂��`�F�C�����ĂȂ���
	if (!m_bChain)
	{
		//�J�E���g
		int nCnt = 0;

		//Scene�̃��X�g
		std::vector<std::shared_ptr<CScene>> pSceneList;

		//�G�̃��X�g�擾
		CScene::GetSceneList(CScene::OBJTYPE_ENEMY, pSceneList);

		//nullcheck
		if (!pSceneList.empty())
		{
			//�v�f��
			for (size_t nCnt = 0; nCnt < pSceneList.size(); nCnt++)
			{
				//�|�C���^�擾 CEnemy�^�ɃL���X�g
				CEnemy *pEnemy = ((CEnemy*)pSceneList[nCnt].get());

				//nullcheck
				if (pEnemy)
				{
					//�X�^����ԂŐ����Ă��鎞
					if (pEnemy->GetStan() && pEnemy->GetAlive())
					{
						//�A������
						m_bChain = true;

						//�_���[�W���� �X�^����Ԃ����炱�ꂾ���Ŕ�������
						pEnemy->ApplyDamage(1, 0);

						////�d������
						CChainElectric::Create(pos, pEnemy->GetPos(), D3DXVECTOR3(200.0f, 50.0f, 0.0f), WhiteColor, pEnemy->GetCntState());

						//�J�E���^++
						nCnt++;

						//1F�ɔ����ł���ʒ�������return
						if (nCnt > MAX_ONE_CHAIN)
						{
							return;
						}
					}
				}
			}
		}
	}
}
//------------------------------------------------------------------------------
//�X�e�[�g�ύX����
//------------------------------------------------------------------------------
void CEnemy::SetState(STATE nextstate)
{
	CCharacter::SetState(nextstate);
	switch (nextstate)
	{
	case CCharacter::STATE_NORMAL:
		break;
	case CCharacter::STATE_DAMAGE:
		break;
	case CCharacter::STATE_STAN:
		break;
	case CCharacter::STATE_DEATH:

		//�q�b�g�G�t�F�N�g
		CEffectAnimation3D::Create(GetCenterPos(), D3DXVECTOR3(400.0f, 400.0f, 0.0f), CTexture::SEPARATE_TEX_EFFECT_HIT_STAN, D3DXCOLOR(0.8f,0.8f,0.3f,0.8f), 0.0f,3);

		//�����܂ł̃J�E���g
		SetCntState(rand() % 15 + 7);
		break;
	}
}
//------------------------------------------------------------------------------
//static�n�̏�񏉊���
//------------------------------------------------------------------------------
void CEnemy::ResetEnemyStaticInfo()
{
	m_nNumEnemy = 0;
	m_nNumStanEnemy = 0;
	m_bChain = false;
}

//------------------------------------------------------------------------------
//���������
//------------------------------------------------------------------------------
void CEnemy::HyperKnockBack()
{
	//�v���C���[�̃|�C���^�擾
	CPlayer *pPlayer = CManager::GetBaseMode()->GetPlayer();

	//�ړ���
	D3DXVECTOR3 &rMove = GetMove();

	//nullcheck
	if (!pPlayer)
	{
		//null�������珈�����Ȃ�
		return;
	}

	//���܂ɐ�����΂Ȃ������
	if (rand() % 15 == 0)
	{
		return;
	}

	//�ϐ��錾
	D3DXVECTOR3 Distance = GetPos() - pPlayer->GetPos();				//�v���C���[�Ǝ����̍���
	float fLength = fabsf(D3DXVec3Length(&Distance));					//�v���C���[�Ƃ̋���
	float fAngle = atan2f(Distance.x, Distance.z);

	float fKnockBackSpeed = KNOCK_BACK_SPEED + rand() % 80;

	//�ړ�����
	rMove.x = sinf(fAngle) * fKnockBackSpeed;
	rMove.y = float(rand() % 15 + 2.0f);
	rMove.z = cosf(fAngle) * fKnockBackSpeed;
}
//------------------------------------------------------------------------------
//AI�ňړ�
//------------------------------------------------------------------------------
void CEnemy::AIMove()
{
	//�v���C���[�̃|�C���^�擾
	CPlayer *pPlayer = CManager::GetBaseMode()->GetPlayer();

	//nullcheck
	if (!pPlayer)
	{
		//null�������珈�����Ȃ�
		m_AIMove = CEnemy::AI_NEUTRAL;
		return;
	}

	//�v���C���[�����S���Ă�����
	if (!pPlayer->GetAlive())
	{
		//���̏�Ƀj���[�g����
		m_AIMove = CEnemy::AI_NEUTRAL;
		return;
	}

	//�ϐ��錾
	D3DXVECTOR3 Distance = GetPos() - pPlayer->GetPos();				//�v���C���[�Ǝ����̍���
	float fLength = fabsf(D3DXVec3Length(&Distance));					//�v���C���[�Ƃ̋���
	float fAngle = atan2f(Distance.x, Distance.z);

	//AI�̃J�E���g
	m_nCntAIMove++;

	//�����̎�
	if (fLength <= ENEMY_PLAYER_FOUND_RANGE)
	{
		//�j���[�g�������ړ����Ă鎞
		if (m_AIMove == AI_NEUTRAL || m_AIMove == AI_PLAYER_FOLLOWING)
		{
			//�v���C���[�̕�������
			SetRotDest(D3DXVECTOR3(0.0f, fAngle, 0.0f));
		}

		//������x���������čU�����Ă��Ȃ���
		if (fLength <= ENEMY_PLAYER_FOUND_RANGE && fLength > ENEMY_ATTACK_RANGE && !GetAttack())
		{
			//�v���C���[�̕��ɗ���
			m_AIMove = CEnemy::AI_PLAYER_FOLLOWING;
		}
		//�U���\����
		else if (fLength <= ENEMY_ATTACK_RANGE)
		{
			//�U�����ĂȂ���
			if (!GetAttack())
			{
				//�j���[�g����
				m_AIMove = CEnemy::AI_NEUTRAL;
				ChangeMotion(CMotion::ENEMY_ARMOR_NEUTRAL);
			}

			//50F�Ɉ��
			if (m_nCntAIMove % 50 == 0)
			{
				//�m����
				if (rand() % 5 == 0)
				{
					//�U��
					m_AIMove = CEnemy::AI_ATTACK;
					ChangeMotion(CMotion::ENEMY_ARMOR_ATTACK01);
					SetAttack(true);
				}
			}
		}
	}
	//������
	else
	{
		//�ړ����ĂȂ���
		if (m_AIMove != CEnemy::AI_RANDOM_MOVE)
		{
			//�j���[�g����
			m_AIMove = CEnemy::AI_NEUTRAL;
		}
	}

	//�ړ���
	D3DXVECTOR3 &rMove = GetMove();

	//�ړ����x
	float fMoveSpeed = 0.0f;

	//AI�̈ړ���Ԃŏ�����ς���
	switch (m_AIMove)
	{
	case CEnemy::AI_NEUTRAL:
		ChangeMotion(CMotion::ENEMY_ARMOR_NEUTRAL);

		//������
		if (m_nCntAIMove % 150 == 0)
		{
			//�m���ŕ����o��
			if (rand() % 2 == 0)
			{
				//�j���[�g����
				m_AIMove = CEnemy::AI_RANDOM_MOVE;
				break;
			}
		}
		break;

	case CEnemy::AI_RANDOM_MOVE:
		//�������[�V����
		ChangeMotion(CMotion::ENEMY_ARMOR_WALK);

		//�ړ����x�ݒ�
		fMoveSpeed = CCharacter::GetDefaultParam(CCharacter::GetParamType())->GetMoveSpeed();

		//������x���Ԃ��������ɕ����]��
		if (m_nCntAIMove % 120 == 0)
		{
			//���܂Ƀj���[�g�����ɂȂ�
			if (rand() % 3 == 0)
			{
				//�j���[�g����
				m_AIMove = CEnemy::AI_NEUTRAL;
				break;
			}
			//�ړ���̊p�x�ݒ�
			m_fMoveAngle = CHossoLibrary::Random_PI();
		}
		//�ړ�����������
		SetRotDest(D3DXVECTOR3(0.0f, m_fMoveAngle, 0.0f));
		break;

		//�ړ�
	case CEnemy::AI_PLAYER_FOLLOWING:

		//�X�s�[�h�̓p�����[�^������������Ă���
		fMoveSpeed = CCharacter::GetDefaultParam(CCharacter::GetParamType())->GetDashSpeed();

		//�������[�V����
		ChangeMotion(CMotion::ENEMY_ARMOR_WALK);

		//�����ݒ�
		m_fMoveAngle = fAngle;

		break;
	case CEnemy::AI_ATTACK:
		break;
	}

	//�ړ�����
	rMove.x -= sinf(m_fMoveAngle) * fMoveSpeed;
	rMove.z -= cosf(m_fMoveAngle) * fMoveSpeed;
}

//------------------------------------------------------------------------------
//�X�^���J�n
//------------------------------------------------------------------------------
void CEnemy::StartStan()
{
	//�X�^���G�������Z
	m_nNumStanEnemy++;

	//�X�^�����true
	m_bStan = true;

	//HP�Q�[�W�_��
	m_pGauge->SetFlash(true);

	//�X�^�����[�V����
	ChangeMotion(CMotion::ENEMY_ARMOR_STAN);

	//�S���X�^�������Ƃ�
	if (GetEnemyNum() == GetStanEnemyNum())
	{
		CFrontUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 550.0f, 0.0f), D3DXVECTOR3(550.0f, 150.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CFrontUI::PUSH_B);
	}
}
