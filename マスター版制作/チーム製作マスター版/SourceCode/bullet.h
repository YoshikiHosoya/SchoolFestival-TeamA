// =====================================================================================================================================================================
//
// �o���b�g�̏��� [bullet.h]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

// =====================================================================================================================================================================
// �C���N���[�h�t�@�C��
// =====================================================================================================================================================================
#include "main.h"
#include "model.h"
#include "gun.h"

// =====================================================================================================================================================================
// �O���錾
// =====================================================================================================================================================================

// =====================================================================================================================================================================
// �o���b�g�N���X
// =====================================================================================================================================================================
class CBullet : public CModel, public CGameObject
{
public:
	// ----- �e�̃p�����[�^�[ -----
	typedef struct
	{
		float				fBulletSpeed;	// �e��
		int					nLife;			// �̗�
		int					nPower;			// �З�
		int					nAmmo;			// �e��
		int					nTrigger;		// 1�g���K�[�Ŕ��˂����e��
		int					nInterval;		// �C���^�[�o��
		D3DXVECTOR3			CollisionSize;	// �����蔻��̃T�C�Y
	}BULLET_PARAM;

	CBullet(OBJ_TYPE type);			// �R���X�g���N�^
	~CBullet();						// �f�X�g���N�^

	/* �����o�֐� */
	virtual HRESULT				Init();													// ������
	virtual void				Uninit();												// �I��
	virtual void				Update();												// �X�V
	virtual void				Draw();													// �`��
	virtual void				DeleteBullet();											// �e����
	virtual void				BulletReaction(D3DXVECTOR3 rot);						// �e�̔���

	/* �ÓI�����o�֐� */
	static	void				BulletLoad();											// �e�̃��[�h
	void						CalcBulletMove(D3DXVECTOR3 ShotRot,int Guntype);		// �e�̔��˕����v�Z
	void						CalcIncendiaryMove(D3DXVECTOR3 ShotRot, float move_x, float move_y);// �e�̔��˕����v�Z

	/* �����o�֐� */
	D3DXVECTOR3					&GetMove()						{ return m_move; };					// �ړ��l�̎擾
	void						SetMove(D3DXVECTOR3 move)		{ m_move = move; };					// �ړ��l�̐ݒ�
	static	BULLET_PARAM		*GetBulletParam(int nCnt)		{ return &m_BulletParam[nCnt]; };	// �e�̃p�����[�^�[�̍\���̂̎擾
	void						SetBulletParam(CGun::GUN_TYPE type);								// �e�̃p�����[�^�[�ݒ�

	int							GetLife()						{ return m_nLife; };
	void						SetBulletPoint(CBullet *pBullet) { m_pBullet = pBullet; };
	CBullet						*GetBullePoint()				{ return m_pBullet; };

private:
	/* �����o�ϐ� */
	D3DXVECTOR3					m_move;					// �ړ��l
	CGun::GUN_TYPE				m_GunType;				// �K���̃^�C�v
	int							m_nLife;				// �̗�
	CBullet						*m_pBullet;				// �e�̎��
	/* �ÓI�����o�ϐ� */
	static char					*m_BulletFileName[CGun::GUNTYPE_MAX];	// �e�̃t�@�C����
	static	BULLET_PARAM		m_BulletParam[CGun::GUNTYPE_MAX];		// �e�̃p�����[�^�[

	void			BulletHitSound();		// �e�������������̃T�E���h�Đ�

};
#endif
