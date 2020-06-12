// =====================================================================================================================================================================
//
// �}�b�v�̏��� [map.cpp]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#include "map.h"			// �C���N���[�h�t�@�C��
#include "debugproc.h"
#include "manager.h"
#include "game.h"
#include "objectmodel.h"
#include "effect.h"
#include "item.h"
#include "object2D.h"
#include "slope.h"

// =====================================================================================================================================================================
// �}�N����`
// =====================================================================================================================================================================
#define MAP_FILE_NAME00			("data/FILE/MAP/map.txt")		// �}�b�v�e�L�X�g

#define MAP2D_FILE_NAME00		("data/FILE/MAP/2Dmap.txt")		// 2D�I�u�W�F�N�g�e�L�X�g

#define ITEM_FILE_NAME00		("data/FILE/MAP/item.txt")		// �A�C�e���e�L�X�g

#define SLOPE_FILE_NAME00		("data/FILE/MAP/sloppe.txt")	// ��̃e�L�X�g

#define OBJECT2D_POS_X			(-148)							// 2D�I�u�W�F�N�g��X��Pos

// =====================================================================================================================================================================
// �ÓI�����o�ϐ��̏�����
// =====================================================================================================================================================================
CObjectModel	*CMap::m_pObject[MAX_OBJECT]	= {};	// �I�u�W�F�N�g���
CObject2D		*CMap::m_pObject2D[MAX_OBJECT2D]	= {};	// 2D�I�u�W�F�N�g���
CItem			*CMap::m_pItem[MAX_ITEM]		= {};	// �A�C�e�����
CSlope			*CMap::m_pSlope[MAX_SLOPE]		= {};	// ��̏��

// =====================================================================================================================================================================
//
// �I�u�W�F�N�g�̓����蔻��
//
// =====================================================================================================================================================================
bool CMap::CollisionObjectAll(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 *pSize)
{
	// �ϐ��錾
	bool bLand = false;						// ���n�t���O

	// �I�u�W�F�N�g���f���̏��
	CObjectModel *pObject;

	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		if (m_pObject[nCntObject] != NULL)
		{
			if (m_pObject[nCntObject]->CollisionObject(pPos, pPosOld, pMove, pSize, &pObject))
			{
				bLand = true;
			}
		}
	}
	return bLand;
}

// =====================================================================================================================================================================
//
// 2D�I�u�W�F�N�g�̓����蔻��
//
// =====================================================================================================================================================================
bool CMap::CollisionObject2DAll(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * pMove, D3DXVECTOR3 * pSize)
{
	bool bLand = false;

	// �I�u�W�F�N�g���f���̏��
	CObject2D *pObject2D;

	for (int nCntObject2D = 0; nCntObject2D < MAX_OBJECT2D; nCntObject2D++)
	{
		if (m_pObject2D[nCntObject2D] != NULL)
		{
			if (m_pObject2D[nCntObject2D]->CollisionObject2D(pPos, pPosOld, pMove, pSize, &pObject2D))
			{
				bLand = true;
			}
		}
	}
	return bLand;
}

// =====================================================================================================================================================================
//
// ��̍����̎擾
//
// =====================================================================================================================================================================
bool CMap::GetHeightSlopeAll(D3DXVECTOR3 &pos, D3DXVECTOR3 &move)
{
	bool bLand = false;

	for (int nCntSlope = 0; nCntSlope < MAX_SLOPE; nCntSlope++)
	{
		if (m_pSlope[nCntSlope] != NULL)
		{
			// �����̎擾
			if (m_pSlope[nCntSlope]->GetHeight(pos))
			{
				CDebugProc::Print("pos %.2f,%.2f %.2f\n", pos.x, pos.y, pos.z);
				CDebugProc::Print("move %.2f,%.2f %.2f\n", move.x, move.y, move.z);

				move.y = 0.0f;
				bLand = true;
			}
		}
	}
	return bLand;
}

// =====================================================================================================================================================================
//
// �}�b�v�̍X�V
//
// =====================================================================================================================================================================
void CMap::MapUpdate()
{
	// �I�u�W�F�N�g�̃Z�b�g
	ObjectSet();

	// 2D�I�u�W�F�N�g�̃Z�b�g
	Object2DSet();

	// �A�C�e���̃Z�b�g
	ItemSet();

	// ��̃Z�b�g
	SlopeSet();
}

// =====================================================================================================================================================================
//
// �}�b�v�̓ǂݍ���
//
// =====================================================================================================================================================================
void CMap::ObjectLoad()
{
	// �t�@�C���|�C���g
	FILE *pFile;

	char cReadText[128];			// �����Ƃ��ēǂݎ��
	char cHeadText[128];			// ��r�p
	char cDie[128];					// �s�v�ȕ���
	static int nCntObject = 0;		// �ԍ�
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu
	CObjectModel::OBJECTTYPE type = CObjectModel::OBJECTTYPE_NONE;						// ���

	// �t�@�C�����J��
	pFile = fopen(MAP_FILE_NAME00, "r");

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

				// MODELSET��������
				if (strcmp(cHeadText, "MODELSET") == 0)
				{
					// END_MODELSET������܂Ń��[�v
					while (strcmp(cHeadText, "END_MODELSET") != 0)
					{
						fgets(cReadText, sizeof(cReadText), pFile); // �ꕶ�ǂݍ���
						sscanf(cReadText, "%s", &cHeadText);		// ��r�p�e�L�X�g�ɕ�������

						// TYPE��������
						if (strcmp(cHeadText, "TYPE") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &type);		// ��r�p�e�L�X�g��TYPE����
						}
						// POS��������
						else if (strcmp(cHeadText, "POS") == 0)
						{
							sscanf(cReadText, "%s %s %f %f %f", &cDie, &cDie, &pos.x, &pos.y, &pos.z);		// ��r�p�e�L�X�g��POS����
						}
						else if (strcmp(cHeadText, "END_MODELSET") == 0)
						{
							if (m_pObject[nCntObject] == NULL)
							{
								// �I�u�W�F�N�g�̐���
								m_pObject[nCntObject] = CObjectModel::Create(pos, type);
							}
						}
					}
					// �J�E���g�A�b�v
					nCntObject++;
				}
			}
		}
		// �t�@�C�������
		fclose(pFile);
	}
	nCntObject = 0;
}

// =====================================================================================================================================================================
//
// 2D�I�u�W�F�N�g�̓ǂݍ���
//
// =====================================================================================================================================================================
void CMap::Object2DLoad(void)
{
	// �t�@�C���|�C���g
	FILE *pFile;

	char cReadText[128];			// �����Ƃ��ēǂݎ��
	char cHeadText[128];			// ��r�p
	char cDie[128];					// �s�v�ȕ���
	static int nCntObject2D = 0;	// �ԍ�
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu
	CObject2D::OBJECT_2D_TYPE type = CObject2D::OBJECT_2D_TYPE_NONE;		// ���

	// �t�@�C�����J��
	pFile = fopen(MAP2D_FILE_NAME00, "r");

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

				// MODELSET��������
				if (strcmp(cHeadText, "2DOBJECTSET") == 0)
				{
					// END_MODELSET������܂Ń��[�v
					while (strcmp(cHeadText, "END_2DOBJECTSET") != 0)
					{
						fgets(cReadText, sizeof(cReadText), pFile); // �ꕶ�ǂݍ���
						sscanf(cReadText, "%s", &cHeadText);		// ��r�p�e�L�X�g�ɕ�������

						// TYPE��������
						if (strcmp(cHeadText, "TYPE") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &type);		// ��r�p�e�L�X�g��TYPE����
						}
						// POS��������
						else if (strcmp(cHeadText, "POS") == 0)
						{
							sscanf(cReadText, "%s %s %f %f %f", &cDie, &cDie, &pos.x, &pos.y, &pos.z);		// ��r�p�e�L�X�g��POS����
						}
						else if (strcmp(cHeadText, "END_2DOBJECTSET") == 0)
						{
							if (m_pObject2D[nCntObject2D] == NULL)
							{
								// 2D�I�u�W�F�N�g�̐���
								m_pObject2D[nCntObject2D] = CObject2D::Create(pos, type);
							}
						}
					}
					// �J�E���g�A�b�v
					nCntObject2D++;
				}
			}
		}
		// �t�@�C�������
		fclose(pFile);
	}
	nCntObject2D = 0;
}

// =====================================================================================================================================================================
//
// �A�C�e���̓ǂݍ���
//
// =====================================================================================================================================================================
void CMap::ItemLoad(void)
{
	// �t�@�C���|�C���g
	FILE *pFile;

	char cReadText[128];			// �����Ƃ��ēǂݎ��
	char cHeadText[128];			// ��r�p
	char cDie[128];					// �s�v�ȕ���
	static int nCntItem = 0;		// �ԍ�
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu
	CItem::ITEMTYPE type = CItem::ITEMTYPE_NONE;		// ���

	// �t�@�C�����J��
	pFile = fopen(ITEM_FILE_NAME00, "r");

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
				if (strcmp(cHeadText, "ITEMSET") == 0)
				{
					// END_ITEMSET������܂Ń��[�v
					while (strcmp(cHeadText, "END_ITEMSET") != 0)
					{
						fgets(cReadText, sizeof(cReadText), pFile); // �ꕶ�ǂݍ���
						sscanf(cReadText, "%s", &cHeadText);		// ��r�p�e�L�X�g�ɕ�������

						// TYPE��������
						if (strcmp(cHeadText, "TYPE") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &type);		// ��r�p�e�L�X�g��TYPE����
						}
						// POS��������
						else if (strcmp(cHeadText, "POS") == 0)
						{
							sscanf(cReadText, "%s %s %f %f %f", &cDie, &cDie, &pos.x, &pos.y, &pos.z);		// ��r�p�e�L�X�g��POS����
						}
						else if (strcmp(cHeadText, "END_ITEMSET") == 0)
						{
							if (m_pItem[nCntItem] == NULL)
							{
								// �I�u�W�F�N�g�̐���
								m_pItem[nCntItem] = CItem::Create(pos, type);
							}
						}
					}
					// �J�E���g�A�b�v
					nCntItem++;
				}
			}
		}
		// �t�@�C�������
		fclose(pFile);
	}
	nCntItem = 0;
}

// =====================================================================================================================================================================
//
// ��̓ǂݍ���
//
// =====================================================================================================================================================================
void CMap::SlopeLoad(void)
{
	// �t�@�C���|�C���g
	FILE *pFile;

	char cReadText[128];			// �����Ƃ��ēǂݎ��
	char cHeadText[128];			// ��r�p
	char cDie[128];					// �s�v�ȕ���
	static int nCntSlope	 = 0;	// �ԍ�
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu
	float fSlope = 0.0f;								// �Ζ�

	// �t�@�C�����J��
	pFile = fopen(SLOPE_FILE_NAME00, "r");

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

				// MODELSET��������
				if (strcmp(cHeadText, "SLOPESET") == 0)
				{
					// END_MODELSET������܂Ń��[�v
					while (strcmp(cHeadText, "END_SLOPESET") != 0)
					{
						fgets(cReadText, sizeof(cReadText), pFile); // �ꕶ�ǂݍ���
						sscanf(cReadText, "%s", &cHeadText);		// ��r�p�e�L�X�g�ɕ�������

						// SLOPE��������
						if (strcmp(cHeadText, "SLOPE") == 0)
						{
							sscanf(cReadText, "%s %s %f", &cDie, &cDie, &fSlope);		// ��r�p�e�L�X�g��SLOPE����
						}
						// POS��������
						else if (strcmp(cHeadText, "POS") == 0)
						{
							sscanf(cReadText, "%s %s %f %f %f", &cDie, &cDie, &pos.x, &pos.y, &pos.z);		// ��r�p�e�L�X�g��POS����
						}
						else if (strcmp(cHeadText, "END_SLOPESET") == 0)
						{
							if (m_pSlope[nCntSlope] == NULL)
							{
								// 2D�I�u�W�F�N�g�̐���
								m_pSlope[nCntSlope] = CSlope::Create(pos, fSlope);
							}
						}
					}
					// �J�E���g�A�b�v
					nCntSlope++;
				}
			}
		}
	}
	nCntSlope = 0;
}

// =====================================================================================================================================================================
//
// �}�b�v�̉��
//
// =====================================================================================================================================================================
void CMap::ReleaseMap()
{
	// 3D�I�u�W�F�N�g
	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		if (m_pObject[nCntObject] != NULL)
		{
			m_pObject[nCntObject] = NULL;
		}
	}

	// 2D�I�u�W�F�N�g
	for (int nCntObject2D = 0; nCntObject2D < MAX_OBJECT2D; nCntObject2D++)
	{
		if (m_pObject2D[nCntObject2D] != NULL)
		{
			m_pObject2D[nCntObject2D] = NULL;
		}
	}

	// �A�C�e��
	for (int nCntItem = 0; nCntItem < MAX_OBJECT2D; nCntItem++)
	{
		if (m_pItem[nCntItem] != NULL)
		{
			m_pItem[nCntItem] = NULL;
		}
	}

	// ��
	for (int nCntSlope = 0; nCntSlope < MAX_OBJECT2D; nCntSlope++)
	{
		if (m_pSlope[nCntSlope] != NULL)
		{
			m_pSlope[nCntSlope] = NULL;
		}
	}
}

// =====================================================================================================================================================================
//
// �����I�}�b�v�̔z�u
//
// =====================================================================================================================================================================
void CMap::SetProvisionalMap(void)
{
	m_pSlope[0] = CSlope::Create(D3DXVECTOR3(0.0f, 200.0f, 1000.0f), 30);
	m_pSlope[1] = CSlope::Create(D3DXVECTOR3(0.0f, 150.0f, 500.0f), -30);
}

// =====================================================================================================================================================================
//
// �}�b�v�̏�������
//
// =====================================================================================================================================================================
void CMap::ObjectSave()
{
	// �t�@�C���|�C���g
	FILE	*pFile;

	// �t�@�C�����J��
	pFile = fopen(MAP_FILE_NAME00, "w");

	// �J���Ă���Ƃ�
	if (pFile != NULL)
	{
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "# �I�u�W�F�N�g�̔z�u���\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "# TYPE���\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#	[ 0 ]	��\n");
		fprintf(pFile, "#	[ 1 ]	��\n");
		fprintf(pFile, "#	[ 2 ]	�n�� ( ��\n");
		fprintf(pFile, "#	[ 3 ]	�n�� ( ��\n");
		fprintf(pFile, "#	[ 4 ]	�n�� ( ��\n");
		fprintf(pFile, "#	[ 5 ]	�Ԍ���\n");
		fprintf(pFile, "#	[ 6 ]	����\n");
		fprintf(pFile, "#	[ 7 ]	2D�ł������鑫��\n");
		fprintf(pFile, "#	[ 8 ]	��������\n");
		fprintf(pFile, "#	[ 9 ]	��\n");
		fprintf(pFile, "#	[ 10 ]	�n�� (�n�[�t\n");
		fprintf(pFile, "#	[ 11 ]	�Ŕ� (������\n");
		fprintf(pFile, "#	[ 12 ]	�Ŕ� (�W�����v\n");
		fprintf(pFile, "#	[ 13 ]	�Ŕ� (�Ԍ���\n");
		fprintf(pFile, "#	[ 14 ]	�Ŕ� (�J�����ؑւ�\n");
		fprintf(pFile, "#	[ 15 ]	�Ŕ� (2D�ł�����\n");
		fprintf(pFile, "#	[ 16 ]	�Ŕ� (3D�ł������Ȃ�\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");

		fprintf(pFile, "SCRIPT\n\n");

		for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
		{
			// NULL�`�F�b�N
			if (m_pObject[nCntObject] != NULL)
			{
				D3DXVECTOR3 ObjectPos = m_pObject[nCntObject]->GetPos();	// �I�u�W�F�N�g�̈ʒu�擾

				fprintf(pFile, "MODELSET									# %d\n", nCntObject);

				fprintf(pFile, "	TYPE	= %d\n", m_pObject[nCntObject]->GetObjectType());
				fprintf(pFile, "	POS		= %.0f %.0f %.0f\n", ObjectPos.x, ObjectPos.y, ObjectPos.z);

				fprintf(pFile, "END_MODELSET\n\n");
			}
		}

		fprintf(pFile, "END_SCRIPT\n");

		// �t�@�C�������
		fclose(pFile);
	}
	else
	{
		// ���b�Z�[�W�E�B���h�E�Ōx��
		MessageBox(NULL, "�t�@�C�����J����Ă��܂�", "�x��", MB_OK | MB_ICONWARNING);
	}
}

// =====================================================================================================================================================================
//
// 2D�I�u�W�F�N�g�̏�������
//
// =====================================================================================================================================================================
void CMap::Object2DSave(void)
{
	// �t�@�C���|�C���g
	FILE	*pFile;

	// �t�@�C�����J��
	pFile = fopen(MAP2D_FILE_NAME00, "w");

	// �J���Ă���Ƃ�
	if (pFile != NULL)
	{
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "# 2D�I�u�W�F�N�g�̔z�u���\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "# TYPE���\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#	[ 0 ]	��\n");
		fprintf(pFile, "#	[ 1 ]	��\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");

		fprintf(pFile, "SCRIPT\n\n");

		for (int nCntObject2D = 0; nCntObject2D < MAX_OBJECT2D; nCntObject2D++)
		{
			// NULL�`�F�b�N
			if (m_pObject2D[nCntObject2D] != NULL)
			{
				D3DXVECTOR3 Object2DPos = m_pObject2D[nCntObject2D]->GetPos();	// 2D�I�u�W�F�N�g�̈ʒu�擾

				fprintf(pFile, "2DOBJECTSET									# %d\n", nCntObject2D);

				fprintf(pFile, "	TYPE	= %d\n", m_pObject2D[nCntObject2D]->GetObject2DType());
				fprintf(pFile, "	POS		= %.0f %.0f %.0f\n", Object2DPos.x, Object2DPos.y, Object2DPos.z);

				fprintf(pFile, "END_2DOBJECTSET\n\n");
			}
		}

		fprintf(pFile, "END_SCRIPT\n");

		// �t�@�C�������
		fclose(pFile);
	}
	else
	{
		// ���b�Z�[�W�E�B���h�E�Ōx��
		MessageBox(NULL, "�t�@�C�����J����Ă��܂�", "�x��", MB_OK | MB_ICONWARNING);
	}
}

// =====================================================================================================================================================================
//
// �A�C�e���̏�������
//
// =====================================================================================================================================================================
void CMap::ItemSave(void)
{
	// �t�@�C���|�C���g
	FILE	*pFile;

	// �t�@�C�����J��
	pFile = fopen(ITEM_FILE_NAME00, "w");

	// �J���Ă���Ƃ�
	if (pFile != NULL)
	{
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "# �A�C�e���̔z�u���\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "# TYPE���\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#	[ 0 ]	�X�s�[�h�A�b�v\n");
		fprintf(pFile, "#	[ 1 ]	�_�C��\n");
		fprintf(pFile, "#	[ 2 ]	���\n");
		fprintf(pFile, "#	[ 3 ]	����\n");
		fprintf(pFile, "#	[ 4 ]	��\n");
		fprintf(pFile, "#	[ 5 ]	1up\n");
		fprintf(pFile, "#	[ 6 ]	����\n");
		fprintf(pFile, "#	[ 7 ]	�G�l���M�[\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");

		fprintf(pFile, "SCRIPT\n\n");

		for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
		{
			// NULL�`�F�b�N
			if (m_pItem[nCntItem] != NULL)
			{
				D3DXVECTOR3 ItemPos = m_pItem[nCntItem]->GetPos();	// �A�C�e���̈ʒu�擾

				fprintf(pFile, "ITEMSET									# %d\n", nCntItem);

				fprintf(pFile, "	TYPE	= %d\n", m_pItem[nCntItem]->GetItemType());
				fprintf(pFile, "	POS		= %.0f %.0f %.0f\n", ItemPos.x, ItemPos.y, ItemPos.z);

				fprintf(pFile, "END_ITEMSET\n\n");
			}
		}

		fprintf(pFile, "END_SCRIPT\n");

		// �t�@�C�������
		fclose(pFile);
	}
	else
	{
		// ���b�Z�[�W�E�B���h�E�Ōx��
		MessageBox(NULL, "�t�@�C�����J����Ă��܂�", "�x��", MB_OK | MB_ICONWARNING);
	}
}

// =====================================================================================================================================================================
//
// ��̏�������
//
// =====================================================================================================================================================================
void CMap::SlopeSave(void)
{
	// �t�@�C���|�C���g
	FILE	*pFile;

	// �t�@�C�����J��
	pFile = fopen(SLOPE_FILE_NAME00, "w");

	// �J���Ă���Ƃ�
	if (pFile != NULL)
	{
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "# ��̔z�u���\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");

		fprintf(pFile, "SCRIPT\n\n");

		for (int nCntSlope = 0; nCntSlope < MAX_SLOPE; nCntSlope++)
		{
			// NULL�`�F�b�N
			if (m_pSlope[nCntSlope] != NULL)
			{
				D3DXVECTOR3 SlopePos = m_pSlope[nCntSlope]->GetPos();	// ��̈ʒu�擾

				fprintf(pFile, "SLOPESET									# %d\n", nCntSlope);

				fprintf(pFile, "	SLOPE	= %f\n", m_pSlope[nCntSlope]->GetSlope());
				fprintf(pFile, "	POS		= %.0f %.0f %.0f\n", SlopePos.x, SlopePos.y, SlopePos.z);

				fprintf(pFile, "END_SLOPESET\n\n");
			}
		}

		fprintf(pFile, "END_SCRIPT\n");

		// �t�@�C�������
		fclose(pFile);
	}
	else
	{
		// ���b�Z�[�W�E�B���h�E�Ōx��
		MessageBox(NULL, "�t�@�C�����J����Ă��܂�", "�x��", MB_OK | MB_ICONWARNING);
	}
}

// =====================================================================================================================================================================
//
// �I�u�W�F�N�g�̃Z�b�g
//
// =====================================================================================================================================================================
void CMap::ObjectSet(void)
{
	static int nObjectType = 0;		// �I�u�W�F�N�g�̎��
	static int nNowSelect = -1;		// ���ݑI�����Ă���I�u�W�F�N�g�ԍ�
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu

	CEffect *pEffect = CManager::GetGame()->GetEffect();	// �G�t�F�N�g���擾

	// �I�u�W�F�N�g�E�B���h�E
	ImGui::Begin("Object", nullptr, ImGuiWindowFlags_MenuBar);

	// �t�@�C�� (�Z�[�u�E���[�h)
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Save"))
			{
				// �I�u�W�F�N�g�̏�������
				ObjectSave();
			}
			if (ImGui::MenuItem("Load"))
			{
				// �I�u�W�F�N�g�̓ǂݍ���
				ObjectLoad();
			}
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}

	// �I�u�W�F�N�g�̃R���{�{�b�N�X
	if (CLibrary::SetObjectComboBox(nObjectType))
	{
		// NULL�`�F�b�N
		if (m_pObject[nNowSelect] != NULL)
		{
			// �I�u�W�F�N�g�̎�ނ̎擾
			CObjectModel::OBJECTTYPE ObjectType = m_pObject[nNowSelect]->GetObjectType();

			// �O��ƈႤ�Ƃ�
			if (ObjectType != nObjectType)
			{
				ObjectType = (CObjectModel::OBJECTTYPE)nObjectType;	// ���

				// �I�u�W�F�N�g�^�C�v�̐ݒ�
				m_pObject[nNowSelect]->SetObjectType(ObjectType);
			}
		}
	}

	// �I�u�W�F�N�g�ԍ��̑I��
	ImGui::InputInt("nowSelect", &nNowSelect, 1, 20, 0);

	// �͈͐���
	if (nNowSelect <= -1)
	{
		nNowSelect = -1;
	}
	else if (nNowSelect >= 0)
	{
		// NULL�`�F�b�N
		if (m_pObject[nNowSelect] != NULL)
		{
			// ���ݒn
			int x = (int)m_pObject[nNowSelect]->GetPos().x,
				y = (int)m_pObject[nNowSelect]->GetPos().y,
				z = (int)m_pObject[nNowSelect]->GetPos().z;

			// �I�u�W�F�N�g�̈ړ�
			ImGui::DragInt("X", &x);
			ImGui::DragInt("Y", &y);
			ImGui::DragInt("Z", &z);

			// �I�u�W�F�N�g�̈ʒu�̐ݒ�
			m_pObject[nNowSelect]->SetPos(D3DXVECTOR3((float)x, (float)y, (float)z));

			if (pEffect != NULL)
			{
				// �G�t�F�N�g�̈ʒu�̐ݒ�
				pEffect->SetPos(D3DXVECTOR3((float)x, (float)y + 50.0f, (float)z));
			}
		}
	}
	// �I�u�W�F�N�g�̐���
	if (ImGui::Button("Crate"))
	{
		for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
		{
			if (m_pObject[nCntObject] == NULL)
			{
				// �I�u�W�F�N�g�̐���
				m_pObject[nCntObject] = CObjectModel::Create(pos, (CObjectModel::OBJECTTYPE)nObjectType);
				break;
			}
		}
	}

	ImGui::End();
}

// =====================================================================================================================================================================
//
// 2D�I�u�W�F�N�g�̃Z�b�g
//
// =====================================================================================================================================================================
void CMap::Object2DSet(void)
{
	static int nObject2DType = 0;		// 2D�I�u�W�F�N�g�̎��
	static int nNowSelect = -1;			// ���ݑI�����Ă���A�C�e���ԍ�
	D3DXVECTOR3 pos = D3DXVECTOR3(OBJECT2D_POS_X, 0.0f, 0.0f);	// �ʒu

	CEffect *pEffect = CManager::GetGame()->GetEffect();	// �G�t�F�N�g���擾

	// 2D�I�u�W�F�N�g�E�B���h�E
	ImGui::Begin("Object2D", nullptr, ImGuiWindowFlags_MenuBar);

	// �t�@�C�� (�Z�[�u�E���[�h)
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Save"))
			{
				// 2D�I�u�W�F�N�g�̏�������
				Object2DSave();
			}
			if (ImGui::MenuItem("Load"))
			{
				// 2D�I�u�W�F�N�g�̓ǂݍ���
				Object2DLoad();
			}

			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}

	// 2D�I�u�W�F�N�g�̃R���{�{�b�N�X
	if (CLibrary::SetObject2DComboBox(nObject2DType))
	{
		// NULL�`�F�b�N
		if (m_pObject2D[nNowSelect] != NULL)
		{
			// 2D�I�u�W�F�N�g�̎�ނ̎擾
			CObject2D::OBJECT_2D_TYPE ObjectType = m_pObject2D[nNowSelect]->GetObject2DType();

			// �O��ƈႤ�Ƃ�
			if (ObjectType != nObject2DType)
			{
				ObjectType = (CObject2D::OBJECT_2D_TYPE)nObject2DType;	// ���

				// 2D�I�u�W�F�N�g�^�C�v�̐ݒ�
				m_pObject2D[nNowSelect]->SetObject2DType(ObjectType);
			}
		}
	}

	// 2D�I�u�W�F�N�g�ԍ��̑I��
	ImGui::InputInt("nowSelect", &nNowSelect, 1, 20, 0);

	// �͈͐���
	if (nNowSelect <= -1)
	{
		nNowSelect = -1;
	}
	else if (nNowSelect >= 0)
	{
		// NULL�`�F�b�N
		if (m_pObject2D[nNowSelect] != NULL)
		{
			// ���ݒn
			int x = (int)m_pObject2D[nNowSelect]->GetPos().x,
				y = (int)m_pObject2D[nNowSelect]->GetPos().y,
				z = (int)m_pObject2D[nNowSelect]->GetPos().z;

			// 2D�I�u�W�F�N�g�̈ړ�
			ImGui::DragInt("X", &x);
			ImGui::DragInt("Y", &y);
			ImGui::DragInt("Z", &z);

			// 2D�I�u�W�F�N�g�̈ʒu�̐ݒ�
			m_pObject2D[nNowSelect]->SetPos(D3DXVECTOR3((float)x, (float)y, (float)z));

			if (pEffect != NULL)
			{
				// �G�t�F�N�g�̈ʒu�̐ݒ�
				pEffect->SetPos(D3DXVECTOR3((float)x, (float)y + 0.0f, (float)z));
			}
		}
	}
	// 2D�I�u�W�F�N�g�̐���
	if (ImGui::Button("Crate"))
	{
		for (int nCntObject2D = 0; nCntObject2D < MAX_OBJECT2D; nCntObject2D++)
		{
			if (m_pObject2D[nCntObject2D] == NULL)
			{
				// 2D�I�u�W�F�N�g�̐���
				m_pObject2D[nCntObject2D] = CObject2D::Create(pos, (CObject2D::OBJECT_2D_TYPE)nObject2DType);
				break;
			}
		}
	}
	ImGui::End();
}

// =====================================================================================================================================================================
//
// �A�C�e���̃Z�b�g
//
// =====================================================================================================================================================================
void CMap::ItemSet(void)
{
	static int nItemType = 0;		// �A�C�e���̎��
	static int nNowSelect = -1;		// ���ݑI�����Ă���A�C�e���ԍ�
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu

	CEffect *pEffect = CManager::GetGame()->GetEffect();	// �G�t�F�N�g���擾

	// �A�C�e���E�B���h�E
	ImGui::Begin("Item", nullptr, ImGuiWindowFlags_MenuBar);

	// �t�@�C�� (�Z�[�u�E���[�h)
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Save"))
			{
				// �I�u�W�F�N�g�̏�������
				ItemSave();
			}
			if (ImGui::MenuItem("Load"))
			{
				// �I�u�W�F�N�g�̓ǂݍ���
				ItemLoad();
			}

			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}

	// �A�C�e���̃R���{�{�b�N�X
	if (CLibrary::SetItemComboBox(nItemType))
	{
		// NULL�`�F�b�N
		if (m_pItem[nNowSelect] != NULL)
		{
			// �A�C�e���̎�ނ̎擾
			CItem::ITEMTYPE ItemType = m_pItem[nNowSelect]->GetItemType();

			// �O��ƈႤ�Ƃ�
			if (ItemType != nItemType)
			{
				ItemType = (CItem::ITEMTYPE)nItemType;	// ���

				// �A�C�e���^�C�v�̐ݒ�
				m_pItem[nNowSelect]->SetItemType(ItemType);
			}
		}
	}

	// �A�C�e���ԍ��̑I��
	ImGui::InputInt("nowSelect", &nNowSelect, 1, 20, 0);

	// �͈͐���
	if (nNowSelect <= -1)
	{
		nNowSelect = -1;
	}
	else if (nNowSelect >= 0)
	{
		// NULL�`�F�b�N
		if (m_pItem[nNowSelect] != NULL)
		{
			// ���ݒn
			int x = (int)m_pItem[nNowSelect]->GetPos().x,
				y = (int)m_pItem[nNowSelect]->GetPos().y,
				z = (int)m_pItem[nNowSelect]->GetPos().z;

			// �A�C�e���̈ړ�
			ImGui::DragInt("X", &x);
			ImGui::DragInt("Y", &y);
			ImGui::DragInt("Z", &z);

			// �A�C�e���̈ʒu�̐ݒ�
			m_pItem[nNowSelect]->SetPos(D3DXVECTOR3((float)x, (float)y, (float)z));

			if (pEffect != NULL)
			{
				// �G�t�F�N�g�̈ʒu�̐ݒ�
				pEffect->SetPos(D3DXVECTOR3((float)x, (float)y + 0.0f, (float)z));
			}
		}
	}
	// �A�C�e���̐���
	if (ImGui::Button("Crate"))
	{
		for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
		{
			if (m_pItem[nCntItem] == NULL)
			{
				// �A�C�e���̐���
				m_pItem[nCntItem] = CItem::Create(pos, (CItem::ITEMTYPE)nItemType);
				break;
			}
		}
	}

	ImGui::End();
}

// =====================================================================================================================================================================
//
// ��̃Z�b�g
//
// =====================================================================================================================================================================
void CMap::SlopeSet(void)
{
	static int		fSlope		= 0;								// ��̎Ζ�
	static int		nNowSelect	= -1;								// ���ݑI�����Ă����̔ԍ�
	D3DXVECTOR3		pos			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu
	CEffect			*pEffect	= CManager::GetGame()->GetEffect();	// �G�t�F�N�g���擾

	// ��E�B���h�E
	ImGui::Begin("Slope", nullptr, ImGuiWindowFlags_MenuBar);

	// �t�@�C�� (�Z�[�u�E���[�h)
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Save"))
			{
				// �I�u�W�F�N�g�̏�������
				SlopeSave();
			}
			if (ImGui::MenuItem("Load"))
			{
				// �I�u�W�F�N�g�̓ǂݍ���
				SlopeLoad();
			}

			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}

	// NULL�`�F�b�N
	if (m_pSlope[nNowSelect] != NULL)
	{
		// ��̎Ζʂ̎擾
		fSlope = (int)m_pSlope[nNowSelect]->GetSlope();

		// ��̃R���{�{�b�N�X
		ImGui::InputInt("Slope", &fSlope, 1, 20, 0);
		{
			// ��̎Ζʂ̐ݒ�
			m_pSlope[nNowSelect]->SetSlopSize((float)fSlope);
		}
	}

	// ��̔ԍ��̑I��
	ImGui::InputInt("nowSelect", &nNowSelect, 1, 20, 0);

	// �͈͐���
	if (nNowSelect <= -1)
	{
		nNowSelect = -1;
	}
	else if (nNowSelect >= 0)
	{
		// NULL�`�F�b�N
		if (m_pSlope[nNowSelect] != NULL)
		{
			// ���ݒn
			int x = (int)m_pSlope[nNowSelect]->GetPos().x,
				y = (int)m_pSlope[nNowSelect]->GetPos().y,
				z = (int)m_pSlope[nNowSelect]->GetPos().z;

			// ��̈ړ�
			ImGui::DragInt("X", &x);
			ImGui::DragInt("Y", &y);
			ImGui::DragInt("Z", &z);

			// ��̈ʒu�̐ݒ�
			m_pSlope[nNowSelect]->SetPos(D3DXVECTOR3((float)x, (float)y, (float)z));

			if (pEffect != NULL)
			{
				// �G�t�F�N�g�̈ʒu�̐ݒ�
				pEffect->SetPos(D3DXVECTOR3((float)x, (float)y + 0.0f, (float)z));
			}
		}
	}
	// ��̐���
	if (ImGui::Button("Crate"))
	{
		for (int nCntSlope = 0; nCntSlope < MAX_SLOPE; nCntSlope++)
		{
			if (m_pSlope[nCntSlope] == NULL)
			{
				// �I�u�W�F�N�g�̐���
				m_pSlope[nCntSlope] = CSlope::Create(pos, (float)fSlope);
				break;
			}
		}
	}

	ImGui::End();
}