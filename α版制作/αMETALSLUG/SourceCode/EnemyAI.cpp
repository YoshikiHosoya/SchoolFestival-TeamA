//=============================================================================
// AI���� [EnemyAI.cpp] Hanzawa
//=============================================================================
#include "EnemyAI.h"
#include "renderer.h"
#include "inputKeyboard.h"
#include "Enemy.h"
#include "Player.h"
#include "manager.h"
#include "BaseMode.h"
#include "map.h"
CEnemyAI::CEnemyAI()
{
}

CEnemyAI::~CEnemyAI()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CEnemyAI::Init(void)
{
	m_cast = 0;
	m_bShot = false;
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CEnemyAI::Uninit(void)
{
}

//=============================================================================
// �X�V����
//=============================================================================
void CEnemyAI::Update(void)
{
	CPlayer *pPlayer = CManager::GetBaseMode()->GetPlayer();
	for (int nCnt = 0; nCnt < CManager::GetBaseMode()->GetMap()->GetMaxEnemy(); nCnt++)
	{
		CEnemy *pEnemy = CManager::GetBaseMode()->GetMap()->GetEnemy(nCnt);
		if (pEnemy != nullptr)
		{
			if (pPlayer != nullptr)
			{
				if (m_bShot == true)
				{
					CDebugProc::Print("�G�l�~�[�V���b�g�F���s\n");
					m_cast++;
					m_AItype = AI_NONE;
					if (m_cast == 120)
					{
						m_cast = 0;
						m_bShot = false;
					}
				}
				CDebugProc::Print("�G�l�~�[�V���b�g�F�Î~\n");
				if (pEnemy->GetPosition().x > pPlayer->GetPosition().x)
				{
					pEnemy->SetRot(D3DXVECTOR3(0.0f, 0.5f*  D3DX_PI, 0.0f));
					if (m_bShot == false)
					{
						m_AItype = AI_SHOT;
						m_bShot = true;
					}
				}
				else
				{
					pEnemy->SetRot(D3DXVECTOR3(0.0f, -0.5f*  D3DX_PI, 0.0f));
					m_AItype = AI_STOP;
				}

			}
		}
	}
	CDebugProc::Print("�G�l�~�[�V���b�g�L���X�g�^�C���F%d\n",m_cast);

}
//=============================================================================
// �^�C�g�����
//=============================================================================
void CEnemyAI::Draw(void)
{
}
//=============================================================================
// �f�o�b�O
//=============================================================================
void CEnemyAI::DebugInfo(void)
{
}
//=============================================================================
// AI�̃N���G�C�g
//=============================================================================
CEnemyAI * CEnemyAI::CreateAI(void)
{
	CEnemyAI*pEnemyAI;
	pEnemyAI = new CEnemyAI();
	pEnemyAI->Init();
	return pEnemyAI;
}
//=============================================================================
// AI�̃^�C�v�擾
//=============================================================================
CEnemyAI::AI_STATE CEnemyAI::GetAIType(void)
{
	return m_AItype;
}
