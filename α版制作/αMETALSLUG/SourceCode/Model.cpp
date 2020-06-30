//=============================================================================
// モデル処理 [Model.cpp]
//=============================================================================
#include "model.h"
#include "inputKeyboard.h"
#include "Player.h"
#include "scene.h"
#include "debugproc.h"
CModel::MODEL CModel::m_Model[TYPE_MAX][MAX_ALLMODEL] = {};
char *CModel::m_PlayerFileName[MODEL_PLAYER_MAX] =
{
	{ "data/MODEL/secondchar/Head.x"},
	{ "data/MODEL/secondchar/Body.x" },
	{ "data/MODEL/secondchar/L_Sholder.x" },
	{ "data/MODEL/secondchar/R_Sholder.x" },
	{ "data/MODEL/secondchar/L_Hand.x" },
	{ "data/MODEL/secondchar/R_Hand.x" },
	{ "data/MODEL/secondchar/L_Foot.x" },
	{ "data/MODEL/secondchar/R_Foot.x" },
	{ "data/MODEL/secondchar/L_Leg.x" },
	{ "data/MODEL/secondchar/R_Leg.x" },
	{ "data/MODEL/secondchar/炎剣.x" },
	{ "data/MODEL/secondchar/氷剣.x" },
	{ "data/MODEL/secondchar/雷剣.x" },
};
char *CModel::m_MapFileName[MODEL_MAP_MAX] =
{
	{ "data/MODEL/map/alphamap.x" },
	{ "data/MODEL/map/block02.x" },
};
char *CModel::m_EnemyFileName[MODEL_ENEMY_MAX] =
{
	{ "data/MODEL/EnemyFire/EnemyHead01.x" },		//1  ==炎==
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
	{ "data/MODEL/Gun/HandGun.x" },					// ハンドガン
	{ "data/MODEL/Gun/HandGun.x" },					// ヘビーマシンガン
	{ "data/MODEL/Gun/HandGun.x" },					// ショットガン
	{ "data/MODEL/Gun/HandGun.x" },					// レーザーガン
	{ "data/MODEL/Gun/HandGun.x" },					// ロケットランチャー
	{ "data/MODEL/Gun/HandGun.x" },					// フレイムショット
};
char *CModel::m_BulletFileName[MODEL_BULLET_MAX] =
{
	{ "data/MODEL/Bullet/Sphere.x" },				// 丸
	{ "data/MODEL/Bullet/Rocketlauncher.x" },		// ロケットランチャー
	{ "data/MODEL/Bullet/Grenade.x" },				// グレネード
};

char *CModel::m_ObstacleFileName[OBSTACLE_TYPE_MAX] =
{
	{ "data/MODEL/Object/Obstacle_Box.x" },				// 箱
};


CModel::CModel(OBJ_TYPE type) : CScene(type)
{
}

CModel::~CModel()
{
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
	}

	//マップのモデル読み込み
	for (int nCnt = 0; nCnt < MODEL_MAP_MAX; nCnt++)
	{
		// Xファイルの読み込み
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
		//テクスチャのメモリ確保
		m_Model[MAP_MODEL][nCnt].m_pTexture = new LPDIRECT3DTEXTURE9[(int)m_Model[MAP_MODEL][nCnt].nNumMat];
		pMat = (D3DXMATERIAL*)m_Model[MAP_MODEL][nCnt].pBuffmat->GetBufferPointer();

		//テクスチャマテリアル情報の格納
		for (int nCntmat = 0; nCntmat < (int)m_Model[MAP_MODEL][nCnt].nNumMat; nCntmat++)
		{
			m_Model[MAP_MODEL][nCnt].m_pTexture[nCntmat] = NULL;
			D3DXCreateTextureFromFile(pDevice, pMat[nCntmat].pTextureFilename, &m_Model[MAP_MODEL][nCnt].m_pTexture[nCntmat]);
		}
	}
	//エネミーのモデル読み込み
	for (int nCnt = 0; nCnt < MODEL_ENEMY_MAX; nCnt++)
	{
		// Xファイルの読み込み
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
		//テクスチャのメモリ確保
		m_Model[ENEMY_MODEL][nCnt].m_pTexture = new LPDIRECT3DTEXTURE9[(int)m_Model[ENEMY_MODEL][nCnt].nNumMat];
		pMat = (D3DXMATERIAL*)m_Model[ENEMY_MODEL][nCnt].pBuffmat->GetBufferPointer();

		for (int nCntmat = 0; nCntmat < (int)m_Model[ENEMY_MODEL][nCnt].nNumMat; nCntmat++)
		{
			m_Model[ENEMY_MODEL][nCnt].m_pTexture[nCntmat] = NULL;
			D3DXCreateTextureFromFile(pDevice, pMat[nCntmat].pTextureFilename, &m_Model[ENEMY_MODEL][nCnt].m_pTexture[nCntmat]);
		}
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
	}
}
//====================================================================
//モデルの開放
//====================================================================
void CModel::UnLoad(void)
{
	//マップのモデル読み込み
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
}
//====================================================================
//初期化
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
	D3DXMATRIX mtxRot, mtxTrans,mtxScal;
	D3DXMATERIAL *pMat;
	D3DMATERIAL9 matDef;
	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		m_rot.y,
		m_rot.x,
		m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld,
		&m_mtxWorld,
		&mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTrans,
		m_pos.x,
		m_pos.y,
		m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld,
		&m_mtxWorld,
		&mtxTrans);

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
	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
	// 現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);
	// マテリアル情報に対するポインタを取得
	if (m_Model[m_type][m_modelCount].pBuffmat != NULL)
	{
		pMat = (D3DXMATERIAL*)m_Model[m_type][m_modelCount].pBuffmat->GetBufferPointer();
		pDevice->SetRenderState(D3DRS_SPECULARENABLE, TRUE);						// すぺきゅらモード有効

		for (int nCnt = 0; nCnt < (int)m_Model[m_type][m_modelCount].nNumMat; nCnt++)
		{
			pDevice->SetTexture(0, m_Model[m_type][m_modelCount].m_pTexture[nCnt]);
			// マテリアルの設定
			pDevice->SetMaterial(&pMat[nCnt].MatD3D);
			// 描画
			m_Model[m_type][m_modelCount].pMesh->DrawSubset(nCnt);
		}
	}
	pDevice->SetRenderState(D3DRS_SPECULARENABLE, FALSE);						// すぺきゅらモード有効

	// マテリアルをデフォルトに戻す
	//pDevice->SetMaterial(&matDef);
}
//====================================================================
//描画
//====================================================================
void CModel::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATERIAL *pMat;

	// マトリックスの計算
	CHossoLibrary::CalcMatrix(&m_mtxWorld, m_pos, m_rot);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// マテリアル情報に対するポインタを取得
	if (m_Model[m_type][m_modelCount].pBuffmat != NULL)
	{
		pMat = (D3DXMATERIAL*)m_Model[m_type][m_modelCount].pBuffmat->GetBufferPointer();
		pDevice->SetRenderState(D3DRS_SPECULARENABLE, TRUE);						// すぺきゅらモード有効

		for (int nCnt = 0; nCnt < (int)m_Model[m_type][m_modelCount].nNumMat; nCnt++)
		{
			pDevice->SetTexture(0, m_Model[m_type][m_modelCount].m_pTexture[nCnt]);
			// マテリアルの設定
			pDevice->SetMaterial(&pMat[nCnt].MatD3D);
			// 描画
			m_Model[m_type][m_modelCount].pMesh->DrawSubset(nCnt);
		}
	}
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
	case 0:
		return m_PlayerFileName[nModelCount];
		break;
		//マップ
	case 1:
		return m_MapFileName[nModelCount];
		break;
		//敵
	case 2:
		return m_EnemyFileName[nModelCount];
		break;
	}
	return nullptr;
}
//====================================================================
//親の設定
//====================================================================
void CModel::SetParent(CModel * pModel)
{
	m_pParent = pModel;
}
//====================================================================
//モデルのオフセット指定
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
//位置の取得
//====================================================================
D3DXVECTOR3 &CModel::GetPosition(void)
{
	return m_pos;
}
//====================================================================
//回転の取得
//====================================================================
D3DXVECTOR3 &CModel::GetRot(void)
{
	return m_rot;
}

//====================================================================
//メッシュ取得
//====================================================================
LPD3DXMESH CModel::GetMesh(void)
{
	return m_Model[m_type][m_modelCount].pMesh;
}
//====================================================================
//マトリックスの取得
//====================================================================
D3DXMATRIX *CModel::GetMatrix(void)
{
	return &m_mtxWorld;
}
//====================================================================
//頂点情報のMAX取得
//====================================================================
D3DXVECTOR3 CModel::GetvtxMax(int nCnt)
{
	return m_Model[MAP_MODEL][nCnt].vtxMax;
}
//====================================================================
//頂点情報のMIN取得
//====================================================================
D3DXVECTOR3 CModel::GetvtxMin(int nCnt)
{
	return m_Model[MAP_MODEL][nCnt].vtxMin;
}
