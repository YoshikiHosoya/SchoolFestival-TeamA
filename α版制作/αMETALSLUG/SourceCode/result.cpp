#include "result.h"
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

#define _CRT_SECURE_NO_WARNINGS // �x������
int			CResult::m_Counter = 0;
CPlayer		*CResult::m_pPlayer = NULL;
CMap		*CResult::m_pMap = NULL;

//==========================================================
// �R���X�g���N�^
//==========================================================
CResult::CResult()
{
}
//==========================================================
// �f�X�g���N�^
//==========================================================
CResult::~CResult()
{
}
//==========================================================
// ������
//==========================================================
HRESULT CResult::Init(void)
{

	m_pMap = CMap::MapCreate(CMap::MAP_1);	// �}�b�v�̐���
	m_pPause->CreatePause();
	m_pPlayer = CPlayer::Create();
	m_pPlayer->SetLife(500);
	m_pPlayer->SetPosition(D3DXVECTOR3(50.0f, 100.0f, 0.0f));

	//�p�[�e�B�N������
	CParticleManager::Create();
	// UI����
	CUIManager::Create();

	return S_OK;

}
//==========================================================
// �I��
//==========================================================
void CResult::Uninit(void)
{
}
//==========================================================
// �X�V
//==========================================================
void CResult::Update(void)
{
	m_pMap->UpdateDieFlag();

	if (m_pPlayer != nullptr && m_pPlayer->GetLife() <= 0)
	{
		m_pPlayer->Rerease();
		m_pPlayer = nullptr;
	}
	//�L�[�{�[�h���擾
	CKeyboard *key = CManager::GetInputKeyboard();;
	if (key->GetKeyboardTrigger(DIK_RETURN))
	{
		CManager::GetRenderer()->GetFade()->SetFade(CManager::MODE_TITLE);
	}
}
//==========================================================
// �v���C���[�擾
//==========================================================
CPlayer * CResult::GetPlayer(void)
{
	return m_pPlayer;
}
//==========================================================
// �}�b�v�擾
//==========================================================
CMap * CResult::GetMap(void)
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
void CResult::Draw(void)
{
}
//==========================================================
// �f�o�b�O���\�L
//==========================================================
void CResult::ShowDebugInfo(void)
{
	//�L�[�{�[�h���擾
	CKeyboard *key = CManager::GetInputKeyboard();;

	// �}�b�v�̍X�V
	m_pMap->MapUpdate();
}