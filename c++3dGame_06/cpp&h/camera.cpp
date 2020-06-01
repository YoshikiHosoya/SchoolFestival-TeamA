//=============================================================================
//
// �J�������� [camera.cpp]
// Author : Fujiwara Masato
//
//=============================================================================
#include "camera.h"
#include "input.h"
#include "joypad.h"
#include "manager.h"
#include "debugproc.h"
#include "player.h"
#include "mouse.h"
#include "title.h"
#include "pause.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define CAMERA_ROTRATE (0.06f)
// ----------------------------------------
// �R���X�g���N�^����
// ----------------------------------------
CCamera::CCamera()
{
	m_fx = 0;
	m_fz = 0;
	m_fy = 300;
	// �J�����̏�����

	m_posV = D3DXVECTOR3(m_fx, m_fy, m_fz);
	m_posVDest = m_posV;
	m_posVDiff = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posR = D3DXVECTOR3(500.0f, 200.0f, 500.0f);
	m_posRDest = m_posR;
	m_posRDiff = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_move = D3DXVECTOR3(1.0f, 3.0f, 3.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fLength = 0;
	m_nCntTime = 0;

	m_fDistance = 500;

	// ���_�ƒ����_�Ƃ̋����v�Z
	D3DXVECTOR3 diffPos = D3DXVECTOR3(m_posV.x, m_posV.y, m_posV.z - m_fDistance);

	// �����v�Z
	m_fLength = 500;
}

// ----------------------------------------
// �f�X�g���N�^����
// ----------------------------------------
CCamera::~CCamera()
{
}

// ----------------------------------------
// ����������
// ----------------------------------------
void CCamera::Init(void)
{
}

// ----------------------------------------
// �I������
// ----------------------------------------
void CCamera::Uninit(void)
{
}

// ----------------------------------------
// �X�V����
// ----------------------------------------
void CCamera::Update(void)
{
	//��l�̎��_ �v���C���[�Ɠ���
	PlayerPos();

	// ��]
	Rot();

	//CDebugproc::Print("�J�����̎��_x:%f,y:%f,z:%f\n", m_posVDest.x, m_posVDest.y, m_posVDest.z);
	//CDebugproc::Print("�J�����̒����_x:%f,y:%f,z:%f\n", m_posR.x, m_posR.y, m_posR.z);
	//CDebugproc::Print("�J�����̊p�xx:%f,y:%f,z:%f\n", m_rot.x, m_rot.y, m_rot.z);
}

// ----------------------------------------
// �`�揈��
// ----------------------------------------
void CCamera::Draw(void)
{
}

// ----------------------------------------
// �쐬����
// ----------------------------------------
CCamera * CCamera::Create(void)
{
	// �ϐ��錾
	CCamera * pCamera;
	// �������̐���(����->��{�N���X,��->�h���N���X)
	pCamera = new CCamera();
	// ����������
	pCamera->Init();
	// ���������I�u�W�F�N�g��Ԃ�
	return pCamera;
}

// ----------------------------------------
// �ݒ�
// ----------------------------------------
void CCamera::Set(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	// �f�o�C�X�̎擾

	// �v���W�F�N�V�����}�g���b�N�X //
	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH(
		&m_mtxProjection,							// (�e���r���_)
		D3DXToRadian(45.0f),						// ����p(��p)
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,	// �A�X�y�N�g��
		10.0f,										// MearZ�l(�߂��r���[���ʂ�Z�l)
		20000.0f);									// FarZ�l(�����r���[���ʂ�Z�l)�����l��1000

													// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	// �r���[�}�g���b�N�X //
	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	// �r���[�}�g���b�N�X���쐬
	D3DXMatrixLookAtLH(
		&m_mtxView,	// (�J�����}�����_)
		&m_posV,		// �J�����̎��_
		&m_posR,		// �J�����̒��ړ_
		&m_posU);	// �J�����̏�����x�N�g��

							// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}

// ----------------------------------------
// �J�����̕���
// ----------------------------------------
D3DXVECTOR3 CCamera::GetRot(void)
{
	return m_rot;
}

// ----------------------------------------
// �J�����̏�Ԃ�ς���
// ----------------------------------------
void CCamera::SetCamera(void)
{
}

// ----------------------------------------
// �v���C���[�Ƃ̋������v�Z
// ----------------------------------------
void CCamera::SetDistance(void)
{
	m_posV = D3DXVECTOR3(m_fx, m_fy, m_fz);

	// ���_�ƒ����_�Ƃ̋����v�Z
	D3DXVECTOR3 diffPos = m_posV - m_posR;

	// �����v�Z
	m_fLength = sqrtf(diffPos.x*diffPos.x + diffPos.z * diffPos.z);
}

// ----------------------------------------
// �J�����̉�]��ݒ�
// ----------------------------------------
void CCamera::SetRot(D3DXVECTOR3 rot)
{
	m_rot = D3DXVECTOR3(rot.x, rot.y, rot.z);
	m_rotDest = D3DXVECTOR3(rot.x, rot.y, rot.z);
}

// ----------------------------------------
// ��]
// ----------------------------------------
void CCamera::SetRotWarp(void)
{
	m_rot = D3DXVECTOR3(0.0f, -1.57f, 0.0f);
	m_rotDest = D3DXVECTOR3(0.0f, -1.57f, 0.0f);
}

// ----------------------------------------
// �v���C���[�Ǐ]
// ----------------------------------------
void CCamera::PlayerFoll(void)
{
	/* �ϐ��錾 */
	CPlayer * pPlayer = NULL;	// �v���C���[
	// ���擾
	for (int nCntLayer = 0; nCntLayer < CScene::GetMaxLayer(CScene::LAYER_3DOBJECT); nCntLayer++)
	{
		if (pPlayer == NULL) pPlayer = (CPlayer*)CScene::GetActor(CScene::ACTOR_PLAYER, CScene::LAYER_3DOBJECT, nCntLayer);	// �v���C���[
	}

	m_nCntTime++;				// �J�E���g�^�C��
	//-------------------- ���_�ړ� --------------------//
	// �Q�[���̃J�����̉�]�̖ړI�n
	m_posR = pPlayer->GetPos();
}

// ----------------------------------------
// �v���C���[���W
// ----------------------------------------
void CCamera::PlayerPos(void)
{
	/* �ϐ��錾 */
	CPlayer * pPlayer = NULL;	// �v���C���[
								// ���擾
	for (int nCntLayer = 0; nCntLayer < CScene::GetMaxLayer(CScene::LAYER_3DOBJECT); nCntLayer++)
	{
		if (pPlayer == NULL) pPlayer = (CPlayer*)CScene::GetActor(CScene::ACTOR_PLAYER, CScene::LAYER_3DOBJECT, nCntLayer);	// �v���C���[
	}

	m_nCntTime++;				// �J�E���g�^�C��
								//-------------------- ���_�ړ� --------------------//
								// �Q�[���̃J�����̈ʒu

	if (pPlayer != NULL)
	{
		m_posV = pPlayer->GetPos();
	}
}

// ----------------------------------------
// ��]
// ----------------------------------------
void CCamera::Rot(void)
{
	CPlayer * pPlayer = NULL;	// �v���C���[

	int nValueH = 0;//�X�e�B�b�N�̉�
	int nValueV = 0;//�X�e�B�b�N�̏c

								// ���擾
	for (int nCntLayer = 0; nCntLayer < CScene::GetMaxLayer(CScene::LAYER_3DOBJECT); nCntLayer++)
	{
		if (pPlayer == NULL) pPlayer = (CPlayer*)CScene::GetActor(CScene::ACTOR_PLAYER, CScene::LAYER_3DOBJECT, nCntLayer);	// �v���C���[
	}

	CManager::GetJoy()->GetStickRight(0, &nValueH, &nValueV);

	if (CPause::GetPause() == false)
	{
		if (CManager::GetMode() == CManager::MODE_TITLE && CManager::GetTitle()->GetMode() == CTitle::TITLEMODE_FREE || CManager::GetMode() == CManager::MODE_GAME)
		{
			if (nValueH != 0 || nValueV != 0)
			{
				// ���ɓ|���Ă��鎞
				if (nValueH <= -1)
				{
					m_rotDest.y -= CAMERA_ROTRATE;
					m_rotDest.y = CCalculation::Rot_One_Limit(m_rotDest.y);
					// -3.14�`3.14�ɉ�]�������Œ肳����
					// ���_�X�V
					m_posVDest.x = m_posRDest.x + sinf(m_rot.y) * m_fLength;
					m_posVDest.z = m_posRDest.z + cosf(m_rot.y) * m_fLength;
				}
				// �E�ɓ|���Ă��鎞
				else if (nValueH >= 1)
				{
					m_rotDest.y += CAMERA_ROTRATE;
					m_rotDest.y = CCalculation::Rot_One_Limit(m_rotDest.y);
					// -3.14�`3.14�ɉ�]�������Œ肳����
					m_rot.y = CCalculation::Rot_One_Limit(m_rot.y);
					// ���_�X�V
					m_posVDest.x = m_posRDest.x + sinf(m_rot.y) * m_fLength;
					m_posVDest.z = m_posRDest.z + cosf(m_rot.y) * m_fLength;
				}
			}

			if (CManager::GetKeyboard()->GetKeyboardPress(DIK_LEFT))
			{//�� �J�������_��]
				m_rotDest.y -= CAMERA_ROTRATE;
				m_rotDest.y = CCalculation::Rot_One_Limit(m_rotDest.y);
				// -3.14�`3.14�ɉ�]�������Œ肳����
				m_rot.y = CCalculation::Rot_One_Limit(m_rot.y);
				// ���_�X�V
				m_posVDest.x = m_posRDest.x + sinf(m_rot.y) * m_fLength;
				m_posVDest.z = m_posRDest.z + cosf(m_rot.y) * m_fLength;
			}

			else if (CManager::GetKeyboard()->GetKeyboardPress(DIK_RIGHT))
			{//�E �J�������_��]
				m_rotDest.y += CAMERA_ROTRATE;
				m_rotDest.y = CCalculation::Rot_One_Limit(m_rotDest.y);
				// -3.14�`3.14�ɉ�]�������Œ肳����
				m_rot.y = CCalculation::Rot_One_Limit(m_rot.y);
				// ���_�X�V
				m_posVDest.x = m_posRDest.x + sinf(m_rot.y) * m_fLength;
				m_posVDest.z = m_posRDest.z + cosf(m_rot.y) * m_fLength;
			}

			// �}�E�X�ł̎��_�ړ�
			//else
			//{
			//	m_rotDest.y = m_rot.y + ((float)CManager::GetMouse()->GetX()/70);
			//	m_rotDest.y = CCalculation::Rot_One_Limit(m_rotDest.y);
			//	// -3.14�`3.14�ɉ�]�������Œ肳����
			//	m_rot.y = CCalculation::Rot_One_Limit(m_rot.y);
			//	// ���_�X�V
			//	m_posVDest.x = m_posRDest.x + sinf(m_rot.y) * m_fLength;
			//	m_posVDest.z = m_posRDest.z + cosf(m_rot.y) * m_fLength;
			//}
		}
	}

	// ����
	float Rotdif = m_rotDest.y - m_rot.y;
	Rotdif = CCalculation::Rot_One_Limit(Rotdif);

	m_rot.y += Rotdif * 0.2f;
	m_rot.y = CCalculation::Rot_One_Limit(m_rot.y);

	if(pPlayer != NULL)
	{
		m_posR.y = pPlayer->GetPos().y;
		m_posR.x = m_posV.x + sinf(D3DX_PI + m_rot.y) * m_fDistance;
		m_posR.z = m_posV.z + cosf(D3DX_PI + m_rot.y) * m_fDistance;
	}
}
