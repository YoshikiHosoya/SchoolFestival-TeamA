//------------------------------------------------------------------------------
//
//円のエフェクト処理  [circle_effect.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "renderer.h"
#include "manager.h"
#include "circle_effect.h"
//------------------------------------------------------------------------------
//マクロ
//------------------------------------------------------------------------------
#define BLOCK_NUM			(INTEGER2(8,8))						//メッシュのブロック数
#define EXPLOSION_DAMAGE	(35)									//爆発ダメージ
//------------------------------------------------------------------------------
//静的メンバ変数の初期化
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//コンストラクタ
//------------------------------------------------------------------------------
CCircle_Effect::CCircle_Effect()
{
	//初期化
	m_nLife = 0;
	m_fAlphaDampingValue = 0.0f;
	m_fRadiusAddValue = 0.0f;
	m_fWidthAddValue = 0.0f;
}

//------------------------------------------------------------------------------
//デストラクタ
//------------------------------------------------------------------------------
CCircle_Effect::~CCircle_Effect()
{

}
//------------------------------------------------------------------------------
//初期化処理
//------------------------------------------------------------------------------
HRESULT CCircle_Effect::Init()
{
	CMeshCircle::Init();

	return S_OK;

}
//------------------------------------------------------------------------------
//終了処理
//------------------------------------------------------------------------------
void CCircle_Effect::Uninit()
{
	CMeshCircle::Uninit();
}
//------------------------------------------------------------------------------
//更新処理
//------------------------------------------------------------------------------
void CCircle_Effect::Update()
{
	//ライフが0になったら消去
	if (m_nLife-- <= 0)
	{
		Release();
	}

	//回転
	GetRot().y += 0.1f;

	//拡縮
	GetRadius() += m_fRadiusAddValue;
	GetWidth() += m_fWidthAddValue;

	//頂点再設定
	ResetVtx(ZeroVector3);

	//色情報取得
	D3DXCOLOR rCol = GetCol();
	rCol.a -= m_fAlphaDampingValue;

	//a値が0になったら終了
	if (rCol.a < 0)
	{
		Release();
		return;
	}
	//色設定
	SetCol(rCol);

	//スフィア更新
	CMeshCircle::Update();
}
//------------------------------------------------------------------------------
//描画処理
//------------------------------------------------------------------------------
void CCircle_Effect::Draw()
{
	//ライティングOFF
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_LIGHTING_OFF);

	//両面描画
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_CULLING_NONE);

	//加算合成
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ALPHABLEND_ADD);

	//Zテスト無効でZライティング有効
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ZTEST_ON_ZWRITING_OFF);

	//描画
	CMeshCircle::Draw();

	//Zテスト通常
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ZTEST_DEFAULT);

	//通常合成
	CManager::GetRenderer()->SetRendererCommand(CRenderer::REDNERER_ALPHABLEND_DEFAULT);

	//カリングを元に戻す
	CHossoLibrary::CheckCulling();

	//を元に戻す
	CHossoLibrary::CheckLighting();
}
//------------------------------------------------------------------------------
//デバッグ情報表記
//------------------------------------------------------------------------------
void CCircle_Effect::ShowDebugInfo()
{
#ifdef _DEBUG

#endif //DEBUG
}
//------------------------------------------------------------------------------
//生成
//------------------------------------------------------------------------------
std::shared_ptr<CCircle_Effect> CCircle_Effect::Create(D3DXVECTOR3 const pos, D3DXCOLOR col, int const nLife, float const fRadius, float const fWidth, int const nSeparate,
														float const fRaidiusAddValue, float const fWidthAddValue, float const fAlphaDanpingValue)
{
	//メモリ確保
	std::shared_ptr<CCircle_Effect> pCircleEffect(new CCircle_Effect);

	//nullcheck
	if (pCircleEffect)
	{
		//初期化　情報設定
		pCircleEffect->Init();
		pCircleEffect->SetPos(pos);
		pCircleEffect->SetBlockNum(BLOCK_NUM);
		pCircleEffect->SetRadius(fRadius);
		pCircleEffect->SetWidth(fWidth);
		pCircleEffect->SetBlockNum(INTEGER2(nSeparate, 2));
		pCircleEffect->m_fAlphaDampingValue = fAlphaDanpingValue;
		pCircleEffect->m_fWidthAddValue = fWidthAddValue;
		pCircleEffect->m_fRadiusAddValue = fRaidiusAddValue;
		pCircleEffect->m_nLife = nLife;

		//頂点設定
		pCircleEffect->MakeVertex();
		pCircleEffect->SetNormal();

		//色設定
		pCircleEffect->SetCol(col);

		//角度ランダム
		pCircleEffect->GetRot().y = CHossoLibrary::Random_PI();

		//マトリックスの計算　このFでしか使わない
		CHossoLibrary::CalcMatrix(pCircleEffect->GetMtx(), pCircleEffect->GetPos(), pCircleEffect->GetRot());

		//テクスチャ張り付け
		pCircleEffect->BindTexture(CTexture::GetTexture(CTexture::TEX_SPHEREEXPLOISON));

		//シーンに追加
		pCircleEffect->SetObjType(OBJTYPE_EFFECT_SPHERE);
		pCircleEffect->AddSharedList(pCircleEffect);

		//頂点更新
		pCircleEffect->Update();
	}

	return pCircleEffect;
}