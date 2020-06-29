//------------------------------------------------------------------------------
//
//�v���C���[����  [player.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "player.h"
#include "keyboard.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "sound.h"
#include "gauge_2D.h"
#include "effectanimation3D.h"
#include "game.h"
#include "sphere_explosion.h"
#include "effectanimation2D.h"
#include "modelcharacter.h"
#include "enemy.h"
#include "frontUI.h"
#include "circle_effect.h"
//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------
bool CPlayer::m_bClearedAlive = true;
//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CPlayer::CPlayer()
{
	m_nCntChainThunder = 0;
	m_bChainThunder = false;
}

//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CPlayer::~CPlayer()
{
}
//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CPlayer::Init()
{
	//������
	CCharacter::Init();

	switch (CManager::GetMode())
	{
		//�Q�[�����`���[�g���A���J�n���ɂ͐�����Ԃɂ��Ă���
	case CManager::MODE_GAME:
	case CManager::MODE_TUTORIAL:
		m_bClearedAlive = true;
	}

	//����
	return S_OK;
}
//------------------------------------------------------------------------------
//�I������
//------------------------------------------------------------------------------
void CPlayer::Uninit()
{
	CCharacter::Uninit();
}
//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CPlayer::Update()
{
	//���U���g�̂Ƃ��̓��[�V�����Œ�@�ړ����ł��Ȃ��悤��
	if (CManager::GetMode() == CManager::MODE_RESULT)
	{
		//�Q�[���N���A���ɐ����Ă�����
		if (m_bClearedAlive)
		{
			//�܂��������ĂȂ���
			if (!m_bChainThunder)
			{
				//��������
				StartChainThunder();
			}
			//�������Ă��Ԃ̂Ƃ�
			else if (m_bChainThunder)
			{
				//���̃G�t�F�N�g����
				ChainThunder();

				//���݃j���[�g�����̎�
				if (GetNowMotion() == CMotion::PLAYER_NEUTRAL)
				{
					//���U���g�p�̃��[�V�����Z�b�g
					ChangeMotion(CMotion::PLAYER_RESULT);
				}
			}
		}
		//�Q�[���N���A���Ɏ���ł�����
		else
		{
			//�|��Ă���
			ChangeMotion(CMotion::PLAYER_DEATH);
		}
	}

	//�����Ă鎞
	else if (GetAlive())
	{
		//���݂̃��[�V����
		switch (GetNowMotion())
		{
			//�j���[�g�������������_�b�V�����̎�
		case CMotion::PLAYER_NEUTRAL:
		case CMotion::PLAYER_WALK:
		case CMotion::PLAYER_DASH:

			//�W�����v��
			if (GetJump())
			{
				//�󒆂̃j���[�g�������
				ChangeMotion(CMotion::PLAYER_AIR_NEUTRAL);
			}
			//�A��������ԉ���
			m_bChainThunder = false;
			SetAttack(false);
			break;
		}

		//�_���[�W�󂯂ĂȂ���
		if (CCharacter::GetNowMotion() != CMotion::PLAYER_HIT)
		{
			//game�̂Ƃ�
			if (CManager::GetMode() == CManager::MODE_GAME)
			{
				//�Q�[���N���A���͓��͂ł��Ȃ��悤�ɂ���
				if (CManager::GetGame()->GetGamestate() == CGame::STATE_GAMECLEAR)
				{
					//�j���[�g�������[�V����
					ChangeMotion(CMotion::PLAYER_NEUTRAL);
				}
				else
				{
					//�ړ��̓��͏���
					MoveInput();
				}
			}
			else
			{
				//�ړ��̓��͏���
				MoveInput();
			}
		}

		//�������Ă��Ԃ̂Ƃ�
		if(m_bChainThunder)
		{
			//���̃G�t�F�N�g����
			ChainThunder();
		}
	}

	//�X�V
	CCharacter::Update();
}
//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void CPlayer::Draw()
{
	CCharacter::Draw();
}

//------------------------------------------------------------------------------
//�f�o�b�O���\�L
//------------------------------------------------------------------------------
void CPlayer::ShowDebugInfo()
{
#ifdef _DEBUG
	//�v���C���[�����
	if (ImGui::TreeNode("PlayerInfo"))
	{
		//�L�����N�^�[���\��
		ShowCharacterInfo();

		ImGui::TreePop();
	}
#endif //DEBUG
}

//------------------------------------------------------------------------------
//�_���[�W�󂯂���̏���
//------------------------------------------------------------------------------
void CPlayer::DamageAction()
{
	//���Đ�
	CManager::GetSound()->Play(CSound::LABEL_SE_SLASH_PLAYER);

	//����Ԃ�
	CFrontUI::Create(SCREEN_CENTER_POS, SCREEN_SIZE, WhiteColor, CFrontUI::PLAYER_HIT);

	//nullcheck
	if (m_pGauge)
	{
		//�Q�[�W�X�V
		m_pGauge->SetLife(GetLife(), GetBlueLife());
	}

	//��e���[�V����
	ChangeMotion(CMotion::PLAYER_HIT);
}
//------------------------------------------------------------------------------
//���S���̏���
//------------------------------------------------------------------------------
void CPlayer::DeathAction()
{
	//�Q�[���I��
	CManager::GetGame()->SetGamestate(CGame::STATE_GAMECLEAR);
	m_bClearedAlive = false;
}
//------------------------------------------------------------------------------
//�X�e�[�g�ύX����
//------------------------------------------------------------------------------
void CPlayer::SetState(STATE nextstate)
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
		//���S��
	case CCharacter::STATE_DEATH:
		//�Q�[���I����\������܂ł̃J�E���g
		SetCntState(240);

		//���S���[�V����
		ChangeMotion(CMotion::PLAYER_DEATH);
		break;
	}
}
//------------------------------------------------------------------------------
//�A���J�n
//------------------------------------------------------------------------------
void CPlayer::StartChainThunder()
{
	//���d�͐ݒ�
	SetGravity(false, 50);

	//�ړ��ʂ�S������
	GetMove() = ZeroVector3;

	//���[�V�����ύX�Ɨ�������ԊJ�n
	ChangeMotion(CMotion::PLAYER_ATTACK_THUNDER);
	m_bChainThunder = true;
	m_nCntChainThunder = 0;
}

//------------------------------------------------------------------------------
//�U�����̐���
//------------------------------------------------------------------------------
void CPlayer::AttackTurning()
{
	//�J������]���擾
	float fCameraRot = CManager::GetRenderer()->GetCamera()->GetCameraRot().y;

	//���݂̉�]�̌���n�擾
	D3DXVECTOR3 &rRotdest = GetRotDest();

	//�X�e�B�b�N�œ��͂��ꂽ��
	if (!CHossoLibrary::Check3DMoveStick(ZeroVector3, 1.0f, fCameraRot, rRotdest.y))
	{
		//�Ȃ񂩂���̃L�[�����͂��ꂽ�ꍇ
		if (CHossoLibrary::CheckMove(CHossoLibrary::LEFT) || CHossoLibrary::CheckMove(CHossoLibrary::RIGHT) ||
			CHossoLibrary::CheckMove(CHossoLibrary::UP) || CHossoLibrary::CheckMove(CHossoLibrary::DOWN))
		{
			if (CHossoLibrary::CheckMove(CHossoLibrary::LEFT))
			{
				if (CHossoLibrary::CheckMove(CHossoLibrary::UP))
				{
					rRotdest.y = D3DX_PI * 0.75f + fCameraRot;
				}
				else if (CHossoLibrary::CheckMove(CHossoLibrary::DOWN))
				{
					rRotdest.y = D3DX_PI * 0.25f + fCameraRot;
				}
				else
				{
					rRotdest.y = D3DX_PI * 0.5f + fCameraRot;
				}
			}
			else if (CHossoLibrary::CheckMove(CHossoLibrary::RIGHT))
			{
				if (CHossoLibrary::CheckMove(CHossoLibrary::UP))
				{
					rRotdest.y = -D3DX_PI * 0.75f + fCameraRot;
				}
				else if (CHossoLibrary::CheckMove(CHossoLibrary::DOWN))
				{
					rRotdest.y = -D3DX_PI * 0.25f + fCameraRot;
				}
				else
				{
					rRotdest.y = -D3DX_PI * 0.5f + fCameraRot;
				}
			}
			else if (CHossoLibrary::CheckMove(CHossoLibrary::UP))
			{
				rRotdest.y = -D3DX_PI * 1.0f + fCameraRot;

			}
			else if (CHossoLibrary::CheckMove(CHossoLibrary::DOWN))
			{
				rRotdest.y = fCameraRot;
			}
		}
	}
}
//------------------------------------------------------------------------------
//��������
//------------------------------------------------------------------------------
std::shared_ptr<CPlayer> CPlayer::Create(D3DXVECTOR3 pos)
{
	//�ϐ��錾
	std::shared_ptr<CPlayer> pPlayer = std::make_shared<CPlayer>();

	if (pPlayer)
	{
		//������7
		pPlayer->Init();

		//���W�ݒ�
		pPlayer->SetPos(pos);

		//�p�����[�^�ݒ�
		pPlayer->SetParameter(MODEL_TYPE::MODEL_PLAYER,CCharacter::PARAM_PLAYER,pPlayer);

		//�I�u�W�F�N�g�^�C�v�ݒ�
		pPlayer->SetObjType(OBJTYPE_PLAYER);

		//���X�g�ɒǉ�
		pPlayer->AddSharedList(pPlayer);

		//�Q�[���̎�����
		if(CManager::GetMode() == CManager::MODE_GAME)
		{
			//HP�Q�[�W����
			pPlayer->m_pGauge = CGauge_2D::Create(D3DXVECTOR3(250.0f, 680.0f, 0.0f), D3DXVECTOR3(200.0f, 20.0f, 0.0f), pPlayer->GetLife());
		}

		return pPlayer;
	}

	//�����������
	return nullptr;
}

//------------------------------------------------------------------------------
//�ړ��̓���
//------------------------------------------------------------------------------
void CPlayer::MoveInput()
{
	D3DXVECTOR3 &rMove = GetMove();		//�ړ����擾
	D3DXVECTOR3 &rRotdest = GetRotDest();	//��]���擾

	if (!GetAttack())
	{
		//�ړ����x
		float fMoveSpeed;

		//�_�b�V�����Ă��邩�m�F
		CHossoLibrary::CheckDash(CHossoLibrary::PRESS) ?
			fMoveSpeed = GetDefaultParam(CCharacter::GetParamType())->GetDashSpeed() :		//�������x
			fMoveSpeed = GetDefaultParam(CCharacter::GetParamType())->GetMoveSpeed();			//�_�b�V�����x

		//�W�����v��Ԃ̏ꍇ
		if (GetJump())
		{
			fMoveSpeed = GetDefaultParam(CCharacter::GetParamType())->GetAirSpeeed();			//�󒆂̈ړ����x
		}

		//�J������]���擾
		float fCameraRot = CManager::GetRenderer()->GetCamera()->GetCameraRot().y;

		//JoyStick�ɂ�����
		//���͂��Ȃ������ꍇ�̓L�[�{�[�h����擾
		if (!CHossoLibrary::Check3DMoveStick(rMove, fMoveSpeed, fCameraRot, rRotdest.y))
		{
			if (CHossoLibrary::CheckMove(CHossoLibrary::LEFT))
			{
				if (CHossoLibrary::CheckMove(CHossoLibrary::UP))
				{
					//����
					rMove.x += sinf(-D3DX_PI * 0.75f - fCameraRot) * fMoveSpeed;
					rMove.z -= cosf(-D3DX_PI * 0.75f - fCameraRot) * fMoveSpeed;

					rRotdest.y = D3DX_PI * 0.75f + fCameraRot;
				}
				else if (CHossoLibrary::CheckMove(CHossoLibrary::DOWN))
				{
					//����
					rMove.x += sinf(-D3DX_PI * 0.25f - fCameraRot) * fMoveSpeed;
					rMove.z -= cosf(-D3DX_PI * 0.25f - fCameraRot) * fMoveSpeed;

					rRotdest.y = D3DX_PI * 0.25f + fCameraRot;
				}
				else
				{
					//��
					rMove.x += sinf(-D3DX_PI * 0.5f - fCameraRot) * fMoveSpeed;
					rMove.z -= cosf(-D3DX_PI * 0.5f - fCameraRot) * fMoveSpeed;

					rRotdest.y = D3DX_PI * 0.5f + fCameraRot;
				}
			}
			else if (CHossoLibrary::CheckMove(CHossoLibrary::RIGHT))
			{
				if (CHossoLibrary::CheckMove(CHossoLibrary::UP))
				{
					//�E��
					rMove.x += sinf(D3DX_PI * 0.75f - fCameraRot) * fMoveSpeed;
					rMove.z -= cosf(D3DX_PI * 0.75f - fCameraRot) * fMoveSpeed;

					rRotdest.y = -D3DX_PI * 0.75f + fCameraRot;
				}
				else if (CHossoLibrary::CheckMove(CHossoLibrary::DOWN))
				{
					//�E��
					rMove.x += sinf(D3DX_PI * 0.25f - fCameraRot) * fMoveSpeed;
					rMove.z -= cosf(D3DX_PI * 0.25f - fCameraRot) * fMoveSpeed;

					rRotdest.y = -D3DX_PI * 0.25f + fCameraRot;
				}
				else
				{
					//�E
					rMove.x += sinf(D3DX_PI * 0.5f - fCameraRot) * fMoveSpeed;
					rMove.z -= cosf(D3DX_PI * 0.5f - fCameraRot) * fMoveSpeed;

					rRotdest.y = -D3DX_PI * 0.5f + fCameraRot;

				}
			}
			else if (CHossoLibrary::CheckMove(CHossoLibrary::UP))
			{
				//��
				rMove.x += sinf(D3DX_PI * 1.0f - fCameraRot) * fMoveSpeed;
				rMove.z -= cosf(D3DX_PI * 1.0f - fCameraRot) * fMoveSpeed;

				rRotdest.y = -D3DX_PI * 1.0f + fCameraRot;

			}
			else if (CHossoLibrary::CheckMove(CHossoLibrary::DOWN))
			{
				//��
				rMove.x += sinf(D3DX_PI * 0 - fCameraRot) * fMoveSpeed;
				rMove.z -= cosf(D3DX_PI * 0 - fCameraRot) * fMoveSpeed;

				rRotdest.y = fCameraRot;
			}
		}
		//��]����
		CCharacter::SetRotDest(rRotdest);
	}

	//�W�����v�L�[
	if (CHossoLibrary::CheckJump(CHossoLibrary::TRIGGER))
	{
		//�܂��W�����v���Ă��Ȃ�&&���������Ă��Ȃ���
		if (!GetJump() && !m_bChainThunder)
		{
			//�ړ����擾
			D3DXVECTOR3 &rMove = GetMove();

			//������ɐi��
			rMove.y = GetDefaultParam(CCharacter::GetParamType())->GetJumpSpeed();

			//�W�����v�ɐ؂�ւ�
			SetJump(true);
			ChangeMotion(CMotion::PLAYER_JUMP);

			//���Đ�
			CManager::GetSound()->Play(CSound::LABEL_SE_JUMP);
		}
	}
	//�U���̓���
	if (AttackInput())
	{
		//��]
		AttackTurning();
		SetAttack(true);
	}

	//�J�������Z�b�g
	if (CHossoLibrary::CheckCameraReset(CHossoLibrary::TRIGGER))
	{
		//�J�����̉�]�ʎ擾
		D3DXVECTOR3 &CameraRot = CManager::GetRenderer()->GetCamera()->GetCameraRot();

		//���݌����Ă�������ݒ�
		CameraRot.y = GetRotDest().y + D3DX_PI;

		//3.14�Ɏ��߂�
		CHossoLibrary::CalcRotation(CameraRot.y);

		//�J������]
		CManager::GetRenderer()->GetCamera()->SetCameraRot(CameraRot);

	}

	//�ړ��ɉ����ă��[�V�����m�F
	MoveMotionCheck();
}

//------------------------------------------------------------------------------
//�A���̂Ƃ��̃G�t�F�N�g
//------------------------------------------------------------------------------
void CPlayer::ChainThunder()
{
	//���p�̃J�E���^++
	m_nCntChainThunder++;

	//�J�E���^�̐��l�ŃA�N�V����
	switch (m_nCntChainThunder)
	{

	case 10:
		//�����̕��Ɋ���Ă��銴���̉~
		CCircle_Effect::Create(GetPos(), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), 19, 400.0f, 600.0f, 8, -20.0f, -30.0f, -0.05f);
		CCircle_Effect::Create(GetPos(), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), 19, 800.0f, 1200.0f, 8, -40.0f, -60.0f, -0.05f);

		break;

	case 25:
		//����
		CEffectAnimation3D::Create(GetPos() + D3DXVECTOR3(0.0f, 300.0f, 0.0f), D3DXVECTOR3(1500.0f, 1500.0f, 0.0f), CTexture::SEPARATE_TEX_EFFECT_CHAINTHUNDER, WhiteColor, 0.0f, 2);

		//���Đ�
		CManager::GetSound()->Play(CSound::LABEL_SE_START_CHAIN);

		break;

	case 30:
		//�t���b�V��
		CEffectAnimation2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 0.0f, 0.0f), D3DXVECTOR3(2000.0f, 2000.0f, 0.0f), CTexture::SEPARATE_TEX_EFFECT_FLASH, 0.0f, 5, CScene::OBJTYPE_BACK);

		break;

	case 40:
		//���o�`���Ȃ��
		CEffectAnimation3D::Create(GetCenterPos(), D3DXVECTOR3(250.0f, 250.0f, 0.0f), CTexture::SEPARATE_TEX_EFFECT_SPARKEXPLOSION, WhiteColor, 0.0f, 2);

		//�X�t�B�A�̔���
		CSphere_Explosion::Create(GetCenterPos(), 50.0f, 100);

		//�A�������J�n
		CEnemy::ChainExplosion(GetPos());

		break;

	default:
		break;
	}
}


//------------------------------------------------------------------------------
//�A���U���̎��̃��[�V�����ǂꂾ
//------------------------------------------------------------------------------
bool CPlayer::AttackInput()
{
	bool bAttack = false;
	CMotion::MOTION_TYPE NowMotion = GetNowMotion();

	//���݂̃��[�V�����ɉ����Ď��̓��������߂�
	switch (NowMotion)
	{
		//�n�ʂɑ������Ă���Ƃ�
	case CMotion::PLAYER_NEUTRAL:
	case CMotion::PLAYER_WALK:
	case CMotion::PLAYER_DASH:

		//X�{�^��
		if (CHossoLibrary::CheckAttack_X(CHossoLibrary::TRIGGER))
		{
			ChangeMotion(CMotion::PLAYER_LAND_ATTACK_X_01);
			return true;
		}

		//Y�{�^��
		if (CHossoLibrary::CheckAttack_Y(CHossoLibrary::TRIGGER))
		{
			ChangeMotion(CMotion::PLAYER_LAND_ATTACK_Y_01);
			return true;
		}

		//B�{�^��
		if (CHossoLibrary::CheckAttack_B(CHossoLibrary::TRIGGER))
		{
			StartChainThunder();
			return true;
		}
		break;

		//�󒆂ɂ��鎞
	case CMotion::PLAYER_AIR_NEUTRAL:
	case CMotion::PLAYER_JUMP:

		//X�{�^��
		if (CHossoLibrary::CheckAttack_X(CHossoLibrary::TRIGGER))
		{
			if (!GetAirAttack())
			{
				ChangeMotion(CMotion::PLAYER_AIR_ATTACK_X_01);
				SetAirAttack(true);
				SetGravity(false, 17);

				return true;
			}
		}

		//Y�{�^��
		if (CHossoLibrary::CheckAttack_Y(CHossoLibrary::TRIGGER))
		{
			ChangeMotion(CMotion::PLAYER_ATTACK_SLAMS);
			GetMove().y = 0.0f;
			SetGravity(false, 5);
			return true;
		}

		//B�{�^��
		if (CHossoLibrary::CheckAttack_B(CHossoLibrary::TRIGGER))
		{
			if (!GetAirAttack())
			{
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

	//X�{�^��
	if (CHossoLibrary::CheckAttack_X(CHossoLibrary::TRIGGER))
	{
		switch (NowMotion)
		{
			//�n��U���̎�
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

			//�󒆍U���̎�
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

	//Y�{�^��
	if (CHossoLibrary::CheckAttack_Y(CHossoLibrary::TRIGGER))
	{
		//X�{�^���̐i�s��Ő؂�ւ���
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

	//Y�{�^��
	if (CHossoLibrary::CheckAttack_Y(CHossoLibrary::TRIGGER))
	{
		//�󒆍U���̊�
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

	//B�{�^��
	if (CHossoLibrary::CheckAttack_B(CHossoLibrary::TRIGGER))
	{
		switch (NowMotion)
		{
			//�ǂ̍U��������Ȃ���悤��
		case CMotion::MOTION_NONE:
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
			StartChainThunder();
			SetAirAttack(true);
			bAttack = true;
			break;

		}
	}
	return bAttack;
}

//------------------------------------------------------------------------------
//�ړ����x����Ƀ��[�V�����؂�ւ�
//------------------------------------------------------------------------------
void CPlayer::MoveMotionCheck()
{
	//�ړ����擾
	D3DXVECTOR3 &rMove = GetMove();

	//�ړ����x�̐�Βl
	float fMoveSpeed = fabsf(D3DXVec2Length(&D3DXVECTOR2(rMove.x, rMove.z)));

	//�܂��U�����ĂȂ������ꍇ
	if (!GetAttack() && !GetJump())
	{
		//�ړ����x�Ń��[�V�����ύX
		if (fMoveSpeed > 1.0f)
		{
			//�ړ����x��������
			if (fMoveSpeed > 6.0f)
			{
				//���郂�[�V����
				ChangeMotion(CMotion::PLAYER_DASH);
			}
			//������x�̑��x�̎�
			else
			{
				//�������[�V����
				ChangeMotion(CMotion::PLAYER_WALK);
			}

			//�����n�ɂ��^�C�~���O
			if (CCharacter::GetModelCharacterPtr()->GetKey() % 2 == 1 && CCharacter::GetModelCharacterPtr()->GetFrame() == 0)
			{
				//������炷
				CManager::GetSound()->Play(CSound::LABEL_SE_WALK);

			}
		}
		else
		{
			//�j���[�g����
			ChangeMotion(CMotion::PLAYER_NEUTRAL);
		}
	}
}


