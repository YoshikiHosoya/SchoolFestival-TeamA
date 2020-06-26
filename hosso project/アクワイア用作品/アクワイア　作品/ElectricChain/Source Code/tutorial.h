//------------------------------------------------------------------------------
//
//チュートリアル処理  [tutorial.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_
//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "main.h"
#include "basemode.h"

//------------------------------------------------------------------------------
//マクロ
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//クラス定義
//------------------------------------------------------------------------------
class CScene2D;
class CPlayer;

class CTutorial : public CBaseMode
{

public:
	CTutorial();
	~CTutorial();
	enum TUTORIAL_STEP
	{
		TUTORIAL_NONE = -1,						//
		TUTORIAL_MOVE,							//移動
		TUTORIAL_DASH,							//ダッシュ
		TUTORIAL_CAMERAMOVE,					//カメラ旋回
		TUTORIAL_CAMERARESET,					//視点リセット
		TUTORIAL_JUMP,							//ジャンプ
		TUTORIAL_ATTACK,						//通常攻撃
		TUTORIAL_START_CHAIN,					//トドメ
		TUTORIAL_CHAINTHUNDER,					//連鎖爆発の説明
		TUTORIAL_FREE,							//自由
		TUTORIAL_END,							//チュートリアルおしまい
		TUTORIAL_MAX,							//
	};

	HRESULT Init(HWND hWnd);					//初期化
	void Uninit();								//終了
	void Update();								//更新
	void Draw();								//描画
	void ShowDebugInfo();						//デバッグ情報表記
private:
	TUTORIAL_STEP m_step;								//現在の項目

	std::shared_ptr<CScene2D> m_pTutorialStep;			//チュートリアルのポリゴンへのポインタ
	std::shared_ptr<CPlayer> m_pPlayer;					//プレイヤーのポインタ
	std::shared_ptr<CScene2D> m_pOK;					//OK! のポインタ
	CPlayer* GetPlayer();								//プレイヤーのポインタ取得関数

	bool m_bClear;						//クリア状態
	bool m_bEnemyPop;					//敵出現させるか
	int m_nEnemyPopTime;				//敵出現カウント
	int m_nCntStep;						//次の項目に移行する時のインターバル用のカウント

	void CheckTutorialAction();			//アクションしてるかチェック
	void ActionClear();					//アクションクリア
	void NextStep();					//次のステップに移行
	void TutorialEnemyPop();			//チュートリアル用に敵をポップ
};
#endif