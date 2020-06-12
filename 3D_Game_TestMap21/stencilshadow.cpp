// =====================================================================================================================================================================
//
// ステンシルシャドウの処理 [stencilshadow.cpp]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#include "stencilshadow.h"			// インクルードファイル
#include "debugproc.h"
#include "manager.h"
#include "renderer.h"
#include "map.h"
#include "camera.h"
#include "player.h"
#include "game.h"
#include "scene2Dnew.h"

// =====================================================================================================================================================================
// マクロ定義
// =====================================================================================================================================================================
#define MODEL_FILE01				"data/OBJECT/stensileshadow.x"				// 円柱

#define TEXTURE_FILE01				"data/TEXTURE/ston.jpg"						// 円柱

#define RESIDUAL_ERROR				(0.4f)										// 誤差
#define OBJECT_MOVE_X				(0.7f)										// 移動オブジェクトの移動量

// =====================================================================================================================================================================
// 静的メンバ変数の初期化
// =====================================================================================================================================================================
MODEL_DRAWINFO		CStencilShadow::m_ModelDrawInfo	= {};
LPDIRECT3DTEXTURE9	CStencilShadow::m_pTexture		= {};
CScene2Dnew			*CStencilShadow::m_pScene2Dnew = {};

// =====================================================================================================================================================================
//
// コンストラクタ
//
// =====================================================================================================================================================================
CStencilShadow::CStencilShadow():CSceneX(PRIORITY_MODEL)
{
}

// =====================================================================================================================================================================
//
// デストラクタ
//
// =====================================================================================================================================================================
CStencilShadow::~CStencilShadow()
{
}

// =====================================================================================================================================================================
//
// 初期化処理
//
// =====================================================================================================================================================================
void CStencilShadow::Init(void)
{
	m_posOld	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);					 // 過去の位置
	m_move		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);					 // 移動
	m_VtxMin	= D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);			 // 最小頂点
	m_VtxMax	= D3DXVECTOR3(-1000.0f, -1000.0f, -1000.0f);		 // 最大頂点

	// 最大・最小頂点の設定
	CLibrary::SetVertexObject(&m_VtxMin, &m_VtxMax, m_ModelDrawInfo.Mesh);

	// モデル描画情報の設定
	SetModelDraw(&m_ModelDrawInfo);

	//m_pScene2Dnew = CScene2Dnew::Create();
	//m_pScene2Dnew->Init();
	//m_pScene2Dnew->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
	//m_pScene2Dnew->SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//m_pScene2Dnew->SetSize(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));

	// 初期化
	CSceneX::Init();
}

// =====================================================================================================================================================================
//
// 終了処理
//
// =====================================================================================================================================================================
void CStencilShadow::Uninit(void)
{
	CSceneX::Uninit();
}

// =====================================================================================================================================================================
//
// 更新処理
//
// =====================================================================================================================================================================
void CStencilShadow::Update(void)
{
	// プレイヤーの情報取得
	CPlayer *pPlayer = CManager::GetGame()->GetPlayer();

	// 位置の取得
	D3DXVECTOR3 pos = CSceneX::GetPos();

	// プレイヤーの位置に合わせる
	pos = pPlayer->GetOldPos();

	// 位置保存
	m_posOld = pos;

	// 位置更新
	pos += m_move;

	// 位置の設定
	CSceneX::SetPos(pos);

	// 更新
	CSceneX::Update();

	//m_pScene2Dnew->Update();
}

// =====================================================================================================================================================================
//
// 描画処理
//
// =====================================================================================================================================================================
void CStencilShadow::Draw(void)
{
	D3DXMATRIX			mtxWorld;
	LPDIRECT3DDEVICE9 pDevice = *CManager::GetRenderer()->GetDevice();	// デバイスの取得

	pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);					// ステンシルバッファを有効にする

	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0);					// 色情報を0に
	pDevice->SetRenderState(D3DRS_STENCILREF, 0);						// ステンシル参照値(0)

	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);			// ステンシルの対象
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILCAPS_ZERO);	// ステンシルZテスト共に合格している
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILCAPS_INCR);	// ステンシルテストに合格、Zテストに不合格
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILCAPS_ZERO);	// ステンシルテストに不合格

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);				// 表面カリング設定
	//モデルの描画
	DrawModel();

	pDevice->SetRenderState(D3DRS_STENCILREF, 1);						// ステンシル参照値(1)

	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);			// ステンシルの対象
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILCAPS_INCR);	// ステンシルZテスト共に合格している
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILCAPS_ZERO);	// ステンシルテストに合格、Zテストに不合格
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILCAPS_ZERO);	// ステンシルテストに不合格

	// ワールドマトリックスの計算
	CLibrary::MatrixCalculation(&mtxWorld, GetRot(), GetPos());

	//計算後マトリックス設定
	SetMatrix(mtxWorld);

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// 裏面カリング設定
	//モデルの描画
	DrawModel();

	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0xf);				// 色をデフォルト値に戻す
	pDevice->SetRenderState(D3DRS_STENCILREF, 2);						// ステンシル参照値(2)

	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);			// ステンシルの対象
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILCAPS_KEEP);	// ステンシルZテスト共に合格している
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILCAPS_KEEP);	// ステンシルテストに合格、Zテストに不合格
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILCAPS_ZERO);	// ステンシルテストに不合格

	//モデルの描画
	DrawModel();

	//m_pScene2Dnew->Draw();

	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);			// ステンシルバッファを無効にする
}

// =====================================================================================================================================================================
//
// ステンシルシャドウの生成
//
// =====================================================================================================================================================================
CStencilShadow * CStencilShadow::Create()
{
	// 変数
	CStencilShadow *pStencilShadow;

	// メモリの確保
	pStencilShadow = new CStencilShadow;

	// 初期化
	pStencilShadow->Init();

	// テクスチャの割り当て
	pStencilShadow->BindTexture(m_pTexture);

	return pStencilShadow;
}

// =====================================================================================================================================================================
//
// ロード
//
// =====================================================================================================================================================================
HRESULT CStencilShadow::Load(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = *CManager::GetRenderer()->GetDevice();

	// Xファイルの読み込み
	D3DXLoadMeshFromX(MODEL_FILE01, D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_ModelDrawInfo.BuffMat, NULL, &m_ModelDrawInfo.nNumMat, &m_ModelDrawInfo.Mesh);

	// テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, TEXTURE_FILE01, &m_pTexture);

	return S_OK;
}

// =====================================================================================================================================================================
//
// アンロード
//
// =====================================================================================================================================================================
void CStencilShadow::Unload(void)
{
		// テクスチャの開放
		if (m_pTexture != NULL)
		{
			m_pTexture->Release();
			m_pTexture = NULL;
		}
}

//// =====================================================================================================================================================================
////
//// オブジェクトの当たり判定
////
//// =====================================================================================================================================================================
//bool CStencilShadow::CollisionObject(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 *pSize, CObjectModel **ppObjectRet)
//{
//	// カメラの取得
//	CCamera *pCamera;
//	pCamera = CManager::GetRenderer()->GetCamera();
//	// 位置の取得
//	D3DXVECTOR3 pos = CSceneX::GetPos();
//	bool bLand = false;							// 着地の判定
//
//	// NULLチェック
//	if (ppObjectRet != NULL)
//	{
//		*ppObjectRet = NULL;
//	}
//
//	// ブロックの範囲 ( 横 )
//	if ((m_VtxMin.x + pos.x < pPos->x + pSize->x &&
//		m_VtxMax.x + pos.x > pPos->x - pSize->x) || 
//		(pCamera->GetCameraMode() == CCamera::CAMERA_MODE_2D &&
//		m_ObjectType == CObjectModel::OBJECTTYPE_SCAFFOLD_HIT))
//	{
//		// ブロックの範囲 ( 縦 )
//		if (m_VtxMin.z + pos.z < pPos->z + pSize->z &&
//			m_VtxMax.z + pos.z > pPos->z - pSize->z)
//		{
//			// ブロックの範囲 ( 高さ )
//			if (m_VtxMin.y + pos.y <= pPos->y + pSize->y &&
//				m_VtxMax.y + pos.y > pPos->y)
//			{
//				// 上の当たり判定
//				if (pPos->y < m_VtxMax.y + pos.y &&
//					pPosOld->y + RESIDUAL_ERROR >= m_VtxMax.y + m_posOld.y)
//				{
//					pMove->y = 0;
//					pPos->y = m_VtxMax.y + pos.y;
//					pPos->x += m_move.x;
//
//					bLand = true;
//					*ppObjectRet = this;
//				}
//
//				// 前の当たり判定
//				else if (pPos->z + pSize->z > m_VtxMin.z + pos.z &&
//					pPosOld->z + pSize->z < m_VtxMin.z + pos.z)
//				{
//					pPos->z = m_VtxMin.z + pos.z - pSize->z - RESIDUAL_ERROR;
//					pMove->z = 0;
//				}
//
//				// 後ろの当たり判定
//				else if (pPos->z - pSize->z < m_VtxMax.z + pos.z &&
//					pPosOld->z - pSize->z >= m_VtxMax.z + m_posOld.z)
//				{
//					pPos->z = m_VtxMax.z + pos.z + pSize->z + RESIDUAL_ERROR;
//					pMove->z = 0;
//				}
//
//				// 左の当たり判定
//				else if (pPos->x + pSize->x > m_VtxMin.x + pos.x &&
//					pPosOld->x + pSize->x <= m_VtxMin.x + m_posOld.x)
//				{
//					pPos->x = m_VtxMin.x + pos.x - pSize->x - RESIDUAL_ERROR;
//					pMove->x = 0;
//				}
//				// 右の当たり判定
//				else if (pPos->x - pSize->x < m_VtxMax.x + pos.x &&
//					pPosOld->x - pSize->x >= m_VtxMax.x + m_posOld.x)
//				{
//					pPos->x = m_VtxMax.x + pos.x + pSize->x + RESIDUAL_ERROR;
//					pMove->x = 0;
//				}
//
//				// 下の当たり判定
//				else if (pPos->y + pSize->y > m_VtxMin.y + pos.y &&
//					pPosOld->y + pSize->y <= m_VtxMin.y + m_posOld.y)
//				{
//					pPos->y = m_VtxMin.y + pos.y - pSize->y - RESIDUAL_ERROR;
//					pMove->y = 0;
//				}
//				else
//				{
//					pMove->y = 0.0f;
//					pPos->y = m_VtxMax.y + pos.y;
//					pPos->x += m_move.x;
//
//					bLand = true;
//					*ppObjectRet = this;
//				}
//			}
//		}
//	}
//	return bLand;
//}