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
//====================================================================
//�}�N����`
//====================================================================
#define ENEMY_SIZE			(D3DXVECTOR3(50.0f,75.0f,0.0f)) //�G�̃T�C�Y


CEnemy::CEnemy(OBJ_TYPE type) :CCharacter(type)
{
	SetObjType(OBJTYPE_ENEMY);
	m_pCollision = NULL;
}

CEnemy::~CEnemy()
{
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
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRendere()->GetDevice();
	m_Attack = false;

	// �����蔻�萶��
	m_pCollision = CCollision::Create();
	m_pCollision->SetPos(&GetPosition());
	m_pCollision->SetPosOld(&GetPositionOld());
	m_pCollision->SetSize2D(ENEMY_SIZE);
	m_pCollision->SetMove(&GetMove());
	m_pCollision->SetType(CCollision::OBJTYPE_ENEMY);
	m_pCollision->DeCollisionCreate(CCollision::COLLISIONTYPE_CHARACTER);

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

	if (m_pCollision != nullptr)
	{
		 //���W�̍X�V
		m_pCollision->SetPos(&GetPosition());
	}

	CDebugProc::Print("\n�G�̃��C�t %d\n", CCharacter::GetLife());
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
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRendere()->GetDevice();
	CEnemy*pEnemy;
	pEnemy = new CEnemy(OBJTYPE_ENEMY);
	pEnemy->Init();
	return pEnemy;
}
void CEnemy::DefaultMotion(void)
{
	SetMotion(CCharacter::ENEMY_MOTION_NORMAL);
}
//====================================================================
//�����蔻��̍폜
//====================================================================
void CEnemy::DeleteCollision(void)
{
	m_pCollision->ReleaseCollision(m_pCollision);
	m_pCollision = NULL;
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
