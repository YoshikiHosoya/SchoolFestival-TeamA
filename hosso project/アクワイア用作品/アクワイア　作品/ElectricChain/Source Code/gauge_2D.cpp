//------------------------------------------------------------------------------
//
//2Dゲージ処理  [gauge_2D.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "gauge_2D.h"	
#include "scene2D.h"
#include "manager.h"
#include "renderer.h"

//------------------------------------------------------------------------------
//マクロ定義
//------------------------------------------------------------------------------
#define INTERVAL	(10)

//------------------------------------------------------------------------------
//静的メンバ変数の初期化
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//コンストラクタ
//------------------------------------------------------------------------------
CGauge_2D::CGauge_2D()
{

}
//------------------------------------------------------------------------------
//デストラクタ
//------------------------------------------------------------------------------
CGauge_2D::~CGauge_2D()
{
}
//------------------------------------------------------------------------------
//初期化処理
//------------------------------------------------------------------------------
HRESULT CGauge_2D::Init()
{

	return S_OK;
}
//------------------------------------------------------------------------------
//終了処理
//------------------------------------------------------------------------------
void CGauge_2D::Uninit()
{

}
//------------------------------------------------------------------------------
//更新処理
//------------------------------------------------------------------------------
void CGauge_2D::Update()
{
	//ゲージの更新
	CGauge::Update();
}
//------------------------------------------------------------------------------
//描画処理
//------------------------------------------------------------------------------
void CGauge_2D::Draw()
{
	//ライティングOFF
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_LIGHTING_OFF);

	//nullcheck
	if (!m_pScene2DList.empty())
	{
		//要素分繰り返す
		for (size_t nCnt = 0; nCnt < m_pScene2DList.size(); nCnt++)
		{
			//描画
			m_pScene2DList[nCnt]->Draw();
		}
	}

	//ライティングを元に戻す
	CHossoLibrary::CheckLighting();
}
//------------------------------------------------------------------------------
//デバッグ情報表示
//------------------------------------------------------------------------------
void CGauge_2D::ShowDebugInfo()
{
#ifdef _DEBUG

#endif // _DEBUG
}

//------------------------------------------------------------------------------
//生成
//------------------------------------------------------------------------------
std::shared_ptr<CGauge_2D> CGauge_2D::Create(D3DXVECTOR3 const & pos, D3DXVECTOR3 const & gaugeSize, int const nMaxLife)
{
	//変数宣言
	std::shared_ptr<CGauge_2D> pGauge = std::make_shared<CGauge_2D>();

	if (pGauge)
	{
		//初期化7
		pGauge->Init();

		//ゲージ作成
		pGauge->MakeGauge(pos, gaugeSize);
		pGauge->SetMaxLife(nMaxLife);

		pGauge->SetObjType(OBJTYPE_2DGAUGE);
		pGauge->AddSharedList(pGauge);

		//return
		return pGauge;
	}
	return nullptr;
}
//------------------------------------------------------------------------------
//ゲージ更新
//------------------------------------------------------------------------------
void CGauge_2D::UpdateGaugeMag(float GreenMag, float RedMag, float BlueMag)
{
	m_pScene2DList[CGauge::GAUGE_FLAME]->UpdateGauge(0.0f);
	m_pScene2DList[CGauge::GAUGE_GREEN]->UpdateGauge(GreenMag);
	m_pScene2DList[CGauge::GAUGE_RED]->UpdateGauge(RedMag);
	m_pScene2DList[CGauge::GAUGE_BLUE]->UpdateGauge(BlueMag);
}
//------------------------------------------------------------------------------
//座標設定
//------------------------------------------------------------------------------
void CGauge_2D::SetPos(D3DXVECTOR3 const & pos)
{
	//nullcheck
	if (!m_pScene2DList.empty())
	{
		//要素分繰り返す
		for (size_t nCnt = 0; nCnt < m_pScene2DList.size(); nCnt++)
		{
			//座標設定
			m_pScene2DList[nCnt]->SetPos(pos);
		}
	}
}

//------------------------------------------------------------------------------
//ゲージ
//------------------------------------------------------------------------------
void CGauge_2D::MakeGauge(D3DXVECTOR3 pos,D3DXVECTOR3 size)
{
	//要素分繰り返し
	for (int nCnt = 0; nCnt < CGauge::GAUGE_MAX; nCnt++)
	{
		//3Dポリゴン生成
		m_pScene2DList.emplace_back(CScene2D::Create_SelfManagement(pos , size));
	}

	m_pScene2DList[CGauge::GAUGE_FLAME]->SetVtxCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
	m_pScene2DList[CGauge::GAUGE_RED]->SetVtxCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	m_pScene2DList[CGauge::GAUGE_BLUE]->SetVtxCol(D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));
	m_pScene2DList[CGauge::GAUGE_GREEN]->SetVtxCol(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));

}
