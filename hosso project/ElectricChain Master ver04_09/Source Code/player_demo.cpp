//------------------------------------------------------------------------------
//
//�f���p�̃v���C���[����  [player_demo.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "player_demo.h"
#include "keyboard.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "sound.h"
#include "gauge_2D.h"
#include "effectanimation3D.h"
#include "game.h"
#include "sphere_explosion.h"
#include "enemy.h"
//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CPlayer_Demo::CPlayer_Demo()
{
	m_AttackInput = CPlayer_Demo::ATTACK_NONE;
}

//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CPlayer_Demo::~CPlayer_Demo()
{
	m_pTargetEnemy.reset();
}
//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CPlayer_Demo::Init()
{
	CCharacter::Init();

	//����
	return S_OK;
}
//------------------------------------------------------------------------------
//�I������
//------------------------------------------------------------------------------
void CPlayer_Demo::Uninit()
{
	CCharacter::Uninit();
}
//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CPlayer_Demo::Update()
{
	//�����Ă鎞
	if (GetAlive())
	{
		switch (GetNowMotion())
		{
		case CMotion::PLAYER_NEUTRAL:
		case CMotion::PLAYER_WALK:
		case CMotion::PLAYER_DASH:
			if (GetJump())
			{
				ChangeMotion(CMotion::PLAYER_AIR_NEUTRAL);
			}
			SetChainThunder(false);
			SetAttack(false);
			break;
		}

		//�_���[�W�󂯂ĂȂ���
		if (CCharacter::GetNowMotion() != CMotion::PLAYER_HIT)
		{
			//�ړ��̓��͏���
			MoveAI();

			//���[�V�����؂�ւ�
			MoveMotionCheck();
		}

		//���������
		if (GetChainThunder())
		{
			//���̃G�t�F�N�g
			ChainThunder();
		}
	}

	//�X�V
	CCharacter::Update();
}
//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void CPlayer_Demo::Draw()
{
	CCharacter::Draw();
}

//------------------------------------------------------------------------------
//�f�o�b�O���\�L
//------------------------------------------------------------------------------
void CPlayer_Demo::ShowDebugInfo()
{
#ifdef _DEBUG


#endif //DEBUG
}

//------------------------------------------------------------------------------
//��������
//------------------------------------------------------------------------------
std::shared_ptr<CPlayer_Demo> CPlayer_Demo::Create(D3DXVECTOR3 pos)
{
	//�ϐ��錾
	std::shared_ptr<CPlayer_Demo> pPlayer_Demo = std::make_shared<CPlayer_Demo>();

	if (pPlayer_Demo)
	{
		//������7
		pPlayer_Demo->Init();

		//���W�ݒ�
		pPlayer_Demo->SetPos(pos);

		//�p�����[�^�ݒ�
		pPlayer_Demo->SetParameter(CHARACTER_PLAYER,CCharacter::PARAM_PLAYER, pPlayer_Demo);

		//�I�u�W�F�N�g�^�C�v�ݒ�
		pPlayer_Demo->SetObjType(OBJTYPE_PLAYER);

		//���X�g�ɒǉ�
		pPlayer_Demo->AddSharedList(pPlayer_Demo);

		return pPlayer_Demo;
	}

	//�����������
	return nullptr;
}

//------------------------------------------------------------------------------
//�ړ��̓���
//------------------------------------------------------------------------------
void CPlayer_Demo::MoveAI()
{
	D3DXVECTOR3 &rMove = GetMove();		//�ړ����擾
	D3DXVECTOR3 &rRotdest = GetRotDest();	//��]���擾
	D3DXVECTOR3 posDif = ZeroVector3;
	float fAngle = 0.0f;
	float fLength = 0.0f;

	//�Ƃ肠�����G�̏��擾
	if (m_pTargetEnemy._Get())
	{
		if (m_pTargetEnemy._Get()->GetStan())
		{
			SetTargetEnemy();
		}
	}
	else
	{
		SetTargetEnemy();
	}

	//�G�^�[�Q�b�g�̓G������Ƃ�
	if (m_pTargetEnemy._Get())
	{
		//�G�Ƃ̋����v��
		posDif = m_pTargetEnemy._Get()->GetPos() - GetPos();
		fAngle = atan2f(posDif.x, posDif.z);
		fLength = D3DXVec3Length(&posDif);
	}
	else
	{
		return;
	}

	if (CEnemy::GetEnemyNum() == CEnemy::GetStanEnemyNum() && !GetChainThunder())
	{
		ChangeMotion(CMotion::PLAYER_ATTACK_THUNDER);
		StartChainThunder();
		SetAirAttack(true);
		m_pTargetEnemy.reset();
	}

	if (!GetAttack())
	{
		//�ړ����x
		float fMoveSpeed;

		//�_�b�V�����Ă��邩�m�F
		fMoveSpeed = GetDefaultParam(CCharacter::GetParamType())->GetDashSpeed();		//��{�_�b�V����

		//�W�����v��Ԃ̏ꍇ
		if (GetJump())
		{
			fMoveSpeed = GetDefaultParam(CCharacter::GetParamType())->GetAirSpeeed();			//�󒆂̈ړ����x
		}

		//�J������]���擾
		float fCameraRot = CManager::GetRenderer()->GetCamera()->GetCameraRot().y;

		//�ړ�
		rMove.x += sinf(fAngle) * fMoveSpeed;
		rMove.z += cosf(fAngle) * fMoveSpeed;

		rRotdest.y = D3DX_PI + fAngle;

		CHossoLibrary::CalcRotation(rRotdest.y);

		//��]����
		CCharacter::SetRotDest(rRotdest);
	}

	//�W�����v�L�[
	if (CHossoLibrary::CheckJump(CHossoLibrary::TRIGGER))
	{
		if (!GetJump())
		{
			//�ړ����擾
			D3DXVECTOR3 &rMove = GetMove();

			//������ɐi��
			rMove.y = GetDefaultParam(CCharacter::GetParamType())->GetJumpSpeed();

			//�W�����v�ɐ؂�ւ�
			SetJump(true);
			ChangeMotion(CMotion::PLAYER_JUMP);
		}
	}

	//�^�[�Q�b�g�̓G�Ƃ̋��������ȉ��ɂȂ�����
	if (fLength < 200.0f)
	{
		//����
		int nAttackRand = rand() % 5;

		if (nAttackRand <= 3)
		{
			//X�̓���
			m_AttackInput = CPlayer_Demo::ATTACK_X;
		}
		else
		{
			//Y�̓���
			m_AttackInput = CPlayer_Demo::ATTACK_Y;
		}

		//�U���̓���
		if (AttackInput())
		{
			//��]
			rRotdest.y = fAngle + D3DX_PI;
			SetAttack(true);
		}
	}
}
//------------------------------------------------------------------------------
//�A���U���̎��̃��[�V�����ǂꂾ
//------------------------------------------------------------------------------
bool CPlayer_Demo::AttackInput()
{
	bool bAttack = false;	//return�p
	CMotion::MOTION_TYPE NowMotion = GetNowMotion();		//���݂̃��[�V�����擾

	//���݂̃��[�V�����ɉ����Ď��̃��[�V���������߂�
	switch (NowMotion)
	{
	case CMotion::PLAYER_NEUTRAL:
	case CMotion::PLAYER_WALK:
	case CMotion::PLAYER_DASH:
		if (m_AttackInput == CPlayer_Demo::ATTACK_X)
		{
			ChangeMotion(CMotion::PLAYER_LAND_ATTACK_X_01);
			return true;
		}
		if (m_AttackInput == CPlayer_Demo::ATTACK_Y)
		{
			ChangeMotion(CMotion::PLAYER_LAND_ATTACK_Y_01);
			return true;
		}
		if (m_AttackInput == CPlayer_Demo::ATTACK_B)
		{
			ChangeMotion(CMotion::PLAYER_ATTACK_THUNDER);
			StartChainThunder();
			return true;
		}
		break;
	case CMotion::PLAYER_AIR_NEUTRAL:
	case CMotion::PLAYER_JUMP:
		if (m_AttackInput == CPlayer_Demo::ATTACK_X)
		{
			if (!GetAirAttack())
			{
				ChangeMotion(CMotion::PLAYER_AIR_ATTACK_X_01);
				SetAirAttack(true);
				SetGravity(false, 17);

				return true;
			}
		}
		if (m_AttackInput == CPlayer_Demo::ATTACK_Y)
		{
			ChangeMotion(CMotion::PLAYER_ATTACK_SLAMS);
			GetMove().y = 0.0f;
			SetGravity(false, 5);
			return true;
		}
		if (m_AttackInput == CPlayer_Demo::ATTACK_B)
		{
			if (!GetAirAttack())
			{
				ChangeMotion(CMotion::PLAYER_ATTACK_THUNDER);
				StartChainThunder();
				SetAirAttack(true);
				return true;
			}
		}
		break;
	}

	//�����čU���ł����Ԃ��m�F
	if (!ContinueAttack())
	{
		return false;
	}


	if (m_AttackInput == CPlayer_Demo::ATTACK_X)
	{
		switch (NowMotion)
		{

		case CMotion::PLAYER_LAND_ATTACK_X_01:
			ChangeMotion(CMotion::PLAYER_LAND_ATTACK_X_02);
			bAttack = true;
			break;

		case CMotion::PLAYER_LAND_ATTACK_X_02:
			ChangeMotion(CMotion::PLAYER_LAND_ATTACK_X_03);
			bAttack = true;
			break;

		case CMotion::PLAYER_LAND_ATTACK_X_03:
			ChangeMotion(CMotion::PLAYER_LAND_ATTACK_X_04);
			bAttack = true;
			break;

		case CMotion::PLAYER_LAND_ATTACK_X_04:
			ChangeMotion(CMotion::PLAYER_LAND_ATTACK_X_05);
			bAttack = true;
			break;

			//��
		case CMotion::PLAYER_AIR_ATTACK_X_01:
			ChangeMotion(CMotion::PLAYER_AIR_ATTACK_X_02);
			SetGravity(false, 17);
			bAttack = true;
			break;

		case CMotion::PLAYER_AIR_ATTACK_X_02:
			ChangeMotion(CMotion::PLAYER_AIR_ATTACK_X_03);
			SetGravity(false, 17);
			bAttack = true;
			break;

		case CMotion::PLAYER_AIR_ATTACK_X_03:
			ChangeMotion(CMotion::PLAYER_AIR_ATTACK_X_04);
			SetGravity(false, 30);
			bAttack = true;
			break;

		}
	}

	if (m_AttackInput == CPlayer_Demo::ATTACK_Y)
	{

		switch (NowMotion)
		{
		case CMotion::PLAYER_LAND_ATTACK_X_03:
		case CMotion::PLAYER_LAND_ATTACK_X_04:
			ChangeMotion(CMotion::PLAYER_LAND_ATTACK_Y_02);
			bAttack = true;
			break;

		case CMotion::PLAYER_LAND_ATTACK_Y_01:
			ChangeMotion(CMotion::PLAYER_LAND_ATTACK_Y_SPEAR);
			bAttack = true;
			break;

		case CMotion::PLAYER_LAND_ATTACK_Y_02:
			ChangeMotion(CMotion::PLAYER_LAND_ATTACK_Y_03);
			bAttack = true;
			break;

		case CMotion::PLAYER_LAND_ATTACK_Y_03:
			ChangeMotion(CMotion::PLAYER_LAND_ATTACK_Y_04);
			bAttack = true;
			break;

		case CMotion::PLAYER_LAND_ATTACK_Y_04:
			ChangeMotion(CMotion::PLAYER_LAND_ATTACK_Y_05);
			bAttack = true;
			break;

		case CMotion::PLAYER_LAND_ATTACK_X_01:
		case CMotion::PLAYER_LAND_ATTACK_X_02:
			ChangeMotion(CMotion::PLAYER_ATTACK_UPPER);
			SetAirAttack(true);
			break;
		}
	}


	if (m_AttackInput == CPlayer_Demo::ATTACK_Y)
	{
		switch (NowMotion)
		{
		case CMotion::PLAYER_AIR_ATTACK_X_01:
		case CMotion::PLAYER_AIR_ATTACK_X_02:
		case CMotion::PLAYER_AIR_ATTACK_X_03:
		case CMotion::PLAYER_AIR_ATTACK_X_04:
			ChangeMotion(CMotion::PLAYER_ATTACK_SLAMS);
			bAttack = true;
			break;
		}
	}
	if (m_AttackInput == CPlayer_Demo::ATTACK_B)
	{
		switch (NowMotion)
		{
		case CMotion::MOTION_NONE:
			break;
		case CMotion::PLAYER_LAND_ATTACK_X_01:
		case CMotion::PLAYER_LAND_ATTACK_X_02:
		case CMotion::PLAYER_LAND_ATTACK_X_03:
		case CMotion::PLAYER_LAND_ATTACK_X_04:
		case CMotion::PLAYER_LAND_ATTACK_X_05:
		case CMotion::PLAYER_LAND_ATTACK_Y_01:
		case CMotion::PLAYER_LAND_ATTACK_Y_02:
		case CMotion::PLAYER_LAND_ATTACK_Y_03:
		case CMotion::PLAYER_LAND_ATTACK_Y_04:
		case CMotion::PLAYER_LAND_ATTACK_Y_05:
		case CMotion::PLAYER_LAND_ATTACK_Y_SPEAR:
		case CMotion::PLAYER_JUMP:
		case CMotion::PLAYER_ATTACK_UPPER:
		case CMotion::PLAYER_ATTACK_SLAMS:
		case CMotion::PLAYER_AIR_ATTACK_X_01:
		case CMotion::PLAYER_AIR_ATTACK_X_02:
		case CMotion::PLAYER_AIR_ATTACK_X_03:
		case CMotion::PLAYER_AIR_ATTACK_X_04:
			ChangeMotion(CMotion::PLAYER_ATTACK_THUNDER);
			StartChainThunder();
			SetAirAttack(true);
			bAttack = true;
			break;

		}
	}
	return bAttack;
}

//------------------------------------------------------------------------------
//�G�̃^�[�Q�b�g�ݒ�
//------------------------------------------------------------------------------
void CPlayer_Demo::SetTargetEnemy()
{
	//�V�[���̃��X�g
	std::vector<std::shared_ptr<CScene>> pSceneList;

	//�V�[�����擾
	CScene::GetSceneList(CScene::OBJTYPE_ENEMY, pSceneList);

	//�z��ɓ����Ă邩
	if (!pSceneList.empty())
	{
		//�v�f��
		for (size_t nCnt = 0; nCnt < pSceneList.size(); nCnt++)
		{
			//�|�C���^�擾 CEnemy�^�Ƀ_�E���L���X�g
			std::shared_ptr<CEnemy> pEnemy = std::static_pointer_cast<CEnemy>(pSceneList[nCnt]);
			//nullcheck
			if (pEnemy)
			{
				//�X�^����Ԃ���Ȃ����
				if (!pEnemy->GetStan())
				{
					//�^�[�Q�b�g�ݒ�
					m_pTargetEnemy = pEnemy;
					return;
				}
			}
		}
	}
}


