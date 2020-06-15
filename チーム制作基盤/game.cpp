#include "game.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "inputKeyboard.h"
#include "fade.h"
#include "createmap.h"
#include "Enemy.h"
#include "pause.h"
#define _CRT_SECURE_NO_WARNINGS // �x������
int CGame::m_Counter = 0;
CPlayer *CGame::m_pPlayer = NULL;
CEnemy *CGame::m_pEnemy = NULL;
int CGame::HP = 0;
int CGame::HPPotion = 0;
int CGame::MP = 0;
int CGame::MPPotion = 0;

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
	m_pCreateMap = CCreateMap::Create(1);
	m_pPlayer = CPlayer::Create();
	m_pPlayer->SetLife(50);
	m_pPlayer->SetPosition(D3DXVECTOR3(50.0f, 100.0f, 0.0f));

	m_pEnemy = CEnemy::Create();
	m_pEnemy->SetLife(50);
	m_pEnemy->SetPosition(D3DXVECTOR3(0.0f, 100.0f, 0.0f));

	m_pPause->CreatePause();
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
	CKeyboard *key;
	key = CManager::GetInputKeyboard();
	if (key->GetKeyboardTrigger(DIK_F9))
	{
		CScene::StopUpdate();
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
// �̗͂̎擾
//==========================================================
int CGame::GetHP(void)
{
	return HP;
}
void CGame::Draw(void)
{
}
void CGame::ShowDebugInfo(void)
{
}
//==========================================================
// �`��
//==========================================================
CCreateMap * CGame::GetCreateMap(void)
{
	return m_pCreateMap;
}
