// =====================================================================================================================================================================
//
// タイトルの処理 [title.h]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

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
class CPlayer;
class CMap;

// =====================================================================================================================================================================
// タイトルクラス
// =====================================================================================================================================================================
class CTitle :public CBaseMode
{
public:

	CTitle();		// コンストラクタ
	~CTitle();		// デストラクタ

	HRESULT				Init(void);							// 初期化
	void				Uninit(void);						// 終了
	void				Update(void);						// 更新
	void				Draw(void);							// 描画
	void				ShowDebugInfo(void);				//デバッグ

	CPlayer				*GetPlayer(void);					// プレイヤーのポインタ取得
	CMap				*GetMap(void);						// マップのポインタ取得

private:
	static int			m_Counter;							// カウンター
	static CPlayer		*m_pPlayer;							// プレイヤーのポインタ
	static CMap			*m_pMap;							// マップのポインタ

};
#endif