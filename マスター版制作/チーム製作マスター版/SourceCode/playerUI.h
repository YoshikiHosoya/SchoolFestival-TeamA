// =====================================================================================================================================================================
//
// �v���C���[UI�̏��� [playerUI.h]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#ifndef _PLAYERUI_H_
#define _PLAYERUI_H_

// =====================================================================================================================================================================
// �C���N���[�h�t�@�C��
// =====================================================================================================================================================================
#include "main.h"
#include "UI.h"
#include "gun.h"

// =====================================================================================================================================================================
// �}�N����`
// =====================================================================================================================================================================
// =====================================================================================================================================================================
// �O���錾
// =====================================================================================================================================================================
class CScene2D;
class CMultiNumber;
class CPlayerGSUI;
// =====================================================================================================================================================================
// �v���C���[UI�N���X
// =====================================================================================================================================================================
class CPlayerUI : CUI
{
public:
	// �v���C���[UI�̎��
	enum PLAYER_UI
	{
		FRAME,						// �g
		STOCK_LETTER,				// �c�@		( ���� )
		BULLET_AMMO_LETTER,			// �c�e�� ( ���� )
		GRENADE_AMMO_LETTER,		// �O���l�[�h�̎c�� ( ���� )
		LIFE_ICON,					// �̗̓A�C�R��
		INFINITY_AMMO,				// �e������
		SCORE_GETLETTER,			// ���肵���X�R�A�̒l
		PLAYER_UI_MAX
	};

	CPlayerUI();								// �R���X�g���N�^
	~CPlayerUI();								// �f�X�g���N�^

	/* �����o�֐� */
	HRESULT				Init(void);				// ������
	void				Uninit(void);			// �I��
	void				Update(void);			// �X�V
	void				Draw(void);				// �`��

	/* �ÓI�����o�֐� */
	static				CPlayerUI	*Create(TAG Tag);		// �v���C���[UI�̐���

	/* �����o�֐� */
	void				SetScore(int nScore);				// �X�R�A�̐ݒ�
	void				SetItemScore(int nScore, int playernum);// �A�C�e���X�R�A�̐ݒ�

	void				SetBulletAmmo(int nBulletAmmo, CGun::GUN_TYPE GunType);		// �c�e���̐ݒ�
	void				SetGrenadeAmmo(int nGrenadeAmmo);	// �O���l�[�h�̎c���̐ݒ�
	void				SetLifeUI(int nLife);				// �̗�UI�̐ݒ�
	void				SetStockUI(int nStock);				// �c�@�̐��̐ݒ�
	void				SetTimeUI(int nTime);				// �c�莞�Ԃ̐ݒ�

	int					GetScore() { return m_nScore; };	// �X�R�A�̎擾
	int					GetTime() { return m_nTime; };		// ���Ԃ̎擾
	int					GetStock() { return m_nStock; };	// �c�@�̎擾
	void				DecrementTime();					// ���Ԃ̌���
	void				ResetTime();						// ���Ԃ̃��Z�b�g
private:
	/* �ÓI�����o�֐� */

	/* �����o�֐� */
	void				PlayerUICreate(TAG Tag);	// �v���C���[UI�̐���

	/* �ÓI�����o�ϐ� */

	/* �����o�ϐ� */
	CScene2D					*m_apScene2D[PLAYER_UI_MAX];	// �V�[��2D�̃|�C���^
	CPlayerGSUI					*m_pPGSUI;						// �\���X�R�A�̃|�C���^
	CMultiNumber				*m_pScore;						// �X�R�A�̃|�C���^
	CMultiNumber				*m_pBulletAmmo;					// �c�e���̃|�C���^
	CMultiNumber				*m_pGrenadeAmmo;				// �O���l�[�h�̎c���̃|�C���^
	CMultiNumber				*m_pLife;						// �̗͂̎c���̃|�C���^
	CMultiNumber				*m_pStock;						// �c�@�̐��̃|�C���^
	CMultiNumber				*m_pTime;						// �Q�[���̎c�莞��
	int							m_nScore;						// �X�R�A
	int							m_nBulletAmmo;					// �c�e��
	int							m_nGrenadeAmmo;					// �O���l�[�h�̎c��
	int							m_nLife;						// �̗�
	int							m_nStock;						// �c�@�̐�
	int							m_nTime;						// �c�莞��

	float						m_PLAYER_2_UI_FramePos;				// �v���C���[2�̘g�̈ʒu
	float						m_PLAYER_2_UI_ScorePos;				// �v���C���[2�̃X�R�A�̈ʒu
	float						m_PLAYER_2_UI_LifePos;				// �v���C���[2�̗̑͂̈ʒu
};
#endif