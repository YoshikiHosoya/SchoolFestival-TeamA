// =====================================================================================================================================================================
//
// パーツモデルの処理 [partsmodel.cpp]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#include "partsmodel.h"			// インクルードファイル
#include "debugproc.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "motion.h"

// =====================================================================================================================================================================
// マクロ定義
// =====================================================================================================================================================================
#define MODEL_FILE00				"data/MODEL/body.x"							// 読み込むプレイヤーファイル名			 体
#define MODEL_FILE01				"data/MODEL/waist.x"						// 読み込むプレイヤーファイル名			 腰
#define MODEL_FILE02				"data/MODEL/head.x"							// 読み込むプレイヤーファイル名			 頭
#define MODEL_FILE03				"data/MODEL/arm.R.x"						// 読み込むプレイヤーファイル名			 右腕
#define MODEL_FILE04				"data/MODEL/hand.R.x"						// 読み込むプレイヤーファイル名			 右手
#define MODEL_FILE05				"data/MODEL/arm.L.x"						// 読み込むプレイヤーファイル名			 左腕
#define MODEL_FILE06				"data/MODEL/hand.L.x"						// 読み込むプレイヤーファイル名			 左手
#define MODEL_FILE07				"data/MODEL/thigh.R.x"						// 読み込むプレイヤーファイル名			 右腿
#define MODEL_FILE08				"data/MODEL/leg.R.x"						// 読み込むプレイヤーファイル名			 右脚
#define MODEL_FILE09				"data/MODEL/foot.R.x"						// 読み込むプレイヤーファイル名			 右足首
#define MODEL_FILE010				"data/MODEL/thigh.L.x"						// 読み込むプレイヤーファイル名			 左腿
#define MODEL_FILE011				"data/MODEL/leg.L.x"						// 読み込むプレイヤーファイル名			 左脚
#define MODEL_FILE012				"data/MODEL/foot.L.x"						// 読み込むプレイヤーファイル名			 左足首

#define SPEED				(1.0f)						// 移動速度

// =====================================================================================================================================================================
// 静的メンバ変数の初期化
// =====================================================================================================================================================================
MODEL_DRAWINFO		CPartsModel::m_ModelDrawInfo[PLAYER_PARTS] = {};

// =====================================================================================================================================================================
//
// コンストラクタ
//
// =====================================================================================================================================================================
CPartsModel::CPartsModel()
{
}

// =====================================================================================================================================================================
//
// デストラクタ
//
// =====================================================================================================================================================================
CPartsModel::~CPartsModel()
{
}

// =====================================================================================================================================================================
//
// 初期化処理
//
// =====================================================================================================================================================================
void CPartsModel::Init(void)
{
	m_nFrame	= 0;

	CSceneX::Init();
}

// =====================================================================================================================================================================
//
// 終了処理
//
// =====================================================================================================================================================================
void CPartsModel::Uninit(void)
{
	CSceneX::Uninit();
}

// =====================================================================================================================================================================
//
// 更新処理
//
// =====================================================================================================================================================================
void CPartsModel::Update(void)
{
	D3DXVECTOR3 rot = GetRot();

	// 更新 ( 向き )
	rot += m_Rot1F;

	// 回転の設定
	CSceneX::SetRot(rot);

	// 親のマトリックスを取得
	m_pParentMatrix = GetMatrix();
}

// =====================================================================================================================================================================
//
// 描画処理
//
// =====================================================================================================================================================================
void CPartsModel::Draw(void)
{
	D3DXMATRIX			mtxWorld;

	// ワールドマトリックスの計算
	CLibrary::MatrixCalculation(&mtxWorld, GetRot(), GetPos());

	// 親の位置分足す
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, m_pParentMatrix);

	//計算後マトリックス設定
	SetMatrix(mtxWorld);

	//モデルの描画
	DrawModel();
}

// =====================================================================================================================================================================
//
// パーツモデルの生成
//
// =====================================================================================================================================================================
CPartsModel * CPartsModel::Create()
{
	// 変数
	CPartsModel *pPartsModel;

	// メモリの確保
	pPartsModel = new CPartsModel;

	// 初期化
	pPartsModel->Init();

	return pPartsModel;
}

// =====================================================================================================================================================================
//
// インデックスの設定
//
// =====================================================================================================================================================================
void CPartsModel::SetIndex(int nIndex)
{
	m_nIndex = nIndex;

	// モデル描画情報の設定
	SetModelDraw(&m_ModelDrawInfo[m_nIndex]);
}

// =====================================================================================================================================================================
//
// プレイヤーのモーション
//
// =====================================================================================================================================================================
void CPartsModel::SetMotionPlayer(int nMotion, int nKeySet)
{
	int nMotionFrame	= CMotion::GetMotionFrame(nMotion, nKeySet);
	D3DXVECTOR3	rotDest	= CMotion::GetMotionRotDest(nMotion, nKeySet, m_nIndex);
	D3DXVECTOR3 rot		= GetRot();

	//差分 ( 向き )
	m_Rot1F = (rotDest - rot) / (float)nMotionFrame;
}

// =====================================================================================================================================================================
//
// ロード
//
// =====================================================================================================================================================================
HRESULT CPartsModel::Load(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = *CManager::GetRenderer()->GetDevice();

	// Xファイルの読み込み
	D3DXLoadMeshFromX(MODEL_FILE00, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_ModelDrawInfo[0].BuffMat, NULL, &m_ModelDrawInfo[0].nNumMat, &m_ModelDrawInfo[0].Mesh);			// 体
	D3DXLoadMeshFromX(MODEL_FILE01, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_ModelDrawInfo[1].BuffMat, NULL, &m_ModelDrawInfo[1].nNumMat, &m_ModelDrawInfo[1].Mesh);			// 腰
	D3DXLoadMeshFromX(MODEL_FILE02, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_ModelDrawInfo[2].BuffMat, NULL, &m_ModelDrawInfo[2].nNumMat, &m_ModelDrawInfo[2].Mesh);			// 頭
	D3DXLoadMeshFromX(MODEL_FILE03, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_ModelDrawInfo[3].BuffMat, NULL, &m_ModelDrawInfo[3].nNumMat, &m_ModelDrawInfo[3].Mesh);			// 右腕
	D3DXLoadMeshFromX(MODEL_FILE04, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_ModelDrawInfo[4].BuffMat, NULL, &m_ModelDrawInfo[4].nNumMat, &m_ModelDrawInfo[4].Mesh);			// 右手
	D3DXLoadMeshFromX(MODEL_FILE05, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_ModelDrawInfo[5].BuffMat, NULL, &m_ModelDrawInfo[5].nNumMat, &m_ModelDrawInfo[5].Mesh);			// 左腕
	D3DXLoadMeshFromX(MODEL_FILE06, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_ModelDrawInfo[6].BuffMat, NULL, &m_ModelDrawInfo[6].nNumMat, &m_ModelDrawInfo[6].Mesh);			// 左手
	D3DXLoadMeshFromX(MODEL_FILE07, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_ModelDrawInfo[7].BuffMat, NULL, &m_ModelDrawInfo[7].nNumMat, &m_ModelDrawInfo[7].Mesh);			// 右腿
	D3DXLoadMeshFromX(MODEL_FILE08, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_ModelDrawInfo[8].BuffMat, NULL, &m_ModelDrawInfo[8].nNumMat, &m_ModelDrawInfo[8].Mesh);			// 右脚
	D3DXLoadMeshFromX(MODEL_FILE09, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_ModelDrawInfo[9].BuffMat, NULL, &m_ModelDrawInfo[9].nNumMat, &m_ModelDrawInfo[9].Mesh);			// 右足首
	D3DXLoadMeshFromX(MODEL_FILE010, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_ModelDrawInfo[10].BuffMat, NULL, &m_ModelDrawInfo[10].nNumMat, &m_ModelDrawInfo[10].Mesh);		// 左腿
	D3DXLoadMeshFromX(MODEL_FILE011, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_ModelDrawInfo[11].BuffMat, NULL, &m_ModelDrawInfo[11].nNumMat, &m_ModelDrawInfo[11].Mesh);		// 左脚
	D3DXLoadMeshFromX(MODEL_FILE012, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_ModelDrawInfo[12].BuffMat, NULL, &m_ModelDrawInfo[12].nNumMat, &m_ModelDrawInfo[12].Mesh);		// 左足首

	return S_OK;
}

// =====================================================================================================================================================================
//
// アンロード
//
// =====================================================================================================================================================================
void CPartsModel::Unload(void)
{

}