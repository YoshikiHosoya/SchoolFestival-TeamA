// =====================================================================================================================================================================
//
// �{�X1�̏��� [boss_one.cpp]
// Author : fujiwara masato
//
// =====================================================================================================================================================================
#include "Boss_One.h"
#include "model.h"
#include "collision.h"
#include "game.h"
#include "manager.h"
#include "map.h"

//====================================================================
//�}�N����`
//====================================================================

// =====================================================================================================================================================================
// �ÓI�����o�ϐ��̏�����
// =====================================================================================================================================================================
BOSS_ONE_DATA		CBoss_One::m_BossOneData = {};
float				CBoss_One::m_fMoveSpeed = 0.0f;
D3DXVECTOR3			CBoss_One::m_CollisionSize = D3DXVECTOR3(200, 100, 0);

// =====================================================================================================================================================================
// �e�L�X�g�t�@�C����
// =====================================================================================================================================================================
char *CBoss_One::m_BossOneFileName =
{
	"data/Load/DragonNosuke/Boss_OneData.txt" 			// �ߗ��̏��
};

// =====================================================================================================================================================================
//
// �R���X�g���N�^
//
// =====================================================================================================================================================================
CBoss_One::CBoss_One(OBJ_TYPE type) :CEnemy(type)
{

	// �ߗ��̏������
	m_BossOneState = BOSS_ONE_STATE_NONE;
}
// =====================================================================================================================================================================
//
// �f�X�g���N�^
//
// =====================================================================================================================================================================
CBoss_One::~CBoss_One()
{
}

// =====================================================================================================================================================================
//
// ����������
//
// =====================================================================================================================================================================
HRESULT CBoss_One::Init(void)
{
	// �L�����̏�����
	CCharacter::Init();
	// �I�t�Z�b�g�̎擾
	LoadOffset(CCharacter::CHARACTER_TYPE_BOSS_ONE);
	// �L�����N�^�[�^�C�v�̐ݒ�
	SetCharacterType(CCharacter::CHARACTER_TYPE_BOSS_ONE);
	//�d�͖���
	SetGravity(false);
	// �p�x�̐ݒ�
	SetRotDest(D3DXVECTOR3(0.0f, 1.2f, 0.0f));
	//SetRotDest(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	// �̗͂̏����l
	CCharacter::SetLife(5000);
	// ���[�V���������Ȃ��ݒ�
	SetMotion(CCharacter::CHARACTER_MOTION_STATE_NONE);
	// �����蔻�萶��
	GetCollision()->SetPos(&GetPosition());
	GetCollision()->SetSize2D(m_CollisionSize);
	GetCollision()->SetMove(&GetMove());
	GetCollision()->DeCollisionCreate(CCollision::COLLISIONTYPE_CHARACTER);

	return S_OK;
}
//====================================================================
//�I��
//====================================================================
void CBoss_One::Uninit(void)
{
	CCharacter::Uninit();
}
//====================================================================
//�X�V
//====================================================================
void CBoss_One::Update(void)
{
	// �����蔻��
	if (GetCollision() != nullptr)
	{
		// ���W�̍X�V pos
		GetCollision()->SetPos(&GetPosition());
	}

	GetCharacterModelPartsList(CModel::MODEL_BOSSONE_BODY)->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	GetCharacterModelPartsList(CModel::MODEL_BOSSONE_HEAD)->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	GetCharacterModelPartsList(CModel::MODEL_BOSSONE_THIGH_L_FRONT)->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	GetCharacterModelPartsList(CModel::MODEL_BOSSONE_THIGH_L_REAR)->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	GetCharacterModelPartsList(CModel::MODEL_BOSSONE_THIGH_R_FRONT)->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	GetCharacterModelPartsList(CModel::MODEL_BOSSONE_THIGH_R_REAR)->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// �L�����N�^�[�̍X�V
	CCharacter::Update();

	for (int nCnt = 0; nCnt < CModel::MODEL_BOSSONE_MAX;nCnt++)
	{
		CDebugProc::Print("rrroottt %f, %f, %f\n",
			GetCharacterModelPartsList(nCnt)->GetRot().x,
			GetCharacterModelPartsList(nCnt)->GetRot().y,
			GetCharacterModelPartsList(nCnt)->GetRot().z);
	}
}
//====================================================================
//�`��
//====================================================================
void CBoss_One::Draw(void)
{
	CCharacter::Draw();
}
//====================================================================
//�f�o�b�O
//====================================================================
void CBoss_One::DebugInfo(void)
{
	//CDebugProc::Print("");
	//CCharacter::DebugInfo();
}
//====================================================================
//���f���̃N���G�C�g
//====================================================================
CBoss_One *CBoss_One::Create()
{
	// ���������m��
	CBoss_One*pBoss_One = new CBoss_One(OBJTYPE_BOSS);
	// ������
	pBoss_One->Init();
	// �l��Ԃ�
	return pBoss_One;
}

// =====================================================================================================================================================================
//
// �{�X�̏��̓ǂݍ���
//
// =====================================================================================================================================================================
void CBoss_One::Boss_One_DataLoad()
{
	// �t�@�C���|�C���g
	FILE *pFile;

	char cReadText[128];			// �����Ƃ��ēǂݎ��
	char cHeadText[128];			// ��r�p
	char cDie[128];					// �s�v�ȕ���

									// �t�@�C�����J��
	pFile = fopen(m_BossOneFileName, "r");

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
						if (strcmp(cHeadText, "LIFE") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_BossOneData.nLife);	// ��r�p�e�L�X�g��DELETE����
						}
						// SPEED��������
						else if (strcmp(cHeadText, "COOLTIME") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_BossOneData.nCoolTime);	// ��r�p�e�L�X�g��SPEED����
						}
						// COLLISIONSIZE��������
						else if (strcmp(cHeadText, "COLLISIONSIZE") == 0)
						{
							sscanf(cReadText, "%s %s %f %f %f", &cDie, &cDie,
								&m_BossOneData.CollisionSize.x,
								&m_BossOneData.CollisionSize.y,
								&m_BossOneData.CollisionSize.z);										// ��r�p�e�L�X�g��COLLISIONSIZE����
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
		MessageBox(NULL, "�{�X1�̃f�[�^�ǂݍ��ݎ��s", "�x��", MB_ICONWARNING);
	}

	// �ǂݍ��񂾏��̑��
	SetBoss_OneData();
}

//====================================================================
//�{�X�̓ǂݍ��񂾏��̐ݒ�
//====================================================================
void CBoss_One::SetBoss_OneData()
{
}

//====================================================================
// �{�X�̃f�t�H���g���[�V����
//====================================================================
bool CBoss_One::Motion(void)
{
	return false;
}

bool CBoss_One::DefaultMotion(void)
{
	return false;
}

void CBoss_One::BossOneState()
{
}
