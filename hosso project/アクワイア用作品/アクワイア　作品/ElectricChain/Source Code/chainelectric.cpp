//------------------------------------------------------------------------------
//
//連鎖の電撃  [chainelectric.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "chainelectric.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"
#include "effectanimation3D.h"
//------------------------------------------------------------------------------
//静的メンバ変数の初期化
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//マクロ
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//コンストラクタ
//------------------------------------------------------------------------------
CChainElectric::CChainElectric()
{
	//初期化
	m_pos = ZeroVector3;
	m_size = ZeroVector3;
	m_rot = ZeroVector3;
	m_col = WhiteColor;
	m_nPatternAnim = 0;
	m_nCntAnim = 0;
}
//------------------------------------------------------------------------------
//デストラクタ
//------------------------------------------------------------------------------
CChainElectric::~CChainElectric()
{
}
//------------------------------------------------------------------------------
//初期化処理
//------------------------------------------------------------------------------
HRESULT CChainElectric::Init()
{
	return S_OK;
}
//------------------------------------------------------------------------------
//終了処理
//------------------------------------------------------------------------------
void CChainElectric::Uninit()
{

}
//------------------------------------------------------------------------------
//更新処理
//------------------------------------------------------------------------------
void CChainElectric::Update()
{
	//ライフが0になったら消去
	if (m_nLife-- < 0)
	{
		Release();
		return;
	}

	//カウンターを進める
	m_nCntAnim++;

	//2フレームごとに
	if (m_nCntAnim % 1 == 0)
	{
		//パターンを進める
		m_nPatternAnim++;
		//終了
		if (m_nPatternAnim >= CTexture::GetSparateTex_UVCnt(CTexture::SEPARATE_TEX_EFFECT_CHAINELECTRIC).x *  CTexture::GetSparateTex_UVCnt(CTexture::SEPARATE_TEX_EFFECT_CHAINELECTRIC).y)
		{
			Release();
			return;
		}

		//UV座標設定
		D3DXVECTOR2 UV;
		UV.x = m_nPatternAnim % (int)CTexture::GetSparateTex_UVCnt(CTexture::SEPARATE_TEX_EFFECT_CHAINELECTRIC).x * CTexture::GetSparateTex_UVSize(CTexture::SEPARATE_TEX_EFFECT_CHAINELECTRIC).x;
		UV.y = m_nPatternAnim / (int)CTexture::GetSparateTex_UVCnt(CTexture::SEPARATE_TEX_EFFECT_CHAINELECTRIC).x * CTexture::GetSparateTex_UVSize(CTexture::SEPARATE_TEX_EFFECT_CHAINELECTRIC).y;

		//頂点情報へのポインタ
		VERTEX_3D *pVtx;

		//頂点データの範囲をロックし、頂点バッファへのポインタを取得
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(UV.x, UV.y);
		pVtx[1].tex = D3DXVECTOR2(UV.x + CTexture::GetSparateTex_UVSize(CTexture::SEPARATE_TEX_EFFECT_CHAINELECTRIC).x, UV.y);
		pVtx[2].tex = D3DXVECTOR2(UV.x, UV.y + CTexture::GetSparateTex_UVSize(CTexture::SEPARATE_TEX_EFFECT_CHAINELECTRIC).y);
		pVtx[3].tex = D3DXVECTOR2(UV.x + CTexture::GetSparateTex_UVSize(CTexture::SEPARATE_TEX_EFFECT_CHAINELECTRIC).x, UV.y + CTexture::GetSparateTex_UVSize(CTexture::SEPARATE_TEX_EFFECT_CHAINELECTRIC).y);

		//頂点データをアンロック
		m_pVtxBuff->Unlock();
	}
}
//------------------------------------------------------------------------------
//描画処理
//------------------------------------------------------------------------------
void CChainElectric::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//加算合成
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ALPHABLEND_ADD);

	//Zテスト無効
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ZTEST_OFF);

	//カリングしない
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_CULLING_NONE);

	//マトリックス計算
	CHossoLibrary::CalcMatrix(&m_Mtx, m_pos, m_rot);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_Mtx);

	//頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, CTexture::GetSeparateTexture(CTexture::SEPARATE_TEX_EFFECT_CHAINELECTRIC));

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
							0,					//開始するインデックス(頂点)
							2);					//ポリゴンの枚数

	//カリングチェック
	CHossoLibrary::CheckCulling();

	//Zテスト通常
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ZTEST_DEFAULT);

	//通常合成
	CManager::GetRenderer()->SetRendererCommand(CRenderer::REDNERER_ALPHABLEND_DEFAULT);
}
//------------------------------------------------------------------------------
//デバッグ情報表示
//------------------------------------------------------------------------------
void CChainElectric::ShowDebugInfo()
{
#ifdef _DEBUG

#endif //_DEBUG
}

//------------------------------------------------------------------------------
//生成処理
//------------------------------------------------------------------------------
void CChainElectric::Create(D3DXVECTOR3 StartPos, D3DXVECTOR3 GoalPos, D3DXVECTOR3 size, D3DXCOLOR col, int nLife)
{
	//変数宣言
	std::unique_ptr<CChainElectric> pChainElectric (new CChainElectric);

	//3Dアニメーション
	if (pChainElectric)
	{
		//初期化
		pChainElectric->Init();

		//情報を入れる
		pChainElectric->m_pos = StartPos;
		pChainElectric->m_size = size;
		pChainElectric->m_col = col;
		pChainElectric->m_size = size;
		pChainElectric->m_nLife = nLife + 3;

		//計算用
		D3DXVECTOR3 Distance = GoalPos - StartPos;
		float fLength = D3DXVec3Length(&Distance);
		float fAngle = atan2f(Distance.x, Distance.z);

		//長さ
		fLength = fabs(fLength);

		//角度設定
		pChainElectric->m_pos = StartPos + ((GoalPos - StartPos) / 2);
		pChainElectric->m_rot = (D3DXVECTOR3(0.0f, fAngle + (D3DX_PI * 0.5f), 0.0f));

		//サイズ
		pChainElectric->m_size = (D3DXVECTOR3(fLength * 2.0f, 450.0f,0.0f));

		//スタンエフェクト　適当にビリビリさせる
		CEffectAnimation3D::Create(pChainElectric->m_pos, pChainElectric->m_size * 0.7f, CTexture::SEPARATE_TEX_EFFECT_STANING, WhiteColor,CHossoLibrary::Random_PI(), 2);

		//音再生
		CManager::GetSound()->Play(CSound::LABEL_SE_CHAINING_SPARK);

		//頂点生成
		pChainElectric->MakeVertex();

		//Sceneで管理
		pChainElectric->SetObjType(OBJTYPE_EFFECT);
		pChainElectric->AddUniqueList(std::move(pChainElectric));

	}
}

//------------------------------------------------------------------------------
//頂点生成
//------------------------------------------------------------------------------
void CChainElectric::MakeVertex()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,	//確保するバッファサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,			//頂点フォーマット
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//頂点情報へのポインタ
	VERTEX_3D *pVtx;

	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点の座標
	pVtx[0].pos = D3DXVECTOR3(-m_size.x * 0.5f, m_size.y * 0.5f, m_size.z * 0.5f);
	pVtx[1].pos = D3DXVECTOR3(m_size.x * 0.5f, m_size.y * 0.5f, m_size.z * 0.5f);
	pVtx[2].pos = D3DXVECTOR3(-m_size.x * 0.5f, -m_size.y * 0.5f, -m_size.z * 0.5f);
	pVtx[3].pos = D3DXVECTOR3(m_size.x * 0.5f, -m_size.y * 0.5f, -m_size.z * 0.5f);

	//頂点の同次座標
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//頂点の色
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f + CTexture::GetSparateTex_UVSize(CTexture::SEPARATE_TEX_EFFECT_CHAINELECTRIC).x, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.0f + CTexture::GetSparateTex_UVSize(CTexture::SEPARATE_TEX_EFFECT_CHAINELECTRIC).y);
	pVtx[3].tex = D3DXVECTOR2(0.0f + CTexture::GetSparateTex_UVSize(CTexture::SEPARATE_TEX_EFFECT_CHAINELECTRIC).x, 0.0f + CTexture::GetSparateTex_UVSize(CTexture::SEPARATE_TEX_EFFECT_CHAINELECTRIC).y);

	//頂点データをアンロック
	m_pVtxBuff->Unlock();
}
