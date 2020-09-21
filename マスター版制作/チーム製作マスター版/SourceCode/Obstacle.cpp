// =====================================================================================================================================================================
//
// ��Q���̏��� [Obstacle.cpp]
// Author : fujiwara masato
//
// =====================================================================================================================================================================
#include "Obstacle.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "debugproc.h"
#include "collision.h"
#include "particle.h"
#include "ModelSet.h"
#include "Character.h"
#include "model.h"
#include "item.h"

// =====================================================================================================================================================================
// �ÓI�����o�ϐ��̏�����
// =====================================================================================================================================================================
OBSTACLE_PARAM	CObstacle::m_ObstacleParam[CObstacle::TYPE_MAX] = {};

// =====================================================================================================================================================================
// �e�L�X�g�t�@�C����
// =====================================================================================================================================================================
char *CObstacle::m_ObstacleFileName[CObstacle::TYPE_MAX] =
{
	{ "data/Load/Obstacle/Box.txt" },				// �ؔ�
	{ "data/Load/Obstacle/Barrel.txt" },			// �M
	{ "data/Load/Obstacle/BarrelBomb.txt" },		// ���e�M
	{ "data/Load/Obstacle/Tree.txt" },				// ��
	{ "data/Load/Obstacle/Chest.txt" },				// ����
	{ "data/Load/Obstacle/Sandbags.txt" },			// �y�X
	{ "data/Load/Obstacle/Car.txt" },				// ��
};

// =====================================================================================================================================================================
// �}�N����`
// =====================================================================================================================================================================

// =====================================================================================================================================================================
//
// �R���X�g���N�^
//
// =====================================================================================================================================================================
CObstacle::CObstacle(OBJ_TYPE type) :CModel(type)
{
	// �ϐ��̏�����
	m_nLife = 0;
	// �^�O�ݒ�
	CGameObject::SetTag(TAG::OBSTACLE);
}
// =====================================================================================================================================================================
//
// �f�X�g���N�^
//
// =====================================================================================================================================================================
CObstacle::~CObstacle()
{
}
// =====================================================================================================================================================================
//
// ����������
//
// =====================================================================================================================================================================
HRESULT CObstacle::Init()
{
	// ������
	CModel::Init();

	// ���̐ݒ�
	SetObstacleParam(TYPE_BOX);

	// �����蔻�萶��
	GetCollision()->SetPos(&GetPosition());
	GetCollision()->SetGameObject(this);

	return S_OK;
}
// =====================================================================================================================================================================
//
// �I������
//
// =====================================================================================================================================================================
void CObstacle::Uninit(void)
{
	// �I��
	CModel::Uninit();
}

// =====================================================================================================================================================================
//
// �X�V����
//
// =====================================================================================================================================================================
void CObstacle::Update(void)
{
	if (GetCollision() != nullptr)
	{
		//���W�̍X�V
		GetCollision()->SetPos(&GetPosition());
	}
	// �X�V
	CModel::Update();
}

// =====================================================================================================================================================================
//
// �`�揈��
//
// =====================================================================================================================================================================
void CObstacle::Draw(void)
{
	// �`��
	CModel::Draw();
}
// =====================================================================================================================================================================
//
// �f�o�b�O
//
// =====================================================================================================================================================================
void CObstacle::DebugInfo()
{
}

// =====================================================================================================================================================================
//
// �e�̐���
//
// =====================================================================================================================================================================
CObstacle * CObstacle::Create()
{
	// �ϐ�
	CObstacle *pObstacle;

	// �������̊m��
	pObstacle = new CObstacle(OBJTYPE_OBSTACLE);

	// ������
	pObstacle->Init();

	// ���f���^�C�v�̐ݒ�
	pObstacle->SetType(OBSTACLE_MODEL);

	return pObstacle;
}

// =====================================================================================================================================================================
//
// ��Q�����󂳂��Ƃ��̏���
//
// =====================================================================================================================================================================
void CObstacle::ObstacleLoad()
{
	// �t�@�C���|�C���g
	FILE *pFile;

	char cReadText[128];			// �����Ƃ��ēǂݎ��
	char cHeadText[128];			// ��r�p
	char cDie[128];					// �s�v�ȕ���
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu
	for (int nCnt = 0; nCnt < CObstacle::TYPE_MAX; nCnt++)
	{
		// �t�@�C�����J��
		pFile = fopen(m_ObstacleFileName[nCnt], "r");

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

					// OBSTACLESET��������
					if (strcmp(cHeadText, "OBSTACLESET") == 0)
					{
						// END_OBSTACLESET������܂Ń��[�v
						while (strcmp(cHeadText, "END_OBSTACLESET") != 0)
						{
							fgets(cReadText, sizeof(cReadText), pFile); // �ꕶ�ǂݍ���
							sscanf(cReadText, "%s", &cHeadText);		// ��r�p�e�L�X�g�ɕ�������

							// LIFE��������
							if (strcmp(cHeadText, "LIFE") == 0)
							{
								sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_ObstacleParam[nCnt].nLife);			// ��r�p�e�L�X�g��LIFE����
							}
							// COLLISIONSIZE��������
							else if (strcmp(cHeadText, "COLLISIONSIZE") == 0)
							{
								sscanf(cReadText, "%s %s %f %f %f", &cDie, &cDie, &m_ObstacleParam[nCnt].CollisionSize.x
									, &m_ObstacleParam[nCnt].CollisionSize.y
									, &m_ObstacleParam[nCnt].CollisionSize.z);		// ��r�p�e�L�X�g��COLLISIONSIZE����
							}
							else if (strcmp(cHeadText, "END_OBSTACLESET") == 0)
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
			MessageBox(NULL, "��Q���̃p�����[�^�[�ǂݍ��ݎ��s", "�x��", MB_ICONWARNING);
		}
	}
}

// =====================================================================================================================================================================
//
// ��Q�����󂳂��Ƃ��̏���
//
// =====================================================================================================================================================================
void CObstacle::Hit(OBSTACLE_TYPE type,int nDamage)
{
	switch (type)
	{
	case CObstacle::TYPE_BOX:
	case CObstacle::TYPE_BARREL:
	case CObstacle::TYPE_BARRELBOMB:
	case CObstacle::TYPE_TREE:
	case CObstacle::TYPE_CHEST:
	case CObstacle::TYPE_SANDBAGS:
	case CObstacle::TYPE_CAR:

		// �̗͂����Z����
		this->AddDamage(nDamage);
		// �폜����
		this->CheckDie();

		break;
	default:
		break;
	}
}

// =====================================================================================================================================================================
// ��ނ��Ƃ̃h���b�v
// =====================================================================================================================================================================
void CObstacle::DropItem()
{
	switch (m_ObstacleType)
	{
	case CObstacle::TYPE_BOX:
		CItem::DropItem_Multiple(GetPosition(), CItem::LIST_FOOD, CItem::BEHAVIOR_BURSTS);
		break;
	case CObstacle::TYPE_BARREL:
		CItem::DropItem_Multiple(GetPosition(), CItem::LIST_FOOD, CItem::BEHAVIOR_BURSTS);
		break;
	case CObstacle::TYPE_BARRELBOMB:
		// ��������
		break;
	case CObstacle::TYPE_TREE:
		CItem::DropItem_Multiple(GetPosition(), CItem::LIST_FOOD, CItem::BEHAVIOR_FREEFALL);
		break;
	case CObstacle::TYPE_CHEST:
		CItem::DropItem(GetPosition(), true, CItem::ITEMTYPE_GOLDCOIN);
		break;
	case CObstacle::TYPE_SANDBAGS:
		break;
	case CObstacle::TYPE_CAR:
		CItem::DropItem_Multiple(GetPosition(), CItem::LIST_COIN, CItem::BEHAVIOR_BURSTS);
		break;

	default:
		break;
	}
}

// =====================================================================================================================================================================
// ��Q����j�󂷂邩���߂鏈��
// =====================================================================================================================================================================
void CObstacle::CheckDie()
{
	if (this->m_nLife <= 0)
	{
		if (!this->GetDieFlag())
		{
			// �A�C�e�����h���b�v����
			DropItem();
		}
		// �̗͂�0�ȉ��Ȃ�폜����
		this->SetDieFlag(true);
		//��������
		CParticle::CreateFromText(GetPosition(), ZeroVector3, CParticleParam::EFFECT_EXPLOSION_OBJECTBREAK);
	}
}
//====================================================================
// �_���[�W���󂯂����̏���
//====================================================================
void CObstacle::AddDamage(int nDamage)
{
	this->m_nLife -= nDamage;
	this->SetLife(m_nLife);
}

//====================================================================
// �T�C�Y�̐ݒ�
//====================================================================
void CObstacle::SetCollisionSize(CObstacle::OBSTACLE_TYPE type)
{
	// �����蔻��̑傫����ݒ�
	GetCollision()->SetSize(m_ObstacleParam[type].CollisionSize);
	GetCollision()->DeCollisionCreate(CCollision::COLLISIONTYPE_CHARACTER);
};

