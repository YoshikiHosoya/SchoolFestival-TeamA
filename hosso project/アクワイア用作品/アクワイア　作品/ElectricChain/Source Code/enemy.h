//------------------------------------------------------------------------------
//
//エネミー処理  [enemy.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _ENEMY_H_
#define _ENEMY_H_
//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "main.h"
#include "character.h"

//------------------------------------------------------------------------------
//前方宣言
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//クラス定義
//------------------------------------------------------------------------------
class CGauge_3D;

class CEnemy : public CCharacter
{
public:
	//AIのパターン
	enum AI_MOVE
	{
		AI_NEUTRAL = 0,				//ニュートラル
		AI_RANDOM_MOVE,				//ランダムに移動
		AI_PLAYER_FOLLOWING,		//プレイヤーの方向に移動
		AI_ATTACK,					//攻撃
	};

	//敵の種類
	enum ENEMY_TYPE
	{
		TYPE_NORMAL = 0,			//通常
		TYPE_TUTORIAL_STANING,		//チュートリアルのスタン状態のやつ
		TYPE_SPEEDY,				//高速移動
		TYPE_STRONG,				//強敵
		TYPE_MAX
	};

	CEnemy();																						//コンストラクタ
	~CEnemy();																						//デストラクタ

	HRESULT Init();																					//初期化
	void Uninit();																					//終了
	void Update();																					//更新
	void Draw();																					//描画
	void ShowDebugInfo();																			//デバッグ情報表記
	void DamageAction();																			//HPゲージ更新
	void DeathAction();																				//死亡時のリアクション
	void AttackTurning();																			//攻撃時の旋回
	void Collision();																				//当たり判定
	static std::shared_ptr<CEnemy> Create(D3DXVECTOR3 const pos, ENEMY_TYPE const enemytype);		//生成
	static void ChainExplosion(D3DXVECTOR3 pos);													//連鎖爆発処理
	void SetState(STATE nextstate);																	//ステート変更処理

	//SET関数
	void SetStan(bool bStan)				{ m_bStan = bStan; };				//スタン設定
	void SetContact(bool bContact)			{ m_bContact = bContact; };			//接触

	//GET関数
	bool GetStan()							{ return m_bStan; };				//スタン状態か取得
	bool GetContact()						{ return m_bContact; };				//接触

	static int	GetEnemyNum()				{ return m_nNumEnemy; };			//敵の総数取得
	static int	GetStanEnemyNum()			{ return m_nNumStanEnemy; };		//スタン状態の敵の総数取得
	static void ResetEnemyStaticInfo();											//static関係の情報リセット

private:
	static int m_nNumEnemy;								//敵の総数
	static int m_nNumStanEnemy;							//スタン状態の敵の総数
	static bool m_bChain;								//このFでチェインしたか
	std::shared_ptr<CGauge_3D> m_pGauge;				//ゲージのポインタ
	bool m_bStan;										//スタンしているかどうか
	bool m_bContact;									//接触

	ENEMY_TYPE m_enemytype;								//敵の種類
	AI_MOVE m_AIMove;									//AIの状態
	int m_nCntAIMove;									//AIMove用のカウンタ
	float m_fMoveAngle;									//移動の方向


	void HyperKnockBack();								//超吹っ飛ぶ
	void AIMove();										//AIで移動
	void StartStan();									//スタン開始
};
#endif