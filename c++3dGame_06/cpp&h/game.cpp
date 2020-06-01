// ------------------------------------------
//
// �Q�[������ [game.cpp]
// Author : Fujiwara Masato
//
// ------------------------------------------
#include "game.h"
/* �`�� */
#include "tlybg.h"
#include "fade.h"
#include "item.h"
#include "floor.h"
#include "player.h"
#include "item.h"
#include "scene_X.h"
#include "3Deffect.h"
#include "meshsphere.h"
#include "player.h"
#include "gauge.h"

/* �����蔻�� */
#include "collision.h"

/* �|�[�Y */
#include "pause.h"
#include "wall.h"
#include "enemy.h"
#include "3ditem.h"
#include "camera.h"
#include "renderer.h"
#include "debugproc.h"
#include "Debugcollision.h"
#include "object.h"
#include "floartile.h"
#include "warp.h"
#include "ceiling.h"
#include "titleEnemy.h"
#include "gameui.h"
#include "key.h"
#include "Manual.h"
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
CGame::STATE CGame::m_state = CGame::STATE_NORMAL;
int CGame::m_nStage = 0;	// �X�e�[�W
CPause *m_pPause = NULL;
CPlayer *CGame::m_pPlayer = NULL;

// ------------------------------------------
// �R���X�g���N�^
// ------------------------------------------
CGame::CGame()
{
	m_state = CGame::STATE_NORMAL;
	m_Shard = 0;
}

// ------------------------------------------
// �f�X�g���N�^
// ------------------------------------------
CGame::~CGame()
{
}

// ------------------------------------------
// ������
// ------------------------------------------
void CGame::Init(void)
{
	// ���
	m_state = STATE_NORMAL;
	// �X�e�[�W
	m_nStage = 0;
	CManager::PLAYER playerID = CManager::PLAYER_1;
	// �v���C���[
	m_pPlayer = CPlayer::Create();
	// �G
	CEnemy::Create();
	// �ǂ̐���
	//CWall::LoadCreate();
	// ���^�C��
	CFloarTile::LoadCreate();
	// �Q�[��ui�̐���
	CGame_ui::Create();

	// �V��̐���
	//CCeiling::LoadCreate();
	// 3DItem�̐���
	C3DItem::LoadCreate();
	// �G�t�F�N�g����
	C3DEffect::Create();
	// ������
	CKey::Create();

	// ���b�V���X�t�B�A
	//CMeshsphere::create();
	//CMeshsphere::Set(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10000.0f);
	//CMeshsphere::SetRadius(0, 10000.0f);

	CPause::Create();
	CManual::Create();

	// 2d�����蔻��̐���
	//CCollision::LoadCreate2D();
}

// ------------------------------------------
// �I��
// ------------------------------------------
void CGame::Uninit(void)
{
	//CGameUI::Unload();
	// �V�[�����̍폜
	CScene::ReleaseAll();
	// �����蔻��̍폜
	CCollision::DeleteAll();
}

// ------------------------------------------
// �X�V
// ------------------------------------------
void CGame::Update(void)
{
	// ��ʑJ�ڂ̏�Ԃ��J�ڂ��Ă��Ȃ���Ԃ�������
	if (CManager::GetFade()->GetFade() == CFade::FADE_NONE)
	{
		C3DItem * p3DItem = NULL;	// 3d�A�C�e��

		for (int nCntLayer = 0; nCntLayer < CScene::GetMaxLayer(CScene::LAYER_3DOBJECT); nCntLayer++)
		{
			if (p3DItem == NULL) p3DItem = (C3DItem*)CScene::GetActor(CScene::ACTOR_3DITEM, CScene::LAYER_3DOBJECT, nCntLayer);	// 3D�A�C�e��
		}

		//���Ђ̐����擾
		if (p3DItem != NULL)
		{
			CDebugproc::Print("���Ђ̑���: %d\n", C3DItem::GetShardNum());
		}
		else if (p3DItem == NULL)
		{
			CDebugproc::Print("���Ђ̑���: %d\n", 0);
		}
	}

	//�|�[�Y����
	if (CManager::GetKeyboard()->GetKeyboardTrigger(DIK_P) || CManager::GetJoy()->GetTrigger(0, CJoypad::KEY_START))
	{
		if (CPause::GetPause())
		{
			CPause::SetPause(false);
		}
		else
		{
			CPause::SetPause(true);
		}
	}

	/*if (CManager::GetKeyboard()->GetKeyboardTrigger(DIK_9))
	{
		if (CManager::GetFade()->GetFade() == CFade::FADE_NONE)
		{
			CManager::GetFade()->SetFade(CManager::MODE_RANKING);
		}
	}*/

	// �����蔻��
	CCollision::UpdateAll();
}

// ------------------------------------------
// �`��
// ------------------------------------------
void CGame::Draw(void)
{
}

// ------------------------------------------
// ��Ԏ擾
// ------------------------------------------
CGame::STATE CGame::GetState(void)
{
	return m_state;
}

// ------------------------------------------
// �X�e�[�W�擾
// ------------------------------------------
int CGame::GetStage(void)
{
	return m_nStage;
}

// ------------------------------------------
// ��Ԑݒ�
// ------------------------------------------
void CGame::SetState(STATE state)
{
	m_state = state;
}
