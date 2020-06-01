//------------------------------------------------------------------------------
//
//�`���[�g���A������  [tutorial.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "basemode.h"

//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CScene2D;
class CPlayer;

class CTutorial : public CBaseMode
{

public:
	CTutorial();
	~CTutorial();
	enum TUTORIAL_STEP
	{
		TUTORIAL_NONE = -1,						//
		TUTORIAL_MOVE,							//�ړ�
		TUTORIAL_DASH,							//�_�b�V��
		TUTORIAL_CAMERAMOVE,					//�J��������
		TUTORIAL_CAMERARESET,					//���_���Z�b�g
		TUTORIAL_JUMP,							//�W�����v
		TUTORIAL_ATTACK,						//�ʏ�U��
		TUTORIAL_START_CHAIN,					//�g�h��
		TUTORIAL_CHAINTHUNDER,					//�A�������̐���
		TUTORIAL_FREE,							//���R
		TUTORIAL_END,							//�`���[�g���A�������܂�
		TUTORIAL_MAX,							//
	};

	HRESULT Init(HWND hWnd);					//������
	void Uninit();								//�I��
	void Update();								//�X�V
	void Draw();								//�`��
	void ShowDebugInfo();						//�f�o�b�O���\�L
private:
	TUTORIAL_STEP m_step;								//���݂̍���

	std::shared_ptr<CScene2D> m_pTutorialStep;			//�`���[�g���A���̃|���S���ւ̃|�C���^
	std::shared_ptr<CPlayer> m_pPlayer;					//�v���C���[�̃|�C���^
	std::shared_ptr<CScene2D> m_pOK;					//OK! �̃|�C���^
	CPlayer* GetPlayer();								//�v���C���[�̃|�C���^�擾�֐�

	bool m_bClear;						//�N���A���
	bool m_bEnemyPop;					//�G�o�������邩
	int m_nEnemyPopTime;				//�G�o���J�E���g
	int m_nCntStep;						//���̍��ڂɈڍs���鎞�̃C���^�[�o���p�̃J�E���g

	void CheckTutorialAction();			//�A�N�V�������Ă邩�`�F�b�N
	void ActionClear();					//�A�N�V�����N���A
	void NextStep();					//���̃X�e�b�v�Ɉڍs
	void TutorialEnemyPop();			//�`���[�g���A���p�ɓG���|�b�v
};
#endif