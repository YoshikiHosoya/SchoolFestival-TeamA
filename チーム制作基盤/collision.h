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
		OBJTYPE_ITEM,						// �A�C�e��
		OBJTYPE_OTHER,						// ���̑�
		OBJTYPE_MAX
	} OBJTYPE;

	/* �����o�֐� */
	CCollision();
	~CCollision();
	void Init(void);
	void Uninit(void);
	void Update(void);

	/* �ÓI�����o�֐� */
	static void UpdateAll(void);				// �����蔻��X�V
	static void Delete(CCollision *pColl);		// �����蔻��폜
	static void DeleteAll(void);				// �S�Ă̓����蔻��폜
	static CCollision * Create(void);			// �����蔻��̐���

	/* �����o�֐� */
	void SetPos(D3DXVECTOR3 *pos);				// ���W�̐ݒ�
	void SetSize(D3DXVECTOR3 size);				// �T�C�Y�̐ݒ�
	void SetSize2D(D3DXVECTOR3 size);			// 2D�p�T�C�Y�̐ݒ�
	void SetMove(D3DXVECTOR3 *move);			// �ړ��ʂ̐ݒ�
	void SetType(OBJTYPE type);					// �^�C�v�̐ݒ�
	bool Collision(OBJTYPE objtype);			// ���^�̓����蔻��
	bool Collision2D(CCollision *pCollision);	// �^�̓����蔻��
	bool GetHitFlag() {return m_bHitFlag;}		// ����̌��ʂ�Ԃ�
	OBJTYPE GetObjtype() {return m_objtype;};	// �N�̓����蔻��Ȃ̂���Ԃ�

protected:
private:
	/* �����o�ϐ� */
	OBJTYPE				m_objtype;				// �^�C�v
	D3DXVECTOR3			*m_ppos;				// �ʒu���̃|�C���^
	D3DXVECTOR3			m_posOld;				// �O��̈ʒu���
	D3DXVECTOR3			m_size;					// �T�C�Y���
	D3DXVECTOR3			*m_pmove;				// �ړ����̃|�C���^
	static CCollision	*m_pTop;				// �擪�I�u�W�F�N�g�ւ̃|�C���^
	static CCollision	*m_pCur;				// ���݃I�u�W�F�N�g�ւ̃|�C���^
	CCollision			*m_pNext;				// ���̃I�u�W�F�N�g�ւ̃|�C���^
	CCollision			*m_pPrey;				// �O�̃I�u�W�F�N�g�ւ̃|�C���^
	CDebugcollision		*m_Debugcollision;		// �f�o�b�O�p�����蔻��̃|�C���^
	bool				m_bDeadFlag;			// ���S�t���O
	bool				m_bHitFlag;				// �����蔻��ɐG�ꂩ�ǂ���
};

#endif