// ----------------------------------------
//
// �S�[�������̐���[goal.cpp]
// Author : Fujiwara Masato
//
// ----------------------------------------

// ----------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ----------------------------------------
/* �`�� */
#include "goal.h"
#include "player.h"
#include "meshdome.h"
#include "fade.h"
#include "debugproc.h"
#include "score.h"
//#include "topscore.h"
#include "time.h"

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
LPDIRECT3DTEXTURE9 CGoal::m_pTex = NULL;

// ----------------------------------------
// �R���X�g���N�^����
// ----------------------------------------
CGoal::CGoal() : CScene(ACTOR_GOAL, LAYER_3DOBJECT)
{
	/* �ϐ��̏����� */
	// ��]��
	//m_pos = D3DXVECTOR3(-100.0f, 3900.0f, 0.0f);
}

// ----------------------------------------
// �f�X�g���N�^����
// ----------------------------------------
CGoal::~CGoal()
{
}

// ----------------------------------------
// ����������
// ----------------------------------------
void CGoal::Init(void)
{
	// ���b�V���h�[���̐���
	CMeshdome::Create(
		m_pos,
		D3DXVECTOR3(100.0f, 400.0f, 100.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f),
		20, 1,
		CMeshdome::TYPE_WAVE
	);
}

// ----------------------------------------
// �I������
// ----------------------------------------
void CGoal::Uninit(void)
{
}

// ----------------------------------------
// �X�V����
// ----------------------------------------
void CGoal::Update(void)
{
	CPlayer *pPlayer = NULL;
	//CTopscore * pTopscore = NULL;
	CScore	* pScore = NULL;
	CTime * pTime = NULL;

	for (int nCntlayer = 0; nCntlayer < CScene::GetMaxLayer(CScene::LAYER_3DOBJECT); nCntlayer++)
	{
		if (pPlayer = (CPlayer *)CScene::GetActor(CScene::ACTOR_PLAYER, CScene::LAYER_3DOBJECT, nCntlayer)) break;
	}
	for (int nCntlayer = 0; nCntlayer < CScene::GetMaxLayer(CScene::LAYER_UI); nCntlayer++)
	{
		//if (pTopscore == NULL) pTopscore = (CTopscore *)CScene::GetActor(CScene::ACTOR_TOPSCORE, CScene::LAYER_UI, nCntlayer);
		if (pScore == NULL) pScore = (CScore *)CScene::GetActor(CScene::ACTOR_SCORE, CScene::LAYER_UI, nCntlayer);
		if (pTime == NULL) pTime = (CTime *)CScene::GetActor(CScene::ACTOR_TIME, CScene::LAYER_UI, nCntlayer);
	}


	// �Q�[���J��
	// �����L���O��
	if (CCalculation::Collision_Circle(
		m_pos,	// ���݂̃I�u�W�F�N�g�̈ʒu
		50.0f,				// ���݂̃I�u�W�F�N�g�̔��a
		pPlayer->GetPos(),	// �ړI�̃I�u�W�F�N�g�̈ʒu
		20.0f))				// �ړI�̃I�u�W�F�N�g�̔��a
	{
		if (CManager::GetFade()->GetFade() == CFade::FADE_NONE)
		{
			//pTopscore->SetScore(pScore->GetScore() + 20000);
			//CManager::GetFade()->SetFade(CManager::MODE_RANKING);
		}
	}
}

// ----------------------------------------
// �`�揈��
// ----------------------------------------
void CGoal::Draw(void)
{
}

// ----------------------------------------
// �ǂݍ��ݏ���
// ----------------------------------------
HRESULT CGoal::Load(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice =
		CManager::GetRenderer()->GetDevice();
	// �e�N�X�`���[�ݒ�
	D3DXCreateTextureFromFile(pDevice, GOAL_TEX, &m_pTex);
	return S_OK;
}

// ----------------------------------------
// �ǂݍ��񂾏���j��
// ----------------------------------------
void CGoal::UnLoad(void)
{
}

// ----------------------------------------
// �쐬����
// ----------------------------------------
CGoal * CGoal::Create(
	D3DXVECTOR3 pos
)
{
	// �ϐ��錾
	CGoal * pGoal;		// �V�[��2D�N���X
	// �������̐���(����->��{�N���X,��->�h���N���X)
	pGoal = new CGoal();
	// �ʒu���
	pGoal->m_pos = pos;
	// ����������
	pGoal->Init();
	// ���������I�u�W�F�N�g��Ԃ�
	return pGoal;
}