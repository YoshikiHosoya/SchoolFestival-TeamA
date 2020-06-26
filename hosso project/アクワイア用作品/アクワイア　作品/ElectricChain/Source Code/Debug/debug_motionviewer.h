//------------------------------------------------------------------------------
//
//���[�V�����r���[���p����  [CDebug_MotionViewer.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _DEBUG_MOTIONVIEWER_H_
#define _DEBUG_MOTIONVIEWER_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "../main.h"
#include "../basemode.h"
//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
//�O���錾
class CDebug_Character;

class CDebug_MotionViewer : public CBaseMode
{
public:
	//�Q�[���̏�ԑJ��
	enum STATE
	{
		STATE_NONE = -1,				//�n�܂��ĂȂ�
		STATE_NORMAL,					//�ʏ��ԁ@�M��
		STATE_DEBUG,					//�f�o�b�O���
		STATE_MAX
	};

	CDebug_MotionViewer();
	~CDebug_MotionViewer();
	HRESULT Init(HWND hWnd);			//������
	void Uninit();						//�I��
	void Update();						//�X�V
	void Draw();						//�`��
	void ShowDebugInfo();				//�f�o�b�O���\�L

	void SetGamestate(STATE gamestate);	//�Q�[���̏�Ԑݒ�
	STATE GetGamestate();				//�Q�[���̏�Ԏ擾
	CDebug_Character *GetDebugChara() { return m_pCharacter.get(); };	//�L�����N�^�[�̃f�[�^�擾

	CPlayer* GetPlayer() { return nullptr; };

private:
	std::shared_ptr<CDebug_Character> m_pCharacter;		//�L�����N�^�[�ւ̃|�C���^
	STATE m_State;										//�Q�[���X�e�[�g
	int m_nCntState;									//�X�e�[�g�̃J�E���^

	int m_nModelType;									//���f���̃^�C�v
	int m_nParamText;									//�p�����[�^

	void DebugCommand();								//�f�o�b�O�p�̏���
};

#endif