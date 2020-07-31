//=============================================================================
// ���f������ [Model.cpp]
//=============================================================================
#include "model.h"
#include "inputKeyboard.h"
#include "Player.h"
#include "scene.h"
#include "debugproc.h"
#include "collision.h"

CModel::MODEL CModel::m_Model[TYPE_MAX][MAX_ALLMODEL] = {};
char *CModel::m_PlayerFileName[MODEL_PLAYER_MAX] =
{
	{ "data/MODEL/character/Player/Waist.x" },
	{ "data/MODEL/character/Player/Body.x" },
	{ "data/MODEL/character/Player/Head.x"},
	{ "data/MODEL/character/Player/L_Sholder.x" },
	{ "data/MODEL/character/Player/R_Sholder.x" },
	{ "data/MODEL/character/Player/L_Arm.x" },
	{ "data/MODEL/character/Player/R_Arm.x" },
	{ "data/MODEL/character/Player/L_Hand.x" },
	{ "data/MODEL/character/Player/R_Hand.x" },
	{ "data/MODEL/character/Player/L_Knee.x" },
	{ "data/MODEL/character/Player/R_Knee.x" },
	{ "data/MODEL/character/Player/L_Foot.x" },
	{ "data/MODEL/character/Player/R_Foot.x" },
	{ "data/MODEL/character/Player/L_Leg.x" },
	{ "data/MODEL/character/Player/R_Leg.x" },
};

char *CModel::m_PrisonerFileName[MODEL_PRISONER_MAX] =
{
	{ "data/MODEL/Prisoner/Waist.x" },
	{ "data/MODEL/Prisoner/Body.x" },
	{ "data/MODEL/Prisoner/Head.x" },
	{ "data/MODEL/Prisoner/L_Sholder.x" },
	{ "data/MODEL/Prisoner/R_Sholder.x" },
	{ "data/MODEL/Prisoner/L_Arm.x" },
	{ "data/MODEL/Prisoner/R_Arm.x" },
	{ "data/MODEL/Prisoner/L_Hand.x" },
	{ "data/MODEL/Prisoner/R_Hand.x" },
	{ "data/MODEL/Prisoner/L_Knee.x" },
	{ "data/MODEL/Prisoner/R_Knee.x" },
	{ "data/MODEL/Prisoner/L_Foot.x" },
	{ "data/MODEL/Prisoner/R_Foot.x" },
	{ "data/MODEL/Prisoner/L_Leg.x" },
	{ "data/MODEL/Prisoner/R_Leg.x" },
};

char *CModel::m_MapFileName[MODEL_MAP_MAX] =
{
	{ "data/MODEL/map/Map1_Boss stage.x" },
	{ "data/MODEL/map/Stage1-1.x" },
	{ "data/MODEL/map/Stage1-2.x" },
	{ "data/MODEL/map/Stage1-3.x" },
	{ "data/MODEL/map/Map1_Boss stage.x" },
};
char *CModel::m_EnemyFileName[MODEL_ENEMY_MAX] =
{
	{ "data/MODEL/Enemy/Waist.x" },
	{ "data/MODEL/Enemy/Body.x" },
	{ "data/MODEL/Enemy/Head.x" },
	{ "data/MODEL/Enemy/L_Sholder.x" },
	{ "data/MODEL/Enemy/R_Sholder.x" },
	{ "data/MODEL/Enemy/L_Arm.x" },
	{ "data/MODEL/Enemy/R_Arm.x" },
	{ "data/MODEL/Enemy/L_Hand.x" },
	{ "data/MODEL/Enemy/R_Hand.x" },
	{ "data/MODEL/Enemy/L_Knee.x" },
	{ "data/MODEL/Enemy/R_Knee.x" },
	{ "data/MODEL/Enemy/L_Foot.x" },
	{ "data/MODEL/Enemy/R_Foot.x" },
	{ "data/MODEL/Enemy/L_Leg.x" },
	{ "data/MODEL/Enemy/R_Leg.x" },
};
char *CModel::m_GunFileName[MODEL_GUN_MAX] =
{
	{ "data/MODEL/Gun/Gun.x" },						// �n���h�K��
	{ "data/MODEL/Gun/Gun.x" },						// �w�r�[�}�V���K��
	{ "data/MODEL/Gun/Gun.x" },						// �V���b�g�K��
	{ "data/MODEL/Gun/Gun.x" },						// ���[�U�[�K��
	{ "data/MODEL/Gun/Gun.x" },						// ���P�b�g�����`���[
	{ "data/MODEL/Gun/Gun.x" },						// �t���C���V���b�g
	{ "data/MODEL/Gun/TankGun.x" },					// ��Ԃ̏e
	{ "data/MODEL/Gun/PlaneGun.x" },				// �퓬�@�̏e
	{ "data/MODEL/Gun/HeliGun.x" },					// �w���̏e
	{ "data/MODEL/Gun/Knife.x" },					// �i�C�t
};
char *CModel::m_BulletFileName[MODEL_BULLET_MAX] =
{
	{ "data/MODEL/Bullet/Sphere.x" },				// ��
	{ "data/MODEL/Bullet/Rocketlauncher.x" },		// ���P�b�g�����`���[
	{ "data/MODEL/Bullet/Grenade.x" },				// �O���l�[�h
};

char *CModel::m_TankFileName[MODEL_TANK_MAX] =
{
	{ "data/MODEL/Tank/Tankbody.x" },				// ��Ԃ̑�
	{ "data/MODEL/Tank/Tank_frontwheel.x" },		// ��Ԃ̑O�^�C��
	{ "data/MODEL/Tank/Tank_backwheel.x" },			// ��Ԃ̌�^�C��
	{ "data/MODEL/Tank/Tankgun.x" },				// ��Ԃ̏e
};

char *CModel::m_PlaneFileName[MODEL_PLANE_MAX] =
{
	{ "data/MODEL/BattlePlane/BattlePlane_Body.x" },// �퓬�@�̋@��
	{ "data/MODEL/BattlePlane/BattlePlane_Gun.x" },	// �퓬�@�̏e
};

char *CModel::m_HeliFileName[MODEL_HELI_MAX] =
{
	{ "data/MODEL/Helicopter/Helicopter_Body.x" },		// �w���R�v�^�[�̋@��
	{ "data/MODEL/Helicopter/Helicopter_Propeller.x" },	// �w���R�v�^�[�̃v���y��
	{ "data/MODEL/Helicopter/Helicopter_Gun.x" },		// �w���R�v�^�[�̏e
};


char *CModel::m_ObstacleFileName[OBSTACLE_TYPE_MAX] =
{
	{ "data/MODEL/Object/Obstacle_Box.x" },			// ��
	{ "data/MODEL/Object/Obstacle_Barrel.x" },		// �M
	{ "data/MODEL/Object/Obstacle_Tree.x" },		// ��
	{ "data/MODEL/Object/Obstacle_Chest.x" },		// ����
	{ "data/MODEL/Object/Obstacle_Sandbags.x" },	// �y�X
};

char *CModel::m_BossFileName[MODEL_BOSS_MAX] =
{
	{ "data/MODEL/Boss/SolodeRoca.x" },			// ��
};

CModel::CModel(OBJ_TYPE type) : CScene(type)
{
	m_pCollision = nullptr;							// �����蔻��̃|�C���^
}

CModel::~CModel()
{
	// �����蔻��̍폜
	if (m_pCollision != nullptr)
	{
		delete m_pCollision;
		m_pCollision = nullptr;
	}
}
//====================================================================
//���f���̃��[�h
//====================================================================
void CModel::LoadModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATERIAL *pMat;

	//�v���C���[�̃��f���ǂݍ���
	for (int nCnt = 0; nCnt < MODEL_PLAYER_MAX; nCnt++)
	{
		// X�t�@�C���̓ǂݍ���
		if (FAILED(D3DXLoadMeshFromX(
			m_PlayerFileName[nCnt],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_Model[PLAYER_MODEL][nCnt].pBuffmat,
			NULL,
			&m_Model[PLAYER_MODEL][nCnt].nNumMat,
			&m_Model[PLAYER_MODEL][nCnt].pMesh
		)))
		{
			//�ۑ�����
			std::cout << "LoadFailed!! >>" << m_PlayerFileName[nCnt] << NEWLINE;
		}
		else
		{
			m_Model[PLAYER_MODEL][nCnt].m_pTexture = new LPDIRECT3DTEXTURE9[(int)m_Model[PLAYER_MODEL][nCnt].nNumMat];
			pMat = (D3DXMATERIAL*)m_Model[PLAYER_MODEL][nCnt].pBuffmat->GetBufferPointer();
			for (int nCntmat = 0; nCntmat < (int)m_Model[PLAYER_MODEL][nCnt].nNumMat; nCntmat++)
			{
				m_Model[PLAYER_MODEL][nCnt].m_pTexture[nCntmat] = NULL;
				D3DXCreateTextureFromFile(pDevice, pMat[nCntmat].pTextureFilename, &m_Model[PLAYER_MODEL][nCnt].m_pTexture[nCntmat]);
			}
		}

		//�ۑ�����
		std::cout << "PlayerModelLoad >>" << m_PlayerFileName[nCnt] << NEWLINE;

	}

	//�}�b�v�̃��f���ǂݍ���
	for (int nCnt = 0; nCnt < MODEL_MAP_MAX; nCnt++)
	{
		// X�t�@�C���̓ǂݍ���
		if (FAILED(D3DXLoadMeshFromX(
			m_MapFileName[nCnt],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_Model[MAP_MODEL][nCnt].pBuffmat,
			NULL,
			&m_Model[MAP_MODEL][nCnt].nNumMat,
			&m_Model[MAP_MODEL][nCnt].pMesh
		)))
		{
			//�ۑ�����
			std::cout << "LoadFailed!! >>" << m_PlayerFileName[nCnt] << NEWLINE;
		}
		else
		{
			m_Model[MAP_MODEL][nCnt].vtxMin = D3DXVECTOR3(1000, 1000, 1000);
			m_Model[MAP_MODEL][nCnt].vtxMax = D3DXVECTOR3(-1000, -1000, -1000);
			//�e�N�X�`���̃������m��
			m_Model[MAP_MODEL][nCnt].m_pTexture = new LPDIRECT3DTEXTURE9[(int)m_Model[MAP_MODEL][nCnt].nNumMat];
			pMat = (D3DXMATERIAL*)m_Model[MAP_MODEL][nCnt].pBuffmat->GetBufferPointer();

			//�e�N�X�`���}�e���A�����̊i�[
			for (int nCntmat = 0; nCntmat < (int)m_Model[MAP_MODEL][nCnt].nNumMat; nCntmat++)
			{
				m_Model[MAP_MODEL][nCnt].m_pTexture[nCntmat] = NULL;
				D3DXCreateTextureFromFile(pDevice, pMat[nCntmat].pTextureFilename, &m_Model[MAP_MODEL][nCnt].m_pTexture[nCntmat]);
			}

			std::cout << "MapModelLoad >>" << m_MapFileName[nCnt] << NEWLINE;
		}

	}
	//�G�l�~�[�̃��f���ǂݍ���
	for (int nCnt = 0; nCnt < MODEL_ENEMY_MAX; nCnt++)
	{
		// X�t�@�C���̓ǂݍ���
		if (FAILED(D3DXLoadMeshFromX(
			m_EnemyFileName[nCnt],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_Model[ENEMY_MODEL][nCnt].pBuffmat,
			NULL,
			&m_Model[ENEMY_MODEL][nCnt].nNumMat,
			&m_Model[ENEMY_MODEL][nCnt].pMesh
		)))
		{
			//�ۑ�����
			std::cout << "LoadFailed!! >>" << m_PlayerFileName[nCnt] << NEWLINE;
		}
		else
		{
				//�e�N�X�`���̃������m��
				m_Model[ENEMY_MODEL][nCnt].m_pTexture = new LPDIRECT3DTEXTURE9[(int)m_Model[ENEMY_MODEL][nCnt].nNumMat];
			pMat = (D3DXMATERIAL*)m_Model[ENEMY_MODEL][nCnt].pBuffmat->GetBufferPointer();

			for (int nCntmat = 0; nCntmat < (int)m_Model[ENEMY_MODEL][nCnt].nNumMat; nCntmat++)
			{
				m_Model[ENEMY_MODEL][nCnt].m_pTexture[nCntmat] = NULL;
				D3DXCreateTextureFromFile(pDevice, pMat[nCntmat].pTextureFilename, &m_Model[ENEMY_MODEL][nCnt].m_pTexture[nCntmat]);
			}

			std::cout << "EnemyLoad >>" << m_EnemyFileName[nCnt] << NEWLINE;
		}
	}

	//�ߗ��̃��f���ǂݍ���
	for (int nCnt = 0; nCnt < MODEL_PRISONER_MAX; nCnt++)
	{
		// X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(
			m_PrisonerFileName[nCnt],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_Model[PRISONER_MODEL][nCnt].pBuffmat,
			NULL,
			&m_Model[PRISONER_MODEL][nCnt].nNumMat,
			&m_Model[PRISONER_MODEL][nCnt].pMesh
		);
		//�e�N�X�`���̃������m��
		m_Model[PRISONER_MODEL][nCnt].m_pTexture = new LPDIRECT3DTEXTURE9[(int)m_Model[PRISONER_MODEL][nCnt].nNumMat];
		pMat = (D3DXMATERIAL*)m_Model[PRISONER_MODEL][nCnt].pBuffmat->GetBufferPointer();

		for (int nCntmat = 0; nCntmat < (int)m_Model[PRISONER_MODEL][nCnt].nNumMat; nCntmat++)
		{
			m_Model[PRISONER_MODEL][nCnt].m_pTexture[nCntmat] = NULL;
			D3DXCreateTextureFromFile(pDevice, pMat[nCntmat].pTextureFilename, &m_Model[PRISONER_MODEL][nCnt].m_pTexture[nCntmat]);
		}

		std::cout << "PrisonerLoad >>" << m_PrisonerFileName[nCnt] << NEWLINE;

	}
	//�e�̃��f���ǂݍ���
	for (int nCnt = 0; nCnt < MODEL_GUN_MAX; nCnt++)
	{
		// X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(
			m_GunFileName[nCnt],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_Model[GUN_MODEL][nCnt].pBuffmat,
			NULL,
			&m_Model[GUN_MODEL][nCnt].nNumMat,
			&m_Model[GUN_MODEL][nCnt].pMesh
		);
		//�e�N�X�`���̃������m��
		m_Model[GUN_MODEL][nCnt].m_pTexture = new LPDIRECT3DTEXTURE9[(int)m_Model[GUN_MODEL][nCnt].nNumMat];
		pMat = (D3DXMATERIAL*)m_Model[GUN_MODEL][nCnt].pBuffmat->GetBufferPointer();

		for (int nCntmat = 0; nCntmat < (int)m_Model[GUN_MODEL][nCnt].nNumMat; nCntmat++)
		{
			m_Model[GUN_MODEL][nCnt].m_pTexture[nCntmat] = NULL;
			D3DXCreateTextureFromFile(pDevice, pMat[nCntmat].pTextureFilename, &m_Model[GUN_MODEL][nCnt].m_pTexture[nCntmat]);
		}

		std::cout << "GunModelLoad >>" << m_GunFileName[nCnt] << NEWLINE;

	}
	//�e�̃��f���ǂݍ���
	for (int nCnt = 0; nCnt < MODEL_BULLET_MAX; nCnt++)
	{
		// X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(
			m_BulletFileName[nCnt],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_Model[BULLET_MODEL][nCnt].pBuffmat,
			NULL,
			&m_Model[BULLET_MODEL][nCnt].nNumMat,
			&m_Model[BULLET_MODEL][nCnt].pMesh
		);
		//�e�N�X�`���̃������m��
		m_Model[BULLET_MODEL][nCnt].m_pTexture = new LPDIRECT3DTEXTURE9[(int)m_Model[BULLET_MODEL][nCnt].nNumMat];
		pMat = (D3DXMATERIAL*)m_Model[BULLET_MODEL][nCnt].pBuffmat->GetBufferPointer();

		for (int nCntmat = 0; nCntmat < (int)m_Model[BULLET_MODEL][nCnt].nNumMat; nCntmat++)
		{
			m_Model[BULLET_MODEL][nCnt].m_pTexture[nCntmat] = NULL;
			D3DXCreateTextureFromFile(pDevice, pMat[nCntmat].pTextureFilename, &m_Model[BULLET_MODEL][nCnt].m_pTexture[nCntmat]);
		}
	}

	//��Q�����̃��f���ǂݍ���
	for (int nCnt = 0; nCnt < OBSTACLE_TYPE_MAX; nCnt++)
	{
		// X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(
			m_ObstacleFileName[nCnt],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_Model[OBSTACLE_MODEL][nCnt].pBuffmat,
			NULL,
			&m_Model[OBSTACLE_MODEL][nCnt].nNumMat,
			&m_Model[OBSTACLE_MODEL][nCnt].pMesh
		);
		//�e�N�X�`���̃������m��
		m_Model[OBSTACLE_MODEL][nCnt].m_pTexture = new LPDIRECT3DTEXTURE9[(int)m_Model[OBSTACLE_MODEL][nCnt].nNumMat];
		pMat = (D3DXMATERIAL*)m_Model[OBSTACLE_MODEL][nCnt].pBuffmat->GetBufferPointer();

		for (int nCntmat = 0; nCntmat < (int)m_Model[OBSTACLE_MODEL][nCnt].nNumMat; nCntmat++)
		{
			m_Model[OBSTACLE_MODEL][nCnt].m_pTexture[nCntmat] = NULL;
			D3DXCreateTextureFromFile(pDevice, pMat[nCntmat].pTextureFilename, &m_Model[OBSTACLE_MODEL][nCnt].m_pTexture[nCntmat]);
		}

		std::cout << "OBSTACLE Load >>" << m_ObstacleFileName[nCnt] << NEWLINE;

	}
	//��Ԃ̃��f���ǂݍ���
	for (int nCnt = 0; nCnt < MODEL_TANK_MAX; nCnt++)
	{
		// X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(
			m_TankFileName[nCnt],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_Model[TANK_MODEL][nCnt].pBuffmat,
			NULL,
			&m_Model[TANK_MODEL][nCnt].nNumMat,
			&m_Model[TANK_MODEL][nCnt].pMesh
		);
		//�e�N�X�`���̃������m��
		m_Model[TANK_MODEL][nCnt].m_pTexture = new LPDIRECT3DTEXTURE9[(int)m_Model[TANK_MODEL][nCnt].nNumMat];
		pMat = (D3DXMATERIAL*)m_Model[TANK_MODEL][nCnt].pBuffmat->GetBufferPointer();

		for (int nCntmat = 0; nCntmat < (int)m_Model[TANK_MODEL][nCnt].nNumMat; nCntmat++)
		{
			m_Model[TANK_MODEL][nCnt].m_pTexture[nCntmat] = NULL;
			D3DXCreateTextureFromFile(pDevice, pMat[nCntmat].pTextureFilename, &m_Model[TANK_MODEL][nCnt].m_pTexture[nCntmat]);
		}

		std::cout << "TANKMODEL Load >>" << m_TankFileName[nCnt] << NEWLINE;

	}

	//�퓬�@�̃��f���ǂݍ���
	for (int nCnt = 0; nCnt < MODEL_PLANE_MAX; nCnt++)
	{
		// X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(
			m_PlaneFileName[nCnt],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_Model[PLANE_MODEL][nCnt].pBuffmat,
			NULL,
			&m_Model[PLANE_MODEL][nCnt].nNumMat,
			&m_Model[PLANE_MODEL][nCnt].pMesh
		);
		//�e�N�X�`���̃������m��
		m_Model[PLANE_MODEL][nCnt].m_pTexture = new LPDIRECT3DTEXTURE9[(int)m_Model[PLANE_MODEL][nCnt].nNumMat];
		pMat = (D3DXMATERIAL*)m_Model[PLANE_MODEL][nCnt].pBuffmat->GetBufferPointer();

		for (int nCntmat = 0; nCntmat < (int)m_Model[PLANE_MODEL][nCnt].nNumMat; nCntmat++)
		{
			m_Model[PLANE_MODEL][nCnt].m_pTexture[nCntmat] = NULL;
			D3DXCreateTextureFromFile(pDevice, pMat[nCntmat].pTextureFilename, &m_Model[PLANE_MODEL][nCnt].m_pTexture[nCntmat]);
		}

		std::cout << "PLANEMODEL Load >>" << m_PlaneFileName[nCnt] << NEWLINE;
	}

	// �w���̃��f���ǂݍ���
	for (int nCnt = 0; nCnt < MODEL_HELI_MAX; nCnt++)
	{
		// X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(
			m_HeliFileName[nCnt],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_Model[HELI_MODEL][nCnt].pBuffmat,
			NULL,
			&m_Model[HELI_MODEL][nCnt].nNumMat,
			&m_Model[HELI_MODEL][nCnt].pMesh
		);
		//�e�N�X�`���̃������m��
		m_Model[HELI_MODEL][nCnt].m_pTexture = new LPDIRECT3DTEXTURE9[(int)m_Model[HELI_MODEL][nCnt].nNumMat];
		pMat = (D3DXMATERIAL*)m_Model[HELI_MODEL][nCnt].pBuffmat->GetBufferPointer();

		for (int nCntmat = 0; nCntmat < (int)m_Model[HELI_MODEL][nCnt].nNumMat; nCntmat++)
		{
			m_Model[HELI_MODEL][nCnt].m_pTexture[nCntmat] = NULL;
			D3DXCreateTextureFromFile(pDevice, pMat[nCntmat].pTextureFilename, &m_Model[HELI_MODEL][nCnt].m_pTexture[nCntmat]);
		}

		std::cout << "HELIMODEL Load >>" << m_HeliFileName[nCnt] << NEWLINE;
	}
	// �{�X�̃��f���ǂݍ���
	for (int nCnt = 0; nCnt < MODEL_BOSS_MAX; nCnt++)
	{
		// X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(
			m_BossFileName[nCnt],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_Model[BOSS_MODEL][nCnt].pBuffmat,
			NULL,
			&m_Model[BOSS_MODEL][nCnt].nNumMat,
			&m_Model[BOSS_MODEL][nCnt].pMesh
		);
		//�e�N�X�`���̃������m��
		m_Model[BOSS_MODEL][nCnt].m_pTexture = new LPDIRECT3DTEXTURE9[(int)m_Model[BOSS_MODEL][nCnt].nNumMat];
		pMat = (D3DXMATERIAL*)m_Model[BOSS_MODEL][nCnt].pBuffmat->GetBufferPointer();

		for (int nCntmat = 0; nCntmat < (int)m_Model[BOSS_MODEL][nCnt].nNumMat; nCntmat++)
		{
			m_Model[BOSS_MODEL][nCnt].m_pTexture[nCntmat] = NULL;
			D3DXCreateTextureFromFile(pDevice, pMat[nCntmat].pTextureFilename, &m_Model[BOSS_MODEL][nCnt].m_pTexture[nCntmat]);
		}

		std::cout << "BOSSMODEL Load >>" << m_BossFileName[nCnt] << NEWLINE;
	}

}
//====================================================================
//���f���̊J��
//====================================================================
void CModel::UnLoad(void)
{
	for (int nCnt = 0; nCnt < MODEL_PLAYER_MAX; nCnt++)
	{
		if (m_Model[PLAYER_MODEL][nCnt].pBuffmat != NULL)
		{
			m_Model[PLAYER_MODEL][nCnt].pBuffmat->Release();
			m_Model[PLAYER_MODEL][nCnt].pBuffmat = NULL;
		}
		if (m_Model[PLAYER_MODEL][nCnt].pMesh != NULL)
		{
			m_Model[PLAYER_MODEL][nCnt].pMesh->Release();
			m_Model[PLAYER_MODEL][nCnt].pMesh = NULL;
		}
		if (m_Model[PLAYER_MODEL][nCnt].m_pTexture != NULL)
		{
			for (int nCntmat = 0; nCntmat < (int)m_Model[PLAYER_MODEL][nCnt].nNumMat; nCntmat++)
			{
				if (m_Model[PLAYER_MODEL][nCnt].m_pTexture[nCntmat] != NULL)
				{
					m_Model[PLAYER_MODEL][nCnt].m_pTexture[nCntmat]->Release();
					m_Model[PLAYER_MODEL][nCnt].m_pTexture[nCntmat] = NULL;
				}
			}
			delete[] m_Model[PLAYER_MODEL][nCnt].m_pTexture;
			m_Model[PLAYER_MODEL][nCnt].m_pTexture = NULL;
		}
	}
	//�}�b�v�̃��f���ǂݍ���
	for (int nCnt = 0; nCnt < MODEL_MAP_MAX; nCnt++)
	{
		if (m_Model[MAP_MODEL][nCnt].pBuffmat != NULL)
		{
			m_Model[MAP_MODEL][nCnt].pBuffmat->Release();
			m_Model[MAP_MODEL][nCnt].pBuffmat = NULL;
		}
		if (m_Model[MAP_MODEL][nCnt].pMesh != NULL)
		{
			m_Model[MAP_MODEL][nCnt].pMesh->Release();
			m_Model[MAP_MODEL][nCnt].pMesh = NULL;
		}
		if (m_Model[MAP_MODEL][nCnt].m_pTexture != NULL)
		{
			for (int nCntmat = 0; nCntmat < (int)m_Model[MAP_MODEL][nCnt].nNumMat; nCntmat++)
			{
				if (m_Model[MAP_MODEL][nCnt].m_pTexture[nCntmat] != NULL)
				{
					m_Model[MAP_MODEL][nCnt].m_pTexture[nCntmat]->Release();
					m_Model[MAP_MODEL][nCnt].m_pTexture[nCntmat] = NULL;
				}
			}
			delete[] m_Model[MAP_MODEL][nCnt].m_pTexture;
			m_Model[MAP_MODEL][nCnt].m_pTexture = NULL;
		}
	}
	for (int nCnt = 0; nCnt < MODEL_ENEMY_MAX; nCnt++)
	{
		if (m_Model[ENEMY_MODEL][nCnt].pBuffmat != NULL)
		{
			m_Model[ENEMY_MODEL][nCnt].pBuffmat->Release();
			m_Model[ENEMY_MODEL][nCnt].pBuffmat = NULL;
		}
		if (m_Model[ENEMY_MODEL][nCnt].pMesh != NULL)
		{
			m_Model[ENEMY_MODEL][nCnt].pMesh->Release();
			m_Model[ENEMY_MODEL][nCnt].pMesh = NULL;
		}
		if (m_Model[ENEMY_MODEL][nCnt].m_pTexture != NULL)
		{
			for (int nCntmat = 0; nCntmat < (int)m_Model[ENEMY_MODEL][nCnt].nNumMat; nCntmat++)
			{
				if (m_Model[ENEMY_MODEL][nCnt].m_pTexture[nCntmat] != NULL)
				{
					m_Model[ENEMY_MODEL][nCnt].m_pTexture[nCntmat]->Release();
					m_Model[ENEMY_MODEL][nCnt].m_pTexture[nCntmat] = NULL;
				}
			}
			delete[] m_Model[ENEMY_MODEL][nCnt].m_pTexture;
			m_Model[ENEMY_MODEL][nCnt].m_pTexture = NULL;
		}
	}
	for (int nCnt = 0; nCnt < MODEL_PRISONER_MAX; nCnt++)
	{
		if (m_Model[PRISONER_MODEL][nCnt].pBuffmat != NULL)
		{
			m_Model[PRISONER_MODEL][nCnt].pBuffmat->Release();
			m_Model[PRISONER_MODEL][nCnt].pBuffmat = NULL;
		}
		if (m_Model[PRISONER_MODEL][nCnt].pMesh != NULL)
		{
			m_Model[PRISONER_MODEL][nCnt].pMesh->Release();
			m_Model[PRISONER_MODEL][nCnt].pMesh = NULL;
		}
		if (m_Model[PRISONER_MODEL][nCnt].m_pTexture != NULL)
		{
			for (int nCntmat = 0; nCntmat < (int)m_Model[PRISONER_MODEL][nCnt].nNumMat; nCntmat++)
			{
				if (m_Model[PRISONER_MODEL][nCnt].m_pTexture[nCntmat] != NULL)
				{
					m_Model[PRISONER_MODEL][nCnt].m_pTexture[nCntmat]->Release();
					m_Model[PRISONER_MODEL][nCnt].m_pTexture[nCntmat] = NULL;
				}
			}
			delete[] m_Model[PRISONER_MODEL][nCnt].m_pTexture;
			m_Model[PRISONER_MODEL][nCnt].m_pTexture = NULL;
		}
	}
	// �e�̃��f��
	for (int nCnt = 0; nCnt < MODEL_GUN_MAX; nCnt++)
	{
		if (m_Model[GUN_MODEL][nCnt].pBuffmat != NULL)
		{
			m_Model[GUN_MODEL][nCnt].pBuffmat->Release();
			m_Model[GUN_MODEL][nCnt].pBuffmat = NULL;
		}
		if (m_Model[GUN_MODEL][nCnt].pMesh != NULL)
		{
			m_Model[GUN_MODEL][nCnt].pMesh->Release();
			m_Model[GUN_MODEL][nCnt].pMesh = NULL;
		}
		if (m_Model[GUN_MODEL][nCnt].m_pTexture != NULL)
		{
			for (int nCntmat = 0; nCntmat < (int)m_Model[GUN_MODEL][nCnt].nNumMat; nCntmat++)
			{
				if (m_Model[GUN_MODEL][nCnt].m_pTexture[nCntmat] != NULL)
				{
					m_Model[GUN_MODEL][nCnt].m_pTexture[nCntmat]->Release();
					m_Model[GUN_MODEL][nCnt].m_pTexture[nCntmat] = NULL;
				}
			}
			delete[] m_Model[GUN_MODEL][nCnt].m_pTexture;
			m_Model[GUN_MODEL][nCnt].m_pTexture = NULL;
		}
	}
	// �e�̃��f��
	for (int nCnt = 0; nCnt < MODEL_BULLET_MAX; nCnt++)
	{
		if (m_Model[BULLET_MODEL][nCnt].pBuffmat != NULL)
		{
			m_Model[BULLET_MODEL][nCnt].pBuffmat->Release();
			m_Model[BULLET_MODEL][nCnt].pBuffmat = NULL;
		}
		if (m_Model[BULLET_MODEL][nCnt].pMesh != NULL)
		{
			m_Model[BULLET_MODEL][nCnt].pMesh->Release();
			m_Model[BULLET_MODEL][nCnt].pMesh = NULL;
		}
		if (m_Model[BULLET_MODEL][nCnt].m_pTexture != NULL)
		{
			for (int nCntmat = 0; nCntmat < (int)m_Model[BULLET_MODEL][nCnt].nNumMat; nCntmat++)
			{
				if (m_Model[BULLET_MODEL][nCnt].m_pTexture[nCntmat] != NULL)
				{
					m_Model[BULLET_MODEL][nCnt].m_pTexture[nCntmat]->Release();
					m_Model[BULLET_MODEL][nCnt].m_pTexture[nCntmat] = NULL;
				}
			}
			delete[] m_Model[BULLET_MODEL][nCnt].m_pTexture;
			m_Model[BULLET_MODEL][nCnt].m_pTexture = NULL;
		}
	}

	for (int nCnt = 0; nCnt < OBSTACLE_TYPE_MAX; nCnt++)
	{
		if (m_Model[OBSTACLE_MODEL][nCnt].pBuffmat != NULL)
		{
			m_Model[OBSTACLE_MODEL][nCnt].pBuffmat->Release();
			m_Model[OBSTACLE_MODEL][nCnt].pBuffmat = NULL;
		}
		if (m_Model[OBSTACLE_MODEL][nCnt].pMesh != NULL)
		{
			m_Model[OBSTACLE_MODEL][nCnt].pMesh->Release();
			m_Model[OBSTACLE_MODEL][nCnt].pMesh = NULL;
		}
		if (m_Model[OBSTACLE_MODEL][nCnt].m_pTexture != NULL)
		{
			for (int nCntmat = 0; nCntmat < (int)m_Model[OBSTACLE_MODEL][nCnt].nNumMat; nCntmat++)
			{
				if (m_Model[OBSTACLE_MODEL][nCnt].m_pTexture[nCntmat] != NULL)
				{
					m_Model[OBSTACLE_MODEL][nCnt].m_pTexture[nCntmat]->Release();
					m_Model[OBSTACLE_MODEL][nCnt].m_pTexture[nCntmat] = NULL;
				}
			}
			delete[] m_Model[OBSTACLE_MODEL][nCnt].m_pTexture;
			m_Model[OBSTACLE_MODEL][nCnt].m_pTexture = NULL;
		}
	}
	//�^���N
	for (int nCnt = 0; nCnt < MODEL_TANK_MAX; nCnt++)
	{
		if (m_Model[TANK_MODEL][nCnt].pBuffmat != NULL)
		{
			m_Model[TANK_MODEL][nCnt].pBuffmat->Release();
			m_Model[TANK_MODEL][nCnt].pBuffmat = NULL;
		}
		if (m_Model[TANK_MODEL][nCnt].pMesh != NULL)
		{
			m_Model[TANK_MODEL][nCnt].pMesh->Release();
			m_Model[TANK_MODEL][nCnt].pMesh = NULL;
		}
		if (m_Model[TANK_MODEL][nCnt].m_pTexture != NULL)
		{
			for (int nCntmat = 0; nCntmat < (int)m_Model[TANK_MODEL][nCnt].nNumMat; nCntmat++)
			{
				if (m_Model[TANK_MODEL][nCnt].m_pTexture[nCntmat] != NULL)
				{
					m_Model[TANK_MODEL][nCnt].m_pTexture[nCntmat]->Release();
					m_Model[TANK_MODEL][nCnt].m_pTexture[nCntmat] = NULL;
				}
			}
			delete[] m_Model[TANK_MODEL][nCnt].m_pTexture;
			m_Model[TANK_MODEL][nCnt].m_pTexture = NULL;
		}
	}

	// �퓬�@
	for (int nCnt = 0; nCnt < MODEL_PLANE_MAX; nCnt++)
	{
		if (m_Model[PLANE_MODEL][nCnt].pBuffmat != NULL)
		{
			m_Model[PLANE_MODEL][nCnt].pBuffmat->Release();
			m_Model[PLANE_MODEL][nCnt].pBuffmat = NULL;
		}
		if (m_Model[PLANE_MODEL][nCnt].pMesh != NULL)
		{
			m_Model[PLANE_MODEL][nCnt].pMesh->Release();
			m_Model[PLANE_MODEL][nCnt].pMesh = NULL;
		}
		if (m_Model[PLANE_MODEL][nCnt].m_pTexture != NULL)
		{
			for (int nCntmat = 0; nCntmat < (int)m_Model[PLANE_MODEL][nCnt].nNumMat; nCntmat++)
			{
				if (m_Model[PLANE_MODEL][nCnt].m_pTexture[nCntmat] != NULL)
				{
					m_Model[PLANE_MODEL][nCnt].m_pTexture[nCntmat]->Release();
					m_Model[PLANE_MODEL][nCnt].m_pTexture[nCntmat] = NULL;
				}
			}
			delete[] m_Model[PLANE_MODEL][nCnt].m_pTexture;
			m_Model[PLANE_MODEL][nCnt].m_pTexture = NULL;
		}
	}

	// �w���R�v�^�[
	for (int nCnt = 0; nCnt < MODEL_HELI_MAX; nCnt++)
	{
		if (m_Model[HELI_MODEL][nCnt].pBuffmat != NULL)
		{
			m_Model[HELI_MODEL][nCnt].pBuffmat->Release();
			m_Model[HELI_MODEL][nCnt].pBuffmat = NULL;
		}
		if (m_Model[HELI_MODEL][nCnt].pMesh != NULL)
		{
			m_Model[HELI_MODEL][nCnt].pMesh->Release();
			m_Model[HELI_MODEL][nCnt].pMesh = NULL;
		}
		if (m_Model[HELI_MODEL][nCnt].m_pTexture != NULL)
		{
			for (int nCntmat = 0; nCntmat < (int)m_Model[HELI_MODEL][nCnt].nNumMat; nCntmat++)
			{
				if (m_Model[HELI_MODEL][nCnt].m_pTexture[nCntmat] != NULL)
				{
					m_Model[HELI_MODEL][nCnt].m_pTexture[nCntmat]->Release();
					m_Model[HELI_MODEL][nCnt].m_pTexture[nCntmat] = NULL;
				}
			}
			delete[] m_Model[HELI_MODEL][nCnt].m_pTexture;
			m_Model[HELI_MODEL][nCnt].m_pTexture = NULL;
		}
	}
	// �{�X
	for (int nCnt = 0; nCnt < MODEL_BOSS_MAX; nCnt++)
	{
		if (m_Model[BOSS_MODEL][nCnt].pBuffmat != NULL)
		{
			m_Model[BOSS_MODEL][nCnt].pBuffmat->Release();
			m_Model[BOSS_MODEL][nCnt].pBuffmat = NULL;
		}
		if (m_Model[BOSS_MODEL][nCnt].pMesh != NULL)
		{
			m_Model[BOSS_MODEL][nCnt].pMesh->Release();
			m_Model[BOSS_MODEL][nCnt].pMesh = NULL;
		}
		if (m_Model[BOSS_MODEL][nCnt].m_pTexture != NULL)
		{
			for (int nCntmat = 0; nCntmat < (int)m_Model[BOSS_MODEL][nCnt].nNumMat; nCntmat++)
			{
				if (m_Model[BOSS_MODEL][nCnt].m_pTexture[nCntmat] != NULL)
				{
					m_Model[BOSS_MODEL][nCnt].m_pTexture[nCntmat]->Release();
					m_Model[BOSS_MODEL][nCnt].m_pTexture[nCntmat] = NULL;
				}
			}
			delete[] m_Model[BOSS_MODEL][nCnt].m_pTexture;
			m_Model[BOSS_MODEL][nCnt].m_pTexture = NULL;
		}
	}

}
//====================================================================
//������
//====================================================================
HRESULT CModel::Init(void)
{
	m_pos				= D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ʒu
	m_move				= D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړ���
	m_rot				= D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ��]
	m_col				= D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	// �J���[
	m_AddColor			= D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	// ���Z����F
	m_bDieFlag			= false;								// ���S�t���O
	m_bColorChangeFlag	= false;									// �F�ύX�t���O
	m_type				= 0;									// ���
	int nNumVertices;
	DWORD sizeFVF;
	BYTE *pVertexBuffer;
															// �����蔻�萶��
	m_pCollision = CCollision::Create();

	for (int nCnt = 0; nCnt < MODEL_MAP_MAX; nCnt++)
	{
		if (m_Model[MAP_MODEL][nCnt].pMesh != NULL)
		{
			//���_�����擾
			nNumVertices = m_Model[MAP_MODEL][nCnt].pMesh->GetNumVertices();
			//���_�t�H�[�}�b�g�̃T�C�Y���擾
			sizeFVF = D3DXGetFVFVertexSize(m_Model[MAP_MODEL][nCnt].pMesh->GetFVF());
			//���_�o�b�t�@�����b�N
			m_Model[MAP_MODEL][nCnt].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVertexBuffer);
			for (int nCntVtx = 0; nCntVtx < nNumVertices; nCntVtx++)
			{
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVertexBuffer;
				//���ׂĂ̒��_�����r���čŏ��A�ő�𔲂��o��
				if (m_Model[MAP_MODEL][nCnt].vtxMin.x > vtx.x)
				{
					m_Model[MAP_MODEL][nCnt].vtxMin.x = vtx.x;
				}
				if (m_Model[MAP_MODEL][nCnt].vtxMin.y > vtx.y)
				{
					m_Model[MAP_MODEL][nCnt].vtxMin.y = vtx.y;
				}
				if (m_Model[MAP_MODEL][nCnt].vtxMin.z > vtx.z)
				{
					m_Model[MAP_MODEL][nCnt].vtxMin.z = vtx.z;
				}
				if (m_Model[MAP_MODEL][nCnt].vtxMax.x < vtx.x)
				{
					m_Model[MAP_MODEL][nCnt].vtxMax.x = vtx.x;
				}
				if (m_Model[MAP_MODEL][nCnt].vtxMax.y < vtx.y)
				{
					m_Model[MAP_MODEL][nCnt].vtxMax.y = vtx.y;
				}
				if (m_Model[MAP_MODEL][nCnt].vtxMax.z < vtx.z)
				{
					m_Model[MAP_MODEL][nCnt].vtxMax.z = vtx.z;
				}
				pVertexBuffer += sizeFVF; // �T�C�Y���|�C���^��i�߂�
			}
			//���_�o�b�t�@���A�����b�N
			m_Model[MAP_MODEL][nCnt].pMesh->UnlockVertexBuffer();
		}
	}
	return S_OK;
}
//====================================================================
//�I��
//====================================================================
void CModel::Uninit(void)
{
}
//====================================================================
//�X�V
//====================================================================
void CModel::Update(void)
{
}
//====================================================================
//�`��
//====================================================================
void CModel::Draw(D3DXMATRIX mat)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �}�g���b�N�X�̌v�Z
	CHossoLibrary::CalcMatrix(&m_mtxWorld, m_pos, m_rot);

	// �|���S���̕`��
	pDevice->SetTexture(0, NULL);

	//�e�q�֌W
	if (m_pParent== NULL)
	{
		D3DXMatrixMultiply(&m_mtxWorld,
			&m_mtxWorld,
			&mat);
	}
	else
	{
		D3DXMatrixMultiply(&m_mtxWorld,
			&m_mtxWorld,
			&m_pParent->m_mtxWorld);
	}

	// �`��
	DrawMesh();
}
//====================================================================
//�`��
//====================================================================
void CModel::Draw()
{
	// �}�g���b�N�X�̌v�Z
	CHossoLibrary::CalcMatrix(&m_mtxWorld, m_pos, m_rot);

	// �`��
	DrawMesh();
}
//====================================================================
//�f�o�b�O
//====================================================================
void CModel::DebugInfo()
{
}
//====================================================================
//���f���̃N���G�C�g
//====================================================================
CModel *CModel::Create(int type, int modelCount)
{
	CModel*pModel;
	pModel = new CModel(TYPE_NONE);
	pModel->Init();
	pModel->m_type = type;
	pModel->m_modelCount = modelCount;
	return pModel;
}
//====================================================================
//���f���̃N���G�C�g(�V�[���ŊǗ�����)
//====================================================================
CModel * CModel::CreateSceneManagement(int type, int modelCount)
{
	CModel*pModel;
	pModel = new CModel(OBJTYPE_MODEL);
	pModel->Init();
	pModel->m_type = type;
	pModel->m_modelCount = modelCount;
	return pModel;
}
//====================================================================
//���f���̃t�@�C�����擾
//====================================================================
char * CModel::GetModelFileName(int nType, int nModelCount)
{
	//�^�C�v�œǂݍ��ޔz���ς���
	switch (nType)
	{
		//�v���C���[
	case PLAYER_MODEL:
		return m_PlayerFileName[nModelCount];
		break;
		//�G
	case ENEMY_MODEL:
		return m_EnemyFileName[nModelCount];
		break;
		//�}�b�v
	case MAP_MODEL:
		return m_MapFileName[nModelCount];
		break;
		//��Q��
	case OBSTACLE_MODEL:
		return m_ObstacleFileName[nModelCount];
		break;
		//�ߗ�
	case PRISONER_MODEL:
		return m_PrisonerFileName[nModelCount];
		break;
		//���
	case TANK_MODEL:
		return m_TankFileName[nModelCount];
		break;
		//���
	case PLANE_MODEL:
		return m_PlaneFileName[nModelCount];
		break;
		//�w��
	case HELI_MODEL:
		return m_HeliFileName[nModelCount];
		break;
		//�{�X
	case BOSS_MODEL:
		return m_BossFileName[nModelCount];
		break;
	}
	return nullptr;
}

//====================================================================
 //�}�g���b�N�X�v�Z
 //====================================================================
void CModel::NotDrawCalcMtxOnly(D3DXMATRIX * pParentMtx)
{
	// �}�g���b�N�X�̌v�Z
	CHossoLibrary::CalcMatrix(&m_mtxWorld, m_pos, m_rot);

	//�e�}�g���b�N�X�̌v�Z
	D3DXMatrixMultiply(&m_mtxWorld,
		&m_mtxWorld,
		pParentMtx);
}
//====================================================================
//�`��
//====================================================================
void CModel::DrawMesh()
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATERIAL *pMat;

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// �}�e���A�����ɑ΂���|�C���^���擾
	if (m_Model[m_type][m_modelCount].pBuffmat != NULL)
	{
		pMat = (D3DXMATERIAL*)m_Model[m_type][m_modelCount].pBuffmat->GetBufferPointer();

		for (int nCnt = 0; nCnt < (int)m_Model[m_type][m_modelCount].nNumMat; nCnt++)
		{
			// ���[�J���̃}�e���A��
			D3DMATERIAL9 LocalMat = pMat[nCnt].MatD3D;

			// �F�ύX�t���O���I���̂Ƃ�
			if (m_bColorChangeFlag)
			{
				// �}�e���A���J���[
				D3DXCOLOR MatCol = LocalMat.Diffuse;
				// ���Z����F����
				MatCol += m_AddColor;
				// ���[�J���}�e���A���̐F�ύX
				LocalMat.Diffuse = MatCol;
			}
			pDevice->SetTexture(0, m_Model[m_type][m_modelCount].m_pTexture[nCnt]);
			// �}�e���A���̐ݒ�
			pDevice->SetMaterial(&LocalMat);
			// �`��
			m_Model[m_type][m_modelCount].pMesh->DrawSubset(nCnt);
		}
	}
}