// =====================================================================================================================================================================
//
// �v���C���[�̏��� [player.cpp]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#include "player.h"			// �C���N���[�h�t�@�C��
#include "renderer.h"
#include "manager.h"
#include "debugproc.h"
#include "camera.h"
#include "keyboard.h"
#include "game.h"
#include "scene3D.h"
#include "modelcharacter.h"
#include "slope.h"
#include "map.h"
#include "gameUI.h"
#include "fade.h"
#include "object2D.h"
#include "sound.h"
#include "xinputGpad.h"

// =====================================================================================================================================================================
// �ÓI�����o�ϐ��̏�����
// =====================================================================================================================================================================
CModelCharacter				*CPlayer::m_pModelCharacter = NULL;
CPlayer::PLAYERSTATE		CPlayer::m_state = PLAYERSTATE::PLAYERSTATE_NONE;

// =====================================================================================================================================================================
// �}�N����`
// =====================================================================================================================================================================
#define TEXTURE_FILE		"data/TEXTURE/kids.jpg"	// �ǂݍ��ރe�N�X�`���t�@�C����

#define PLAYER_SIZEX		(300 / 2)				// ���W�̕�
#define PLAYER_SIZEY		(220 / 2)				// ���W�̍���

#define PLAYER_SPEED		(2)						// �v���C���[�̑���
#define PLAYER_RADIUS		(10.0f)					// �v���C���[�̔��a
#define PLAYER_MAX_LIFE		(99)					// �v���C���[�̍ő�̗�

#define FALL_DISTANCE		(70)					// ���������鋗��

#define FLASHING_TIME		(90)					// �_�ł��鎞��
#define FLASHING_INTERVAL	(3)						// �_�ł��銴�o

#define MOVE_MOTION_VALUE	(0.2f)					// �ړ����[�V��������Ƃ��̈ړ���
#define INERTIA_VALUE		(0.3f)					// �����̒l
#define ROT_DIFFERENCE		(0.15f)					// ��]�̍���
#define FIELD_LIMIT			(145.0f)				// �t�B�[���h�̌��E�͈�
#define JUMP_VALUE			(4)						// �W�����v�̒l
#define GRAVITY_VALUE		(0.5f)					// �d�͂̒l

// =====================================================================================================================================================================
//
// �R���X�g���N�^
//
// =====================================================================================================================================================================
CPlayer::CPlayer():CScene()
{
}

// =====================================================================================================================================================================
//
// �R���X�g���N�^
//
// =====================================================================================================================================================================
CPlayer::CPlayer(PRIORITY Priority) :CScene(Priority)
{
}

// =====================================================================================================================================================================
//
// �f�X�g���N�^
//
// =====================================================================================================================================================================
CPlayer::~CPlayer()
{
}

// =====================================================================================================================================================================
//
// ����������
//
// =====================================================================================================================================================================
void CPlayer::Init()
{
	// �ϐ�������
	m_pos			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �ʒu
	m_posOld		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �ߋ��̈ʒu
	m_posRestart	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �ĊJ�ʒu
	m_size			= D3DXVECTOR3(4.0f, 50.0f, 4.0f);			// �T�C�Y
	m_move			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �ړ�
	m_rot			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ��]
	m_rotDiff		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �����̍���
	m_rotDest		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �ړI�̌���
	m_fJumpingPos	= 0;										// �n�ʂ��痣�ꂽ�u�Ԃ̈ʒu
	m_fLandingPos	= 0;										// ���n�������̈ʒu
	m_bJump			= false;									// �W�����v�t���O
	m_bFlashing		= false;									// ���񂾂Ƃ��̓_�Ńt���O
	m_bLand			= false;									// ���n�����Ƃ��̃t���O
	m_nCntDeath		= 0;										// ���񂾂Ƃ��̃J�E���g
	m_nLife			= 3;										// �̗�
	m_state			= PLAYERSTATE_APPEAR;						// �v���C���[�̏��
	m_LeftStick_X	= 0;										// ���X�e�B�b�N��X�̒l
	m_LeftStick_Y	= 0;										// ���X�e�B�b�N��Y�̒l
	m_RightStick_X	= 0;										// �E�X�e�B�b�N��X�̒l
	m_RightStick_Y	= 0;										// �E�X�e�B�b�N��Y�̒l
}

// =====================================================================================================================================================================
//
// �I������
//
// =====================================================================================================================================================================
void CPlayer::Uninit(void)
{
	if (m_pModelCharacter != NULL)
	{
		// ���f���L�����N�^�[�̏I��
		m_pModelCharacter->Uninit();

		// �������J��
		delete m_pModelCharacter;
		m_pModelCharacter = NULL;
	}
}

// =====================================================================================================================================================================
//
// �X�V����
//
// =====================================================================================================================================================================
void CPlayer::Update(void)
{
	// �ϐ�
	CCamera *pCamera;
	CKeyboard *pKeyboard;
	CXinputGpad *pXinputGpad;
	// �������̊m��
	pKeyboard = CManager::GetKeyboard();
	pCamera = CRenderer::GetCamera();
	pXinputGpad = CManager::GetXinputGpad();

	m_bLand = false;	// �n��ɂ��锻��
	m_posOld = m_pos;	// �ߋ��̈ʒu�̕ۑ�

	// ==========================================================================
	// ----- [ �W�����v ] -----
	// ==========================================================================
	if (!m_bJump)
	{
		if (pKeyboard->GetKeyboardTrigger(DIK_SPACE) || pXinputGpad->GetTriggerXinputGpad(CXinputGpad::XINPUT_A))
		{
			//	�W�����v��
			CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_JUMP);

			m_fJumpingPos = m_pos.y;		// ��Ԉʒu�̕ۑ�

			// �W�����v���[�V����
			m_pModelCharacter->SetMotion(CModelCharacter::PlayerMotionType_JUMP);

			m_bJump = true;			// �W�����v���Ă�����

			m_move.y += PLAYER_SPEED * JUMP_VALUE;		// �W�����v�l
		}
	}

	// ����łȂ��Ƃ�
	if (m_state != PLAYERSTATE_DEATH)
	{
		// �v���C���[�̈ړ�����
		MovePlayer();
	}

	// �ړ��ʂ����߂�
	float MoveValue = D3DXVec2Length(&D3DXVECTOR2(m_move.x, m_move.z));
	// ��Βl�v�Z
	MoveValue = fabsf(MoveValue);

	// �W�����v���Ă��Ȃ��Ƃ�
	if (!m_bJump)
	{
		// ���̈ړ��ʂɒB���Ă�����
		if (MoveValue >= MOVE_MOTION_VALUE)
		{
			// �������[�V����
			m_pModelCharacter->SetMotion(CModelCharacter::PlayerMotionType_WALK);
		}
		else
		{
			// �j���[�g�������[�V����
			m_pModelCharacter->SetMotion(CModelCharacter::PlayerMotionType_NEUTRAL);
		}
	}

	float fFallDistance = 0.0f;						// �������鋗��
	fFallDistance = m_fJumpingPos - m_pos.y;	// �������Ă��鋗���v�Z

	// ����������
	if (fFallDistance >= FALL_DISTANCE)
	{
		// �v���C���[�̗�����
		PlayerFallDeath();
	}

#ifdef _DEBUG
	// [ �����l�ɖ߂� ]	�����I�z�u
	if (pKeyboard->GetKeyboardPress(DIK_0))
	{
		D3DXVECTOR3 pos = D3DXVECTOR3(m_pos.x, m_pos.y + 10.0f, m_pos.z);

		m_pos = pos;
	}
#endif

	// �I�u�W�F�N�g�̓����蔻��
	if (CMap::CollisionObjectAll(&m_pos, &m_posOld, &m_move, &m_size))
	{
		if (m_bJump)
		{
			//	���n��
			CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_LAND);
			// ���n����
			m_bLand = true;
		}

		m_bJump = false;

		m_fLandingPos = m_pos.y;	// ��Ԉʒu�̕ۑ�

		float fFallDistance = 0.0f;								// ������������
		fFallDistance = m_fJumpingPos - m_fLandingPos;	// �������������v�Z

		// ����������
		if (fFallDistance >= FALL_DISTANCE)
		{
			// �v���C���[�̗�����
			PlayerFallDeath();
		}
		m_fJumpingPos = m_pos.y;		// ��Ԉʒu�̕ۑ�
	}
	// 2D�I�u�W�F�N�g�̓����蔻��
	else if (CMap::CollisionObject2DAll(&m_pos, &m_posOld, &m_move, &m_size))
	{
		if (m_bJump)
		{
			//	���n��
			CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_LAND);
			// ���n����
			m_bLand = true;
		}

		m_bJump = false;

		m_fLandingPos = m_pos.y;	// ��Ԉʒu�̕ۑ�

		float fFallDistance = 0.0f;								// ������������
		fFallDistance = m_fJumpingPos - m_fLandingPos;	// �������������v�Z

		// ����������
		if (fFallDistance >= FALL_DISTANCE)
		{
			// �v���C���[�̗�����
			PlayerFallDeath();
		}
		m_fJumpingPos = m_pos.y;		// ��Ԉʒu�̕ۑ�
	}
	// ��̓����蔻��
	else if (CMap::GetHeightSlopeAll(m_pos, m_move))
	{
		if (m_bJump)
		{
			//	���n��
			CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_LAND);
			// ���n����
			m_bLand = true;
		}

		m_bJump = false;

		m_fLandingPos = m_pos.y;	// ��Ԉʒu�̕ۑ�

		float fFallDistance = 0.0f;								// ������������
		fFallDistance = m_fJumpingPos - m_fLandingPos;			// �������������v�Z

		// ����������
		if (fFallDistance >= FALL_DISTANCE)
		{
			// �v���C���[�̗�����
			PlayerFallDeath();
		}
		m_fJumpingPos = m_pos.y;		// ��Ԉʒu�̕ۑ�
	}
	else
	{
		m_bJump = true;		// �W�����v�ł�����
	}

	// ���f���L�����N�^�[�̍X�V
	m_pModelCharacter->Update();

	// ���[���h�}�g���b�N�X�̌v�Z
	CLibrary::MatrixCalculation(&m_mtxWorld, m_rot, m_pos);

	// ���C�t�̐ݒ�
	CManager::GetGame()->GetGameUI()->SetLife(m_nLife);

	// �v���C���[�̏�Ԃ̊e�ݒ�
	PlayerStateConfig();

	// �f�o�b�O�\��
	CDebugProc::Print("PlayerPos :(%.0f, %.0f, %.0f)\n", m_pos.x, m_pos.y, m_pos.z);

	ImGui::SliderFloat3("player_pos", m_pos, -50000.0f, 50000.0f);
}

// =====================================================================================================================================================================
//
// �`�揈��
//
// =====================================================================================================================================================================
void CPlayer::Draw(void)
{
	if (!m_bFlashing)
	{
		// �}�g���b�N�X�̐ݒ�
		m_pModelCharacter->SetMatrix(&m_mtxWorld);

		// ���f���L�����N�^�[�̕`��
		m_pModelCharacter->Draw();
	}
}

// =====================================================================================================================================================================
//
// �v���C���[�̐���
//
// =====================================================================================================================================================================
CPlayer * CPlayer::Create()
{
	// �ϐ�
	CPlayer *pPlayer;

	// �������̊m��
	pPlayer = new CPlayer(PRIORITY_MODEL);

	// ���f���L�����N�^�[�̐���
	pPlayer->m_pModelCharacter = CModelCharacter::Create();

	// ������
	pPlayer->Init();

	return pPlayer;
}

// =====================================================================================================================================================================
//
// ���[�h
//
// =====================================================================================================================================================================
HRESULT CPlayer::Load(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = *CManager::GetRenderer()->GetDevice();

	return S_OK;
}

// =====================================================================================================================================================================
//
// �A�����[�h
//
// =====================================================================================================================================================================
void CPlayer::Unload(void)
{

}

// =====================================================================================================================================================================
//
// �v���C���[�̈ړ�����
//
// =====================================================================================================================================================================
void CPlayer::MovePlayer(void)
{
	// �ϐ�
	CCamera *pCamera;
	CKeyboard *pKeyboard;
	CXinputGpad *pXinputGpad;

	// �������̊m��
	pCamera = CManager::GetRenderer()->GetCamera();
	pKeyboard = CManager::GetKeyboard();
	pXinputGpad = CManager::GetXinputGpad();

	// �J�����̉�]
	D3DXVECTOR3 CameraRot = CManager::GetRenderer()->GetCamera()->GetRot();

	// ���X�e�B�b�N�̒l�̎擾
	pXinputGpad->GetLeftStickValue(m_LeftStick_X, m_LeftStick_Y);

	// ���X�e�B�b�N��|�����Ƃ��̊p�x
	float fLeftStickAngle = atan2f(m_LeftStick_X, m_LeftStick_Y);
	// ���X�e�B�b�N��|�����Ƃ��̌���
	D3DXVECTOR2 LeftStickVec = D3DXVECTOR2((float)sin(fLeftStickAngle - CameraRot.y), (float)cos(fLeftStickAngle - CameraRot.y));
	CDebugProc::Print("���X�e�B�b�N X ( %f )\n", LeftStickVec.x);
	CDebugProc::Print("���X�e�B�b�N Y ( %f )\n", LeftStickVec.y);

	// -------------------------------------------------------------------------
	// [ ���X�e�B�b�N�ړ� ]
	// -------------------------------------------------------------------------
	if (m_LeftStick_X > 0 || m_LeftStick_Y > 0 ||
		m_LeftStick_X < 0 || m_LeftStick_Y < 0)
	{
		if (m_move != D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		{
			m_rotDest.y = (D3DX_PI + fLeftStickAngle - CameraRot.y);
		}
		m_move.x += PLAYER_SPEED * LeftStickVec.x;
		m_move.z += PLAYER_SPEED * LeftStickVec.y;
	}

	// -------------------------------------------------------------------------
	// [ ���ړ� ]
	// -------------------------------------------------------------------------
	if (pKeyboard->GetKeyboardPress(DIK_A))
	{
		if (pKeyboard->GetKeyboardPress(DIK_W))
		{// ����
			// �J�������[�h��2D����Ȃ��Ƃ�
			if (pCamera->GetCameraMode() != CCamera::CAMERA_MODE_2D)
			{
				m_rotDest.y = (D3DX_PI * 0.75f - CameraRot.y);

				m_move.x += sinf(-D3DX_PI * 0.75f + CameraRot.y) * PLAYER_SPEED;
				m_move.z -= cosf(-D3DX_PI * 0.75f + CameraRot.y) * PLAYER_SPEED;
			}
		}
		else if (pKeyboard->GetKeyboardPress(DIK_S))
		{// ����
			// �J�������[�h��2D����Ȃ��Ƃ�
			if (pCamera->GetCameraMode() != CCamera::CAMERA_MODE_2D)
			{
				m_rotDest.y = (D3DX_PI * 0.25f - CameraRot.y);

				m_move.x += sinf(-D3DX_PI * 0.25f + CameraRot.y) * PLAYER_SPEED;
				m_move.z -= cosf(-D3DX_PI * 0.25f + CameraRot.y) * PLAYER_SPEED;
			}
		}
		else
		{// ��
			m_rotDest.y = (D3DX_PI * 0.5f - CameraRot.y);

			m_move.x += sinf(-D3DX_PI * 0.5f + CameraRot.y) * PLAYER_SPEED;
			m_move.z -= cosf(-D3DX_PI * 0.5f + CameraRot.y) * PLAYER_SPEED;
		}
	}

	// -------------------------------------------------------------------------
	// [ �E�ړ� ]
	// -------------------------------------------------------------------------
	else if (pKeyboard->GetKeyboardPress(DIK_D))
	{
		if (pKeyboard->GetKeyboardPress(DIK_W))
		{// �E��
			// �J�������[�h��2D����Ȃ��Ƃ�
			if (pCamera->GetCameraMode() != CCamera::CAMERA_MODE_2D)
			{
				m_rotDest.y = (-D3DX_PI * 0.75f - CameraRot.y);

				m_move.x += sinf(D3DX_PI * 0.75f + CameraRot.y) * PLAYER_SPEED;
				m_move.z -= cosf(D3DX_PI * 0.75f + CameraRot.y) * PLAYER_SPEED;
			}

		}
		else if (pKeyboard->GetKeyboardPress(DIK_S))
		{// �E��
			// �J�������[�h��2D����Ȃ��Ƃ�
			if (pCamera->GetCameraMode() != CCamera::CAMERA_MODE_2D)
			{
				m_rotDest.y = (-D3DX_PI * 0.25f - CameraRot.y);

				m_move.x += sinf(D3DX_PI * 0.25f + CameraRot.y) * PLAYER_SPEED;
				m_move.z -= cosf(D3DX_PI * 0.25f + CameraRot.y) * PLAYER_SPEED;
			}

		}
		else
		{// �E
			m_rotDest.y = (-D3DX_PI * 0.5f - CameraRot.y);

			m_move.x += sinf(D3DX_PI * 0.5f + CameraRot.y) * PLAYER_SPEED;
			m_move.z -= cosf(D3DX_PI * 0.5f + CameraRot.y) * PLAYER_SPEED;
		}
	}
	// -------------------------------------------------------------------------
	// [ �O�ړ� ]
	// -------------------------------------------------------------------------
	else if (pKeyboard->GetKeyboardPress(DIK_W))
	{
		// �J�������[�h��2D����Ȃ��Ƃ�
		if (pCamera->GetCameraMode() != CCamera::CAMERA_MODE_2D)
		{
			m_rotDest.y = (D3DX_PI * 1.0f - CameraRot.y);

			m_move.x += sinf(D3DX_PI * 1.0f + CameraRot.y) * PLAYER_SPEED;
			m_move.z -= cosf(D3DX_PI * 1.0f + CameraRot.y) * PLAYER_SPEED;
		}
	}
	// -------------------------------------------------------------------------
	// [ ��ړ� ]
	// -------------------------------------------------------------------------
	else if (pKeyboard->GetKeyboardPress(DIK_S))
	{
		// �J�������[�h��2D����Ȃ��Ƃ�
		if (pCamera->GetCameraMode() != CCamera::CAMERA_MODE_2D)
		{
			m_rotDest.y = (D3DX_PI * 0.0f - CameraRot.y);

			m_move.x += sinf(D3DX_PI * 0.0f + CameraRot.y) * PLAYER_SPEED;
			m_move.z -= cosf(D3DX_PI * 0.0f + CameraRot.y) * PLAYER_SPEED;
		}
	}

	// ����
	m_rotDiff.y = m_rotDest.y - m_rot.y;

	// ��]���̍�����������
	if (m_rotDiff.y > D3DX_PI)
	{
		m_rotDiff.y -= D3DX_PI * 2;
	}
	if (m_rotDiff.y <= -D3DX_PI)
	{
		m_rotDiff.y += D3DX_PI * 2;
	}

	// ��������
	m_move.x += (0 - m_move.x) * INERTIA_VALUE;
	m_move.z += (0 - m_move.z) * INERTIA_VALUE;

	// �d�͏���
	m_move.y -= GRAVITY_VALUE;

	// �ʒu�X�V
	m_pos += m_move;

	// ��]�X�V 
	m_rot.y += m_rotDiff.y * ROT_DIFFERENCE;

	// ��]����������
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2;
	}
	if (m_rot.y <= -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2;
	}

	// �J�������[�h��2D�̂Ƃ�
	if (pCamera->GetCameraMode() == CCamera::CAMERA_MODE_2D)
	{
		m_pos.x = 0.0f;
	}

	// �v���C���[�̈ړ�����
	if (m_pos.x <= -FIELD_LIMIT)
	{
		m_move.x = 0.0f;
		m_pos.x = -FIELD_LIMIT;
	}
	else if (m_pos.x >= FIELD_LIMIT)
	{
		m_move.x = 0.0f;
		m_pos.x = FIELD_LIMIT;
	}
}

// =====================================================================================================================================================================
//
// �v���C���[�̏�Ԃ̊e�ݒ�
//
// =====================================================================================================================================================================
void CPlayer::PlayerStateConfig(void)
{
	// �J�����̏��
	CCamera *pCamera;
	pCamera = CRenderer::GetCamera();

	switch (m_state)
	{
	case CPlayer::PLAYERSTATE_APPEAR:
		break;
	case CPlayer::PLAYERSTATE_NORMAL:
		break;
	case CPlayer::PLAYERSTATE_SPEED:
		break;
	case CPlayer::PLAYERSTATE_FALL:
		break;
	case CPlayer::PLAYERSTATE_DEATH:
		// �J�E���g�A�b�v
		m_nCntDeath++;

		// �_�ł��銴�o
		if (m_nCntDeath % FLASHING_INTERVAL == 0)
		{
			// ���񂾂Ƃ��̓_��
			m_bFlashing = !m_bFlashing;
		}

		// ��莞�Ԍ�Ƀ��X�|�[��
		if (m_nCntDeath >= FLASHING_TIME)
		{
			if (m_nLife > 0)
			{
				// ���X�|�[���n�_�ɖ߂�		( �����I�z�u
				m_pos = m_posRestart;

				if (pCamera != NULL)
				{
					// �v���C���[�����񂾂Ƃ��̃J�����̈ʒu
					pCamera->SetDeadPlayerCameraPos(m_pos);
				}
			}

			// ��Ԉʒu�����ݒn�Ɏw��
			m_fJumpingPos = m_pos.y;

			// �_�ł��~�߂�
			m_bFlashing = false;
			// �J�E���g������
			m_nCntDeath = 0;
			// �v���C���[�̏�Ԃ�ʏ펞��
			m_state = PLAYERSTATE_NORMAL;

			if (m_nLife <= 0)
			{
				// �v���C���[�̏�Ԃ�ʏ펞��
				m_state = PLAYERSTATE_DEATH;

				// �Q�[���I��(�Q�[���G���h)
				CManager::GetGame()->SetGameMode(CGame::GAME_MODE_END);
			}
		}
		// �Q�[�W�̉�
		CGameUI::RecoveryGage();
		break;
	}
}

// =====================================================================================================================================================================
//
// �v���C���[�̗�����
//
// =====================================================================================================================================================================
void CPlayer::PlayerFallDeath(void)
{
	//	���񂾂Ƃ��̉�
	CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_DEATH);

	// �v���C���[�_���[�W
	PlayerDamage(1);

	m_state = PLAYERSTATE_DEATH;	// �v���C���[�����S��Ԃ�
}

// =====================================================================================================================================================================
//
// �_���[�W����
//
// =====================================================================================================================================================================
void CPlayer::PlayerDamage(int nLife)
{
	// ���S��ԈȊO�̂Ƃ�
	if (m_state != PLAYERSTATE_DEATH)
	{
		m_nLife -= nLife;
	}

	// �̗͂��Ȃ��Ȃ�����
	if (m_nLife <= 0)
	{
		// �̗͂�0��
		m_nLife = 0;

		// ��Ԃ����S����
		m_state = PLAYERSTATE::PLAYERSTATE_NORMAL;
	}
}

// =====================================================================================================================================================================
//
// �񕜏���
//
// =====================================================================================================================================================================
void CPlayer::PlayerRecovery(int nLife)
{
	m_nLife += nLife;

	// ���
	if (m_nLife >= PLAYER_MAX_LIFE)
	{
		m_nLife = PLAYER_MAX_LIFE;
	}
}