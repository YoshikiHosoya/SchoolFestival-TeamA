// =====================================================================================================================================================================
//
// �K���̏��� [gun.h]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#ifndef _GUN_H_
#define _GUN_H_

// =====================================================================================================================================================================
// �C���N���[�h�t�@�C��
// =====================================================================================================================================================================
#include "main.h"
#include "model.h"

// =====================================================================================================================================================================
// �K���N���X
// =====================================================================================================================================================================
class CGun : public CModel
{
public:

	// �e�̎��
	enum BULLET_TYPE
	{
		TYPE_PLAYER = 0,
		TYPE_ENEMY,
		TYPE_MAX,
	};

	// �e�̎��
	enum GUN_TYPE
	{
		GUNTYPE_HANDGUN = 0,						// �n���h�K��
		GUNTYPE_HEAVYMACHINEGUN,					// �w�r�[�}�V���K��
		GUNTYPE_SHOTGUN,							// �V���b�g�K��
		GUNTYPE_LASERGUN,							// ���[�U�[�K��
		GUNTYPE_ROCKETLAUNCHER,						// ���P�b�g�����`���[
		GUNTYPE_FLAMESHOT,							// �t���C���V���b�g
		GUNTYPE_GRENADE,							// �O���l�[�h
		GUNTYPE_MAX									// �e�̎�ނ̍ő吔
	};

	CGun(OBJ_TYPE type);							// �R���X�g���N�^
	~CGun();										// �f�X�g���N�^

	/* �����o�֐� */
	virtual HRESULT			Init();					// ������
	virtual void			Uninit();				// �I��
	virtual void			Update();				// �X�V
	virtual void			Draw();					// �`��
	virtual void			DebugInfo();			//�f�o�b�O

	/* �ÓI�����o�֐� */
	static	CGun			*Create(D3DXMATRIX *mtx);		// �e�̐���

	/* �����o�֐� */
	GUN_TYPE				&GetGunType() { return m_GunType; };				// �e�̎�ނ̎擾
	void					SetGunType(GUN_TYPE type);							// �e�̎�ނ̐ݒ�
	BULLET_TYPE				&GetBulletType() { return m_BulletType; };				// �e�̎�ނ̎擾
	void					SetBulletType(BULLET_TYPE type) { m_BulletType = type; };	// �e�̎�ނ̐ݒ�

	void					Shot(D3DXVECTOR3 rot);								// �e�̔���

private:
	/* �����o�֐� */
	void					MultipleShot();			// ������������
	/* �����o�ϐ� */
	GUN_TYPE				m_GunType;				// �K���̎��
	BULLET_TYPE				m_BulletType;			// �e�̎��
	int						m_nAmmo;				// �e��
	int						m_nInterval;			// �C���^�[�o��
	D3DXMATRIX				*m_mtx;					// �}�g���b�N�X
	bool					m_bMultiple;			// �������t���O
	D3DXVECTOR3				m_rot;					// ��]
	int						m_nCntFrame;			// �t���[���J�E���g
	int						m_nCntBullet;			// �e�̃J�E���g
};
#endif
