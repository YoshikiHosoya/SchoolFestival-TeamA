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
//=============================================================================
// �J�����̏���������
//=============================================================================
void CCamera::InitCamera(void)
{
	posVDest = posV = D3DXVECTOR3(0.0f, 500.0f, 330.0f);

	posRDest = posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vecV = D3DXVECTOR3(0.0f,1.0f,0.0f);
	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 diff = (posV-posR);
	//fDistance = sqrtf(diff.x*diff.x + diff.z*diff.z);
	fDistance = 300;
	move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	rot = D3DXVECTOR3(0.1f, 0.0f, 0.0f);
	//rot  = D3DXVECTOR3(atan2f(diff.y, diff.z),atan2f(diff.x, diff.z),atan2f(diff.x,diff.y));
	m_bCameraMode = false;
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


	//�J�����̏�ԂŃJ�����̓���������ς���
	m_bCameraMode ?
		MouseMoveCamera() :
		CharacterFollowingMoveCamera();
}
//=============================================================================
// �J�����̐ݒ菈��
//=============================================================================
void CCamera::SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH(&mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		10000.0f);

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &mtxProjection);

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxView);

	// �r���[�}�g���b�N�X���쐬
	D3DXMatrixLookAtLH(&mtxView,
		&posV,
		&posR,
		&vecV);

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &mtxView);
}
//=============================================================================
//�J�����̈ړ��֐�
//=============================================================================
void CCamera::SetMoveCamera(float Crot)
{
	move.x += sinf(-D3DX_PI* Crot + rot.y) * 5;
	move.z += cosf(-D3DX_PI* Crot + rot.y) * 5;
}

//=============================================================================
//�f�o�b�O�R�}���h
//=============================================================================
void CCamera::DebugCommand()
{
	CKeyboard *key = CManager::GetInputKeyboard();

	//�g��������
	CDebugProc::Print("---------Camera Debug Command----------\n");
	CDebugProc::Print("[Ctrl] + [1] : �J�����ؑ� : CameraMode >> [%d]\n",m_bCameraMode);
	CDebugProc::Print("[Ctrl] + [2] or [Ctrl] + [3] : �J������������ : Distance>>[%f]\n",fDistance);



	if (key->GetKeyboardPress(DIK_LCONTROL))
	{
		if (key->GetKeyboardTrigger(DIK_1))
		{
			//�J�����؂�ւ�
			m_bCameraMode ^= 1;
		}
		if (key->GetKeyboardPress(DIK_2))
		{
			fDistance += 5.0f;
			//�J�����؂�ւ�
		}
		if (key->GetKeyboardPress(DIK_3))
		{
			//�J�����؂�ւ�
			fDistance -= 5.0f;
		}
	}

}

//=============================================================================
//�L�����N�^�[�Ǐ]�J����
//=============================================================================
void CCamera::CharacterFollowingMoveCamera()
{
#ifdef _DEBUG
	CKeyboard *key;
	key = CManager::GetInputKeyboard();
	//�J�����̉�]
	if (key->GetKeyboardPress(DIK_UP))
	{
		rot.x += 0.08f;
	}
	if (key->GetKeyboardPress(DIK_DOWN))
	{
		rot.x -= 0.08f;
	}
	if (key->GetKeyboardPress(DIK_RIGHT))
	{
		rot.y += 0.08f;
	}
	if (key->GetKeyboardPress(DIK_LEFT))
	{
		rot.y -= 0.08f;
	}
#endif

	//��]�̐��l�w��
	if (rot.y > D3DX_PI)
	{
		rot.y += -D3DX_PI * 2;
	}
	if (rot.y < -D3DX_PI)
	{
		rot.y += D3DX_PI * 2;
	}
	if (rot.x > D3DX_PI*0.5f)
	{
		rot.x = D3DX_PI*0.5f;
	}
	if (rot.x < -D3DX_PI*0.5f)
	{
		rot.x = -D3DX_PI*0.5f;
	}
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
			pos = pPlayer->GetPosition();
		}
	}

	//���_�̖ړI�n�̌v�Z
	posVDest.x = pos.x - sinf(rot.y)*cosf(rot.x)*fDistance;
	posVDest.y = pos.y + sinf(rot.x)			*fDistance;
	posVDest.z = pos.z - cosf(rot.y)*cosf(rot.x)*fDistance;

	//���_�̈ړ�
	posV.x += (posVDest.x - posV.x) * 0.08f;
	posV.y += (posVDest.y - posV.y) * 0.08f;
	posV.z += (posVDest.z - posV.z) * 0.08f;

	//�J�����ŏI�ړI�n�̌v�Z
	posRDest.x = pos.x;
	posRDest.y = pos.y;
	posRDest.z = pos.z;

	posR.x += (posRDest.x - posR.x) * 0.08f;
	posR.y += (posRDest.y - posR.y) * 0.08f;
	posR.z += (posRDest.z - posR.z) * 0.08f;

	//������R
	move.x += (0 - move.x)*0.3f;
	move.y += (0 - move.y)*0.3f;
	move.z += (0 - move.z)*0.3f;
	pos += move;

	CDebugProc::Print("posV.x:%0.2f\nposV.y:%0.2f\nposV.z:%0.2f\n\n", posV.x, posV.y, posV.z);
	CDebugProc::Print("posR.x:%0.2f\nposR.y:%0.2f\nposR.z:%0.2f\n", posR.x, posR.y, posR.z);
	CDebugProc::Print("rot.x:%0.2f\nrot.y:%0.2f\nrot.z:%0.2f\n", rot.x, rot.y, rot.z);

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

	static D3DXVECTOR2 MousePosCurrent;
	static D3DXVECTOR2 MousePosOld;
	static D3DXVECTOR2 MouseRot;

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
		rotDest.y = NewRotation.y;

		// ��]�ʂ�360�x�Ȃ��ɒ���
		CHossoLibrary::CalcRotation(rotDest.y);

		// �s�b�`���[��]
		NewRotation.x = (MousePosCurrent.y - MousePosOld.y) / (D3DX_PI*2.0f) *0.03f + MouseRot.x;

		// ��]��90�x�����ɗ}����
		if (NewRotation.x >= D3DX_PI*0.49f)
		{
			NewRotation.x = D3DX_PI*0.49f;
			MousePosOld = MousePosCurrent;
			MouseRot.y = rotDest.y;
			MouseRot.x = rotDest.x;

		}
		else if (NewRotation.x <= -D3DX_PI*0.49f)
		{
			NewRotation.x = -D3DX_PI*0.49f;
			MousePosOld = MousePosCurrent;
			MouseRot.y = rotDest.y;
			MouseRot.x = rotDest.x;

		}
		rotDest.x = NewRotation.x;
	}

	if (pMouse->GetRelease(1))
	{
		MouseRot.y = rotDest.y;
		MouseRot.x = rotDest.x;
	}

	//�����_��]
	if (pKeyboard->GetKeyboardPress(DIK_2))
	{
		rotDest.z += 0.01f;
	}
	else if (pKeyboard->GetKeyboardPress(DIK_X))
	{
		rotDest.z -= 0.01f;
	}

	// �J�����̉�]��90�x�����ɗ}����
	if (rotDest.x >= D3DX_PI*0.49f)
	{
		rotDest.x = D3DX_PI*0.49f;
	}
	else if (rotDest.x <= -D3DX_PI*0.49f)
	{
		rotDest.x = -D3DX_PI*0.49f;
	}
	// ��]�ʂ�360�x�Ȃ��ɒ���
	CHossoLibrary::CalcRotation(rotDest.y);


	//[W]�L�[����������
	if (pKeyboard->GetKeyboardPress(DIK_W))
	{
		//��
		posRDest.x += sinf(D3DX_PI * 0.0f + rotDest.y) * CAMERA_MOVE_SPEED;
		posRDest.z += cosf(D3DX_PI * 0.0f + rotDest.y) * CAMERA_MOVE_SPEED;
	}
	//[S]�L�[����������
	if (pKeyboard->GetKeyboardPress(DIK_S))
	{
		//�O
		posRDest.x += sinf(D3DX_PI * 1.0f + rotDest.y) * CAMERA_MOVE_SPEED;
		posRDest.z += cosf(D3DX_PI * 1.0f + rotDest.y) * CAMERA_MOVE_SPEED;
	}
	//[A]�L�[����������
	if (pKeyboard->GetKeyboardPress(DIK_A))
	{
		//��
		posRDest.x += sinf(-D3DX_PI * 0.5f + rotDest.y) * CAMERA_MOVE_SPEED;
		posRDest.z += cosf(-D3DX_PI * 0.5f + rotDest.y) * CAMERA_MOVE_SPEED;
	}
	//[D]�L�[����������
	if (pKeyboard->GetKeyboardPress(DIK_D))
	{
		//�E
		posRDest.x += sinf(D3DX_PI * 0.5f + rotDest.y) * CAMERA_MOVE_SPEED;
		posRDest.z += cosf(D3DX_PI * 0.5f + rotDest.y) * CAMERA_MOVE_SPEED;
	}

	//[1]�L�[����������
	else if (pKeyboard->GetKeyboardPress(DIK_1))
	{
		//��Ɉړ�
		posRDest.x += sinf(D3DX_PI * 0.0f) * CAMERA_MOVE_SPEED;
		posRDest.y += cosf(D3DX_PI * 0.0f) * CAMERA_MOVE_SPEED;
	}
	//[3]�L�[����������
	else if (pKeyboard->GetKeyboardPress(DIK_3))
	{
		//���Ɉړ�
		posRDest.x += sinf(D3DX_PI * 1.0f) * CAMERA_MOVE_SPEED;
		posRDest.y += cosf(D3DX_PI * 1.0f) * CAMERA_MOVE_SPEED;
	}

	//��]��
	rot = rotDest;

	// ���_�̍s����̍X�V
	posVDest.x = posR.x - cosf(rot.x) * sinf(rot.y) * fDistance;
	posVDest.y = posR.y + sinf(rot.x) * fDistance;
	posVDest.z = posR.z - cosf(rot.x) * cosf(rot.y) * fDistance;

	// ���_�̍X�V
	posV += (posVDest - posV) * 0.2f;


	// �����_�̍X�V
	posR += (posRDest - posR) * 0.2f;


}