//------------------------------------------------------------------------------
//
//爆発の痕跡処理  [traces.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "traces.h"
#include "manager.h"
#include "renderer.h"
#include "effectanimation3D.h"

//------------------------------------------------------------------------------
//マクロ
//------------------------------------------------------------------------------
#define DEFAULT_LIFE	(1000)
//------------------------------------------------------------------------------
//コンストラクタ
//------------------------------------------------------------------------------
CTraces::CTraces()
{

}
//------------------------------------------------------------------------------
//デストラクタ
//------------------------------------------------------------------------------
CTraces::~CTraces()
{
}
//------------------------------------------------------------------------------
//初期化処理
//------------------------------------------------------------------------------
HRESULT CTraces::Init()
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
void CTraces::Uninit()
{
	//終了処理
	CScene3D::Uninit();
}
//------------------------------------------------------------------------------
//更新処理
//------------------------------------------------------------------------------
void CTraces::Update()
{
	//寿命を減らす
	m_nLife--;

	//適度な感覚で
	if (m_nLife % 25 == 0 && m_nLife > 0)
	{
		//煙を発生
		CEffectAnimation3D::Create(GetPos(), D3DXVECTOR3(120.0f, 120.0f, 0.0f), CTexture::SEPARATE_TEX_EFFECT_SMOKE, D3DXCOLOR(0.5f,0.5f,0.5f,0.15f), 0.0f, 20);
	}

	//寿命が０以下になった後
	if (m_nLife <= 0)
	{
		//a値を減らしてく
		D3DXCOLOR &rCol = GetCol();
		rCol.a -= 0.01f;
		SetVtxCol(rCol);

		//a値が0以下になった時
		if(rCol.a <= 0)
		{
			Release();
			return;
		}
	}

	//更新処理
	CScene3D::Update();
}
//------------------------------------------------------------------------------
//描画処理
//------------------------------------------------------------------------------
void CTraces::Draw()
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//減算合成
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ALPHABLEND_SUB);

	//Zテスト無効でZライティング有効
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ZTEST_OFF_ZWRITING_ON);

	//描画処理
	CScene3D::Draw();

	//Zテスト通常
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ZTEST_DEFAULT);

	//加算合成
	CManager::GetRenderer()->SetRendererCommand(CRenderer::REDNERER_ALPHABLEND_DEFAULT);

}
//------------------------------------------------------------------------------
//デバッグ情報表示
//------------------------------------------------------------------------------
void CTraces::ShowDebugInfo()
{
#ifdef _DEBUG

#endif //_DEBUG
}
//------------------------------------------------------------------------------
//生成処理
//------------------------------------------------------------------------------
void CTraces::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//メモリ確保
	std::unique_ptr<CTraces> pTraecs (new CTraces);

	//nullcheck
	if (pTraecs)
	{
		//初期化
		pTraecs->Init();

		//初期化
		pTraecs->BindTexture(CTexture::GetTexture(CTexture::TEX_EXPLOSION_TRACE));
		pTraecs->m_nLife = DEFAULT_LIFE;
		pTraecs->SetPos(pos);
		pTraecs->SetSize(size);

		//Sceneで管理
		pTraecs->SetObjType(OBJTYPE_TRACES);
		pTraecs->AddUniqueList(std::move(pTraecs));

	}
}
