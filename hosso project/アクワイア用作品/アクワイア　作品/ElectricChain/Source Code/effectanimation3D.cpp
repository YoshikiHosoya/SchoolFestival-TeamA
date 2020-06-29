//------------------------------------------------------------------------------
//
//テクスチャアニメーション  [effectanimation.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "effectanimation3D.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"
//------------------------------------------------------------------------------
//静的メンバ変数の初期化
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//マクロ
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//コンストラクタ
//------------------------------------------------------------------------------
CEffectAnimation3D::CEffectAnimation3D()
{
	//初期化
	m_nPatternAnim = 0;
	m_nCntAnim = 0;
}
//------------------------------------------------------------------------------
//デストラクタ
//------------------------------------------------------------------------------
CEffectAnimation3D::~CEffectAnimation3D()
{
}
//------------------------------------------------------------------------------
//初期化処理
//------------------------------------------------------------------------------
HRESULT CEffectAnimation3D::Init()
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
void CEffectAnimation3D::Uninit()
{
	//終了処理
	CScene3D::Uninit();
}
//------------------------------------------------------------------------------
//更新処理
//------------------------------------------------------------------------------
void CEffectAnimation3D::Update()
{
	//カウンターを進める
	m_nCntAnim++;

	//2フレームごとに
	if (m_nCntAnim % m_nCntSwitch == 0)
	{
		//パターンを進める
		m_nPatternAnim++;

		//パターンが最後までいったら終わり
		if (m_nPatternAnim >= CTexture::GetSparateTex_UVCnt(m_Type).x *  CTexture::GetSparateTex_UVCnt(m_Type).y)
		{
			Release();
			return;
		}

		//UV座標設定
		D3DXVECTOR2 UV;
		UV.x = m_nPatternAnim % (int)CTexture::GetSparateTex_UVCnt(m_Type).x * CTexture::GetSparateTex_UVSize(m_Type).x;
		UV.y = m_nPatternAnim / (int)CTexture::GetSparateTex_UVCnt(m_Type).x * CTexture::GetSparateTex_UVSize(m_Type).y;

		//テクスチャアニメーション処理
		SetAnimation(UV, CTexture::GetSparateTex_UVSize(m_Type));
	}

	//タイプに応じて動きを変える
	switch (m_Type)
	{
		//煙
	case CTexture::SEPARATE_TEX_EFFECT_SMOKE:
		//徐々に↑へ
		GetPos().y += 2.5f;

		//徐々に拡大
		GetSize().x++;
		GetSize().y++;
		SetSize(GetSize());

		break;
	}

	//更新処理
	CScene3D::Update();
}
//------------------------------------------------------------------------------
//描画処理
//------------------------------------------------------------------------------
void CEffectAnimation3D::Draw()
{
	//タイプに応じて描画方法を設定
	//煙と敵出現は黒くする
	if (m_Type == CTexture::SEPARATE_TEX_EFFECT_SMOKE || m_Type == CTexture::SEPARATE_TEX_EFFECT_ENEMY_RESPAWN)
	{
		//減算合成
		CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ALPHABLEND_SUB);
	}
	else
	{
		//加算合成
		CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ALPHABLEND_ADD);
	}

	//Zテスト無効でZライティング有効
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ZTEST_OFF_ZWRITING_ON);

	//マトリックス計算
	D3DXMATRIX *pMtx = CScene3D::GetMtxPtr();
	CHossoLibrary::CalcMatrix(pMtx, GetPos(), GetRot());
	CHossoLibrary::SetBillboard_XZ_Only(pMtx);

	//描画処理
	CScene3D::DrawSettingMtx(*pMtx);

	//Zテスト通常
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ZTEST_DEFAULT);

	//通常合成
	CManager::GetRenderer()->SetRendererCommand(CRenderer::REDNERER_ALPHABLEND_DEFAULT);
}
//------------------------------------------------------------------------------
//デバッグ情報表示
//------------------------------------------------------------------------------
void CEffectAnimation3D::ShowDebugInfo()
{
#ifdef _DEBUG

#endif //_DEBUG
}

//------------------------------------------------------------------------------
//生成処理
//------------------------------------------------------------------------------
void CEffectAnimation3D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, CTexture::SEPARATE_TEX_TYPE type , D3DXCOLOR col, float fAngle, int nCntSwitch)
{
	//変数宣言
	std::unique_ptr<CEffectAnimation3D> pEffectAnimation3D (new CEffectAnimation3D);

	//3Dアニメーション
	if (pEffectAnimation3D)
	{
		//初期化
		pEffectAnimation3D->Init();

		//情報を入れる
		pEffectAnimation3D->BindTexture(CTexture::GetSeparateTexture(type));
		pEffectAnimation3D->m_Type = type;
		pEffectAnimation3D->SetPos(pos);
		pEffectAnimation3D->SetRot(D3DXVECTOR3(0.0f, 0.0f, fAngle));
		pEffectAnimation3D->SetSize(size);
		pEffectAnimation3D->SetVtxCol(col);
		pEffectAnimation3D->SetAnimation(ZeroVector2, CTexture::GetSparateTex_UVSize(type));
		pEffectAnimation3D->SetBboard(true);
		pEffectAnimation3D->m_nCntSwitch = nCntSwitch;

		//Sceneで管理
		pEffectAnimation3D->SetObjType(OBJTYPE_EFFECT);
		pEffectAnimation3D->AddUniqueList(std::move(pEffectAnimation3D));

	}
}
