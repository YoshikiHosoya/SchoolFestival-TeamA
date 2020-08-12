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
#include "Obstacle.h"
//====================================================================
//前方宣言
//====================================================================
//====================================================================
//シールド
//====================================================================
class CShield : public CObstacle
{
public:
	CShield(OBJ_TYPE type);											// コンストラクタ
	~CShield();														// デストラクタ

	HRESULT	Init();													// 初期化
	void	Uninit();												// 終了
	void	Update();												// 更新
	void	Draw();													// 描画
static	CShield	* Create(D3DXMATRIX *mtx);
	int		GetLife() { return m_nLife; };
	int		SetLife(int life) { m_nLife = life;};					//体力の設定
private:
	/* メンバ変数 */
	int							m_nLife;							// 体力
	D3DXMATRIX			*m_HasHandMtx;			// 持ち手のマトリックス

};
#endif
