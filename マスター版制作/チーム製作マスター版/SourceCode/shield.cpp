// ===================================================================
//
// shield�̏��� [shield.cpp]
// Author : �̂肳��
//
// ===================================================================
#include "shield.h"
#include "bullet.h"
#include "collision.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "debugproc.h"
#include "collision.h"
#include "Player.h"
#include "Enemy.h"
#include "map.h"
#include "Obstacle.h"
#include "particle.h"
// ===================================================================
// �ÓI�����o�ϐ��̏�����
// ===================================================================

// ===================================================================
// �}�N����`
// ===================================================================
#define SHIELD_LIFE				(20)			// shield�̗̑�
#define SHIELD_SIZE				(D3DXVECTOR3(100.0f,100.0f,0.0f))
// ===================================================================
// �R���X�g���N�^
// ===================================================================
CShield::CShield(OBJ_TYPE type) :CObstacle(type)
{
}

// ===================================================================
// �f�X�g���N�^
// ===================================================================
CShield::~CShield()
{
}

// ===================================================================
// ����������
// ===================================================================
HRESULT CShield::Init()
{
	CModel::Init();
	// �ϐ�������
	m_nLife = SHIELD_LIFE;				// �̗�
	// ������
	SetPosition(D3DXVECTOR3(200,100,0));
	// �����蔻�萶��
	GetCollision()->SetPos(&GetPosition());
	GetCollision()->SetSize2D(SHIELD_SIZE);
//	GetCollision()->SetMove(&GetMove());
	GetCollision()->DeCollisionCreate(CCollision::COLLISIONTYPE_NORMAL);

	return S_OK;
}

// ===================================================================
// �I������
// ===================================================================
void CShield::Uninit(void)
{
	CModel::Uninit();
}

// ===================================================================
// �X�V����
// ===================================================================
void CShield::Update(void)
{
	// �X�V
	CModel::Update();
}
// ===================================================================
// �`�揈��
// ===================================================================
void CShield::Draw(void)
{
	CModel::Draw();
}
//====================================================================
//���f���̃N���G�C�g
//====================================================================
CShield *CShield::Create(D3DXMATRIX *mtx)
{
	CShield*pShield;
	pShield = new CShield(OBJTYPE_SHIELD);
	pShield->Init();
	// �}�g���b�N�X���
	pShield->m_HasHandMtx = mtx;
	// ���f���^�C�v�̐ݒ�
	pShield->SetType(WEPON_MODEL);
	// ���f���J�E���g�̐ݒ�
	pShield->SetModelConut(MODEL_WEPON_SHIELD);

	return pShield;
}