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
	{ "data/MODEL/Prisoner/Head.x" },
	{ "data/MODEL/Prisoner/Body.x" },
	{ "data/MODEL/Prisoner/L_Sholder.x" },
	{ "data/MODEL/Prisoner/R_Sholder.x" },
	{ "data/MODEL/Prisoner/L_Hand.x" },
	{ "data/MODEL/Prisoner/R_Hand.x" },
	{ "data/MODEL/Prisoner/L_Foot.x" },
	{ "data/MODEL/Prisoner/R_Foot.x" },
	{ "data/MODEL/Prisoner/L_Leg.x" },
	{ "data/MODEL/Prisoner/R_Leg.x" }
};

char *CModel::m_MapFileName[MODEL_MAP_MAX] =
{
	{ "data/MODEL/map/alphamap.x" },
	{ "data/MODEL/map/block02.x" },
};
char *CModel::m_EnemyFileName[MODEL_ENEMY_MAX] =
{
	{ "data/MODEL/EnemyFire/EnemyHead01.x" },		//1  ==��==
	{ "data/MODEL/EnemyFire/EnemyBody01.x" },		//2
	{ "data/MODEL/EnemyFire/EnemySholder_L01.x" },	//3
	{ "data/MODEL/EnemyFire/EnemySholder_R01.x" },	//4
	{ "data/MODEL/EnemyFire/EnemyHand_L01.x" },		//5
	{ "data/MODEL/EnemyFire/EnemyHand_R01.x" },		//6
	{ "data/MODEL/EnemyFire/EnemyFoot_L01.x" },		//9
	{ "data/MODEL/EnemyFire/EnemyFoot_R01.x" },		//10
	{ "data/MODEL/EnemyFire/EnemyLeg_L01.x" },		//7
	{ "data/MODEL/EnemyFire/EnemyLeg_R01.x" },		//8
	{ "data/MODEL/EnemyFire/Enemy_Wepon01.x" },		//11
};
char *CModel::m_GunFileName[MODEL_GUN_MAX] =
{
	{ "data/MODEL/Gun/Gun.x" },					// �n���h�K��
	{ "data/MODEL/Gun/Gun.x" },					// �w�r�[�}�V���K��
	{ "data/MODEL/Gun/Gun.x" },					// �V���b�g�K��
	{ "data/MODEL/Gun/Gun.x" },					// ���[�U�[�K��
	{ "data/MODEL/Gun/Gun.x" },					// ���P�b�g�����`���[
	{ "data/MODEL/Gun/Gun.x" },					// �t���C���V���b�g
	{ "data/MODEL/Gun/Knife.x" },				// �i�C�t

};
char *CModel::m_BulletFileName[MODEL_BULLET_MAX] =
{
	{ "data/MODEL/Bullet/Sphere.x" },				// ��
	{ "data/MODEL/Bullet/Rocketlauncher.x" },		// ���P�b�g�����`���[
	{ "data/MODEL/Bullet/Grenade.x" },				// �O���l�[�h
};

char *CModel::m_TankFileName[MODEL_TANK_MAX] =
{
	{ "data/MODEL/Tank/Tankbody.x" },				// ��Ԃ̓�
	{ "data/MODEL/Tank/Tankhead.x" },				// ��Ԃ̑�
	{ "data/MODEL/Tank/Tankwheel.x" },				// ��Ԃ̃^�C��
	{ "data/MODEL/Tank/Tankgun.x" },				// ��Ԃ̏e
};

char *CModel::m_ObstacleFileName[OBSTACLE_TYPE_MAX] =
{
	{ "data/MODEL/Object/Obstacle_Box.x" },				// ��
	{ "data/MODEL/Object/testmodel.x" },				// �m�F�p���f��
};


CModel::CModel(OBJ_TYPE type) : CScene(type)
{
	m_pCollision = nullptr;									// �����蔻��̃|�C���^
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
		D3DXLoadMeshFromX(
			m_PlayerFileName[nCnt],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_Model[PLAYER_MODEL][nCnt].pBuffmat,
			NULL,
			&m_Model[PLAYER_MODEL][nCnt].nNumMat,
			&m_Model[PLAYER_MODEL][nCnt].pMesh
		);
		m_Model[PLAYER_MODEL][nCnt].m_pTexture = new LPDIRECT3DTEXTURE9[(int)m_Model[PLAYER_MODEL][nCnt].nNumMat];
		pMat = (D3DXMATERIAL*)m_Model[PLAYER_MODEL][nCnt].pBuffmat->GetBufferPointer();
		for (int nCntmat = 0; nCntmat < (int)m_Model[PLAYER_MODEL][nCnt].nNumMat; nCntmat++)
		{
			m_Model[PLAYER_MODEL][nCnt].m_pTexture[nCntmat] = NULL;
			D3DXCreateTextureFromFile(pDevice, pMat[nCntmat].pTextureFilename, &m_Model[PLAYER_MODEL][nCnt].m_pTexture[nCntmat]);
		}

		//�ۑ�����
		std::cout << "PlayerModelLoad >>" << m_PlayerFileName[nCnt] << NEWLINE;

	}

	//�}�b�v�̃��f���ǂݍ���
	for (int nCnt = 0; nCnt < MODEL_MAP_MAX; nCnt++)
	{
		// X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(
			m_MapFileName[nCnt],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_Model[MAP_MODEL][nCnt].pBuffmat,
			NULL,
			&m_Model[MAP_MODEL][nCnt].nNumMat,
			&m_Model[MAP_MODEL][nCnt].pMesh
		);
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
	//�G�l�~�[�̃��f���ǂݍ���
	for (int nCnt = 0; nCnt < MODEL_ENEMY_MAX; nCnt++)
	{
		// X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(
			m_EnemyFileName[nCnt],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_Model[ENEMY_MODEL][nCnt].pBuffmat,
			NULL,
			&m_Model[ENEMY_MODEL][nCnt].nNumMat,
			&m_Model[ENEMY_MODEL][nCnt].pMesh
		);
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

}
//====================================================================
//���f���̊J��
//====================================================================
void CModel::UnLoad(void)
{
	//�}�b�v�̃��f���ǂݍ���
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
	// �e�̃��f��
	for (int nCnt = 0; nCnt < MODEL_GUN_MAX; nCnt++)


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
			delete[] m_Model[OBSTACLE_MODEL][nCnt].m_pTexture;
			m_Model[TANK_MODEL][nCnt].m_pTexture = NULL;
		}
	}

}
//====================================================================
//������
//====================================================================
HRESULT CModel::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	int nNumVertices;
	m_bDieFlag = false;
	m_type = 0;
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
	D3DXMATRIX mtxRot, mtxTrans,mtxScal;
	D3DXMATERIAL *pMat;
	D3DMATERIAL9 matDef;
	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		m_rot.y,
		m_rot.x,
		m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld,
		&m_mtxWorld,
		&mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTrans,
		m_pos.x,
		m_pos.y,
		m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld,
		&m_mtxWorld,
		&mtxTrans);

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
	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);
	// �}�e���A�����ɑ΂���|�C���^���擾
	if (m_Model[m_type][m_modelCount].pBuffmat != NULL)
	{
		pMat = (D3DXMATERIAL*)m_Model[m_type][m_modelCount].pBuffmat->GetBufferPointer();
		pDevice->SetRenderState(D3DRS_SPECULARENABLE, TRUE);						// ���؂���烂�[�h�L��

		for (int nCnt = 0; nCnt < (int)m_Model[m_type][m_modelCount].nNumMat; nCnt++)
		{
			pDevice->SetTexture(0, m_Model[m_type][m_modelCount].m_pTexture[nCnt]);
			// �}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCnt].MatD3D);
			// �`��
			m_Model[m_type][m_modelCount].pMesh->DrawSubset(nCnt);
		}
	}
	pDevice->SetRenderState(D3DRS_SPECULARENABLE, FALSE);						// ���؂���烂�[�h�L��

	// �}�e���A�����f�t�H���g�ɖ߂�
	//pDevice->SetMaterial(&matDef);
}
//====================================================================
//�`��
//====================================================================
void CModel::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATERIAL *pMat;

	// �}�g���b�N�X�̌v�Z
	CHossoLibrary::CalcMatrix(&m_mtxWorld, m_pos, m_rot);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// �}�e���A�����ɑ΂���|�C���^���擾
	if (m_Model[m_type][m_modelCount].pBuffmat != NULL)
	{
		pMat = (D3DXMATERIAL*)m_Model[m_type][m_modelCount].pBuffmat->GetBufferPointer();
		pDevice->SetRenderState(D3DRS_SPECULARENABLE, TRUE);						// ���؂���烂�[�h�L��

		for (int nCnt = 0; nCnt < (int)m_Model[m_type][m_modelCount].nNumMat; nCnt++)
		{
			pDevice->SetTexture(0, m_Model[m_type][m_modelCount].m_pTexture[nCnt]);
			// �}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCnt].MatD3D);
			// �`��
			m_Model[m_type][m_modelCount].pMesh->DrawSubset(nCnt);
		}
	}
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
	}
	return nullptr;
}
//====================================================================
//�e�̐ݒ�
//====================================================================
void CModel::SetParent(CModel * pModel)
{
	m_pParent = pModel;
}
//====================================================================
//���f���̃I�t�Z�b�g�w��
//====================================================================
void CModel::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}
void CModel::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}
void CModel::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}
//====================================================================
//�ʒu�̎擾
//====================================================================
D3DXVECTOR3 &CModel::GetPosition(void)
{
	return m_pos;
}
//====================================================================
//��]�̎擾
//====================================================================
D3DXVECTOR3 &CModel::GetRot(void)
{
	return m_rot;
}

//====================================================================
//���b�V���擾
//====================================================================
LPD3DXMESH CModel::GetMesh(void)
{
	return m_Model[m_type][m_modelCount].pMesh;
}
//====================================================================
//�}�g���b�N�X�̎擾
//====================================================================
D3DXMATRIX *CModel::GetMatrix(void)
{
	return &m_mtxWorld;
}
//====================================================================
//���_����MAX�擾
//====================================================================
D3DXVECTOR3 CModel::GetvtxMax(int nCnt)
{
	return m_Model[MAP_MODEL][nCnt].vtxMax;
}
//====================================================================
//���_����MIN�擾
//====================================================================
D3DXVECTOR3 CModel::GetvtxMin(int nCnt)
{
	return m_Model[MAP_MODEL][nCnt].vtxMin;
}
