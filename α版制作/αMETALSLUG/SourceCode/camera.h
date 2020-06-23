#pragma once
//=============================================================================
// �J�������� [camera.h]
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
class CCamera
{
public:
	void InitCamera(void);
	void UninitCamera(void);
	void UpdateCamera(void);
	void SetCamera(void);
	void SetMoveCamera(float rot);

	void DebugCommand();						//�f�o�b�O�p�̃R�}���h
	void CharacterFollowingMoveCamera();		//�L�����N�^�[�Ǐ]�J����
	void MouseMoveCamera();						//�}�E�X����J����
private:
	D3DXVECTOR3 posV;			//���_
	D3DXVECTOR3 posVDest;		//���_�̖ړI�n
	D3DXVECTOR3 posR;			//�����_
	D3DXVECTOR3 posRDest;		//�����_�̖ړI�n
	D3DXVECTOR3 rot;			//����
	D3DXVECTOR3 rotDest;		//������������
	D3DXVECTOR3 move;			//�ړ����_
	D3DXVECTOR3 vecV;			//������x�N�g��
	D3DXMATRIX mtxProjection;	//�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX mtxView;			//�r���[�}�g���b�N�X
	float fDistance;			//����
	int nCountTimer;			//�Ǐ]�̃^�C�}�[
	int nCnt;
	D3DXVECTOR3 pos;			//�|�W�V����

	bool m_bCameraMode;		//�f�o�b�O�J�������ǂ���
};
#endif
