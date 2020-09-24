#pragma once
// =====================================================================================================================================================================
//
// キャラクターの処理 [Character.h]
// Author :Hanzawa
//
// =====================================================================================================================================================================
#ifndef _CHARACTER_H_
#define _CHARACTER_H_
#include "main.h"
#include "Scene.h"
#include "manager.h"
#include "renderer.h"

#define MAX_MODEL (20)			//モデルのパーツ数
class CModel;
class CCollision;
class CModelSet;
//レンダリングクラス
class CCharacter :public CScene
{
public:
	typedef enum
	{
		CHARACTER_STATE_NONE,
		CHARACTER_STATE_NORMAL,
		CHARACTER_STATE_ITEMGET_FLASH,
		CHARACTER_STATE_DAMAGE_FLASHING,
		CHARACTER_STATE_DAMAGE_RED,
		CHARACTER_STATE_DEATH,
		CHARACTER_STATE_INVINCIBLE,
	}CHARACTER_STATE;

	CCharacter() {};
	CCharacter(OBJ_TYPE type);
	~CCharacter();
	virtual HRESULT Init(void) override;			//初期化
	virtual void Uninit(void) override;				//終了
	virtual void Update(void) override;				//更新
	virtual void Draw(void) override;				//描画
	virtual void DebugInfo(void) override;			//デバッグ用関数
	virtual bool DefaultMotion(void) = 0;			//デフォルトのモーションセット
	virtual void DamageReaction();					//ダメージ時のリアクション
	virtual void DeathReaction();					//死亡のリアクション
	virtual void State();							//ステートに応じた処理
	virtual void StateChangeReaction();				//ステート変更処理

	void Move(float move, float fdest, float fSpeed = 4.0f);
	void AddDamage(int Damage);
	void ForcedUpdate();						//強制的にモーションチェンジ
	void ResetCharacterDirection();				//回転量を基に向きを設定しなおす

	//セッツ
	void SetPosition(D3DXVECTOR3 pos);
	void SetPotisionOld(D3DXVECTOR3 posOld);
	void SetMove(D3DXVECTOR3 move);
	void SetRot(D3DXVECTOR3 rot);
	void SetRotDest(D3DXVECTOR3 rotDest);
	void SetLife(int Life);
	void SetJump(bool bJump);
	void SetState(CHARACTER_STATE state);
	void SetStateCount(int nCntState);
	void SetMtxWorld(D3DXMATRIX mtxWorld);
	void SetGravity(bool gravity);
	void SetCharacterDirection(DIRECTION direction);
	void SetShotDirection(D3DXVECTOR3 direction);
	void SetRotArm(bool use);
	void SetArmCalculation(int nCnt);
	//ゲット
	D3DXVECTOR3 &GetPosition(void);				//ポジション
	D3DXVECTOR3 &GetPositionOld(void);			//前のポジション
	D3DXVECTOR3 &GetMove(void);					//移動
	D3DXVECTOR3 &GetRot(void);					//回転
	D3DXVECTOR3 &GetRotDest(void);				//回転の差分
	D3DXVECTOR3 GetShotDirection(void);
	D3DXMATRIX *GetMtxWorld(void);
	CHARACTER_STATE GetCharacterState(void);
	CModelSet *GetModelSet(void);
	int &GetLife(void);
	bool GetJump(void);
	bool GetGravity(void);
	float GetHeightBet(void);
	DIRECTION &GetCharacterDirection(void);							//向きの取得
	DIRECTION &GetCharacterDirectionOld(void);						//1F前の向きの取得

	//モーション関連
	void SetDieFlag(bool DieFlag)					{ m_bDieFlag = DieFlag; };					// 死亡フラグの設定
	void SetFallFlag(bool bFall)					{ m_bFall = bFall; };						// 落下フラグの設定

	D3DXVECTOR3 *GetPositionPtr()					{ return &m_pos; };							//座標のポインタ取得
	bool GetDieFlag()								{ return m_bDieFlag; };						// 死亡フラグの取得
	bool GetDraw()									{ return m_bDraw; };						// 描画するかどうか取得
	bool GetFallFlag()								{ return m_bFall; };						// 落下フラグの取得
	int GetCharacterStateCnt()						{ return m_nStateCnt; };					// キャラクターのステートのカウント

	//void ChangeColor(bool ColorChangeFlag, D3DXCOLOR AddColor);									// 色変更
	bool CheckDrawRange();


	CCollision *GetCollision() { return m_pCollision; };			// 当たり判定のポインタ取得
	virtual void Collision();										//当たり判定処理

private:
	D3DXVECTOR3 m_rotBET[MAX_MODEL];
	float m_HeightBet;
	D3DXVECTOR3 m_pos;												//位置
	D3DXVECTOR3 m_posfall;											//落ちた位置
	D3DXVECTOR3 m_posold;											//前の位置
	D3DXVECTOR3 m_move;												//移動量
	D3DXVECTOR3 m_rot;												//回転
	D3DXVECTOR3 m_rotDest;											//回転する差分
	D3DXVECTOR3 m_ShotRotDest;										//撃つ向きの決定地　ヘビーマシンガン用
	D3DXVECTOR3 m_AddHeadRot;
	D3DXVECTOR3 m_AddArmRot;
	D3DXMATRIX  m_mtxWorld;											//マトリックス
	CHARACTER_STATE m_state;										//

	int m_Life;														//ライフ
	int m_nStateCnt;												//ステータスのカウント
	bool m_bGravity;												//重力がかかっているか
	bool m_bCanJump;												//ジャンプしているかどうか
	bool m_bDieFlag;												// 死亡フラグ
	bool m_bMotion;													//モーションするかどうか
	bool m_bFall;													//モーションするかどうか
	bool m_bDraw;													//描画するかどうか
	bool m_bRotArm;
	DIRECTION	m_CharacterDirection;								//キャラクターの向き
	DIRECTION	m_CharacterDirectionOld;							//1F前のキャラクターの向き

	//モーション関連の情報
	CCollision				*m_pCollision;							//当たり判定のポインタ
	CModelSet *m_pModelSet;											//モデルの情報

	void CalcShotDirection();										//撃つ方向決める
	void CalcMove();												//移動の計算
	void CalcRotation();											//回転の計算
};
#endif