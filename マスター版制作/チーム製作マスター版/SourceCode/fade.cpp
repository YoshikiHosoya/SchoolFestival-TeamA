//=============================================================================
//
// フェード処理 [fade.cpp]
//
//=============================================================================
#include "fade.h"
#include "renderer.h"
#include "game.h"
#include "GameManager.h"
#include "ResultManager.h"
#include "map.h"
#include "Player.h"
#include "playerUI.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define	TEXTURE_FADE					"data/TEXTURE/fade000.jpg"	// 読み込むテクスチャファイル名
#define FADE_COLOR_WHITE				(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f))
#define WAPE_SPEED						(50.0f)
#define FADE_ALPHADAMPING_MODE			(0.05f)
#define FADE_ALPHADAMPING_STAGE			(0.02f)

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
	m_pos = SCREEN_CENTER_POS;
	m_fadeState = FADESTATE::FADESTATE_NONE;
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
	if (m_fadeState != FADESTATE::FADESTATE_NONE)
	{
		//フェードのタイプで動きを変える
		switch (m_fadeType)
		{
		case CFADE::FADETYPE::FADETYPE_MODE:
		case CFADE::FADETYPE::FADETYPE_STAGE_CHANGE:
			//ホワイトアウト
			FadeWhiteOut();
			break;
		case CFADE::FADETYPE::FADETYPE_MAPMOVE:
			//ワイプ
			FadeWipe();
			break;

		}
	}

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
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuffFade,
		NULL);

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標更新
	pVtx[0].pos = m_pos + D3DXVECTOR3(-SCREEN_WIDTH, -SCREEN_HEIGHT, 0.0f);
	pVtx[1].pos = m_pos + D3DXVECTOR3(+SCREEN_WIDTH, -SCREEN_HEIGHT, 0.0f);
	pVtx[2].pos = m_pos + D3DXVECTOR3(-SCREEN_WIDTH, +SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = m_pos + D3DXVECTOR3(+SCREEN_WIDTH, +SCREEN_HEIGHT, 0.0f);

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
// フェードの状態取得
//=============================================================================
CFADE::FADESTATE CFADE::GetFadeState(void)
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
//=============================================================================
// フェードに必要な情報の初期化
//=============================================================================
void CFADE::ResetFadeParam()
{
	switch (m_fadeType)
	{
		//モードのフェードの時
	case CFADE::FADETYPE::FADETYPE_MODE:
		m_colorFade = FADE_COLOR_WHITE;
		m_pos = SCREEN_CENTER_POS;

		break;
		//マップのフェード時
	case CFADE::FADETYPE::FADETYPE_MAPMOVE:
		m_colorFade = BlackColor;
		m_pos = D3DXVECTOR3(-SCREEN_WIDTH, SCREEN_HEIGHT * 0.5f, 0.0f);
		break;

		//マップのフェード時
	case CFADE::FADETYPE::FADETYPE_STAGE_CHANGE:
		m_colorFade = ZeroColor;
		m_pos = SCREEN_CENTER_POS;

		break;
	}

	m_fadeState = FADESTATE::FADESTATE_OUT;

}
//=============================================================================
// フェード　ホワイトアウトしてくタイプ
//=============================================================================
void CFADE::FadeWhiteOut()
{
	//フェードアウト時
	if (m_fadeState == FADESTATE::FADESTATE_OUT)
	{
		if (m_fadeType == CFADE::FADETYPE::FADETYPE_MODE)
		{
			//どんどん白く
			m_colorFade.a += FADE_ALPHADAMPING_MODE;
		}
		else
		{
			//どんどん白く
			m_colorFade.a += FADE_ALPHADAMPING_STAGE;

		}

		//α値が1超えた時
		if (m_colorFade.a >= 1.0f)
		{
			//a値を1に固定
			m_colorFade.a = 1.0f;

			//フェードインに切り替え
			m_fadeState = FADESTATE::FADESTATE_IN;

			//フェードアウト時の切り替え処理
			FadeOut();
		}
	}
	//フェードイン時
	else if (m_fadeState == FADESTATE::FADESTATE_IN)
	{
		//どんどん薄く
		m_colorFade.a -= FADE_ALPHADAMPING_MODE;

		//α値が0になった時
		if (m_colorFade.a <= 0.0f)
		{
			//α値を0に固定
			m_colorFade.a = 0.0f;

			//フェード終了
			m_fadeState = FADESTATE::FADESTATE_NONE;
			m_fadeType = FADETYPE::FADETYPE_NONE;
		}
	}
	UpdateVertex();
}

//=============================================================================
// フェード　ワイプしていくタイプ
//=============================================================================
void CFADE::FadeWipe()
{
	//ワイプ
	m_pos.x += WAPE_SPEED;

	//フェードアウト時
	if (m_fadeState == FADESTATE::FADESTATE_OUT)
	{
		//画面全体が埋まった時
		if (m_pos.x > SCREEN_CENTER_POS.x)
		{
			//フェードインに切り替え
			m_fadeState = FADESTATE::FADESTATE_IN;

			//フェードアウト時の切り替え処理
			FadeOut();
		}
	}
	//フェードイン時
	else if (m_fadeState == FADESTATE::FADESTATE_IN)
	{
		//α値が0になった時
		if (m_pos.x > SCREEN_WIDTH * 2)
		{
			//フェード終了
			m_fadeState = FADESTATE::FADESTATE_NONE;
			m_fadeType = FADETYPE::FADETYPE_NONE;
		}
	}
	UpdateVertex();
}
//=============================================================================
// フェードアウト時の処理
//=============================================================================
void CFADE::FadeOut()
{
	switch (m_fadeType)
	{
		//モードのフェードの時
	case CFADE::FADETYPE::FADETYPE_MODE:
		CManager::SetMode((CManager::MODE)m_NextID);
		break;
		//マップのフェード時
	case CFADE::FADETYPE::FADETYPE_MAPMOVE:
	case CFADE::FADETYPE::FADETYPE_STAGE_CHANGE:

		//マップのポインタ取得
		CMap *pMap = CManager::GetBaseMode()->GetMap();

		//プレイヤーのマップ遷移時の処理
		if (CPlayer::GetTwoPPlayFlag())
		{
			for (int nCntPlayer = 0; nCntPlayer < MAX_CONTROLLER; nCntPlayer++)
			{
				if (CManager::GetBaseMode()->GetPlayer((TAG)(nCntPlayer)))
				{
					CManager::GetBaseMode()->GetPlayer((TAG)(nCntPlayer))->MapChangePlayerRespawn();
				}
			}
		}
		else
		{
			if (CManager::GetBaseMode()->GetPlayer((TAG)(0)))
			{
				CManager::GetBaseMode()->GetPlayer((TAG)(0))->MapChangePlayerRespawn();
			}
		}
		//レンダラー設定初期化
		CManager::GetRenderer()->ResetRenderer();

		//タイマーリセット
		CManager::GetGame()->GetPlayer(TAG::PLAYER_1)->GetPlayerUI()->ResetTime();

		//シーン管理にあるマップ変更時に必要ないものを消去
		CScene::MapChangeRelease();

		//nullcheck
		if (pMap)
		{
			//マップ更新
			pMap->AllDelete();
			pMap->MapLoad((CMap::MAP)m_NextID);
			CManager::GetGame()->GetGameManager()->MapTransitionWaveSet((CMap::MAP)m_NextID);
		}


		if (m_fadeType == CFADE::FADETYPE::FADETYPE_STAGE_CHANGE)
		{
			//ゲームの状態を通常に戻す
			CManager::GetGame()->GetGameManager()->SetGameState(CGameManager::GAMESTATE::NORMAL);

			//プレイヤーリセット
			for (int nCntPlayer = 0; nCntPlayer < MAX_CONTROLLER; nCntPlayer++)
			{
				if (CManager::GetBaseMode()->GetPlayer((TAG)(nCntPlayer)))
				{
					CManager::GetBaseMode()->GetPlayer((TAG)(nCntPlayer))->ResetPlayer();
				}
			}
		}
		break;

	}
}
//=============================================================================
// 頂点バッファ更新
//=============================================================================
void CFADE::UpdateVertex()
{
	//変数宣言
	VERTEX_2D *pVtx;

	//頂点バッファロック
	m_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標更新
	pVtx[0].pos = m_pos + D3DXVECTOR3(-SCREEN_WIDTH, -SCREEN_HEIGHT, 0.0f);
	pVtx[1].pos = m_pos + D3DXVECTOR3(+SCREEN_WIDTH, -SCREEN_HEIGHT, 0.0f);
	pVtx[2].pos = m_pos + D3DXVECTOR3(-SCREEN_WIDTH, +SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = m_pos + D3DXVECTOR3(+SCREEN_WIDTH, +SCREEN_HEIGHT, 0.0f);

	//頂点カラー更新
	pVtx[0].col = m_colorFade;
	pVtx[1].col = m_colorFade;
	pVtx[2].col = m_colorFade;
	pVtx[3].col = m_colorFade;

	//頂点バッファアンロック
	m_pVtxBuffFade->Unlock();
}
