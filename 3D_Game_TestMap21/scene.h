// =====================================================================================================================================================================
//
// �V�[���̏��� [scene.h]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

#include "main.h"
#include "manager.h"

// =====================================================================================================================================================================
// �}�N����`
// =====================================================================================================================================================================
#define		MAX_SCENE		(128)

// =====================================================================================================================================================================
// �I�u�W�F�N�g�N���X
// =====================================================================================================================================================================
class CScene
{
public:
	// �`�揇
	enum PRIORITY
	{
		PRIORITY_NONE = -1,
		PRIORITY_BG,												 // �w�i
		PRIORITY_ITEM,												 // �A�C�e��
		PRIORITY_WALL,												 // ��
		PRIORITY_MODEL,												 // ���f��
		PRIORITY_2DOBJECT,											 // 2D�I�u�W�F�N�g
		PRIORITY_EFFECT,											 // �G�t�F�N�g
		PRIORITY_UI,												 // UI
		PRIORITY_MAX,
	};

	CScene();										// �R���X�g���N�^
	CScene(PRIORITY Priority);						// �R���X�g���N�^
	virtual~CScene();								// �f�X�g���N�^

	/* �����o�֐� */
	virtual void	Init() = 0;						// ������
	virtual void	Uninit() = 0;					// �I��
	virtual void	Update() = 0;					// �X�V
	virtual void	Draw() = 0;						// �`��
	virtual void	SetPos(D3DXVECTOR3 pos) = 0;	// �Z�b�g�|�W�V����

	/* �ÓI�����o�֐� */
	static void		ReleaseAll();					// �I�u�W�F�N�g�̔j��
	static void		UpdateAll();					// �I�u�W�F�N�g�̍X�V
	static void		DrawAll();						// �I�u�W�F�N�g�̕`��
	static	void	SetPauseStop(bool stop);		// �|�[�Y�Ŏ~�߂�ݒ�

	/* �����o�֐� */
	void			Release();						// ���

private:
	/* �����o�֐� */
	void			Death(void);						// ���S�t���O��ɊJ��
	/* �ÓI�����o�ϐ� */
	static int		m_nNumAll;							// ����
	static CScene	*m_apTop[CScene::PRIORITY_MAX];		// �擪�I�u�W�F�N�g�ւ̃|�C���^
	static CScene	*m_apCur[CScene::PRIORITY_MAX];		// ����(�Ō��)�I�u�W�F�N�g�ւ̃|�C���^
	static	bool	m_bStop;							// �~�߂�t���O

	/* �����o�ϐ� */
	int				m_nID;								// �����̔ԍ�
	CScene			*m_apPrev;	// �O�̃I�u�W�F�N�g�ւ̃|�C���^
	CScene			*m_apNext;	// ���̃I�u�W�F�N�g�ւ̃|�C���^
	bool			m_bDeath;							// ���S�t���O
	PRIORITY		m_priority;							// �D�揇��
};
#endif
