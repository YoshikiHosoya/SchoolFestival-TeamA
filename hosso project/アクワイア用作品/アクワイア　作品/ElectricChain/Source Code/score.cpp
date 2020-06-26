//------------------------------------------------------------------------------
//
//スコア処理  [score.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "score.h"
#include "enemy.h"
#include "multinumber.h"

//------------------------------------------------------------------------------
//マクロ
//------------------------------------------------------------------------------
#define DEFAULT_KILL_POS				(D3DXVECTOR3(1000.0f,650.0f,0.0f))			//初期座標
#define DEFAULT_COMBO_POS				(D3DXVECTOR3(1000.0f,550.0f,0.0f))			//初期座標
#define DEFAULT_CHAIN_POS				(D3DXVECTOR3(1000.0f,200.0f,0.0f))			//初期座標

#define DEFAULT_KILL_NUMBER_SIZE		(D3DXVECTOR3(60.0f, 120.0f, 0.0f))			//ナンバーの大きさ
#define DEFAULT_COMBO_NUMBER_SIZE		(D3DXVECTOR3(35.0f, 70.0f, 0.0f))			//ナンバーの大きさ
#define DEFAULT_CHAIN_NUMBER_SIZE		(D3DXVECTOR3(35.0f, 70.0f, 0.0f))			//ナンバーの大きさ
#define RANKING_NUM						(5)											//ランキングの人数

#define SCORE_DIGITS					(4)											//スコアの桁数
#define SCORE_DATA						("data/SAVEDATA/score.txt")					//スコアのテキスト名
//------------------------------------------------------------------------------
//静的メンバ変数の初期化
//------------------------------------------------------------------------------
std::vector<int> CScore::m_nRankingScoreList(5);
int CScore::m_nScore = 0;
int CScore::m_nKill = 0;
int CScore::m_nCombo = 0;

//------------------------------------------------------------------------------
//コンストラクタ
//------------------------------------------------------------------------------
CScore::CScore()
{
	//初期化
	m_nScore = 0;
	m_nKill = 0;
	m_nCombo = 0;
	m_pMultiNumberLIst.clear();
}
//------------------------------------------------------------------------------
//デストラクタ
//------------------------------------------------------------------------------
CScore::~CScore()
{
	m_pMultiNumberLIst.clear();
}

//------------------------------------------------------------------------------
//初期化処理
//------------------------------------------------------------------------------
HRESULT CScore::Init()
{
	//生成処理
	m_pMultiNumberLIst.emplace_back(CMultiNumber::Create(DEFAULT_KILL_POS, DEFAULT_KILL_NUMBER_SIZE, 0, SCORE_DIGITS, CScene::OBJTYPE_NUMBER));
	m_pMultiNumberLIst.emplace_back(CMultiNumber::Create(DEFAULT_COMBO_POS, DEFAULT_COMBO_NUMBER_SIZE, 0, SCORE_DIGITS, CScene::OBJTYPE_NUMBER));

	return S_OK;
}
//------------------------------------------------------------------------------
//終了処理
//------------------------------------------------------------------------------
void CScore::Uninit()
{
}
//------------------------------------------------------------------------------
//更新処理
//------------------------------------------------------------------------------
void CScore::Update()
{

}
//------------------------------------------------------------------------------
//描画処理
//------------------------------------------------------------------------------
void CScore::Draw()
{

}
//------------------------------------------------------------------------------
//生成処理
//------------------------------------------------------------------------------
std::unique_ptr<CScore> CScore::Create()
{
	//変数宣言
	std::unique_ptr<CScore> pScore(new CScore);

	//初期化処理
	pScore->Init();

	//リターン
	return pScore;
}

//------------------------------------------------------------------------------
//スコア加算処理
//------------------------------------------------------------------------------
void CScore::AddKill(int nValue)
{
	//古い情報保存
	int nNumKillOld = m_nKill;

	//値を加算
	m_nKill += nValue;

	//50キルおきに
	if (m_nKill % 50 == 0)
	{
		//ナンバー生成
		std::shared_ptr<CMultiNumber> pMultiNumber = CMultiNumber::Create(SCREEN_CENTER_POS, D3DXVECTOR3(150.0f, 300.0f, 0.0f), m_nKill,3, CScene::OBJTYPE_FRONTUI);
		pMultiNumber->Settype(CMultiNumber::TYPE_CENTER_DISAPPEAR);
	}

	//値のテクスチャを更新
	if (m_pMultiNumberLIst[CScore::SCORE_KILL])
	{
		m_pMultiNumberLIst[CScore::SCORE_KILL]->SetMultiNumber(m_nKill);
		m_pMultiNumberLIst[CScore::SCORE_KILL]->SetChangeAnimation(m_nKill,nNumKillOld);
	}
}
//------------------------------------------------------------------------------
//スコア加算処理
//------------------------------------------------------------------------------
void CScore::AddCombo(int nValue)
{
	//古い情報保存
	int nNumComboOld = m_nCombo;

	//値を加算
	m_nCombo += nValue;

	//値のテクスチャを更新
	if (m_pMultiNumberLIst[CScore::SCORE_COMBO])
	{
		m_pMultiNumberLIst[CScore::SCORE_COMBO]->SetMultiNumber(m_nCombo);
		m_pMultiNumberLIst[CScore::SCORE_COMBO]->SetChangeAnimation(m_nCombo, nNumComboOld);
	}
}
//------------------------------------------------------------------------------
//チェイン数計算
//------------------------------------------------------------------------------
void CScore::SetNowChain()
{
	//古い情報保存
	int nNumNowChainOld = m_nNowChain;

	//スタンしてる数取得
	m_nNowChain = CEnemy::GetStanEnemyNum();

	//値のテクスチャを更新
	if (m_pMultiNumberLIst[CScore::SCORE_NOWCHAIN])
	{
		m_pMultiNumberLIst[CScore::SCORE_NOWCHAIN]->SetMultiNumber(m_nNumChain);
	}
}
//------------------------------------------------------------------------------
//スコア加算処理
//------------------------------------------------------------------------------
void CScore::AddNumChain(int nValue)
{
	//古い情報保存
	int mNumChainOld = m_nNumChain;

	//値を加算
	m_nNumChain += nValue;

	//値のテクスチャを更新
	if (m_pMultiNumberLIst[CScore::SCORE_NUMCHAIN])
	{
		m_pMultiNumberLIst[CScore::SCORE_NUMCHAIN]->SetMultiNumber(m_nNumChain);
	}
}

//------------------------------------------------------------------------------
//ランキングのスコア取得
//------------------------------------------------------------------------------
int CScore::GetRankingScore(int nRank)
{
	return m_nRankingScoreList[nRank];
}

//------------------------------------------------------------------------------
// スコア読み込み
//------------------------------------------------------------------------------
HRESULT CScore::LoadScore()
{
	// ファイルポイント
	FILE *pFile;

	// ファイル開
	pFile = fopen(SCORE_DATA, "r");

	// 開けた
	if (pFile != nullptr)
	{
		//5位まで
		for (int nCnt = 0; nCnt < RANKING_NUM; nCnt++)
		{
			fscanf(pFile, "%d", &m_nRankingScoreList[nCnt]); // 名前
			std::cout << "LoadScore - " << nCnt << " - Score >> " << m_nRankingScoreList[nCnt] << NEWLINE;

		}
		// ファイル閉
		fclose(pFile);
	}

	// 開けない
	else
	{
		return E_FAIL;
	}
	return S_OK;
}
//------------------------------------------------------------------------------
// スコアセーブ
//------------------------------------------------------------------------------
HRESULT CScore::SaveScore()
{
	//スコア計算
	m_nScore = m_nCombo * 50 + m_nKill * 1000;

	//ファイルのポインタ
	FILE *pFile;

	//一番最後のやつよりスコアが高かった時
	if (m_nScore >= m_nRankingScoreList[m_nRankingScoreList.size() - 1])
	{
		//配列に追加
		m_nRankingScoreList.emplace_back(m_nScore);

		//仮の変数
		int nData;

		//ソート 降順
		for (size_t nCntSave01 = 0; nCntSave01 < m_nRankingScoreList.size(); nCntSave01++)
		{
			for (size_t nCntSave02 = nCntSave01 + 1; nCntSave02 < m_nRankingScoreList.size(); nCntSave02++)
			{
				if (m_nRankingScoreList[nCntSave01] < m_nRankingScoreList[nCntSave02])
				{
					nData = m_nRankingScoreList[nCntSave02];
					m_nRankingScoreList[nCntSave02] = m_nRankingScoreList[nCntSave01];
					m_nRankingScoreList[nCntSave01] = nData;
				}
			}
		}
		//一番低かった奴を除外
		m_nRankingScoreList.pop_back();
	}

	// ファイル開
	pFile = fopen(SCORE_DATA, "w");

	// 開けた
	if (pFile != nullptr)
	{
		for (size_t nCnt = 0; nCnt < m_nRankingScoreList.size(); nCnt++)
		{
			fprintf(pFile, "%d\n\n", m_nRankingScoreList[nCnt]);	// ポイント
			std::cout << "SaveScore - " << nCnt << " - Score >> " << m_nRankingScoreList[nCnt] << NEWLINE;
		}
		// ファイル閉
		fclose(pFile);
	}
	// 開けない
	else
	{
		std::cout << "Score SAVEFAILED!! can't open file!" << NEWLINE;
		return E_FAIL;
	}

	return S_OK;
}