//------------------------------------------------------------------------------
//
//エフェクトアニメーション2D処理  [effectanimation2D.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "effectanimation2D.h"
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
CEffectAnimation2D::CEffectAnimation2D()
{
	//初期化
	m_nPatternAnim = 0;
	m_nCntAnim = 0;
}
//------------------------------------------------------------------------------
//デストラクタ
//------------------------------------------------------------------------------
CEffectAnimation2D::~CEffectAnimation2D()
{
}
//------------------------------------------------------------------------------
//初期化処理
//------------------------------------------------------------------------------
HRESULT CEffectAnimation2D::Init()
{
	//初期化処理
	if (FAILED(CScene2D::Init()))
	{
		return E_FAIL;
	}
	return S_OK;
}
//------------------------------------------------------------------------------
//終了処理
//------------------------------------------------------------------------------
void CEffectAnimation2D::Uninit()
{
	//終了処理
	CScene2D::Uninit();
}
//------------------------------------------------------------------------------
//更新処理
//------------------------------------------------------------------------------
void CEffectAnimation2D::Update()
{
	//カウンターを進める
	m_nCntAnim++;

	//2フレームごとに
	if (m_nCntAnim % m_nCntSwitch == 0)
	{
		//パターンを進める
		m_nPatternAnim++;

		//最後のパターンまで進んだ時
		if (m_nPatternAnim >= CTexture::GetSparateTex_UVCnt(m_Type).x *  CTexture::GetSparateTex_UVCnt(m_Type).y)
		{
			//開放
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

	//更新処理
	CScene2D::Update();
}
//------------------------------------------------------------------------------
//描画処理
//------------------------------------------------------------------------------
void CEffectAnimation2D::Draw()
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//Zテスト無効でZライティング有効
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ZTEST_OFF_ZWRITING_ON);

	//加算合成
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ALPHABLEND_ADD);

	//描画処理
	CScene2D::Draw();

	//Zテスト通常
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ZTEST_DEFAULT);

	//通常合成
	CManager::GetRenderer()->SetRendererCommand(CRenderer::REDNERER_ALPHABLEND_DEFAULT);
}
//------------------------------------------------------------------------------
//デバッグ情報表示
//------------------------------------------------------------------------------
void CEffectAnimation2D::ShowDebugInfo()
{
#ifdef _DEBUG

#endif //_DEBUG
}
//------------------------------------------------------------------------------
//生成処理
//------------------------------------------------------------------------------
void CEffectAnimation2D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, CTexture::SEPARATE_TEX_TYPE type, float fAngle, int nCntSwitch, OBJTYPE objtype)
{
	//メモリ確保
	std::unique_ptr<CEffectAnimation2D> pEffectAnimation(new CEffectAnimation2D);

	//nullcheck
	if (pEffectAnimation)
	{
		//初期化
		pEffectAnimation->Init();

		//初期化
		pEffectAnimation->m_Type = type;
		pEffectAnimation->BindTexture(CTexture::GetSeparateTexture(type));
		pEffectAnimation->SetPos(pos);
		pEffectAnimation->SetSize(size);
		pEffectAnimation->SetAnimation(ZeroVector2, CTexture::GetSparateTex_UVSize(type));
		pEffectAnimation->SetAngle(fAngle);
		pEffectAnimation->m_nCntSwitch = nCntSwitch;

		//オブジェタイプ追加してSceneに追加
		pEffectAnimation->SetObjType(objtype);
		pEffectAnimation->AddUniqueList(std::move(pEffectAnimation));
	}
}
