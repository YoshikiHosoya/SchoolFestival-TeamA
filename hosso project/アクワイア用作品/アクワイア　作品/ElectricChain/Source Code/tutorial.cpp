//------------------------------------------------------------------------------
//
//�`���[�g���A������  [tutorial.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "tutorial.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"
#include "fade.h"
#include "Map.h"
#include "miniMap.h"
#include "UI.h"
#include "Pad_XInput.h"
#include "player.h"
#include "enemy.h"
#include "keyboard.h"
#include "camera.h"
#include "effectanimation2D.h"
//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------
#define DEFAULT_PLAYER_POS				(D3DXVECTOR3(0.0f, 0.0f, -800.0f))	//�������W
#define TUTORIAL_STEP_INTERVAL			(60)								//�`���[�g���A���̍��ڂ��N���A���Ă��玟�̍��ڂɓ���܂ł̃C���^�[�o��
#define ENEMY_POP_INTERVAL				(65)								//�G�o���܂ł̃C���^�[�o��
#define ENEMY_SPACE						(400)								//�`���[�g���A���p�̓G�̊��o
#define ENEMY_LINE						(INTEGER2(6,6))						//�`���[�g���A���p�̓G�̗�
//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CTutorial::CTutorial()
{
	//������
	m_pPlayer.reset();
	m_pTutorialStep.reset();
	m_pOK.reset();

	m_bEnemyPop = false;
	m_bClear = false;
	m_nEnemyPopTime = ENEMY_POP_INTERVAL;
	m_nCntStep = 0;
	m_step = CTutorial::TUTORIAL_NONE;
}
//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CTutorial::~CTutorial()
{
	m_pPlayer.reset();
	m_pTutorialStep.reset();
}
//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CTutorial::Init(HWND hWnd)
{
	//�}�b�v����
	CMap::Create();

	//�`���[�g���A����2D����
	m_pTutorialStep = CScene2D::Create_Shared(D3DXVECTOR3(640.0f, 80.0f, 0.0f), D3DXVECTOR3(600.0f, 120.0f, 0.0f), CScene::OBJTYPE_UI);

	//�v���C���[����
	m_pPlayer = CPlayer::Create(DEFAULT_PLAYER_POS);

	//�~�j�}�b�v����
	CMiniMap::Create();

	//�J�������W�ݒ�
	CManager::GetRenderer()->GetCamera()->SetCameraPos(DEFAULT_PLAYER_POS, DEFAULT_PLAYER_POS + D3DXVECTOR3(0.0f, 200, -600));
	CManager::GetRenderer()->GetCamera()->SetState(CCamera::CAMERA_GAME);

	//SKIP�R�}���h
	//�R���g���[�����ڑ�����Ă��邩�ǂ����Ńe�N�X�`�������ւ�
	CManager::GetXInput()->GetConnect() ?
		CScene2D_UI::Create(D3DXVECTOR3(1100.0f, 230.0f, 0.0f), D3DXVECTOR3(300.0f, 80.0f, 0.0f), WhiteColor, CTexture::TEX_UI_TUTORIAL_X_SKIP, CScene::OBJTYPE_2DUI):
		CScene2D_UI::Create(D3DXVECTOR3(1100.0f, 230.0f, 0.0f), D3DXVECTOR3(300.0f, 80.0f, 0.0f), WhiteColor, CTexture::TEX_UI_TUTORIAL_KEY_SKIP, CScene::OBJTYPE_2DUI);

	//�X�e�b�v�i�s
	NextStep();

	return S_OK;
}

//------------------------------------------------------------------------------
//�I������
//------------------------------------------------------------------------------
void CTutorial::Uninit()
{
	//�I������
	CScene::ReleaseAll();
}

//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CTutorial::Update()
{
	//�G�̑������S���Ȃ��ēG���o���\��Ԃ̂Ƃ�
	if (CEnemy::GetEnemyNum() <= 0 && m_bEnemyPop)
	{
		//�G�o���J�E���^
		m_nEnemyPopTime--;

		//�J�E���^��0�ɂȂ�����
		if (m_nEnemyPopTime < 0)
		{
			//�J�E���^���Z�b�g
			m_nEnemyPopTime = ENEMY_POP_INTERVAL;

			//�G����
			CEnemy::Create(D3DXVECTOR3(100.0f, 0.0f, 200.0f),CEnemy::TYPE_NORMAL);
			CEnemy::Create(D3DXVECTOR3(-100.0f, 0.0f, 200.0f), CEnemy::TYPE_NORMAL);
			CEnemy::Create(D3DXVECTOR3(0.0f, 0.0f, 300.0f), CEnemy::TYPE_STRONG);
			CEnemy::Create(D3DXVECTOR3(100.0f, 0.0f, 400.0f), CEnemy::TYPE_NORMAL);
			CEnemy::Create(D3DXVECTOR3(-100.0f, 0.0f, 400.0f), CEnemy::TYPE_NORMAL);
		}
	}

	//�N���A��Ԃ̂Ƃ�
	if (m_bClear)
	{
		//�J�E���g�_�E��
		m_nCntStep--;

		//�J�E���g��0�ɂȂ�����
		if (m_nCntStep <= 0)
		{
			//OK! ������
			m_pOK->Release();
			m_pOK.reset();

			//���̃X�e�b�v��
			NextStep();
		}
	}
	else
	{
		//�`���[�g���A���̃A�N�V�����`�F�b�N
		CheckTutorialAction();
	}

	//�`���[�g���A���X�L�b�v�{�^�������ꂽ
	if (CHossoLibrary::CheckSkipTutorial() && m_step != TUTORIAL_END)
	{
		m_step = TUTORIAL_END;
		m_pTutorialStep->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_TUTORIAL_END));
		CManager::GetSound()->Play(CSound::LABEL_SE_DECISION);
	}


}

//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void CTutorial::Draw()
{
}

//------------------------------------------------------------------------------
//�f�o�b�O�p
//------------------------------------------------------------------------------
void CTutorial::ShowDebugInfo()
{
#ifdef _DEBUG
	CKeyboard *pKeyboard = CManager::GetKeyboard();

	//debug
	if (pKeyboard->GetTrigger(DIK_L))
	{
		NextStep();
	}
#endif //_DEBUG
}

//------------------------------------------------------------------------------
//�`���[�g���A��
//------------------------------------------------------------------------------
void CTutorial::NextStep()
{
	//���̃X�e�b�v�Ɉڍs
	switch (m_step)
	{
	case CTutorial::TUTORIAL_NONE:
		m_step = TUTORIAL_MOVE;

		//�R���g���[�����ڑ�����Ă��邩�ǂ����Ńe�N�X�`�������ւ�
		CManager::GetXInput()->GetConnect() ?
			m_pTutorialStep->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_TUTORIAL_X_MOVE)) :
			m_pTutorialStep->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_TUTORIAL_KEY_MOVE));

		break;
	case CTutorial::TUTORIAL_MOVE:
		m_step = TUTORIAL_DASH;

		//�R���g���[�����ڑ�����Ă��邩�ǂ����Ńe�N�X�`�������ւ�
		CManager::GetXInput()->GetConnect() ?
			m_pTutorialStep->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_TUTORIAL_X_DASH)) :
			m_pTutorialStep->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_TUTORIAL_KEY_DASH));

		break;

	case CTutorial::TUTORIAL_DASH:
		m_step = TUTORIAL_CAMERAMOVE;

		//�R���g���[�����ڑ�����Ă��邩�ǂ����Ńe�N�X�`�������ւ�
		CManager::GetXInput()->GetConnect() ?
			m_pTutorialStep->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_TUTORIAL_X_CAMERAMOVE)) :
			m_pTutorialStep->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_TUTORIAL_KEY_CAMERAMOVE));

		break;

	case CTutorial::TUTORIAL_CAMERAMOVE:
		m_step = TUTORIAL_CAMERARESET;

		//�R���g���[�����ڑ�����Ă��邩�ǂ����Ńe�N�X�`�������ւ�
		CManager::GetXInput()->GetConnect() ?
			m_pTutorialStep->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_TUTORIAL_X_CAMERARESET)) :
			m_pTutorialStep->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_TUTORIAL_KEY_CAMERARESET));

		break;

	case CTutorial::TUTORIAL_CAMERARESET:
		m_step = TUTORIAL_JUMP;

		//�R���g���[�����ڑ�����Ă��邩�ǂ����Ńe�N�X�`�������ւ�
		CManager::GetXInput()->GetConnect() ?
			m_pTutorialStep->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_TUTORIAL_X_JUMP)) :
			m_pTutorialStep->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_TUTORIAL_KEY_JUMP));

		break;

	case CTutorial::TUTORIAL_JUMP:
		m_step = TUTORIAL_ATTACK;

		//�R���{�p�^�[��
		//�R���g���[�����ڑ�����Ă��邩�ǂ����Ńe�N�X�`�������ւ�
		CManager::GetXInput()->GetConnect() ?
			CScene2D_UI::Create(D3DXVECTOR3(170.0f, 80.0f, 0.0f), D3DXVECTOR3(300.0f, 120.0f, 0.0f), WhiteColor, CTexture::TEX_UI_GAME_X_COMBOPATTERN, CScene::OBJTYPE_2DUI) :
			CScene2D_UI::Create(D3DXVECTOR3(170.0f, 80.0f, 0.0f), D3DXVECTOR3(300.0f, 120.0f, 0.0f), WhiteColor, CTexture::TEX_UI_GAME_KEY_COMBOPATTERN, CScene::OBJTYPE_2DUI);

		//�G����
		CEnemy::Create(D3DXVECTOR3(0.0f, 0.0f, 300.0f), CEnemy::TYPE_NORMAL);

		//�R���g���[�����ڑ�����Ă��邩�ǂ����Ńe�N�X�`�������ւ�
		CManager::GetXInput()->GetConnect() ?
			m_pTutorialStep->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_TUTORIAL_X_ATTACK)) :
			m_pTutorialStep->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_TUTORIAL_KEY_ATTACK));

		break;

	case CTutorial::TUTORIAL_ATTACK:
		m_step = TUTORIAL_START_CHAIN;

		//�R���g���[�����ڑ�����Ă��邩�ǂ����Ńe�N�X�`�������ւ�
		CManager::GetXInput()->GetConnect() ?
			m_pTutorialStep->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_TUTORIAL_X_STARTCHAIN)) :
			m_pTutorialStep->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_TUTORIAL_KEY_STARTCHAIN));

		break;

	case CTutorial::TUTORIAL_START_CHAIN:
		m_step = TUTORIAL_CHAINTHUNDER;

		//�R���g���[�����ڑ�����Ă��邩�ǂ����Ńe�N�X�`�������ւ�
		CManager::GetXInput()->GetConnect() ?
			m_pTutorialStep->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_TUTORIAL_X_CHAINTHUNDER)) :
			m_pTutorialStep->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_TUTORIAL_KEY_CHAINTHUNDER));

		//�`���[�g���A���p�̃X�^����Ԃ̓G�o��
		TutorialEnemyPop();

		break;

	case CTutorial::TUTORIAL_CHAINTHUNDER:
		m_pTutorialStep->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_TUTORIAL_FREE));
		m_step = TUTORIAL_FREE;
		m_bEnemyPop = true;

		break;

	case CTutorial::TUTORIAL_FREE:
		m_pTutorialStep->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_TUTORIAL_END));
		m_step = TUTORIAL_END;

		break;

	case CTutorial::TUTORIAL_END:

		break;
	case CTutorial::TUTORIAL_MAX:

		break;
	default:
		break;
	}

	//�N���A��Ԃ�false��
	m_bClear = false;
}
//------------------------------------------------------------------------------
//�`���[�g���A���p�̓G�o��
//------------------------------------------------------------------------------
void CTutorial::TutorialEnemyPop()
{
	//�G����
	for (int nCntH = 0; nCntH < ENEMY_LINE.x; nCntH++)
	{
		for (int nCntV = 0; nCntV < ENEMY_LINE.y; nCntV++)
		{
			//�G����ׂĐ���
			CEnemy::Create(D3DXVECTOR3(
				-ENEMY_LINE.x * 0.5f * ENEMY_SPACE + nCntH * ENEMY_SPACE,
				0.0f,
				-ENEMY_LINE.y * 0.5f * ENEMY_SPACE + nCntV * ENEMY_SPACE), CEnemy::TYPE_TUTORIAL_STANING);
		}
	}

}
//------------------------------------------------------------------------------
//�v���C���[�̏��擾
//------------------------------------------------------------------------------
CPlayer * CTutorial::GetPlayer()
{
	if (m_pPlayer)
	{
		return m_pPlayer.get();
	}
	return nullptr;
}
//------------------------------------------------------------------------------
//�`���[�g���A���̃A�N�V�����`�F�b�N
//------------------------------------------------------------------------------
void CTutorial::CheckTutorialAction()
{
	//���ꂼ��̃X�e�b�v�ŏ���
	switch (m_step)
	{
	case CTutorial::TUTORIAL_MOVE:
		//�������[�V�����ɂȂ���
		if (m_pPlayer->GetNowMotion() == CMotion::PLAYER_WALK)
		{
			ActionClear();
		}
		break;
	case CTutorial::TUTORIAL_DASH:
		//�_�b�V�����[�V�����ɂȂ���
		if (m_pPlayer->GetNowMotion() == CMotion::PLAYER_DASH)
		{
			ActionClear();
		}
		break;
		//�J������������x������
	case CTutorial::TUTORIAL_CAMERAMOVE:
		if (fabsf(CManager::GetRenderer()->GetCamera()->GetCameraRot().y) > 1.0f)
		{
			ActionClear();
		}
		break;
		//�J�������Z�b�g�{�^���������ꂽ
	case CTutorial::TUTORIAL_CAMERARESET:
		if (CHossoLibrary::CheckCameraReset(CHossoLibrary::TRIGGER))
		{
			ActionClear();
		}
		break;
		//�W�����v���[�V�����ɂȂ���
	case CTutorial::TUTORIAL_JUMP:
		if (m_pPlayer->GetNowMotion() == CMotion::PLAYER_JUMP)
		{
			ActionClear();
		}
		break;
		//�G���S���ɂȂ���
	case CTutorial::TUTORIAL_ATTACK:
		if (CEnemy::GetEnemyNum() == CEnemy::GetStanEnemyNum())
		{
			ActionClear();
		}
		break;
		//�G�����Ȃ��Ȃ���
	case CTutorial::TUTORIAL_START_CHAIN:
		if (CEnemy::GetEnemyNum() <= 0)
		{
			ActionClear();
		}
		break;
		//�G�����Ȃ��Ȃ���
	case CTutorial::TUTORIAL_CHAINTHUNDER:
		if (CEnemy::GetEnemyNum() <= 0)
		{
			ActionClear();
		}
		break;
	case CTutorial::TUTORIAL_FREE:

		break;
	case CTutorial::TUTORIAL_END:
		//�Q�[���ɑJ��
		CManager::GetRenderer()->GetFade()->SetModeFade(CManager::MODE_GAME);
		break;
	}

}
//------------------------------------------------------------------------------
//�A�N�V�����N���A
//------------------------------------------------------------------------------
void CTutorial::ActionClear()
{
	//�N���A���
	m_bClear = true;

	//���̃A�N�V�������o��܂ł̃C���^�[�o���ݒ�
	m_nCntStep = TUTORIAL_STEP_INTERVAL;

	//OK! ��\��
	m_pOK = CScene2D::Create_Shared(D3DXVECTOR3(870.0f, 120.0f, 0.0f), D3DXVECTOR3(250.0f, 120.0f, 0.0f),CScene::OBJTYPE_2DUI);
	m_pOK->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_TUTORIAL_OK));

	//���Đ�
	CManager::GetSound()->Play(CSound::LABEL_SE_SLASH_STAN);

	//�G�t�F�N�g
	CEffectAnimation2D::Create(D3DXVECTOR3(870.0f, 120.0f, 0.0f), D3DXVECTOR3(250.0f, 250.0f, 0.0f), CTexture::SEPARATE_TEX_EFFECT_HIT_STAN, 0.0f, 1, CScene::OBJTYPE_2DEFFECT);
}
