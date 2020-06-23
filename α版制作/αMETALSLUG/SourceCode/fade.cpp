//=============================================================================
//
// フェード処理 [fade.cpp]
//
//=============================================================================
#include "fade.h"
#include "renderer.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define	TEXTURE_FADE	"data/TEXTURE/fade000.jpg"	// 読み込むテクスチャファイル名
#define FADE_COLOR	(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f))
//=============================================================================
// プロトタイプ宣言
//=============================================================================
//=============================================================================
// 初期化処理
//=============================================================================
void CFADE::InitFade(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_fadeState = FADE_NONE;
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_FADE,		// ファイルの名前
		&m_pTextureFade);	// 読み込むメモリー
							// 頂点情報の設定
	MakeVertexFade();
}

//=============================================================================
// 終了処理
//=============================================================================
void CFADE::UninitFade(void)
{
	// テクスチャの開放
	if (m_pTextureFade != NULL)
	{
		m_pTextureFade->Release();
		m_pTextureFade = NULL;
	}

	// 頂点バッファの開放
	if (m_pVtxBuffFade != NULL)
	{
		m_pVtxBuffFade->Release();
		m_pVtxBuffFade = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void CFADE::UpdateFade(void)
{
	VERTEX_2D *pVtx;
	m_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);
	if (m_fadeState == FADE_IN)
	{
			m_colorFade.a -= 0.01f;
			if (m_colorFade.a <= 0.0f)
			{
				m_colorFade.a = 0.0f;
				m_fadeState = FADE_NONE;
			}

	}
	else if (m_fadeState == FADE_OUT)
	{
		m_colorFade.a += 0.05f;
		if (m_colorFade.a >= 1.0f)
		{
			m_colorFade.a = 1.0f;
			m_fadeState = FADE_IN;
			if (m_modeNext != CManager::MODE_NONE)
			{
				CManager::SetGameMode(m_modeNext);
			}
			else
			{

			}
		}
	}
	pVtx[0].col = m_colorFade;
	pVtx[1].col = m_colorFade;
	pVtx[2].col = m_colorFade;
	pVtx[3].col = m_colorFade;
	m_pVtxBuffFade->Unlock();
}

//=============================================================================
// タイトル画面
//=============================================================================
void CFADE::DrawFade(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, m_pVtxBuffFade, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, m_pTextureFade);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=============================================================================
// 頂点の作成
//=============================================================================
void CFADE::MakeVertexFade(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	VERTEX_2D *pVtx;

	// オブジェクトの頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 1, D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuffFade,
		NULL);

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);


	// 頂点カラーの設定
	pVtx[0].rhm = 1.0f;
	pVtx[1].rhm = 1.0f;
	pVtx[2].rhm = 1.0f;
	pVtx[3].rhm = 1.0f;

	// 頂点カラーの設定
	pVtx[0].col = m_colorFade;
	pVtx[1].col = m_colorFade;
	pVtx[2].col = m_colorFade;
	pVtx[3].col = m_colorFade;

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点データをアンロックする
	m_pVtxBuffFade->Unlock();
}

//=============================================================================
// フェードの状態設定
//=============================================================================
void CFADE::SetFade(CManager::GAME_MODE modeNext)
{
	if (m_fadeState == FADE_NONE)
	{
		m_fadeState = FADE_OUT;
		m_modeNext = modeNext;
		m_colorFade = FADE_COLOR;
	}
}
//=============================================================================
// フェードの状態取得
//=============================================================================
CFADE::FADE CFADE::GetFadeState(void)
{
	return m_fadeState;
}
//=============================================================================
// フェードのクリエイト
//=============================================================================
CFADE *CFADE::CreateFade(void)
{
	CFADE *pfade;
	pfade = new CFADE;
	pfade->InitFade();
	return pfade;
}
