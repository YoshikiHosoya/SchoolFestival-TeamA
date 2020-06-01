// ----------------------------------------
//
// �^�C���������̐���[floartile.h]
// Author : Fujiwara Masato
//
// ----------------------------------------

// ----------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ----------------------------------------
#include "floartile.h"
#include "model_info.h"
#include "enemy.h"
#include "player.h"
#include "debugproc.h"
// ----------------------------------------
//
// �ÓI�ϐ��錾
//
// ----------------------------------------
LPDIRECT3DTEXTURE9 CFloarTile::m_pTexture = NULL;				// �e�N�X�`���ւ̃|�C���^
CLoad	*CFloarTile::m_pload = NULL;							// ���[�h
CModel_info	*CFloarTile::m_pmodel_info = NULL;					// ���f�����
int		CFloarTile::m_aTileType[MAX_TILENUMBER] = {};			// �^�C���̎��
int		CFloarTile::m_aTileNum[MAX_TILENUMBER] = {};			// �^�C���̐�
int CFloarTile::m_nPlayerSavepos = 0;							// �v���C���[�����񂾃}�X��ۑ�
CFloarTile *CFloarTile::m_paFloarTile[MAX_WALKTILENUMBER] = {}; // ���s�\�ȃ}�X�̑���
// ----------------------------------------
// �R���X�g���N�^
// ----------------------------------------
CFloarTile::CFloarTile() : CScene_X::CScene_X(ACTOR_FLOATTILE, LAYER_3DOBJECT)
{
	m_type = TILE_TYPE_WALL;			// �^�C���̎��
	m_Dire = DIRECTION_FORWARD;
	m_pEnemy = NULL;
	m_pFloarTile = NULL;
	m_nTileNum = 0;
	m_nEnemySavepos = 0;
	m_nSaveArrayNumber = 0;
	m_nDirection = 0;
	m_bLand_Enemy = false;
	m_nDirEnemyBackward = 0;
	for (int nCount = 0; nCount < DIRECTION_ALL; nCount++)
	{
		m_bFlag[nCount] = false;
	}
}

// ----------------------------------------
// �f�X�g���N�^����
// ----------------------------------------
CFloarTile::~CFloarTile()
{
	m_bLand_Enemy = false;
}

// ----------------------------------------
// ����������
// ----------------------------------------
void CFloarTile::Init(void)
{
	// X�I�u�W�F�N�g����
	CScene_X::Init();
	// ���f�����ݒ�
	CScene_X::BindModel(m_pmodel_info->GetModel_info());
	// �e�N�X�`���[�ݒ�
	CScene_X::BindTexture(m_pTexture);
}

// ----------------------------------------
// �I������
// ----------------------------------------
void CFloarTile::Uninit(void)
{
	CScene_X::Uninit();
}

// ----------------------------------------
// �X�V����
// ----------------------------------------
void CFloarTile::Update(void)
{
	// ���菈��
	//PlayerJudg();

	// ���菈��
	EnemyJudg();

	CScene_X::Update();
}

// ----------------------------------------
// �`�揈��
// ----------------------------------------
void CFloarTile::Draw(void)
{
	CScene_X::Draw();
}

// ----------------------------------------
// �쐬����
// ----------------------------------------
CFloarTile * CFloarTile::Create(void)
{
	// �ϐ��錾
	CFloarTile * pFloarTile;		// �V�[��3D�N���X
	// �������̐���(����->��{�N���X,��->�h���N���X)
	pFloarTile = new CFloarTile();
	// ����������
	pFloarTile->Init();
	// ���������I�u�W�F�N�g��Ԃ�
	return pFloarTile;
}

// ----------------------------------------
// �ǂݍ��ݍ쐬����
// ----------------------------------------
void CFloarTile::LoadCreate(void)
{
	// �ϐ��錾
	int nCount = 0;
	for (int nCntTile = 0; nCntTile < MAX_TILENUMBER; nCntTile++)
	{
		// �^�C���̎�ނ����s�\�Ȓʏ�̏���������
		if (m_aTileType[nCntTile] == TILE_TYPE_TILE_NOR)
		{
			m_paFloarTile[nCount] = CFloarTile::Create();						// ����
			m_paFloarTile[nCount]->SetPos(m_pload->GetInfo(nCount).pos);		// ���W

			m_paFloarTile[nCount]->m_nTileNum = m_aTileNum[nCntTile];			// �^�C���̔ԍ�����
			m_paFloarTile[nCount]->m_type = (TILE_TYPE)m_aTileType[nCntTile];	// �^�C�v(���s�\�}�X)

			nCount++; // �J�E���g���Z
		}
		// �^�C���̎�ނ����s�\�œG�Ɣ�������悤�̏���������
		else if (m_aTileType[nCntTile] == TILE_TYPE_TILE_SP)
		{
			m_paFloarTile[nCount] = CFloarTile::Create();						// ����
			m_paFloarTile[nCount]->SetPos(m_pload->GetInfo(nCount).pos);		// ���W

			m_paFloarTile[nCount]->m_nTileNum = m_aTileNum[nCntTile];			// �^�C���̔ԍ�����
			m_paFloarTile[nCount]->m_type = (TILE_TYPE)m_aTileType[nCntTile];	// �^�C�v(���s�\�}�X)

			nCount++; // �J�E���g���Z
		}
	}
}

// ----------------------------------------
// ���菈��
// ----------------------------------------
void CFloarTile::PlayerJudg()
{
}

// ----------------------------------------
// ���菈��
// ----------------------------------------
void CFloarTile::EnemyJudg()
{
	// �G�l�~�[�̃|�C���^��T��
	for (int nCntlayer = 0; nCntlayer < CScene::GetMaxLayer(CScene::LAYER_3DOBJECT); nCntlayer++)
	{
		if (m_pEnemy = (CEnemy *)CScene::GetActor(CScene::ACTOR_ENEMY, CScene::LAYER_3DOBJECT, nCntlayer)) break;
	}

	// �G�����݂��Ă��Ĕ��肪�o�Ă��Ȃ�����
	if (m_pEnemy != NULL)
	{
		for (int nCntTile = 0; nCntTile < MAX_WALKTILENUMBER; nCntTile++)
		{
			// ���ƓG�Ƃ̔���
			if (CCalculation::Plane_GetOn(
				m_paFloarTile[nCntTile]->GetPos(),
				D3DXVECTOR3(150.0f, 0.0f, 150.0f),
				m_pEnemy->GetPos(),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f)))
			{
				// ������n�_�̃}�X���O��̃}�X�łȂ����ǂ���
				if (m_nEnemySavepos != m_paFloarTile[nCntTile]->m_nTileNum)
				{
					// ���G��Ă���}�X�̔ԍ���ۑ�
					m_nEnemySavepos = m_paFloarTile[nCntTile]->m_nTileNum;

					// �^�C���ɐG��Ă��Ȃ��� ����Ȃ���������Ȃ�
					if (m_bLand_Enemy == false)
					{
						// �^�C���̃^�C�v���G�̐i�s����p�̃^�C����������
						if (m_paFloarTile[nCntTile]->m_type == TILE_TYPE_TILE_SP)
						{
							// �z��ԍ���ۑ�
							m_nSaveArrayNumber = nCntTile;

							// �G�̍s���𐧌䂷��AI
							EnemyAi();

							// �}�X�ɐG��Ă���t���O
							m_bLand_Enemy = true;
						}
					}

					//// ���G��Ă���}�X�̔ԍ���ۑ�
					//m_nEnemySavepos = m_paFloarTile[nCntTile]->m_nTileNum;
				}
			}

			else
			{
				// �G��Ă��Ȃ����A����t���O�����ɖ߂�
				m_bLand_Enemy = false;
			}
		}
	}
}

// ----------------------------------------
// �G�̐i�s�����߂�v�Z
// ----------------------------------------
void CFloarTile::EnemyAi()
{
	for (int nCount = 0; nCount < DIRECTION_ALL; nCount++)
	{
		m_bFlag[nCount] = false;
	}

	// �㉺���E�̃}�X���i�s�\�����ׂ�	//

	//----- ������}�X�̔ԍ� - ��񕪂̒��� �̏ꏊ�ɂ���^�C�������s�\�ȃ^�C�����ǂ��� -----//

	// �O�����ǂ���Ȃ�������
	if ((TILE_TYPE)m_aTileType[m_paFloarTile[m_nSaveArrayNumber]->m_nTileNum - MAX_HORIZONTALNUM] != TILE_TYPE_WALL)
	{
		m_bFlag[DIRECTION_FORWARD] = true;
	}

	//----- ������}�X�̔ԍ� + ��񕪂̒��� �̏ꏊ�ɂ���^�C�������s�\�ȃ^�C�����ǂ��� -----//

	// ������ǂ���Ȃ�������
	if ((TILE_TYPE)m_aTileType[m_paFloarTile[m_nSaveArrayNumber]->m_nTileNum + MAX_HORIZONTALNUM] != TILE_TYPE_WALL)
	{
		m_bFlag[DIRECTION_BACKWARD] = true;
	}

	//----- ������}�X�̔ԍ� - ��}�X���̒��� �̏ꏊ�ɂ���^�C�������s�\�ȃ^�C�����ǂ��� -----//

	// �����ǂ���Ȃ�������
	if ((TILE_TYPE)m_aTileType[m_paFloarTile[m_nSaveArrayNumber]->m_nTileNum - 1] != TILE_TYPE_WALL)
	{
		m_bFlag[DIRECTION_LEFT] = true;
	}

	//----- ������}�X�̔ԍ� + ��}�X���̒��� �̏ꏊ�ɂ���^�C�������s�\�ȃ^�C�����ǂ��� -----//

	// �E���ǂ���Ȃ�������
	if ((TILE_TYPE)m_aTileType[m_paFloarTile[m_nSaveArrayNumber]->m_nTileNum + 1] != TILE_TYPE_WALL)
	{
		m_bFlag[DIRECTION_RIGHT] = true;
	}

	//------------------------------------------------------------//

	// �G�̉�]��Ԃ��������m�F //
	if (m_pEnemy->GetEnemyROT() == CEnemy::ROT_FORWARD)			// �O�Ȃ���
	{
		m_bFlag[DIRECTION_BACKWARD] = false;
		m_nDirEnemyBackward = DIRECTION_BACKWARD;
	}
	else if (m_pEnemy->GetEnemyROT() == CEnemy::ROT_BACKWARD)	// ���Ȃ�O
	{
		m_bFlag[DIRECTION_FORWARD] = false;
		m_nDirEnemyBackward = DIRECTION_FORWARD;
	}
	else if (m_pEnemy->GetEnemyROT() == CEnemy::ROT_LEFT)		// ���Ȃ�E
	{
		m_bFlag[DIRECTION_RIGHT] = false;
		m_nDirEnemyBackward = DIRECTION_RIGHT;
	}
	else if (m_pEnemy->GetEnemyROT() == CEnemy::ROT_RIGHT)		// �E�Ȃ獶
	{
		m_bFlag[DIRECTION_LEFT] = false;
		m_nDirEnemyBackward = DIRECTION_LEFT;
	}

	//------------------------------------------------------------//

	bool bOK = false;

	// �i�s�������_���Ɍ��߂�
	//do {
	//	// �i�s������������܂�܂Ń����_���Ő��������߂�
	//	this->m_nDirection = rand() % DIRECTION_ALL;
	//} while (m_bFlag[this->m_nDirection] == false && this->m_nDirection == m_nDirEnemyBackward);

	if (m_bFlag[m_nDirection] == true && m_nDirection != m_nDirEnemyBackward)
	{
		bOK = true;
	}
	else
	{
		// �i�s�������_���Ɍ��߂�
		do {
			// �i�s������������܂�܂Ń����_���Ő��������߂�
			m_nDirection = rand() % DIRECTION_ALL;
		} while (m_bFlag[m_nDirection] == false && m_nDirection == m_nDirEnemyBackward);
	}


	// �v�Z���ʂ��o���猈�܂����i�s�����ɉ�]������
	if (bOK == true)
	{
		if (this->m_nDirection == DIRECTION_FORWARD && m_nDirEnemyBackward != DIRECTION_FORWARD)
		{
			m_pEnemy->SetRot(D3DXVECTOR3(0.0f, 3.14f, 0.0f), CEnemy::ROT_FORWARD);
			for (int nCount = 0; nCount < DIRECTION_ALL; nCount++)
			{
				m_bFlag[nCount] = false;
			}
		}
		else if (this->m_nDirection == DIRECTION_BACKWARD && m_nDirEnemyBackward != DIRECTION_BACKWARD)
		{
			m_pEnemy->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f), CEnemy::ROT_BACKWARD);
			for (int nCount = 0; nCount < DIRECTION_ALL; nCount++)
			{
				m_bFlag[nCount] = false;
			}
		}
		else if (this->m_nDirection == DIRECTION_LEFT && m_nDirEnemyBackward != DIRECTION_LEFT)
		{
			m_pEnemy->SetRot(D3DXVECTOR3(0.0f, 1.57f, 0.0f), CEnemy::ROT_LEFT);
			for (int nCount = 0; nCount < DIRECTION_ALL; nCount++)
			{
				m_bFlag[nCount] = false;
			}
		}
		else if (this->m_nDirection == DIRECTION_RIGHT && m_nDirEnemyBackward != DIRECTION_RIGHT)
		{
			m_pEnemy->SetRot(D3DXVECTOR3(0.0f, -1.57f, 0.0f), CEnemy::ROT_RIGHT);
			for (int nCount = 0; nCount < DIRECTION_ALL; nCount++)
			{
				m_bFlag[nCount] = false;
			}
		}

		bOK = false;
	}

	m_nDirEnemyBackward = 0;
}

// ----------------------------------------
// �ǂݍ��ݏ���
// ----------------------------------------
HRESULT CFloarTile::Load(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice =
		CManager::GetRenderer()->GetDevice();
	// �e�N�X�`���[��
	char cTex[128] =
	{
		"data/TEXTURE/FLOOR/floor01.png",
	};
	// ���f���t�@�C����
	char cModelfile[128] =
	{
		"data/MODEL/object/tile.x"
	};

	// 0����ő吔�܂ł̐�����
	for (int nCntObj = 0; nCntObj < MAX_TILENUMBER; nCntObj++)
	{
		m_aTileNum[nCntObj] += nCntObj;
	}

	// �e�N�X�`���[�ݒ�
	D3DXCreateTextureFromFile(pDevice, cTex, &m_pTexture);
	// �S�Ẵ}�X�̎�ޓǂݍ���
	LoadTileNum("data/LOAD/OBJECT/Tile_Infor.txt");
	// ���[�h����
	m_pload = new CLoad;
	// ���[�h�ǂݍ���
	m_pload->Load("data/LOAD/OBJECT/Tile_Location.txt");
	// ���f����񐶐�
	m_pmodel_info = new CModel_info;
	// ���f���ǂݍ���
	m_pmodel_info->Load(pDevice, cModelfile);
	return S_OK;
}

// ----------------------------------------
// unload����
// ----------------------------------------
void CFloarTile::UnLoad(void)
{
	// �e�N�X�`���[�ݒ�
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

	// ���[�h�̔j��
	delete m_pload;
	m_pload = NULL;
	// ���f���̔j��
	m_pmodel_info->Unload();
	delete m_pmodel_info;
	m_pmodel_info = NULL;
}

// ----------------------------------------
// load����
// ----------------------------------------
HRESULT CFloarTile::LoadTileNum(const char * filename)
{
	// �t�@�C���|�C���g
	FILE *pFile;

	// �ϐ��錾
	int	nCntObj = 0;		// ���f���J�E���g
	char cRaedText[128];	// �����Ƃ��ēǂݎ��p
	char cHeadText[128];	// ��r����悤
	char cDie[128];			// �s�K�v�ȕ���

							// �t�@�C���J
	pFile = fopen(filename, "r");

	// �J����
	if (pFile != NULL)
	{
		// �X�N���v�g������܂Ń��[�v
		while (strcmp(cHeadText, "SCRIPT") != 0)
		{
			fgets(cRaedText, sizeof(cRaedText), pFile);	// �ꕶ��ǂݍ���
			sscanf(cRaedText, "%s", &cHeadText);		// ��r�p�e�N�X�g�ɕ�������
		}

		// �X�N���v�g��������
		if (strcmp(cHeadText, "SCRIPT") == 0)
		{
			// �G���h�X�N���v�g������܂Ń��[�v
			while (strcmp(cHeadText, "END_SCRIPT") != 0)
			{
				// ������
				cHeadText[0] = '\0';
				fgets(cRaedText, sizeof(cRaedText), pFile);
				sscanf(cRaedText, "%s", &cHeadText);

				// �^�C�v���ǂݍ���
				if (strcmp(cHeadText, "TYPE") == 0)
				{
					sscanf(cRaedText, "%s %s %d", &cDie, &cDie,
						&m_aTileType[nCntObj]);

					// �z��̍X�V
					nCntObj++;
				}

			}
		}
		// �t�@�C����
		fclose(pFile);
	}

	// �J���Ȃ�
	else
	{
		MessageBox(NULL, "�I�u�W�F�N�g�ǂݍ��݂Ɏ��s���܂���", "�x���I", MB_ICONWARNING);
	}

	// �S�̂̑���
	return nCntObj;
}

// ----------------------------------------
// �ʒu�̐ݒ菈��
// ----------------------------------------
void CFloarTile::SetPos(D3DXVECTOR3 pos)
{
	CScene_X::SetPos(pos);
}

// ----------------------------------------
// ��]�̐ݒ菈��
// ----------------------------------------
void CFloarTile::SetRot(D3DXVECTOR3 rot)
{
	CScene_X::SetRot(rot);
}

// ----------------------------------------
// �ʒu�̎擾����
// ----------------------------------------
D3DXVECTOR3 CFloarTile::GetPos(void)
{
	return CScene_X::GetPos();
}