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

	void ResetCamera();
	void SetCameraPosfromDistance(D3DXVECTOR3 posR,D3DXVECTOR3 rot,float fDistance);
	void SetCameraPos(D3DXVECTOR3 posR, D3DXVECTOR3 posV);
private:
	D3DXVECTOR3 m_posV;			//���_
	D3DXVECTOR3 m_posVDest;		//���_�̖ړI�n
	D3DXVECTOR3 m_posR;			//�����_
	D3DXVECTOR3 m_posRDest;		//�����_�̖ړI�n
	D3DXVECTOR3 m_rot;			//����
	D3DXVECTOR3 m_rotDest;		//������������
	D3DXVECTOR3 m_move;			//�ړ����_
	D3DXVECTOR3 m_vecV;			//������x�N�g��
	D3DXMATRIX m_mtxProjection;	//�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX m_mtxView;			//�r���[�}�g���b�N�X
	float m_fDistance;			//����
	int m_nCountTimer;			//�Ǐ]�̃^�C�}�[
	int m_nCnt;

	bool m_bCameraMode;		//�f�o�b�O�J�������ǂ���
};
#endif
