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
//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------
#define DEFAULT_CREATE_POS (1000.0f)
#define WAY_SIZE (400.0f)
#define BENDING_TIME (4)
//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CGame_2D::CGame_2D()
{
	m_fSpeed = 10.0f;
	m_direction = DIRECTION::UP;
	m_nCnt = 0;
	m_fScoreDistance = 0.0f;
	m_bBendingFlag = false;
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

	for (int nCnt = 0; nCnt < 8; nCnt++)
	{
		m_pWayList.emplace_back(CWay::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, nCnt * 400.0f - DEFAULT_CREATE_POS, 0.0f), CWay::UP));
	}

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
	m_nCnt++;
	m_fScoreDistance += m_fSpeed;

	m_nBendingTime--;

	if (m_nBendingTime < 0)
	{
		m_direction = DIRECTION::UP;
	}

	//���̋Ȃ���p�܂ł̍���
	float fNextBendingDistance = m_fNextBendingPoint - m_fScoreDistance;

	CDebugProc::Print(CDebugProc::PLACE_LEFT, "m_fScoreDistance >> %.2f\n", m_fScoreDistance);
	CDebugProc::Print(CDebugProc::PLACE_LEFT, "m_fNextBendingPoint >> %.2f\n", m_fNextBendingPoint);
	CDebugProc::Print(CDebugProc::PLACE_LEFT, "fNextBendingDistance >> %.2f\n", fNextBendingDistance);
	CDebugProc::Print(CDebugProc::PLACE_LEFT, "NextDirection >> %d\n", m_NextBendingDirection);

	if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN))
	{
		m_fSpeed += 2.0f;
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
//�Ȃ��鏈��
//------------------------------------------------------------------------------
void CGame_2D::Bending()
{
	m_NextBendingDirection = (DIRECTION)(rand() % 2);
	m_fNextBendingPoint = m_fScoreDistance + 2500.0f;

	m_bBendingFlag = true;

}
