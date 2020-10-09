//-----------------------------------------------------------------------------
//
// �J�������� [camera.h]
// Author : Yoshiki Hosoya
//
//-----------------------------------------------------------------------------
#ifndef _CAMERA_H_
#define _CAMERA_H_

#define _CRT_SECURE_NO_WARNINGS

//-----------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------
#include "main.h"

//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CCollision;

class CCamera
{
public:
	typedef enum
	{
		CAMERA_FIXED = 0,			//�J�����Œ�
		CAMERA_PLAYER_FOLLOWING,	//�v���C���[�Ǐ]
		CAMERA_DEBUG				//�f�o�b�O���[�h
	} CAMERA_STATE;

	CCamera();
	~CCamera();
	void Init();															//������
	void Uninit();															//�I��
	void Update();															//�X�V
	void SetCamera();														//�J�����ݒ�

	void ShowCameraInfo();													//�J�������\��
	void SetState(CAMERA_STATE state) { m_CameraState = state; };			//�J�����̏�Ԑ؂�ւ�
	void ResetCamera();

	D3DXVECTOR3 GetCameraRot()		{ return m_rot; };						//��]���擾
	D3DXVECTOR3 GetCameraPosV()		{ return m_posV; };						//���_�擾
	D3DXVECTOR3 GetCameraPosR()		{ return m_posR; };						//�����_�擾
	D3DXMATRIX GetMtxView()			{ return m_mtxView; };					//�r���[�}�g���b�N�X�擾
	D3DXMATRIX GetMtxProjection()	{ return m_mtxProjection; };			//�v���W�F�N�V�����}�g���b�N�擾

	CAMERA_STATE GetCameraState()	{return m_CameraState;};

private:
	D3DXVECTOR3		m_posV;							//���_
	D3DXVECTOR3		m_posVDest;						//�ړI�̎��_
	D3DXVECTOR3		m_posVOld;						//1F�O�̍��W
	D3DXVECTOR3		m_posR;							//�����_
	D3DXVECTOR3		m_posRDest;						//�ړI�̒����_
	D3DXVECTOR3		m_move;							//�ړ���
	D3DXVECTOR3		m_rot;							//��]
	D3DXVECTOR3		m_rotDest;						//��]�̌���n

	D3DXVECTOR3		m_vecU;							//�x�N�g��
	D3DXMATRIX		m_mtxProjection;				//�}�g���b�N�X�v���W�F�N�V����
	D3DXMATRIX		m_mtxView;						//�}�g���b�N�X�r���[
	D3DXMATRIX		m_mtxWorld;						//���[���h�}�g���b�N�X
	float			m_fDistance;					//���_�ƒ����_�̋���
	float			m_fDefaultDistace;				//�����̃J��������

	D3DXVECTOR2		m_MousePosCurrent;				//���݂̃}�E�X�̈ʒu
	D3DXVECTOR2		m_MousePosOld;					//�O��̃}�E�X�̈ʒu
	D3DXVECTOR2		m_MouseRotSave;					//��]��ۑ�
	D3DXVECTOR3		m_DirecVector;					//�����Ă�x�N�g��

	std::unique_ptr<CCollision> m_pCollision;		//����

	CAMERA_STATE	m_CameraState;					//�J�����̏��

	void MoveCameraDebug();							//�J�����ړ�����
	void RotCameraDebug();							//�J������]����
	void MouseCameraOperation();					//�}�E�X�ŃJ��������

	void MoveCameraGame();							//�J�����ړ�����
	void RotCameraGame();							//�J������]����

};

#endif