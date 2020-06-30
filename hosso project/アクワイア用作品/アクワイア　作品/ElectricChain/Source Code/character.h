//------------------------------------------------------------------------------
//
//キャラクター処理  [character.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _CHARACTER_H_
#define _CHARACTER_H_
//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "main.h"
#include "scene.h"
#include "motion.h"
//------------------------------------------------------------------------------
//クラス定義
//------------------------------------------------------------------------------
class CModelCharacter;
class CCollision;

//初期パラメータのクラス
class CDefaultParam
{
public:
	//コンストラクタ
	CDefaultParam()
	{
		//初期化
		m_nMaxLife = 0;
		m_fMoveSpeed = 0.0f;
		m_fDashSpeed = 0.0f;
		m_fJumpSpeed = 0.0f;
		m_fAirSpeed = 0.0f;
		m_nInvincibleTime = 0;
	}

	void SetMaxLife(int nLife)								{ m_nMaxLife = nLife; };							//ライフ
	void SetMoveSpeed(float fMoveSpeed)						{ m_fMoveSpeed = fMoveSpeed; };						//移動速度
	void SetDashSpeed(float fDashSpeed)						{ m_fDashSpeed = fDashSpeed; };						//ダッシュ速度
	void SetJumpSpeed(float fJumpSpeed)						{ m_fJumpSpeed = fJumpSpeed; };						//ジャンプ速度
	void SetAirSpeed(float fAirSpeed)						{ m_fAirSpeed = fAirSpeed; };						//空中移動速度
	void SetInvincinbleTime(int nInvincinbleTime)			{ m_nInvincibleTime = nInvincinbleTime; };			//無敵時間

	int	GetMaxLife()				{ return m_nMaxLife; };					//最大ライフ取得
	float GetMoveSpeed()			{ return m_fMoveSpeed; };				//移動速度取得
	float GetDashSpeed()			{ return m_fDashSpeed; };				//ダッシュ速度取得
	float GetJumpSpeed()			{ return m_fJumpSpeed; };				//ジャンプ速度取得
	float GetAirSpeeed()			{ return m_fAirSpeed; };				//ジャンプ速度取得
	int	GetInvincibleTime()			{ return m_nInvincibleTime; };			//無敵時間取得

private:
	int m_nMaxLife;															//最大HP
	float m_fMoveSpeed;														//移動速度
	float m_fDashSpeed;														//ダッシュ速度
	float m_fJumpSpeed;														//ジャンプ速度
	float m_fAirSpeed;														//ダッシュ速度
	int m_nInvincibleTime;													//無敵時間
};

//キャラクターのクラス
class CCharacter : public CScene
{
public:

	//パラメータ
	enum PARAM_TYPE
	{
		PARAM_PLAYER = 0,		//プレイヤー
		PARAM_ENEMY,			//敵
		PARAM_ENEMY_GREEN,		//緑の敵　素早い
		PARAM_ENEMY_BLACK,		//黒の敵　強敵
		PARAM_MAX
	};

	//状態
	enum STATE
	{
		STATE_NONE = -1,		//none
		STATE_NORMAL,			//通常状態
		STATE_DAMAGE,			//被ダメージ中
		STATE_STAN,				//スタン中
		STATE_DEATH,			//死亡
	};

	CCharacter();
	~CCharacter();

	virtual HRESULT Init();									//初期化
	virtual void Uninit();									//終了
	virtual void Update();									//更新
	virtual void Draw();									//描画
	virtual void ShowDebugInfo();							//デバッグ情報表記
	virtual void DamageAction() = 0;						//ダメージ受けた時のリアクション
	virtual void DeathAction() = 0;							//死亡時のリアクション
	virtual void AttackTurning() = 0;						//攻撃時に旋回する
	virtual void SetState(STATE nextstate);					//ステート変更処理

	bool ApplyDamage(int nDamage, int nBlueDamage);								//ダメージ処理
	void KnockBack(float fKnockBack_Front, float fKockBack_Up,float fAngle);	//ノックバック

	//Set関数
	void SetPos(D3DXVECTOR3 const &pos)						{ m_pos = pos; };									//座標設定
	void SetMove(D3DXVECTOR3 const &move)					{ m_move = move; };									//移動設定
	void SetRot(D3DXVECTOR3 const &rot)						{ m_rot = rot; }; 									//回転設定
	void SetRotDest(D3DXVECTOR3 const &rotdest)				{ m_rotDest = rotdest; };							//回転の決定先設定
	void SetLife(int nLife)									{ m_nLife = nLife; };								//ライフ
	void SetBlueLife(int nBlueLife)							{ m_nBlueLife = nBlueLife; };						//青のライフ
	void SetAttack(bool bAttack)							{ m_bAttack = bAttack; };							//攻撃してる状態
	void SetJump(bool bJump)								{ m_bJump = bJump; };								//ジャンプ状態
	void SetJumpInterval(bool bJumpInterval)				{ m_bJumpInterval = bJumpInterval; };				//ジャンプのインターバル
	void SetAirAttack(bool bAirAttack)						{ m_bAirAttack = bAirAttack; };						//空中攻撃したか
	void SetContinueAttack	(bool bContinueAttack)			{ m_bContinueAttack = bContinueAttack; };			//続けて攻撃できるか
	void SetInvincible(bool bInvincible)					{ m_bInvincible = bInvincible; };					//無敵時間かどうか
	void SetAlive(bool bAlive)								{ m_bAlive = bAlive; };								//生きてるかどうか
	void SetCntState(int nCntState)							{ m_nCntState = nCntState; };						//カウントステート設定
	void SetChangeMotion(bool bChangeMotion)				{ m_bChangeMotion = bChangeMotion; };				//モーション変更したか

	void SetGravity(bool bGravity, int nCntGravity) { m_bGravity = bGravity; m_nCntGravity = nCntGravity; };	//重力かけるか
	void SetParameter(MODEL_TYPE modeltype, PARAM_TYPE m_Paramtype,std::shared_ptr<CCharacter> MyPtr);			//パラメータ設定

	static HRESULT LoadDefaultParam();					//初期パラメータ読み込み

	//Get関数
	D3DXVECTOR3		 &GetPos()								{ return m_pos; };									//座標取得
	D3DXVECTOR3		 &GetMove()								{ return m_move; };									//移動取得
	D3DXVECTOR3		 &GetRot()								{ return m_rot; };									//回転取得
	D3DXVECTOR3		 &GetRotDest()							{ return m_rotDest; };								//回転の決定先取得
	D3DXMATRIX		*GetMtx()								{ return &m_mtxWorld; };							//ワールドマトリックス取得
	CCollision		*GetCollision()							{ return m_pCollision.get(); };						//コリジョン   のポインタ取得
	int				GetLife()								{ return m_nLife; };								//ライフ取得
	int				GetBlueLife()							{ return m_nBlueLife; };							//ブルーライフ取得
	int				GetCntState()							{ return m_nCntState; };							//カウントステート取得
	PARAM_TYPE		GetParamType()							{ return m_Paramtype; };							//パラメータの種類取得
	MODEL_TYPE		GetModelType()							{ return m_modeltype; };							//モデルの種類取得
	bool			&GetJump()								{ return m_bJump; };								//ジャンプしているかどうかの取得
	bool			GetJumpInterval()						{ return m_bJumpInterval; };						//ジャンプのインターバル
	bool			GetAttack()								{ return m_bAttack; };								//攻撃してるかどうか取得
	bool			GetInvincible()							{ return m_bInvincible; };							//無敵かどうか取得
	bool			GetGravity()							{ return m_bGravity; };								//重力かけるかどうか
	bool			GetAirAttack()							{ return m_bAirAttack; };							//空中攻撃
	bool			GetContinueAttack()						{ return m_bContinueAttack; };						//続けて攻撃できるか
	bool			GetChangeMotion()						{ return m_bChangeMotion; };						//モーション変更したかどうか
	bool			GetAlive()								{ return m_bAlive; };								//生きていたかどうか
	CDefaultParam	*GetDefaultParam(PARAM_TYPE type)		{ return m_DefaultParam[type].get(); };				//初期パラメータ取得
	STATE			GetState()								{ return m_State; };								//状態取得
	CModelCharacter	*GetModelCharacterPtr()					{ return m_pModelCharacter.get(); };				//モデルキャラクター情報取得

	D3DXVECTOR3		 GetCenterPos()							{ return m_pos + D3DXVECTOR3(0.0f,m_fCenterPosOffset,0.0f); };		//キャラクターの中心座標取得　エフェクトとかの発生源
	CMotion::MOTION_TYPE GetNowMotion();																						//現在のモーション取得 インクルードされてないからインライン不可
protected:

	void ShowCharacterInfo();								//キャラクター情報表示
	void ChangeMotion(CMotion::MOTION_TYPE nextmotion);		//モーション切り替え
	bool ContinueAttack();									//連続攻撃
	virtual void Collision();								//当たり判定系の処理
private:
	D3DXVECTOR3 m_pos;										//座標
	D3DXVECTOR3 m_posOld;									//1F前の座標
	D3DXVECTOR3 m_move;										//移動距離
	D3DXVECTOR3 m_rot;										//現在の回転
	D3DXVECTOR3 m_rotDest;									//回転の目的地
	D3DXVECTOR3 m_rotDif;									//回転の差分
	D3DXMATRIX m_mtxWorld;									//ワールドマトリックス
	std::unique_ptr<CModelCharacter> m_pModelCharacter;		//モデルのポインタ
	std::unique_ptr<CCollision> m_pCollision;				//コリジョンのポインタ
	MODEL_TYPE m_modeltype;									//モデルの種類
	PARAM_TYPE m_Paramtype;									//パラメータの種類
	STATE m_State;											//キャラクターの状態

	bool m_bJump;											//ジャンプしているかどうか
	bool m_bJumpInterval;									//連続ジャンプ防止　着地してから少しインターバルを設ける用
	bool m_bAttack;											//攻撃してるか
	bool m_bInvincible;										//無敵状態かどうか
	bool m_bGravity;										//重力かかるかどうか
	bool m_bAirAttack;										//空中攻撃したか
	bool m_bContinueAttack;									//続けて攻撃できるか
	bool m_bChangeMotion;									//このフレーム中にモーションを変更したかどうか
	bool m_bAlive;											//生きてるか

	int m_nLife;											//HP
	int m_nBlueLife;										//青のHP
	int m_nCntState;										//状態遷移のカウンタ
	int m_nCntGravity;										//無重力状態のカウンタ
	int m_nCntJumpInterval;									//着地してから再ジャンプまでのインターバル

	float m_fCenterPosOffset;								//体の中心の高さまでのオフセット

	void Move();											//移動関数
	void Rot();												//回転関数
	void State();											//状態に応じた処理

	static std::vector<std::string>	m_aParamFileName;						//パラメータ用のファイル名
	static std::vector<std::unique_ptr<CDefaultParam>> m_DefaultParam;		//初期パラメータ
};
#endif