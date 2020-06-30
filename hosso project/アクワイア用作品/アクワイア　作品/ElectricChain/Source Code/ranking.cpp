//------------------------------------------------------------------------------
//
//�����L���O����  [ranking.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "scene.h"
#include "ranking.h"
#include "manager.h"
#include "renderer.h"
#include "fade.h"
#include "multinumber.h"
#include "UI.h"
#include "effectanimation2D.h"
#include "score.h"
#include "sound.h"
//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------
#define FADE_COUNT				(520)		//�t�F�[�h����܂ł̃J�E���g
#define RANKING_POP_INTERVAL	(40)		//�����L���O���o�Ă���C���^�[�o��
//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CRanking::CRanking()
{
	m_nCntFadeTitle = FADE_COUNT;
}
//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CRanking::~CRanking()
{
}

//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CRanking::Init(HWND hWnd)
{
	CUI::LoadPlace(CUI::SCENE_RANKING);

	return S_OK;
}

//------------------------------------------------------------------------------
//�I������
//------------------------------------------------------------------------------
void CRanking::Uninit()
{
	//�I������
	CScene::ReleaseAll();
}

//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CRanking::Update()
{
	m_nCntFadeTitle--;

	//���Ԋu�ň������L���O�\��
	if (m_nCntFadeTitle % RANKING_POP_INTERVAL == 0)
	{
		//5�܂��o�ĂȂ���
		if (m_pMultiNumberList.size() < 5)
		{
			//�����L���O����
			CreateRank();
		}
	}


	//�t�F�[�h���ĂȂ���
	if (CManager::GetRenderer()->GetFade()->GetFade() == CFade::FADE_NONE)
	{
		//������x���Ԃ�������
		if ((m_nCntFadeTitle < 0 || CHossoLibrary::CheckAnyButton()))
		{
			if (m_pMultiNumberList.size() >= 5)
			{
				//�^�C�g���ɖ߂�
				CManager::GetRenderer()->GetFade()->SetModeFade(CManager::MODE_TITLE);
				CManager::GetSound()->Play(CSound::LABEL_SE_DECISION);
			}
			else
			{
				while (m_pMultiNumberList.size() < 5)
				{
					//�����L���O����
					CreateRank();
				}
			}
		}
	}
}

//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void CRanking::Draw()
{
}

//------------------------------------------------------------------------------
//�����N�����@�G�t�F�N�g�Ɖ��ƈꏏ��
//------------------------------------------------------------------------------
void CRanking::CreateRank()
{
	//�����L���O�̐����\��
	std::shared_ptr<CMultiNumber> pMultiNumber =
		CMultiNumber::Create(
			D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 650.0f - (m_pMultiNumberList.size() * 100.0f), 0.0f),
			D3DXVECTOR3(40.0f, 80.0f, 0.0f),
			CScore::GetRankingScore(4 - m_pMultiNumberList.size()),
			6,
			CScene::OBJTYPE_NUMBER);

	//�������̃X�R�A�Ɠ����X�R�A��������
	if (CScore::GetScore() == CScore::GetRankingScore(4 - m_pMultiNumberList.size()))
	{
		//�_��
		pMultiNumber->Settype(CMultiNumber::TYPE_FLASHING);
	}

	//���̃G�t�F�N�g
	CEffectAnimation2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 650.0f - (m_pMultiNumberList.size() * 100.0f), 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH, 200.0f + (m_pMultiNumberList.size() * 50.0f), 0.0f), CTexture::SEPARATE_TEX_EFFECT_LINETHUNDER, 0.0f, 3, CScene::OBJTYPE_2DEFFECT);

	//�z��ɒǉ�
	m_pMultiNumberList.emplace_back(std::move(pMultiNumber));

	//���Đ�
	CManager::GetSound()->Play(CSound::LABEL_SE_RANKING_THUNDER);
}
