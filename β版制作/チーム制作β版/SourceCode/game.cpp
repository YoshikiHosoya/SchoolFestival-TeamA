#include "game.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "inputKeyboard.h"
#include "fade.h"
#include "map.h"
#include "pause.h"
#include "ParticleManager.h"
#include "TexAnimation3D_Collision.h"
#include "item.h"
#include "UIManager.h"
#include "Scene.h"

#define _CRT_SECURE_NO_WARNINGS // �x������
int			CGame::m_Counter	= 0;
CPlayer		*CGame::m_pPlayer	= NULL;
CMap		*CGame::m_pMap		= NULL;

//==========================================================
// �R���X�g���N�^
//==========================================================
CGame::CGame()
{
}
//==========================================================
// �f�X�g���N�^
//==========================================================
CGame::~CGame()
{
}
//==========================================================
// ������
//==========================================================
HRESULT CGame::Init(void)
{

	m_pMap		= CMap::MapCreate(CMap::MAP_1);	// �}�b�v�̐���
	m_pPlayer	= CPlayer::Create();
	m_pPlayer->SetLife(500);
	m_pPlayer->SetPosition(D3DXVECTOR3(50.0f, 100.0f, 0.0f));

	m_pPause->CreatePause();

	//�p�[�e�B�N������
	CParticleManager::Create();
	// UI����
	CUIManager::Create();

	return S_OK;

}
//==========================================================
// �I��
//==========================================================
void CGame::Uninit(void)
{
}
//==========================================================
// �X�V
//==========================================================
void CGame::Update(void)
{
	m_pMap->UpdateDieFlag();

	if (m_pPlayer != nullptr && m_pPlayer->GetLife() <= 0)
	{
		m_pPlayer->Rerease();
		m_pPlayer = nullptr;
	}
 }
//==========================================================
// �v���C���[�擾
//==========================================================
CPlayer * CGame::GetPlayer(void)
{
	return m_pPlayer;
}
//==========================================================
// �}�b�v�擾
//==========================================================
CMap * CGame::GetMap(void)
{
	if (m_pMap)
	{
		return m_pMap;
	}
	return nullptr;
}

//==========================================================
// �̗͂̎擾
//==========================================================
void CGame::Draw(void)
{
}
//==========================================================
// �f�o�b�O���\�L
//==========================================================
void CGame::ShowDebugInfo(void)
{
	//�L�[�{�[�h���擾
	CKeyboard *key = CManager::GetInputKeyboard();;

	// �}�b�v�̍X�V
	m_pMap->MapUpdate();
}