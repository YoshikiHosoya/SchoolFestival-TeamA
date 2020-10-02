//------------------------------------------------------------------------------
//
//テクスチャアニメーション3D処理  [TexAnimation3D.h]
//Author:Fujiwara Masato
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "TexAnimation3D.h"
#include "manager.h"
#include "renderer.h"
//------------------------------------------------------------------------------
//静的メンバ変数の初期化
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//マクロ
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//コンストラクタ
//------------------------------------------------------------------------------
CTexAnimation3D::CTexAnimation3D()
{

}
//------------------------------------------------------------------------------
//コンストラクタ
//------------------------------------------------------------------------------
CTexAnimation3D::CTexAnimation3D(OBJ_TYPE obj) : CScene3D(obj)
{

}
//------------------------------------------------------------------------------
//デストラクタ
//------------------------------------------------------------------------------
CTexAnimation3D::~CTexAnimation3D()
{
}
//------------------------------------------------------------------------------
//初期化処理
//------------------------------------------------------------------------------
HRESULT CTexAnimation3D::Init()
{
	//初期化処理
	if (FAILED(CScene3D::Init()))
	{
		return E_FAIL;
	}
	return S_OK;
}
//------------------------------------------------------------------------------
//終了処理
//------------------------------------------------------------------------------
void CTexAnimation3D::Uninit()
{
	//終了処理
	CScene3D::Uninit();
}
//------------------------------------------------------------------------------
//更新処理
//------------------------------------------------------------------------------
void CTexAnimation3D::Update()
{
	//更新処理
	CScene3D::Update();

	//テクスチャアニメーションの更新
	if (CTexAnimationBase::UpdateAnimation())
	{
		//テクスチャアニメーション処理
		SetAnimation(CalcUV(), CTexture::GetSparateTex_UVSize(GetEffectTex()));
	}

	//終了のフラグが立っていた時
	if (GetEndFlag())
	{
		//消去
		//Rerease();
		return;
	}

}
//------------------------------------------------------------------------------
//描画処理
//------------------------------------------------------------------------------
void CTexAnimation3D::Draw()
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//Zテスト無効でZライティング有効
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ZTEST_OFF_ZWRITING_ON);

	//加算合成
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ALPHABLEND_ADD);

	//描画処理
	CScene3D::Draw();

	//Zテスト通常
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ZTEST_DEFAULT);

	//通常合成
	CManager::GetRenderer()->SetRendererCommand(CRenderer::REDNERER_ALPHABLEND_DEFAULT);
}
//------------------------------------------------------------------------------
//デバッグ情報表示
//------------------------------------------------------------------------------
void CTexAnimation3D::ShowDebugInfo()
{
#ifdef _DEBUG
	//CDebugProc::Print_Left("pos %.1f %.1f %.1f", GetPosition().x, GetPosition().x, GetPosition().x);
	//CDebugProc::Print_Left("col %.1f %.1f %.1f %.1f", GetColor().r, GetColor().g, GetColor().b, GetColor().a);


#endif //_DEBUG
}
//------------------------------------------------------------------------------
//生成処理
//------------------------------------------------------------------------------
void CTexAnimation3D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot,
	CTexture::SEPARATE_TEX_TYPE type, int nCntSwitch, CScene::OBJ_TYPE objtype, bool bLoop)
{
	//メモリ確保
	CTexAnimation3D *pTexAnimation = new CTexAnimation3D(objtype);

	//nullcheck
	if (pTexAnimation)
	{
		//初期化
		pTexAnimation->Init();

		//情報をいれる　Scene側
		pTexAnimation->SetPosition(pos);
		pTexAnimation->SetSize(size);
		pTexAnimation->SetRot(rot);
		pTexAnimation->BindTexture(CTexture::GetSeparateTexture(type));
		pTexAnimation->SetAnimation(ZeroVector2, CTexture::GetSparateTex_UVSize(type));
		//情報をいれる　TexAnimation側
		pTexAnimation->SetLoop(bLoop);
		pTexAnimation->SetTex(type);
		pTexAnimation->SetCntSwitch(nCntSwitch);
	}
}
