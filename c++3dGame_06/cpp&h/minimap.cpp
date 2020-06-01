// ----------------------------------------
//
// ミニマップ処理の説明[minimap.cpp]
// Author : Fujiwara Masato
//
// ----------------------------------------

// ----------------------------------------
//
// インクルードファイル
//
// ----------------------------------------
#include "minimap.h"
#include "debugproc.h"
#include "player.h"
#include "enemy.h"
#include "3ditem.h"
#include "input.h"
#include "camera.h"
// ----------------------------------------
//
// マクロ定義
//
// ----------------------------------------
#define MAP_UI_ANIM (2)
#define MAP_UI_SPLIT (1.0f / MAP_UI_ANIM)

#define MAP_TEX_X0 (0.4f)
#define MAP_TEX_Y0 (0.4f)
#define MAP_TEX_X1 (1.0f)
#define MAP_TEX_Y1 (1.0f)

#define MAP_MOVESPEED (0.001f)
#define MAP_ZERO (0.0000f)

// ----------------------------------------
//
// 静的変数宣言
//
// ----------------------------------------
LPDIRECT3DTEXTURE9	CMinimap::m_pTexture[MINIMAP_UI_MAX] = {};		// テクスチャへのポインタ
CLoad2D				*CMinimap::m_pload2D = NULL;						// ロード
int					CMinimap::m_nAll = 0;							// 番号
// ----------------------------------------
// コンストラクタ
// ----------------------------------------
CMinimap::CMinimap() : CScene_TWO::CScene_TWO(ACTOR_MAP_UI, LAYER_UI)
{
	m_fMult = 0.0f;									// 倍数
	m_fAdd = 0.0f;									// 加算
	m_nRange = 0;									// 描画する幅
	m_state = MINIMAP_STATE_NORMAL;
	m_type = MINIMAP_UI_MAP;
	m_rot = 0.0f;
	m_TexFirst = D3DXVECTOR2(MAP_TEX_X0, MAP_TEX_Y0);
	m_TexLast = D3DXVECTOR2(MAP_TEX_X1, MAP_TEX_Y1);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_TexFirstMove = D3DXVECTOR2(0.0f, 0.0f);
	m_TexLastMove = D3DXVECTOR2(0.0f, 0.0f);
}

// ----------------------------------------
// デストラクタ処理
// ----------------------------------------
CMinimap::~CMinimap()
{
}

// ----------------------------------------
// 初期化処理
// ----------------------------------------
void CMinimap::Init(void)
{
	// シーン3Dの初期化
	CScene_TWO::Init();
}

// ----------------------------------------
// 終了処理
// ----------------------------------------
void CMinimap::Uninit(void)
{
	CScene_TWO::Uninit();
}

// ----------------------------------------
// 更新処理
// ----------------------------------------
void CMinimap::Update(void)
{
	CScene_TWO::Update();

	if (m_type == MINIMAP_UI_MAP || m_type == MINIMAP_UI_SHARD_POS || m_type == MINIMAP_UI_PLAYER_POS)
	{
		MAP_MOVE();
	}

	if (m_type == MINIMAP_UI_PLAYER_POS)
	{
		CScene_TWO::SetRot(m_rot);
	}
}

// ----------------------------------------
// 描画処理
// ----------------------------------------
void CMinimap::Draw(void)
{
	if(m_type == MINIMAP_UI_ENEMY_POS)
	{
		// 変数宣言
		LPDIRECT3DDEVICE9 pDevice =					// デバイスの取得
			CManager::GetRenderer()->GetDevice();

		// ライティングモード無効
		pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
		//Zバッファ　有効　無効
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, D3DZB_FALSE);
		// レンダーステート(加算合成処理)
		pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		// 裏面(左回り)をカリングする
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

		// 描画
		CScene_TWO::Draw();

		//アルファテスト戻す
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
		//Zバッファ　有効　無効
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, D3DZB_TRUE);
		// ライティングモード有効
		pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
		// 裏面(左回り)をカリングする
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

		// レンダーステート(通常ブレンド処理)
		pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}

	//マップのテクスチャ座標内に欠片があったら描画
	/*if ()
	{
		CScene_TWO::Draw();
	}*/

	//[敵]鍵の効果が発動していてマップのテクスチャ座標内に敵があったら描画
	/*if ()
	{
		CScene_TWO::Draw();
	}*/

	else
	{
		CScene_TWO::Draw();
	}
}

// ----------------------------------------
// テクスチャー設定処理
// ----------------------------------------
void CMinimap::SetTexture(MINIMAP_UI_TYPE type)
{
	// 設定
	CScene_TWO::BindTexture(m_pTexture[type]);	// テクスチャー
}


// ----------------------------------------
// 作成処理
// ----------------------------------------
CMinimap * CMinimap::Create(void)
{
	// 変数宣言
	CMinimap * pMinimap;		// シーン3Dクラス
						// メモリの生成(初め->基本クラス,後->派生クラス)
	pMinimap = new CMinimap();
	// 初期化処理
	pMinimap->Init();
	// 生成したオブジェクトを返す
	return pMinimap;
}

// ----------------------------------------
// 読み込み作成処理
// ----------------------------------------
void CMinimap::LoadCreate(void)
{
	// 変数宣言
	CMinimap * pMiniMap;	// ミニマップ

	for (int nCntMap = 0; nCntMap < m_nAll; nCntMap++)
	{
		pMiniMap = CMinimap::Create();						// 生成
		if (nCntMap != 1)
		{
			pMiniMap->SetTexture((MINIMAP_UI_TYPE)m_pload2D->GetInfo(nCntMap).nType);
		}
		pMiniMap->m_type = (MINIMAP_UI_TYPE)m_pload2D->GetInfo(nCntMap).nType;
		pMiniMap->SetPos(m_pload2D->GetInfo(nCntMap).pos);		// 位置
		pMiniMap->SetRot(m_pload2D->GetInfo(nCntMap).rot);		// 回転
		if (pMiniMap->m_type == MINIMAP_UI_SHARD_POS ||
			pMiniMap->m_type == MINIMAP_UI_ENEMY_POS ||
			pMiniMap->m_type == MINIMAP_UI_PLAYER_POS)
		{
			pMiniMap->SetCol(m_pload2D->GetInfo(nCntMap).col);		// 色
		}
		pMiniMap->SetSize(m_pload2D->GetInfo(nCntMap).size);	// サイズ

		if (pMiniMap->m_type == MINIMAP_UI_MAP)
		{
			pMiniMap->SetTex(D3DXVECTOR2(pMiniMap->m_TexFirst), D3DXVECTOR2(pMiniMap->m_TexLast));
		}
	}
}

// ----------------------------------------
// 読み込み処理4
// ----------------------------------------
HRESULT CMinimap::Load(void)
{
	// 変数宣言
	LPDIRECT3DDEVICE9 pDevice =					// デバイスの取得
		CManager::GetRenderer()->GetDevice();
	char cTex[MINIMAP_UI_MAX][128] =					// テクスチャー名
	{
		"data/TEXTURE/MAP/Map.png",				//マップの画像
		"",										//画像なし
		"data/TEXTURE/Effect/effect000.jpg",	//敵の座標 (エフェクト)
		"data/TEXTURE/MAP/0Arrows.png",		//自分の座標 (上と同じ)
		"data/TEXTURE/MAP/MapFrame.png",		//マップの外枠
		"data/TEXTURE/MAP/Map_Mission00.png",	//ミッションの表示(一つ目)
		"data/TEXTURE/MAP/Map_Mission01.png"	//ミッションの表示(二つ目)
	};

	// テクスチャー設定
	for (int nCnt = 0; nCnt < MINIMAP_UI_MAX; nCnt++)
	{
		if (strcmp(cTex[nCnt], "") != 0)
		{
			D3DXCreateTextureFromFile(pDevice, cTex[nCnt], &m_pTexture[nCnt]);
		}

		/*if (strcmp(cTex[MINIMAP_UI_PLAYER_POS], "") == 0)
		{
			m_pTexture[MINIMAP_UI_PLAYER_POS] = m_pTexture[MINIMAP_UI_ENEMY_POS];
		}*/
	}

	// ロード生成
	m_pload2D = new CLoad2D;
	// ロード読み込み
	m_nAll = m_pload2D->Load("data/LOAD/MAP/MiniMap.txt");

	return S_OK;
}

// ----------------------------------------
// unload処理
// ----------------------------------------
void CMinimap::UnLoad(void)
{
	// テクスチャー設定
	for (int nCnt = 0; nCnt < MINIMAP_UI_MAX; nCnt++)
	{
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
	// ロードの破棄
	delete m_pload2D;
	m_pload2D = NULL;
}

// ----------------------------------------
// タイプによって処理を変える
// ----------------------------------------
void CMinimap::Various(int nCnt)
{
}


// ----------------------------------------
// ロード取得
// ----------------------------------------
CLoad2D * CMinimap::GetLoad(void)
{
	return m_pload2D;
}

// ----------------------------------------
// 位置の設定処理
// ----------------------------------------
void CMinimap::SetPos(D3DXVECTOR3 pos)
{
	CScene_TWO::SetPosition(pos);
}

// ----------------------------------------
// 回転の設定処理
// ----------------------------------------
void CMinimap::SetRot(float rot)
{
	CScene_TWO::SetRot(rot);
}

// ----------------------------------------
// サイズ設定処理
// ----------------------------------------
void CMinimap::SetSize(D3DXVECTOR2 size)
{
	CScene_TWO::SetSize(size);
}

// ----------------------------------------
// 色の設定処理
// ----------------------------------------
void CMinimap::SetCol(D3DXCOLOR col)
{
	CScene_TWO::SetCol(col);
}

// ----------------------------------------
// 表示テクスチャー設定処理
// ----------------------------------------
void CMinimap::SetTex(D3DXVECTOR2 first, D3DXVECTOR2 last)
{
	CScene_TWO::SetTex(first, last);
}

// ----------------------------------------
// サイズの取得処理
// ----------------------------------------
D3DXVECTOR2 CMinimap::GetSize(void)
{
	return CScene_TWO::GetSize();
}

// ----------------------------------------
// 位置の取得処理
// ----------------------------------------
D3DXVECTOR3 CMinimap::GetPos(void)
{
	return CScene_TWO::GetPosition();
}

// ----------------------------------------
// テクスチャ座標の限界設定
// ----------------------------------------
void CMinimap::TexRange(void)
{
	if (m_TexFirst.x <= 0.0)
	{
		m_TexFirst.x = 0.0f;
	}

	else if (m_TexFirst.y <= 0.0)
	{
		m_TexFirst.y = 0.0f;
	}

	else if (m_TexLast.x >= 1.0)
	{
		m_TexLast.x = 1.0;
	}

	else if (m_TexLast.y >= 1.0)
	{
		m_TexLast.y = 1.0;
	}
}

// ----------------------------------------
// マップのテクスチャ座標の移動
// ----------------------------------------
void CMinimap::MAP_MOVE(void)
{
	CPlayer *pPlayer = NULL;	// プレイヤー

	for (int nCntlayer = 0; nCntlayer < CScene::GetMaxLayer(CScene::LAYER_3DOBJECT); nCntlayer++)
	{
		if (pPlayer = (CPlayer *)CScene::GetActor(CScene::ACTOR_PLAYER, CScene::LAYER_3DOBJECT, nCntlayer)) break;
	}

	float fRot;
	fRot = CManager::GetRenderer()->GetCamera()->GetRot().y;	// 回転情報取得

	// マップの移動 //
	// ----------------------------------------
	// 左移動
	// ----------------------------------------
	if (CManager::GetKeyboard()->GetKeyboardPress(DIK_A))
	{//Aを押している時
		if (pPlayer->GetbCollL() == false)
		{//プレイヤーの左側の当たり判定がfalseだったら
			if (pPlayer->GetbCollB() == false)
			{//プレイヤーの奥側の当たり判定がfalseだったら
				if (CManager::GetKeyboard()->GetKeyboardPress(DIK_W))
				{// 奥
					m_TexFirst.x += sinf(D3DX_PI * 0.25f - fRot) * MAP_MOVESPEED;
					m_TexLast.y += cosf(D3DX_PI * 0.25f - fRot) * MAP_MOVESPEED;

					m_TexFirst.y += cosf(D3DX_PI * 0.25f - fRot) * MAP_MOVESPEED;
					m_TexLast.x += sinf(D3DX_PI * 0.25f - fRot) * MAP_MOVESPEED;

					m_rot = 0.785f;

					//m_TexFirst += D3DXVECTOR2(-MAP_MOVESPEED, -MAP_MOVESPEED);
					//m_TexLast += D3DXVECTOR2(-MAP_MOVESPEED, -MAP_MOVESPEED);
				}
			}

			else if (pPlayer->GetbCollB() == true)
			{//プレイヤーの奥側の当たり判定がtrueだったら
				if (CManager::GetKeyboard()->GetKeyboardPress(DIK_W))
				{// 奥
					m_TexFirst.x += sinf(D3DX_PI * 0.5f + fRot) * MAP_MOVESPEED;
					m_TexLast.y += cosf(D3DX_PI * 0.5f + fRot) * MAP_MOVESPEED;

					m_TexFirst.y += cosf(D3DX_PI * 0.5f + fRot) * MAP_MOVESPEED;
					m_TexLast.x += sinf(D3DX_PI * 0.5f + fRot) * MAP_MOVESPEED;

					m_rot = 0.785f;

					//m_TexFirst += D3DXVECTOR2(-MAP_MOVESPEED, -MAP_ZERO);
					//m_TexLast += D3DXVECTOR2(-MAP_MOVESPEED, -MAP_ZERO);
				}
			}

			if (pPlayer->GetbCollF() == false)
			{//プレイヤーの奥側の当たり判定がfalseだったら
				if (CManager::GetKeyboard()->GetKeyboardPress(DIK_S))
				{// 手前
					m_TexFirst.x += sinf(D3DX_PI * -0.25f + fRot) * -MAP_MOVESPEED;
					m_TexLast.y += cosf(D3DX_PI * -0.25f + fRot) * -MAP_MOVESPEED;

					m_TexFirst.y += cosf(D3DX_PI * -0.25f + fRot) * -MAP_MOVESPEED;
					m_TexLast.x += sinf(D3DX_PI * -0.25f + fRot) * -MAP_MOVESPEED;

					m_rot = 2.355f;

					//m_TexFirst += D3DXVECTOR2(-MAP_MOVESPEED, MAP_MOVESPEED);
					//m_TexLast += D3DXVECTOR2(-MAP_MOVESPEED, MAP_MOVESPEED);
				}
			}

			else if (pPlayer->GetbCollF() == true)
			{//プレイヤーの奥側の当たり判定がtrueだったら
				// 手前
				if (CManager::GetKeyboard()->GetKeyboardPress(DIK_S))
				{
					m_TexFirst.x += sinf(D3DX_PI * 0.5f + fRot) * -MAP_MOVESPEED;
					m_TexLast.y += cosf(D3DX_PI * 0.5f + fRot) * -MAP_MOVESPEED;

					m_TexFirst.y += cosf(D3DX_PI * 0.5f + fRot) * -MAP_MOVESPEED;
					m_TexLast.x += sinf(D3DX_PI * 0.5f + fRot) * -MAP_MOVESPEED;

					m_rot = 2.355f;

					//m_TexFirst += D3DXVECTOR2(-MAP_MOVESPEED, MAP_ZERO);
					//m_TexLast += D3DXVECTOR2(-MAP_MOVESPEED, MAP_ZERO);
				}
			}
		}

		else if (pPlayer->GetbCollL() == true)
		{//プレイヤーの左側の当たり判定がtrueだったら
			if (CManager::GetKeyboard()->GetKeyboardPress(DIK_W))
			{// 奥
				//m_TexFirst += D3DXVECTOR2(-0.0f,-MAP_MOVESPEED);
				//m_TexLast += D3DXVECTOR2(-0.0f,-MAP_MOVESPEED);

				m_TexFirst.x += sinf(D3DX_PI * -1.0f + fRot) * -MAP_MOVESPEED;
				m_TexLast.y += cosf(D3DX_PI * -1.0f + fRot) * -MAP_MOVESPEED;

				m_TexFirst.y += cosf(D3DX_PI * -1.0f + fRot) * -MAP_MOVESPEED;
				m_TexLast.x += sinf(D3DX_PI * -1.0f + fRot) * -MAP_MOVESPEED;

				m_rot = 0.785f;
			}
			else if (CManager::GetKeyboard()->GetKeyboardPress(DIK_S))
			{// 手前
				//m_TexFirst += D3DXVECTOR2(-0.0f, MAP_MOVESPEED);
				//m_TexLast += D3DXVECTOR2(-0.0f, MAP_MOVESPEED);

				m_TexFirst.x += sinf(D3DX_PI * -0.0f + fRot) * -MAP_MOVESPEED;
				m_TexLast.y += cosf(D3DX_PI * -0.0f + fRot) * -MAP_MOVESPEED;

				m_TexFirst.y += cosf(D3DX_PI * -0.0f + fRot) * -MAP_MOVESPEED;
				m_TexLast.x += sinf(D3DX_PI * -0.0f + fRot) * -MAP_MOVESPEED;

				m_rot = 2.355f;
			}
		}

		if (CManager::GetKeyboard()->GetKeyboardPress(DIK_A) &&
			CManager::GetKeyboard()->GetKeyboardPress(DIK_W) == false &&
			CManager::GetKeyboard()->GetKeyboardPress(DIK_S) == false)
		{// 左
			if (pPlayer->GetbCollL() == false)
			{//プレイヤーの左側の当たり判定がfalseだったら
				//m_TexFirst.x += sinf(D3DX_PI * 0.25f + fRot) * MAP_MOVESPEED;
				//m_TexLast.y += cosf(D3DX_PI * 0.25f + fRot) * MAP_MOVESPEED;

				m_TexFirst.x += sinf(D3DX_PI * -0.5f + fRot) * -MAP_MOVESPEED;
				m_TexLast.y += cosf(D3DX_PI * -0.5f + fRot) * -MAP_MOVESPEED;

				m_TexFirst.y += cosf(D3DX_PI * -0.5f + fRot) * -MAP_MOVESPEED;
				m_TexLast.x += sinf(D3DX_PI * -0.5f + fRot) * -MAP_MOVESPEED;

				m_rot = D3DX_PI / 2;

				//m_TexFirst += D3DXVECTOR2(-MAP_MOVESPEED, 0.0f);
				//m_TexLast += D3DXVECTOR2(-MAP_MOVESPEED, 0.0f);
			}
		}
	}

	// ----------------------------------------
	// 右移動
	// ----------------------------------------
	else if (CManager::GetKeyboard()->GetKeyboardPress(DIK_D))
	{
		if (pPlayer->GetbCollR() == false)
		{
			if (pPlayer->GetbCollB() == false)
			{
				// 奥
				if (CManager::GetKeyboard()->GetKeyboardPress(DIK_W))
				{
					//m_TexLast += D3DXVECTOR2(MAP_MOVESPEED, -MAP_MOVESPEED);
					//m_TexFirst += D3DXVECTOR2(MAP_MOVESPEED, -MAP_MOVESPEED);

					m_TexFirst.x += sinf(D3DX_PI * -0.25f - fRot) * MAP_MOVESPEED;
					m_TexLast.y += cosf(D3DX_PI * -0.25f - fRot) * MAP_MOVESPEED;

					m_TexFirst.y += cosf(D3DX_PI * -0.25f - fRot) * MAP_MOVESPEED;
					m_TexLast.x += sinf(D3DX_PI * -0.25f - fRot) * MAP_MOVESPEED;

					m_rot = -0.785f;
				}
			}

			else if (pPlayer->GetbCollB() == true)
			{
				// 奥
				if (CManager::GetKeyboard()->GetKeyboardPress(DIK_W))
				{
					//m_TexLast += D3DXVECTOR2(MAP_MOVESPEED, -MAP_ZERO);
					//m_TexFirst += D3DXVECTOR2(MAP_MOVESPEED, -MAP_ZERO);

					m_TexFirst.x += sinf(D3DX_PI * -0.5f - fRot) * MAP_MOVESPEED;
					m_TexLast.y += cosf(D3DX_PI * -0.5f - fRot) * MAP_MOVESPEED;

					m_TexFirst.y += cosf(D3DX_PI * -0.5f - fRot) * MAP_MOVESPEED;
					m_TexLast.x += sinf(D3DX_PI * -0.5f - fRot) * MAP_MOVESPEED;

					m_rot = -0.785f;
				}
			}

			if (pPlayer->GetbCollF() == false)
			{
				// 手前
				if (CManager::GetKeyboard()->GetKeyboardPress(DIK_S))
				{
					//m_TexLast += D3DXVECTOR2(MAP_MOVESPEED, MAP_MOVESPEED);
					//m_TexFirst += D3DXVECTOR2(MAP_MOVESPEED, MAP_MOVESPEED);

					m_TexFirst.x += sinf(D3DX_PI * -0.75f - fRot) * MAP_MOVESPEED;
					m_TexLast.y += cosf(D3DX_PI * -0.75f - fRot) * MAP_MOVESPEED;

					m_TexFirst.y += cosf(D3DX_PI * -0.75f - fRot) * MAP_MOVESPEED;
					m_TexLast.x += sinf(D3DX_PI * -0.75f - fRot) * MAP_MOVESPEED;


					m_rot = -2.355f;
				}
			}

			else if (pPlayer->GetbCollF() == true)
			{
				// 手前
				if (CManager::GetKeyboard()->GetKeyboardPress(DIK_S))
				{
					//m_TexLast += D3DXVECTOR2(MAP_MOVESPEED, MAP_ZERO);
					//m_TexFirst += D3DXVECTOR2(MAP_MOVESPEED, MAP_ZERO);

					m_TexFirst.x += sinf(D3DX_PI * 1.0f - fRot) * MAP_MOVESPEED;
					m_TexLast.y += cosf(D3DX_PI * 1.0f - fRot) * MAP_MOVESPEED;

					m_TexFirst.y += cosf(D3DX_PI * 1.0f - fRot) * MAP_MOVESPEED;
					m_TexLast.x += sinf(D3DX_PI * 1.0f - fRot) * MAP_MOVESPEED;

					m_rot = -2.355f;
				}
			}
		}

		else if (pPlayer->GetbCollR() == true)
		{
			// 奥
			if (CManager::GetKeyboard()->GetKeyboardPress(DIK_W))
			{
				//m_TexLast += D3DXVECTOR2(0.0f, -MAP_MOVESPEED);
				//m_TexFirst += D3DXVECTOR2(0.0f, -MAP_MOVESPEED);

				m_TexFirst.x += sinf(D3DX_PI * -0.0f - fRot) * MAP_MOVESPEED;
				m_TexLast.y += cosf(D3DX_PI * -0.0f - fRot) * MAP_MOVESPEED;

				m_TexFirst.y += cosf(D3DX_PI * -0.0f - fRot) * MAP_MOVESPEED;
				m_TexLast.x += sinf(D3DX_PI * -0.0f - fRot) * MAP_MOVESPEED;

				m_rot = -0.785f;
			}


			// 手前
			else if (CManager::GetKeyboard()->GetKeyboardPress(DIK_S))
			{
				//m_TexLast += D3DXVECTOR2(0.0f, MAP_MOVESPEED);
				//m_TexFirst += D3DXVECTOR2(0.0f, MAP_MOVESPEED);

				m_TexFirst.x += sinf(D3DX_PI * -1.0f - fRot) * MAP_MOVESPEED;
				m_TexLast.y += cosf(D3DX_PI * -1.0f - fRot) * MAP_MOVESPEED;

				m_TexFirst.y += cosf(D3DX_PI * -1.0f - fRot) * MAP_MOVESPEED;
				m_TexLast.x += sinf(D3DX_PI * -1.0f - fRot) * MAP_MOVESPEED;


				m_rot = -2.355f;
			}
		}

		// 右
		if (CManager::GetKeyboard()->GetKeyboardPress(DIK_D) &&
			CManager::GetKeyboard()->GetKeyboardPress(DIK_W) == false &&
			CManager::GetKeyboard()->GetKeyboardPress(DIK_S) == false)
		{
			if (pPlayer->GetbCollR() == false)
			{
				//m_TexLast += D3DXVECTOR2(MAP_MOVESPEED, 0.0f);
				//m_TexFirst += D3DXVECTOR2(MAP_MOVESPEED, 0.0f);

				m_TexFirst.x += sinf(D3DX_PI * -0.5f - fRot) * MAP_MOVESPEED;
				m_TexLast.y += cosf(D3DX_PI * -0.5f - fRot) * MAP_MOVESPEED;

				m_TexFirst.y += cosf(D3DX_PI * -0.5f - fRot) * MAP_MOVESPEED;
				m_TexLast.x += sinf(D3DX_PI * -0.5f - fRot) * MAP_MOVESPEED;

				m_rot = -D3DX_PI / 2;
			}
		}
	}

	// ----------------------------------------
	// 奥移動
	// ----------------------------------------
	else if (CManager::GetKeyboard()->GetKeyboardPress(DIK_W))
	{
		if (pPlayer->GetbCollB() == false)
		{
			//m_TexFirst += D3DXVECTOR2(0.0f, -MAP_MOVESPEED);
			//m_TexLast += D3DXVECTOR2(0.0f, -MAP_MOVESPEED);

			m_TexFirst.x += sinf(D3DX_PI * 0.0f - fRot) * MAP_MOVESPEED;
			m_TexLast.y += cosf(D3DX_PI * 0.0f - fRot) * MAP_MOVESPEED;

			m_TexFirst.y += cosf(D3DX_PI * 0.0f - fRot) * MAP_MOVESPEED;
			m_TexLast.x += sinf(D3DX_PI * 0.0f - fRot) * MAP_MOVESPEED;

			m_rot = -0.0f;
		}
	}

	// ----------------------------------------
	// 手前移動
	// ----------------------------------------
	else if (CManager::GetKeyboard()->GetKeyboardPress(DIK_S))
	{
		if (pPlayer->GetbCollF() == false)
		{
			//m_TexLast += D3DXVECTOR2(0.0f, MAP_MOVESPEED);
			//m_TexFirst += D3DXVECTOR2(0.0f, MAP_MOVESPEED);

			m_TexFirst.x += sinf(D3DX_PI * 1.0f - fRot) * MAP_MOVESPEED;
			m_TexLast.y += cosf(D3DX_PI * 1.0f - fRot) * MAP_MOVESPEED;

			m_TexFirst.y += cosf(D3DX_PI * 1.0f - fRot) * MAP_MOVESPEED;
			m_TexLast.x += sinf(D3DX_PI * 1.0f - fRot) * MAP_MOVESPEED;

			m_rot = -D3DX_PI;
		}
	}

	//マップの描画限界設定
	//TexRange();

	if (m_type == MINIMAP_UI_MAP)
	{
		//テクスチャ座標の更新
		CScene_TWO::SetTex(m_TexFirst, m_TexLast);
	}
}

// ----------------------------------------
// 不要なマップUIの削除
// ----------------------------------------
void CMinimap::ExceptUI(void)
{
}
