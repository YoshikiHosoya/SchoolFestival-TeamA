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
#include "Normal_Iten.h"
#include "Anim_Item.h"
#include "map.h"
#include "sound.h"

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
	{ "data/Load/Obstacle/Balloon.txt" },			// ���D
	{ "data/Load/Obstacle/PresentBox01.txt" },		// �v���[���g
	{ "data/Load/Obstacle/PresentBox00.txt" },		// �v���[���g ���A
	{ "data/Load/Obstacle/Bridge.txt" },			// ��
	{ "data/Load/Obstacle/Bell.txt" },				// ��
	{ "data/Load/Obstacle/Cage.txt" },				// �B
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
	m_pBalloon = nullptr;
	m_BalloonMove = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
	m_fGravity = -5.0f;
	m_bGravity = false;
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

	CMap *pMap = CManager::GetBaseMode()->GetMap();

	D3DXVECTOR3 ofsetpos = D3DXVECTOR3(GetPosition().x, GetPosition().y + 70.0f, GetPosition().z);
	if (this->m_ObstacleType == TYPE_PRESENTBOX)
	{
		m_pBalloon = pMap->PresentCreate(ofsetpos, TYPE_BALLOON);
		GetCollision()->SetCanCollision(false);
	}
	else if (this->m_ObstacleType == TYPE_PRESENTBOX_RARE)
	{
		m_pBalloon = pMap->PresentCreate(ofsetpos, TYPE_BALLOON);
		GetCollision()->SetCanCollision(false);
	}

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
	D3DXVECTOR3 posold = GetPosition();
	if (m_pBalloon && m_pBalloon->GetObstacleType() == TYPE_BALLOON && m_pBalloon->m_nLife <= 0)
	{
		m_bBreakBalloon = true;
	}

	if (GetCollision() != nullptr)
	{
		//���W�̍X�V
		GetCollision()->SetPos(&GetPosition());

		if (this->m_ObstacleType == TYPE_PRESENTBOX ||
			this->m_ObstacleType == TYPE_PRESENTBOX_RARE)
		{
			if (m_bBreakBalloon)
			{
				// �}�b�v�̃|�C���^�擾
				CMap *pMap = CManager::GetBaseMode()->GetMap();

				// �}�b�v���f�������݂��������ē����蔻�肪���݂��鎞
				if (pMap && GetCollision())
				{
					// ��Q���̔���ƃ��C�̔���
					if (GetCollision()->RayBlockCollision(pMap, (this->GetMatrix())))
					{
						GetPosition().y -= 15.0f;
					}
					else
					{
					}

					// ��Q���̔���ƃ��C�̔���
					//if (GetCollision()->RayCollision(pMap, posold, GetPosition()))
					//{
					//	//GetPosition().y += m_fGravity;
					//}
					//else
					//{
					//	//GetPosition().y += m_fGravity;
					//}
				}
			}
		}
	}

	// ���D�����ꂽ�畗�D�̎�����̓����蔻����\�ɂ���
	if (this->m_ObstacleType == TYPE_PRESENTBOX ||
		this->m_ObstacleType == TYPE_PRESENTBOX_RARE)
	{
		if (m_pBalloon && m_pBalloon->GetDieFlag())
		{
			GetCollision()->SetCanCollision(true);
			m_pBalloon = nullptr;
		}
		else if (m_pBalloon && !m_pBalloon->GetDieFlag())
		{
			m_pBalloon->GetPosition() += m_BalloonMove;
			GetPosition().x = m_pBalloon->GetPosition().x;
		}
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
// ��Q���̐���
//
// =====================================================================================================================================================================
CObstacle * CObstacle::Create(OBSTACLE_TYPE Type)
{
	// �ϐ�
	CObstacle *pObstacle;

	// �������̊m��
	pObstacle = new CObstacle(OBJTYPE_OBSTACLE);

	// �^�O�ݒ�
	pObstacle->SetTag(TAG::OBSTACLE);

	pObstacle->SetObstacleType(Type);

	// ������
	pObstacle->Init();

	// ���f���^�C�v�̐ݒ�
	pObstacle->SetType(OBSTACLE_MODEL);

	return pObstacle;
}

// =====================================================================================================================================================================
//
// ��Q���̐���
//
// =====================================================================================================================================================================
CObstacle * CObstacle::Create_Editor()
{
	// �ϐ�
	CObstacle *pObstacle;

	// �������̊m��
	pObstacle = new CObstacle(OBJTYPE_OBSTACLE);

	// �^�O�ݒ�
	pObstacle->SetTag(TAG::OBSTACLE);

	// ������
	pObstacle->Init();

	// ���f���^�C�v�̐ݒ�
	pObstacle->SetType(OBSTACLE_MODEL);

	return pObstacle;
}

// =====================================================================================================================================================================
//
// �v���[���g�̐���
//
// =====================================================================================================================================================================
CObstacle * CObstacle::Create_Present(D3DXVECTOR3 pos, CObstacle::OBSTACLE_TYPE Type)
{
	// �ϐ�
	CObstacle *pObstacle;

	// �������̊m��
	pObstacle = new CObstacle(OBJTYPE_OBSTACLE);

	// �^�O�ݒ�
	pObstacle->SetTag(TAG::OBSTACLE);

	pObstacle->SetObstacleType(Type);

	pObstacle->SetPosition(pos);

	// ������
	pObstacle->Init();

	// ���f���^�C�v�̐ݒ�
	pObstacle->SetType(OBSTACLE_MODEL);

	return pObstacle;
}

// =====================================================================================================================================================================
//
// �p�����[�^�[�̓ǂݍ���
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
							// break��������
							else if (strcmp(cHeadText, "BBREAK") == 0)
							{
								int nBreak;
								sscanf(cReadText, "%s %s %d", &cDie, &cDie, &nBreak);
								m_ObstacleParam[nCnt].bBreak = nBreak ? false : true;
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
void CObstacle::Hit(TAG tag,int nDamage)
{
	switch (m_ObstacleType)
	{
	case CObstacle::TYPE_BOX:
	case CObstacle::TYPE_BARREL:
	case CObstacle::TYPE_BARRELBOMB:
	case CObstacle::TYPE_TREE:
	case CObstacle::TYPE_CHEST:
	case CObstacle::TYPE_SANDBAGS:
	case CObstacle::TYPE_CAR:
	case CObstacle::TYPE_BALLOON:
	case CObstacle::TYPE_PRESENTBOX:
	case CObstacle::TYPE_PRESENTBOX_RARE:
	case CObstacle::TYPE_BOSSMAP_CAGE:
		// �̗͂����Z����
		this->AddDamage(nDamage);
		// �폜����
		this->CheckDie(tag);
		break;

	case CObstacle::TYPE_BOSSMAP_BELL:
		CManager::GetSound()->Play(CSound::LABEL_SE_HIT_BELL);
		// �̗͂����Z����
		this->AddDamage(nDamage);
		// �폜����
		this->CheckDie(tag);
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
		CNormalItem::DropItem_Multiple(GetPosition(), CItem::LIST_FOOD, CItem::BEHAVIOR_BURSTS);
		break;
	case CObstacle::TYPE_BARREL:
		CAnimationItem::DropItem_Multiple(GetPosition(), CItem::LIST_ANI_NORMAL, CItem::BEHAVIOR_BURSTS);
		break;
	case CObstacle::TYPE_BARRELBOMB:
		// ��������
		break;
	case CObstacle::TYPE_TREE:
		CNormalItem::DropItem_Multiple(GetPosition(), CItem::LIST_FOOD, CItem::BEHAVIOR_FREEFALL);
		break;
	case CObstacle::TYPE_CHEST:
		CNormalItem::DropItem(GetPosition(), true, CItem::ITEMTYPE_GOLDCOIN);
		break;
	case CObstacle::TYPE_SANDBAGS:
		break;
	case CObstacle::TYPE_CAR:
		CNormalItem::DropItem_Multiple(GetPosition(), CItem::LIST_COIN, CItem::BEHAVIOR_BURSTS);
		break;

	case CObstacle::TYPE_BALLOON:
		break;
	case CObstacle::TYPE_PRESENTBOX:
		CNormalItem::DropItem_Multiple(GetPosition(), CItem::LIST_FOOD, CItem::BEHAVIOR_BURSTS);
		break;
	case CObstacle::TYPE_PRESENTBOX_RARE:
		CNormalItem::DropItem_Multiple(GetPosition(), CItem::LIST_RARE, CItem::BEHAVIOR_BURSTS);
		break;

	case CObstacle::TYPE_BOSSMAP_BELL:
		CAnimationItem::DropItem_Multiple(GetPosition(), CItem::LIST_ANI_RARE, CItem::BEHAVIOR_FULLBURSTS);
		break;
	case CObstacle::TYPE_BOSSMAP_CAGE:
		CAnimationItem::DropItem(GetPosition(), true, CItem::ANIM_ITEMTYPE_DANCEMONKEY);
		break;
	default:
		break;
	}
}

// =====================================================================================================================================================================
// ��Q����j�󂷂邩���߂鏈��
// =====================================================================================================================================================================
void CObstacle::CheckDie(TAG tag)
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

		//����s�ɂ���
		GetCollision()->SetCanCollision(false);

		switch (m_ObstacleType)
		{
		case CObstacle::TYPE_BOX:
		case CObstacle::TYPE_BARREL:
		case CObstacle::TYPE_TREE:
		case CObstacle::TYPE_CHEST:
		case CObstacle::TYPE_SANDBAGS:
		case CObstacle::TYPE_CAR:
		case CObstacle::TYPE_BALLOON:
		case CObstacle::TYPE_PRESENTBOX:
		case CObstacle::TYPE_PRESENTBOX_RARE:
		case CObstacle::TYPE_BOSSMAP_BELL:
		case CObstacle::TYPE_BOSSMAP_CAGE:

			//��������
			CParticle::CreateFromText(GetPosition(), ZeroVector3, CParticleParam::EFFECT_EXPLOSION_OBJECTBREAK);
			break;

			//������
		case CObstacle::TYPE_BARRELBOMB:
			//�f�J����������
			CParticle::CreateFromText(GetPosition() - D3DXVECTOR3(0.0f,GetSize().y * 0.5f,0.0f), ZeroVector3, CParticleParam::EFFECT_EXPLOSION_DANGERBOX,tag);
			break;

		}
	}
}
//====================================================================
// �_���[�W���󂯂����̏���
//====================================================================
void CObstacle::AddDamage(int nDamage)
{
	this->SetLife(this->m_nLife -= nDamage);
}

//====================================================================
// �p�����[�^�[�̐ݒ�
//====================================================================
void CObstacle::SetObstacleParam(CObstacle::OBSTACLE_TYPE type)
{
	m_nLife = m_ObstacleParam[type].nLife;
	SetSize(m_ObstacleParam[type].CollisionSize);
}

//====================================================================
// �T�C�Y�̐ݒ�
//====================================================================
void CObstacle::SetCollisionSize(CObstacle::OBSTACLE_TYPE type)
{
	// �����蔻��̑傫����ݒ�
	GetCollision()->SetSize(m_ObstacleParam[type].CollisionSize);
	GetCollision()->DeCollisionCreate(CCollision::COLLISIONTYPE_CHARACTER);
	// ���̐ݒ�
	SetObstacleParam(type);

	if (type == OBSTACLE_TYPE_BRIDGE-500)
	{
		GetCollision()->SetCanCollision(false);
	}
};

