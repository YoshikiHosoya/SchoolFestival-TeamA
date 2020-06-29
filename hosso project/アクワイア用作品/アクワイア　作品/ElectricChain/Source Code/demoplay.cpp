//------------------------------------------------------------------------------
//
//�f���v���C����  [demoplay.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "demoplay.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"
#include "player.h"
#include "fade.h"
#include "keyboard.h"
#include "camera.h"
#include "Map.h"
#include "enemy.h"
#include "ui.h"
#include "player_demo.h"
//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------
#define DEFAULT_PLAYER_POS	(D3DXVECTOR3(0.0f, 0.0f, -800.0f))		//�v���C���[�̏������W
#define ENEMY_LINE			(INTEGER2(4,4))							//�G�̗�
#define ENEMY_SPACE			(150.0f)								//�G�̊��o
#define TITLE_FADE_COUNT	(1200)									//�^�C�g���Ƀt�F�[�h����܂ł̃J�E���^
//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CDemoPlay::CDemoPlay()
{
	//������
	m_pPlayer.reset();
	m_nCntTitleFade = TITLE_FADE_COUNT;
	m_nEnemyPopTime = 0;
}
//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CDemoPlay::~CDemoPlay()
{

}

//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CDemoPlay::Init(HWND hWnd)
{
	//�J�������W�ݒ�
	CManager::GetRenderer()->GetCamera()->SetCameraPos(DEFAULT_PLAYER_POS, DEFAULT_PLAYER_POS + D3DXVECTOR3(0.0f, 200, -600));
	CManager::GetRenderer()->GetCamera()->SetState(CCamera::CAMERA_GAME);

	//�}�b�v
	CMap::Create();

	//�v���C���[����
	m_pPlayer = CPlayer_Demo::Create(DEFAULT_PLAYER_POS);

	//�G����
	EnemyRespawn();

	return S_OK;
}

//------------------------------------------------------------------------------
//�I������
//------------------------------------------------------------------------------
void CDemoPlay::Uninit()
{
	//�I������
	CScene::ReleaseAll();
}

//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CDemoPlay::Update()
{
	//�t�F�[�h���ĂȂ���
	if (CManager::GetRenderer()->GetFade()->GetFade() == CFade::FADE_NONE)
	{
		//�J�E���g�_�E��
		m_nCntTitleFade--;

		//������x���Ԃ����G���S�ł������Ȃ񂩓��͂��ꂽ�Ƃ�
		if (m_nCntTitleFade <= 0 || CEnemy::GetEnemyNum() <= 0 || CHossoLibrary::CheckAnyButton())
		{
			//�^�C�g���ɖ߂�
			CManager::GetRenderer()->GetFade()->SetModeFade(CManager::MODE_TITLE);
			CManager::GetSound()->Play(CSound::LABEL_SE_DECISION);
		}
	}
}

//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void CDemoPlay::Draw()
{

}
//------------------------------------------------------------------------------
//�f�o�b�O���\�L
//------------------------------------------------------------------------------
void CDemoPlay::ShowDebugInfo()
{

}
//------------------------------------------------------------------------------
//�v���C���[�擾
//------------------------------------------------------------------------------
CPlayer * CDemoPlay::GetPlayer()
{
	if (m_pPlayer)
	{
		return m_pPlayer.get();
	}
	return nullptr;
}

//------------------------------------------------------------------------------
//�G����
//------------------------------------------------------------------------------
void CDemoPlay::EnemyRespawn()
{
	//�G����
	for (int nCntH = 0; nCntH < ENEMY_LINE.x; nCntH++)
	{
		for (int nCntV = 0; nCntV < ENEMY_LINE.y; nCntV++)
		{
			CEnemy::Create(D3DXVECTOR3(
				-ENEMY_LINE.x * 0.5f * ENEMY_SPACE + nCntH * ENEMY_SPACE,
				0.0f,
				-ENEMY_LINE.y * 0.5f * ENEMY_SPACE + nCntV * ENEMY_SPACE), CEnemy::TYPE_NORMAL);
		}
	}
}
