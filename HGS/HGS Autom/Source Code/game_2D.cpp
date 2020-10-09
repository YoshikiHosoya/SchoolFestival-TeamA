//------------------------------------------------------------------------------
//
//�Q�[������  [game.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "game_2D.h"
#include "manager.h"
#include "renderer.h"
#include "player_2D.h"
#include "fade.h"
#include "keyboard.h"
#include "camera.h"
#include "Way.h"
#include "ParticleManager.h"
#include "multinumber.h"
#include "bg.h"
//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------
#define DEFAULT_CREATE_POS (1000.0f)
#define WAY_SIZE (400.0f)
#define BENDING_TIME (4)
#define DEFAULT_TIME (30)
//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CGame_2D::CGame_2D()
{
	m_nSpeed = 10;
	m_direction = DIRECTION::UP;
	m_nCnt = 0;
	m_nScoreDistance = 0;
	SetScore(0);
	m_bBendingFlag = false;
	m_nTime = DEFAULT_TIME;
	m_pWayList = {};
}
//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CGame_2D::~CGame_2D()
{

}

//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CGame_2D::Init(HWND hWnd)
{
	//�J�������W�ݒ�
	CManager::GetRenderer()->GetCamera()->SetState(CCamera::CAMERA_DEBUG);

	CGame::SetPlayerPtr(CPlayer_2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 650.0f, 0.0f)));

	//�p�[�e�B�N���̃}�l�[�W��
	CParticleManager::Create();

	// �w�i�̐���
	CBg::Create();

	for (int nCnt = 0; nCnt < 5; nCnt++)
	{
		m_pWayList.emplace_back(CWay::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, -nCnt * 400.0f + DEFAULT_CREATE_POS, 0.0f), CWay::UP));
	}

	m_pScore = CScene2D::Create_Shared(D3DXVECTOR3(850.0f, 100.0f, 0.0f), D3DXVECTOR3(150.0f, 50.0f, 0.0f), CScene::OBJTYPE_UI);
	m_pScore->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_RANKING_SCORE));


	m_pScoreNumber = CMultiNumber::Create(D3DXVECTOR3(1000.0f, 100.0f, 0.0f), D3DXVECTOR3(50.0f, 75.0f, 0.0f),0,7, CScene::OBJTYPE_UI);
	m_pTimeNumber = CMultiNumber::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 50.0f, 0.0f), D3DXVECTOR3(50.0f, 75.0f, 0.0f), m_nTime, 2, CScene::OBJTYPE_UI);

	m_pNextBending = CScene2D::Create_Shared(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 300.0f, 0.0f), D3DXVECTOR3(200.0f, 200.0f, 0.0f), CScene::OBJTYPE_UI);
	m_pNextBending->SetDisp(false);

	//�ŏ��̃J�[�u
	Bending();

	//�Q�[���X�e�[�g������
	SetGamestate(CGame::STATE_NORMAL);

	return S_OK;
}

//------------------------------------------------------------------------------
//�I������
//------------------------------------------------------------------------------
void CGame_2D::Uninit()
{
	//�I������
	CScene::ReleaseAll();
}

//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CGame_2D::Update()
{
	if (GetGamestate() == CGame::STATE_NORMAL)
	{
		m_nCnt++;

		if (m_nCnt % 60 == 0)
		{
			AddTimer(-1);
		}

		if (m_nCnt % 60 == 0)
		{
			m_nSpeed += 1;
		}

		m_nScoreDistance += m_nSpeed;
		m_pScoreNumber->SetMultiNumber(m_nScoreDistance);

		m_nBendingTime--;

		if (m_nBendingTime < 0)
		{
			m_direction = DIRECTION::UP;


		}

		//���̋Ȃ���p�܂ł̍���
		float fNextBendingDistance = m_fNextBendingPoint - m_nScoreDistance;

		if (m_pWayList[m_pWayList.size() - 1]->GetPos().y >= -600.0f)
		{
			if (fNextBendingDistance <= 1200 && m_bBendingFlag)
			{
				switch (m_NextBendingDirection)
				{
				case DIRECTION::LEFT:
					m_pWayList.emplace_back(CWay::Create(m_pWayList[m_pWayList.size() - 1]->GetPos() + D3DXVECTOR3(0.0f, -WAY_SIZE, 0.0f), CWay::LEFT_01));
					m_pWayList.emplace_back(CWay::Create(m_pWayList[m_pWayList.size() - 1]->GetPos() + D3DXVECTOR3(-WAY_SIZE, 0.0f, 0.0f), CWay::LEFT_02));
					m_bBendingFlag = false;
					break;

				case DIRECTION::RIGHT:
					m_pWayList.emplace_back(CWay::Create(m_pWayList[m_pWayList.size() - 1]->GetPos() + D3DXVECTOR3(0.0f, -WAY_SIZE, 0.0f), CWay::RIGHT_01));
					m_pWayList.emplace_back(CWay::Create(m_pWayList[m_pWayList.size() - 1]->GetPos() + D3DXVECTOR3(WAY_SIZE, 0.0f, 0.0f), CWay::RIGHT_02));
					m_bBendingFlag = false;
					break;

				default:
					break;
				}
			}
			else
			{
				m_pWayList.emplace_back(CWay::Create(m_pWayList[m_pWayList.size() - 1]->GetPos() + D3DXVECTOR3(0.0f, -WAY_SIZE, 0.0f), CWay::UP));
			}
		}

		for (size_t nCnt = 0; nCnt < m_pWayList.size(); nCnt++)
		{
			if (m_pWayList[nCnt]->GetPos().y >= 1200.0f)
			{
				m_pWayList[nCnt]->Release();
				m_pWayList.erase(m_pWayList.begin() + nCnt);
			}
		}

	}
	else if (GetGamestate() == CGame::STATE_GAMEOVER)
	{
		//�J�E���g�_�E��
		m_nCnt--;

		//�J�E���g0
		if (m_nCnt <= 0)
		{
			//�Q�[���I��
			GameEnd();
		}

	}

}
//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void CGame_2D::Draw()
{

}
//------------------------------------------------------------------------------
//�f�o�b�O���\�L
//------------------------------------------------------------------------------
void CGame_2D::ShowDebugInfo()
{
#ifdef _DEBUG
	//�L�[�{�[�h�̃|�C���^
	CKeyboard *pKeyboard = CManager::GetKeyboard();


	CDebugProc::Print(CDebugProc::PLACE_LEFT, "m_nScoreDistance >> %d\n", m_nScoreDistance);
	CDebugProc::Print(CDebugProc::PLACE_LEFT, "m_fNextBendingPoint >> %.2f\n", m_fNextBendingPoint);
	CDebugProc::Print(CDebugProc::PLACE_LEFT, "NextDirection >> %d\n", m_NextBendingDirection);

	if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN))
	{
		GameEnd();
	}

	if (CManager::GetKeyboard()->GetTrigger(DIK_L))
	{
		m_nSpeed += 5;
	}

	if (CManager::GetKeyboard()->GetTrigger(DIK_LEFT))
	{
		Bending();
		m_NextBendingDirection = DIRECTION::LEFT;

	}

	if (CManager::GetKeyboard()->GetTrigger(DIK_RIGHT))
	{
		Bending();
		m_NextBendingDirection = DIRECTION::RIGHT;

	}

	//[0]�L�[����������
	if (pKeyboard->GetTrigger(DIK_0))
	{
		//�X�e�[�g�ύX
		SetGamestate(CGame_2D::STATE_GAMECLEAR);
		return;
	}

#endif //_DEBUG
}

//------------------------------------------------------------------------------
//�v���C���[�̋Ȃ��鏈��
//------------------------------------------------------------------------------
void CGame_2D::PlayerBending(DIRECTION Direction)
{
	m_direction = Direction;
	m_nBendingTime = BENDING_TIME;;

	Bending();
}

//------------------------------------------------------------------------------
//�Q�[���I��
//------------------------------------------------------------------------------
void CGame_2D::GameEnd()
{
	CGame::SetScore(m_nScoreDistance);
	CManager::GetRenderer()->GetFade()->SetModeFade(CManager::MODE_RANKING);
	SetGamestate(CGame::STATE_NONE);

}
//------------------------------------------------------------------------------
//�^�C�}�[
//------------------------------------------------------------------------------
void CGame_2D::AddTimer(int nAddTime)
{
	m_nTime += nAddTime;
	m_pTimeNumber->SetMultiNumber(m_nTime);
}

//------------------------------------------------------------------------------
//�Ȃ��鏈��
//------------------------------------------------------------------------------
void CGame_2D::Bending()
{
	m_NextBendingDirection = (DIRECTION)(rand() % 2);
	//m_fNextBendingPoint = m_nScoreDistance + (m_nSpeed * 60) + rand() % (m_nSpeed * 60);
	m_fNextBendingPoint = m_nScoreDistance + (m_nSpeed * 60);
	//m_fNextBendingPoint = m_nScoreDistance + 2500.0f;

	m_bBendingFlag = true;

}

//------------------------------------------------------------------------------
//�Q�[���X�e�[�g�ݒ�
//------------------------------------------------------------------------------
void CGame_2D::SetGamestate(STATE gamestate)
{
	if (GetGamestate() != gamestate)
	{
		CGame::SetGamestate(gamestate);
		//�X�e�[�g���i��ł���ꍇ

		if (gamestate == CGame::STATE_GAMEOVER)
		{
			m_nCnt = 30;
		}
	}
}
