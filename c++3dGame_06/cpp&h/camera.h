//=============================================================================
//
// �J�������� [camera.h]
// Author : Fujiwara Masato
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

// ------------------------------------------
//
// �N���X
//
// ------------------------------------------
class CCamera
{
public:
	/* �֐� */
	CCamera();
	~CCamera();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CCamera * Create(void);	// �쐬
	// �J�����ݒ�
	void Set(void);
	D3DXVECTOR3 GetRot(void);

	void SetCamera(void);
	void SetDistance(void);
	void SetRot(D3DXVECTOR3 rot);
	void SetRotWarp(void);		// ���[�v�p�̉�]���f

protected:

private:
	/* �֐� */
	void Rot(void);
	void PlayerFoll(void);
	void PlayerPos(void);

	/* �ϐ� */
	D3DXVECTOR3 m_posV;			// ���_
	D3DXVECTOR3 m_posVDest;		// �ړI���_
	D3DXVECTOR3 m_posVDiff;		// �ړI���_���王�_
	D3DXVECTOR3 m_posR;			// �����_
	D3DXVECTOR3 m_posRDest;		// �ڕW�����_
	D3DXVECTOR3 m_posRDiff;		// �ړI�����_���璍���_
	D3DXVECTOR3 m_posU;			// ������x�N�g��
	D3DXVECTOR3 m_between;		// �v���C���[�Ƃ̋���
	D3DXVECTOR3 m_last;			//
	D3DXVECTOR3 m_move;			// �ړ���
	D3DXVECTOR3 m_rot;			// ���_�̉�]��
	D3DXVECTOR3 m_rotDest;		// ���_�̖ړI��]�n�_
	D3DXVECTOR3 m_rotDiff;		// �ړI��]�n�_���猻�݉�]�n�_
	D3DXVECTOR3 m_rotBetween;		// �ړI��]�n�_�ƌ��݉�]�n�_�̍���
	D3DXMATRIX	m_mtxProjection;	// �v���W�F�N�V�����}�g���b�N�X(�e���r���_)
	D3DXMATRIX	m_mtxView;		// �r���[�}�g���b�N�X(�J�����}�����_)
	float		m_fLength;		// ���_�ƒ����_�̋���
	int			m_nCntTime;		// ���ʂɌ����̂ɂ����鎞��

	float		m_fx;			// x�̈ړ���
	float		m_fy;			// y�̈ړ���
	float		m_fz;			// z�̈ړ���

	float m_fDistance;
};

#endif
