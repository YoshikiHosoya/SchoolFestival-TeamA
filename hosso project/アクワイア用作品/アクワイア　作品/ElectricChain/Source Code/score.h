//------------------------------------------------------------------------------
//
//スコア処理  [score.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _SCORE_H_
#define _SCORE_H_
//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "main.h"

//------------------------------------------------------------------------------
//クラス定義
//------------------------------------------------------------------------------

//前方宣言
class CMultiNumber;

class CScore
{
public:
	enum SCORE_TYPE
	{
		SCORE_KILL = 0,
		SCORE_COMBO,
		SCORE_NOWCHAIN,

		SCORE_NUMCHAIN,		//使うかわからｎ
		SCORE_MAX
	};

	CScore();
	~CScore();
	HRESULT Init();													//初期化
	void Uninit();													//終了
	void Update();													//更新
	void Draw();													//描画
	static std::unique_ptr<CScore> Create();						//生成処理

	static int GetRankingScore(int nRank);							//ランキングのスコア取得
	static HRESULT LoadScore();										//スコアロード
	HRESULT SaveScore();											//スコアロード

	//Add関数
	void AddKill(int nValue);										//キル数
	void AddCombo(int nValue);										//コンボ数
	void AddNumChain(int nValue);									//チェイン数

	void SetNowChain();

	//Get関数
	int GetNowChainNum()	{ return m_nNowChain; };				//現在のチェイン数
	int GetNumChainNum()	{ return m_nNumChain;};					//チェイン総数
	static int GetScore()	{ return m_nScore; };					//スコア取得
	static int GetCombo()	{ return m_nCombo; };					//コンボ数取得
	static int GetKill()	{ return m_nKill; };					//キル数取得

private:
	std::vector<std::shared_ptr<CMultiNumber>> m_pMultiNumberLIst;	//ナンバーのポインタのリスト
	static std::vector<int> m_nRankingScoreList;					//ランキング用のスコア
	static int m_nScore;											//最終的なスコア
	static int m_nKill;												//キル数
	static int m_nCombo;											//コンボ数

	int m_nNowChain;												//現在のチェイン数
	int m_nNumChain;												//チェイン数
};

#endif