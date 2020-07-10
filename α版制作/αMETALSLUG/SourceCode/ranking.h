// =====================================================================================================================================================================
//
// ランキングの処理 [ranking.h]
// Author : fujiwara masato
//
// =====================================================================================================================================================================
#ifndef _RANKING_H_
#define _RANKING_H_

// =====================================================================================================================================================================
// インクルードファイル
// =====================================================================================================================================================================
#include "main.h"
#include "BaseMode.h"

// =====================================================================================================================================================================
// 前方宣言
// =====================================================================================================================================================================
class CRenderer;
class CKeyboard;
class CRankingUI;

// =====================================================================================================================================================================
// マクロ定義
// =====================================================================================================================================================================
#define MAX_RANKING_TEXTURE (5)
// =====================================================================================================================================================================
// タイトルクラス
// =====================================================================================================================================================================
class CRanking :public CBaseMode
{
public:

	/* メンバ関数 */
	CRanking();									// コンストラクタ
	~CRanking();								// デストラクタ
	HRESULT Init(void);							// 初期化処理
	void Uninit(void);							// 終了処理
	void Update(void);							// 更新処理
	void Draw(void);							// 描画処理
	void ShowDebugInfo(void);					// デバッグ情報表記

	/* メンバ関数 */
	CPlayer* GetPlayer() { return nullptr; };
	CMap* GetMap() { return nullptr; };
private:
	/* メンバ変数 */
	CRankingUI		*m_pRankingUI;				// ランキングUIのポインタ
};
#endif