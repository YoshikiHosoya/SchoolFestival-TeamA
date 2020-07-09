//====================================================================
// �G�l�~�[���� [enemy.cpp]: NORI
//====================================================================
#include "Enemy.h"
#include "inputKeyboard.h"
#include "model.h"
#include "game.h"
#include "fade.h"
#include "Xinput.h"
#include "collision.h"
#include "debugproc.h"
#include "item.h"
#include "EnemyAI.h"
#include "gun.h"
//====================================================================
//�}�N����`
//====================================================================
#define ENEMY_SIZE			(D3DXVECTOR3(50.0f,75.0f,0.0f)) //�G�̃T�C�Y

CEnemy::CEnemy(OBJ_TYPE type) :CCharacter(type)
{
	SetObjType(OBJTYPE_ENEMY);
}

CEnemy::~CEnemy()
{
	if (m_pAI != nullptr)
	{
		delete m_pAI;
		m_pAI = nullptr;
	}

	CItem::Create(this->GetPosition(), CItem::ITEMTYPE_HEAVYMACHINEGUN);
}
//====================================================================
//������
//====================================================================
HRESULT CEnemy::Init(void)
{
	//�L�����̏�����
	CCharacter::Init();
	LoadOffset(CCharacter::CHARACTER_TYPE_ENEMY);
	SetCharacterType(CCharacter::CHARACTER_TYPE_ENEMY);
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	m_Attack = false;

	// �e�̐���
	m_pGun = CGun::Create(GetCharacterModelPartsList(CModel::MODEL_ENEMY_RHAND)->GetMatrix());
	// �e�̒e�̎��
	m_pGun->GetTag() = TAG_ENEMY;

	// �����蔻�萶��
	GetCollision()->SetPos(&GetPosition());
	GetCollision()->SetPosOld(&GetPositionOld());
	GetCollision()->SetSize2D(ENEMY_SIZE);
	GetCollision()->SetMove(&GetMove());
	GetCollision()->DeCollisionCreate(CCollision::COLLISIONTYPE_CHARACTER);
	CCharacter::SetLife(50);
	return S_OK;
}
//====================================================================
//�I��
//====================================================================
void CEnemy::Uninit(void)
{
	CCharacter::Uninit();
}
//====================================================================
//�X�V
//====================================================================
void CEnemy::Update(void)
{
	CKeyboard *key;
	key = CManager::GetInputKeyboard();

	if (key->GetKeyboardTrigger(DIK_8))
	{
		SetMotion(CCharacter::ENEMY_MOTION_NORMAL);
	}
	if (key->GetKeyboardTrigger(DIK_9))
	{
		SetMotion(CCharacter::ENEMY_MOTION_WALK);
	}
	if (GetCollision() != nullptr)
	{
		 //���W�̍X�V
		GetCollision()->SetPos(&GetPosition());
	}
	//�̗͂�0�ȉ��ɂȂ�����
	if (this->GetLife() <= 0)
	{//�A�C�e���𐶐�
		m_pGun->Rerease();
		m_pGun = nullptr;
		//CItem::Create(this->GetPosition(), CItem::ITEMTYPE_HEAVYMACHINEGUN);
	}
	else
	{
		// �e����������ݒ�
		m_pGun->SetShotRot(GetShotDirection());
	}
	//AI�֘A����
	if (m_pAI != nullptr)
	{
		if (m_pAI->GetAIType() == m_pAI->AI_SHOT && m_pAI->GetShot() == true)
		{
			m_pGun->Shot();
		}
		//m_pAI->Update();
	}

	//CDebugProc::Print("\n�G�̃��C�t %d\n", CCharacter::GetLife());
	CCharacter::Update();
}
//====================================================================
//�`��
//====================================================================
void CEnemy::Draw(void)
{
	CCharacter::Draw();
}
//====================================================================
//�f�o�b�O
//====================================================================
void CEnemy::DebugInfo(void)
{
}
//====================================================================
//���f���̃N���G�C�g
//====================================================================
CEnemy *CEnemy::Create(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	CEnemy*pEnemy;
	pEnemy = new CEnemy(OBJTYPE_ENEMY);
	pEnemy->Init();
	pEnemy->m_pAI = CEnemyAI::CreateAI(pEnemy);
	return pEnemy;
}
bool CEnemy::DefaultMotion(void)
{
	SetMotion(CCharacter::ENEMY_MOTION_NORMAL);
	return true;
}
//====================================================================
//�ړ�
//====================================================================
void CEnemy::Move(float move, float fdest)
{
	GetMove().x += sinf(move * -D3DX_PI) * 1.0f;
	GetMove().z += cosf(move * -D3DX_PI) * 1.0f;
	//m_rotDest.y = fdest *  D3DX_PI;
}
