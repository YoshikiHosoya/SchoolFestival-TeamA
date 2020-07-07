// =====================================================================================================================================================================
//
// �ߗ��̏��� [prisoner.h]
// Author : fujiwara masato
//
// =====================================================================================================================================================================
#include "prisoner.h"
#include "model.h"
#include "collision.h"
#include "game.h"
#include "manager.h"
#include "map.h"
#include "item.h"
#include "debugproc.h"
//====================================================================
//�}�N����`
//====================================================================
#define PRISONER_COLLISION_SIZE			(D3DXVECTOR3(50.0f,65.0f,0.0f))			 //�ߗ��̃T�C�Y
#define PRISONER_DIETIME				(180)									 //�ߗ������ł���܂ł̎���

// =====================================================================================================================================================================
//
// �R���X�g���N�^
//
// =====================================================================================================================================================================
CPrisoner::CPrisoner(OBJ_TYPE type) :CCharacter(type)
{
	// �ߗ��̏������
	m_PrisonerState		= PRISONER_STATE_STAY;
	// �ߗ������ł���܂ł̃J�E���g��������
	m_nDieCount			= 0;
	// �|�C���^����������ێg���邩�ǂ���
	m_bUse				= false;
}
// =====================================================================================================================================================================
//
// �f�X�g���N�^
//
// =====================================================================================================================================================================
CPrisoner::~CPrisoner()
{
}

// =====================================================================================================================================================================
//
// ����������
//
// =====================================================================================================================================================================
HRESULT CPrisoner::Init(void)
{
	// �L�����̏�����
	CCharacter::Init();
	// �I�t�Z�b�g�̎擾
	LoadOffset(CCharacter::CHARACTER_TYPE_PRISONER);
	// �L�����N�^�[�^�C�v�̐ݒ�
	SetCharacterType(CCharacter::CHARACTER_TYPE_PRISONER);
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �����蔻�萶��
	GetCollision()->SetPos(&GetPosition());
	GetCollision()->SetSize2D(PRISONER_COLLISION_SIZE);
	GetCollision()->SetMove(&GetMove());
	GetCollision()->DeCollisionCreate(CCollision::COLLISIONTYPE_CHARACTER);

	return S_OK;
}
//====================================================================
//�I��
//====================================================================
void CPrisoner::Uninit(void)
{
	CCharacter::Uninit();
}
//====================================================================
//�X�V
//====================================================================
void CPrisoner::Update(void)
{
	// �����蔻��
	if (GetCollision() != nullptr)
	{
		// ���W�̍X�V pos
		GetCollision()->SetPos(&GetPosition());
	}

	// �ߗ��̏�ԕʏ���
	this->PrisonerState();

	// �}�b�v�̃|�C���^�擾
	CMap *pMap;
	pMap = CManager::GetBaseMode()->GetMap();
	// �L�����N�^�[�̍X�V
	CCharacter::Update();

	// �ߗ��̏��
	CDebugProc::Print("\n �ߗ��̏�� %d\n\n", m_PrisonerState);
}
//====================================================================
//�`��
//====================================================================
void CPrisoner::Draw(void)
{
	CCharacter::Draw();
}
//====================================================================
//�f�o�b�O
//====================================================================
void CPrisoner::DebugInfo(void)
{
	//CDebugProc::Print("");
}
//====================================================================
//���f���̃N���G�C�g
//====================================================================
CPrisoner *CPrisoner::Create()
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���������m��
	CPrisoner*pPrisoner = new CPrisoner(OBJTYPE_PRISONER);
	// ������
	pPrisoner->Init();
	// �l��Ԃ�
	return pPrisoner;
}
//====================================================================
//�ߗ��̃f�t�H���g���[�V����
//====================================================================
bool CPrisoner::DefaultMotion(void)
{
	SetMotion(CCharacter::PRISONER_MOTION_STAY);
	return false;
}

//====================================================================
//�ߗ��̏�ԕʏ���
//====================================================================
void CPrisoner::PrisonerState()
{
	switch (m_PrisonerState)
	{
		// �ߗ��̏�ԃA�C�e���𗎂Ƃ���ԂɂȂ�����
	case PRISONER_STATE_DROPITEM:
	{
		// �A�C�e���𗎂Ƃ����[�V����
		//

		// �A�C�e���̐���
		CItem::RandCreate(GetPosition());
		// �ߗ��̏�Ԃ̕ύX
		this->SetPrisonerState(PRISONER_STATE_RUN);
	}
	break;

	case PRISONER_STATE_RUN:
	{
		// ���ɕ���
		SetMove(D3DXVECTOR3(-1.0f, 0.0f, 1.0f));
		Move(-1.0f, -1.57f);

		// ���ł܂ł̃J�E���g�����Z
		m_nDieCount++;
		// �J�E���g����v�l�𒴂�����
		if (m_nDieCount >= PRISONER_DIETIME)
		{
			// �폜
			Rerease();
		}

	}
	default:
		break;
	}
}

//====================================================================
//�ړ�
//====================================================================
void CPrisoner::Move(float move, float fdest)
{
	GetMove().x += sinf(move * -D3DX_PI) * 1.0f;
	GetMove().z += cosf(move * -D3DX_PI) * 1.0f;
	GetRotDest().y = fdest *  D3DX_PI;
}
