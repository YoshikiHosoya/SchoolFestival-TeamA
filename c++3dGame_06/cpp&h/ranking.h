// ------------------------------------------
//
// ランキングヘッダー処理 [ranking.h]
// Author : Fujiwara Masato
//
// ------------------------------------------
#ifndef _RANKING_H_
#define _RANKING_H_

#define _CRT_SECURE_NO_WARNINGS

// ------------------------------------------
//
// インクルードファイル
//
// ------------------------------------------
#include "main.h"

// ------------------------------------------
//
// マクロ定義
//
// ------------------------------------------

// ------------------------------------------
//
// 前方宣言
//
// ------------------------------------------

// ------------------------------------------
//
// クラス
//
// ------------------------------------------
class CRanking
{
public:
	/* 関数 */
	CRanking();
	~CRanking();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
protected:
private:
	int m_CntChange;
};
#endif
