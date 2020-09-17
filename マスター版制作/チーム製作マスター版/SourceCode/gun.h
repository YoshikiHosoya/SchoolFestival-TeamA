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
class CGun : public CModel, public CGameObject
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
		GUNTYPE_TANKGUN,							// ��Ԃ̏e
		GUNTYPE_PLANEGUN,							// �퓬�@�̏e
		GUNTYPE_HELIGUN,							// �w���̏e
		GUNTYPE_BALKAN,								// �o���J��
		GUNTYPE_FLAMETHROWER,						// �Ή����ˊ�
		GUNTYPE_INCENDIARY,							// �ĈΒe
		GUNTYPE_HANDGRENADE,						// �蓊���O���l�[�h
		GUNTYPE_TANKGRENADE,						// ��Ԃ̃O���l�[�h

		GUNTYPE_TRACKINGGUN,						// �Ǐ]�e
		GUNTYPE_DIFFUSIONGUN,						// �g�U�e
		GUNTYPE_BOSSLASERGUN,						// �{�X�p�̃��[�U�[�K��
		GUNTYPE_HANDGUN_ENEMY,						// �G�̃n���h�K��
		GUNTYPE_MISSILE,							// �~�T�C��
		GUNTYPE_FLAMEBULLET,						// �t���C���o���b�g
		GUNTYPE_DROPBOMB,							// �h���b�v�{��

		GUNTYPE_MAX									// �e�̎�ނ̍ő吔
	};

	CGun();											// �R���X�g���N�^
	~CGun();										// �f�X�g���N�^

	/* �����o�֐� */
	virtual HRESULT		Init();					// ������
	virtual void		Uninit();				// �I��
	virtual void		Update();				// �X�V
	virtual void		Draw();					// �`��
	virtual void		DebugInfo();			//�f�o�b�O

	/* �ÓI�����o�֐� */
	static	CGun		*Create();		// �e�̐���
	void				NoDrawCalcMatrixOnly();			// �}�g���b�N�X�̌v�Z

	/* �����o�֐� */
	GUN_TYPE			&GetGunType()				{ return m_GunType; };				// �e�̎�ނ̎擾
	int					GetGunAmmo()				{ return m_nAmmo; };				// �e�̎c�e���擾
	D3DXVECTOR3			GetShotOffsetPos()			{ return m_ShotOffsetPos; };		// ���ˈʒu�̃I�t�Z�b�g�̎擾
	D3DXVECTOR3			GetShotRot()				{ return m_ShotRot; };				// ���Ƃ��̉�]�̌����̎擾
	D3DXVECTOR3			GetShotVec()				{ return m_Shotvector; };			// ���Ƃ��̌����̎擾
	D3DXVECTOR3			GetShotPos()				{ return m_ShotPos; };				// ���Ƃ��̍��W�擾
	D3DXVECTOR3			*GetShotPosPtr()			{ return &m_ShotPos; };				// ���Ƃ��̍��W�̃|�C���^�擾

	void				SetGunType(GUN_TYPE type);															// �e�̎�ނ̐ݒ�
	void				GunAddAmmo(GUN_TYPE type);															// �e���̉��Z
	void				SetGunTypeOnly(GUN_TYPE type)				{ m_GunType = type; };					// �e�̎�ނ����ύX
	void				SetHandMtx(D3DXMATRIX *pMtx)				{ m_HasHandMtx = pMtx; };				// ��̃}�g���b�N�X�ݒ�
	void				SetShotOffsetPos(D3DXVECTOR3 ShotOffsetPos)	{ m_ShotOffsetPos = ShotOffsetPos; };	// ���ˈʒu�̃I�t�Z�b�g�̐ݒ�
	void				SetShotRot(D3DXVECTOR3 ShotRot)				{ m_ShotRot = ShotRot; };				// ���Ƃ��̉�]�̌����̐ݒ�
	void				SetShotVec(D3DXVECTOR3 ShotVec)				{ m_Shotvector = ShotVec; };			// ���Ƃ��̌����̐ݒ�
	void				SetMtxWorld(D3DXMATRIX *mtx)				{ m_HasHandMtx = mtx; };				// �}�g���b�N�X�̐ݒ�
	void				SetMoveZero(bool bMoveZero)					{ m_bMoveZero = bMoveZero; };			// �ړ��𖳌��ɂ��邩�̐ݒ�
	void				Shot();																				// �e�̔���

private:
	/* �����o�֐� */
	void				MultipleShot();						// ������������
	void				ProcessReduceMultipleBullet();		// �����������e�����炷����

	/* �����o�ϐ� */
	GUN_TYPE			m_GunType;				// �K���̎��
	GUN_TYPE			m_GunTypeOld;			// �O��̃K���̎��
	int					m_nAmmo;				// �e��
	int					m_nInterval;			// �C���^�[�o��
	D3DXMATRIX			*m_HasHandMtx;			// ������̃}�g���b�N�X
	bool				m_bMultiple;			// �������t���O
	D3DXVECTOR3			m_ShotPos;				// ���ˈʒu
	D3DXVECTOR3			m_ShotOffsetPos;		// ���ˈʒu�̃I�t�Z�b�g
	D3DXVECTOR3			m_ShotRot;				// ���Ƃ��̉�]�̌���
	D3DXVECTOR3			m_Shotvector;			// ���Ƃ��̑��x
	int					m_nCntFrame;			// �t���[���J�E���g
	int					m_nCntBullet;			// �e�̃J�E���g
	bool				m_bMoveZero;			// �ړ��𖳌��ɂ���t���O
};
#endif
