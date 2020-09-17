// =====================================================================================================================================================================
//
// �O���l�[�h���˂̏��� [grenadefire.h]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#ifndef _GRENADEFIRE_H_
#define _GRENADEFIRE_H_

// =====================================================================================================================================================================
// �C���N���[�h�t�@�C��
// =====================================================================================================================================================================
#include "main.h"
#include "scene.h"
#include "bullet.h"

// =====================================================================================================================================================================
// �O���l�[�h���˃N���X
// =====================================================================================================================================================================
class CGrenadeFire : public CScene, public CGameObject
{
public:
	// �O���l�[�h�̎��
	enum GRENADE_TYPE
	{
		HAND_GRENADE = 0,				// ��֒e
		TANK_GRENADE,					// ��Ԃ̃O���l�[�h
		DROP_BOMB,						// �h���b�v�{��
		GRENADE_TYPE_MAX
	};

	CGrenadeFire(OBJ_TYPE type);							// �R���X�g���N�^
	~CGrenadeFire();										// �f�X�g���N�^

	/* �����o�֐� */
	HRESULT						Init();						// ������
	void						Uninit();					// �I��
	void						Update();					// �X�V
	void						Draw();						// �`��
	void						DebugInfo(void);			// �f�o�b�O

	/* �ÓI�����o�֐� */
	static	CGrenadeFire		*Create(D3DXMATRIX *mtx, GRENADE_TYPE type);	// �O���l�[�h���ʒu�̐���

	/* �����o�֐� */
	void						Fire(D3DXVECTOR3 rot);					// �O���l�[�h�����
	int							GetGrenadeAmmo() { return m_nAmmo; };	// �O���l�[�h�̎c�e���擾
	void						SetGrenadeAmmoDefault();				// �O���l�[�h�̒e��������
	void						GrenadeAddAmmo();						// �O���l�[�h�̒e���ǉ�

private:
	/* �����o�֐� */
	void						MultipleFire();						// ������������
	void						ProcessReduceMultipleGrenade();		// �����������O���l�[�h�����炷����

	/* �����o�ϐ� */
	int							m_nAmmo;					// �c�e��
	int							m_nInterval;				// �C���^�[�o��
	D3DXMATRIX					*m_mtx;						// �}�g���b�N�X
	GRENADE_TYPE				m_type;						// �O���l�[�h�̎��
	bool						m_bMultiple;				// �������t���O
	int							m_nCntFrame;				// �t���[���J�E���g
	int							m_nCntGrenade;				// �O���l�[�h�̃J�E���g
	CBullet::BULLET_PARAM		*m_pBulletParam;			// �e(�O���l�[�h)�̃p�����[�^�[
	D3DXVECTOR3					m_rot;						// ��]
};
#endif