// =====================================================================================================================================================================
//
// オブジェクトモデルの処理 [objectmodel.cpp]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#include "objectmodel.h"			// インクルードファイル
#include "debugproc.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "motion.h"
#include "map.h"
#include "effect.h"
#include "camera.h"

// =====================================================================================================================================================================
// マクロ定義
// =====================================================================================================================================================================
#define MODEL_FILE01				"data/OBJECT/stone0.x"						// 石
#define MODEL_FILE02				"data/OBJECT/box0.x"						// 箱
#define MODEL_FILE03				"data/OBJECT/ground.L.x"					// 地面 (大
#define MODEL_FILE04				"data/OBJECT/ground.M.x"					// 地面 (中
#define MODEL_FILE05				"data/OBJECT/ground.S.x"					// 地面 (小
#define MODEL_FILE06				"data/OBJECT/geyser.x"						// 間欠泉
#define MODEL_FILE07				"data/OBJECT/scaffold.x"					// 足場
#define MODEL_FILE08				"data/OBJECT/scaffold_Hit.x"				// 2Dでも当たる足場
#define MODEL_FILE09				"data/OBJECT/scaffold_Move.x"				// 動く足場
#define MODEL_FILE010				"data/OBJECT/wall.x"						// 壁
#define MODEL_FILE011				"data/OBJECT/ground.Half.x"					// 地面 (ハーフ
#define MODEL_FILE012				"data/OBJECT/ground.quarter.x"				// 地面 (4/1
#define MODEL_FILE013				"data/OBJECT/signboard_fall.x"				// 看板 (落ちる
#define MODEL_FILE014				"data/OBJECT/signboard_jump.x"				// 看板 (ジャンプ
#define MODEL_FILE015				"data/OBJECT/signboard_gayser.x"			// 看板 (間欠泉
#define MODEL_FILE016				"data/OBJECT/signboard_change.x"			// 看板 (カメラ切替え
#define MODEL_FILE017				"data/OBJECT/signboard_All_ride.x"			// 看板 (2Dでも乗れる
#define MODEL_FILE018				"data/OBJECT/signboard_3D_ride.x"			// 看板 (3Dでしか乗れない

#define TEXTURE_FILE01				"data/TEXTURE/stone.jpg"					// 石
#define TEXTURE_FILE02				"data/TEXTURE/box02.png"					// 箱
#define TEXTURE_FILE03				"data/TEXTURE/Rock00.jpg"					// 地面
#define TEXTURE_FILE04				"data/TEXTURE/Stone00.jpg"					// 間欠泉
#define TEXTURE_FILE05				"data/TEXTURE/hibi.jpg"						// 足場
#define TEXTURE_FILE06				"data/TEXTURE/iron.jpg"						// 2Dでも当たる足場
#define TEXTURE_FILE07				"data/TEXTURE/block.png"					// 動く足場
#define TEXTURE_FILE08				"data/TEXTURE/fall00.png"					// 看板 (落ちる
#define TEXTURE_FILE09				"data/TEXTURE/jump00.png"					// 看板 (ジャンプ
#define TEXTURE_FILE10				"data/TEXTURE/gayser_caution.png"			// 看板 (間欠泉
#define TEXTURE_FILE11				"data/TEXTURE/change.png"					// 看板 (カメラ切替え
#define TEXTURE_FILE12				"data/TEXTURE/ride01.png"					// 看板 (2Dでも乗れる
#define TEXTURE_FILE13				"data/TEXTURE/ride02.png"					// 看板 (3Dでしか乗れない

#define RESIDUAL_ERROR				(0.4f)										// 誤差
#define OBJECT_MOVE_X				(0.7f)										// 移動オブジェクトの移動量

// =====================================================================================================================================================================
// 静的メンバ変数の初期化
// =====================================================================================================================================================================
MODEL_DRAWINFO		CObjectModel::m_ModelDrawInfo[OBJECTTYPE_MAX]	= {};
LPDIRECT3DTEXTURE9	CObjectModel::m_apTexture[OBJECTTYPE_MAX]		= {};

// =====================================================================================================================================================================
//
// コンストラクタ
//
// =====================================================================================================================================================================
CObjectModel::CObjectModel():CSceneX(PRIORITY_MODEL)
{
	m_ObjectType = OBJECTTYPE_NONE;		// オブジェクトの種類
}

// =====================================================================================================================================================================
//
// デストラクタ
//
// =====================================================================================================================================================================
CObjectModel::~CObjectModel()
{
}

// =====================================================================================================================================================================
//
// 初期化処理
//
// =====================================================================================================================================================================
void CObjectModel::Init(void)
{
	m_posOld	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);					 // 過去の位置
	m_move		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);					 // 移動
	m_VtxMin	= D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);			 // 最小頂点
	m_VtxMax	= D3DXVECTOR3(-1000.0f, -1000.0f, -1000.0f);		 // 最大頂点

	// 最大・最小頂点の設定
	CLibrary::SetVertexObject(&m_VtxMin, &m_VtxMax, m_ModelDrawInfo[m_ObjectType].Mesh);

	// モデル描画情報の設定
	SetModelDraw(&m_ModelDrawInfo[m_ObjectType]);

	// 初期化
	CSceneX::Init();
}

// =====================================================================================================================================================================
//
// 終了処理
//
// =====================================================================================================================================================================
void CObjectModel::Uninit(void)
{
	CSceneX::Uninit();
}

// =====================================================================================================================================================================
//
// 更新処理
//
// =====================================================================================================================================================================
void CObjectModel::Update(void)
{
	// 位置の取得
	D3DXVECTOR3 pos = CSceneX::GetPos();

	// 位置保存
	m_posOld = pos;

	switch (m_ObjectType)
	{
	case CObjectModel::OBJECTTYPE_SCAFFOLD_MOVE:

		// 移動制限
		if (pos.x <= -100.0f)
		{
			// 反転
			m_move.x *= -1;
		}
		else if (pos.x >= 100.0f)
		{
			// 反転
			m_move.x *= -1;
		}
		break;
	}

	// 位置更新
	pos += m_move;

	// 位置の設定
	CSceneX::SetPos(pos);

	// 更新
	CSceneX::Update();
}

// =====================================================================================================================================================================
//
// 描画処理
//
// =====================================================================================================================================================================
void CObjectModel::Draw(void)
{
	D3DXMATRIX			mtxWorld;

	// ワールドマトリックスの計算
	CLibrary::MatrixCalculation(&mtxWorld, GetRot(), GetPos());

	//計算後マトリックス設定
	SetMatrix(mtxWorld);

	//モデルの描画
	DrawModel();
}

// =====================================================================================================================================================================
//
// オブジェクトモデルの生成
//
// =====================================================================================================================================================================
CObjectModel * CObjectModel::Create(D3DXVECTOR3 pos, OBJECTTYPE type)
{
	// 変数
	CObjectModel *pObjectModel;

	// メモリの確保
	pObjectModel = new CObjectModel;

	// オブジェクトの種類
	pObjectModel->m_ObjectType = type;

	// 初期化
	pObjectModel->Init();

	// 位置の設定
	pObjectModel->SetPos(pos);

	// テクスチャの割り当て
	pObjectModel->BindTexture(m_apTexture[type]);

	switch (pObjectModel->m_ObjectType)
	{
	case CObjectModel::OBJECTTYPE_SCAFFOLD_MOVE:
		// 横移動
		pObjectModel->m_move.x = OBJECT_MOVE_X;
		break;
	}
	// 間欠泉のオブジェクトのとき
	if (pObjectModel->m_ObjectType == OBJECTTYPE_GAYSER)
	{
		// 間欠泉のエフェクト生成
		CEffect::Create(pos, CEffect::EFFECTTYPE_GAYSER);
	}
	return pObjectModel;
}

// =====================================================================================================================================================================
//
// ロード
//
// =====================================================================================================================================================================
HRESULT CObjectModel::Load(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = *CManager::GetRenderer()->GetDevice();

	// モデルファイル名
	char *sModelFileName[OBJECTTYPE_MAX]
	{
		{ MODEL_FILE01 },		// OBJECTTYPE_STONE				( 石
		{ MODEL_FILE02 },		// OBJECTTYPE_BOX				( 箱
		{ MODEL_FILE03 },		// OBJECTTYPE_GROUND_L			( 地面 (大
		{ MODEL_FILE04 },		// OBJECTTYPE_GROUND_M			( 地面 (中
		{ MODEL_FILE05 },		// OBJECTTYPE_GROUND_S			( 地面 (小
		{ MODEL_FILE06 }, 		// OBJECTTYPE_GAYSER			( 間欠泉
		{ MODEL_FILE07 }, 		// OBJECTTYPE_SCAFFOLD			( 足場
		{ MODEL_FILE08 }, 		// OBJECTTYPE_SCAFFOLD_HIT		( 2Dでも当たる足場
		{ MODEL_FILE09 }, 		// OBJECTTYPE_SCAFFOLD_MOVE		( 動く足場
		{ MODEL_FILE010 }, 		// OBJECTTYPE_WALL				( 壁
		{ MODEL_FILE011 }, 		// OBJECTTYPE_GROUND_HALF		( 地面 (ハーフ
		{ MODEL_FILE012 }, 		// OBJECTTYPE_GROUND_QUARTER	( 地面 (4/1
		{ MODEL_FILE013 }, 		// OBJECTTYPE_SIGNBOARD_FALL	( 看板 (落ちる
		{ MODEL_FILE014 }, 		// OBJECTTYPE_SIGNBOARD_JUMP	( 看板 (ジャンプ
		{ MODEL_FILE015 }, 		// OBJECTTYPE_SIGNBOARD_GAYSER	( 看板 (間欠泉
		{ MODEL_FILE016 }, 		// OBJECTTYPE_SIGNBOARD_CHANGE	( 看板 (カメラ切替え
		{ MODEL_FILE017 }, 		// OBJECTTYPE_SIGNBOARD_ALL_RIDE( 看板 (2Dでも乗れる
		{ MODEL_FILE018 }, 		// OBJECTTYPE_SIGNBOARD_3D_RIDE	( 看板 (3Dでしか乗れない
	};

	// テクスチャファイル名
	char *sTextureFileName[OBJECTTYPE_MAX]
	{
		{ TEXTURE_FILE01 },		// OBJECTTYPE_STONE				( 石
		{ TEXTURE_FILE02 },		// OBJECTTYPE_BOX				( 箱
		{ TEXTURE_FILE03 },		// OBJECTTYPE_GROUND_L			( 地面 (大
		{ TEXTURE_FILE03 },		// OBJECTTYPE_GROUND_M			( 地面 (中
		{ TEXTURE_FILE03 },		// OBJECTTYPE_GROUND_S			( 地面 (小
		{ TEXTURE_FILE04 },		// OBJECTTYPE_GAYSER			( 間欠泉
		{ TEXTURE_FILE05 },		// OBJECTTYPE_SCAFFOLD			( 足場
		{ TEXTURE_FILE06 },		// OBJECTTYPE_SCAFFOLD_HIT		( 2Dでも当たる足場
		{ TEXTURE_FILE07 },		// OBJECTTYPE_SCAFFOLD_MOVE		( 動く足場
		{ TEXTURE_FILE03 },		// OBJECTTYPE_WALL				( 壁
		{ TEXTURE_FILE03 },		// OBJECTTYPE_GROUND_HALF		( 地面 (ハーフ
		{ TEXTURE_FILE03 },		// OBJECTTYPE_GROUND_QUARTER	( 地面 (4/1
		{ TEXTURE_FILE08 },		// OBJECTTYPE_SIGNBOARD_FALL	( 看板 (落ちる
		{ TEXTURE_FILE09 },		// OBJECTTYPE_SIGNBOARD_JUMP	( 看板 (ジャンプ
		{ TEXTURE_FILE10 },		// OBJECTTYPE_SIGNBOARD_GAYSER	( 看板 (間欠泉
		{ TEXTURE_FILE11 },		// OBJECTTYPE_SIGNBOARD_CHANGE	( 看板 (カメラ切替え
		{ TEXTURE_FILE12 },		// OBJECTTYPE_SIGNBOARD_ALL_RIDE( 看板 (2Dでも乗れる
		{ TEXTURE_FILE13 },		// OBJECTTYPE_SIGNBOARD_3D_RIDE	( 看板 (3Dでしか乗れない
	};

	for (int nCntObject = 0; nCntObject < OBJECTTYPE_MAX; nCntObject++)
	{
		// Xファイルの読み込み
		D3DXLoadMeshFromX(sModelFileName[nCntObject], D3DXMESH_SYSTEMMEM, pDevice, NULL, 
			&m_ModelDrawInfo[nCntObject].BuffMat, NULL, &m_ModelDrawInfo[nCntObject].nNumMat, &m_ModelDrawInfo[nCntObject].Mesh);

		// テクスチャ読み込み
		D3DXCreateTextureFromFile(pDevice, sTextureFileName[nCntObject], &m_apTexture[nCntObject]);
	}

	return S_OK;
}

// =====================================================================================================================================================================
//
// アンロード
//
// =====================================================================================================================================================================
void CObjectModel::Unload(void)
{
	for (int nCntTex = 0; nCntTex < CObjectModel::OBJECTTYPE_MAX; nCntTex++)
	{
		// テクスチャの開放
		if (m_apTexture[nCntTex] != NULL)
		{
			m_apTexture[nCntTex]->Release();
			m_apTexture[nCntTex] = NULL;
		}
	}
}

// =====================================================================================================================================================================
//
// オブジェクトの当たり判定
//
// =====================================================================================================================================================================
bool CObjectModel::CollisionObject(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 *pSize, CObjectModel **ppObjectRet)
{
	// カメラの取得
	CCamera *pCamera;
	pCamera = CManager::GetRenderer()->GetCamera();
	// 位置の取得
	D3DXVECTOR3 pos = CSceneX::GetPos();
	bool bLand = false;							// 着地の判定

	// NULLチェック
	if (ppObjectRet != NULL)
	{
		*ppObjectRet = NULL;
	}

	// ブロックの範囲 ( 横 )
	if ((m_VtxMin.x + pos.x < pPos->x + pSize->x &&
		m_VtxMax.x + pos.x > pPos->x - pSize->x) || 
		(pCamera->GetCameraMode() == CCamera::CAMERA_MODE_2D &&
		m_ObjectType == CObjectModel::OBJECTTYPE_SCAFFOLD_HIT))
	{
		// ブロックの範囲 ( 縦 )
		if (m_VtxMin.z + pos.z < pPos->z + pSize->z &&
			m_VtxMax.z + pos.z > pPos->z - pSize->z)
		{
			// ブロックの範囲 ( 高さ )
			if (m_VtxMin.y + pos.y <= pPos->y + pSize->y &&
				m_VtxMax.y + pos.y > pPos->y)
			{
				// 上の当たり判定
				if (pPos->y < m_VtxMax.y + pos.y &&
					pPosOld->y + RESIDUAL_ERROR >= m_VtxMax.y + m_posOld.y)
				{
					pMove->y = 0;
					pPos->y = m_VtxMax.y + pos.y;
					pPos->x += m_move.x;

					bLand = true;
					*ppObjectRet = this;
				}

				// 前の当たり判定
				else if (pPos->z + pSize->z > m_VtxMin.z + pos.z &&
					pPosOld->z + pSize->z < m_VtxMin.z + pos.z)
				{
					pPos->z = m_VtxMin.z + pos.z - pSize->z - RESIDUAL_ERROR;
					pMove->z = 0;
				}

				// 後ろの当たり判定
				else if (pPos->z - pSize->z < m_VtxMax.z + pos.z &&
					pPosOld->z - pSize->z >= m_VtxMax.z + m_posOld.z)
				{
					pPos->z = m_VtxMax.z + pos.z + pSize->z + RESIDUAL_ERROR;
					pMove->z = 0;
				}

				// 左の当たり判定
				else if (pPos->x + pSize->x > m_VtxMin.x + pos.x &&
					pPosOld->x + pSize->x <= m_VtxMin.x + m_posOld.x)
				{
					pPos->x = m_VtxMin.x + pos.x - pSize->x - RESIDUAL_ERROR;
					pMove->x = 0;
				}
				// 右の当たり判定
				else if (pPos->x - pSize->x < m_VtxMax.x + pos.x &&
					pPosOld->x - pSize->x >= m_VtxMax.x + m_posOld.x)
				{
					pPos->x = m_VtxMax.x + pos.x + pSize->x + RESIDUAL_ERROR;
					pMove->x = 0;
				}

				// 下の当たり判定
				else if (pPos->y + pSize->y > m_VtxMin.y + pos.y &&
					pPosOld->y + pSize->y <= m_VtxMin.y + m_posOld.y)
				{
					pPos->y = m_VtxMin.y + pos.y - pSize->y - RESIDUAL_ERROR;
					pMove->y = 0;
				}
				else
				{
					pMove->y = 0.0f;
					pPos->y = m_VtxMax.y + pos.y;
					pPos->x += m_move.x;

					bLand = true;
					*ppObjectRet = this;
				}
			}
		}
	}
	return bLand;
}

// =====================================================================================================================================================================
//
// オブジェクトの種類の設定
//
// =====================================================================================================================================================================
void CObjectModel::SetObjectType(OBJECTTYPE type)
{
	m_ObjectType = type;

	// 最大・最小頂点の設定
	CLibrary::SetVertexObject(&m_VtxMin, &m_VtxMax, m_ModelDrawInfo[m_ObjectType].Mesh);

	// モデル描画情報の設定
	SetModelDraw(&m_ModelDrawInfo[m_ObjectType]);
}