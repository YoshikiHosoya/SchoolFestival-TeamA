// =====================================================================================================================================================================
//
// ���U���gUI�̏��� [resultUI.h]
// Author : fujiwara masato
//
// =====================================================================================================================================================================
#ifndef _RESULTUI_H_
#define _RESULTUI_H_

// =====================================================================================================================================================================
// �C���N���[�h�t�@�C��
// =====================================================================================================================================================================
#include "main.h"
#include "UI.h"
#include "game.h"
#include "resultmanager.h"

// =====================================================================================================================================================================
// �O���錾
// =====================================================================================================================================================================
class CScene2D;
class CMultiNumber;

// =====================================================================================================================================================================
// ���U���gUI�N���X
// =====================================================================================================================================================================
class CResultUI : CUI
{
public:
	// ���U���gUI�̎��
	enum RESULT_UI
	{
		RESULT_UI_BG,				// �w�i
		RESULT_UI_NAME,				// ���U���g�̖��O
		RESULT_UI_1P,				// 1�v���C���[
		RESULT_UI_2P,				// 2�v���C���[
		RESULT_UI_EVALUATION01P,	// �]��0
		RESULT_UI_EVALUATION11P,	// �]��1
		RESULT_UI_EVALUATION21P,	// �]��2
		RESULT_UI_EVALUATION02P,	// �]��0
		RESULT_UI_EVALUATION12P,	// �]��1
		RESULT_UI_EVALUATION22P,	// �]��2
		RESULT_UI_MISSIONCOMP1,		// �~�b�V�����N���A1
		RESULT_UI_MISSIONCOMP2,		// �~�b�V�����N���A2
		RESULT_UI_MAX
	};

	CResultUI();							// �R���X�g���N�^
	~CResultUI();							// �f�X�g���N�^

	/* �����o�֐� */
	HRESULT					Init(void);		// ������
	void					Uninit(void);	// �I��
	void					Update(void);	// �X�V
	void					Draw(void);		// �`��

	/* �ÓI�����o�֐� */
	static  CResultUI		*Create();									// ���U���gUI�̐���
	static	int				GetTotalScore() { return m_nTotalScore; };	// �g�[�^���X�R�A�̎擾
	static	void			TotalScoreCalculation();					// �Q�[���X�R�A�ƃ{�[�i�X�X�R�A�̌v�Z

	/* �����o�֐� */

private:
	/* �����o�֐� */
	void					DrawConditions(CResultManager::RESULT_STATE state);	// �`�����
	void					ResultUICreate();									// ���U���gUI���܂Ƃ߂Đ�������
	void					AllDraw();											// �S�ĕ`��
	void					AllNotDraw();										// �S�ĕ`�悵�Ȃ�
	void					Result0Draw();										// 0�Ԗڂ̃��U���g�ŕ\������UI�̐ݒ�
	void					Result1Draw();										// 1�Ԗڂ̃��U���g�ŕ\������UI�̐ݒ�
	void					ScoreCal();											// �}���`�i���o�[�ɒl����
	void					Conditions();										// �����ɂ���ď�����i�߂�
	void					TargetValue(const int &Target,
										int &Value,
										int Add,
										CMultiNumber *pMultiNumber);			// �ڕW�̒l�ɂȂ�܂Œl���v�Z����

	void					SetWaitTime(int time) { m_nWaitTime = time; };		// �҂����Ԃ̐ݒ�
	void					WaitTime(int nTime, bool &bFlag,bool &bUse);		// �҂����Ԃ̌v�Z
	void					ResultUiOrder(bool bUse0, bool bUse1, bool bUse2);	// Ui�̏o������
	void					Flashing(CScene2D *m_apScene2D);					// �_�ŏ���

	/* �ÓI�����o�ϐ� */
	static LPDIRECT3DTEXTURE9	m_TexNum[RESULT_UI_MAX];						// �o�C���h����e�N�X�`���̏��
	static D3DXVECTOR3			m_Pos[RESULT_UI_MAX];							// ���W���
	static D3DXVECTOR3			m_Size[RESULT_UI_MAX];							// �T�C�Y���
	static int					m_nTotalScore;									// �X�R�A�ƃ{�[�i�X�����Z�����X�R�A
	static int					m_nBonusScore;									// �{�[�i�X�X�R�A
	static int					m_PlayerScore;									// �Q�[�����[�h�ŉ҂����X�R�A

	/* �����o�ϐ� */
	CScene2D				*m_apScene2D[RESULT_UI_MAX];						// �V�[��2D�̃|�C���^
	CMultiNumber			*m_pPrisonerNum;									// �v���C���[�̎c�@�̐���UI
	CMultiNumber			*m_pBonusScore;										// �{�[�i�X�X�R�A��UI

	int						m_nPrisonerNum;										// �v���C���[�̎c�@�̐�
	bool					m_bPrisonerNum;										// �ߗ��̐���\���X�V���Ă������ǂ���
	bool					m_bBonusScore;										// �ǉ����_��\���X�V���Ă������ǂ���
	bool					m_bEvaluation;										// �]����\�����Ă������ǂ���
	int						m_nWaitTime;										// ���̏���������܂ł̎���
	bool					m_bWaitFlag;										// �҂����Ԃ����������ۂɎg���t���O
	int						m_nColCnt;											// �J���[�J�E���g

	bool					m_bUseUIFlag[3];									// UI���o�������邽�߂̃t���O 3�s�����邽��
	bool					m_bUse_One[3];										// ������1�x�����ʂ����߂̃t���O
};
#endif