// ===================================================================
//
// shield�̏��� [shield.cpp]
// Author : �̂肳��
//
// ===================================================================
#include "shield.h"
#include "WeakEnemy.h"
#include "collision.h"
#include "particle.h"
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

	//�^�O�ݒ�
	CGameObject::SetTag(TAG::SHIELD);

	// �ϐ�������
	m_nLife = SHIELD_LIFE;				// �̗�
	// ������
	SetPosition(SHIELD_OFFSET);
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

	//�J�E���g�_�E��
	if (m_nCntState-- <= 0)
	{
		//�F�����ɖ߂�
		SetColorChangeFlag(false);
	}

	//���j����
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
	//�j��
	if (m_bBreak)
	{
		//���̐ݒ�
		SetPosition(m_ShieldPos);

		//�`��
		CModel::Draw();
	}
	else
	{
		//��̃}�g���b�N�X����ɕ`��
		CModel::Draw(*m_HasHandMtx);
	}
}
//====================================================================
//�f�o�b�O���\�L
//====================================================================
void CShield::DebugInfo()
{
	char aTreeName[MAX_TEXT] = {};
	sprintf(aTreeName, "ShieldInfo [%d]", CScene::GetID());

	if (ImGui::TreeNode(aTreeName))
	{
		ImGui::Text("m_ShieldPos [%.2f %.2f %.2f]", m_ShieldPos.x, m_ShieldPos.y, m_ShieldPos.z);
		ImGui::Text("m_BreakShieldMoveValue [%.2f %.2f %.2f]", m_BreakShieldMoveValue.x, m_BreakShieldMoveValue.y, m_BreakShieldMoveValue.z);
		ImGui::Text("m_BreakShieldRotValue [%.2f %.2f %.2f]", m_BreakShieldRotValue.x, m_BreakShieldRotValue.y, m_BreakShieldRotValue.z);

		ImGui::Text("m_nLife [%d]", m_nLife); ImGui::SameLine();
		ImGui::Text("m_nCntState [%d]", m_nCntState);

		ImGui::Text("m_bBreak [%d]", m_bBreak); ImGui::SameLine();
		ImGui::Text("m_nDeleteCnt [%d]", m_nDeleteCnt);

		ImGui::TreePop();
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
	pShield->SetModelID(MODEL_WEPON_SHIELD);

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
	DeleteCollision();
	m_bBreak = true;
	m_nDeleteCnt = SHIELD_DELETE_COUNT;
	SetRot(D3DXVECTOR3(D3DX_PI * 0.5f, D3DX_PI * 0.5f, 0.0f));
	m_BreakShieldMoveValue = (BREAK_SHIELD_DEFAULT);
}