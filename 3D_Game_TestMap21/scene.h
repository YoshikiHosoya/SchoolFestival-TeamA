// =====================================================================================================================================================================
//
// シーンの処理 [scene.h]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

#include "main.h"
#include "manager.h"

// =====================================================================================================================================================================
// マクロ定義
// =====================================================================================================================================================================
#define		MAX_SCENE		(128)

// =====================================================================================================================================================================
// オブジェクトクラス
// =====================================================================================================================================================================
class CScene
{
public:
	// 描画順
	enum PRIORITY
	{
		PRIORITY_NONE = -1,
		PRIORITY_BG,												 // 背景
		PRIORITY_ITEM,												 // アイテム
		PRIORITY_WALL,												 // 壁
		PRIORITY_MODEL,												 // モデル
		PRIORITY_2DOBJECT,											 // 2Dオブジェクト
		PRIORITY_EFFECT,											 // エフェクト
		PRIORITY_UI,												 // UI
		PRIORITY_MAX,
	};

	CScene();										// コンストラクタ
	CScene(PRIORITY Priority);						// コンストラクタ
	virtual~CScene();								// デストラクタ

	/* メンバ関数 */
	virtual void	Init() = 0;						// 初期化
	virtual void	Uninit() = 0;					// 終了
	virtual void	Update() = 0;					// 更新
	virtual void	Draw() = 0;						// 描画
	virtual void	SetPos(D3DXVECTOR3 pos) = 0;	// セットポジション

	/* 静的メンバ関数 */
	static void		ReleaseAll();					// オブジェクトの破棄
	static void		UpdateAll();					// オブジェクトの更新
	static void		DrawAll();						// オブジェクトの描画
	static	void	SetPauseStop(bool stop);		// ポーズで止める設定

	/* メンバ関数 */
	void			Release();						// 解放

private:
	/* メンバ関数 */
	void			Death(void);						// 死亡フラグ後に開放
	/* 静的メンバ変数 */
	static int		m_nNumAll;							// 総数
	static CScene	*m_apTop[CScene::PRIORITY_MAX];		// 先頭オブジェクトへのポインタ
	static CScene	*m_apCur[CScene::PRIORITY_MAX];		// 現在(最後尾)オブジェクトへのポインタ
	static	bool	m_bStop;							// 止めるフラグ

	/* メンバ変数 */
	int				m_nID;								// 自分の番号
	CScene			*m_apPrev;	// 前のオブジェクトへのポインタ
	CScene			*m_apNext;	// 次のオブジェクトへのポインタ
	bool			m_bDeath;							// 死亡フラグ
	PRIORITY		m_priority;							// 優先順位
};
#endif
