// ===================================================================
//
// shield�̏��� [shield.cpp]
// Author : �̂肳��
//
// ===================================================================
#include "shield.h"
#include "WeakEnemy.h"
#include "collision.h"

// ===================================================================
// �ÓI�����o�ϐ��̏�����
// ===================================================================

// ===================================================================
// �}�N����`
// ===================================================================
#define SHIELD_LIFE				(12)			// shield�̗̑�
#define SHIELD_SIZE				(D3DXVECTOR3(30.0f,100.0f,0.0f))
#define SHIELD_OFFSET			(D3DXVECTOR3(0.0f,-30.0f,0.0f))
#define SHIELD_DELETE_COUNT		(60)
#define DAMAGE_FLASH_COUNT		(5)
#define BREAK_SHIELD_DEFAULT	(D3DXVECTOR3(CHossoLibrary::Random(20.0f), 15.0f, 0.0f))
// ===================================================================
// �R���X�g���N�^
// ===================================================================
CShield::CShield(OBJ_TYPE type) :CModel(type)
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
	m_bBreak = false;

	CModel::Init();
	// �ϐ�������
	m_nLife = SHIELD_LIFE;				// �̗�
	// ������
	SetPosition(D3DXVECTOR3(0.0f,-20.0f,0.0f));
	// �����蔻�萶��
	GetCollision()->SetPos(&GetPosition());
	GetCollision()->SetSize2D(SHIELD_SIZE);
	GetCollision()->DeCollisionCreate(CCollision::COLLISIONTYPE_NORMAL);

	//�_���[�W�󂯂����̓_�ŐF
	SetAddColor(D3DXCOLOR(1.0f, 0.4f, 0.0f, 0.0f));

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


	if (m_nCntState-- <= 0)
	{
		SetColorChangeFlag(false);
	}

	if (m_bBreak)
	{
		//������J�E���g�_�E��
		m_nDeleteCnt--;

		//��������΂�
		m_BreakShieldMoveValue.y -= 0.5f;
		m_ShieldPos += m_BreakShieldMoveValue;

		//����]
		GetRot().x += 0.05f;
		GetRot().z += 0.25f;

		//�J�E���g��0�ɂȂ�����
		if (m_nDeleteCnt <= 0)
		{
			//����
			Rerease();
			return;
		}
	}
	else
	{
		//���̍��W
		m_ShieldPos = D3DXVECTOR3(m_HasHandMtx->_41, m_HasHandMtx->_42, m_HasHandMtx->_43) + SHIELD_OFFSET;

		//�����蔻��̍��W�ݒ�
		GetCollision()->SetPos(&m_ShieldPos);
	}
}
// ===================================================================
// �`�揈��
// ===================================================================
void CShield::Draw(void)
{
	if (m_bBreak)
	{
		SetPosition(m_ShieldPos);
		CModel::Draw();
	}
	else
	{
		CModel::Draw(*m_HasHandMtx);
	}
}
//====================================================================
//���f���̃N���G�C�g
//====================================================================
CShield *CShield::Create()
{
	CShield*pShield;
	pShield = new CShield(OBJTYPE_SHIELD);
	pShield->Init();
	// ���f���^�C�v�̐ݒ�
	pShield->SetType(WEPON_MODEL);
	// ���f���J�E���g�̐ݒ�
	pShield->SetModelConut(MODEL_WEPON_SHIELD);

	return pShield;
}
//====================================================================
//�_���[�W�󂯂�
//====================================================================
void CShield::AddDamage(int nDamage)
{
	m_nLife -= nDamage;

	//�Ԃ��_��
	SetColorChangeFlag(true);
	m_nCntState = DAMAGE_FLASH_COUNT;


	//���C�t���Ȃ��Ȃ�����
	if (m_nLife <= 0)
	{
		m_HasEnemyPtr->ShieldBreak();

	}
}
//====================================================================
//����������Ԑݒ�
//====================================================================
void CShield::AwayShield()
{
	m_bBreak = true;
	m_nDeleteCnt = SHIELD_DELETE_COUNT;
	DeleteCollision();
	SetRot(D3DXVECTOR3(D3DX_PI * 0.5f, D3DX_PI * 0.5f, 0.0f));
	m_BreakShieldMoveValue = (BREAK_SHIELD_DEFAULT);
}