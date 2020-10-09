//-----------------------------------------------------------------------------
//
// �J�������� [Camera.cpp]
// Author : Yoshiki Hosoya
//
//-----------------------------------------------------------------------------
#include "camera.h"
#include "manager.h"
#include "renderer.h"
#include "keyboard.h"
#include "game.h"
#include "player_3D.h"
#include "mouse.h"
#include "collision.h"
#include "model_object.h"
#include "Map.h"
//-----------------------------------------------------------------------------
// �}�N����`
//-----------------------------------------------------------------------------
#define CAMERA_MOVE_SPEED			(10.0f)			//�J�����ړ����x
#define CAMERA_HORIZON_ROTATION		(0.05f)			//�J�����̉���]
#define CAMERA_VERTICAL_ROTATION	(0.02f)			//�J�����̏c��]

#define DEFAULT_DISTANCE (850.0f)
#define DEFAULT_CAMERA_ROTATION (D3DXVECTOR3(0.17f,0.0f,0.0f))

#define CAMERA_LENGTH_NEAR			(10.0f)			//�J�����̌����鋗���i�߁j
#define CAMERA_LENGTH_FAR			(5000.0f)		//�J�����̌����鋗���i���j


//-----------------------------------------------------------------------------
// �ÓI�����o�ϐ��錾
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//�R���X�g���N�^
//-----------------------------------------------------------------------------
CCamera::CCamera()
{
	//������
	m_posR = ZeroVector3;
	m_posV = ZeroVector3;
	m_posVOld = ZeroVector3;
	m_posRDest = ZeroVector3;
	m_posVDest = ZeroVector3;
	m_rot = ZeroVector3;
	m_rotDest = ZeroVector3;
	m_move = ZeroVector3;
	m_fDistance = 0.0f;
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_pCollision = nullptr;
	m_CameraState = CCamera::CAMERA_FIXED;
	m_MousePosCurrent = ZeroVector2;
	m_MousePosOld = ZeroVector2;
	m_MouseRotSave = ZeroVector2;

	ResetCamera();

}
//-----------------------------------------------------------------------------
//�f�X�g���N�^
//-----------------------------------------------------------------------------
CCamera::~CCamera()
{
	m_pCollision.reset();
}
//-----------------------------------------------------------------------------
//������
//-----------------------------------------------------------------------------
void CCamera::Init(void)
{
	//�}�g���b�N�X�v�Z
	CHossoLibrary::CalcMatrix(&m_mtxWorld, m_posV, m_rot);

	//�R���W��������
	m_pCollision = CCollision::Create(&m_mtxWorld, CCollision::COLLISION_CAMERA);

	//�R���W�������ݒ�
	m_pCollision->SetCollisionInfo(10.0f, 10.0f);

	//�����̋���������
	m_fDefaultDistace = 0.0f;

}
//-----------------------------------------------------------------------------
//�I��
//-----------------------------------------------------------------------------
void CCamera::Uninit(void)
{
}
//-----------------------------------------------------------------------------
//�X�V
//-----------------------------------------------------------------------------
void CCamera::Update(void)
{
	//1F�O�̍��W�ۑ�
	m_posVOld = m_posV;

	switch (m_CameraState)
	{

		//�Q�[����
	case CCamera::CAMERA_PLAYER_FOLLOWING:
		//�����̋����ɏk�߂�
		m_fDistance += (m_fDefaultDistace - m_fDistance) * 0.03f;

		//�J�����ړ�
		MoveCameraGame();

		//�J������]
		RotCameraGame();

		if (m_fDistance <= 700.0f)
		{

		}
		break;

	case CCamera::CAMERA_DEBUG:
		//�}�E�X����
		MouseCameraOperation();

		//�J�����ړ�
		MoveCameraDebug();

		//�J������]
		RotCameraDebug();
		break;
	}
	//�}�g���b�N�X�v�Z
	CHossoLibrary::CalcMatrix(&m_mtxWorld, m_posV, m_rot);

}
//-----------------------------------------------------------------------------
//�ݒ菈��
//-----------------------------------------------------------------------------
void CCamera::SetCamera(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH(
		&m_mtxProjection,
		D3DXToRadian(45.0f),	//����p
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,		//�A�X�y�N�g��
		CAMERA_LENGTH_NEAR,								//NearZ�l
		CAMERA_LENGTH_FAR);								//FarZ�l

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_mtxView, &m_posV, &m_posR, &m_vecU);

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

}

//-----------------------------------------------------------------------------
//�J�������
//-----------------------------------------------------------------------------
void CCamera::ShowCameraInfo()
{
#ifdef _DEBUG

	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	if (ImGui::CollapsingHeader("CameraInfo"))
	{
		ImGui::InputFloat3("PosV", m_posV);
		ImGui::InputFloat3("PosR", m_posR);
		ImGui::InputFloat3("Rot", m_rot);
		ImGui::InputFloat3("RotDest", m_rotDest);
		ImGui::InputFloat("distance", &m_fDistance, 10.0f, 10.0f);

		ImGui::Text("ViewVec %.2f %.2f %.2f", m_mtxView._31, m_mtxView._32, m_mtxView._33);
	}
#endif //DEBUG
}

//-----------------------------------------------------------------------------
//�ړ�����
//-----------------------------------------------------------------------------
void CCamera::MoveCameraDebug(void)
{
	CKeyboard *pKeyboard = CManager::GetKeyboard();

	//[W]�L�[����������
	if (pKeyboard->GetPress(DIK_W))
	{
		//��
		m_posRDest.x += sinf(D3DX_PI * 0.0f + m_rotDest.y) * CAMERA_MOVE_SPEED;
		m_posRDest.z += cosf(D3DX_PI * 0.0f + m_rotDest.y) * CAMERA_MOVE_SPEED;
	}
	//[S]�L�[����������
	if (pKeyboard->GetPress(DIK_S))
	{
		//�O
		m_posRDest.x += sinf(D3DX_PI * 1.0f + m_rotDest.y) * CAMERA_MOVE_SPEED;
		m_posRDest.z += cosf(D3DX_PI * 1.0f + m_rotDest.y) * CAMERA_MOVE_SPEED;
	}
	//[A]�L�[����������
	if (pKeyboard->GetPress(DIK_A))
	{
		//��
		m_posRDest.x += sinf(-D3DX_PI * 0.5f + m_rotDest.y) * CAMERA_MOVE_SPEED;
		m_posRDest.z += cosf(-D3DX_PI * 0.5f + m_rotDest.y) * CAMERA_MOVE_SPEED;
	}
	//[D]�L�[����������
	if (pKeyboard->GetPress(DIK_D))
	{
		//�E
		m_posRDest.x += sinf(D3DX_PI * 0.5f + m_rotDest.y) * CAMERA_MOVE_SPEED;
		m_posRDest.z += cosf(D3DX_PI * 0.5f + m_rotDest.y) * CAMERA_MOVE_SPEED;
	}

	//[1]�L�[����������
	else if (pKeyboard->GetPress(DIK_1))
	{
		//��Ɉړ�
		m_posRDest.x += sinf(D3DX_PI * 0.0f) * CAMERA_MOVE_SPEED;
		m_posRDest.y += cosf(D3DX_PI * 0.0f) * CAMERA_MOVE_SPEED;
	}
	//[3]�L�[����������
	else if (pKeyboard->GetPress(DIK_3))
	{
		//���Ɉړ�
		m_posRDest.x += sinf(D3DX_PI * 1.0f) * CAMERA_MOVE_SPEED;
		m_posRDest.y += cosf(D3DX_PI * 1.0f) * CAMERA_MOVE_SPEED;
	}
}
//-----------------------------------------------------------------------------
//��]����
//-----------------------------------------------------------------------------
void CCamera::RotCameraDebug(void)
{
	//3.14�͈̔͂ɗ}����
	CHossoLibrary::CalcRotation(m_rotDest.y);

	//��]��
	m_rot = m_rotDest;

	/*---------------------------------------------
	//	���_�̍X�V
	---------------------------------------------*/
	// ���_�̍s����̍X�V
	m_posVDest.x = m_posR.x - cosf(m_rot.x) * sinf(m_rot.y) * m_fDistance;
	m_posVDest.y = m_posR.y + sinf(m_rot.x) * m_fDistance;
	m_posVDest.z = m_posR.z - cosf(m_rot.x) * cosf(m_rot.y) * m_fDistance;

	// ���_�̍X�V
	m_posV += (m_posVDest - m_posV) * 0.2f;

	/*---------------------------------------------
	//	�����_�̍X�V
	---------------------------------------------*/
	// �����_�̍s����̍X�V
	m_posRDest.x;
	m_posRDest.y;
	m_posRDest.z;

	// �����_�̍X�V
	m_posR += (m_posRDest - m_posR) * 0.2f;
}

//-----------------------------------------------------------------------------
//�J�����̑���
//-----------------------------------------------------------------------------
void CCamera::MouseCameraOperation()
{
	// �L�[�{�[�h�̎擾
	CKeyboard *pKeyboard = CManager::GetKeyboard();
	CMouse *pMouse = CManager::GetMouse();

	D3DXVECTOR2 NewRotation = ZeroVector2;

	// �}�E�X�̍��W�ێ�
	m_MousePosCurrent = pMouse->GetMousePos();

	//�}�E�X���͂���ĂȂ���
	if (pMouse->GetPress(1) == false)
	{
		// �O��̈ʒu�̐ݒ�
		m_MousePosOld = m_MousePosCurrent;
	}
	//�}�E�X���͂���Ă���Ƃ�
	else
	{
		// ����]
		NewRotation.y = (m_MousePosCurrent.x - m_MousePosOld.x) / (D3DX_PI*2.0f) *0.03f + m_MouseRotSave.y;
		m_rotDest.y = NewRotation.y;

		// ��]�ʂ�360�x�Ȃ��ɒ���
		CHossoLibrary::CalcRotation(m_rotDest.y);

		// �s�b�`���[��]
		NewRotation.x = (m_MousePosCurrent.y - m_MousePosOld.y) / (D3DX_PI*2.0f) *0.03f + m_MouseRotSave.x;

		// ��]��90�x�����ɗ}����
		if (NewRotation.x >= D3DX_PI*0.49f)
		{
			NewRotation.x = D3DX_PI*0.49f;
			m_MousePosOld = m_MousePosCurrent;
			m_MouseRotSave.y = m_rotDest.y;
			m_MouseRotSave.x = m_rotDest.x;

		}
		else if (NewRotation.x <= -D3DX_PI*0.49f)
		{
			NewRotation.x = -D3DX_PI*0.49f;
			m_MousePosOld = m_MousePosCurrent;
			m_MouseRotSave.y = m_rotDest.y;
			m_MouseRotSave.x = m_rotDest.x;

		}
		m_rotDest.x = NewRotation.x;
	}

	if (pMouse->GetRelease(1))
	{
		m_MouseRotSave.y = m_rotDest.y;
		m_MouseRotSave.x = m_rotDest.x;
	}

	//�����_��]
	if (pKeyboard->GetPress(DIK_2))
	{
		m_rotDest.z += 0.01f;
	}
	else if (pKeyboard->GetPress(DIK_X))
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
}

//-----------------------------------------------------------------------------
//�ړ�����
//-----------------------------------------------------------------------------
void CCamera::MoveCameraGame(void)
{
	CKeyboard	*pKeyboard	= CManager::GetKeyboard();

	float fCameraRotation_X = CAMERA_HORIZON_ROTATION;
	float fCameraRotation_Y = CAMERA_VERTICAL_ROTATION;

	// �㏸
	if (pKeyboard->GetPress(DIK_W))
	{
		// ���v���ɉ�]
		m_rotDest.x += fCameraRotation_Y;
	}

	// ���~
	if (pKeyboard->GetPress(DIK_S))
	{
		// ���v���ɉ�]
		m_rotDest.x -= fCameraRotation_Y;
	}

	// ���_�̉�]
	if (pKeyboard->GetPress(DIK_D))
	{
		// ���v���ɉ�]
		m_rotDest.y -= fCameraRotation_X;
	}

	if (pKeyboard->GetPress(DIK_A))
	{
		// ���v���ɉ�]
		m_rotDest.y += fCameraRotation_X;
	}

	//�E�X�e�B�b�N�ŃJ�����̉�]
	CHossoLibrary::Check3DCameraStick(m_rotDest, fCameraRotation_X, fCameraRotation_Y);

	//�c�����@��]����
	if (m_rotDest.x < 2.0f)
	{
		m_rotDest.x = 2.0f;
	}
	if (m_rotDest.x > 3.1f)
	{
		m_rotDest.x = 3.1f;
	}

	//3.14�͈̔͂ɗ}����
	CHossoLibrary::CalcRotation(m_rotDest.y);
}
//-----------------------------------------------------------------------------
//��]����
//-----------------------------------------------------------------------------
void CCamera::RotCameraGame(void)
{
	//�L�[�{�[�h�̃|�C���^
	CKeyboard	*pKeyboard = CManager::GetKeyboard();

	// posR��posV�̂��ꂼ��̍���
	D3DXVECTOR3 difposR, difposV;

	//�v���C���[�̏��擾
	CPlayer *pPlayer = CManager::GetBaseMode()->GetPlayer();

	//nullcheck
	if (pPlayer)
	{
		//3D�̃v���C���[�ɃL���X�g
		CPlayer_3D *pPlayer3D = dynamic_cast<CPlayer_3D*>(pPlayer);		//�����_���v���C���[�ɍ��킷
		//nullcheck
		if (pPlayer3D)
		{
			m_posRDest = pPlayer3D->GetPos();
		}
	}

	//��]�̍���
	D3DXVECTOR3 rotDiff = m_rotDest - m_rot;

	//3.14�����Ȃ��悤�ɂ���
	CHossoLibrary::CalcRotation(rotDiff.x);
	CHossoLibrary::CalcRotation(rotDiff.y);

	//��]
	m_rot += rotDiff * 0.1f;

	// ���݂̒����_�ƖړI�̒����_�̍����̌v�Z
	difposR = m_posRDest - m_posR;

	// �����_��ǂ������鑬�x
	m_posR += difposR * 0.1f;

	m_posVDest.x = m_posR.x + cosf(m_rot.x) * sinf(m_rot.y) * m_fDistance;
	m_posVDest.y = m_posR.y + sinf(m_rot.x) * m_fDistance;
	m_posVDest.z = m_posR.z + cosf(m_rot.x) * cosf(m_rot.y) * m_fDistance;

	// ���݂̎��_�ƖړI�̎��_�̍����̌v�Z
	difposV = m_posVDest - m_posV;

	// ���_�������_�ɒǂ������x
	m_posV += difposV * 0.15f;

	//3.14�����Ȃ��悤�ɂ���
	CHossoLibrary::CalcRotation(m_rot.x);
	CHossoLibrary::CalcRotation(m_rot.y);

}

//-----------------------------------------------------------------------------
//�J�������������W�ɐݒ�
//-----------------------------------------------------------------------------
void CCamera::ResetCamera()
{
	//�������W��
	m_rotDest = m_rot = DEFAULT_CAMERA_ROTATION;
	m_fDistance = DEFAULT_DISTANCE;

	m_posV.x = m_posVDest.x = m_posRDest.x - sinf(m_rot.y) * cosf(m_rot.x) * m_fDistance;
	m_posV.y = m_posVDest.y = m_posRDest.y + sinf(m_rot.x)	* m_fDistance;
	m_posV.z = m_posVDest.z = m_posRDest.z - cosf(m_rot.y) * cosf(m_rot.x) * m_fDistance;

	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}