// ------------------------------------------
//
// �^�C�g������ [title.cpp]
// Author : Fujiwara Masato
//
// ------------------------------------------
#include "title.h"
/* �`�� */
#include "tlybg.h"
#include "title_ui.h"
#include "fade.h"
#include "floor.h"
#include "player.h"
#include "titleobject.h"
#include "lighteffect.h"
#include "item.h"
#include "gate.h"
#include "explosion.h"
#include "titleEnemy.h"
#include "telop.h"
#include "TelopComment.h"
#include "bulletinboard.h"
#include "2DAnimationUI.h"
#include "key.h"
#include "map.h"
#include "camera.h"
#include "pause.h"
#include "manual.h"
// ------------------------------------------
//
// �}�N����`
//
// ------------------------------------------
// ------------------------------------------
//
// �ÓI�ϐ��錾
//
// ------------------------------------------
CTitle_ui * CTitle::m_pTitle_ui = NULL;
CTitleEnemy * CTitle::m_pTitleEnemy = NULL;
CLightEffect * CTitle::m_pLightEffect = NULL;
CTelop * CTitle::m_pTelop = NULL;
bool CTitle::m_bFlag = false;
bool CTitle::m_bStartFlag = false;
bool CTitle::m_bTelopFlag = false;
// ------------------------------------------
// �R���X�g���N�^
// ------------------------------------------
CTitle::CTitle()
{
	m_Mode = TITLEMODE_TITLE;
	m_CreateCnt = 0;
	m_Enterflag = true;
	m_PhaseCount = 0;
	m_Phaseflag = false;
}

// ------------------------------------------
// �f�X�g���N�^
// ------------------------------------------
CTitle::~CTitle()
{
}

// ------------------------------------------
// ������
// ------------------------------------------
void CTitle::Init(void)
{
	//�g���I�u�W�F�N�g�̐���
	CreateTitleObj();

	CPause::Create();
	CManual::Create();
}

// ------------------------------------------
// �I��
// ------------------------------------------
void CTitle::Uninit(void)
{
	m_pTitle_ui = NULL;
	m_pTitleEnemy = NULL;
	m_pLightEffect = NULL;
	m_pTelop = NULL;
	m_bFlag = false;
	m_bStartFlag = false;
	m_bTelopFlag = false;
	CScene::ReleaseAll();
}

// ------------------------------------------
// �X�V
// ------------------------------------------
void CTitle::Update(void)
{
	// �L�[�{�[�h��ENTER���������u��
	if (CManager::GetKeyboard()->GetKeyboardTrigger(DIK_RETURN))
	{
		//���[�h�̐ݒ�
		SetMode();
		// ENTER���������ۂ̃t���O��true�ɂ���
		m_Enterflag = true;
	}

	if (CManager::GetKeyboard()->GetKeyboardTrigger(DIK_SPACE))
	{
		CManager::GetFade()->SetFade(CManager::MODE_GAME);
	}

	if (m_Mode == TITLEMODE_FREE && CManager::GetKeyboard()->GetKeyboardTrigger(DIK_P))
	{
		if (CPause::GetPause() == false)
		{
			CPause::SetPause(true);
		}
		else
		{
			CPause::SetPause(false);
		}
	}

	if (CManager::GetJoy()->GetTrigger(0, CJoypad::KEY_A) || CManager::GetJoy()->GetTrigger(0, CJoypad::KEY_B))
	{
		//���[�h�̐ݒ�
		SetMode();
		// ENTER���������ۂ̃t���O��true�ɂ���
		m_Enterflag = true;
	}

	//���[�h���Ƃ̏���
	Mode();
}

// ------------------------------------------
// �`��
// ------------------------------------------
void CTitle::Draw(void)
{
}

// ------------------------------------------
// �^�C�g���Ŏg���I�u�W�F�N�g�̐���
// ------------------------------------------
void CTitle::CreateTitleObj(void)
{
	// �w�i
	CTlyBg::Create(CManager::MODE_TITLE);
	// UI
	m_pTitle_ui = CTitle_ui::Create();

	//��
	CFloor::Create(
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(500.0f, 0.0f, 400.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		10, 10);

	// �^�C�g���p�̃I�u�W�F�N�g
	CTitleObject::LoadCreate();

	// �v���C���[
	CPlayer *pPlayer = CPlayer::Create();
	CManager::GetRenderer()->GetCamera()->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// �^�C�g���p�̓G
	m_pTitleEnemy = CTitleEnemy::Create();

	// ���C�g�G�t�F�N�g
	CLightEffect::Create(D3DXVECTOR3(-20.000, 100.000, -1700.000),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(500.000, 500.000, 0.000),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f),
		CLightEffect::TYPE_P_LIGHT,
		false);

	// ��
	//CKey::Create();
}

// ------------------------------------------
// �^�C�g���̃��[�h�ݒ�
// ------------------------------------------
void CTitle::SetMode(void)
{
	// ��ʑJ�ڂ̏�Ԃ��J�ڂ��Ă��Ȃ���Ԃ�������
	if (CManager::GetFade()->GetFade() == CFade::FADE_NONE)
	{
		// �^�C�g���̏�����ʂőI�񂾃��[�h��NEWGAME��������
		if (m_pTitle_ui->GetSelect() == CTitle_ui::TITLESELECT_NEWGAME)
		{
			//�^�C�g���̏�Ԃ���`���[�g���A�����[�h��
			if (m_Mode == TITLEMODE_TITLE)
			{
				// ���C�g�G�t�F�N�g���폜
				CLightEffect::ReleaseLight(CLightEffect::TYPE_P_LIGHT);
				// �^�C�g���̃��[�h���`���[�g���A���Ɉڍs
				m_Mode = TITLEMODE_TUTORIAL;
			}
		}

		// �`���[�g���A������������
		if (m_Mode == TITLEMODE_TUTORIAL)
		{
			// �`���[�g���A�����I�������
			if (CTelopComment::GetEndPhaseFlag() == true)
			{
				// ���C�g�G�t�F�N�g���폜
				CLightEffect::ReleaseLight(CLightEffect::TYPE_S_LIGHT);
				// �^�C�g���p�̓G���폜
				m_pTitleEnemy->Release();
				// �����𐶐�
				CExplosion::Create(D3DXVECTOR3(0.000f, 250.000f, -1700.000f), D3DXVECTOR3(300.0f, 300.0f, 0.0f), CExplosion::TYPE_EXPLOSION);
				// �^�C�g���̃��[�h�𑀍�\��ԂɈڍs
				m_Mode = TITLEMODE_FREE;
			}
		}
	}
}

// ------------------------------------------
// �^�C�g���̃��[�h���Ƃ̏���
// ------------------------------------------
void CTitle::Mode(void)
{
	switch (m_Mode)
	{
	case TITLEMODE_TITLE:
		break;

	case TITLEMODE_TUTORIAL:
		// �^�C�g��ui����������ʂ�
		if (CTitle_ui::GetFlag() == true)
		{
			// �܂���������Ă��Ȃ�������
			if (m_bFlag == false)
			{
				//�����܂ł̎��Ԃ��J�E���g
				//m_CreateCnt++;
				//if (m_CreateCnt >= ONEMIN / 2)
				//{
					//���C�g�G�t�F�N�g����x��������
					CLightEffect::Create(D3DXVECTOR3(-20.000, 400.000, -1700.000),
						D3DXVECTOR3(0.0f, 0.0f, 0.0f),
						D3DXVECTOR3(200.000, 500.000, 0.000),
						D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f),
						CLightEffect::TYPE_S_LIGHT,
						false);

					// �����܂ł̎��Ԃ�������
					m_CreateCnt = 0;
					// �o�������̂Ńt���O��true�ɂ���
					m_bFlag = true;
				//}
			}

			// �o�����Ă��Ȃ�������
			else if (m_bTelopFlag == false)
			{
				//�����܂ł̎��Ԃ��J�E���g
				m_CreateCnt++;

				// ��������J�E���g���ɂȂ�����
				if (m_CreateCnt >= ONEMIN * 0.5f)
				{
					//�e���b�v����x��������
					m_pTelop = CTelop::Create();
					//�����܂ł̎��Ԃ����Z�b�g
					m_CreateCnt = 0;
					// �o�������̂Ńt���O��true�ɂ���
					m_bTelopFlag = true;
				}
			}

			// �o��������
			else if (m_bTelopFlag == true)
			{
				// ���X�ɕs�����x���グ��
				m_pTelop->Transparency(CTelop::STATE_EMERGENCE);
			}
			m_pTitleEnemy->SetMotion();
		}

		break;

	case TITLEMODE_FREE:
		if (m_bStartFlag == false)
		{
			// �����܂ł̎��Ԃ��J�E���g
			m_CreateCnt++;
			// 2�b�o������
			if (m_CreateCnt >= ONEMIN * 2)
			{
				// �Q�[�����[�h�Ɉڍs���邽�߂̃Q�[�g���쐬
				CGate::LoadCreate();
				// �����p�̌f���쐬
				//CBulletinBoard::LoadCreate();
				// ��
				//CKey::Create();
				// 2DAnimation
				//C2DAnimation::Create(D3DXVECTOR3(1200.0f, 80, 0.0f), D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.2f, 0.25f), C2DAnimation::TYPE_KEY);
				// �����܂ł̎��Ԃ�������
				m_CreateCnt = 0;
				// �Q�[�g���������ꂽ�̂Ńt���O��true�ɂ���
				m_bStartFlag = true;
			}
		}

		// �Q�[�g���o�����ăe���b�v�����݂��Ă�����
		else if (m_pTelop != NULL)
		{
			// �e���b�v���폜
			m_pTelop->Transparency(CTelop::STATE_DISAPPEARANCE);
		}

		break;

	default:
		break;
	}
}

// ------------------------------------------
// �^�C�g���̃��[�h�̎擾
// ------------------------------------------
CTitle::TITLEMODE CTitle::GetMode(void)
{
	return m_Mode;
}

// ------------------------------------------
// �t���O�����ɖ߂�
// ------------------------------------------
void CTitle::SetEnterflag()
{
	m_Enterflag = false;
}

// ------------------------------------------
// �t���O�̎擾
// ------------------------------------------
bool CTitle::GetEnterflag()
{
	return m_Enterflag;
}
