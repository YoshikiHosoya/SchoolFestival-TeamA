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
		COLLISION_PLAYERBULLET = 0,			// �v���C���[�e
		COLLISION_ENEMYBULLET,				// �G�e
		COLLISION_PLAYER,						// �v���C���[
		COLLISION_ENEMY,						// �G�l�~�[
		COLLISION_PRISONER,					// �ߗ�
		COLLISION_ITEM,						// �A�C�e��
		COLLISION_OBSTACLE,					// ��Q��
		COLLISION_VEHICLE,					// ��蕨
		COLLISION_OTHER,						// ���̑�
		COLLISION_MAX
	} COLLISION;

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
	static CCollision * Create(void);					// �����蔻��̐���

	/* �����o�֐� */
	void SetPos(D3DXVECTOR3 *pos);						// ���W�̐ݒ�
	void SetPosOld(D3DXVECTOR3 *posold);				// 1�t���[���O�̍��W�̐ݒ�
	void SetSize(D3DXVECTOR3 size);						// �T�C�Y�̐ݒ�
	void SetSize2D(D3DXVECTOR3 size);					// 2D�p�T�C�Y�̐ݒ�
	void SetMove(D3DXVECTOR3 *move);					// �ړ��ʂ̐ݒ�
	void SetType(COLLISION type);							// �^�C�v�̐ݒ�
	bool Collision2D(CCollision *pCollision);			// �^�̓����蔻��
	bool CharCollision2D(CCollision *pCollision);		// �L�����N�^�[�p�^�̓����蔻��
	bool OtherCollision2D(CCollision *pCollision);		// �^�̓����蔻��
	bool BlockCollision2D(CCollision *pCollision);		// �^�u���b�N�̓����蔻��
	COLLISION GetObjtype() {return m_objtype;};			// �N�̓����蔻��Ȃ̂���Ԃ�
	void DeCollisionCreate(COLLISIONTYPE collisiontype);// �f�o�b�O�p�����蔻��̐���
	bool ForPlayerBulletCollision(int nEnemyDamage,
							int nObstacleDamage,
							bool Penetration);			// �v���C���[�̒e���s������ �_���[�W�� �ђʂ��邩�ǂ���

	bool ForEnemyCollision(int nPlayerDamage,
		bool Penetration);								// �G�l�~�[�̒e���s������ �_���[�W�� �ђʂ��邩�ǂ���

	bool ForPlayer_EnemyCollision(bool Penetration);	// �v���C���[�ƃG�l�~�[���s������ �_���[�W�� �ђʂ��邩�ǂ���

	bool ForPlayer_ObstacleCollision(bool Penetration);	// �v���C���[�Ə�Q�����s������ �_���[�W�� �ђʂ��邩�ǂ���

	bool ForPlayer_PrisonerCollision(bool Penetration);	// �v���C���[�ƕߗ����s������ �_���[�W�� �ђʂ��邩�ǂ���

	bool ForPlayer_ItemCollision(bool Penetration);	// �v���C���[�ƕߗ����s������ �_���[�W�� �ђʂ��邩�ǂ���

protected:
private:
	/* �����o�ϐ� */
	COLLISION			m_objtype;						// �^�C�v
	COLLISIONTYPE		m_Collisiontype;				// �����蔻��̃^�C�v
	D3DXVECTOR3			*m_ppos;						// �ʒu���̃|�C���^
	D3DXVECTOR3			*m_posOld;						// �O��̈ʒu���
	D3DXVECTOR3			m_size;							// �T�C�Y���
	D3DXVECTOR3			*m_pmove;						// �ړ����̃|�C���^
	CDebugcollision		*m_Debugcollision;				// �f�o�b�O�p�����蔻��̃|�C���^
	bool				m_bDeadFlag;					// ���S�t���O
};

#endif