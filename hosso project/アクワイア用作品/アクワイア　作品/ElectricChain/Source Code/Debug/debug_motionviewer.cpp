//------------------------------------------------------------------------------
//
//�f�o�b�O�@���[�V�����r���[���p�̏���  [debug_motionviewer.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "debug_motionviewer.h"
#include "debug_character.h"
#include "../manager.h"
#include "../renderer.h"
#include "../keyboard.h"
#include "../camera.h"
#include "../orbit.h"
#include "../fade.h"
#include "../Map.h"
//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------
#define DEFAULT_PLAYER_POS (ZeroVector3)
#define DEFAULT_SCORE_POS (D3DXVECTOR3(1150.0f, 50.0f, 0.0f))

//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CDebug_MotionViewer::CDebug_MotionViewer()
{
	m_nCntState = 0;
	m_State = CDebug_MotionViewer::STATE_NORMAL;
	SetGamestate(CDebug_MotionViewer::STATE_NORMAL);
	m_nModelType = 0;
	m_nParamText = 0;
}
//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CDebug_MotionViewer::~CDebug_MotionViewer()
{

}

//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CDebug_MotionViewer::Init(HWND hWnd)
{
	//������
	m_State = STATE_NORMAL;
	m_nCntState = 0;

	//�J�������W�ݒ�
	CManager::GetRenderer()->GetCamera()->SetCameraPos(DEFAULT_PLAYER_POS, DEFAULT_PLAYER_POS + D3DXVECTOR3(0.0f, 300.0f, -500.0f));
	CManager::GetRenderer()->GetCamera()->SetState(CCamera::CAMERA_DEBUG);
	//�}�b�v
	CMap::Create();

	return S_OK;
}

//------------------------------------------------------------------------------
//�I������
//------------------------------------------------------------------------------
void CDebug_MotionViewer::Uninit()
{

	if (m_pCharacter)
	{
		m_pCharacter->Release();
		m_pCharacter = nullptr;
	}

	//�I������
	CScene::ReleaseAll();
}

//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CDebug_MotionViewer::Update()
{
	//debug����
	DebugCommand();

	// �L�[�{�[�h�̃|�C���^
	CKeyboard *pKeyboard = CManager::GetKeyboard();

	//�Q�[���̏�Ԃŏ�����ς���
	switch (m_State)
	{
		//�ʏ펞
	case CDebug_MotionViewer::STATE_NORMAL:


		break;

	}
}

//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void CDebug_MotionViewer::Draw()
{

}
//------------------------------------------------------------------------------
//�f�o�b�O���\�L
//------------------------------------------------------------------------------
void CDebug_MotionViewer::ShowDebugInfo()
{
#ifdef _DEBUG
	CDebugProc::Print(CDebugProc::PLACE_LEFT, "------------ MotionViewer ----------------\n");
	CDebugProc::Print(CDebugProc::PLACE_LEFT, "ImGui�E�B���h�E�Ń��f���I��\n");
	CDebugProc::Print(CDebugProc::PLACE_LEFT, "[F5] : MotionViewer�N��\n");

	//���f���̎��
	if (ImGui::InputInt("ModelType", &m_nModelType))
	{
		CHossoLibrary::RangeLimit_Equal_Int(m_nModelType, 0, MODEL_MAX - 1);
	}
	//�p�����[�^
	if (ImGui::InputInt("ParamText", &m_nParamText))
	{
		CHossoLibrary::RangeLimit_Equal_Int(m_nParamText, 0, CCharacter::PARAM_MAX - 1);
	}

#endif
}

//------------------------------------------------------------------------------
//�Q�[���X�e�[�g�Z�b�g
//------------------------------------------------------------------------------
void CDebug_MotionViewer::SetGamestate(STATE gamestate)
{
	//�X�e�[�g���i��ł���ꍇ
	if (m_State != CDebug_MotionViewer::STATE_NONE)
	{
		//�X�e�[�g�ύX
		m_State = gamestate;

		switch (gamestate)
		{
		case STATE_NORMAL:
			if (m_pCharacter)
			{
				m_pCharacter->Release();
				m_pCharacter = nullptr;
			}
			CScene::SetStop(false);
			break;

		case CDebug_MotionViewer::STATE_DEBUG:
			CScene::SetStop(true);

			m_pCharacter = CDebug_Character::Create((MODEL_TYPE)m_nModelType,(CCharacter::PARAM_TYPE)m_nParamText);

			break;
		}
	}
}
//------------------------------------------------------------------------------
//�Q�[���X�e�[�g�擾
//------------------------------------------------------------------------------
CDebug_MotionViewer::STATE CDebug_MotionViewer::GetGamestate()
{
	return m_State;
}

//------------------------------------------------------------------------------
//�f�o�b�O����
//------------------------------------------------------------------------------
void CDebug_MotionViewer::DebugCommand()
{
#ifdef _DEBUG

	CKeyboard *pKeyboard = CManager::GetKeyboard();

	//[ENTER]�L�[����������
	if (pKeyboard->GetPress(DIK_9))
	{
		//�X�e�[�g�ύX
		CManager::GetRenderer()->GetFade()->SetModeFade(CManager::MODE_GAME);
		return;

	}

	//Debug
	if (pKeyboard->GetTrigger(DIK_F5))
	{
		if (m_State == STATE_DEBUG)
		{
			CDebug_MotionViewer::SetGamestate(STATE_NORMAL);
		}
		else
		{
			CDebug_MotionViewer::SetGamestate(STATE_DEBUG);
		}
	}
#endif // _DEBUG

}