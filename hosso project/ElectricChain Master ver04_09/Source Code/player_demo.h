//------------------------------------------------------------------------------
//
//デモ用のプレイヤー処理  [player_demo.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _PLAYER_DEMO_H_
#define _PLAYER_DEMO_H_
//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "main.h"
#include "player.h"

//------------------------------------------------------------------------------
//前方宣言
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//クラス定義
class CEnemy;

class CPlayer_Demo : public CPlayer
{
public:
	//攻撃の入力
	enum ATTACK_INPUT
	{
		ATTACK_NONE,	//攻撃してない
		ATTACK_X,		//Xボタン
		ATTACK_Y,		//Yボタン
		ATTACK_B,		//Bボタン
		ATTACK_MAX
	};

	CPlayer_Demo();													//コンストラクタ
	~CPlayer_Demo();												//デストラクタ

	HRESULT Init();													//初期化
	void Uninit();													//終了
	void Update();													//更新
	void Draw();													//描画
	void ShowDebugInfo();											//デバッグ情報表記
	static std::shared_ptr<CPlayer_Demo> Create(D3DXVECTOR3 pos);	//生成

private:
	ATTACK_INPUT m_AttackInput;										//攻撃の入力
	void MoveAI();													//移動の入力
	bool AttackInput();												//攻撃の入力処理
	void SetTargetEnemy();											//ターゲットの敵設定

	std::weak_ptr<CEnemy> m_pTargetEnemy;							//ターゲットの敵のポインタ
};
#endif