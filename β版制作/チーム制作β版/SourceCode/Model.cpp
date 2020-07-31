//=============================================================================
// モデル処理 [Model.cpp]
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
	{ "data/MODEL/Gun/Gun.x" },						// ハンドガン
	{ "data/MODEL/Gun/Gun.x" },						// ヘビーマシンガン
	{ "data/MODEL/Gun/Gun.x" },						// ショットガン
	{ "data/MODEL/Gun/Gun.x" },						// レーザーガン
	{ "data/MODEL/Gun/Gun.x" },						// ロケットランチャー
	{ "data/MODEL/Gun/Gun.x" },						// フレイムショット
	{ "data/MODEL/Gun/TankGun.x" },					// 戦車の銃
	{ "data/MODEL/Gun/PlaneGun.x" },				// 戦闘機の銃
	{ "data/MODEL/Gun/HeliGun.x" },					// ヘリの銃
	{ "data/MODEL/Gun/Knife.x" },					// ナイフ
};
char *CModel::m_BulletFileName[MODEL_BULLET_MAX] =
{
	{ "data/MODEL/Bullet/Sphere.x" },				// 丸
	{ "data/MODEL/Bullet/Rocketlauncher.x" },		// ロケットランチャー
	{ "data/MODEL/Bullet/Grenade.x" },				// グレネード
};

char *CModel::m_TankFileName[MODEL_TANK_MAX] =
{
	{ "data/MODEL/Tank/Tankbody.x" },				// 戦車の体
	{ "data/MODEL/Tank/Tank_frontwheel.x" },		// 戦車の前タイヤ
	{ "data/MODEL/Tank/Tank_backwheel.x" },			// 戦車の後タイヤ
	{ "data/MODEL/Tank/Tankgun.x" },				// 戦車の銃
};

char *CModel::m_PlaneFileName[MODEL_PLANE_MAX] =
{
	{ "data/MODEL/BattlePlane/BattlePlane_Body.x" },// 戦闘機の機体
	{ "data/MODEL/BattlePlane/BattlePlane_Gun.x" },	// 戦闘機の銃
};

char *CModel::m_HeliFileName[MODEL_HELI_MAX] =
{
	{ "data/MODEL/Helicopter/Helicopter_Body.x" },		// ヘリコプターの機体
	{ "data/MODEL/Helicopter/Helicopter_Propeller.x" },	// ヘリコプターのプロペラ
	{ "data/MODEL/Helicopter/Helicopter_Gun.x" },		// ヘリコプターの銃
};


char *CModel::m_ObstacleFileName[OBSTACLE_TYPE_MAX] =
{
	{ "data/MODEL/Object/Obstacle_Box.x" },			// 箱
	{ "data/MODEL/Object/Obstacle_Barrel.x" },		// 樽
	{ "data/MODEL/Object/Obstacle_Tree.x" },		// 木
	{ "data/MODEL/Object/Obstacle_Chest.x" },		// 金庫
	{ "data/MODEL/Object/Obstacle_Sandbags.x" },	// 土嚢
};

char *CModel::m_BossFileName[MODEL_BOSS_MAX] =
{
	{ "data/MODEL/Boss/SolodeRoca.x" },			// 箱
};

CModel::CModel(OBJ_TYPE type) : CScene(type)
{
	m_pCollision = nullptr;							// 当たり判定のポインタ
}

CModel::~CModel()
{
	// 当たり判定の削除
	if (m_pCollision != nullptr)
	{
		delete m_pCollision;
		m_pCollision = nullptr;
	}
}
//====================================================================
//モデルのロード
//====================================================================
void CModel::LoadModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATERIAL *pMat;

	//プレイヤーのモデル読み込み
	for (int nCnt = 0; nCnt < MODEL_PLAYER_MAX; nCnt++)
	{
		// Xファイルの読み込み
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
			//保存成功
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

		//保存成功
		std::cout << "PlayerModelLoad >>" << m_PlayerFileName[nCnt] << NEWLINE;

	}

	//マップのモデル読み込み
	for (int nCnt = 0; nCnt < MODEL_MAP_MAX; nCnt++)
	{
		// Xファイルの読み込み
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
			//保存成功
			std::cout << "LoadFailed!! >>" << m_PlayerFileName[nCnt] << NEWLINE;
		}
		else
		{
			m_Model[MAP_MODEL][nCnt].vtxMin = D3DXVECTOR3(1000, 1000, 1000);
			m_Model[MAP_MODEL][nCnt].vtxMax = D3DXVECTOR3(-1000, -1000, -1000);
			//テクスチャのメモリ確保
			m_Model[MAP_MODEL][nCnt].m_pTexture = new LPDIRECT3DTEXTURE9[(int)m_Model[MAP_MODEL][nCnt].nNumMat];
			pMat = (D3DXMATERIAL*)m_Model[MAP_MODEL][nCnt].pBuffmat->GetBufferPointer();

			//テクスチャマテリアル情報の格納
			for (int nCntmat = 0; nCntmat < (int)m_Model[MAP_MODEL][nCnt].nNumMat; nCntmat++)
			{
				m_Model[MAP_MODEL][nCnt].m_pTexture[nCntmat] = NULL;
				D3DXCreateTextureFromFile(pDevice, pMat[nCntmat].pTextureFilename, &m_Model[MAP_MODEL][nCnt].m_pTexture[nCntmat]);
			}

			std::cout << "MapModelLoad >>" << m_MapFileName[nCnt] << NEWLINE;
		}

	}
	//エネミーのモデル読み込み
	for (int nCnt = 0; nCnt < MODEL_ENEMY_MAX; nCnt++)
	{
		// Xファイルの読み込み
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
			//保存成功
			std::cout << "LoadFailed!! >>" << m_PlayerFileName[nCnt] << NEWLINE;
		}
		else
		{
				//テクスチャのメモリ確保
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

	//捕虜のモデル読み込み
	for (int nCnt = 0; nCnt < MODEL_PRISONER_MAX; nCnt++)
	{
		// Xファイルの読み込み
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
		//テクスチャのメモリ確保
		m_Model[PRISONER_MODEL][nCnt].m_pTexture = new LPDIRECT3DTEXTURE9[(int)m_Model[PRISONER_MODEL][nCnt].nNumMat];
		pMat = (D3DXMATERIAL*)m_Model[PRISONER_MODEL][nCnt].pBuffmat->GetBufferPointer();

		for (int nCntmat = 0; nCntmat < (int)m_Model[PRISONER_MODEL][nCnt].nNumMat; nCntmat++)
		{
			m_Model[PRISONER_MODEL][nCnt].m_pTexture[nCntmat] = NULL;
			D3DXCreateTextureFromFile(pDevice, pMat[nCntmat].pTextureFilename, &m_Model[PRISONER_MODEL][nCnt].m_pTexture[nCntmat]);
		}

		std::cout << "PrisonerLoad >>" << m_PrisonerFileName[nCnt] << NEWLINE;

	}
	//銃のモデル読み込み
	for (int nCnt = 0; nCnt < MODEL_GUN_MAX; nCnt++)
	{
		// Xファイルの読み込み
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
		//テクスチャのメモリ確保
		m_Model[GUN_MODEL][nCnt].m_pTexture = new LPDIRECT3DTEXTURE9[(int)m_Model[GUN_MODEL][nCnt].nNumMat];
		pMat = (D3DXMATERIAL*)m_Model[GUN_MODEL][nCnt].pBuffmat->GetBufferPointer();

		for (int nCntmat = 0; nCntmat < (int)m_Model[GUN_MODEL][nCnt].nNumMat; nCntmat++)
		{
			m_Model[GUN_MODEL][nCnt].m_pTexture[nCntmat] = NULL;
			D3DXCreateTextureFromFile(pDevice, pMat[nCntmat].pTextureFilename, &m_Model[GUN_MODEL][nCnt].m_pTexture[nCntmat]);
		}

		std::cout << "GunModelLoad >>" << m_GunFileName[nCnt] << NEWLINE;

	}
	//弾のモデル読み込み
	for (int nCnt = 0; nCnt < MODEL_BULLET_MAX; nCnt++)
	{
		// Xファイルの読み込み
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
		//テクスチャのメモリ確保
		m_Model[BULLET_MODEL][nCnt].m_pTexture = new LPDIRECT3DTEXTURE9[(int)m_Model[BULLET_MODEL][nCnt].nNumMat];
		pMat = (D3DXMATERIAL*)m_Model[BULLET_MODEL][nCnt].pBuffmat->GetBufferPointer();

		for (int nCntmat = 0; nCntmat < (int)m_Model[BULLET_MODEL][nCnt].nNumMat; nCntmat++)
		{
			m_Model[BULLET_MODEL][nCnt].m_pTexture[nCntmat] = NULL;
			D3DXCreateTextureFromFile(pDevice, pMat[nCntmat].pTextureFilename, &m_Model[BULLET_MODEL][nCnt].m_pTexture[nCntmat]);
		}
	}

	//障害物箱のモデル読み込み
	for (int nCnt = 0; nCnt < OBSTACLE_TYPE_MAX; nCnt++)
	{
		// Xファイルの読み込み
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
		//テクスチャのメモリ確保
		m_Model[OBSTACLE_MODEL][nCnt].m_pTexture = new LPDIRECT3DTEXTURE9[(int)m_Model[OBSTACLE_MODEL][nCnt].nNumMat];
		pMat = (D3DXMATERIAL*)m_Model[OBSTACLE_MODEL][nCnt].pBuffmat->GetBufferPointer();

		for (int nCntmat = 0; nCntmat < (int)m_Model[OBSTACLE_MODEL][nCnt].nNumMat; nCntmat++)
		{
			m_Model[OBSTACLE_MODEL][nCnt].m_pTexture[nCntmat] = NULL;
			D3DXCreateTextureFromFile(pDevice, pMat[nCntmat].pTextureFilename, &m_Model[OBSTACLE_MODEL][nCnt].m_pTexture[nCntmat]);
		}

		std::cout << "OBSTACLE Load >>" << m_ObstacleFileName[nCnt] << NEWLINE;

	}
	//戦車のモデル読み込み
	for (int nCnt = 0; nCnt < MODEL_TANK_MAX; nCnt++)
	{
		// Xファイルの読み込み
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
		//テクスチャのメモリ確保
		m_Model[TANK_MODEL][nCnt].m_pTexture = new LPDIRECT3DTEXTURE9[(int)m_Model[TANK_MODEL][nCnt].nNumMat];
		pMat = (D3DXMATERIAL*)m_Model[TANK_MODEL][nCnt].pBuffmat->GetBufferPointer();

		for (int nCntmat = 0; nCntmat < (int)m_Model[TANK_MODEL][nCnt].nNumMat; nCntmat++)
		{
			m_Model[TANK_MODEL][nCnt].m_pTexture[nCntmat] = NULL;
			D3DXCreateTextureFromFile(pDevice, pMat[nCntmat].pTextureFilename, &m_Model[TANK_MODEL][nCnt].m_pTexture[nCntmat]);
		}

		std::cout << "TANKMODEL Load >>" << m_TankFileName[nCnt] << NEWLINE;

	}

	//戦闘機のモデル読み込み
	for (int nCnt = 0; nCnt < MODEL_PLANE_MAX; nCnt++)
	{
		// Xファイルの読み込み
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
		//テクスチャのメモリ確保
		m_Model[PLANE_MODEL][nCnt].m_pTexture = new LPDIRECT3DTEXTURE9[(int)m_Model[PLANE_MODEL][nCnt].nNumMat];
		pMat = (D3DXMATERIAL*)m_Model[PLANE_MODEL][nCnt].pBuffmat->GetBufferPointer();

		for (int nCntmat = 0; nCntmat < (int)m_Model[PLANE_MODEL][nCnt].nNumMat; nCntmat++)
		{
			m_Model[PLANE_MODEL][nCnt].m_pTexture[nCntmat] = NULL;
			D3DXCreateTextureFromFile(pDevice, pMat[nCntmat].pTextureFilename, &m_Model[PLANE_MODEL][nCnt].m_pTexture[nCntmat]);
		}

		std::cout << "PLANEMODEL Load >>" << m_PlaneFileName[nCnt] << NEWLINE;
	}

	// ヘリのモデル読み込み
	for (int nCnt = 0; nCnt < MODEL_HELI_MAX; nCnt++)
	{
		// Xファイルの読み込み
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
		//テクスチャのメモリ確保
		m_Model[HELI_MODEL][nCnt].m_pTexture = new LPDIRECT3DTEXTURE9[(int)m_Model[HELI_MODEL][nCnt].nNumMat];
		pMat = (D3DXMATERIAL*)m_Model[HELI_MODEL][nCnt].pBuffmat->GetBufferPointer();

		for (int nCntmat = 0; nCntmat < (int)m_Model[HELI_MODEL][nCnt].nNumMat; nCntmat++)
		{
			m_Model[HELI_MODEL][nCnt].m_pTexture[nCntmat] = NULL;
			D3DXCreateTextureFromFile(pDevice, pMat[nCntmat].pTextureFilename, &m_Model[HELI_MODEL][nCnt].m_pTexture[nCntmat]);
		}

		std::cout << "HELIMODEL Load >>" << m_HeliFileName[nCnt] << NEWLINE;
	}
	// ボスのモデル読み込み
	for (int nCnt = 0; nCnt < MODEL_BOSS_MAX; nCnt++)
	{
		// Xファイルの読み込み
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
		//テクスチャのメモリ確保
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
//モデルの開放
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
	//マップのモデル読み込み
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
	// 銃のモデル
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
	// 弾のモデル
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
	//タンク
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

	// 戦闘機
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

	// ヘリコプター
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
	// ボス
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
//初期化
//====================================================================
HRESULT CModel::Init(void)
{
	m_pos				= D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 位置
	m_move				= D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 移動量
	m_rot				= D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 回転
	m_col				= D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	// カラー
	m_AddColor			= D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	// 加算する色
	m_bDieFlag			= false;								// 死亡フラグ
	m_bColorChangeFlag	= false;									// 色変更フラグ
	m_type				= 0;									// 種類
	int nNumVertices;
	DWORD sizeFVF;
	BYTE *pVertexBuffer;
															// 当たり判定生成
	m_pCollision = CCollision::Create();

	for (int nCnt = 0; nCnt < MODEL_MAP_MAX; nCnt++)
	{
		if (m_Model[MAP_MODEL][nCnt].pMesh != NULL)
		{
			//頂点数を取得
			nNumVertices = m_Model[MAP_MODEL][nCnt].pMesh->GetNumVertices();
			//頂点フォーマットのサイズを取得
			sizeFVF = D3DXGetFVFVertexSize(m_Model[MAP_MODEL][nCnt].pMesh->GetFVF());
			//頂点バッファをロック
			m_Model[MAP_MODEL][nCnt].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVertexBuffer);
			for (int nCntVtx = 0; nCntVtx < nNumVertices; nCntVtx++)
			{
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVertexBuffer;
				//すべての頂点情報を比較して最小、最大を抜き出す
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
				pVertexBuffer += sizeFVF; // サイズ分ポインタを進める
			}
			//頂点バッファをアンロック
			m_Model[MAP_MODEL][nCnt].pMesh->UnlockVertexBuffer();
		}
	}
	return S_OK;
}
//====================================================================
//終了
//====================================================================
void CModel::Uninit(void)
{
}
//====================================================================
//更新
//====================================================================
void CModel::Update(void)
{
}
//====================================================================
//描画
//====================================================================
void CModel::Draw(D3DXMATRIX mat)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// マトリックスの計算
	CHossoLibrary::CalcMatrix(&m_mtxWorld, m_pos, m_rot);

	// ポリゴンの描画
	pDevice->SetTexture(0, NULL);

	//親子関係
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

	// 描画
	DrawMesh();
}
//====================================================================
//描画
//====================================================================
void CModel::Draw()
{
	// マトリックスの計算
	CHossoLibrary::CalcMatrix(&m_mtxWorld, m_pos, m_rot);

	// 描画
	DrawMesh();
}
//====================================================================
//デバッグ
//====================================================================
void CModel::DebugInfo()
{
}
//====================================================================
//モデルのクリエイト
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
//モデルのクリエイト(シーンで管理する)
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
//モデルのファイル名取得
//====================================================================
char * CModel::GetModelFileName(int nType, int nModelCount)
{
	//タイプで読み込む配列を変える
	switch (nType)
	{
		//プレイヤー
	case PLAYER_MODEL:
		return m_PlayerFileName[nModelCount];
		break;
		//敵
	case ENEMY_MODEL:
		return m_EnemyFileName[nModelCount];
		break;
		//マップ
	case MAP_MODEL:
		return m_MapFileName[nModelCount];
		break;
		//障害物
	case OBSTACLE_MODEL:
		return m_ObstacleFileName[nModelCount];
		break;
		//捕虜
	case PRISONER_MODEL:
		return m_PrisonerFileName[nModelCount];
		break;
		//戦車
	case TANK_MODEL:
		return m_TankFileName[nModelCount];
		break;
		//戦車
	case PLANE_MODEL:
		return m_PlaneFileName[nModelCount];
		break;
		//ヘリ
	case HELI_MODEL:
		return m_HeliFileName[nModelCount];
		break;
		//ボス
	case BOSS_MODEL:
		return m_BossFileName[nModelCount];
		break;
	}
	return nullptr;
}

//====================================================================
 //マトリックス計算
 //====================================================================
void CModel::NotDrawCalcMtxOnly(D3DXMATRIX * pParentMtx)
{
	// マトリックスの計算
	CHossoLibrary::CalcMatrix(&m_mtxWorld, m_pos, m_rot);

	//親マトリックスの計算
	D3DXMatrixMultiply(&m_mtxWorld,
		&m_mtxWorld,
		pParentMtx);
}
//====================================================================
//描画
//====================================================================
void CModel::DrawMesh()
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATERIAL *pMat;

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// マテリアル情報に対するポインタを取得
	if (m_Model[m_type][m_modelCount].pBuffmat != NULL)
	{
		pMat = (D3DXMATERIAL*)m_Model[m_type][m_modelCount].pBuffmat->GetBufferPointer();

		for (int nCnt = 0; nCnt < (int)m_Model[m_type][m_modelCount].nNumMat; nCnt++)
		{
			// ローカルのマテリアル
			D3DMATERIAL9 LocalMat = pMat[nCnt].MatD3D;

			// 色変更フラグがオンのとき
			if (m_bColorChangeFlag)
			{
				// マテリアルカラー
				D3DXCOLOR MatCol = LocalMat.Diffuse;
				// 加算する色を代入
				MatCol += m_AddColor;
				// ローカルマテリアルの色変更
				LocalMat.Diffuse = MatCol;
			}
			pDevice->SetTexture(0, m_Model[m_type][m_modelCount].m_pTexture[nCnt]);
			// マテリアルの設定
			pDevice->SetMaterial(&LocalMat);
			// 描画
			m_Model[m_type][m_modelCount].pMesh->DrawSubset(nCnt);
		}
	}
}