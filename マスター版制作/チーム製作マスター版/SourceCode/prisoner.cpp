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
#include "player.h"

// =====================================================================================================================================================================
//
//�}�N����`
//
// =====================================================================================================================================================================
#define PLAYER_PRISONER_MINDISTANCE (150) // �ߗ��̃X�e�[�g[PRISONER_STATE_SKIP]�̎��̃v���C���[�ƕߗ��̋����̍ő�l

// =====================================================================================================================================================================
//
// �ÓI�����o�ϐ��̏�����
//
// =====================================================================================================================================================================
PRISONER_DATA		CPrisoner::m_PrisonerData	= {};

// =====================================================================================================================================================================
//
// �e�L�X�g�t�@�C����
//
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
	//
	m_bDrop = false;
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
	// �f�t�H���g���[�V�����̐ݒ�
	GetModelSet()->SetMotion(CModelSet::PRISONER_MOTION_STAY);
	// �X�e�[�g�̐ݒ�
	CCharacter::SetState(CCharacter::CHARACTER_STATE_NONE);
	// ����
	Move(0.0f, -1.57f);
	// �����蔻�萶��
	GetCollision()->SetPos(&GetPosition());
	GetCollision()->SetSize(m_PrisonerData.CollisionSize);
	GetCollision()->SetMove(&GetMove());
	GetCollision()->DeCollisionCreate(CCollision::COLLISIONTYPE_NORMAL);
	GetCollision()->SetGameObject(this);

	return S_OK;
}
// =====================================================================================================================================================================
//
// �I��
//
// =====================================================================================================================================================================
void CPrisoner::Uninit(void)
{
	CCharacter::Uninit();
}
// =====================================================================================================================================================================
//
// �X�V
//
// =====================================================================================================================================================================
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
// =====================================================================================================================================================================
//
// �`��
//
// =====================================================================================================================================================================
void CPrisoner::Draw(void)
{
	CCharacter::Draw();
}
// =====================================================================================================================================================================
//
// �f�o�b�O
//
// =====================================================================================================================================================================
void CPrisoner::DebugInfo(void)
{
}
// =====================================================================================================================================================================
//
// ���f���̃N���G�C�g
//
// =====================================================================================================================================================================
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

// =====================================================================================================================================================================
//
// �ߗ��̃f�t�H���g���[�V����
//
// =====================================================================================================================================================================
bool CPrisoner::DefaultMotion(void)
{
	GetModelSet()->SetMotion(CModelSet::PRISONER_MOTION_STAY);
	return false;
}
// =====================================================================================================================================================================
//
// �ߗ��̓����蔻��
//
// =====================================================================================================================================================================
void CPrisoner::Collision()
{
	CMap *pMap = CManager::GetBaseMode()->GetMap();

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

// =====================================================================================================================================================================
//
// �ߗ��̏�ԕʏ���
//
// =====================================================================================================================================================================
void CPrisoner::PrisonerState()
{
	// �ߗ��̏�Ԃɂ���čs����ς���
	switch (m_PrisonerState)
	{
		// �������
	case CPrisoner::PRISONER_STATE_STAY:
		// ���ɉ������Ȃ�
		break;

		// �v���C���[�Ƃ̋����ɂ���Ď��̍s�����l����
	case CPrisoner::PRISONER_STATE_THINKING:

		// �v���C���[�ƕߗ��̋�����n�ȉ����������ߗ��̃X�e�[�g��[PRISONER_STATE_DROPITEM]�Ɉڍs����
		if (GetDistance_Player_This() <= PLAYER_PRISONER_MINDISTANCE)
		{
			SetStateTime(20 * 4 + 60);
			this->SetPrisonerState(PRISONER_STATE_DROPITEM);
		}

		// ������n�ȏ㗣��Ă����狗����n�ȉ��ɂȂ�܂ŕߗ��̃X�e�[�g��[PRISONER_STATE_SKIP]�ɂ���
		else
		{
			this->SetPrisonerState(PRISONER_STATE_SKIP);
		}

		break;

		// �v���C���[�̕��������ăX�L�b�v����
	case CPrisoner::PRISONER_STATE_SKIP:

		if (GetFallFlag())
		{
			SetMove(D3DXVECTOR3(0.0f, -2.0f, 0.0f));
			SetStateTime(120);	GetModelSet()->SetMotion(CModelSet::PRISONER_MOTION_FALL);
		}
		else
		{
			// �X�L�b�v�̃��[�V����������
			GetModelSet()->SetMotion(CModelSet::PRISONER_MOTION_SKIP);

			// �ߗ����v���C���[���E�ɂ����獶�ɓ���
			if (this->PrisonerPosX_Than_Large())
			{
				Move(0.0f,-1.57f);
				SetMove(D3DXVECTOR3(-3.0f, 0.0f, 0.0f));
			}
			// ���Ȃ獶��
			else
			{
				// ����
				Move(0.0f, 1.57f);
				SetMove(D3DXVECTOR3(3.0f, 0.0f, 0.0f));
			}
		}

		// �ߗ��ƃv���C���[�̋������K��l��艺�������ߗ��̃X�e�[�g��[PRISONER_STATE_DROPITEM]�Ɉڍs����
		if (GetRotDest().y <= D3DX_PI / 2)
		{
			if (GetDistance_Player_This() <= PLAYER_PRISONER_MINDISTANCE)
			{
				// 20�t���[��*4
				SetStateTime(20 * 4 + 60);
				this->SetPrisonerState(PRISONER_STATE_DROPITEM);
			}
		}
		else if(GetRotDest().y >= -D3DX_PI / 2)
		{
			if (GetDistance_Player_This() <= PLAYER_PRISONER_MINDISTANCE)
			{
				// 20�t���[��*4
				SetStateTime(20 * 4 + 60);
				this->SetPrisonerState(PRISONER_STATE_DROPITEM);
			}
		}

		break;

		// �A�C�e�����h���b�v����
	case CPrisoner::PRISONER_STATE_DROPITEM:
		// �A�C�e���𗎂Ƃ����[�V����������
		GetModelSet()->SetMotion(CModelSet::PRISONER_MOTION_DROP);

		// ���[�V�������I�������ߗ��̃X�e�[�g[PRISONER_STATE_RAMPAGE]�Ɉڍs������
		m_StateTime--;
		if (m_StateTime <= 40)
		{
			// �ߗ��̏�Ԃ̕ύX
			// �ߗ��̃^�C�v�ʃh���b�v����
			PrisonerDropType();

			if (m_StateTime <= 0)
			{
				SetStateTime(60);
				this->SetPrisonerState(PRISONER_STATE_RAMPAGE);
			}
		}
		break;

		// �\���
	case CPrisoner::PRISONER_STATE_RAMPAGE:
		// �\��郂�[�V������������
		GetModelSet()->SetMotion(CModelSet::PRISONER_MOTION_SALUTE);

		// ��莞�Ԍo�߂�����X�e�[�g��[PRISONER_STATE_RUN]�Ɉڍs����
		// ���̎��ߗ��͈ړ����Ȃ�
		m_StateTime--;

		if (m_StateTime <= 0)
		{
			this->SetPrisonerState(PRISONER_STATE_RUN);
		}
		break;

	case CPrisoner::PRISONER_STATE_RUN:
		if (m_StateTime <= 0)
		{
			if (GetFallFlag())
			{
				SetMove(D3DXVECTOR3(0.0f, -3.0f, 0.0f));
				GetModelSet()->SetMotion(CModelSet::PRISONER_MOTION_FALL);
			}
			else
			{
				// �������ɂɑ���
				GetModelSet()->SetMotion(CModelSet::PRISONER_MOTION_RUN);
				Move(0.0f, -1.57f);
				SetMove(D3DXVECTOR3(-15.0f, 0.0f, 0.0f));
			}

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

// =====================================================================================================================================================================
//
// �ߗ��̃^�C�v�ʏ���
//
// =====================================================================================================================================================================
void CPrisoner::PrisonerDropType()
{
	if (!m_bDrop)
	{
		D3DXVECTOR3 DropPos = GetPosition();
		if (GetRotDest().y <= D3DX_PI / 2)
		{
			DropPos.x -= 50.0f;
		}
		else if(GetRotDest().y >= -D3DX_PI / 2)
		{
			DropPos.x += 50.0f;
		}

		switch (m_PrisonerDropType)
		{
			// �A�C�e����1��ގw�肵�Ċm��Ńh���b�v������
		case CPrisoner::PRISONER_ITEM_DROPTYPE_PICK_ONE:
			// �A�C�e���̐���[�ߗ��̍��W �h���b�v����A�C�e�����m�肳���邩�ǂ��� �m�肳����A�C�e���̃^�C�v�̎w��]
			CItem::DropItem(
				DropPos,
				true,
				GetPrisonerDropItem());
			break;

			// �h���b�v����A�C�e����͈͂Ŏw�肵�ăh���b�v������
		case CPrisoner::PRISONER_ITEM_DROPTYPE_RANGE:
			CItem::DropItem(
				DropPos,
				false,
				CItem::ITEMTYPE_NONE);
			break;
		}

		m_bDrop = true;
	}
}

// =====================================================================================================================================================================
//
// �v���C���[�ƑI�����ꂽ�ߗ��̋����̒��������߂� ���ʂ͕K�����R��
//
// =====================================================================================================================================================================
unsigned int CPrisoner::GetDistance_Player_This()
{
	// ����1p�̃|�C���^���擾��1p�̋����ŎQ�Ƃ��Ă���
	CPlayer *pPlayer = CManager::GetBaseMode()->GetPlayer(TAG::PLAYER_1);

	// �v���C���[�ƕߗ��̋��������R���ŋ��߂�
	return (unsigned int)fabs(this->GetPosition().x - pPlayer->GetPosition().x);
}

// =====================================================================================================================================================================
//
// �ߗ���x���W���猩�č��ɂ��邩�E�ɂ��邩�̌��ʂ�Ԃ�
//
// =====================================================================================================================================================================
bool CPrisoner::PrisonerPosX_Than_Large()
{
	// ����1p�̃|�C���^���擾��1p�̋����ŎQ�Ƃ��Ă���
	CPlayer *pPlayer =  CManager::GetBaseMode()->GetPlayer(TAG::PLAYER_1);

	 // ��ׂ�Ώ�(���̓v���C���[�̂�)���ߗ��̍��W��荶�ɂ��邩�E�ɂ��邩�����߂�
	 // ��(�ߗ����l��������������false)�E(�l���傫��������true)
	 if (this->GetPosition().x >= pPlayer->GetPosition().x)
	 {
		 return true;
	 }
	 else
	 {
		 return false;
	 }

	return false;
}

// =====================================================================================================================================================================
//
// �ړ�
//
// =====================================================================================================================================================================
void CPrisoner::Move(float move, float fdest)
{
	GetMove().x += sinf(move * -D3DX_PI) * 3.0f;
	GetMove().z += cosf(move * -D3DX_PI) * 3.0f;
	GetRotDest().y = fdest *  D3DX_PI;
}
