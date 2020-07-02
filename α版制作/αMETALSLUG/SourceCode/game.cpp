#include "game.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "inputKeyboard.h"
#include "fade.h"
#include "map.h"
#include "pause.h"
#include "TexAnimation3D.h"
#include "TexAnimation2D.h"
#include "particleManager.h"
#include "particle.h"
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
	m_pPlayer->SetLife(50);
	m_pPlayer->SetPosition(D3DXVECTOR3(50.0f, 100.0f, 0.0f));

	m_pPause->CreatePause();

	//�p�[�e�B�N������
	CParticleManager::Create();

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
	//2D�G�t�F�N�g
	if (key->GetKeyboardTrigger(DIK_2))
	{
		CTexAnimation2D::Create(SCREEN_CENTER_POS, D3DXVECTOR3(150.0f, 150.0f, 0.0f), ZeroVector3, CTexture::SEPARATE_TEX_EFFECT_EXPLOSION01, 3, CScene::OBJTYPE_EXPROSION);
	}
	//3D�G�t�F�N�g
	if (key->GetKeyboardTrigger(DIK_3))
	{
		CTexAnimation3D::Create(m_pPlayer->GetPosition(), D3DXVECTOR3(150.0f, 150.0f, 0.0f), ZeroVector3, CTexture::SEPARATE_TEX_EFFECT_EXPLOSION01, 3, CScene::OBJTYPE_EXPROSION);
	}
	//�p�[�e�B�N��
	if (key->GetKeyboardTrigger(DIK_4))
	{
		CParticle::Create(m_pPlayer->GetPosition(), 60, 50.0f, RedColor, 20, 5);
	}
	//�p�[�e�B�N�� �e�L�X�g�̃p�����[�^�Q��
	if (key->GetKeyboardTrigger(DIK_5))
	{
		CParticle::CreateFromText(m_pPlayer->GetPosition(), CParticleParam::PARTICLE_DEFAULT);
	}
	//�p�[�e�B�N�� �e�L�X�g�̃p�����[�^�Q��
	if (key->GetKeyboardTrigger(DIK_5))
	{
		CParticle::CreateFromText(m_pPlayer->GetPosition(), CParticleParam::PARTICLE_EXPLOSION);
	}

	// �}�b�v�̍X�V
	m_pMap->MapUpdate();
}