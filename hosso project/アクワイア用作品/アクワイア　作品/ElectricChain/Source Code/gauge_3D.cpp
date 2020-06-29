//------------------------------------------------------------------------------
//
//3Dゲージ処理  [gauge_3D.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "gauge_3D.h"	
#include "scene3D.h"
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
CGauge_3D::CGauge_3D()
{
	m_bFlashing = false;
	m_offset = ZeroVector3;
	m_nCntFlash = 0;
	m_pScene3DList.clear();
}

//------------------------------------------------------------------------------
//デストラクタ
//------------------------------------------------------------------------------
CGauge_3D::~CGauge_3D()
{
}
//------------------------------------------------------------------------------
//初期化処理
//------------------------------------------------------------------------------
HRESULT CGauge_3D::Init()
{

	return S_OK;
}
//------------------------------------------------------------------------------
//終了処理
//------------------------------------------------------------------------------
void CGauge_3D::Uninit()
{

}
//------------------------------------------------------------------------------
//更新処理
//------------------------------------------------------------------------------
void CGauge_3D::Update()
{
	//ゲージの更新
	CGauge::Update();

	//ライフが0になったら点滅終了
	if (GetLife() <= 0)
	{
		m_bFlashing = false;
	}

	//点滅状態
	if (m_bFlashing)
	{
		//カウンタ
		m_nCntFlash++;

		//色取得して点滅させる
		D3DXCOLOR &rCol = m_pScene3DList[CGauge::GAUGE_BLUE]->GetCol();
		m_nCntFlash % 20 < 10 ?
			rCol.a -= 0.1f :
			rCol.a += 0.1f;

		//範囲内に抑える
		CHossoLibrary::RangeLimit_Equal_Float(rCol.a, 0.0f, 1.0f);

		//色設定
		m_pScene3DList[CGauge::GAUGE_BLUE]->SetVtxCol(rCol);
	}

	//nullcheck
	if (!m_pScene3DList.empty())
	{
		//要素分繰り返す
		for (size_t nCnt = 0; nCnt < m_pScene3DList.size(); nCnt++)
		{
			//更新
			m_pScene3DList[nCnt]->Update();
		}
	}

}
//------------------------------------------------------------------------------
//描画処理
//------------------------------------------------------------------------------
void CGauge_3D::Draw()
{
	//ビルボード設定
	CHossoLibrary::SetBillboard(&m_Mtx);

	//ライティングOFF
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_LIGHTING_OFF);

	//nullcheck
	if (!m_pScene3DList.empty())
	{
		//要素分繰り返す
		for (size_t nCnt = 0; nCnt < m_pScene3DList.size(); nCnt++)
		{
			if (m_bFlashing && nCnt == CGauge::GAUGE_RED)
			{

			}
			else
			{
				//描画
				m_pScene3DList[nCnt]->DrawSettingMtx(m_Mtx);
			}
		}
	}

	//ライティングを元に戻す
	CHossoLibrary::CheckLighting();
}
//------------------------------------------------------------------------------
//デバッグ情報表示
//------------------------------------------------------------------------------
void CGauge_3D::ShowDebugInfo()
{
#ifdef _DEBUG

#endif // _DEBUG
}

//------------------------------------------------------------------------------
//生成
//------------------------------------------------------------------------------
std::shared_ptr<CGauge_3D> CGauge_3D::Create(D3DXVECTOR3 const & pos, D3DXVECTOR3 const & gaugeSize, D3DXVECTOR3 const & offset, int const nMaxLife,D3DXMATRIX mtx)
{
	//変数宣言
	std::shared_ptr<CGauge_3D> pGauge = std::make_shared<CGauge_3D>();

	if (pGauge)
	{
		//初期化7
		pGauge->Init();

		//ゲージ作成
		pGauge->m_offset = offset;
		pGauge->MakeGauge(pos, gaugeSize);
		pGauge->SetMaxLife(nMaxLife);
		pGauge->m_Mtx = mtx;
		pGauge->SetObjType(OBJTYPE_3DGAUGE);
		pGauge->AddSharedList(pGauge);

		//return
		return pGauge;
	}
	return nullptr;
}
//------------------------------------------------------------------------------
//ゲージ更新
//------------------------------------------------------------------------------
void CGauge_3D::UpdateGaugeMag(float GreenMag, float RedMag, float BlueMag)
{
	//ゲージ更新
	m_pScene3DList[CGauge::GAUGE_GREEN]->UpdateGauge(GreenMag);
	m_pScene3DList[CGauge::GAUGE_RED]->UpdateGauge(RedMag);
	m_pScene3DList[CGauge::GAUGE_BLUE]->UpdateGauge(BlueMag);

}
//------------------------------------------------------------------------------
//座標設定
//------------------------------------------------------------------------------
void CGauge_3D::SetPos(D3DXVECTOR3 const & pos)
{
	//nullcheck
	if (!m_pScene3DList.empty())
	{
		//要素分繰り返す
		for (size_t nCnt = 0; nCnt < m_pScene3DList.size(); nCnt++)
		{
			//座標設定
			m_pScene3DList[nCnt]->SetPos(pos + m_offset);
		}
	}
}

//------------------------------------------------------------------------------
//ゲージ
//------------------------------------------------------------------------------
void CGauge_3D::SetMtx(D3DXMATRIX mtx)
{
	//マトリックス代入
	m_Mtx = mtx;

	//計算用マトリックス
	D3DXMATRIX mtxTrans;

	//マトリックス計算
	D3DXMatrixTranslation(&mtxTrans, m_offset.x, m_offset.y, m_offset.z);
	D3DXMatrixMultiply(&m_Mtx, &m_Mtx, &mtxTrans);
}


//------------------------------------------------------------------------------
//ゲージ
//------------------------------------------------------------------------------
void CGauge_3D::MakeGauge(D3DXVECTOR3 pos,D3DXVECTOR3 size)
{
	//要素分繰り返し
	for (int nCnt = 0; nCnt < CGauge::GAUGE_MAX; nCnt++)
	{
		//3Dポリゴン生成
		m_pScene3DList.emplace_back(CScene3D::Create_SelfManagement(pos + m_offset, size));
		m_pScene3DList[nCnt]->SetBboard(true);
	}

	//ゲージの色設定
	m_pScene3DList[CGauge::GAUGE_FLAME]->SetVtxCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
	m_pScene3DList[CGauge::GAUGE_BLUE]->SetVtxCol(D3DXCOLOR(0.2f, 0.2f, 1.0f, 1.0f));
	m_pScene3DList[CGauge::GAUGE_RED]->SetVtxCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	m_pScene3DList[CGauge::GAUGE_GREEN]->SetVtxCol(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));

}
