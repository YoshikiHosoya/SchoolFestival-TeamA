//------------------------------------------------------------------------------
//
//�p�[�c�ƂȂ郂�f���̏���  [modelparts.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _MODELPARTS_H_
#define _MODELPARTS_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "sceneX.h"
#include "motion.h"

//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class COrbit;
class CModelParts : public CSceneX
{
public:
	CModelParts();
	virtual ~CModelParts();

	virtual HRESULT Init();																	//������
	virtual void Uninit();																	//�I��
	virtual void Update();																	//�X�V
	virtual void Draw();																	//�`��
	virtual void ShowDebugInfo();															//�f�o�b�O���\�L
	static std::unique_ptr<CModelParts> Create(std::shared_ptr<CModelInfo> pModelInfo);		//��������
	void SetPartsInfo(int nIndex,int nParent, D3DXVECTOR3 pos, D3DXVECTOR3 rot);			//�p�[�c�̏��ݒ�
	void SetParentMtx(D3DXMATRIX *pParentMtx);												//�}�g���b�N�X�ݒ�
	int GetParent() {return m_nParent;}														//�e�ԍ��擾
	int GetIndex() { return m_nIndex; }														//�����̔ԍ��擾

	void SetMotionRotDest(CMotion::MOTION_TYPE motiontype,int nKey);						//���[�V�����̉�]�̌v�Z�@1F������̉�]�ʎZ�o
	void SetForcedRot(CMotion::MOTION_TYPE motiontype, int nKey);							//���[�V�����@������]
	void SetMotionPosDest(CMotion::MOTION_TYPE motiontype, int nKey);						//���[�V�����̌��_���W�ݒ� 1F������̈ړ��ʎZ�o
	void SetForcedPos(CMotion::MOTION_TYPE motiontype, int nKey);							//���[�V�����@�������W�ݒ�@���p

protected:

private:
	D3DXVECTOR3	m_rot1F;												//��]�̍���
	float m_fHeight1F;													//���W�̍��� ���̂�
	int m_nIndex;														//������ID
	int m_nParent;														//�e�̔ԍ�
	D3DXMATRIX *m_pParentMtx;											//�e�̃}�g���b�N�X

};
#endif