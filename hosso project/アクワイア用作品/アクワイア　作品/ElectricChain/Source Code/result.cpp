//------------------------------------------------------------------------------
//
//���U���g����  [result.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "scene.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "fade.h"
#include "result.h"
#include "UI.h"
#include "Map.h"
#include "multinumber.h"
#include "score.h"
#include "player.h"
#include "sound.h"
#include "effectanimation2D.h"
//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------
#define ITEM_COMBO_POP		(40)									//�R���{�����\������J�E���^
#define ITEM_KILL_POP		(80)									//�L�������\�������J�E���^
#define ITEM_TOTAL_POP		(150)									//�g�[�^�����\�������J�E���^
#define DEFAULT_PLAYER_POS	(D3DXVECTOR3(0.0f, 0.0f, 1000.0f))		//�v���C���[�������W
//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CResult::CResult()
{
	m_nCntResult = 0;
}

//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CResult::~CResult()
{
}

//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CResult::Init(HWND hWnd)
{
	//UI����
	CUI::LoadPlace(CUI::SCENE_RESULT);

	//�}�b�v����
	CMap::Create();

	//�v���C���[����
	CPlayer::Create(DEFAULT_PLAYER_POS);

	//�J�������W�ݒ�
	CManager::GetRenderer()->GetCamera()->SetCameraPos(DEFAULT_PLAYER_POS + D3DXVECTOR3(130.0f,100.0f,0.0f), DEFAULT_PLAYER_POS + D3DXVECTOR3(-80.0f, 40.0f, -300.0f));
	CManager::GetRenderer()->GetCamera()->SetState(CCamera::CAMERA_RESULT);

	return S_OK;
}

//------------------------------------------------------------------------------
//�I������
//------------------------------------------------------------------------------
void CResult::Uninit()
{
	//�I������
	CScene::ReleaseAll();
}

//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CResult::Update()
{
	//�J�E���^++
	m_nCntResult++;

	//�J�E���^�ɉ����ă��U���g�̍��ڕ\��
	PopResultItem();

	//�t�F�[�h���ĂȂ���
	if (CManager::GetRenderer()->GetFade()->GetFade() == CFade::FADE_NONE)
	{
		//�����{�^���������Ƃ�
		if (CHossoLibrary::CheckAnyButton())
		{
			//���ڂ��S���\������ĂȂ���
			if (m_nCntResult <= ITEM_TOTAL_POP)
			{
				//�S���\�������Ƃ��܂ŃJ�E���^���΂�
				m_nCntResult = ITEM_TOTAL_POP;
			}
			//���ڂ��S���\������Ă�����
			else
			{
				//�X�e�[�g�ύX
				CManager::GetRenderer()->GetFade()->SetModeFade(CManager::MODE_RANKING);
				CManager::GetSound()->Play(CSound::LABEL_SE_DECISION);
			}
		}
	}
}

//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void CResult::Draw()
{

}

//------------------------------------------------------------------------------
//�J�E���^�ɉ����č��ڂ�\��
//------------------------------------------------------------------------------
void CResult::PopResultItem()
{

	if (m_nCntResult > ITEM_COMBO_POP && m_pNumberList.size() <= CResult::RESULT_COMBO)
	{
		//Combo
		m_pNumberList.emplace_back(CMultiNumber::Create(
			D3DXVECTOR3(720.0f, 270.0f, 0.0f),
			D3DXVECTOR3(40.0f, 80.0f, 0.0f),
			CScore::GetCombo(),
			4,
			CScene::OBJTYPE_NUMBER));

		//���̃G�t�F�N�g
		CEffectAnimation2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 270.0f, 0.0f),
			D3DXVECTOR3(SCREEN_WIDTH, 200.0f, 0.0f), CTexture::SEPARATE_TEX_EFFECT_LINETHUNDER, 0.0f, 3, CScene::OBJTYPE_2DEFFECT);

		CManager::GetSound()->Play(CSound::LABEL_SE_RANKING_THUNDER);
	}
	if (m_nCntResult > ITEM_KILL_POP && m_pNumberList.size() <= CResult::REUSLT_KILL)
	{
		//Kill
		m_pNumberList.emplace_back(CMultiNumber::Create(
			D3DXVECTOR3(720.0f, 390.0f, 0.0f),
			D3DXVECTOR3(40.0f, 80.0f, 0.0f),
			CScore::GetKill(),
			4,
			CScene::OBJTYPE_NUMBER));
		//���̃G�t�F�N�g
		CEffectAnimation2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 390.0f, 0.0f),
			D3DXVECTOR3(SCREEN_WIDTH, 200.0f, 0.0f), CTexture::SEPARATE_TEX_EFFECT_LINETHUNDER, 0.0f, 3, CScene::OBJTYPE_2DEFFECT);

		CManager::GetSound()->Play(CSound::LABEL_SE_RANKING_THUNDER);

	}
	if (m_nCntResult > ITEM_TOTAL_POP && m_pNumberList.size() <= CResult::RESULT_TOTAL)
	{
		//Total
		m_pNumberList.emplace_back(CMultiNumber::Create(
			D3DXVECTOR3(1020.0f, 520.0f, 0.0f),
			D3DXVECTOR3(55.0f, 120.0f, 0.0f),
			CScore::GetScore(),
			6,
			CScene::OBJTYPE_NUMBER));
		//���̃G�t�F�N�g
		CEffectAnimation2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 520.0f, 0.0f),
			D3DXVECTOR3(SCREEN_WIDTH, 500.0f, 0.0f), CTexture::SEPARATE_TEX_EFFECT_LINETHUNDER, 0.0f, 4, CScene::OBJTYPE_2DEFFECT);

		CManager::GetSound()->Play(CSound::LABEL_SE_RANKING_THUNDER);

		//�_�ł�����
		m_pNumberList[RESULT_TOTAL]->Settype(CMultiNumber::TYPE_FLASHING);

	}

}
