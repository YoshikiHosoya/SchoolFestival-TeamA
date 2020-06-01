// ----------------------------------------
//
// �X�^�[�g�S�[�������̐���[startgoal.cpp]
// Author : Fujiwara Masato
//
// ----------------------------------------

// ----------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ----------------------------------------
/* �`�� */
#include "startgoalpoint.h"
#include "player.h"
#include "meshdome.h"
#include "fade.h"
#include "debugproc.h"
#include "3DTexture.h"
// ----------------------------------------
//
// �}�N����`
//
// ----------------------------------------
#define GOAL_ROTMOVE (0.01f)				// �p�x�̈ړ���
#define GOAL_SIZE (100.0f)					// �T�C�Y
#define GOAL_TEX "data/TEXTURE/Line.png"	// �e�N�X�`���[
#define GOAL_ANGLE (D3DX_PI / 1)			// �p�Ȃ̊p�x

// ----------------------------------------
//
// �O���[�o���ϐ�
//
// ----------------------------------------

// ----------------------------------------
//
// �ÓI�ϐ��錾
//
// ----------------------------------------

// ----------------------------------------
// �R���X�g���N�^����
// ----------------------------------------
CStartGoal::CStartGoal() : CScene(ACTOR_GOAL, LAYER_3DOBJECT)
{
	/* �ϐ��̏����� */
	// ��]��
	//m_pos = D3DXVECTOR3(-100.0f, 3900.0f, 0.0f);
}

// ----------------------------------------
// �f�X�g���N�^����
// ----------------------------------------
CStartGoal::~CStartGoal()
{
}

// ----------------------------------------
// ����������
// ----------------------------------------
void CStartGoal::Init(void)
{
	if (m_type == TYPE_START)
	{
		// ���b�V���h�[���̐���
		CMeshdome::Create(
			m_pos,
			D3DXVECTOR3(100.0f, 400.0f, 100.0f),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f),
			20, 1,
			CMeshdome::TYPE_START
		);
	}

	else if (m_type == TYPE_GOAL)
	{
		// ���b�V���h�[���̐���
		CMeshdome::Create(
			m_pos,
			D3DXVECTOR3(100.0f, 400.0f, 100.0f),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f),
			20, 1,
			CMeshdome::TYPE_GOAL
		);

		C3DTexture::Create(D3DXVECTOR3(	m_pos.x, m_pos.y + 10, m_pos.z),
										D3DXVECTOR3(1.57f, 0.0f, 0.0f),
										D3DXVECTOR3(250.0f, 0.0f, 250.0f),
										D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f),
										C3DTexture::TYPE_EFFECT_000,
										false);
	}
}

// ----------------------------------------
// �I������
// ----------------------------------------
void CStartGoal::Uninit(void)
{
}

// ----------------------------------------
// �X�V����
// ----------------------------------------
void CStartGoal::Update(void)
{
	CPlayer *pPlayer = NULL;

	for (int nCntlayer = 0; nCntlayer < CScene::GetMaxLayer(CScene::LAYER_3DOBJECT); nCntlayer++)
	{
		if (pPlayer = (CPlayer *)CScene::GetActor(CScene::ACTOR_PLAYER, CScene::LAYER_3DOBJECT, nCntlayer)) break;
	}

	if (pPlayer != NULL)
	{
		// �Q�[���J��
		if (CCalculation::Collision_Circle(
			m_pos,	// ���݂̃I�u�W�F�N�g�̈ʒu
			200.0f,				// ���݂̃I�u�W�F�N�g�̔��a
			pPlayer->GetPos(),	// �ړI�̃I�u�W�F�N�g�̈ʒu
			200.0f))			// �ړI�̃I�u�W�F�N�g�̔��a
		{
			if (CManager::GetFade()->GetFade() == CFade::FADE_NONE)
			{
				//pTopscore->SetScore(pScore->GetScore() + 20000);
				CManager::GetFade()->SetFade(CManager::MODE_RANKING);
			}
		}
	}
}

// ----------------------------------------
// �`�揈��
// ----------------------------------------
void CStartGoal::Draw(void)
{
}

// ----------------------------------------
// �쐬����
// ----------------------------------------
CStartGoal * CStartGoal::Create(D3DXVECTOR3 pos , TYPE type)
{
	// �ϐ��錾
	CStartGoal * pStartGoal;		// �V�[��2D�N���X
						// �������̐���(����->��{�N���X,��->�h���N���X)
	pStartGoal = new CStartGoal();
	// �ʒu���
	pStartGoal->m_pos = pos;
	// ��ނ̐ݒ�
	pStartGoal->m_type = type;
	// ����������
	pStartGoal->Init();
	// ���������I�u�W�F�N�g��Ԃ�
	return pStartGoal;
}