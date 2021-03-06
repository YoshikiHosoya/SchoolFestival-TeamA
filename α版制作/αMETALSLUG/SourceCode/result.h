// =====================================================================================================================================================================
//
// リザルトの処理 [result.h]
// Author : fujiwara masato
//
// =====================================================================================================================================================================
#ifndef _RESULT_H_
#define _RESULT_H_

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
class CResultUI;

// =====================================================================================================================================================================
// マクロ定義
// =====================================================================================================================================================================
#define MAX_RESULT_TEXTURE (5)
// =====================================================================================================================================================================
// タイトルクラス
// =====================================================================================================================================================================
class CResult :public CBaseMode
{
public:
	/* メンバ関数 */
	CResult();					// コンストラクタ
	~CResult();					// デストラクタ
	HRESULT				Init(void);							// 初期化処理
	void				Uninit(void);						// 終了処理
	void				Update(void);						// 更新処理
	void				Draw(void);							// 描画処理
	void				ShowDebugInfo(void);				// デバッグ情報表記
	/* メンバ関数 */
	CPlayer				*GetPlayer() { return nullptr; };	// プレイヤーのポインタ取得
	CMap				*GetMap() { return nullptr; };		// マップのポインタ取得
private:
	/* メンバ変数 */
	CResultUI			*m_pResultUI;						// リザルトUIのポインタ
};
#endif