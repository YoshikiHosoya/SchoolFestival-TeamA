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
#include "scoremanager.h"
#include "ModelSet.h"

// =====================================================================================================================================================================
//�}�N����`
// =====================================================================================================================================================================

// =====================================================================================================================================================================
// �ÓI�����o�ϐ��̏�����
// =====================================================================================================================================================================
PRISONER_DATA		CPrisoner::m_PrisonerData	= {};

// =====================================================================================================================================================================
// �e�L�X�g�t�@�C����
// =====================================================================================================================================================================
char *CPrisoner::m_PrisonerFileName =
{
	"data/Load/Prisoner/PrisonerData.txt" 			// �ߗ��̏��
};

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
	// �X�e�[�g���؂�ւ��܂ł̎���
	m_StateTime			= 60;
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
	GetModelSet()->LoadOffset(CModelSet::CHARACTER_TYPE_PRISONER);
	// �L�����N�^�[�^�C�v�̐ݒ�
	GetModelSet()->SetCharacterType(CModelSet::CHARACTER_TYPE_PRISONER);

	GetModelSet()->SetMotion(CModelSet::PRISONER_MOTION_STAY);
	CCharacter::SetState(CCharacter::CHARACTER_STATE_NONE);

	Move(0.0f, -1.57f);
	// �����蔻�萶��
	GetCollision()->SetPos(&GetPosition());
	GetCollision()->SetSize(m_PrisonerData.CollisionSize);
	GetCollision()->SetMove(&GetMove());
	GetCollision()->DeCollisionCreate(CCollision::COLLISIONTYPE_NORMAL);
	GetCollision()->SetGameObject(this);

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
	//�`��͈͓̔����`�F�b�N
	if (!CheckDrawRange())
	{
		// �����蔻��
		if (GetCollision() != nullptr)
		{
			// ���W�̍X�V pos
			GetCollision()->SetPos(&GetPosition());
			if (m_PrisonerState != PRISONER_STATE_STAY)
			{
				//����
				SetDieFlag(true);
			}
			//�������Ȃ�
			return;
		}
	}

	// �ߗ��̏�ԕʏ���
	this->PrisonerState();
	// �L�����N�^�[�̍X�V
	CCharacter::Update();
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
}
//====================================================================
//���f���̃N���G�C�g
//====================================================================
CPrisoner *CPrisoner::Create()
{
	// ���������m��
	CPrisoner*pPrisoner = new CPrisoner(OBJTYPE_PRISONER);
	// ������
	pPrisoner->Init();
	// �l��Ԃ�
	return pPrisoner;
}

// =====================================================================================================================================================================
//
// �ߗ��̏��̓ǂݍ���
//
// =====================================================================================================================================================================
void CPrisoner::PrisonerLoad()
{
	// �t�@�C���|�C���g
	FILE *pFile;

	char cReadText[128];			// �����Ƃ��ēǂݎ��
	char cHeadText[128];			// ��r�p
	char cDie[128];					// �s�v�ȕ���

									// �t�@�C�����J��
	pFile = fopen(m_PrisonerFileName, "r");

	// �J���Ă���Ƃ�
	if (pFile != NULL)
	{
		// SCRIPT������܂Ń��[�v
		while (strcmp(cHeadText, "SCRIPT") != 0)
		{
			fgets(cReadText, sizeof(cReadText), pFile); // �ꕶ�ǂݍ���
			sscanf(cReadText, "%s", &cHeadText);		// ��r�p�e�L�X�g�ɕ�������
		}

		// SCRIPT��������
		if (strcmp(cHeadText, "SCRIPT") == 0)
		{
			// END_SCRIPT������܂Ń��[�v
			while (strcmp(cHeadText, "END_SCRIPT") != 0)
			{
				fgets(cReadText, sizeof(cReadText), pFile); // �ꕶ�ǂݍ���
				sscanf(cReadText, "%s", &cHeadText);		// ��r�p�e�L�X�g�ɕ�������

															// ITEMSET��������
				if (strcmp(cHeadText, "PRISONERSET") == 0)
				{
					// END_ITEMSET������܂Ń��[�v
					while (strcmp(cHeadText, "END_PRISONERSET") != 0)
					{
						fgets(cReadText, sizeof(cReadText), pFile); // �ꕶ�ǂݍ���
						sscanf(cReadText, "%s", &cHeadText);		// ��r�p�e�L�X�g�ɕ�������

						// DELETE��������
						if (strcmp(cHeadText, "DELETE") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_PrisonerData.nDeleteTime);	// ��r�p�e�L�X�g��DELETE����
						}
						// SPEED��������
						else if (strcmp(cHeadText, "SPEED") == 0)
						{
							sscanf(cReadText, "%s %s %f", &cDie, &cDie, &m_PrisonerData.fMoveSpeed);	// ��r�p�e�L�X�g��SPEED����
						}
						// COLLISIONSIZE��������
						else if (strcmp(cHeadText, "COLLISIONSIZE") == 0)
						{
							sscanf(cReadText, "%s %s %f %f %f", &cDie, &cDie,
								&m_PrisonerData.CollisionSize.x,
								&m_PrisonerData.CollisionSize.y,
								&m_PrisonerData.CollisionSize.z);										// ��r�p�e�L�X�g��COLLISIONSIZE����
						}
						else if (strcmp(cHeadText, "END_PRISONERSET") == 0)
						{
						}
					}
				}
			}
		}
		// �t�@�C�������
		fclose(pFile);
	}
	else
	{
		MessageBox(NULL, "�ߗ��̃f�[�^�ǂݍ��ݎ��s", "�x��", MB_ICONWARNING);
	}
}

//====================================================================
// �ߗ��̃f�t�H���g���[�V����
//====================================================================
bool CPrisoner::DefaultMotion(void)
{
	GetModelSet()->SetMotion(CModelSet::PRISONER_MOTION_STAY);
	return false;
}
//====================================================================
// �ߗ��̓����蔻��
//====================================================================
void CPrisoner::Collision()
{
	CMap *pMap;
	pMap = CManager::GetBaseMode()->GetMap();

	// �}�b�v���f�������݂��������ē����蔻�肪���݂��鎞
	if (pMap && GetCollision())
	{
		GetCollision()->SetPos(&GetPosition());

		GetCollision()->SetHeight(GetModelSet()->GetCharacterModelList()[0]->GetPosition().y);

		// ���C�̔���
		if (GetCollision()->RayBlockCollision(pMap, GetModelSet()->GetCharacterModelList()[0]->GetMatrix()))
		{
			// �W�����v���邱�Ƃ����F����
			SetJump(true);
			SetFallFlag(false);
		}
		else
		{
			// �W�����v���邱�Ƃ����F���Ȃ�
			SetJump(false);
			SetFallFlag(true);
		}
		if (GetFallFlag() == true)
		{
		}
	}

}

//====================================================================
// �ߗ��̏�ԕʏ���
//====================================================================
void CPrisoner::PrisonerState()
{
	switch (m_PrisonerState)
	{
		// �A�C�e�����h���b�v����X�e�[�g
	case CPrisoner::PRISONER_STATE_DROPITEM:
	{
		// �A�C�e���𗎂Ƃ����[�V����
		GetModelSet()->SetMotion(CModelSet::PRISONER_MOTION_RELEASE);

		m_StateTime--;
		if (m_StateTime <= 0)
		{
			SetStateTime(40);
			// �ߗ��̏�Ԃ̕ύX
			// �ߗ��̃^�C�v�ʃh���b�v����
			PrisonerDropType();
			this->SetPrisonerState(PRISONER_STATE_SALUTE);
		}
	}
		break;

		// �\��邷��
	case CPrisoner::PRISONER_STATE_SALUTE:

		GetModelSet()->SetMotion(CModelSet::PRISONER_MOTION_SALUTE);

		m_StateTime--;
		if (m_StateTime <= 0)
		{
			SetStateTime(120);
			// �ߗ��̏�Ԃ̕ύX
			this->SetPrisonerState(PRISONER_STATE_RUN);
		}
		break;

		// ����
	case CPrisoner::PRISONER_STATE_RUN:

		if (GetFallFlag())
		{
			GetModelSet()->SetMotion(CModelSet::PRISONER_MOTION_FALL);
		}
		else
		{
			// ���ɑ���
			GetModelSet()->SetMotion(CModelSet::PRISONER_MOTION_RUN);
			SetMove(D3DXVECTOR3(-15.0f, 0.0f, 1.0f));

			// ���ł܂ł̃J�E���g�����Z
			m_nDieCount++;
			// �J�E���g����v�l�𒴂�����
			if (m_nDieCount >= m_PrisonerData.nDeleteTime)
			{
				SetDieFlag(true);
			}
		}

		break;
	}

	//�����蔻��\���ǂ����ݒ�
	//�����Ă����ԈȊO�͓����蔻�肪���Ȃ��悤�ɂ���
	GetCollision()->SetCanCollision(m_PrisonerState == PRISONER_STATE_STAY);
}

//====================================================================
// �ߗ��̃^�C�v�ʏ���
//====================================================================
void CPrisoner::PrisonerDropType()
{
	switch (m_PrisonerDropType)
	{
		// �A�C�e����1��ގw�肵�Ċm��Ńh���b�v������
	case CPrisoner::PRISONER_ITEM_DROPTYPE_DESIGNATE_ONE:
		// �A�C�e���̐���
		CItem::DropItem(
			GetPosition(),
			CItem::ITEMDROP_NONE,
			CItem::ITEMDROP_PATTERN_DESIGNATE,
			GetPrisonerDropItem());
		break;

		// �h���b�v����A�C�e����͈͂Ŏw�肵�ăh���b�v������
	case CPrisoner::PRISONER_ITEM_DROPTYPE_DESIGNATE_RANGE:
		CItem::DropItem(
			GetPosition(),
			CItem::ITEMDROP_WEAPON,
			CItem::ITEMDROP_PATTERN_RANDOM,
			CItem::ITEMTYPE_NONE);
		break;

		// �S�ẴA�C�e���̒����烉���_���ŃA�C�e�����h���b�v������
	case CPrisoner::PRISONER_ITEM_DROPTYPE_ALL:
		CItem::DropItem(
			GetPosition(),
			CItem::ITEMDROP_ALL,
			CItem::ITEMDROP_PATTERN_RANDOM,
			CItem::ITEMTYPE_NONE);
		break;
	}
}

//====================================================================
// �ړ�
//====================================================================
void CPrisoner::Move(float move, float fdest)
{
	GetMove().x += sinf(move * -D3DX_PI) * 3.0f;
	GetMove().z += cosf(move * -D3DX_PI) * 3.0f;
	GetRotDest().y = fdest *  D3DX_PI;
}
