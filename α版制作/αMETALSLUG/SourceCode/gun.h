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
	enum GUN_TYPE
	{
		GUNTYPE_HANDGUN = 0,						// �n���h�K��
		GUNTYPE_HEAVYMACHINEGUN,					// �w�r�[�}�V���K��
		GUNTYPE_SHOTGUN,							// �V���b�g�K��
		GUNTYPE_LASERGUN,							// ���[�U�[�K��
		GUNTYPE_ROCKETLAUNCHER,						// ���P�b�g�����`���[
		GUNTYPE_FLAMESHOT,							// �t���C���V���b�g
		GUNTYPE_TANKTURRET,							// ��ԖC��
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
	TAG						&GetTag() { return m_Tag; };						// �^�O�̎擾
	void					SetTag(TAG type) { m_Tag = type; };					// �^�O�̐ݒ�

	bool					GetDrawFlag()				{ return m_bDraw; };	// �`��t���O�̎擾
	void					SetDrawFlag(bool bflag)		{ m_bDraw = bflag; };	// �`��t���O�̐ݒ�

	void					Shot(D3DXVECTOR3 rot);								// �e�̔���
	int						GetGunAmmo() { return m_nAmmo; };					// �e�̎c�e���擾

private:
	/* �����o�֐� */
	void					MultipleShot();			// ������������
	/* �����o�ϐ� */
	GUN_TYPE				m_GunType;				// �K���̎��
	TAG						m_Tag;					// �^�O
	int						m_nAmmo;				// �e��
	int						m_nInterval;			// �C���^�[�o��
	D3DXMATRIX				*m_mtx;					// �}�g���b�N�X
	bool					m_bMultiple;			// �������t���O
	D3DXVECTOR3				m_rot;					// ��]
	D3DXVECTOR3				m_ShotPos;				// ���ˈʒu
	int						m_nCntFrame;			// �t���[���J�E���g
	int						m_nCntBullet;			// �e�̃J�E���g
	bool					m_bDraw;				// ���f���̕\����\��
};
#endif
