//------------------------------------------------------------------------------
//
//�����蔻�菈��  [collision.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _COLLISION_H_
#define _COLLISION_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"

//------------------------------------------------------------------------------
//�O���錾
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CMesh;

class CCollision
{
public:
	CCollision();
	~CCollision();

	//�R���W�����̎��
	enum COLLISION_TYPE
	{
		COLLISION_CHARACTER,		//�L�����N�^�[
		COLLISION_WEAPON,			//����
		COLLISION_EXPLOSION,		//����
		COLLISION_OBJECT,			//�I�u�W�F�N�g
		COLLISION_CAMERA,			//�J����
	};
	void ShowDebugInfo();																				//�f�o�b�O���\�L
	static std::unique_ptr<CCollision> Create(D3DXMATRIX *pMtx, COLLISION_TYPE ColisionType);			//��������
	void SetCollisionInfo(float fRadius,float fLength);													//���ݒ�@���a�ƒ���
	void SetCollisionVtx(MODEL_VTX &modelVtx);															//���ݒ�@���_
	bool CollisionCylinder(CCollision *pTargetCollision);												//�V�����_�[�̃R���W�����֐�
	bool CollisionCharacter(CCollision *pTargetCollision,D3DXVECTOR3 *pOut);							//�L�����N�^�[���m�̏Փ˔���@�V�����_�[�Ŏ��
	bool CollisionExplosion(CCollision *pTargetCollision);												//�����p�̔���
	bool CollisionObject(CCollision *pTargetCollision, D3DXVECTOR3 &rPos,D3DXVECTOR3 &rPosOld,D3DXVECTOR3 &rMove);			//�I�u�W�F�N�g�Ƃ̏Փ˔���@���Ɓ�
	bool CollisionObjectToCamera(CCollision *pTargetCollision, D3DXVECTOR3 &rPos, D3DXVECTOR3 &rPosOld);					//�I�u�W�F�N�g�Ƃ̏Փ˔���@�J�����p

private:
	D3DXMATRIX *m_pParentMtx;			//������̃}�g���b�N�X
	MODEL_VTX m_ModelVtx;				//���Ŕ�����Ƃ��Ɏg���@�ő咸�_�ƍŏ����_
	float m_fRadius;					//���a
	float m_fLength;					//����̒���

#ifdef _DEBUG
	std::shared_ptr<CMesh> m_pDebugMesh;		//���b�V���̃|�C���^ �`��p
	void CreateMesh();							//���b�V������
#endif // _DEBUG

};
#endif