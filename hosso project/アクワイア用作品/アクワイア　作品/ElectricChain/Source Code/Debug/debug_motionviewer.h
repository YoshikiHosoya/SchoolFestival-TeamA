//------------------------------------------------------------------------------
//
//モーションビューワ用処理  [CDebug_MotionViewer.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _DEBUG_MOTIONVIEWER_H_
#define _DEBUG_MOTIONVIEWER_H_
//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "../main.h"
#include "../basemode.h"
//------------------------------------------------------------------------------
//マクロ
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//クラス定義
//------------------------------------------------------------------------------
//前方宣言
class CDebug_Character;

class CDebug_MotionViewer : public CBaseMode
{
public:
	//ゲームの状態遷移
	enum STATE
	{
		STATE_NONE = -1,				//始まってない
		STATE_NORMAL,					//通常状態　信仰
		STATE_DEBUG,					//デバッグ状態
		STATE_MAX
	};

	CDebug_MotionViewer();
	~CDebug_MotionViewer();
	HRESULT Init(HWND hWnd);			//初期化
	void Uninit();						//終了
	void Update();						//更新
	void Draw();						//描画
	void ShowDebugInfo();				//デバッグ情報表記

	void SetGamestate(STATE gamestate);	//ゲームの状態設定
	STATE GetGamestate();				//ゲームの状態取得
	CDebug_Character *GetDebugChara() { return m_pCharacter.get(); };	//キャラクターのデータ取得

	CPlayer* GetPlayer() { return nullptr; };

private:
	std::shared_ptr<CDebug_Character> m_pCharacter;		//キャラクターへのポインタ
	STATE m_State;										//ゲームステート
	int m_nCntState;									//ステートのカウンタ

	int m_nModelType;									//モデルのタイプ
	int m_nParamText;									//パラメータ

	void DebugCommand();								//デバッグ用の処理
};

#endif