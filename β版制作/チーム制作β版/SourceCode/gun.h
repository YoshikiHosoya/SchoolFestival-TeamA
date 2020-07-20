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
		GUNTYPE_TANKGUN,							// ��Ԃ̏e
		GUNTYPE_PLANEGUN,							// �퓬�@�̏e
		GUNTYPE_HELIGUN,							// �w���̏e
		GUNTYPE_GRENADE,							// �O���l�[�h
		GUNTYPE_MAX									// �e�̎�ނ̍ő吔
	};

	CGun(OBJ_TYPE type);							// �R���X�g���N�^
	~CGun();										// �f�X�g���N�^

	/* �����o�֐� */
	virtual HRESULT		Init();					// ������
	virtual void		Uninit();				// �I��
	virtual void		Update();				// �X�V
	virtual void		Draw();					// �`��
	virtual void		DebugInfo();			//�f�o�b�O

	/* �ÓI�����o�֐� */
	static	CGun		*Create(D3DXMATRIX *mtx);		// �e�̐���

	/* �����o�֐� */
	GUN_TYPE			&GetGunType()				{ return m_GunType; };				// �e�̎�ނ̎擾
	TAG					&GetTag()					{ return m_Tag; };					// �^�O�̎擾
	bool				GetDrawFlag()				{ return m_bDraw; };				// �`��t���O�̎擾
	int					GetGunAmmo()				{ return m_nAmmo; };				// �e�̎c�e���擾
	D3DXVECTOR3			GetShotOffsetPos()			{ return m_ShotOffsetPos; };		// ���ˈʒu�̃I�t�Z�b�g�̎擾
	D3DXVECTOR3			GetShotRot()				{ return m_ShotRot; };				// ���Ƃ��̉�]�̌����̎擾

	void				SetGunType(GUN_TYPE type);															// �e�̎�ނ̐ݒ�
	void				SetDrawFlag(bool bflag)						{ m_bDraw = bflag; };					// �`��t���O�̐ݒ�
	void				SetTag(TAG type)							{ m_Tag = type; };						// �^�O�̐ݒ�
	void				SetShotOffsetPos(D3DXVECTOR3 ShotOffsetPos)	{ m_ShotOffsetPos = ShotOffsetPos; };	// ���ˈʒu�̃I�t�Z�b�g�̐ݒ�
	void				SetShotRot(D3DXVECTOR3 ShotRot)				{ m_ShotRot = ShotRot; };				// ���Ƃ��̉�]�̌����̐ݒ�
	void				SetMtxWorld(D3DXMATRIX *mtx)				{ m_mtx = mtx; };						// �}�g���b�N�X�̐ݒ�
	void				AddAmmo(int nAmmo)							{ m_nAmmo += nAmmo; };					// �e���̉��Z
	void				Shot();																				// �e�̔���
private:
	/* �����o�֐� */
	void				MultipleShot();			// ������������
	/* �����o�ϐ� */
	GUN_TYPE			m_GunType;				// �K���̎��
	TAG					m_Tag;					// �^�O
	int					m_nAmmo;				// �e��
	int					m_nInterval;			// �C���^�[�o��
	D3DXMATRIX			*m_mtx;					// �}�g���b�N�X
	bool				m_bMultiple;			// �������t���O
	D3DXVECTOR3			m_ShotPos;				// ���ˈʒu
	D3DXVECTOR3			m_ShotOffsetPos;		// ���ˈʒu�̃I�t�Z�b�g
	D3DXVECTOR3			m_ShotRot;				// ���Ƃ��̉�]�̌���
	int					m_nCntFrame;			// �t���[���J�E���g
	int					m_nCntBullet;			// �e�̃J�E���g
	bool				m_bDraw;				// ���f���̕\����\��
};
#endif
