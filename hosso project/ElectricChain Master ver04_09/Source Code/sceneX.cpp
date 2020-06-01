//------------------------------------------------------------------------------
//
//Xファイルモデル処理  [SceneX.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "sceneX.h"
#include "renderer.h"
#include "manager.h"
#include "keyboard.h"
#include "light.h"
#include "modelinfo.h"
#include "meshcylinder.h"
//------------------------------------------------------------------------------
//静的メンバ変数の初期化
//------------------------------------------------------------------------------
int CSceneX::m_nNumSceneX = 0;

std::vector<D3DMATERIAL9> CSceneX::m_MaterialColor[CSceneX::MAT_MAX] ={};

//------------------------------------------------------------------------------
//マクロ
//------------------------------------------------------------------------------
#define SHADOW_COLOR (D3DXCOLOR(0.0f,0.0f,0.0f,0.5f))

//------------------------------------------------------------------------------
//コンストラクタ
//------------------------------------------------------------------------------
CSceneX::CSceneX()
{
	//初期化
	m_pos = ZeroVector3;
	m_rot = ZeroVector3;
	m_SceneXInfo = nullptr;
	m_MatCol = MAT_NORMAL;

	//総数加算
	m_nNumSceneX++;
}

//------------------------------------------------------------------------------
//デストラクタ
//------------------------------------------------------------------------------
CSceneX::~CSceneX()
{
	//ポインタの開放
	m_SceneXInfo = nullptr;

	//総数減算
	m_nNumSceneX--;
}
//------------------------------------------------------------------------------
//初期化処理
//------------------------------------------------------------------------------
HRESULT CSceneX::Init()
{
	//シェーダー設定
	m_pShader = CShader::Create();
	m_pShader->SetType(CShader::SHADER_MODELDRAW);

	return S_OK;
}
//------------------------------------------------------------------------------
//終了処理
//------------------------------------------------------------------------------
void CSceneX::Uninit()
{
}
//------------------------------------------------------------------------------
//更新処理
//------------------------------------------------------------------------------
void CSceneX::Update()
{
}
//------------------------------------------------------------------------------
//描画処理
//------------------------------------------------------------------------------
void CSceneX::Draw()
{
	//マトリックス計算
	CHossoLibrary::CalcMatrix(&m_mtxWorld, m_pos, m_rot);

	//メッシュ描画
	DrawMesh();
}
//------------------------------------------------------------------------------
//シェーダで描画
//------------------------------------------------------------------------------
void CSceneX::DrawShader()
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//マテリアル
	D3DXMATERIAL		*pMat;

	//シェーダーに情報を設定する
	m_pShader->GetEffectPtr()->SetMatrix("g_WorldMatrix", &m_mtxWorld);
	//m_pShader->GetEffectPtr()->SetTexture("pTex", CTexture::GetTexture(CTexture::TEX_MESH_FIELD));

	// マテリアル情報に対するポインタを取得
	pMat = (D3DXMATERIAL*)m_SceneXInfo->GetMatBuff()->GetBufferPointer();

	//シェーダーの描画開始
	// 描画開始
	m_pShader->GetEffectPtr()->SetTechnique("BasicTec");
	m_pShader->GetEffectPtr()->Begin(0, 0);
		m_pShader->GetEffectPtr()->BeginPass(0);

	for (int nCntMat = 0; nCntMat < (int)m_SceneXInfo->GetMatNum(); nCntMat++)
	{
		////描画用のマテリアル取得
		//D3DXCOLOR DiffuseCol = pMat[nCntMat].MatD3D.Diffuse;
		//float Power = pMat[nCntMat].MatD3D.Power;
		//D3DXCOLOR EmissiveCol = pMat[nCntMat].MatD3D.Emissive;
		//D3DXCOLOR SpecularCol = pMat[nCntMat].MatD3D.Specular;
		//D3DXCOLOR Ambient = pMat[nCntMat].MatD3D.Ambient;

		//DiffuseCol = D3DXCOLOR(1, 1, 1, 1);
		//m_pShader->SetModelColor(DiffuseCol, SpecularCol, EmissiveCol, Ambient, Power);

		//m_pShader->GetEffectPtr()->SetVector("g_DiffuseColor", &D3DXVECTOR4(DiffuseCol));
		//m_pShader->GetEffectPtr()->SetVector("g_SpecularColor", &D3DXVECTOR4(SpecularCol));
		//m_pShader->GetEffectPtr()->SetVector("g_EmissiveColor", &D3DXVECTOR4(EmissiveCol));
		//m_pShader->GetEffectPtr()->SetVector("g_Ambient", &D3DXVECTOR4(Ambient));
		//m_pShader->GetEffectPtr()->SetFloat("g_Power", Power);

		//m_pShader->GetEffectPtr()->CommitChanges();


		// マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		// 描画
		m_SceneXInfo->GetMesh()->DrawSubset(nCntMat);


	}
		m_pShader->GetEffectPtr()->EndPass();
	m_pShader->GetEffectPtr()->End();
	//シェーダの描画終了

	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ZTEST_DEFAULT);

	////頂点情報へのポインタ
	//VERTEX_3D *pVtx;

	//LPDIRECT3DVERTEXBUFFER9 vertex;

	////頂点データの範囲をロックし、頂点バッファへのポインタを取得
	//m_SceneXInfo->GetMesh()->LockVertexBuffer(0, (void**)&pVtx);


	//for (int nCnt = 0; nCnt < m_SceneXInfo->GetMesh()->GetNumVertices(); nCnt++)
	//{
	//	//pVtx[0].col = BlueColor;
	//	pVtx->pos;
	//	pVtx++;
	//}

	////頂点データアンロック
	//m_SceneXInfo->GetMesh()->UnlockVertexBuffer();

}

//------------------------------------------------------------------------------
//頂点情報を元にメッシュの描画
//------------------------------------------------------------------------------
void CSceneX::DrawMesh()
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATERIAL		*pMat;
	D3DMATERIAL9		matDef;
	D3DMATERIAL9		DrawMat;

	//テクスチャの設定
	pDevice->SetTexture(0, NULL);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// 現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	// マテリアル情報に対するポインタを取得
	pMat = (D3DXMATERIAL*)m_SceneXInfo->GetMatBuff()->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_SceneXInfo->GetMatNum(); nCntMat++)
	{
		//描画用のマテリアル取得
		DrawMat = pMat[nCntMat].MatD3D;

		// マテリアルの設定
		pDevice->SetMaterial(&DrawMat);

		// 描画
		m_SceneXInfo->GetMesh()->DrawSubset(nCntMat);
	}
	// マテリアルをデフォルトに戻す
	pDevice->SetMaterial(&matDef);
}


//------------------------------------------------------------------------------
//影のマトリックス描画
//------------------------------------------------------------------------------
void CSceneX::DrawShadow()
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATERIAL		*pMat;
	D3DMATERIAL9		matDef;
	D3DMATERIAL9		matBlack;

	// 現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	//初期化
	matBlack = matDef;

	//黒設定
	matBlack.Diffuse = SHADOW_COLOR;

	// マテリアル情報に対するポインタを取得
	pMat = (D3DXMATERIAL*)m_SceneXInfo->GetMatBuff()->GetBufferPointer();

	//ステンシル有効　0のところにのみ描画可能
	pDevice->SetRenderState(D3DRS_STENCILREF, 0);					//ステンシルの条件の値
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);		//ステンシルの条件 ==
	pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);				//ステンシル･バッファ有効

	for (int nCntMat = 0; nCntMat < (int)m_SceneXInfo->GetMatNum(); nCntMat++)
	{
		//ステンシル設定
		pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCR);

		// マテリアルの設定
		pDevice->SetMaterial(&matBlack);

		// 描画
		m_SceneXInfo->GetMesh()->DrawSubset(nCntMat);
	}

	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);	// ステンシル･バッファ無効

	// マテリアルをデフォルトに戻す
	pDevice->SetMaterial(&matDef);
}
//------------------------------------------------------------------------------
//ステンシルシャドウ
//------------------------------------------------------------------------------
void CSceneX::DrawStencilShadow()
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//ステンシルバッファ有効
	pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);

	//Zバッファ書き込み禁止
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ZTEST_ON_ZWRITING_OFF);



	//色描画しない
	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0x00000000);

	//シリンダー生成
	std::shared_ptr<CMeshCylinder> pCylinder = CMeshCylinder::Create(D3DXVECTOR3(0.0f,-200.0f,0.0f), D3DXVECTOR3(30.0f, 200.0f, 30.0f), INTEGER2(16, 4), &m_mtxWorld);




	//表面カリング
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_CULLING_CW);

	//ステンシル条件
	pDevice->SetRenderState(D3DRS_STENCILREF, 0);					//ステンシルの条件の値
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);		//ステンシルの条件 ==
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_ZERO);	//ステンシルZテスト共に合格している時　0
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_ZERO);	//ステンシルテストに不合格の時　0
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_INCR);	//ステンシルに合格、Zテストに不合格 インクリメント

	//色
	pCylinder->SetCol(D3DXCOLOR(0.8f, 0.0f, 0.0f, 0.0f));

	//描画
	pCylinder->DrawShadowMesh();





	//裏面カリング
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_CULLING_CCW);

	//色設定
	pCylinder->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.8f, 0.0f));

	//ステンシル条件
	pDevice->SetRenderState(D3DRS_STENCILREF, 1);					//ステンシルの条件の値
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);		//ステンシルの条件 ==
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCR);	//ステンシルZテスト共に合格している時　インクリメント
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_ZERO);	//ステンシルテストに不合格の時　0
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_ZERO);	//ステンシルに合格、Zテストに不合格 0


	//描画
	pCylinder->DrawShadowMesh();


	//裏面カリング
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_CULLING_CCW);

	//色の描画設定を元に戻す
	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0x0000000f);


	//色設定
	pCylinder->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f));

	//ステンシル条件
	pDevice->SetRenderState(D3DRS_STENCILREF, 2);						//ステンシルの条件の値
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);			//ステンシルの条件 ==
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILCAPS_KEEP);	//ステンシルZテスト共に合格している時 特に何もしない
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILCAPS_KEEP);	//ステンシルテストに不合格の時　0
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILCAPS_KEEP);	//ステンシルに合格、Zテストに不合格 0

	//描画
	pCylinder->DrawShadowMesh();

	//Zテストを元に戻す
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ZTEST_DEFAULT);

	//カリングを元に戻す
	CHossoLibrary::CheckCulling();

	//ステンシルバッファ無効
	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);

	//シリンダー破棄
	pCylinder->Release();
	pCylinder = nullptr;
}
//------------------------------------------------------------------------------
//デバッグ情報表記
//------------------------------------------------------------------------------
void CSceneX::ShowDebugInfo()
{
#ifdef _DEBUG

#endif //DEBUG
}


//------------------------------------------------------------------------------
//生成処理
//------------------------------------------------------------------------------
CSceneX * CSceneX::Create(D3DXVECTOR3 pos, OBJTYPE objtype)
{
	//変数宣言
	CSceneX *pSceneX;

	//メモリ確保
	pSceneX = new CSceneX();

	//初期化
	pSceneX->Init();

	//座標とサイズ設定
	pSceneX->SetPos(pos);

	//オブジェクトタイプ設定
	pSceneX->SetObjType(objtype);

	//生成した情報
	return pSceneX;
}
