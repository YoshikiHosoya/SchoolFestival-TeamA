// =====================================================================================================================================================================
//
// シーン3Dの処理 [scene3D.cpp]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#include "sceneX.h"			// インクルードファイル
#include "renderer.h"
#include "manager.h"
#include "debugproc.h"
#include "camera.h"
#include "keyboard.h"
#include "scene3D.h"
#include "meshfield.h"
#include "game.h"

// =====================================================================================================================================================================
// マクロ定義
// =====================================================================================================================================================================
#define TEX_POSX			(640)			// 画像のx座標
#define TEX_POSY			(360)			// 画像のy座標
#define TEX_SIZEX			(300 / 2)		// 座標の幅
#define TEX_SIZEY			(220 / 2)		// 座標の高さ

#define SPEED				(1.0f)			// 移動速度

// =====================================================================================================================================================================
// 静的メンバ変数の初期化
// =====================================================================================================================================================================

// =====================================================================================================================================================================
//
// コンストラクタ
//
// =====================================================================================================================================================================
CSceneX::CSceneX()
{
}

// =====================================================================================================================================================================
//
// コンストラクタ
//
// =====================================================================================================================================================================
CSceneX::CSceneX(PRIORITY Priority) : CScene(Priority)
{
}

// =====================================================================================================================================================================
//
// デストラクタ
//
// =====================================================================================================================================================================
CSceneX::~CSceneX()
{
}

// =====================================================================================================================================================================
//
// 初期化処理
//
// =====================================================================================================================================================================
void CSceneX::Init(void)
{
	// 初期化
	m_pos		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);								// 位置
	m_size		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);								// 位置
	m_rot		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);								// 回転
}

// =====================================================================================================================================================================
//
// 終了処理
//
// =====================================================================================================================================================================
void CSceneX::Uninit(void)
{
}

// =====================================================================================================================================================================
//
// 更新処理
//
// =====================================================================================================================================================================
void CSceneX::Update(void)
{
}

// =====================================================================================================================================================================
//
// 描画処理
//
// =====================================================================================================================================================================
void CSceneX::Draw(void)
{	
	// ワールドマトリックスの計算
	CLibrary::MatrixCalculation(&m_mtxWorld, m_rot, m_pos);

	// モデルの描画
	DrawModel();
}

// =====================================================================================================================================================================
//
// 画像の設定
//
// =====================================================================================================================================================================
void CSceneX::SetTexture(char TexName[])
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = *CManager::GetRenderer()->GetDevice();

	// テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, TexName, &m_pTexture);
}

// =====================================================================================================================================================================
//
// 画像の代入
//
// =====================================================================================================================================================================
void CSceneX::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}

// =====================================================================================================================================================================
//
// モデルの描画
//
// =====================================================================================================================================================================
void CSceneX::DrawModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = *CManager::GetRenderer()->GetDevice();

	D3DXMATERIAL		*pMat;							// 現在のマテリアル保存用
	D3DMATERIAL9		matDef;							// マテリアルデータへのポインタ

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
	// 現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);
	// マテリアル情報に対するポインタを取得
	pMat = (D3DXMATERIAL*)m_pModelDrawInfo->BuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_pModelDrawInfo->nNumMat; nCntMat++)
	{
		// マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		// テクスチャ設定
		pDevice->SetTexture(0, m_pTexture);

		// 描画
		m_pModelDrawInfo->Mesh->DrawSubset(nCntMat);
	}

	// マテリアルをデフォルトに戻す
	pDevice->SetMaterial(&matDef);
}

// =====================================================================================================================================================================
//
// モデルの生成
//
// =====================================================================================================================================================================
CSceneX * CSceneX::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// 変数
	CSceneX *pSceneX;

	// メモリの確保
	pSceneX = new CSceneX(CScene::PRIORITY_MODEL);

	// 初期化
	pSceneX->Init();

	pSceneX->SetPos(pos);

	return pSceneX;
}