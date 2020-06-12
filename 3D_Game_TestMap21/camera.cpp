// =====================================================================================================================================================================
//
// �J�������� [camera.cpp]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#include "camera.h"				// �C���N���[�h�t�@�C��
#include "keyboard.h"
#include "manager.h"
#include "renderer.h"
#include "scene3D.h"
#include "sceneX.h"
#include "debugproc.h"
#include "game.h"
#include "player.h"
#include "sound.h"
#include "xinputGpad.h"

// =====================================================================================================================================================================
// �ÓI�����o�ϐ��̏�����
// =====================================================================================================================================================================
CCamera::CAMERA_MODE CCamera::m_CameraMode = CAMERA_MODE::CAMERA_MODE_3D;

// =====================================================================================================================================================================
// �}�N����`
// =====================================================================================================================================================================
#define CAMERA_SPEED			(1.5f)							// �J�����̃X�s�[�h

#define DISTANCE_V				(250.0f)						// ���_�̋���
#define DISTANCE_R				(0.0f)							// �����_�̋���

#define NEAR_VALUE				(10.0f)							// �r���[�{�����[���̋ߕ��ʂ܂ł̋��� NearZ�l
#define FAR_VALUE				(2000.0f)						// �r���[�{�����[���̉����ʂ܂ł̋��� FarZ�l
#define VIEWING_ANGLE			(45.0f)							// ����p

// =====================================================================================================================================================================
//
// �R���X�g���N�^
//
// =====================================================================================================================================================================
CCamera::CCamera()
{
}

// =====================================================================================================================================================================
//
// �f�X�g���N�^
//
// =====================================================================================================================================================================
CCamera::~CCamera()
{
}
// =====================================================================================================================================================================
//
// ����������
//
// =====================================================================================================================================================================
void CCamera::Init(void)
{
	m_posV					= D3DXVECTOR3(0.0f, 80.0f, -150.0f);					// ���_
	m_posR					= D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// �����_( �Q�Ɠ_ )
	m_posVDest				= D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// �ړI�̎��_
	m_posRDest				= D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// �ړI�̒����_( �Q�Ɠ_ )
	m_vecU					= D3DXVECTOR3(0.0f, 1.0f, 0.0f);						// ������x�N�g��
	m_rot					= D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// ��]
	m_rotDest				= D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// �ړI�̉�]
	m_fDistance				= 0;													// ����
	m_RightStick_X			= 0;													// �E�X�e�B�b�N��X�̒l
	m_RightStick_Y			= 0;													// �E�X�e�B�b�N��Y�̒l
	m_posVOld				= D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// �ߋ��̎��_
	m_bSwitchingCameraMode	= false;												// �J�������[�h�̐؂�ւ��t���O
}

// =====================================================================================================================================================================
//
// �J�����̏I������
//
// =====================================================================================================================================================================
void CCamera::Uninit(void)
{
}

// =====================================================================================================================================================================
//
// �J�����̍X�V����
//
// =====================================================================================================================================================================
void CCamera::Update(void)
{
	// �ϐ�
	CKeyboard	*pKeyboard		= CManager::GetKeyboard();
	CPlayer		*pPlayer		= CManager::GetGame()->GetPlayer();
	CXinputGpad *pXinputGpad	= CManager::GetXinputGpad();

	// ����
	D3DXVECTOR3	fLength = m_posR - m_posV;
	m_fDistance = sqrtf(fLength.x * fLength.x + fLength.z * fLength.z);

	// ���X�e�B�b�N�̒l�̎擾
	pXinputGpad->GetRightStickValue(m_RightStick_X, m_RightStick_Y);
	// ���X�e�B�b�N��|�����Ƃ��̊p�x
	float fLeftStickAngle = atan2f(m_RightStick_X, m_RightStick_Y);
	// ���X�e�B�b�N��|�����Ƃ��̌���
	D3DXVECTOR2 LeftStickVec = D3DXVECTOR2((float)sin(fLeftStickAngle), (float)cos(fLeftStickAngle));

	// �Q�[�����[�h�̂Ƃ�
	if (CManager::GetMode() == CManager::GAME)
	{
		// === �J�����̃��[�h��3D�̂Ƃ� ===
		if (m_CameraMode == CAMERA_MODE_3D)
		{
			// ----- [ �E�X�e�B�b�N�ړ� ] -----
			// [ ����] ( �����_ ) ]
			if (m_RightStick_X > 0)
			{
				m_rot.y -= 0.03f;
			}
			// [ �E��] ( �����_ ) ]
			else if (m_RightStick_X < -0)												// �����l�ŏ����J�������X��
			{
				m_rot.y += 0.03f;
			}

			// ----- [ ���_��] ] -----
			// [ ����] ( �����_ ) ]
			if (pKeyboard->GetKeyboardPress(DIK_LEFT))
			{
				m_rot.y += 0.03f;
			}
			// [ �E��] ( �����_ ) ]
			else if (pKeyboard->GetKeyboardPress(DIK_RIGHT))
			{
				m_rot.y -= 0.03f;
			}
		}
		// === �J�����̃��[�h��2D�̂Ƃ� ===
		else if (m_CameraMode == CAMERA_MODE_2D)
		{
			if (pPlayer != NULL)
			{
				// ���_��2D���_��
				m_posV = pPlayer->GetPos() + D3DXVECTOR3(900.0f, 50.0f, 0.0f);
				m_rot.y = D3DX_PI / 2;
			}
		}

		// �J�����̃��[�h�ؑ�(2D, 3D)
		if (pKeyboard->GetKeyboardTrigger(DIK_C) || pXinputGpad->GetTriggerXinputGpad(CXinputGpad::XINPUT_RIGHT_SHOULDER))
		{
			//	�J�����ؑւ���
			CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_CHANGE);

			// ��񂾂��ʂ�
			if (m_bSwitchingCameraMode)
			{
				m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �J�����̉�]������

				if (pPlayer != NULL)
				{
					// ���_��3D���_��
					m_posV = pPlayer->GetPos() + D3DXVECTOR3(0.0f, 120.0f, -200.0f);
				}

				m_bSwitchingCameraMode = false;		// �J�������[�h��3D��
			}
			else
			{
				m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �J�����̉�]������
				m_bSwitchingCameraMode = true;		// �J�������[�h��2D��
			}
		}

	}
	// �J�����̃��[�h�ؑ�(�펞)
	SwitchingCameraMode();

	// ���[�h���Q�[���̂Ƃ�
	if (CManager::GetMode() == CManager::MODE::GAME)
	{
		// ���_�ƒ����_�̐ݒ�
		if (pPlayer != NULL)
		{
			// �ړI�̒����_�ݒ�
			m_posRDest.x = pPlayer->GetPos().x + sinf(pPlayer->GetRot().y) * DISTANCE_R;
			m_posRDest.y = pPlayer->GetPos().y + 50;
			m_posRDest.z = pPlayer->GetPos().z - cosf(pPlayer->GetRot().y) * DISTANCE_R;

			// �ړI�̎��_�ݒ�
			m_posVDest.x = pPlayer->GetPos().x + sinf(m_rot.y) * DISTANCE_V;
			m_posVDest.y = pPlayer->GetPos().y + 120;
			m_posVDest.z = pPlayer->GetPos().z - cosf(m_rot.y) * DISTANCE_V;

			// �����_�̒Ǐ]�ݒ�
			m_posR.x += (m_posRDest.x - m_posR.x)* 0.08f;
			m_posR.y += (m_posRDest.y - m_posR.y)* 0.08f;
			m_posR.z += (m_posRDest.z - m_posR.z)* 0.08f;

			if (m_CameraMode == CAMERA_MODE_2D)
			{
				// ���_�̒Ǐ]�ݒ�
				m_posV.x += (m_posVDest.x - m_posV.x) * 0.03f;
				m_posV.y += (m_posVDest.y - m_posV.y) * 0.03f;
				m_posV.z += (m_posVDest.z - m_posV.z) * 0.03f;
			}
			else if (m_CameraMode == CAMERA_MODE_3D)
			{
				// ���_�̒Ǐ]�ݒ�
				m_posV.x += (m_posVDest.x - m_posV.x) * 0.03f;
				m_posV.y += (m_posVDest.y - m_posV.y) * 0.03f;
				m_posV.z += (m_posVDest.z - m_posV.z) * 0.03f;
			}
		}
	}
	// ��]����������
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2;
	}
	if (m_rot.y < -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2;
	}

	CDebugProc::Print("\nCameraRot %f\n", m_rot.y);
}

// =====================================================================================================================================================================
//
// �J�����̐ݒ菈��
//
// =====================================================================================================================================================================
void CCamera::SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = *CManager::GetRenderer()->GetDevice();

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	// �ߕ��ʂ̏c�� = zn * tan(Y�����̎���p/2) * 2
	float nearH = NEAR_VALUE * (float)tan(D3DXToRadian(90) / 2.0f) * 70.0f;
	// �ߕ��ʂ̉��� = �ߕ��ʂ̏c�� * �A�X�y�N�g��
	float nearW = nearH * SCREEN_WIDTH / SCREEN_HEIGHT;

	// �J�������[�h�œ��e���@�ؑւ�
	switch (m_CameraMode)
	{
	case CCamera::CAMERA_MODE_3D:
		// �v���W�F�N�V�����}�g���b�N�X���쐬
		D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
									D3DXToRadian(VIEWING_ANGLE),							// ����p
									(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,				// �A�X�y�N�g��
									NEAR_VALUE,												// Near Z�l
									FAR_VALUE);												// Far Z�l
		break;

	case CCamera::CAMERA_MODE_2D:
		// �v���W�F�N�V�����}�g���b�N�X���쐬 ( ���s���e )
		D3DXMatrixOrthoLH(&m_mtxProjection,
							nearW,				// �r���[�{�����[���̉���
							nearH,				// �r���[�{�����[���̏c��
							NEAR_VALUE,			// �r���[�{�����[���̋ߕ��ʂ܂ł̋���
							FAR_VALUE);			// �r���[�{�����[���̉����ʂ܂ł̋���
		break;
	}

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);
	
	// �r���[�}�g���b�N�X���쐬
	D3DXMatrixLookAtLH(&m_mtxView,
						&m_posV,													// �J�����̎��_
						&m_posR,													// �J�����̒����_
						&m_vecU);													// �J�����̏�����x�N�g��

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}

// =====================================================================================================================================================================
//
// �J�����̏������W�ݒ�
//
// =====================================================================================================================================================================
void CCamera::SetCameraPosInit(void)
{
	m_CameraMode = CAMERA_MODE::CAMERA_MODE_3D;							// �J�����̃��[�h��3D��
	m_posV = D3DXVECTOR3(0.0f, 80.0f, -150.0f);							// ���_
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);								// ��]
	m_bSwitchingCameraMode = false;										// �J�������[�h�̐؂�ւ�
}

// =====================================================================================================================================================================
//
// �v���C���[�����񂾂Ƃ��̃J�����̈ʒu
//
// =====================================================================================================================================================================
void CCamera::SetDeadPlayerCameraPos(D3DXVECTOR3 pos)
{
	// ���_��3D���_��
	m_posV = pos + D3DXVECTOR3(0.0f, 120.0f, -200.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);								// ��]
}

// =====================================================================================================================================================================
//
// �J�������[�h�̐؂�ւ�
//
// =====================================================================================================================================================================
void CCamera::SwitchingCameraMode(void)
{
	if (m_bSwitchingCameraMode)
	{
		// �J�����̃��[�h��2D��
		m_CameraMode = CAMERA_MODE_2D;
	}
	else
	{
		// �J�����̃��[�h��3D��
		m_CameraMode = CAMERA_MODE_3D;
	}
}