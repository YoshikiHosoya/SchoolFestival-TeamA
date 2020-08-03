//------------------------------------------------------------------------------
//
//�Q�[���̐i�s�Ǘ�  [GameManager.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "GameManager.h"
#include "scene2D.h"
#include "map.h"
#include "fade.h"
#include "Player.h"
#include "Playerui.h"
#include "game.h"
#include "camera.h"

//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CGameManager::CGameManager()
{
	m_nTimeCnt = 0;
}
//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CGameManager::~CGameManager()
{

}

//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
void CGameManager::Update()
{
	m_nCnt++;

	CPlayer *pPlayer = CManager::GetBaseMode()->GetPlayer();

	if (pPlayer)
	{
		if(pPlayer->GetPosition().x >= 8500.0f)
		{
			CManager::GetRenderer()->GetFade()->SetFade(CFADE::FADETYPE::FADETYPE_MAPMOVE, CMap::MAP_1_BOSS);
		}
	}

	if (m_pScene2D_GoSign)
	{
		if (CManager::GetGame()->GetMap()->GetMapNum() == CMap::MAP_1_1)
		{
			if (m_nCnt % 40 == 0)
			{
				m_pScene2D_GoSign->SetDisp(m_pScene2D_GoSign->GetDisp() ^ 1);
			}
		}
	}

	// �Q�[���N���X�̃|�C���^�擾
	CGame *pGame = (CGame*)CManager::GetBaseMode();

	// �Q�[�����[�h�Ńv���C����\�ȃ^�C�~���O�̎�
	if (pGame->GetGameMode() == CGame::GAME_MODE_NORMAL)
	{
		// �J�E���g���Z
		m_nTimeCnt++;
	}

	// 5�b�o�߂�����
	if (m_nTimeCnt >= 300)
	{
		if (CManager::GetBaseMode()->GetPlayer()->GetPlayerUI())
		{
			// �̗͂�0���傫��������
			if (CManager::GetBaseMode()->GetPlayer()->GetPlayerUI()->GetTime() > 0)
			{
				// �^�C�}�[�̒l����������
				CManager::GetBaseMode()->GetPlayer()->GetPlayerUI()->DecrementTime();
			}
			// �^�C�}�[��0�ȉ��ɂȂ�����
			else
			{
			}
		}

		// �^�C�}�[�J�E���g�����Z�b�g����
		m_nTimeCnt = 0;
	}
}

//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void CGameManager::Draw()
{

}

//------------------------------------------------------------------------------
//�f�o�b�O���\�L
//------------------------------------------------------------------------------
void CGameManager::ShowDebugInfo()
{
#ifdef _DEBUG

	ImGui::End();
#endif
}

//------------------------------------------------------------------------------
//��������
//------------------------------------------------------------------------------
std::unique_ptr<CGameManager> CGameManager::Create()
{
	//�������m��
	std::unique_ptr<CGameManager> pGameManager(new CGameManager);

	//nullcheck
	if (pGameManager)
	{
		////Go�T�C������
		//pGameManager->m_pScene2D_GoSign = CScene2D::CreateSceneManagement(D3DXVECTOR3(1000.0f, 300.0f, 0.0f), D3DXVECTOR3(200.0f, 120.0f,0.0f),CScene::OBJTYPE_UI);
		//pGameManager->m_pScene2D_GoSign->BindTexture(CTexture::GetTexture(CTexture::TEX_ITEM_MEDAL));
		//pGameManager->m_pScene2D_GoSign->SetColor(WhiteColor);

		return pGameManager;
	}
	return nullptr;
}
