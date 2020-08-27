//=============================================================================
// �J�������� [camera.cpp]
//=============================================================================
#include "camera.h"
#include "inputKeyboard.h"
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"
#include "basemode.h"
#include "Player.h"
#include "Scene.h"
#include "mouse.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_LENGTH (-100) //�J�����̋���
#define CAMERA_MOVE_SPEED (10.0f)
#define CAMERA_ROTATION_SPEED (0.05f)
#define CAMETA_POSR_OFFSET (D3DXVECTOR3(0.0f,200.0f,0.0f))

#define DEFAULT_DISTANCE (850.0f)
#define DEFAULT_CAMERA_ROTATION (D3DXVECTOR3(0.17f,0.0f,0.0f))

#define CAMERA_LENGTH_NEAR (10.0f)
#define CAMERA_LENGTH_FAR (3000.0f)
//=============================================================================
// �J�����̏���������
//=============================================================================
void CCamera::InitCamera(void)
{
	// �J�������v���C��Ǐ]�ɂ���
	m_CameraFollowingType = CAMERA_FOLLOWING_TYPE_PLAYER;

	m_posCameraEndLine = ZeroVector3;
	m_fNear = CAMERA_LENGTH_NEAR;
	m_fFar = CAMERA_LENGTH_FAR;
	m_bStopMove = false;

	//�J����������
	ResetCamera();
}
//=============================================================================
// �J�����̏I������
//=============================================================================
void CCamera::UninitCamera(void)
{
}
//=============================================================================
// �J�����̍X�V����
//=============================================================================
void CCamera::UpdateCamera(void)
{
#ifdef _DEBUG

	//�J�����̃f�o�b�O�R�}���h
	DebugCommand();

#endif // _DEBUG

	// �J�����̒Ǐ]��ނɂ���ăJ�����̓���������ς���
	switch (m_CameraFollowingType)
	{
	case CCamera::CAMERA_FOLLOWING_TYPE_PLAYER:
		// �L�����N�^�[�Ǐ]�J����
		CharacterFollowingMoveCamera();
		break;
	case CCamera::CAMERA_FOLLOWING_TYPE_MOUSE:
		// �}�E�X�ɂ��J��������
		MouseMoveCamera();
		break;
	}
}
//=============================================================================
// �J�����̐ݒ菈��
//=============================================================================
void CCamera::SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		m_fNear,
		m_fFar);

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	// �r���[�}�g���b�N�X���쐬
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posV,
		&m_posR,
		&m_vecV);

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}
//=============================================================================
//�J�����̈ړ��֐�
//=============================================================================
void CCamera::SetMoveCamera(float Cm_rot)
{
	m_move.x += sinf(-D3DX_PI* Cm_rot + m_rot.y) * 5;
	m_move.z += cosf(-D3DX_PI* Cm_rot + m_rot.y) * 5;
}

//=============================================================================
//�f�o�b�O�R�}���h
//=============================================================================
void CCamera::DebugCommand()
{
	CKeyboard *key = CManager::GetInputKeyboard();

	//�g��������
	CDebugProc::Print("---------Camera Debug Command----------\n");
	CDebugProc::Print("[Ctrl] + [1] : �J�����ؑ� : CameraMode >> [%d]\n", m_CameraFollowingType);
	CDebugProc::Print("[Ctrl] + [��] or [Ctrl] + [��] : �J������������ : Distance>>[%f]\n", m_fDistance);

	CDebugProc::Print("m_posV %.1f %.1f %.1f \n", m_posV.x, m_posV.y, m_posV.z);
	CDebugProc::Print("m_posR %.1f %.1f %.1f \n", m_posR.x, m_posR.y, m_posR.z);
	CDebugProc::Print("m_rot  %.1f %.1f %.1f \n", m_rot.x, m_rot.y, m_rot.z);
	CDebugProc::Print("bCameraStop >> %d",m_bStopMove);


	if (key->GetKeyboardPress(DIK_LCONTROL) || key->GetKeyboardPress(DIK_RCONTROL))
	{
		if (key->GetKeyboardTrigger(DIK_1))
		{
			//�J�����؂�ւ�
			m_CameraFollowingType += 1;

			if (m_CameraFollowingType >= CAMERA_FOLLOWING_TYPE_MAX)
			{
				m_CameraFollowingType = CAMERA_FOLLOWING_TYPE_PLAYER;
			}
		}
		if (key->GetKeyboardPress(DIK_DOWN))
		{
			//�J��������++
			m_fDistance += 5.0f;
		}
		if (key->GetKeyboardPress(DIK_UP))
		{
			//�J����--
			m_fDistance -= 5.0f;
		}
	}

}

//=============================================================================
//�L�����N�^�[�Ǐ]�J����
//=============================================================================
void CCamera::CharacterFollowingMoveCamera()
{
	//��]�̐��l�w��
	CHossoLibrary::CalcRotation(m_rot.x);
	CHossoLibrary::CalcRotation(m_rot.y);

	//�J�����̈ړ��Ƃ߂邩�ǂ���
	if (!m_bStopMove)
	{
		//�Ǐ]����
		CBaseMode *pBaseMode = CManager::GetBaseMode();

		//nullcheck
		if (pBaseMode)
		{
			//�v���C���[�̃|�C���^�擾
			CPlayer *pPlayer = pBaseMode->GetPlayer();

			//nullcheck
			if (pPlayer)
			{
				//���W�擾
				//�J�����ŏI�ړI�n
				m_posRDest.x = pPlayer->GetPosition().x;
				m_posRDest.y = CAMETA_POSR_OFFSET.y;

				//�J�����̃G���h���C��
				if (m_posCameraEndLine.x > pPlayer->GetPosition().x)
				{
					m_posRDest.x = m_posCameraEndLine.x;
				}
				else
				{
					//�J�����̃G���h���C���ݒ�
					m_posCameraEndLine.x = m_posRDest.x;
					//m_posCameraEndLine.y = m_posRDest.y;

				}
			}
		}
	}

	//�J������x��0�ȉ��ɂȂ�Ȃ��悤�ɂ���
	CHossoLibrary::RangeLimit_Equal(m_posRDest.x, 0.0f, 99999.0f);

	//���_�̖ړI�n�̌v�Z
	m_posVDest.x = m_posRDest.x - sinf(m_rot.y) * cosf(m_rot.x) * m_fDistance;
	m_posVDest.y = m_posRDest.y + sinf(m_rot.x)	* m_fDistance;
	m_posVDest.z = m_posRDest.z - cosf(m_rot.y) * cosf(m_rot.x) * m_fDistance;

	//���_�̈ړ�
	m_posV.x += (m_posVDest.x - m_posV.x) * 0.08f;
	m_posV.y += (m_posVDest.y - m_posV.y) * 0.08f;
	m_posV.z += (m_posVDest.z - m_posV.z) * 0.08f;

	//�����_�̈ړ�
	m_posR.x += (m_posRDest.x - m_posR.x) * 0.08f;
	m_posR.y += (m_posRDest.y - m_posR.y) * 0.08f;
	m_posR.z += (m_posRDest.z - m_posR.z) * 0.08f;

	//������R
	m_move.x += (0 - m_move.x)*0.3f;
	m_move.y += (0 - m_move.y)*0.3f;
	m_move.z += (0 - m_move.z)*0.3f;
	m_posRDest += m_move;
}

//=============================================================================
//�}�E�X�ɂ��J�����̑���
//=============================================================================
void CCamera::MouseMoveCamera()
{
	// �L�[�{�[�h�̎擾
	CKeyboard *pKeyboard = CManager::GetInputKeyboard();
	CMouse *pMouse = CManager::GetMouse();

	D3DXVECTOR2 NewRotation = ZeroVector2;

	static D3DXVECTOR2 MousePosCurrent = ZeroVector2;
	static D3DXVECTOR2 MousePosOld = ZeroVector2;
	static D3DXVECTOR2 MouseRot = ZeroVector2;

	// �}�E�X�̍��W�ێ�
	MousePosCurrent = pMouse->GetMousePos();

	//�}�E�X���͂���ĂȂ���
	if (pMouse->GetPress(1) == false)
	{
		// �O��̈ʒu�̐ݒ�
		MousePosOld = MousePosCurrent;
	}
	//�}�E�X���͂���Ă���Ƃ�
	else
	{
		// ����]
		NewRotation.y = (MousePosCurrent.x - MousePosOld.x) / (D3DX_PI*2.0f) *0.03f + MouseRot.y;
		m_rotDest.y = NewRotation.y;

		// ��]�ʂ�360�x�Ȃ��ɒ���
		CHossoLibrary::CalcRotation(m_rotDest.y);

		// �s�b�`���[��]
		NewRotation.x = (MousePosCurrent.y - MousePosOld.y) / (D3DX_PI*2.0f) *0.03f + MouseRot.x;

		// ��]��90�x�����ɗ}����
		if (NewRotation.x >= D3DX_PI*0.49f)
		{
			NewRotation.x = D3DX_PI*0.49f;
			MousePosOld = MousePosCurrent;
			MouseRot.y = m_rotDest.y;
			MouseRot.x = m_rotDest.x;

		}
		else if (NewRotation.x <= -D3DX_PI*0.49f)
		{
			NewRotation.x = -D3DX_PI*0.49f;
			MousePosOld = MousePosCurrent;
			MouseRot.y = m_rotDest.y;
			MouseRot.x = m_rotDest.x;

		}
		m_rotDest.x = NewRotation.x;
	}

	if (pMouse->GetRelease(1))
	{
		MouseRot.y = m_rotDest.y;
		MouseRot.x = m_rotDest.x;
	}

	//�����_��]
	if (pKeyboard->GetKeyboardPress(DIK_2))
	{
		m_rotDest.z += 0.01f;
	}
	else if (pKeyboard->GetKeyboardPress(DIK_X))
	{
		m_rotDest.z -= 0.01f;
	}

	// �J�����̉�]��90�x�����ɗ}����
	if (m_rotDest.x >= D3DX_PI*0.49f)
	{
		m_rotDest.x = D3DX_PI*0.49f;
	}
	else if (m_rotDest.x <= -D3DX_PI*0.49f)
	{
		m_rotDest.x = -D3DX_PI*0.49f;
	}
	// ��]�ʂ�360�x�Ȃ��ɒ���
	CHossoLibrary::CalcRotation(m_rotDest.y);

	//[W]�L�[����������
	if (pKeyboard->GetKeyboardPress(DIK_W))
	{
		//��
		m_posRDest.x += sinf(D3DX_PI * 0.0f + m_rotDest.y) * CAMERA_MOVE_SPEED;
		m_posRDest.z += cosf(D3DX_PI * 0.0f + m_rotDest.y) * CAMERA_MOVE_SPEED;
	}
	//[S]�L�[����������
	if (pKeyboard->GetKeyboardPress(DIK_S))
	{
		//�O
		m_posRDest.x += sinf(D3DX_PI * 1.0f + m_rotDest.y) * CAMERA_MOVE_SPEED;
		m_posRDest.z += cosf(D3DX_PI * 1.0f + m_rotDest.y) * CAMERA_MOVE_SPEED;
	}
	//[A]�L�[����������
	if (pKeyboard->GetKeyboardPress(DIK_A))
	{
		//��
		m_posRDest.x += sinf(-D3DX_PI * 0.5f + m_rotDest.y) * CAMERA_MOVE_SPEED;
		m_posRDest.z += cosf(-D3DX_PI * 0.5f + m_rotDest.y) * CAMERA_MOVE_SPEED;
	}
	//[D]�L�[����������
	if (pKeyboard->GetKeyboardPress(DIK_D))
	{
		//�E
		m_posRDest.x += sinf(D3DX_PI * 0.5f + m_rotDest.y) * CAMERA_MOVE_SPEED;
		m_posRDest.z += cosf(D3DX_PI * 0.5f + m_rotDest.y) * CAMERA_MOVE_SPEED;
	}

	//[1]�L�[����������
	else if (pKeyboard->GetKeyboardPress(DIK_1))
	{
		//��Ɉړ�
		m_posRDest.x += sinf(D3DX_PI * 0.0f) * CAMERA_MOVE_SPEED;
		m_posRDest.y += cosf(D3DX_PI * 0.0f) * CAMERA_MOVE_SPEED;
	}
	//[3]�L�[����������
	else if (pKeyboard->GetKeyboardPress(DIK_3))
	{
		//���Ɉړ�
		m_posRDest.x += sinf(D3DX_PI * 1.0f) * CAMERA_MOVE_SPEED;
		m_posRDest.y += cosf(D3DX_PI * 1.0f) * CAMERA_MOVE_SPEED;
	}

	//��]��
	m_rot = m_rotDest;

	// ���_�̍s����̍X�V
	m_posVDest.x = m_posR.x - cosf(m_rot.x) * sinf(m_rot.y) * m_fDistance;
	m_posVDest.y = m_posR.y + sinf(m_rot.x) * m_fDistance;
	m_posVDest.z = m_posR.z - cosf(m_rot.x) * cosf(m_rot.y) * m_fDistance;

	// ���_�̍X�V
	m_posV += (m_posVDest - m_posV) * 0.2f;

	// �����_�̍X�V
	m_posR += (m_posRDest - m_posR) * 0.2f;
}

//-----------------------------------------------------------------------------
//�����_��ݒ�
//-----------------------------------------------------------------------------
void CCamera::SetPosR(D3DXVECTOR3 posR)
{
	m_posCameraEndLine = m_posR = m_posRDest = posR;

	m_posV.x = m_posVDest.x = m_posRDest.x - sinf(m_rot.y) * cosf(m_rot.x) * m_fDistance;
	m_posV.y = m_posVDest.y = m_posRDest.y + sinf(m_rot.x)	* m_fDistance;
	m_posV.z = m_posVDest.z = m_posRDest.z - cosf(m_rot.y) * cosf(m_rot.x) * m_fDistance;
}

//-----------------------------------------------------------------------------
//�J�������������W�ɐݒ�
//-----------------------------------------------------------------------------
void CCamera::ResetCamera()
{
	//�������W��
	m_rotDest = m_rot = DEFAULT_CAMERA_ROTATION;
	m_fDistance = DEFAULT_DISTANCE;
	m_posCameraEndLine = m_posR = m_posRDest = ZeroVector3;

	m_posV.x = m_posVDest.x = m_posRDest.x - sinf(m_rot.y) * cosf(m_rot.x) * m_fDistance;
	m_posV.y = m_posVDest.y = m_posRDest.y + sinf(m_rot.x)	* m_fDistance;
	m_posV.z = m_posVDest.z = m_posRDest.z - cosf(m_rot.y) * cosf(m_rot.x) * m_fDistance;

	m_vecV = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �J�������v���C��Ǐ]�ɂ���
	m_CameraFollowingType = CAMERA_FOLLOWING_TYPE_PLAYER;
	m_bStopMove = false;
}
//-----------------------------------------------------------------------------
//�J�������W�ݒ� �p�x�Ƌ�������ɎZ�o
//-----------------------------------------------------------------------------
void CCamera::SetCameraPosfromDistance(D3DXVECTOR3 posR, D3DXVECTOR3 rot, float fDistance)
{
	//�������W��
	m_rotDest = m_rot = rot;
	m_fDistance = fDistance;
	m_posCameraEndLine = m_posR = m_posRDest = posR;

	m_posV.x = m_posVDest.x = m_posRDest.x - sinf(m_rot.y) * cosf(m_rot.x) * m_fDistance;
	m_posV.y = m_posVDest.y = m_posRDest.y + sinf(m_rot.x)	* m_fDistance;
	m_posV.z = m_posVDest.z = m_posRDest.z - cosf(m_rot.y) * cosf(m_rot.x) * m_fDistance;

	m_vecV = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �J�������v���C��Ǐ]�ɂ���
	m_CameraFollowingType = CAMERA_FOLLOWING_TYPE_PLAYER;
}

//-----------------------------------------------------------------------------
//�J�������W�ݒ�
//-----------------------------------------------------------------------------
void CCamera::SetCameraPos(D3DXVECTOR3 posR, D3DXVECTOR3 posV)
{
	//���i�[
	m_posCameraEndLine = m_posR = m_posRDest = posR;
	m_posV = m_posVDest = posV;

	//�J�����̎��_�ƒ����_����p�x�Ƌ��������߂�
	D3DXVECTOR3	Length = m_posV - m_posR;																						//PosR��PosV�̍��W�̍�
	m_rot = m_rotDest = D3DXVECTOR3(atan2f(Length.y, Length.z), atan2f(-Length.x, -Length.z), atan2f(Length.x, Length.z));		//�����p�x�����߂�
	m_fDistance = (float)sqrt((Length.y * Length.y + Length.z * Length.z) + Length.x * Length.x);								//���_�ƒ����_�̋���
}