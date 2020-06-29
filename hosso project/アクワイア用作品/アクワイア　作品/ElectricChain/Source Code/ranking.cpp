//------------------------------------------------------------------------------
//
//ランキング処理  [ranking.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "scene.h"
#include "ranking.h"
#include "manager.h"
#include "renderer.h"
#include "fade.h"
#include "multinumber.h"
#include "UI.h"
#include "effectanimation2D.h"
#include "score.h"
#include "sound.h"
//------------------------------------------------------------------------------
//マクロ
//------------------------------------------------------------------------------
#define FADE_COUNT				(520)		//フェードするまでのカウント
#define RANKING_POP_INTERVAL	(40)		//ランキングが出てくるインターバル
//------------------------------------------------------------------------------
//コンストラクタ
//------------------------------------------------------------------------------
CRanking::CRanking()
{
	m_nCntFadeTitle = FADE_COUNT;
}
//------------------------------------------------------------------------------
//デストラクタ
//------------------------------------------------------------------------------
CRanking::~CRanking()
{
}

//------------------------------------------------------------------------------
//初期化処理
//------------------------------------------------------------------------------
HRESULT CRanking::Init(HWND hWnd)
{
	CUI::LoadPlace(CUI::SCENE_RANKING);

	return S_OK;
}

//------------------------------------------------------------------------------
//終了処理
//------------------------------------------------------------------------------
void CRanking::Uninit()
{
	//終了処理
	CScene::ReleaseAll();
}

//------------------------------------------------------------------------------
//更新処理
//------------------------------------------------------------------------------
void CRanking::Update()
{
	m_nCntFadeTitle--;

	//一定間隔で一個一個ランキング表示
	if (m_nCntFadeTitle % RANKING_POP_INTERVAL == 0)
	{
		//5個まだ出てない時
		if (m_pMultiNumberList.size() < 5)
		{
			//ランキング生成
			CreateRank();
		}
	}


	//フェードしてない時
	if (CManager::GetRenderer()->GetFade()->GetFade() == CFade::FADE_NONE)
	{
		//ある程度時間たったら
		if ((m_nCntFadeTitle < 0 || CHossoLibrary::CheckAnyButton()))
		{
			if (m_pMultiNumberList.size() >= 5)
			{
				//タイトルに戻る
				CManager::GetRenderer()->GetFade()->SetModeFade(CManager::MODE_TITLE);
				CManager::GetSound()->Play(CSound::LABEL_SE_DECISION);
			}
			else
			{
				while (m_pMultiNumberList.size() < 5)
				{
					//ランキング生成
					CreateRank();
				}
			}
		}
	}
}

//------------------------------------------------------------------------------
//描画処理
//------------------------------------------------------------------------------
void CRanking::Draw()
{
}

//------------------------------------------------------------------------------
//ランク生成　エフェクトと音と一緒に
//------------------------------------------------------------------------------
void CRanking::CreateRank()
{
	//ランキングの数字表示
	std::shared_ptr<CMultiNumber> pMultiNumber =
		CMultiNumber::Create(
			D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 650.0f - (m_pMultiNumberList.size() * 100.0f), 0.0f),
			D3DXVECTOR3(40.0f, 80.0f, 0.0f),
			CScore::GetRankingScore(4 - m_pMultiNumberList.size()),
			6,
			CScene::OBJTYPE_NUMBER);

	//さっきのスコアと同じスコアだった時
	if (CScore::GetScore() == CScore::GetRankingScore(4 - m_pMultiNumberList.size()))
	{
		//点滅
		pMultiNumber->Settype(CMultiNumber::TYPE_FLASHING);
	}

	//雷のエフェクト
	CEffectAnimation2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 650.0f - (m_pMultiNumberList.size() * 100.0f), 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH, 200.0f + (m_pMultiNumberList.size() * 50.0f), 0.0f), CTexture::SEPARATE_TEX_EFFECT_LINETHUNDER, 0.0f, 3, CScene::OBJTYPE_2DEFFECT);

	//配列に追加
	m_pMultiNumberList.emplace_back(std::move(pMultiNumber));

	//音再生
	CManager::GetSound()->Play(CSound::LABEL_SE_RANKING_THUNDER);
}
