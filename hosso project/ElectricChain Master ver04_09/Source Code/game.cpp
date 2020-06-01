//------------------------------------------------------------------------------
//
//�Q�[������  [game.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "game.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"
#include "player.h"
#include "fade.h"
#include "sound.h"
#include "keyboard.h"
#include "camera.h"
#include "Map.h"
#include "multinumber.h"
#include "pause.h"
#include "enemy.h"
#include "score.h"
#include "timer.h"
#include "ui.h"
#include "effectanimation2D.h"
#include "player_demo.h"
#include "Pad_XInput.h"
#include "miniMap.h"
#include "FrontUI.h"
//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------
#define DEFAULT_PLAYER_POS	(D3DXVECTOR3(0.0f, 0.0f, -800.0f))		//�v���C���[�̏������W
#define ENEMY_MAX			(50)									//�G�̍ő吔
#define DEFAULT_TIMER		(120)									//�^�C�}�[
#define ENEMY_POP_INTERVAL	(60)									//�G�̏o���̃C���^�[�o��
#define ENEMY_SPAWN_NUM		(30)										//�ŏ��̓G�̏o�����鐔
#define GAMEEND_INTERVAL	(240)									//�Q�[���I�����Ă���J�ڂ���܂ł̃J�E���^
#define READY_COUNT			(3)										//�Q�[���J�n�̃J�E���g�_�E��
//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CGame::CGame()
{
	//������
	m_pPause.reset();
	m_pMap.reset();
	m_pScore.reset();
	m_pTimer.reset();
	m_pPlayer.reset();

	m_nReadyCount = READY_COUNT + 1;
	m_nCntState = 0;
	m_nEnemyPopTime = 0;
	m_gamestate = STATE_READY;
}
//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CGame::~CGame()
{
	//�J��
	m_pPause.reset();
	m_pMap.reset();
	m_pScore.reset();
	m_pTimer.reset();
	m_pPlayer.reset();

}

//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CGame::Init(HWND hWnd)
{
	//�J�������W�ݒ�
	CManager::GetRenderer()->GetCamera()->SetCameraPos(DEFAULT_PLAYER_POS, DEFAULT_PLAYER_POS + D3DXVECTOR3(0.0f, 200, -450));
	CManager::GetRenderer()->GetCamera()->SetState(CCamera::CAMERA_GAME);

	//debug�p
	if (CHossoLibrary::CheckDebugPlayer())
	{
		//�v���C���[����
		//AI debug�p
		m_pPlayer = CPlayer_Demo::Create(DEFAULT_PLAYER_POS);
	}
	else
	{
		//�v���C���[����
		m_pPlayer = CPlayer::Create(DEFAULT_PLAYER_POS);
	}

	//�}�b�v����
	m_pMap = CMap::Create();

	//�^�C�}�[
	m_pTimer = CTimer::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f,95.0f,0.0f), DEFAULT_TIMER);

	//�X�R�A
	m_pScore = CScore::Create();

	//�~�j�}�b�v����
	CMiniMap::Create();

	//�Q�[����UI�ǂݍ���
	CUI::LoadPlace(CUI::SCENE_GAME);

	//�R���{�p�^�[��
	//�R���g���[�����ڑ�����Ă��邩�ǂ����Ńe�N�X�`�������ւ�
	CManager::GetXInput()->GetConnect() ?
		CScene2D_UI::Create(D3DXVECTOR3(170.0f, 80.0f, 0.0f), D3DXVECTOR3(300.0f, 120.0f, 0.0f), WhiteColor, CTexture::TEX_UI_GAME_X_COMBOPATTERN, CScene::OBJTYPE_2DUI) :
		CScene2D_UI::Create(D3DXVECTOR3(170.0f, 80.0f, 0.0f), D3DXVECTOR3(300.0f, 120.0f, 0.0f), WhiteColor, CTexture::TEX_UI_GAME_KEY_COMBOPATTERN, CScene::OBJTYPE_2DUI);

	//������
	SetGamestate(CGame::STATE_READY);

	return S_OK;
}

//------------------------------------------------------------------------------
//�I������
//------------------------------------------------------------------------------
void CGame::Uninit()
{
	//�I������
	CScene::ReleaseAll();
}

//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CGame::Update()
{
	//�Q�[���̏�Ԃŏ�����ς���
	switch (m_gamestate)
	{
	case CGame::STATE_READY:
		if (m_nCntState % 60 == 0)
		{
			//�J�E���^++
			m_nReadyCount--;

			//�J�E���g��0�ɂȂ�����
			if (m_nReadyCount <= 0)
			{
				//�Q�[���J�n
				SetGamestate(CGame::STATE_NORMAL);
				CFrontUI::Create(SCREEN_CENTER_POS, D3DXVECTOR3(850.0f, 300.0f, 0.0f), WhiteColor, CFrontUI::GAMESTART);
				CEffectAnimation2D::Create(SCREEN_CENTER_POS, D3DXVECTOR3(1000.0f, 1000.0f, 0.0f), CTexture::SEPARATE_TEX_EFFECT_GAME_START, 0.0f, 2, CScene::OBJTYPE_2DEFFECT);
				break;
			}

			//���l����
			std::shared_ptr<CMultiNumber> pMultiNumber = CMultiNumber::Create(SCREEN_CENTER_POS, D3DXVECTOR3(250.0f, 400.0f, 0.0f), m_nReadyCount, 1, CScene::OBJTYPE_NUMBER);
			pMultiNumber->Settype(CMultiNumber::TYPE_CENTER_DISAPPEAR);
		}

		//��ԍŏ��ɏ����ʉ߂������������ŉ��Z
		m_nCntState++;
		break;

		//�ʏ펞
	case CGame::STATE_NORMAL:

		//�G���X�|�[��
		EnemyRespawn();

		//�^�C�}�[�X�V
		m_pTimer->Update();

		//P�Ń|�[�Y���
		if (CHossoLibrary::CheckPause())
		{
			SetGamestate(CGame::STATE_PAUSE);
		}
		break;

		//�|�[�Y��
	case CGame::STATE_PAUSE:
		//nullcheck
		if (m_pPause)
		{
			//�|�[�Y�ŃI�v�V�������J���Ă��Ȃ������ꍇ
			if (!m_pPause->GetOptionWindow())
			{
				//P�Ń|�[�Y���
				if (CHossoLibrary::CheckPause() || CHossoLibrary::CheckCancel())
				{
					//�ʏ��Ԃɖ߂�
					SetGamestate(CGame::STATE_NORMAL);
				}
			}
			if (CScene::CheckStop())
			{
				//�X�V
				//Scene���̍X�V���~�܂��Ă���̂ł������ōX�V
				//�`���Scene����
				m_pPause->Update();
			}
		}
		break;
	case CGame::STATE_GAMEOVER:

		break;
		//�Q�[���N���A
	case CGame::STATE_GAMECLEAR:
		m_nCntState--;
		if (m_nCntState <= 0)
		{
			//�X�R�A�ۑ�
			m_pScore->SaveScore();

			//���U���g�ɑJ��
			CManager::GetRenderer()->GetFade()->SetModeFade(CManager::MODE_RESULT);
			SetGamestate(CGame::STATE_NONE);
		}
		break;
	}
}

//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void CGame::Draw()
{

}
//------------------------------------------------------------------------------
//�f�o�b�O���\�L
//------------------------------------------------------------------------------
void CGame::ShowDebugInfo()
{
#ifdef _DEBUG
	//�L�[�{�[�h�̃|�C���^
	CKeyboard *pKeyboard = CManager::GetKeyboard();

	//[0]�L�[����������
	if (pKeyboard->GetTrigger(DIK_0))
	{
		//�X�e�[�g�ύX
		SetGamestate(CGame::STATE_GAMECLEAR);
		return;
	}

	if (ImGui::TreeNode("GameDebugCommand"))
	{
		if (ImGui::Button("AllEnemyBlueDamage"))
		{
			//Scene�̃��X�g
			std::vector<std::shared_ptr<CScene>> pSceneList;

			//�G�̃��X�g�擾
			CScene::GetSceneList(CScene::OBJTYPE_ENEMY, pSceneList);

			//nullcheck
			if (!pSceneList.empty())
			{
				//�v�f��
				for (size_t nCnt = 0; nCnt < pSceneList.size(); nCnt++)
				{
					//�|�C���^�擾 CMeshField�^�ɃL���X�g
					CCharacter *pCharacter = ((CCharacter*)pSceneList[nCnt].get());

					//nullcheck
					if (pCharacter)
					{
						//���G��ԉ���
						pCharacter->ApplyDamage(0, 999);
					}
				}
			}
		}

		if (ImGui::Button("EnemyCreate"))
		{
			CEnemy::Create(D3DXVECTOR3(float(rand() % 200), 50.0f, float(rand() % 200)), CEnemy::TYPE_NORMAL);
		}

		ImGui::TreePop();
	}
#endif //_DEBUG
}

//------------------------------------------------------------------------------
//�Q�[���X�e�[�g�Z�b�g
//------------------------------------------------------------------------------
void CGame::SetGamestate(STATE gamestate)
{
	//�X�e�[�g���i��ł���ꍇ
	if (m_gamestate != CGame::STATE_NONE)
	{
		//�X�e�[�g�ύX
		m_gamestate = gamestate;

		switch (gamestate)
		{
		case STATE_READY:
			m_nCntState = 0;
			m_nReadyCount = READY_COUNT + 1;
			break;

		case STATE_NORMAL:
			if (m_pPause)
			{
				m_pPause->Release();
				m_pPause = nullptr;
			}
			CScene::SetStop(false);
			break;

		case STATE_PAUSE:
			if (!m_pPause)
			{
				m_pPause = CPause::Create();
			}
			CScene::SetStop(true);
			break;

		case CGame::STATE_GAMECLEAR:
			//�J�E���^���Z�b�g
			m_nCntState = GAMEEND_INTERVAL;

			//�I���̃e�N�X�`��
			CScene2D_UI::Create(SCREEN_CENTER_POS, SCREEN_SIZE, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.7f), CTexture::TEX_NONE, CScene::OBJTYPE_FRONT);
			CScene2D_UI::Create(SCREEN_CENTER_POS, D3DXVECTOR3(850.0f, 300.0f, 0.0f), WhiteColor, CTexture::TEX_FINISH, CScene::OBJTYPE_FRONT);

			//�v���C���[�������Ă邩����ł邩�ŉ��Đ�
			GetPlayer()->GetAlive() ?
				CManager::GetSound()->Play(CSound::LABEL_SE_GAMECLEAR) :
				CManager::GetSound()->Play(CSound::LABEL_SE_GAMEOVER);

			//�Q�[���N���A
			break;

		case CGame::STATE_DEBUG:
			CScene::SetStop(true);
			break;
		}
	}
}
//------------------------------------------------------------------------------
//�}�b�v�擾
//------------------------------------------------------------------------------
CMap * CGame::GetMap()
{
	if (m_pMap)
	{
		return m_pMap.get();
	}
	return nullptr;
}
//------------------------------------------------------------------------------
//�X�R�A�擾
//------------------------------------------------------------------------------
CScore * CGame::GetScore()
{
	if (m_pScore)
	{
		return m_pScore.get();
	}
	return nullptr;
}
//------------------------------------------------------------------------------
//�v���C���[�擾
//------------------------------------------------------------------------------
CPlayer * CGame::GetPlayer()
{
	if (m_pPlayer)
	{
		return m_pPlayer.get();
	}
	return nullptr;
}

//------------------------------------------------------------------------------
//�G�̃��X�|�[��
//------------------------------------------------------------------------------
void CGame::EnemyRespawn()
{
	//������x���Ȃ��Ȃ�����
	if (CEnemy::GetEnemyNum() <= 1 + m_nEnemuPopWave)
	{
		//�J�E���g�_�E��
		m_nEnemyPopTime--;

		//�J�E���g0�̂Ƃ�
		if (m_nEnemyPopTime < 0)
		{
			//�E�F�[�u�ǉ�
			m_nEnemuPopWave++;
			m_nEnemyPopTime = ENEMY_POP_INTERVAL + (m_nEnemuPopWave * 2);

			//�o��
			CManager::GetSound()->Play(CSound::LABEL_SE_APPEAR);

			for (int nCnt = 0; nCnt < ENEMY_SPAWN_NUM + (m_nEnemuPopWave * 1.7f); nCnt++)
			{
				//�ő�l��������
				if (CEnemy::GetEnemyNum() >= ENEMY_MAX)
				{
					//������
					break;
				}

				//�G�̏o��������W�v�Z
				D3DXVECTOR3 PopPos = D3DXVECTOR3(float(rand() % (200 + 45 * m_nEnemuPopWave) - rand() % (200 + 45 * m_nEnemuPopWave)),20.0f,float(rand() % (200 + 45 * m_nEnemuPopWave) - rand() % (200 + 45 * m_nEnemuPopWave)));

				//�t�B�[���h�̍L���擾
				D3DXVECTOR3 FieldSize = CMap::GetFieldSize() * 0.5f;

				//�t�B�[���h�O�ɏo��Ȃ��悤�ɂ���
				CHossoLibrary::RangeLimit_Equal_Float(PopPos.x, -FieldSize.x, +FieldSize.x);
				CHossoLibrary::RangeLimit_Equal_Float(PopPos.z, -FieldSize.z, +FieldSize.z);

				//�G����
				CEnemy::Create(PopPos, CEnemy::TYPE_NORMAL);

			}
		}
	}
}