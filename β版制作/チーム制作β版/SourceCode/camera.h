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

	// �J�����̒Ǐ]���
	enum CAMERA_FOLLOWING_TYPE
	{
		CAMERA_FOLLOWING_TYPE_PLAYER,			// �v���C���[
		CAMERA_FOLLOWING_TYPE_MAPEDITOR,		// �}�b�v�G�f�B�^�[
		CAMERA_FOLLOWING_TYPE_MOUSE,			// �}�E�X
		CAMERA_FOLLOWING_TYPE_MAX
	};

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
	void SetCameraPosRDest(D3DXVECTOR3 posR) { m_posRDest = posR; };	// �����_�̖ړI�n�̐ݒ�
	void SetCameraStopMove(bool bStop) { m_bStopMove = bStop; };

	D3DXVECTOR3 GetPosV()			{ return m_posV; };				//���_
	D3DXVECTOR3 GetPosR()			{ return m_posR; };				//�����_
	D3DXVECTOR3 GetRot()			{ return m_rot; };				//����
	D3DXMATRIX *GetProjMtxPtr()		{ return &m_mtxProjection; };	//�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX *GetViewMtxPtr()		{ return &m_mtxView; };			//�r���[�}�g���b�N�X
	float GetDistance()				{ return m_fDistance; };		//���_�ƒ����_�̋���
	float GetNear()					{ return m_fNear; };			//Near�l
	float GetFar()					{ return m_fFar; };				//Far�l
	bool GetStop()					{ return m_bStopMove; };		//�J�����̈ړ��X�g�b�v

private:
	D3DXVECTOR3 m_posV;							//���_
	D3DXVECTOR3 m_posVDest;						//���_�̖ړI�n
	D3DXVECTOR3 m_posR;							//�����_
	D3DXVECTOR3 m_posRDest;						//�����_�̖ړI�n
	D3DXVECTOR3 m_rot;							//����
	D3DXVECTOR3 m_rotDest;						//������������
	D3DXVECTOR3 m_move;							//�ړ����_
	D3DXVECTOR3 m_vecV;							//������x�N�g��
	D3DXMATRIX m_mtxProjection;					//�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX m_mtxView;						//�r���[�}�g���b�N�X
	float m_fDistance;							//����
	float m_fNear;								//Near�l
	float m_fFar;								//Far�l

	D3DXVECTOR3 m_posCameraEndLine;				//�J�����̃��C��

	int m_nCountTimer;							//�Ǐ]�̃^�C�}�[
	int m_nCnt;
	int m_CameraFollowingType;					// �J�����̒Ǐ]���

	bool m_bStopMove;							// �J�����ړ����Ȃ�
};
#endif
