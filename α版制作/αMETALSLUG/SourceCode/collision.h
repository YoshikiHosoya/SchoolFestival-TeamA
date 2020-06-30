//=============================================================================
//
// Collision�w�b�_�[�����̐���[collision.h]
// Author : Fujiwara Masato
//
//=============================================================================
#ifndef _COLLISION_H_
#define _COLLISION_H_	 // �t�@�C������������߂�

//=============================================================================
//
// �C���N���[�h�t�@�C��
//
//=============================================================================
#include "main.h"

//=============================================================================
//
// �}�N����`
//
//=============================================================================

//=============================================================================
//
// �O���錾
//
//=============================================================================
class CDebugcollision;

//=============================================================================
//
// �N���X
//
//=============================================================================
class CCollision
{
public:
	// �I�u�W�F�N�g�̎��
	typedef enum
	{
		OBJTYPE_PLAYERBULLET = 0,			// �v���C���[�e
		OBJTYPE_ENEMYBULLET,				// �G�e
		OBJTYPE_PLAYER,						// �v���C���[
		OBJTYPE_ENEMY,						// �G�l�~�[
		OBJTYPE_PRISONER,					// �ߗ�
		OBJTYPE_ITEM,						// �A�C�e��
		OBJTYPE_OBSTACLE,					// ��Q��
		OBJTYPE_OTHER,						// ���̑�
		OBJTYPE_MAX
	} OBJTYPE;

	// �����蔻��̎�Ȏ��
	typedef enum
	{
		// �͈͔���
		COLLISIONTYPE_NORMAL = 0,			// ���S�_�����_�ɂ��锻��
		COLLISIONTYPE_CHARACTER,			// ���������_�ɂ��锻��
		COLLISIONTYPE_OTHER,				// ���S�_�����_�Ƃ���I�u�W�F�N�g�Ƒ��������_�ɂ���I�u�W�F�N�g�Ŕ���
		// �u���b�N����
		COLLISIONTYPE_BLOCK,				// ���S�_�����_�Ƃ���u���b�N�Ƒ��������_�̃I�u�W�F�N�g�Ŕ���
		COLLISIONTYPE_MAX
	} COLLISIONTYPE;



	/* �����o�֐� */
	CCollision();
	~CCollision();
	void Init(void);
	void Uninit(void);
	void Update(void);

	/* �ÓI�����o�֐� */
	static void ReleaseCollision(CCollision *pColl);	// �����蔻��폜
	static CCollision * Create(void);					// �����蔻��̐���

	/* �����o�֐� */
	void SetPos(D3DXVECTOR3 *pos);						// ���W�̐ݒ�
	void SetPosOld(D3DXVECTOR3 *posold);				// 1�t���[���O�̍��W�̐ݒ�
	void SetSize(D3DXVECTOR3 size);						// �T�C�Y�̐ݒ�
	void SetSize2D(D3DXVECTOR3 size);					// 2D�p�T�C�Y�̐ݒ�
	void SetMove(D3DXVECTOR3 *move);					// �ړ��ʂ̐ݒ�
	void SetType(OBJTYPE type);							// �^�C�v�̐ݒ�
	bool Collision(OBJTYPE objtype);					// ���^�̓����蔻��
	bool Collision2D(CCollision *pCollision);			// �^�̓����蔻��
	bool CharCollision2D(CCollision *pCollision);		// �L�����N�^�[�p�^�̓����蔻��
	bool OtherCollision2D(CCollision *pCollision);		// �^�̓����蔻��
	bool BlockCollision2D(CCollision *pCollision);		// �^�u���b�N�̓����蔻��
	OBJTYPE GetObjtype() {return m_objtype;};			// �N�̓����蔻��Ȃ̂���Ԃ�
	void DeCollisionCreate(COLLISIONTYPE collisiontype);// �f�o�b�O�p�����蔻��̐���

protected:
private:
	/* �����o�ϐ� */
	OBJTYPE				m_objtype;						// �^�C�v
	COLLISIONTYPE		m_Collisiontype;				// �����蔻��̃^�C�v
	D3DXVECTOR3			*m_ppos;						// �ʒu���̃|�C���^
	D3DXVECTOR3			*m_posOld;						// �O��̈ʒu���
	D3DXVECTOR3			m_size;							// �T�C�Y���
	D3DXVECTOR3			*m_pmove;						// �ړ����̃|�C���^
	CDebugcollision		*m_Debugcollision;				// �f�o�b�O�p�����蔻��̃|�C���^
	bool				m_bDeadFlag;					// ���S�t���O
	bool				m_bHitFlag;						// �����蔻��ɐG�ꂩ�ǂ���
	CCollision			*m_pCollision;					// �����蔻��̃|�C���^
};

#endif