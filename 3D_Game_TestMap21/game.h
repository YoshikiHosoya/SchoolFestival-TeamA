// =====================================================================================================================================================================
//
// �Q�[���̏��� [game.h]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"

// =====================================================================================================================================================================
// �O���錾	( �|�C���^�����Ȃ�g���� )
// =====================================================================================================================================================================
class	CManager;				// �}�l�[�W���[�N���X
class	CScore;					// �X�R�A�N���X
class	CScene3D;				// �V�[��3D�N���X
class	CSlope;					// ��N���X
class	CPlayer;				// �v���C���[�N���X
class	CObjectModel;			// �I�u�W�F�N�g�N���X
class	CEffect;				// �G�t�F�N�g�N���X
class	CGameUI;				// �Q�[��UI�N���X
class	CItem;					// �A�C�e���N���X
class	CObject2D;				// 2D�I�u�W�F�N�g�N���X

// =====================================================================================================================================================================
// �Q�[���N���X
// =====================================================================================================================================================================
class CGame
{
public:

	// �Q�[�����[�h
	enum GAME_MODE
	{
		GAME_MODE_NONE = -1,
		GAME_MODE_MAIN,											// ���C��
		GAME_MODE_END,											// �Q�[���G���h
		GAME_MODE_CLEAR,										// �N���A
		GAME_MODE_MAX,
	};

	CGame();													// �R���X�g���N�^
	~CGame();													// �f�X�g���N�^

	/* �����o�֐� */
	HRESULT					Init();								// ������
	void					Uninit();							// �I��
	void					Update();							// �X�V
	void					Draw();								// �`��

	/* �ÓI�����o�֐� */
	static	CGame			*Create();							// �Q�[���N���X�̐���
	static	CScore			*GetScore();						// �X�R�A�̎擾
	static	CScene3D		*GetScene3D();						// �V�[��3D�̎擾
	static	CSlope			*GetSlope();						// ��̎擾
	static	CPlayer			*GetPlayer();						// �v���C���[�̎擾
	static	CItem			*GetItemModel();					// �A�C�e���̎擾
	static	CEffect			*GetEffect();						// �G�t�F�N�g�̎擾
	static	CGameUI			*GetGameUI();						// �Q�[��UI�̎擾
	static	GAME_MODE		GetGameMode();						// �Q�[�����[�h�̎擾

	/* �����o�֐� */
	void					SetGameMode(GAME_MODE GameMode)		{ m_GameMode = GameMode; };	// �Q�[�����[�h�̐ݒ�

private:
	/* �����o�֐� */
	void					LoadAll();							// �S�ēǂݍ���
	void					UnloadAll();						// ���ׂĔj��
	/* �ÓI�����o�ϐ� */
	static  CScore			*m_pScore;							// �X�R�A�N���X�̃|�C���^
	static	CSlope			*m_pSlope;							// ��̃|�C���^
	static	CScene3D		*m_pScene3D;						// �V�[��3D�̃|�C���^
	static	CPlayer			*m_pPlayer;							// �v���C���[�̃|�C���^
	static	CObjectModel	*m_pObjectModel;					// �I�u�W�F�N�g���f���̃|�C���^
	static	CItem			*m_pItem;							// �A�C�e���̃|�C���^
	static	CEffect			*m_pEffect;							// �G�t�F�N�g�̃|�C���^
	static  CGameUI			*m_pGameUI;							// �Q�[���N���X�̃|�C���^
	static  CObject2D		*m_pObject2D;						// 2D�I�u�W�F�N�g�̃|�C���^
	/* �����o�ϐ� */
	int						m_nCntTransition;					// �J�ڂ���܂ł̎���
	static	GAME_MODE		m_GameMode;							// �Q�[�����[�h
	bool					m_bDisplayGameEndUI;				// �Q�[���G���hUI�̕\���t���O
};
#endif
