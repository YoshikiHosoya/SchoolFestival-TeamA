//------------------------------------------------------------------------------
//
//ゲーム処理  [game.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _GAME_2D_H_
#define _GAME_2D_H_
//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "game.h"
//------------------------------------------------------------------------------
//マクロ
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//クラス定義
//------------------------------------------------------------------------------
class CWay;

class CGame_2D : public CGame
{
public:
	CGame_2D();
	~CGame_2D();
	HRESULT Init(HWND hWnd);								//初期化
	void Uninit();											//終了
	void Update();											//更新
	void Draw();											//描画
	void ShowDebugInfo();									//デバッグ情報表記


	float GetSpeed() { return m_fSpeed; };
	DIRECTION GetDirection() { return m_direction; };
	void Bending();
	void PlayerBending(DIRECTION Direction);
protected:
private:
	int m_nCnt;
	float m_fSpeed;										//移動速度
	float m_fScoreDistance;								//総合距離
	DIRECTION m_direction;								//向き

	float m_fNextBendingPoint;							//次の曲がり角までの距離
	DIRECTION m_NextBendingDirection;					//次の曲がり角の方向
	bool m_bBendingFlag;								//曲がりのフラグ
	int m_nBendingTime;									//曲がってる時間

	std::vector<std::shared_ptr<CWay>> m_pWayList;


};

#endif