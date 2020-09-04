#pragma once
//====================================================================
//
//盾の処理 [Shield.h]
//Author : のりさん
//
//====================================================================
#ifndef _SHIELD_H_
#define _SHIELD_H_

//====================================================================
//インクルードファイル
//====================================================================
#include "main.h"
#include "model.h"
//====================================================================
//前方宣言
//====================================================================
//====================================================================
//シールド
//====================================================================
class CWeakEnemy;

class CShield : public CModel , public CGameObject
{
public:
	CShield() {};
	CShield(OBJ_TYPE type);											// コンストラクタ
	~CShield();														// デストラクタ

	HRESULT	Init();													// 初期化
	void	Uninit();												// 終了
	void	Update();												// 更新
	void	Draw();													// 描画
	static	CShield	* Create();
	int		GetLife() { return m_nLife; };
	int		SetLife(int life) { m_nLife = life;};					//体力の設定
	void	AddDamage(int nLIfe);
	void	SetHandMtx(D3DXMATRIX *pMtx) { m_HasHandMtx = pMtx; };
	void	SetHasEnemyPtr(CWeakEnemy *pEnemy) { m_HasEnemyPtr = pEnemy; };
	void	AwayShield();


	D3DXVECTOR3 GetShieldPos() { return m_ShieldPos; };

private:
	/* メンバ変数 */
	int					m_nLife;						// 体力
	int					m_nCntState;					// カウンタ
	int					m_nDeleteCnt;					// 盾が破壊されてから消えるまでのカウント
	D3DXVECTOR3			m_ShieldPos;					// 盾の座標　コリジョン用
	D3DXMATRIX			*m_HasHandMtx;					// 持ち手のマトリックス
	CWeakEnemy			*m_HasEnemyPtr;					// 持ってる敵のポインタ
	bool				m_bBreak;						// 破壊状態
	D3DXVECTOR3			m_BreakShieldMoveValue;			// 盾が破壊された時の吹っ飛ぶ方向
	D3DXVECTOR3			m_BreakShieldRotValue;			// 盾が破壊された時の回転量

};
#endif
