// ----------------------------------------
//
// スタートゴール処理の説明[startgoal.cpp]
// Author : Fujiwara Masato
//
// ----------------------------------------

// ----------------------------------------
//
// インクルードファイル
//
// ----------------------------------------
/* 描画 */
#include "startgoalpoint.h"
#include "player.h"
#include "meshdome.h"
#include "fade.h"
#include "debugproc.h"
#include "3DTexture.h"
// ----------------------------------------
//
// マクロ定義
//
// ----------------------------------------
#define GOAL_ROTMOVE (0.01f)				// 角度の移動量
#define GOAL_SIZE (100.0f)					// サイズ
#define GOAL_TEX "data/TEXTURE/Line.png"	// テクスチャー
#define GOAL_ANGLE (D3DX_PI / 1)			// 湾曲の角度

// ----------------------------------------
//
// グローバル変数
//
// ----------------------------------------

// ----------------------------------------
//
// 静的変数宣言
//
// ----------------------------------------

// ----------------------------------------
// コンストラクタ処理
// ----------------------------------------
CStartGoal::CStartGoal() : CScene(ACTOR_GOAL, LAYER_3DOBJECT)
{
	/* 変数の初期化 */
	// 回転量
	//m_pos = D3DXVECTOR3(-100.0f, 3900.0f, 0.0f);
}

// ----------------------------------------
// デストラクタ処理
// ----------------------------------------
CStartGoal::~CStartGoal()
{
}

// ----------------------------------------
// 初期化処理
// ----------------------------------------
void CStartGoal::Init(void)
{
	if (m_type == TYPE_START)
	{
		// メッシュドームの生成
		CMeshdome::Create(
			m_pos,
			D3DXVECTOR3(100.0f, 400.0f, 100.0f),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f),
			20, 1,
			CMeshdome::TYPE_START
		);
	}

	else if (m_type == TYPE_GOAL)
	{
		// メッシュドームの生成
		CMeshdome::Create(
			m_pos,
			D3DXVECTOR3(100.0f, 400.0f, 100.0f),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f),
			20, 1,
			CMeshdome::TYPE_GOAL
		);

		C3DTexture::Create(D3DXVECTOR3(	m_pos.x, m_pos.y + 10, m_pos.z),
										D3DXVECTOR3(1.57f, 0.0f, 0.0f),
										D3DXVECTOR3(250.0f, 0.0f, 250.0f),
										D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f),
										C3DTexture::TYPE_EFFECT_000,
										false);
	}
}

// ----------------------------------------
// 終了処理
// ----------------------------------------
void CStartGoal::Uninit(void)
{
}

// ----------------------------------------
// 更新処理
// ----------------------------------------
void CStartGoal::Update(void)
{
	CPlayer *pPlayer = NULL;

	for (int nCntlayer = 0; nCntlayer < CScene::GetMaxLayer(CScene::LAYER_3DOBJECT); nCntlayer++)
	{
		if (pPlayer = (CPlayer *)CScene::GetActor(CScene::ACTOR_PLAYER, CScene::LAYER_3DOBJECT, nCntlayer)) break;
	}

	if (pPlayer != NULL)
	{
		// ゲーム遷移
		if (CCalculation::Collision_Circle(
			m_pos,	// 現在のオブジェクトの位置
			200.0f,				// 現在のオブジェクトの半径
			pPlayer->GetPos(),	// 目的のオブジェクトの位置
			200.0f))			// 目的のオブジェクトの半径
		{
			if (CManager::GetFade()->GetFade() == CFade::FADE_NONE)
			{
				//pTopscore->SetScore(pScore->GetScore() + 20000);
				CManager::GetFade()->SetFade(CManager::MODE_RANKING);
			}
		}
	}
}

// ----------------------------------------
// 描画処理
// ----------------------------------------
void CStartGoal::Draw(void)
{
}

// ----------------------------------------
// 作成処理
// ----------------------------------------
CStartGoal * CStartGoal::Create(D3DXVECTOR3 pos , TYPE type)
{
	// 変数宣言
	CStartGoal * pStartGoal;		// シーン2Dクラス
						// メモリの生成(初め->基本クラス,後->派生クラス)
	pStartGoal = new CStartGoal();
	// 位置情報
	pStartGoal->m_pos = pos;
	// 種類の設定
	pStartGoal->m_type = type;
	// 初期化処理
	pStartGoal->Init();
	// 生成したオブジェクトを返す
	return pStartGoal;
}