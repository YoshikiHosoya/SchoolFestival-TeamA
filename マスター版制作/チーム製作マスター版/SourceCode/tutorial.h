// =====================================================================================================================================================================
//
// チュートリアルの処理 [tutorial.h]
// Author : fujiwara masato
//
// =====================================================================================================================================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

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
class CTutorialManager;
class CMap;
class CPlayer;

// =====================================================================================================================================================================
// マクロ定義
// =====================================================================================================================================================================
#define MAX_TUTORIAL_TEXTURE (5)
// =====================================================================================================================================================================
// タイトルクラス
// =====================================================================================================================================================================
class CTutorial :public CBaseMode
{
public:

	/* メンバ関数 */
	CTutorial();								// コンストラクタ
	~CTutorial();								// デストラクタ
	HRESULT Init(void);							// 初期化処理
	void Uninit(void);							// 終了処理
	void Update(void);							// 更新処理
	void Draw(void);							// 描画処理
	void ShowDebugInfo(void);					// デバッグ情報表記

	/* メンバ関数 */
	CPlayer* GetPlayer(TAG Tag) { return m_pPlayer[(int)Tag]; };
	CMap* GetMap() { return m_pMap; };
private:
	/* 静的メンバ変数 */
	static CMap					*m_pMap;
	static CPlayer				*m_pPlayer[MAX_CONTROLLER];

	/* メンバ変数 */
	CTutorialManager	*m_pTutorialManager;
};
#endif